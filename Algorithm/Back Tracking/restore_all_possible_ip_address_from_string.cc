# include "iostream"
#include <vector>
#include <sstream>
using namespace std;


vector<string> split(string str, char delimeter) {
    vector<string> tokens;
    stringstream sstream(str);
    string token;
    while (std::getline(sstream, token, delimeter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int sizeof_split_elem(vector<string> tokens) {
    int size = 0;
    for (auto token : tokens) {
        size += token.size();
    }
    return size;
}

bool isValidNum(int token) {
    cout << token << endl;
    if (token >= 48 && token <= 57) {
        return true;
    }
    return false;
}

bool solve(vector<string> & ans, string & output, int strpointer, string & str) {
    vector<string> tokens = split(output, '.');
    if (tokens.size() == 4 && sizeof_split_elem(tokens) == str.size()) {
        ans.push_back(output);
        return true;
    }

    if (tokens.size() >= 4) {
        return false;
    }

    if (strpointer >= str.size()) {
        return false;
    }

    for (int i=1; i<=3; i++) {
        if (strpointer + i > str.size()) {
            break;
        }
        
        string letter = str.substr(strpointer , i);

        // Append the segment to the output
        string prev_output = output;
        output += (output.empty() ? "" : ".") + letter;
        // Recurse to explore further splits
        solve(ans, output, strpointer + i, str);
        // Backtrack
        output = prev_output;
    
    }
    return false;
}

int main() {
    string s = "211111";
    vector<string> ans;
    vector<bool> used(s.size(), false);
    string output = "";
    int strpointer = 0;

    for (auto letter : s) {
        cout << letter << endl;
        if (!isValidNum(letter)) {
            return false;
        }
    }

    solve(ans, output, strpointer, s);

    for (auto i : ans) {
        cout << i << endl;
    }
    return 0;
}