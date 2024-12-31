#include "iostream"
#include <vector>

using namespace std;

string longestCommonPrefix(vector<string>& strs) {
    if (strs[0].size() == 0) {
        return "";
    }
    string output = "";

    for (int i=0; i<strs[0].size(); i++) {
        output.push_back(strs[0][i]);
        for (auto str : strs) {
            if (str[i] == output.back()) {
                continue;
            }
            else {
                output.pop_back();
                return output;
            }
        }
    }
    return output;
}

int main() {
    vector<string> strs = {"flower", "flo", "flows"};
    string output = longestCommonPrefix(strs);
    cout << output;
    return 0;
}