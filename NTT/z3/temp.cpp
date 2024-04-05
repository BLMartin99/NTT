#include <iostream>
#include "z3++.h"

using namespace z3;

// Function to compute modulo using bit vectors
expr mod(expr dividend, expr modulus, context& ctx, solver &s) {
    // Compute the remainder
    expr quotient = dividend / modulus;
    expr remainder = dividend - quotient * modulus;

    // Adjust the remainder to ensure it is non-negative
    expr zero = ctx.bv_val(0, dividend.get_sort().bv_size());
    expr is_negative = dividend < zero;
    expr adjusted_remainder = ite(is_negative, remainder + modulus, remainder);
    
    
    s.add(adjusted_remainder > zero);
    s.add(adjusted_remainder < modulus);
    return adjusted_remainder;
}

int main() {
    // Context
    context ctx;

    // Solver
    solver s(ctx);

    expr x = ctx.bv_const("x", 4);  // 4-bit signed bit-vector variable
    x = ctx.bv_val(-2, 4);  // 4-bit signed bit-vector variable
    expr modulus = ctx.bv_const("modulus", 4);  // 4-bit signed bit-vector variable
    modulus = ctx.bv_val(5, 4);
    expr mod_value = mod(x, modulus, ctx, s); // Compute x % 5 using custom mod function

    if (s.check() == sat){
        model m = s.get_model();
        expr result = m.eval(mod_value);

        std::cout << "Result of -2 % 5 using custom mod function: " << result << std::endl;
    }
    else{
        std::cout << "Unsat" << std::endl;
    }


    return 0;
}
