#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
Q1:
    O, Z, T -> unsigned long long to store the number of bits in an 1GB file
    N       -> integer to store the size in bytes of an 1GB file     
    S       -> pointer to the first char (1 byte) value of the randomly generated array which
                will have the size N
            -> will point to the bytes array
    E       -> double value to store the entropy (between 0 and 1)

Q2:
    Functions used:
        rand()  -> generates a random integer value
        srand() -> initializes the random number generator used by the function rand
    Headers necessary:
        stdlib.h

Q3:
    I used the clock() function from time.h that computes the number of clocks until the 
    current moment and then divided the number of clocks with CLOCKS_PER_SEC to get the 
    time

Q4:
    Dynamic allocation of size N*sizeof(byte)

Q5:
    Static: SIZE_MAX (18446744073709551615UL)

Q6:
    Dynamic: RAM size

Q7:
    We have log2(X). Which is our desired function.

    HOWEVER, if we want to reinvent the wheel, we could do:
        log2(X) = log(X) / log(2)

Q8:
    As all values are fromj 0 to 255 (all possible values) we could store them in
    a look-up table where for value bitCount[i] we have the number of 1s in the 
    binary representation of i

    Brian Kernighan Algorithm is a fast way to compute the number of 1s in a number

*/

static uint8_t bitCount[256];

int brianKernighan(int num) {
    int count;
    for (count = 0; num; count++) {
        num &= num - 1;
    }

    return count;
}

void bitCount_init() {
    for (int currentNumber = 0; currentNumber < 256; currentNumber++) {
        bitCount[currentNumber] = brianKernighan(currentNumber);
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Expected 1 parameter: N.\n");
        exit(1);
    }

    int N = atoi(argv[1]);

    if (N <= 0) {
        printf("Expected N to be greater than 0.\n");
        exit(2);
    }
    
    unsigned char* S = (unsigned char*)malloc(N * sizeof(unsigned char));

    long startTime = clock();

    time_t t;
    srand(time(NULL));
    for (int i = 0 ; i < N; i++) {
        *(S + i) = rand() % 256;
    }

    bitCount_init();

    unsigned long long T = (unsigned long long)8 * N;

    unsigned long long O = 0;
    for (int i = 0 ; i < N; i++) {
        O += bitCount[*(S + i)];
    }

    unsigned long long Z = T - O;

    double E = 
        - ((double) O * 1.0 / T) * log2(((double) O * 1.0 / T)) 
        - ((double) Z * 1.0 / T) * log2(((double) Z * 1.0 / T));


    printf("Entropy: %.20lf\n", E);

    double execTime = ((double)(clock() - startTime) / CLOCKS_PER_SEC) * 1000;
    printf("Execution time: %lf ms\n", execTime);
    return 0;
}
