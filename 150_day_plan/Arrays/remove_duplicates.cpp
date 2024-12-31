#include "iostream"
#include <vector>

using namespace std;

int main() {
    vector<int> nums = {0,0,1,1,1,2,2,3,3,4};
    int unique = 0;
    for (int i=1; i<nums.size(); i++) {
        if (nums[i] != nums[unique]) {
            unique++;
            nums[unique] = nums[i];
        }
    }
    
    return 0;
}