#include "iostream"

using namespace std;

int main() {
    string s = "abc", t = "ahbdc";
    if (!s.size()) {
        return true;
    }
    int fptr = 0, bptr = s.size() - 1, i = 0, j = t.size() - 1;
    bool isSubsequence = false;
    cout << t.size() << endl;
    while (i <= j) {
        if (t[i] == s[fptr]) {
            fptr += 1;
        }
        i += 1;
        if (t[j] == s[bptr] && j >= i) {
            bptr -= 1;
        }
        j -= 1;

        if (fptr > bptr || bptr < fptr) {
            isSubsequence = true;
        }
    }

    

    cout << isSubsequence;
    return 0;
}