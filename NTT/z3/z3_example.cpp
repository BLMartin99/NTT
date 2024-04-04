/*
 * g++ -o z3_example z3_example.cpp /usr/local/lib/libz3.so
 */

#include <iostream>
#include <z3++.h>

int main() {
    // Create Z3 context
    z3::context ctx;

    // Create Z3 integers
    z3::expr x = ctx.int_const("x");
    z3::expr y = ctx.int_const("y");

    // Create Z3 solver
    z3::solver s(ctx);

    // Add constraints
    s.add(x >= 0);
    s.add(y >= 0);
    s.add(x + y == 10);

    // Check if there's a solution
    if (s.check() == z3::sat) {
        z3::model m = s.get_model();
        std::cout << "Solution: x = " << m.eval(x) << ", y = " << m.eval(y) << std::endl;
    } else {
        std::cout << "No solution found." << std::endl;
    }

    return 0;
}
