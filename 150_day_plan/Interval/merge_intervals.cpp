#include "iostream"
#include <vector>
#include <algorithm>

using namespace std;

int main () {

    vector<vector<int>> intervals = {{1, 4}, {0, 5}};
    sort(intervals.begin(), intervals.end(), [](vector<int> a, vector<int> b) { return a[0] < b[0]; });

    int start = intervals[0][0];
    int end = intervals[0][1];
    vector<vector<int>> ans;

    for (int i=1; i<intervals.size(); i++) {
        if (
            (intervals[i][0] <= end && intervals[i][0] >= start) ||
            (intervals[i][1] <= end && intervals[i][1] >= start)
        ) {
            start = min(intervals[i][0], start);
            end = max(intervals[i][1], end);
            continue;
        }
        else {
            ans.push_back({start, end});
            start = intervals[i][0];
            end = intervals[i][1];
        }
    }
    ans.push_back({start, end});

    for (auto i : ans) {
        cout << "[" << i[0] << " " << i[1] << "], ";
    }

    return 0;
}