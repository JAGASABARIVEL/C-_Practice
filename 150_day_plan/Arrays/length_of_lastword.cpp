#include "iostream"
#include <vector>
#include <sstream>
using namespace std;

vector<string> split(string line, char delimiter) {
    vector<string> result;
    stringstream ss(line);
    string token;
    while (getline(ss, token, delimiter)) {
        result.push_back(token);
    }
    return result;
}

int main() {
    string s = "  ";

    vector<string> ans = split(s, ' ');
    int answer;
    for (int i=ans.size()-1; i>=0; i--) {
        answer = ans[i].size();
        if (answer) {
            break;
        }
    }
    cout << answer;
    return 0;
}