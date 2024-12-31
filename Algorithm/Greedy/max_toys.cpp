#include "iostream"
#include <bits/stdc++.h>

using namespace std;

int buy_toys(int * toys, int total_toys, int available_amount) {
    int sum=0, count=0;
    sort(toys, toys + total_toys);

    for (int i=0; i < total_toys; i++) {
        if (toys[i] > available_amount) {
            break;
        }
        sum += toys[i];
        if (sum < available_amount) {
            count++;
        }
    }
    return count;
}

int main() {
    int N = 10, K =  50,  cost[10] = { 1, 12, 5, 111, 200, 1000, 10, 9, 12, 15 };
    cout << buy_toys(cost, N, K);
    return 0;
}