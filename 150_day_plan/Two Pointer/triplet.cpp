#include "iostream"
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    vector<int> nums = {-1,0,1,2,-1,-4 };
    vector<vector<int>> ans;
    int i = 0, j = i + 1, k = nums.size() - 1, sum = 0;

    sort(nums.begin(), nums.end());

    while (i < nums.size()) {
        if (i > 0 && nums[i] == nums[i - 1]) {
            i += 1;
            continue;
        }
        j = i + 1;
        k = nums.size() - 1;
        while (j < k) {
            sum = nums[i] + nums[j] + nums[k];
            if (sum == 0) {
                ans.push_back({nums[i], nums[j], nums[k]});
                j += 1;
                while(j < k && nums[j] == nums[j - 1]) {
                    j += 1;
                }
            }
            else if (sum > 0) {
                k -= 1;
            }
            else if (sum < 0) {
                j += 1;
            }
        }
        i += 1;
    }

    for (auto elem : ans) {
        cout << "[";
        for (auto elem1 : elem) {
            cout << elem1 << ",";
        }
        cout << "]";
    }

    return 0;
}