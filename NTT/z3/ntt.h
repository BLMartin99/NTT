#include <cmath> 
#include <iostream>
#include <tuple>
#include <vector>

#include <z3++.h>

int mod(int dividend, int modulus, z3::context &ctx, z3::solver &s);
std::vector<int> make_LUT(int N, int root_of_unity, int modulus, z3::context &ctx, z3::solver &s);
int bit_reversal(int num, int N, z3::context &ctx, z3::solver &s);
std::vector<int> vec_bit_reversal(std::vector<int> x, z3::context &ctx, z3::solver &s);
z3::expr_vector ntt_LUT (std::vector<int> x, int root_of_unity, int modulus, z3::context &ctx, z3::solver &s);
z3::expr_vector ntt_naive (std::vector<int> x, int root_of_unity, int modulus, z3::context &ctx, z3::solver &s);
