#include <cmath> 
#include <iostream>
#include <tuple>
#include <vector>

typedef std::vector<uint32_t> vec_num_t;

uint32_t mod (int32_t x, uint32_t modulus);
vec_num_t make_LUT(vec_num_t x, uint32_t root_of_unity, uint32_t modulus);
uint32_t bit_reversal(uint32_t num, size_t N);
vec_num_t vec_bit_reversal(vec_num_t x);
void ntt (vec_num_t &x, uint32_t root_of_unity, uint32_t modulus);
