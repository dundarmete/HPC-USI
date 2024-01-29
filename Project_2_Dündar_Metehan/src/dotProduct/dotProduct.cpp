#include <omp.h>
#include "walltime.h"
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <unistd.h>

#define NUM_ITERATIONS 100

// Example benchmarks
// 0.008s ~0.8MB
// #define N 100000
// 0.1s ~8MB
 #define N 1000000
// 1.1s ~80MB
// #define N 10000000
// 13s ~800MB
// #define N 100000000
// 127s 16GB
// #define N 1000000000
#define EPSILON 0.1

using namespace std;

int main() {
  double time_serial, time_start = 0.0;
  double *a, *b;

  // Allocate memory for the vectors as 1-D arrays
  a = new double[N];
  b = new double[N];

  // Initialize the vectors with some values
  for (int i = 0; i < N; i++) {
    a[i] = i;
    b[i] = i / 10.0;
  }

  long double alpha = 0;

  // Serial execution
  // Note that we do extra iterations to reduce relative timing overhead
  time_start = wall_time();
  for (int iterations = 0; iterations < NUM_ITERATIONS; iterations++) {
    alpha = 0.0;
    for (int i = 0; i < N; i++) {
      alpha += a[i] * b[i];
    }
  }
  time_serial = wall_time() - time_start;
  cout << "Serial execution time = " << time_serial << " sec" << endl;

  // Parallel version using reduction pragma
  cout << "Parallel dot product (reduction):" << endl;
  for (int num_threads = 1; num_threads <= 24; num_threads++) {
    omp_set_num_threads(num_threads);
    long double alpha_parallel_red = 0;
    double time_red = 0;

    time_start = wall_time();
    for (int iterations = 0; iterations < NUM_ITERATIONS; iterations++) {
      alpha_parallel_red = 0.0;
#pragma omp parallel for reduction(+:alpha_parallel_red)
      for (int i = 0; i < N; i++) {
        alpha_parallel_red += a[i] * b[i];
      }
    }
    time_red = wall_time() - time_start;

    // Check correctness
    if ((fabs(alpha_parallel_red - alpha) / fabs(alpha_parallel_red)) > EPSILON) {
      cout << "Incorrect result for num_threads=" << num_threads << endl;
      cerr << "Alpha not implemented correctly!\n";
      exit(1);
    }

    cout << "Threads: " << num_threads
         << ", Dot product: " << alpha_parallel_red
         << ", Time: " << time_red << " sec" << endl;
  }

  // Parallel version using critical pragma
  cout << "Parallel dot product (critical):" << endl;
  for (int num_threads = 1; num_threads <= 24; num_threads++) {
    omp_set_num_threads(num_threads);
    long double alpha_parallel_crit = 0;
    double time_critical = 0;

    time_start = wall_time();
    for (int iterations = 0; iterations < NUM_ITERATIONS; iterations++) {
      alpha_parallel_crit = 0.0;
#pragma omp parallel
      {
        double local_alpha = 0.0;
#pragma omp for
        for (int i = 0; i < N; i++) {
          local_alpha += a[i] * b[i];
        }
#pragma omp critical
        alpha_parallel_crit += local_alpha;
      }
    }
    time_critical = wall_time() - time_start;

    // Check correctness
    if ((fabs(alpha_parallel_crit - alpha) / fabs(alpha_parallel_crit)) > EPSILON) {
      cout << "Incorrect result for num_threads=" << num_threads << endl;
      cerr << "Alpha not implemented correctly!\n";
      exit(1);
    }

    cout << "Threads: " << num_threads
         << ", Dot product: " << alpha_parallel_crit
         << ", Time: " << time_critical << " sec" << endl;
  }

  // De-allocate memory
  delete[] a;
  delete[] b;

  return 0;
}
