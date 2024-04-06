#include <cmath> 
#include <iostream>
#include <tuple>
#include <vector>

#include <z3++.h>

typedef std::vector<uint32_t> vec_num_t;

z3::expr mod(z3::expr dividend, z3::expr modulus, z3::context& ctx, z3::solver &s); 
/*
vec_num_t make_LUT(size_t N, uint32_t root_of_unity, uint32_t modulus);
uint32_t bit_reversal(uint32_t num, size_t N);
vec_num_t vec_bit_reversal(vec_num_t x);
vec_num_t ntt (vec_num_t x, uint32_t root_of_unity, uint32_t modulus);
vec_num_t ntt_LUT (vec_num_t x, uint32_t root_of_unity, uint32_t modulus);
*/
