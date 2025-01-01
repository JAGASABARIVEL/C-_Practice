#include "iostream"

using namespace std;

int main() {
    int n = 1234;
    int reversed_number = 0;
    while (n != 0) {
        reversed_number = (reversed_number * 10) + (n%10);
        n = n / 10;
    }
    cout << reversed_number;
    return 0;
}