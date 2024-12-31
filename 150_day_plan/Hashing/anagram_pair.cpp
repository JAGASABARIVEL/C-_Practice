#include "iostream"
#include <vector>
#include <unordered_map>
#include <array>

using namespace std;


int main() {
    vector<string> strs = {"eat","tea","tan","ate","nat","bat"};
    unordered_map<string, vector<string>> ans;
    vector<vector<string>> result;
    for (auto str : strs) {
        array<int, 26> count = {0};
        for (char chr : str) {
            count[chr - 'a']++;
        }
        string key = "";
        for (int c : count) {
            key += to_string(c) + "#";
        }
        cout << "Key " << key <<endl;
        ans[key].push_back(str);
    }
    for (auto & a : ans) {
        result.push_back(move(a.second));
    }
    return 0;
}