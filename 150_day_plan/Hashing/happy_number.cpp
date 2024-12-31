#include "iostream"
#include <unistd.h>

#include <unordered_set>

using namespace std;

int main() {
    int n = 2;
    unordered_set<int> map;
    int sum = 0, digit;
    while (n >= 0) {
        digit = n % 10;
        sum += (digit * digit);
        n = n / 10;
        if (n <= 0) {
            n = sum;
            sum = 0;
            if (map.find(n) != map.end()) {
                break;
            }
            else  if (n == 1) {
                break;
            }
            else {
                map.insert(n);
            }
        }
    }
    cout << sum;
}