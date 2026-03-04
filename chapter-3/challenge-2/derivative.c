#include <stdio.h>
#include <stdlib.h>
#include <math.h> /* Required for fabs and math functions */

/* The step size for the derivative.
 * 1e-5 is usually a sweet spot for double precision.
 * Too small = round-off error (floating point noise).
 * Too large = approximation error.
 */
static double const EPS = 1.0E-5;

/* 1. The target function F(x)
 * Let's use something easy to verify: F(x) = x^2
 * We know analytically that F'(x) = 2x.
 */
double F(double x) {
    return x * x;
}

/* 2. The Numerical Derivative Function
 * Returns the approximate slope at point x.
 */
double diff(double x) {
    double x_plus = x + EPS;
    double x_minus = x - EPS;

    // Central Difference Formula
    return (F(x_plus) - F(x_minus)) / (2 * EPS);
}

int main(void) {
    double test_val = 5.0;
    double result = diff(test_val);
    double expected = 2.0 * test_val;

    printf("F(x) = x^2 at x = %.1f\n", test_val);
    printf("Numerical Derivative: %.5f\n", result);
    printf("Analytical Derivative: %.5f\n", expected);
    printf("Error: %.10f\n", fabs(result - expected));

    return EXIT_SUCCESS;
}
