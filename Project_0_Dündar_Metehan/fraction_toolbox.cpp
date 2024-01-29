#include <iostream>
#include "fraction_toolbox.hpp"

void print_fraction(fraction frac) {
    std::cout << frac.num << '/' << frac.denom << std::endl;
}

void print_fraction_array(fraction frac_array[], int n) {
    std::cout << "[ " << frac_array[0].num << '/' << frac_array[0].denom << std::endl;
    for (int i = 1; i < n-1; i++)
    {
        std::cout << "  ";
        print_fraction(frac_array[i]);
    }
    std::cout << "  " << frac_array[n-1].num << '/' << frac_array[n-1].denom << " ]" << std::endl;
}

fraction square_fraction(fraction frac) {
    struct fraction result;
    result.num = frac.num * frac.num;
    result.denom = frac.denom * frac.denom;
    return result;
}

void square_fraction_inplace(fraction &frac) {
    frac.num = frac.num * frac.num;
    frac.denom = frac.denom * frac.denom;
}

double fraction2double(fraction frac) {
    return (double)frac.num / frac.denom;
}

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

int gcd(fraction frac) {
    int a = frac.num;
    int b = frac.denom;
    int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void reduce_fraction_inplace(fraction & frac) {
    int great_common_divisor = gcd(frac.num, frac.denom); //recursive
    frac.num /= great_common_divisor;
    frac.denom /= great_common_divisor;
}

fraction add_fractions(fraction frac1, fraction frac2) {
    struct fraction result;
    int denom   = frac1.denom * frac2.denom;
    int num1    = frac1.num * frac2.denom;
    int num2    = frac2.num * frac1.denom;
    result.num  = num1 + num2;
    result.denom = denom;
    reduce_fraction_inplace(result);
    return result;
}

double sum_fraction_array_approx(fraction frac_array[], int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += static_cast<double>(frac_array[i].num) / static_cast<double>(frac_array[i].denom);
    }
    return sum;
    //Some fractions cannot be precisely represented in the binary floating-point format due to the finite accuracy of floating-point integers.
    //Therefore, we might lose some precision while converting a fraction to a double, which could lead to minor rounding mistakes.
}

struct fraction sum_fraction_array(fraction frac_array[], int n) {
    struct fraction result;
    result.num = 0;
    result.denom = 1;
    for (int i = 0; i < n; i++) {
        int denom = result.denom * frac_array[i].denom;
        int num1 = result.num * frac_array[i].denom;
        int num2 = frac_array[i].num * result.denom;
        result.num = num1 + num2;
        result.denom = denom;
        reduce_fraction_inplace(result);
    }
    return result;
}

void fill_fraction_array(fraction frac_array[], int n) {
    fraction temp_frac;
    temp_frac.num = 1;
    for (int i = 1; i <= n; i++)
    {
        temp_frac.denom = i * (i+1);
        frac_array[i-1] = temp_frac;
    }
}