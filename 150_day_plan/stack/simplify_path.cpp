#include "iostream"
#include<vector>
#include <sstream>

using namespace std;


void split(vector<string> & result, string s, char delimiter) {
    stringstream ss(s);
    string token;
    while(getline(ss, token, delimiter)) {
        result.push_back(token);
    }
}

int main() {
    string path = "/../";
    vector<string> stack, ans_stack;
    string ans = "/";
    split(stack, path, '/');

    for (auto j : stack) {
        if (j == ".." && ans_stack.size() > 0) {
            ans_stack.pop_back();
            continue;
        }
        if (j == "." || j == ".." || j.size() == 0) {
            continue;
        }
        ans_stack.push_back(j);
    }
    
    for (auto i : ans_stack) {
        ans += i + '/';
    }
    if (ans.size() > 1)
        ans.pop_back();
    
    //return ans;

    cout << ans;

    return 0;
}