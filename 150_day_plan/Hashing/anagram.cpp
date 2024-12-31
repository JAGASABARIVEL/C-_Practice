#include "iostream"
#include <unordered_map>

using namespace std;

int main() {
    string s = "anagram", t = "naagaram";
    bool is_anagram = true;
    unordered_map<char, int> map;

    if (s.size() != t.size()) {
        is_anagram = false;
    }

    for (char c : s) {
        if (map[c]) {
            map[c] = map[c] + 1;
        }
        else {
            map[c] = 1;
        }
    }

    for (char c : t) {
        if (map[c] && map[c] > 0) {
            map[c] = map[c] - 1;
        }
        else {
            is_anagram = false;
            break;
        }
    }

    cout << is_anagram;

    return 0;
}