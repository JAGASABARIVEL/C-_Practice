#include "iostream"
#include <vector>

using namespace std;

int main() {
    int start = 0, end = 0, sum = 0, length = 0, target = 7;
    vector<int> array = {2,3,1,2,4,3};

    for (;end < array.size();end++) {
        sum += array[end];

        while (sum >= target) {
            if (length == 0 || (end - start) + 1 < length) {
                length = (end - start) + 1;
            }
            sum -= array[start];
        }
    }
    return length;
}