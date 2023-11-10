#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

char* prepareLetters() {
    char* letters = (char*)malloc(sizeof(char) * 26);
    for (char letter = 'A'; letter <= 'Z'; letter++) {
        letters[letter - 'A'] = letter;
    }

    return letters;
}

int main(int argc, char* argv[]) {
    char* letters = prepareLetters();
    vector<string> keys;

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            for (int k = 0; k < 26; k++) {
                for (int l = 0; l < 26; l++) {
                    int det = i * l - k * j;

                    if (det != 0 && det % 2 != 0 && det % 13 != 0) {
                        string key = "";
                        key.push_back(letters[i]); 
                        key.push_back(letters[j]);
                        key.push_back(letters[k]);
                        key.push_back(letters[l]);

                        keys.push_back(key);
                    }
                }
            }
        }
    }

    sort(keys.begin(), keys.end());

    cout << "Total keys: " << keys.size() << "\n";

    ofstream write("keys.txt");
    for (string key: keys) {
        write << key << "\n";
    }

    return 0;
}
