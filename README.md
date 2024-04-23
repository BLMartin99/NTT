# NTT
This a project by Bailey Martin and Bhavani Sampath of the University of Utah on verification of Number Theoretic Transforms using Theory of Bit Vectors. We attempted to use different approaches but ended up using Z3 for this though other work is left to be viewed. NTT is a Fourier Transform over some finite field Z\_q we used the Cooley-Tukey algorithm for O(nlogn) complexity. Final implementation uses the modulus q (= 17 as based on Baby-Kyber), a number sequence of length N (= 8 for this example) which represents the coefficients of the input polynomial to the transform, and a root of unity (= 15 in our example). 
1. Navigate to the NTT/z3 directory.
2. On the University of Utah Cade machines run "g++ -o ntt ntt.cpp /usr/local/lib/libz3.so" to compile.
3. The executable is ntt run "./ntt" to run.
