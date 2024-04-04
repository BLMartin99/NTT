#include "ntt.h" 

int main ()
{
    // Get the tuple of vectors from the function
    vec_num_t a = {1, 2, 3, 4, 3, 2, 1, 0};

    vec_num_t A = ntt(a, 9, 17);

    std::cout << "NTT output" << std::endl;
    for(const auto& num : A)
    {
        std::cout << num << std::endl;
    }

    vec_num_t A_LUT = ntt_LUT(a, 9, 17);

    std::cout << "LUT NTT output" << std::endl;
    for(const auto& num : A_LUT)
    {
        std::cout << num << std::endl;
    }

    // Get the tuple of vectors from the function
    vec_num_t b = {2, 3, 4, 3, 2, 1, 0};

    vec_num_t B = ntt(b, 9, 17);

    std::cout << "NTT output" << std::endl;
    for(const auto& num : B)
    {
        std::cout << num << std::endl;
    }

    vec_num_t B_LUT = ntt_LUT(b, 9, 17);

    std::cout << "LUT NTT output" << std::endl;
    for(const auto& num : B_LUT)
    {
        std::cout << num << std::endl;
    }


    return 0;
}

uint32_t mod (int32_t x, uint32_t modulus)
{
    uint32_t x_ = x;
    if(x < 0)
    {
        x_ = modulus + x; 
    }

    return x_ % modulus;
}

vec_num_t make_LUT(size_t N, uint32_t root_of_unity, uint32_t modulus)
{
    vec_num_t LUT(N);
    size_t k;
    for(k = 0; k < N; k++)
    {
       std::cout << root_of_unity << " " << k << " " << mod(std::pow(root_of_unity, k), modulus) << std::endl;
       LUT[k] = mod(std::pow(root_of_unity, k), modulus);  
    }

    return LUT;
}

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

vec_num_t ntt (vec_num_t x, uint32_t root_of_unity, uint32_t modulus)
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

    size_t m; 
    size_t w_m; 
    size_t w; 
    size_t j; 
    size_t k; 
    uint32_t t;
    uint32_t u;

    for(m = 2; m <= N; m*=2)
    {
        w_m = mod(std::pow(root_of_unity, N/m), modulus); 
        w = 1;
        for(j = 0; j < m/2; j++)
        {
            for(k = 0; k < N; k+=m)
            {
                t = mod(w*A[k+j+m/2], modulus);
                u = mod(A[k+j], modulus);
                A[k+j] = mod(u + t, modulus);
                A[k+j+m/2] = mod(u - t, modulus);
                std::cout << "m: " << m << " j: " << j << " k: " << k << " w " << w << " t: " << t << " u: " << u << " u + t: " << mod(u+t, modulus) << " u - t: " << mod(u-t, modulus) << " A[k+j] = A[" << k+j << "] = " <<  mod(u+t, modulus) << " A[k+j+m/2] = A[" << k+j+m/2 << "] = " << mod(u-t, modulus) << std::endl;

            }
            w = mod(w*w_m, modulus);
        }
    }
    return A;
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
                std::cout << "m: " << m << " j: " << j << " k: " << k << " w " << LUT[j*N/m] << " t: " << t << " u: " << u << " u + t: " << mod(u+t, modulus) << " u - t: " << mod(u-t, modulus) << " A[k+j] = A[" << k+j << "] = " <<  mod(u+t, modulus) << " A[k+j+m/2] = A[" << k+j+m/2 << "] = " << mod(u-t, modulus) << std::endl;

            }
        }
    }
    return A;
}
