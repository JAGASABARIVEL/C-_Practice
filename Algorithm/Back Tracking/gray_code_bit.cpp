#include "iostream"
#include <vector>

using namespace std;


int pow(int base, int exponent) {
    int total = 1;
    for (int i = 0; i < exponent; i++) {
        total = total * base;
    }
    return total;
}

int main() {
    int n = 5;

    int max_range = pow(2, n);
    vector<int> ans;
    
    for (int i = 0; i < max_range; ++i) {
        ans.push_back(i ^ (i >> 1));
    }

    for (auto i : ans) {
        cout << i;
    }
}
