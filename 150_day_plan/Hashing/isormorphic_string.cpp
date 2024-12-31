#include "iostream"
#include <vector>
#include <map>
using namespace std;

int main() {

    string s = "foo", t = "bar";
    map<char, char> smaps;
    map<char, char> tmaps;
    bool isoprophic = true;

    for (int i = 0; i< s.length(); i++) {
        char s_letter = s[i], t_letter = t[i];

        if ((smaps[s_letter] && smaps[s_letter] != t_letter) || (tmaps[t_letter] && tmaps[t_letter] != s_letter)) {
            isoprophic = false;
            break;
        }
        smaps[s_letter] = t_letter;
        tmaps[t_letter] = s_letter;
    }

    //return isoprophic;
    cout << isoprophic << endl;
    return 0;
}