#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define INTERVAL_START 11
#define INTERVAL_END 200000

bool isPrime(int number) {
    if (number % 2 == 0) 
        return false;

    for (int divisor = 3; divisor <= floor(sqrt(number)); divisor += 2) {
        if (number % divisor == 0) {
            return false;
        }
    }

    return true;
}

bool isCircularPrime(int number) {
    int count = 0;

    int temp = number;
    while (temp) {
        count++;
        temp /= 10;
    }
 
    int num = number;
    while (isPrime(num)) {
        num = (pow(10, count - 1)) * (num % 10) + num / 10;
        if (num == number)
            return true;
    }
 
    return false;
}

/* this function is executed by each process */
void do_work(int i, int PROCESSES) {
    for (int count = 0, number = INTERVAL_START + 2 * i; 
        number < INTERVAL_END; 
        count++, number = INTERVAL_START + 2 * i + 2 * count * PROCESSES) {
        if (isCircularPrime(number)) {
            printf("%d ", number);
        }
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Expected 1 parameter: PROCESSES.\n");
        exit(1);
    }

    int PROCESSES = atoi(argv[1]);

    int i, pid;
    struct timespec start, stop;

    /* Take initial time here *//* Use clock_gettime(). Do NOT use clock() */
    if( clock_gettime(CLOCK_REALTIME, &start) == -1 ) {
        printf("Error"); 
        exit(-2);
    }
    
    for ( i = 0 ; i < PROCESSES; i++) {
        pid = fork();
        if (pid < 0) {
            /* some error occurred –fork failed */
            printf("Error"); 
            exit(-1);
        }
        if(pid == 0) {
            /* child process code */
            do_work(i, PROCESSES); 
            exit(0);
        }
        /* do not place anywait()call here*/
    }
    
    /* wait for all processes to finish their execution */

    for (i = 0; i < PROCESSES; i++)
        wait(NULL);

    /* Take final time here */
    /* Use clock_gettime(). Do NOT use clock() */
    /* Compute the execution time*/
    if (clock_gettime(CLOCK_REALTIME, &stop) == -1) {
        printf("Error"); 
        exit(-2);
    }

    double exec_time = (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec) * 1.0 / 1000000L;
    printf("\n%lf\n", exec_time);

    return 0;
}