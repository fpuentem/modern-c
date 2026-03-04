#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h> // Type-generic math (Modern C standard)

int main(void) {
    double pi_approx = 0.0;
    double sign = 1.0;

    /* * We run the loop for a fixed number of iterations.
     * Note: Leibniz is notoriously slow to converge.
     * You need millions of iterations to get good precision.
     */
    size_t const max_iter = 1000000;

    for (size_t i = 0; i < max_iter; ++i) {
        // The denominator follows the sequence 1, 3, 5, 7...
        // Formula: 2*i + 1
        double term = 1.0 / (2.0 * i + 1.0);

        pi_approx += sign * term;

        // Flip the sign for the next iteration (+, -, +, -)
        sign = -sign;
    }

    // The series sums to pi/4, so multiply by 4 at the end
    pi_approx *= 4.0;

    printf("Calculated Pi: %.9f\n", pi_approx);
    printf("Standard Pi:   %.9f\n", 3.141592653);

    return EXIT_SUCCESS;

}
