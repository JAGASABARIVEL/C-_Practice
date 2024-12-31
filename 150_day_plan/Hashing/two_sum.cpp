#include "iostream"
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    vector<int> ans, nums = {3,2,4};
    int target = 6;

    unordered_map<int, int> mapper;
    for (int i=0; i<nums.size(); i++) {
        int num = target - nums[i];
        auto second_pair = mapper.find(num);
        if (second_pair != mapper.end()) {
            ans = {second_pair->second, i};
            break;
        }
        mapper[nums[i]] = i;
    }
    
    

    for (auto j : ans) {
        cout << j << ",";
    }

    return 0;
}