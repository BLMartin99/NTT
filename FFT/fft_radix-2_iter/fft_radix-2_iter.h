#include <cmath> 
#include <complex>
#include <iostream>
#include <tuple>
#include <vector>

typedef std::complex<double> complex_num;
const complex_num i (0.0, 1.0); // imaginary number
typedef std::vector<complex_num> vec_complex_num;

complex_num compute_twiddle_factor(size_t m);
uint32_t bit_reversal(uint32_t num, size_t N);
vec_complex_num vec_bit_reversal(vec_complex_num a);
vec_complex_num fft (vec_complex_num a);
