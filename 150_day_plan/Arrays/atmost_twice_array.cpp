#include "iostream"
#include <vector>
using namespace std;

int main() {
    vector<int> nums = {0,0,1,1,1,1,2,3,3}; // {0, 0, 1, 1, 2, 3, 2, 3, 3}

    int unique = 0, unique_count = 1;

    for (int i=1; i < nums.size(); i++) {
        if (nums[i] != nums[unique]) {
            unique += 1;
            unique_count = 1;
            nums[unique] = nums[i];
        }
        else if (nums[i] == nums[unique] && unique_count < 2) {
            unique += 1;
            nums[unique] = nums[i];
            unique_count += 1;
        }
    }

    for (int j=0; j < unique; j++) {
        cout << nums[j] << ",";
    }


    return 0;
}