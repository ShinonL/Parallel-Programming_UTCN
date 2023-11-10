#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

#define FILE_SIZE 157248
#define ENCRYPTED_VALUE "FRAKEA"
#define WORD_LENGTH 7
#define MaxDataLen 7

using namespace std;

char* prepareLetters() {
    char* letters = (char*)malloc(sizeof(char) * 26);
    for (char letter = 'A'; letter <= 'Z'; letter++) {
        letters[letter - 'A'] = letter;
    }

    return letters;
}

set<string> prepareDictionary() {
    ifstream read_words("6-letter-words.txt");

    set<string> dictionary;
    string word;
    while(getline(read_words, word)) {
        transform(word.begin(), word.end(), word.begin(), [](unsigned char c){ return std::toupper(c); });
        dictionary.insert(word);
    }

    read_words.close();
    return dictionary;
}

string convertToString(int** mat, char* letters) {
    string val = "";

    val.push_back(letters[mat[0][0]]); 
    val.push_back(letters[mat[1][0]]);

    return val;
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
    char* letters = prepareLetters();
    set<string> dictionary = prepareDictionary();
    
    ifstream read("keys.txt");
    ofstream write("mesg.txt");
    ofstream write_words("engl.txt");

    string key;
    while(getline(read, key)) {
        string decryptedValue = decrypt(key, ENCRYPTED_VALUE, letters);
        write << decryptedValue << "\n";

        if (dictionary.find(decryptedValue) != dictionary.end()) {
            write_words << decryptedValue << "\n";
            dictionary.erase(decryptedValue);
        }
    }

    read.close();
    write.close();
    write_words.close();

    return 0;
}
