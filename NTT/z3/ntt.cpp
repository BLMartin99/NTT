/*
 * g++ -o ntt ntt.cpp /usr/local/lib/libz3.so
 */
#include "ntt.h" 

int main ()
{
    z3::context ctx;

    z3::solver s(ctx);

    // 8-bit bit-vector -- allow -128 to 127
    // Set to a 8-bit value -15
    int dividend = 4;

    // 8-bit bit-vector -- allow -128 to 127
    int modulus = 17;
    // Set to a 8-bit value

    // Call mod
    int mod_value = mod(dividend, modulus, ctx, s);

    std::cout << "Mod val: " << mod_value << std::endl;
    /*
    // Check N-th root calculation 
    int N = 8;
    std::vector<int> vec_temp = make_LUT(N, 15, modulus, ctx, s);

    // Check bit reversal
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
        int result_mod = mod_value;

        std::cout << "Result of " << dividend << " % " << modulus << " using mod: " << result_mod << std::endl;

        
        std::cout << "Result of make_LUT:" << std::endl;
        std::cout << "Size of make_LUT: " << vec_temp.size() << std::endl;
        int i;
        for(i = 0; i < vec_temp.size(); i++)
        {
            int val = vec_temp[i];
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
    */

    return 0;
}

/*
 * Modulo of dividend. 
 * If dividend is negative: (modulus + dividend) % modulus
 * If dividend is not negative: dividend % modulus
 */
int mod(int dividend, int modulus, z3::context &ctx, z3::solver &s)
{
    //---------- Add constraints to solver----------
    // Expression to hold log base 2 of N (workaround to get into expr form)
    z3::expr edividend = ctx.bv_val(static_cast<int>(dividend), 32);

    // Expression to hold log base 2 of N (workaround to get into expr form)
    z3::expr emodulus = ctx.bv_val(static_cast<int>(modulus), 32);

    // Declare zero
    z3::expr zero = ctx.bv_val(0, 32);

    int idividend = dividend;

    if(dividend < 0)
    {

        idividend += modulus;
        s.add(edividend < zero);
    }
    else
    {
        s.add(edividend >= zero);
    }

    int iremainder = idividend % modulus;
 
    // Expression to hold iremainder (workaround to get into expr form)
    z3::expr eremainder = ctx.bv_val(static_cast<int>(iremainder), 32);

    // remainders must never be below zero
    s.add(eremainder >= zero);

    // remainders must never be above the modulus
    s.add(eremainder < emodulus);

    return iremainder;
}

/*
 * Returns a lookup table of the Nth roots of unity.
 */
std::vector<int> make_LUT(int N, int root_of_unity, int modulus, z3::context &ctx, z3::solver &s)
{
    // Make LUT
    std::vector<int> iLUT(N);
    int k;
    iLUT.push_back(1);
    for(k = 1; k < N; k++)
    {
        int value = iLUT[k-1] * root_of_unity;
        int mod_value = mod(value, modulus, ctx, s);
        iLUT.push_back(mod_value);  
    }

    //---------- Add constraints to solver----------
    // Create lookup table and add it to the context
    z3::expr_vector eLUT(ctx);

    // Declare one
    z3::expr one = ctx.bv_val(1, 32);

    // Expression to hold log base 2 of N (workaround to get into expr form)
    z3::expr eroot_of_unity = ctx.bv_val(static_cast<int>(root_of_unity), 32);

    // Iterate for the N-th root of unity
    for(k = 0; k < N; k++)
    {
        int value = std::pow(root_of_unity, k);
        int imod_value = value % modulus; 
        z3::expr emod_value = ctx.bv_val(static_cast<int>(imod_value), 32);
        eLUT.push_back(emod_value);  
    }

    // Check that the LUT matches
    for(k = 0; k < N; k++)
    {
        z3::expr eval = eLUT[k];
        z3::expr ival =  ctx.bv_val(static_cast<int>(iLUT[k]), 32);
        s.add(eval == ival);  
    }

    // Check that LUT is the given size N
    z3::expr lut_size = ctx.bv_val(static_cast<int>(iLUT.size()), 32);
    z3::expr req_size = ctx.bv_val(static_cast<int>(N), 32);
    s.add(lut_size == req_size);

    // Check that the pattern repeats for the next Nth roots
    int itemp_value = mod(iLUT[k-1]*root_of_unity, modulus, ctx, s);
    z3::expr etemp_value = ctx.bv_val(static_cast<int>(itemp_value), 32);
    z3::expr iindex_value = ctx.bv_val(static_cast<int>(iLUT[0]), 32);
    s.add(etemp_value == iindex_value);
    
    int i;
    for(i = 1; i < N; i++)
    {
        itemp_value = mod(itemp_value*root_of_unity, modulus, ctx, s); 
        etemp_value = ctx.bv_val(static_cast<int>(itemp_value), 32);
        iindex_value = ctx.bv_val(static_cast<int>(iLUT[i]), 32);
        s.add(etemp_value == iindex_value);
    }
    
    return iLUT;
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
        int mod_iNum = mod(iNum, 2, ctx, s);
     
        // Expression to hold log base 2 of N (workaround to get into expr form)
        z3::expr mod_eNum = ctx.bv_val(static_cast<int>(mod_iNum), 32);

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
    int imod_val = mod(N, 2, ctx, s); 
    // Expression to hold N (workaround to get into expr form)
    z3::expr emod_val = ctx.bv_val(static_cast<int>(imod_val), 32);
    s.add(emod_val == zero);
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
