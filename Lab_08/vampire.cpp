#include <omp.h>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

bool isVampireNumber(int number) {
    string numberStr = to_string(number);
    sort(numberStr.begin(), numberStr.end());

    int fangSize = strlen(numberStr.c_str()) / 2;

    for (int i = pow(10, fangSize - 1); i <= sqrt(number); i++) {
        if (number % i == 0) {
            bool doubleZero = (i % 10 == 0) && ((number / i ) % 10 == 0);
            string fangs = to_string(i) + to_string(number / i);
            sort(fangs.begin(), fangs.end());
            if (fangs.compare(numberStr) == 0 && !doubleZero) {
                return true;
            }
        }
    }

    return false;
}

int main(int argc, char* argv[]) {
    omp_set_num_threads(atoi(argv[1]));

    long long int start = atoi(argv[2]);
    long long int end = atoi(argv[3]);
    vector<int> result;
    int count = 0;

    double startTime = omp_get_wtime();

#pragma omp parallel shared(result) firstprivate(count)
    {
        int threadId = omp_get_thread_num();
        #pragma omp for
        for (long long int i = start; i <= end; i++) {
            if (isVampireNumber(i)) {
                count++;

                #pragma omp critical
                result.push_back(i);
            }
        }
        printf("Thread %d count: %d\n", threadId, count);
    }
    
    double endTime = omp_get_wtime();

    sort(result.begin(), result.end());

    FILE* fd = fopen("result.txt", "w+");
    for (auto i : result) {
        fprintf(fd, "%d\n", i);
    }

    printf("\nTotal count: %d\nExecution time: %lf", result.size(), endTime - startTime);

    return 0;
}
