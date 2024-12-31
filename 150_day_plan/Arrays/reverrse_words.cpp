#include "iostream"
#include <vector>
#include <sstream>

using namespace std;

void split(vector<string> & result, string line, char delimiter) {
    stringstream ss(line);
    string token;
    vector<string> resut;

    while(getline(ss, token, delimiter)) {
        if (token != " ")
            result.push_back(token);
    }
}

int main() {
    string s = "  hello world  ";
    vector<string> output;
    split(output, s, ' ');
    string ans="", word;
    for (int i=output.size() - 1; i>=0; i--) {
        word = output[i];
        if (!word.size())
            continue;
        ans +=word;
    }
    if (ans.back() == ' ')
        ans.pop_back();
    return 0;
}