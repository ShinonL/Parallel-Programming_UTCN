#include <omp.h>
#include <iostream>

int main(int argc, char* argv[]) {
    omp_set_num_threads(atoi(argv[1]));

    long long int M = 0;
    long long int N = 1000000000;

    double startTime = omp_get_wtime();

#pragma omp parallel 
    {
        srand(omp_get_thread_num() + omp_get_wtime());

        #pragma omp for reduction(+:M)
        for (long long int i = 0; i < N; i++) {
            double point_X = (double)rand() / RAND_MAX;
            double point_Y = (double)rand() / RAND_MAX;
            
            if (point_X * point_X + point_Y * point_Y < 1) {
                M++;
            }
        }
    }
    
    double endTime = omp_get_wtime();

    double pi = 4.0 * M / N;
    printf("PI = %lf \n Execution time: %lf", pi, endTime - startTime);
}
