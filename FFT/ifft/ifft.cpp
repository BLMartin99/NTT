#include "../types.h"
#include "../fft_radix-2_iter/fft_radix-2_iter.h" 
#include "ifft.h"

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

complex_num ifft_compute_twiddle_factor(size_t m)
{ 
    complex_num pi (M_PI, 0.0);
    return std::exp(2.0*pi*i/static_cast<double>(m));
}

vec_complex_num fft (vec_complex_num a)
{
    // Get size N
    size_t N = a.size();

    // Log2(N)
    size_t log2N = log2(N);

    // Reverse bit LUT
    vec_complex_num A = vec_bit_reversal(a);

    std::cout << "Input vector reversed" << std::endl;
    for(const auto& num : A)
    {
        std::cout << num.real() << " + " << num.imag() << "i" << std::endl;
    }


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

    size_t size_of_A = A.size();
    size_t l;
    for(l = 0; l < size_of_A; l++)
    {
        A[l] /= size_of_A;
    }

    return A;
}


