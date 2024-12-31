#include "iostream"
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

void solve(vector<vector<int>> & ans, vector<int> & output, vector<bool> & visited, int start, vector<int> input) {
    if (output.size() == 3) {
        int sum = accumulate(output.begin(), output.end(), 0);
        if (sum == 0) {
            ans.push_back(output);
        }
        return;
    }

    for (int i = start; i < input.size(); i++) {
        if (visited[i] || i > 0 && input[i] == input[i - 1] && !visited[i - 1]) {
            continue;
        }
        visited[i] = true;
        output.push_back(input[i]);
        solve(ans, output, visited, i + 1, input);
        output.pop_back();
        visited[i] = false;
    }
}

int main() {
    vector<int> input = {-1,0,1,2,-1,-4};
    vector<vector<int>> ans;
    vector<int> output;
    vector<bool> visited(nums.size(), false);
    sort(nums.begin(), nums.end());
    solve(ans, output, visited, 0, nums);

    for (auto elem : ans) {
        cout << "[";
        for (auto elem1 : elem) {
            cout << elem1 << ",";
        }
        cout << "]";
    }
}