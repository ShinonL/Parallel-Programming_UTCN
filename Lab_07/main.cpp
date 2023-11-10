#include <omp.h>
#include <iostream>

int main() {
    omp_set_num_threads(7);
    // int x = 0; // shared

    int a = 1; //shared
    int b = 1; // private fara valoare, local pentru fiecare thread, neinitializat in thread
    int c = 1; // private, copiat cu tot cu valoare, dupa regiunea paralela b va fi cat era inainte

    // last privat -> ia ultima valoare a numarului

// parte din cod care se executa pe nr max de thread-uri (daca nu e setat nimic)
// master are id 0
#pragma omp parallel 
    {
        // printf("ceva %d \n", omp_get_thread_num());
        // x++; // nu e sincronizat -> pragma omp critical {}

        // pragma omp bariera -> toate asteapta pana se termina codul de deasupra 

        #pragma omp for reduction(+ : x) private(b) firstprivate(c) // reduction(operatorul_atomic:variabila_atomica) nu e mandatory
        for (int i = 0; i < 10; i++) {
            printf("i = %d Thread = %d\n", i, omp_get_thread_num());
        }
    }

    // printf("x = %d", x);
}
