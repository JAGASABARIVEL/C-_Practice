#include "iostream"
#include <map>

using namespace std;

int main() {
    string s = "ababcd", longest_substring = "", temp_substring = "";
    map<char, bool> registers;
    int start = 0, end = 0;
    while (start < s.size()) {
        if (registers.count(s[end]) > 0) {
            if (temp_substring.size() > longest_substring.size()) {
                longest_substring = temp_substring;
            }
            temp_substring = "";
            start = start + 1;
            end = start;
            registers.clear();
        }
        else {
            registers[s[end]] = true;
            if (end != s.size()) {
                temp_substring += s[end];
                end += 1;
            }
        }
    }
    cout << "longest " << longest_substring << " " << longest_substring.size();

    return 0;
}