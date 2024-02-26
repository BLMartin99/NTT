#include <cmath> 
#include <complex>
#include <iostream>
#include <tuple>
#include <vector>

typedef std::complex<double> complex_num;
const complex_num i (0.0, 1.0); // imaginary number
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

    size_t k;
    size_t j;
    for(k = 0, j = 0; k < size_vec; k+=2, j++)
    {
        std::cout << "k is: " << i << " j is: " << j << std::endl;
        evens[j] = original_vec[k]; 
        odds[j] = original_vec[k+1]; 
    }

    return std::make_tuple(evens, odds);
}

complex_num compute_twiddle_factor(size_t k, size_t N)
{ 
    complex_num pi (M_PI, 0.0);
    return std::exp((complex_num(2.0, 0.0)*pi*i*complex_num((double)k, 0.0))/complex_num((double)N, 0.0));
}

vec_complex_num get_twiddle_factors(size_t N)
{
    vec_complex_num vec_twiddle_factors(N);

    size_t k;
    for(k = 0; k < N; k++)
    {
       vec_twiddle_factors[k] = compute_twiddle_factor(k, N); 
    }

    return vec_twiddle_factors;
}

int main ()
{
    // Get the tuple of vectors from the function
    vec_complex_num input = {7.0, 9.0, 11.0, 2.0};
    auto result = split_evens_and_odds(input);

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

    std::cout << "Even twiddle factors" << std::endl;
    auto even_twiddle_factors = get_twiddle_factors(evens.size()); 
    for(const auto& num : even_twiddle_factors)
    {
        std::cout << num.real() << " + " << num.imag() << "i" << std::endl;
    }

    std::cout << "Odd twiddle factors" << std::endl;
    auto odd_twiddle_factors = get_twiddle_factors(odds.size()); 
    for(const auto& num : odd_twiddle_factors)
    {
        std::cout << num.real() << " + " << num.imag() << "i" << std::endl;
    }

    std::cout << "Input twiddle factors" << std::endl;
    auto input_twiddle_factors = get_twiddle_factors(input.size()); 
    for(const auto& num : input_twiddle_factors)
    {
        std::cout << num.real() << " + " << num.imag() << "i" << std::endl;
    }

   return 0;
}
