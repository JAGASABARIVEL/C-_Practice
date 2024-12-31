#include "iostream"

using namespace std;

void find_max_activities(int * start, int * finish, int total_activity) {
    int i=0, j=1;

    // Select 1st activity by default since we start from from somewhere
    cout << i << " ";
    
    for (j; j<total_activity; j++) {
        if (start[j] > finish[i]) {
            i = j;
            cout << i << " ";
        }
    }
}

int main() {
    int start[] = {1, 3, 0, 5, 8, 5}, finish[] = {2, 4, 6, 7, 9, 9};
    find_max_activities(start, finish, sizeof(start)/sizeof(start[0]));
    return 0;
}