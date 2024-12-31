#include "iostream"
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> height = {8,7,2,1};
    int i = 0, j = height.size() - 1, max_volume = 0;
    while (i != j) {
        int volume = min(height[i] , height[j]) *  (j - i);
        if (volume >= max_volume) {
            max_volume = volume;
        }
        height[i] > height[j] ? j -= 1 : i += 1;
    }
    cout << max_volume;
    return 0;
}