/*
 * g++ -o ntt ntt.cpp /usr/local/lib/libz3.so
 */
#include "ntt.h" 

int main ()
{
    z3::context ctx;

    z3::solver s(ctx);

    // 8-bit bit-vector -- allow -128 to 127
    z3::expr dividend = ctx.bv_const("dividend", 32);
    // Set to a 8-bit value -15
    dividend = ctx.bv_val(36, 32);

    // 8-bit bit-vector -- allow -128 to 127
    z3::expr modulus = ctx.bv_const("modulus", 32);
    // Set to a 8-bit value
    modulus = ctx.bv_val(17, 32);

    // Call mod
    z3::expr mod_value = mod(dividend, modulus, ctx, s);

    // Check N-th root calculation 
    int N = 8;
    z3::expr root_of_unity = ctx.bv_const("root_of_unity", 32);
    root_of_unity = ctx.bv_val(15, 32);
    z3::expr_vector vec_temp = make_LUT(N, root_of_unity, modulus, ctx, s);

    if (s.check() == z3::sat)
    {
        std::cout << "Sat" << std::endl;
        z3::model m = s.get_model();
        z3::expr result_mod = m.eval(mod_value);

        std::cout << "Result of " << dividend << " % " << modulus << " using mod: " << result_mod << std::endl;

        
        std::cout << "Result of make_LUT:" << std::endl;
        std::cout << "Size of make_LUT: " << vec_temp.size() << std::endl;
        int i;
        for(i = 0; i < vec_temp.size(); i++)
        {
            z3::expr val = m.eval(vec_temp[i]);
            std::cout << "Index: " << i << " root of unity " << val << std::endl;
        }
    }
    else
    {
        std::cout << "Unsat" << std::endl;
    }

    return 0;
}

/*
 * Modulo of dividend. 
 * If dividend is negative: (modulus + dividend) % modulus
 * If dividend is not negative: dividend % modulus
 */
z3::expr mod(z3::expr dividend, z3::expr modulus, z3::context &ctx, z3::solver &s)
{
    // Declare zero
    z3::expr zero = ctx.bv_val(0, 32);

    // "Bool" for negative
    z3::expr is_negative = dividend < zero;

    // If negative dividend then add by modulus else just dividend 
    z3::expr adjusted_dividend = ite(is_negative, dividend + modulus, dividend);

    // Get quotient 
    z3::expr quotient = adjusted_dividend / modulus;

    // Get remainder
    z3::expr remainder = adjusted_dividend - quotient * modulus;

    //---------- Add constraints to solver----------

    // remainders must never be below zero
    s.add(remainder >= zero);

    // remainders must never be above the modulus
    s.add(remainder < modulus);
    return remainder;
}

z3::expr_vector make_LUT(int N, z3::expr root_of_unity, z3::expr modulus, z3::context &ctx, z3::solver &s)
{
    // Create lookup table and add it to the context
    z3::expr_vector LUT(ctx);

    // Declare one
    z3::expr one = ctx.bv_val(1, 32);
    std::cout << one << std::endl;

    // Iterate for the N-th root of unity
    int k;
    LUT.push_back(one);
    for(k = 1; k < N; k++)
    {
        z3::expr value = LUT[k-1] * root_of_unity;
        z3::expr mod_value = mod(value, modulus, ctx, s);
        LUT.push_back(mod_value);  
    }

    //---------- Add constraints to solver----------
    
    // Check that LUT is the given size N
    z3::expr lut_size = ctx.int_val(LUT.size());
    z3::expr req_size = ctx.int_val(N);
    s.add(lut_size == req_size);

    // Check that the pattern repeats for the next Nth roots
    z3::expr temp_value = mod(LUT[k-1]*root_of_unity, modulus, ctx, s);
    s.add(temp_value == LUT[0]);
    
    int i;
    for(i = 1; i < N; i++)
    {
        temp_value = mod(temp_value*root_of_unity, modulus, ctx, s); 
        s.add(temp_value == LUT[i]);
    }

    return LUT;
}

/*
uint32_t bit_reversal(uint32_t num, size_t N)
{
    uint32_t reverse = 0;
    uint32_t log2N = log2(N);
    size_t j; 
    for(j = 0; j < log2N; j++)
    {
        reverse <<= 1;
        reverse |= (num & 1);
        num >>= 1;
    }

    return reverse;
}

vec_num_t vec_bit_reversal(vec_num_t x)
{
    size_t N = x.size();

    vec_num_t vec_reversed(N);
    uint32_t reversed_index;
    size_t k;
    for (k = 0; k < N; k++)
    {
       reversed_index = bit_reversal(k, N);
       vec_reversed[reversed_index] = x[k]; 
    }

    return vec_reversed;
}

vec_num_t ntt_LUT (vec_num_t x, uint32_t root_of_unity, uint32_t modulus)
{
    // Get size N
    size_t N = x.size();

    if(N % 2 != 0)
    {
        std::cout << "Sample size should be an even number" << std::endl;
        std::terminate();
    }

    // Log2(N)
    size_t log2N = log2(N);

    // Bit reverse a
    vec_num_t A = vec_bit_reversal(x);

    // Make LUT for w
    vec_num_t LUT = make_LUT(N, root_of_unity, modulus);

    size_t m; 
    size_t w_m; 
    size_t w; 
    size_t j; 
    size_t k; 
    uint32_t t;
    uint32_t u;

    for(m = 2; m <= N; m*=2)
    {
        for(j = 0; j < m/2; j++)
        {
            for(k = 0; k < N; k+=m)
            {
                t = mod(LUT[j*N/m]*A[k+j+m/2], modulus);
                u = mod(A[k+j], modulus);
                A[k+j] = mod(u + t, modulus);
                A[k+j+m/2] = mod(u - t, modulus);
                // std::cout << "m: " << m << " j: " << j << " k: " << k << " w " << LUT[j*N/m] << " t: " << t << " u: " << u << " u + t: " << mod(u+t, modulus) << " u - t: " << mod(u-t, modulus) << " A[k+j] = A[" << k+j << "] = " <<  mod(u+t, modulus) << " A[k+j+m/2] = A[" << k+j+m/2 << "] = " << mod(u-t, modulus) << std::endl;

            }
        }
    }
    return A;
}
*/
