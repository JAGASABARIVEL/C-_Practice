#include "iostream"
#include <vector>
#include <numeric>

using namespace std;

int pow(int base, int exponent) {
    int total = 1;
    for (int i = 0; i < exponent; i++) {
        total = total * base;
    }
    return total;
}

bool isItSafe(vector<int> & ans, int next) {
    if (ans.size() == 0) {
        return true;
    }

    int current = ans.back();
    int bit_difference = current ^ next;

    if ((bit_difference & (bit_difference - 1)) == 0) {
        return true;
    }
    return false;
}

bool solve(vector<int> & ans, vector<bool> & used, vector<int> & scale) {
    if (ans.size() == scale.size()) {
        return isItSafe(ans, ans[0]);
    }

    for (int i=0; i < scale.size(); i++) {
        if (used[i]) {
            continue;
        }
        if (isItSafe(ans, scale[i])) {
            used[i] = true;
            ans.push_back(scale[i]);
            if (solve(ans, used, scale)) {
                return true;
            }
            ans.pop_back();
            used[i] = false;
        }
    }
    return false;
}

int main() {
    
    int n = 5;
    int max_range = pow(2, n);
    vector<int> ans;
    vector<int> scale(max_range);
    vector<bool> used(max_range, false);
    iota(scale.begin(), scale.end(), 0);
    solve(ans, used, scale);

    for (auto i : ans)
        cout << i;

    return 0;
}