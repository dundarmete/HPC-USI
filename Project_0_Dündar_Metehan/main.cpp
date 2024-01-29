#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>

#include "fraction_toolbox.hpp"

using namespace std;

static void readcmdline(fraction & frac, int argc, char* argv[]) {
    if (argc!=3)
    {
        printf("Usage: n d\n");
        printf("  n        numerator of fraction\n");
        printf("  d        denominator of fraction\n");
        exit(1);
    }

    frac.num = atoi(argv[1]);

    frac.denom = atoi(argv[2]);
}

static void test23467(int argc, char* argv[]) {
    
    fraction frac;
    readcmdline(frac, argc, argv);

    cout << "Function 2: Squaring the fraction" << endl;
    fraction squared = square_fraction(frac);
    cout << "Result: ";
    print_fraction(squared);
    cout << endl;

    cout << "Function 3: Squaring the fraction in-place" << endl;
    fraction squareInplace = frac;
    square_fraction_inplace(squareInplace);
    cout << "Original Fraction: ";
    print_fraction(frac);
    cout << "Result: ";
    print_fraction(squareInplace);
    cout << endl;

    cout << "Function 4: Converting the fraction to a double" << endl;
    double doubleValue = fraction2double(frac);
    cout << "Result: " << doubleValue << endl;
    cout << endl;

    cout << "Function 6: Calculating the GCD iteratively of the fraction" << endl;
    int gcdValue = gcd(frac);
    cout << "Result (GCD): " << gcdValue << endl;
    cout << endl;

    cout << "Function to Reduce the Fraction In-Place" << endl;
    fraction reduceInplace = frac;
    reduce_fraction_inplace(reduceInplace);
    cout << "Original Fraction: ";
    print_fraction(frac);
    cout << "Reduced Fraction: ";
    print_fraction(reduceInplace);
    cout << endl;
}

static void test5()
{
    int num1, num2;

    cout << "Enter the first integer: ";
    cin >> num1;
    cout << "Enter the second integer: ";
    cin >> num2;

    int gcdValue = gcd(num1, num2);

    cout << "GCD of " << num1 << " and " << num2 << " is: " << gcdValue << endl;
    cout << endl;
}

static void test_array_functions(int n) {
    
    fraction *fracArray = (fraction *)malloc(n * sizeof(fraction));

    if (fracArray == nullptr) {
        cerr << "Memory allocation failed." << endl;
        return;
    }

    fill_fraction_array(fracArray, n);

    cout << "Sum using sum_fraction_array() for n=" << n << ": ";
    fraction sumArray = sum_fraction_array(fracArray, n);
    print_fraction(sumArray);

    cout << "Sum using sum_fraction_array_approx() for n=" << n << ": ";
    double sumApprox = sum_fraction_array_approx(fracArray, n);
    cout << sumApprox << endl;
    cout << endl;

    free(fracArray);

    //The sum of all of the fractions in sum_fraction_array() may exceed 
    //the range of 32-bit integers when n (1290) gets large, leading to 
    //integer overflow and inaccurate output. By implementing double-precision 
    //floating-point arithmetic, which allows for a broader range of values 
    //without overflowing, sum_fraction_array_approx() solves this problem.
}

static void test_toolbox(int argc, char* argv[])
{
    cout << "\n===============  test23467  =============== " << endl;
    test23467(argc, argv);

    cout << "\n=================  test5  ================= " << endl;
    test5();

    cout << "\n==========  test_array_functions  ========= " << endl;
    int n = 5;
    test_array_functions(n);
}

int main(int argc, char* argv[])
{
    test_toolbox(argc, argv);
    return 0;
}