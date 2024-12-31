#include "iostream"
#include <bits/stdc++.h>
#include <vector>

using namespace std;

struct meetings
{
    int start_time, end_time, pos=0;
};

bool compare(meetings m1, meetings m2) {
    return m1.end_time < m2.end_time;
}

void find_max_meetings(vector<int> start, vector<int> end) {
    int total_meetings = start.size();
    vector<meetings> meet(total_meetings);

    for (int i=0; i<total_meetings; i++) {
        meet[i].start_time = start[i];
        meet[i].end_time = end[i];
        meet[i].pos = i + 1;
    }
    //sort(meet.begin(), meet.end(), compare);

    int i=0;
    cout << meet[i].pos <<" ";
    for (int j=1; j<total_meetings; j++) {
        if (meet[j].start_time >= meet[i].end_time) {
            i = j;
            cout << meet[j].pos <<" ";
        }
    }
}

int main() {
    vector<int> start = { 1, 3, 0, 5, 8, 5 };
    vector<int> end = { 2, 4, 6, 7, 9, 9 };
    find_max_meetings(start, end);
    return 0;
}