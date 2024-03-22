#include "ntt.h" 

int main ()
{
    // Get the tuple of vectors from the function
    vec_num_t a = {1, 2, 3, 4};

    ntt(a, 2, 5);

    std::cout << "NTT output" << std::endl;
    for(const auto& num : a)
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
        x_ = modulus - x; 
    }

    return x % modulus;
}

vec_num_t make_LUT(vec_num_t x, uint32_t root_of_unity, uint32_t modulus)
{
    size_t N = x.size();

    if(N % 2 != 0)
    {
        std::cout << "Sample size should be an even number" << std::endl;
        std::terminate();
    }

    vec_num_t LUT(N);
    size_t k;
    for(k = 0; k < N; k++)
    {
        std::cout << root_of_unity << " " << k << " " << std::pow(root_of_unity, k) << std::endl;
       LUT[k] = std::pow(root_of_unity, k);  
    }

    return LUT;
}

uint32_t bit_reversal(uint32_t num, size_t N)
{
    if(N % 2 != 0)
    {
        std::cout << "Sample size should be an even number" << std::endl;
        std::terminate();
    }

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

    if(N % 2 != 0)
    {
        std::cout << "Sample size should be an even number" << std::endl;
        std::terminate();
    }

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

void ntt (vec_num_t &x, uint32_t root_of_unity, uint32_t modulus)
{
    // Get size N
    size_t N = x.size();

    // Log2(N)
    size_t log2N = log2(N);

    // Make LUT using root of unity
    vec_num_t LUT = make_LUT(x, root_of_unity, modulus);

    // Reverse bit LUT
    vec_num_t LUT_rev = vec_bit_reversal(LUT);

    std::cout << "LUT vector reversed" << std::endl;
    for(const auto& num : LUT_rev)
    {
        std::cout << num << std::endl;
    }

    size_t i;
    size_t m;
    size_t r;
    size_t k;
    uint32_t w;
    size_t j;
    uint32_t t;
    uint32_t u;

    for(i = log2N; i > 1; i--)
    {
        m = std::pow(2, i);
        r = 0;
        for(k = 0; k < N; k+=m)
        {
            w = LUT_rev[r + bit_reversal(m/2, N)]; 
            for(j = 0; j < m/2; j++)
            {
                t = w*x[j+k+m/2];
                u = x[j+k]; 
                x[j+k] = mod(u + t, modulus);
                x[j+k+m/2] = mod(u - t, modulus);
            }
            r++;
        }
    }
}
