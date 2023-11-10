#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool isPerfect(int number) {
    if (number == 1) {
        return false;
    }
    
    int sum = 1;
    for (int divisor = 2; divisor <= floor(sqrt(number)); divisor++) {
        if (number % divisor == 0) {
            sum += (divisor + (number / divisor));
        }
    }

    return sum == number;
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

    for (int X = A; X <= B; X++) {
        if (isPerfect(X)) {
            printf("%d ", X);
        }
    }

    printf("\n");
    return 0;
}
