#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>

#define FILE_SIZE 157248

using namespace std;

string readKey() {
    ifstream read("keys.txt");

    srand(time(0));
    int lineNumber = rand() % FILE_SIZE;
    int count = 0;

    string key;
    while(getline(read, key)) {
        if (lineNumber == count) {
            read.close();
            return key;
        }
        count++;
    }

    read.close();
    return "";
}

int** convertKey(string str) {
    int** mat = (int**)malloc(sizeof(int*) * 2);
    mat[0] = (int*)malloc(sizeof(int) * 2);
    mat[1] = (int*)malloc(sizeof(int) * 2);

    mat[0][0] = str.at(0) - 'A';
    mat[0][1] = str.at(1) - 'A';
    mat[1][0] = str.at(2) - 'A';
    mat[1][1] = str.at(3) - 'A';

    return mat;
}

int** convertValue(string str, int start) {
    int** mat = (int**)malloc(sizeof(int*) * 2);
    mat[0] = (int*)malloc(sizeof(int));
    mat[1] = (int*)malloc(sizeof(int));

    mat[0][0] = str.at(0 + start * 2) - 'A';
    mat[1][0] = str.at(1 + start * 2) - 'A';

    return mat;
}

int** multiply(int** mat, int** key) {
    int** result = (int**)malloc(2 * sizeof(int*));
    result[0] = (int*)malloc(sizeof(int));
    result[1] = (int*)malloc(sizeof(int));

    result[0][0] = (mat[0][0] * key[0][0] + mat[1][0] * key[0][1]) % 26;
    result[1][0] = (mat[0][0] * key[1][0] + mat[1][0] * key[1][1]) % 26;

    return result;
}

int** computeAdjoint(int** mat) {
    int** adjoint = (int**)malloc(sizeof(int*) * 2);
    adjoint[0] = (int*)malloc(sizeof(int) * 2);
    adjoint[1] = (int*)malloc(sizeof(int) * 2);

    adjoint[0][0] = mat[1][1];
    adjoint[1][1] = mat[0][0];
    adjoint[0][1] = 26 - mat[0][1];
    adjoint[1][0] = 26 - mat[1][0];

    return adjoint;
}

int modularInverse(int number) {
    number = number < 0 ? 26 + number : number;

    for (int i = 1; i < 26; i++)
        if (((number % 26) * (i % 26)) % 26 == 1)
            return i;
    return 0;
}

int** computeInverse(int** mat) {
    int** inverse = (int**)malloc(sizeof(int*) * 2);
    inverse[0] = (int*)malloc(sizeof(int) * 2);
    inverse[1] = (int*)malloc(sizeof(int) * 2);

    int det = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    int modularInv = modularInverse(det % 26);

    int** adjoint = computeAdjoint(mat);

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            inverse[i][j] = (adjoint[i][j] * modularInv) % 26;
        }
    }

    return inverse;
}

char* prepareLetters() {
    char* letters = (char*)malloc(sizeof(char) * 26);
    for (char letter = 'A'; letter <= 'Z'; letter++) {
        letters[letter - 'A'] = letter;
    }

    return letters;
}

string convertToString(int** mat, char* letters) {
    string val = "";

    val.push_back(letters[mat[0][0]]); 
    val.push_back(letters[mat[1][0]]);

    return val;
}

string encrypt(string keyStr, string value, char* letters) {
    int** key = convertKey(keyStr);
    cout << "Random key: " << keyStr << " --> [[" << key[0][0] << " " << key[0][1] << "] [" << key[1][0] << " " << key[1][1] << "]]\n";

    int start = 0;
    string encryptedValue = "";
    while (start < value.size() / 2) {
        int** mat = convertValue(value, start);

        int** encryptedMat = multiply(mat, key);
        encryptedValue = encryptedValue + convertToString(encryptedMat, letters);

        start++;
    }

    return encryptedValue;
}

string decrypt(string keyStr, string value, char* letters) {
    int** key = convertKey(keyStr);
    int** inverse = computeInverse(key);

    int start = 0;
    string decryptedValue = "";
    while (start < value.size() / 2) {
        int** mat = convertValue(value, start);

        int** decryptedMat = multiply(mat, inverse);
        decryptedValue = decryptedValue + convertToString(decryptedMat, letters);

        start++;
    }

    return decryptedValue;
}

int main(int argc, char* argv[]) {
    string value = argv[1];
    if (value.size() % 2 == 1 || argc != 2) {
        cout << "Please enter an even value for encryption.\n";
        return -1;
    }

    char* letters = prepareLetters();
    string keyStr = readKey();
    
    string encryptedValue = encrypt(keyStr, value, letters);
    cout << "Encrypted value: " << encryptedValue << "\n";

    string decryptedValue = decrypt(keyStr, encryptedValue, letters);
    cout << "Decrypted value: " << decryptedValue << "\n";

    return 0;
}
