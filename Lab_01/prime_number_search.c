#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*

Q1: 
    A, B, X -> integers
    P       -> pointer to the first value of the result array
            -> points to a contignous zone of memory where the values are stored in order

Q2:
    I used the clock() function from time.h that computes the number of clocks until the 
    current moment and then divided the number of clocks with CLOCKS_PER_SEC to get the 
    time

Q3:
    We need math.h

*/

bool isPrime(int number) {
    for (int divisor = 3; divisor <= floor(sqrt(number)); divisor += 2) {
        if (number % divisor == 0) {
            return false;
        }
    }

    return true;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Expected 2 parameters: A B.\n");
        exit(1);
    }

    int A = atoi(argv[1]);
    int B = atoi(argv[2]);

    if (A >= B) {
        printf("Expected A to be less than B.\n");
        exit(2);
    }

    int* P = (int*)malloc(((B - A ) / 2 + 1) * sizeof(int));
    int length = 0;
    
    long startTime = clock();

    printf("Prime numbers between %d and %d: \n", A, B);
    if (A < 3) {
        *(P + length) = 2;
        length++;
        A = 3;
    } 

    for (int X = A + 1 - (A % 2); X <= B; X += 2) {
        if (isPrime(X)) {
            *(P + length) = X;
            length++;
        }
    }

    for (int i = 0; i < length; i++) {
        printf("%d ", *(P + i));
    }
    printf("\n");

    double execTime = ((double)(clock() - startTime) / CLOCKS_PER_SEC) * 1000;
    printf("Execution time: %lf ms\n", execTime);
    return 0;
}
