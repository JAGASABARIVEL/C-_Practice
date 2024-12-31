#include "iostream"
#include <vector>

using namespace std;

int main() {
    vector<int> nums = {1,2,3,4,5,6,7};
    int k = 6;
    k = k % nums.size();
    vector<int> front, back;
    

    for (int i=nums.size() - k; i<nums.size(); i++) {
        front.push_back(nums[i]);
    }
    for (int j=0; j<nums.size() - k; j++) {
        back.push_back(nums[j]);
    }

    nums.clear();
    for (auto i : front) {
        nums.push_back(i);
    }
    for (auto i : back) {
        nums.push_back(i);
    }

    for (int i=0; i <nums.size(); i++) {
        cout << nums[i] << ", ";
    }
    return 0;
}