#include <cmath> 
#include <complex>
#include <iostream>
#include <tuple>
#include <vector>

typedef std::complex<double> complex_num;
const complex_num i (0.0, 1.0); // imaginary number
typedef std::vector<complex_num> vec_complex_num;

complex_num compute_twiddle_factor(size_t m)
{ 
    complex_num pi (M_PI, 0.0);
    return std::exp(-2.0*pi*i/static_cast<double>(m));
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

vec_complex_num vec_bit_reversal(vec_complex_num a)
{
    size_t N = a.size();

    if(N % 2 != 0)
    {
        std::cout << "Sample size should be an even number" << std::endl;
        std::terminate();
    }

    vec_complex_num vec_reversed(N);
    uint32_t reversed_index;
    size_t k;
    for (k = 0; k < N; k++)
    {
       reversed_index = bit_reversal(k, N);
       vec_reversed[reversed_index] = a[k]; 
    }

    return vec_reversed;
}

vec_complex_num fft (vec_complex_num a)
{
    // Get size N
    size_t N = a.size();

    // Log2(N)
    size_t log2N = log2(N);

    // Reverse bit LUT
    vec_complex_num A = vec_bit_reversal(a);
    
    // FFT loop
    size_t s;
    size_t k;
    size_t j;
    size_t m;
    complex_num w_m;
    complex_num w;
    complex_num t;
    complex_num u;
    for(s = 1; s <= log2N; s++)
    {
      m = (size_t)std::pow(2.0,(double)s); 
      w_m = compute_twiddle_factor(m);
       for(k = 0; k < N; k+=m)
       {
          w = 1;
          for(j = 0; j < m/2; j++)
          {
            t = w*A[k + j + m/2];
            u = A[k + j];
            A[k + j] = u + t;
            A[k + j + m/2] = u - t;
            w = w*w_m;
          }
       }
    }
    return A;
}

int main ()
{
    // Get the tuple of vectors from the function
    vec_complex_num a = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};

    std::cout << "Input vector" << std::endl;
    for(const auto& num : a)
    {
        std::cout << num.real() << " + " << num.imag() << "i" << std::endl;
    }

    vec_complex_num A = fft(a);

    std::cout << "fft vector" << std::endl;
    for(const auto& num : A)
    {
        std::cout << num.real() << " + " << num.imag() << "i" << std::endl;
    }

   return 0;
}
