#include "walltime.h"
#include <math.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_THREADS 16 // Set the desired number of threads

int main(int argc, char *argv[]) {
  int N = 2000000000;
  double up = 1.00000001;
  double Sn = 1.00000001;
  int n;
  /* allocate memory for the recursion */
  double *opt = (double *)malloc((N + 1) * sizeof(double));

  if (opt == NULL)
    die("failed to allocate problem size");

  double time_start = wall_time();
  
  // Set the number of threads
  omp_set_num_threads(NUM_THREADS);
  #pragma omp parallel for firstprivate(Sn) lastprivate(Sn)
  for (n = 0; n <= N; ++n) {
    opt[n] = Sn;
    Sn *= up;
  }

  printf("Parallel RunTime   :  %f seconds\n", wall_time() - time_start);
  printf("Final Result Sn    :  %.17g \n", Sn);

  double temp = 0.0;
  for (n = 0; n <= N; ++n) {
    temp += opt[n] * opt[n];
  }
  printf("Result ||opt||^2_2 :  %f\n", temp / (double)N);
  printf("#Thread: %d\n", (int)NUM_THREADS);

  free(opt);
  
  return 0;
}
