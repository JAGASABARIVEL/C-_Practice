#include "iostream"
#include <map>
#include <vector>
#include <sstream>

using namespace std;

vector<string> split(string str, char delimiter) {
    vector<string> result;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delimiter)) {
        result.push_back(token);
    }
    return result;
}

int main() {
    string pattern = "jquery", s = "jquery";
    map<char, string> ps;
    map<string, char> sp;
    bool word_pattern = true;
    auto ssplit = split(s, ' ');
    cout << ssplit.size() << endl;
    if (ssplit.size() != pattern.size()) {
        return false;
    }
    for (int i = 0; i < ssplit.size(); i++) {
        char pattern_char = pattern[i];
        string word_string = ssplit[i];
        if ((ps.count(pattern_char) > 0 && ps[pattern_char] != word_string) || (sp[word_string] && sp[word_string] != pattern_char)) {
            word_pattern = false;
            break;
        }
        ps[pattern_char] = word_string;
        sp[word_string] = pattern_char;
    }
    cout << word_pattern;
    return 0;
}