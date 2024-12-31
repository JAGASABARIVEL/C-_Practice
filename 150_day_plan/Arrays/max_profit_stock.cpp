#include "iostream"
#include <vector>
#include <climits>

using namespace std;

int main() {
    vector<int> prices = {7,1,5,3,6,4};
    int i = 0, j = prices.size() - 1, max_profit=0, min_price = INT_MAX;

    for (int i=0; i <prices.size(); i++) {
        if (prices[i] < min_price)
            min_price = prices[i];
        
        if (prices[i] - min_price > max_profit)
            max_profit = prices[i] - min_price;
    }
    cout << max_profit;
    return 0;
}