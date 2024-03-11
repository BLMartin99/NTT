complex_num compute_twiddle_factor(bool fft, size_t m);
uint32_t bit_reversal(uint32_t num, size_t N);
vec_complex_num vec_bit_reversal(vec_complex_num a);
vec_complex_num fft (vec_complex_num a);
vec_complex_num ifft (vec_complex_num a);
