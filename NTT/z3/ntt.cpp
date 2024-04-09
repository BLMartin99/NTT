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
    dividend = ctx.bv_val(4, 32);

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
    z3::expr_vector vec_temp = make_LUT(N, 15, modulus, ctx, s);

    // Check bit reversal
    z3::expr temp1 = ctx.bv_const("temp1", 32);
    temp1 = ctx.bv_val(4, 32);
    int temp1_br = bit_reversal(3, N, ctx, s);

    // Check bit reversal vector
    std::vector<int> x; 
    int j;
    for(j = 0; j < N; j++)
    {
        x.push_back(j+1);
    }
    std::vector<int> vec_br = vec_bit_reversal(x, ctx, s);

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

        std::cout << temp1_br << std::endl;

        for(i = 0; i < vec_br.size(); i++)
        {
            int val = vec_br[i];
            std::cout << "Index: " << i << " val: " << val << std::endl;
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
    z3::expr is_negative = edividend < zero;

    // If negative dividend then add by modulus else just dividend 
    z3::expr adjusted_edividend = ite(is_negative, edividend + emodulus, edividend);

    // Get quotient 
    z3::expr equotient = adjusted_edividend / emodulus;

    // Get remainder
    z3::expr eremainder = adjusted_edividend - quotient * modulus;

    //---------- Add constraints to solver----------

    // remainders must never be below zero
    s.add(remainder >= zero);

    // remainders must never be above the modulus
    s.add(remainder < modulus);

    return remainder;
}

/*
 * Returns a lookup table of the Nth roots of unity.
 */
z3::expr_vector make_LUT(int N, int root_of_unity, z3::expr modulus, z3::context &ctx, z3::solver &s)
{
    // Create lookup table and add it to the context
    z3::expr_vector eLUT(ctx);

    // Declare one
    z3::expr one = ctx.bv_val(1, 32);

    // Expression to hold log base 2 of N (workaround to get into expr form)
    z3::expr eroot_of_unity = ctx.bv_val(static_cast<int>(root_of_unity), 32);

    //---------- Add constraints to solver----------
    // Iterate for the N-th root of unity
    int k;
    eLUT.push_back(one);
    for(k = 1; k < N; k++)
    {
        z3::expr value = eLUT[k-1] * eroot_of_unity;
        z3::expr mod_value = mod(value, modulus, ctx, s);
        eLUT.push_back(mod_value);  
    }

    // Check that LUT is the given size N
    z3::expr lut_size = ctx.int_val(eLUT.size());
    z3::expr req_size = ctx.int_val(N);
    s.add(lut_size == req_size);

    // Check that the pattern repeats for the next Nth roots
    z3::expr temp_value = mod(eLUT[k-1]*eroot_of_unity, modulus, ctx, s);
    s.add(temp_value == eLUT[0]);
    
    int i;
    for(i = 1; i < N; i++)
    {
        temp_value = mod(temp_value*eroot_of_unity, modulus, ctx, s); 
        s.add(temp_value == eLUT[i]);
    }
    
    return eLUT;
}

/*
 * Reverses the bits based on size N.
 * Given 6 (decimal) = 3'b110 (binary) and N = 8 -> log2N = 3
 * Reverse will be 3'b011 (binary) = 3 (decimal)
 */
int bit_reversal(int num, int N, z3::context &ctx, z3::solver &s)
{
    // Variable for shifting num
    int32_t iNum = num;

    // Expression to hold iNum (workaround to get into expr form)
    z3::expr eNum = ctx.bv_val(static_cast<int>(iNum), 32);

    // Initialize reverse to equal zero
    int32_t ireverse = 0;

    // Expression to hold ireverse (workaround to get into expr form)
    z3::expr ereverse = ctx.bv_val(static_cast<int>(ireverse), 32);

    // Declare one
    z3::expr one = ctx.bv_val(1, 32);

    // Declare 2 
    z3::expr two = ctx.bv_val(2, 32);

    // Get log base 2 of N (number of bits needed to represent the number)
    size_t ilog2N = log2(N);

    // Expression to hold log base 2 of N (workaround to get into expr form)
    z3::expr elog2N = ctx.bv_val(static_cast<int>(ilog2N), 32);

    size_t j; 
    for(j = 0; j < ilog2N; j++)
    {
        // Left shift by one bit
        // (Make room for next bit)
        ireverse <<= 1;
        ereverse = ereverse * two;

        //---------- Add constraints to solver----------

        // Make sure bit vector and int manipulation match
        s.add(ireverse == ereverse);

        // Make sure bit vector and int manipulation match
        s.add(iNum == eNum);

        //----------------------------------------------
        
        // If odd then the next bit is one
        // Add one
        z3::expr mod_eNum = mod(eNum, two, ctx, s);
        if(iNum % 2 == 1)
        {
            ireverse |= (iNum & 1);
            ereverse = ereverse + one;

            //---------- Add constraint to solver----------
            // Make sure bit vector and int manipulation match
            s.add(mod_eNum == 1);
        }
        else
        {
            //---------- Add constraint to solver----------
            // Make sure bit vector and int manipulation match
            s.add(mod_eNum == 0);
        }

        // Remover lsb (was just added to reverse)
        // Get next lsb
        iNum >>= 1;
        eNum = eNum/two;
    }

    //---------- Add constraints to solver----------
    // Make sure bit vector and int manipulation match
    s.add(ereverse == ireverse);

    // Prove that reverse is the reverse of num  
    for (j = 0; j < ilog2N; j++)
    {
        z3::expr num_bit = ctx.bv_val(static_cast<int>(((num & (1 << (ilog2N-1-j))) >> ilog2N-1)), 1);
        z3::expr rev_bit = ctx.bv_val(static_cast<int>((ireverse & (1 << j))), 1);
        s.add(num_bit == rev_bit); 
    }

    return ireverse;
}

std::vector<int> vec_bit_reversal(std::vector<int> x, z3::context &ctx, z3::solver &s)
{
    // Declare zero
    z3::expr zero = ctx.bv_val(0, 32);

    // Declare 2 
    z3::expr two = ctx.bv_val(2, 32);

    // Size of vector
    size_t N = x.size();

    // Expression to hold N (workaround to get into expr form)
    z3::expr eN = ctx.bv_val(static_cast<int>(N), 32);

    //---------- Add constraint to solver----------
    // Make sure N is even
    z3::expr mod_val = mod(eN, two, ctx, s); 
    s.add(mod_val == zero);
    //----------------------------------------------
    
    // Make int vector of size N
    std::vector<int> ivec_rev(N);

    // Prefill with zero
    size_t k;
    for (k = 0; k < N; k++)
    {
       int rev_index = bit_reversal((int)k, (int)N, ctx, s);
       std::cout << x[k] << std::endl;
       ivec_rev[rev_index] = x[k]; 
    }

    //---------- Add constraint to solver----------
    // Ensure the same size as N
    z3::expr evec_rev_size = ctx.bv_val(static_cast<int>(ivec_rev.size()), 32);
    s.add(evec_rev_size == eN);
    //----------------------------------------------

    return ivec_rev;
}

/*
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
