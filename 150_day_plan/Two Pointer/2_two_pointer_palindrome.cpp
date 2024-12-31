#include "iostream"
#include "vector"

using namespace std;

bool isAlpha(int symbol) {
    if (symbol >= 65 && symbol <=90 || symbol >= 97 && symbol <= 122) {
        return true;
    }
    return false;
}

bool isNum(int symbol) {
    if (symbol >= 48 && symbol <= 57) {
        return true;
    }
    return false;
}

bool isPlaindrome(string word) {
    int i = 0, j = word.size() - 1;
    while (i < word.size() / 2 && j >= word.size() / 2) {
        if (word[i] != word[j]) {
            return false;
        }
        i++;
        j--;
    }
    return true;
}

int main() {
    string raw_string = "0P";
    string clean_string;
    for (auto symbol : raw_string) {
        if (isAlpha(symbol) || isNum(symbol)) {
            clean_string.push_back(tolower(symbol));
        }
    }
    cout << isPlaindrome(clean_string);
    return 0;
}