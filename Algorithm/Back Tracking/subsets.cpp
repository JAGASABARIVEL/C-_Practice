#include "iostream"
#include <vector>
#include <algorithm>

using namespace std;

void solve(vector<vector<int>> & ans, int start, vector<int> & output, vector<bool> & used, vector<int> nums) {
    ans.push_back(output);
    if (output.size() == nums.size()){
        return;
    }
    for (int i = start; i < nums.size(); i++) {
        if (used[i] || i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) {
            continue;
        }
        used[i] = true;
        output.push_back(nums[i]);
        solve(ans, i + 1, output, used, nums);
        output.pop_back();
        used[i] = false;
    }
}


int main() {
    vector<vector<int>> ans;
    vector<int> nums = {4,4,4,1,4};
    // Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
    // output: [[],[1],[1,4],[1,4,4],[1,4,4,4],[1,4,4,4,4],[4],[4,4],[4,4,4],[4,4,4,4]]
    int start = 0;
    vector<int> output;
    vector<bool> used(nums.size(), false);
    sort(nums.begin(), nums.end());
    solve(ans, start, output, used, nums);

    //ans = {{}, {1}, {1,2}};
    for (auto i : ans) {
        cout << "[";
        for (auto j : i) {
            cout << j << ",";
        }
        cout << "],";
    }
    return 0;
}