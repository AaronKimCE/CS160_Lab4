#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

static long num_steps = 100000;
double step;

void main () {
  int i;
  double pi, sum;

  step = 1.0/(double)num_steps;
  double start, end;
  
  start = omp_get_wtime();
  omp_set_num_threads(16); 

  #pragma omp parallel 
  {
    int id = omp_get_thread_num();
    int num = omp_get_num_threads();
    double x;
    #pragma omp for reduction(+:sum)
    for (i = 0; i < num_steps; i++) {
      x = (i + 0.5) * step;
      sum = sum + 4.0 / (1.0 + x * x);
    }
    
  }
  pi = sum * step;
   
  end = omp_get_wtime() - start;
  printf("pi = %f, Runtime = %f \n", pi, end);

  return;
}
