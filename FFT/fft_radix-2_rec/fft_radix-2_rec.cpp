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
        evens[j] = original_vec[k]; 
        odds[j] = original_vec[k+1]; 
    }

    return std::make_tuple(evens, odds);
}

complex_num compute_twiddle_factor(size_t k, size_t N)
{ 
    complex_num pi (M_PI, 0.0);
    return std::exp((complex_num(-2.0, 0.0)*pi*i*complex_num((double)k, 0.0))/complex_num((double)N, 0.0));
}

vec_complex_num get_twiddle_factors(size_t N)
{
    vec_complex_num vec_twiddle_factors(N);

    size_t k;
    for(k = 0; k < N/2; k++)
    {
       vec_twiddle_factors[k] = compute_twiddle_factor(k, N);
    }

    return vec_twiddle_factors;
}

void fft (vec_complex_num &x)
{
    size_t N = x.size();

    if(N == 1)
    {
        return;
    }
    else
    {
        // Split into even and odd
        auto result = split_evens_and_odds(x);

        // Extract the vectors from the tuple
        vec_complex_num evens = std::get<0>(result);
        vec_complex_num odds = std::get<1>(result);

        // Recurse
        fft(evens);
        fft(odds);

        vec_complex_num vec_of_twiddle_factors = get_twiddle_factors(N);

        for(size_t k = 0; k < N/2; k++)
        {
            // Get twiddle factor from collection of twiddle factors
            complex_num twiddle_factor = vec_of_twiddle_factors[k];

            // Odd times twiddle factor
            complex_num temp = odds[k]*twiddle_factor;

            // Place in x
            x[k] = evens[k] + temp;
            x[k + N/2] = evens[k] - temp;
        }
    }
}

int main ()
{
    // Get the tuple of vectors from the function
    vec_complex_num x = {7.0, 9.0, 11.0, 2.0};

    std::cout << "Input vector" << std::endl;
    for(const auto& num : x)
    {
        std::cout << num.real() << " + " << num.imag() << "i" << std::endl;
    }

    fft(x);

    std::cout << "fft vector" << std::endl;
    for(const auto& num : x)
    {
        std::cout << num.real() << " + " << num.imag() << "i" << std::endl;
    }


   return 0;
}
