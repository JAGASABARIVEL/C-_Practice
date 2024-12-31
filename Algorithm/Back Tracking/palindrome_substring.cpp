#include "iostream"
#include <vector>

using namespace std;

    string reverse(string word) {
    int lengthof_word = word.size();
    string new_word;

    while(lengthof_word > 0) {
        new_word += word[lengthof_word - 1];
        lengthof_word -= 1;
    }
    return new_word;
}

bool isPalindrome(vector<string> s) {
    for (auto word : s) {
        if (word != reverse(word)) {
            return false;
        }
    }
    return true;
}

bool solve(vector<vector<string>> & ans, vector<string> & output, int strpointer, string s) {
    if (strpointer == s.size()) {
        if (isPalindrome(output)) {
            ans.push_back(output);
            return true;
        }
        return false;
    }
    for (int i=1; i<=s.size(); i++) {
        if (strpointer >= s.size()) {
            return false;
        }
        string word = s.substr(strpointer, i);
        cout << word << endl;
        output.push_back(word);
        if (solve(ans, output, strpointer + i, s)) {
            output.pop_back();
            break;
        }
        output.pop_back();
    }
    return false;
}

int main() {
    string s = "a";
    vector<vector<string>> ans;
    vector<string> output;
    int strpointer = 0;
    solve(ans, output, strpointer, s);

    for (auto i : ans) {
        cout << "[";
        for (auto j : i) {
            cout << j << " ";
        }
        cout << "], ";
        cout << endl;
    }

    return 0;
}