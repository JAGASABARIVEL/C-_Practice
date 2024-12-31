#include "iostream"
#include <vector>

using namespace std;

void swap(vector<int> & array, int & i, int & j, int & k) {
    while (true) {
        if (array[i] == array[j]) {
            if (j <= i) {
                return;
            }
            k -= 1; j -= 1;
            continue;
        }
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
        k -= 1; j -= 1;
        break;
    }
}

int main() {
    vector<int> nums = {1};
    int val = 1, sizeof_array = nums.size();
    int i = 0, j = sizeof_array - 1, k = sizeof_array;
    while (i <= j) {
        if (nums[i] == val) {
            swap(nums, i, j, k);
        }
        if (nums[j] == val) {
            k -= 1; j -= 1;
        }
        i += 1;
    }

    for (auto i : nums) {
        cout << i << ",";
    }
    cout << endl << k;
    
    return 0;
}