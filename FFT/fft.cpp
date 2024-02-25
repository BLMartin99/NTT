#include <complex>
#include <iostream>
#include <tuple>
#include <vector>

typedef std::complex<double> complex_num;
typedef std::vector<complex_num> vec_complex_num;

std::tuple<vec_complex_num, vec_complex_num> split_evens_and_odds(vec_complex_num original_vec)
{
    size_t size_vec = original_vec.size();
    if(size_vec % 2 != 0)
    {
        std::cout << "Sample size should be an even number" << std::endl;
        std::terminate();
    }

    
    vec_complex_num evens = vec_complex_num(size_vec/2);
    vec_complex_num odds = vec_complex_num(size_vec/2);

    size_t i;
    size_t j;
    for(i = 0, j = 0; i < size_vec; i+=2, j++)
    {
        std::cout << "i is: " << i << " j is: " << j << std::endl;
        evens[j] = original_vec[i]; 
        odds[j] = original_vec[i+1]; 
    }

    return std::make_tuple(evens, odds);
}

int main ()
{
    // Get the tuple of vectors from the function
    auto result = split_evens_and_odds({1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0});

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
