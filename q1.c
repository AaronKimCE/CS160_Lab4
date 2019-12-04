#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

static long num_steps = 100000;
double step;

void main () {
  int i;
  double pi, sum[16];

  step = 1.0/(double)num_steps;
  double start, end;
  
  start = omp_get_wtime();
  omp_set_num_threads(16);
  double total = 0; 

  #pragma omp parallel 
  {
    int id = omp_get_thread_num();
    int num = omp_get_num_threads();
    double x;
    total = 0;
    for (int j = id; j < num_steps; j += num) {
      x = (j + 0.5) * step;
      sum[id] = sum[id] + 4.0 / (1.0 + x * x);
    }
    
  }
  for (i = 0, pi = 0; i < 16; i++) {
    pi += sum[i] * step;
  } 
  end = omp_get_wtime() - start;
  printf("pi = %f, Runtime = %f \n", pi, end);

  return;
}
