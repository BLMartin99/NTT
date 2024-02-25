#include <complex>
#include <iostream>
#include <tuple>
#include <vector>

typedef std::complex<double> complex_num;
typedef std::vector<complex_num> vec_complex_num;

std::tuple<vec_complex_num, vec_complex_num> split_evens_and_odds(vec_complex_num)
{
    return std::make_tuple(vec_complex_num{1.0}, vec_complex_num{2.0});
}

int main ()
{
    // Get the tuple of vectors from the function
    auto result = split_evens_and_odds({1.0, 2.0});

    // Extract the vectors from the tuple
    vec_complex_num evens = std::get<0>(result);
    vec_complex_num odds = std::get<1>(result);

    // Print the elements of the evens vector
    std::cout << "Evens:" << std::endl;
    for(const auto& num : evens)
    {
        std::cout << num.real() << " + " << num.imag() << "i" << std::endl;
    }

    // Print the elements of the odds vector
    std::cout << "Odds:" << std::endl;
    for(const auto& num : odds)
    {
        std::cout << num.real() << " + " << num.imag() << "i" << std::endl;
    }
   return 0;
}
