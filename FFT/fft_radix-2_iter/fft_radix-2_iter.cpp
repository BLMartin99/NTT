#include <cmath> 
#include <complex>
#include <iostream>
#include <tuple>
#include <vector>

typedef std::complex<double> complex_num;
const complex_num i (0.0, 1.0); // imaginary number
typedef std::vector<complex_num> vec_complex_num;

std::tuple<vec_complex_num, vec_complex_num> split_evens_and_odds(vec_complex_num original_vec)
{
    size_t size_vec = original_vec.size();
    if(size_vec % 2 != 0)
    {
        std::cout << "Sample size should be an even number" << std::endl;
        std::terminate();
    }

    
    vec_complex_num evens = vec_complex_num(size_vec/2);
    vec_complex_num odds = vec_complex_num(size_vec/2);

    size_t k;
    size_t j;
    for(k = 0, j = 0; k < size_vec; k+=2, j++)
    {
        evens[j] = original_vec[k]; 
        odds[j] = original_vec[k+1]; 
    }

    return std::make_tuple(evens, odds);
}

complex_num compute_twiddle_factor(size_t k, size_t N)
{ 
    complex_num pi (M_PI, 0.0);
    return std::exp((complex_num(-2.0, 0.0)*pi*i*complex_num((double)k, 0.0))/complex_num((double)N, 0.0));
}

vec_complex_num get_twiddle_factors(size_t N)
{
    vec_complex_num vec_twiddle_factors(N);

    size_t k;
    for(k = 0; k < N/2; k++)
    {
       vec_twiddle_factors[k] = compute_twiddle_factor(k, N);
    }

    return vec_twiddle_factors;
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

vec_complex_num vec_bit_reversal(vec_complex_num x)
{
    size_t N = x.size();

    if(N % 2 != 0)
    {
        std::cout << "Sample size should be an even number" << std::endl;
        std::terminate();
    }

    vec_complex_num vec_reversed(N);
    uint32_t reversed_index;
    size_t j;
    for (j = 0; j < N; j++)
    {
       reversed_index = bit_reversal(j, N);
       vec_reversed[reversed_index] = x[j]; 
    }

    return vec_reversed;
}

/*
void fft (vec_complex_num &x)
{
    
}
*/


int main ()
{
    // N = 4;
    // log2(4) = 2

    //uint32_t temp = bit_reversal(7, 8);
    //std::cout << temp << std::endl;
    // Get the tuple of vectors from the function
    vec_complex_num x = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};

    vec_complex_num vec_return = vec_bit_reversal(x);

    std::cout << "LUT" << std::endl;
    for(const auto& num : vec_return)
    {
        std::cout << num.real() << " + " << num.imag() << "i" << std::endl;
    }



    /*
    std::cout << "Input vector" << std::endl;
    for(const auto& num : x)
    {
        std::cout << num.real() << " + " << num.imag() << "i" << std::endl;
    }

    fft(x);

    std::cout << "fft vector" << std::endl;
    for(const auto& num : x)
    {
        std::cout << num.real() << " + " << num.imag() << "i" << std::endl;
    }
    */

   return 0;
}
