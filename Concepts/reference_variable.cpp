#include "iostream"

using namespace std;

void swap(int & red) {
    red = 20;
}

int main() {
    int red = 10, blue = 20;
    swap(red);
    cout << red << endl;

    int * i;
    i = &red;
    int & j = *i;
    cout << *i << endl;

    j = blue;
    cout << *i << endl;

    return 0;
}
