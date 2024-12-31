#include "iostream"

using namespace std;

enum Color {
    Red,
    Green,
    Blue,
    Yellow
};

int main() {
    // Can not re-initialize i
    const int i = Red;
    // Can not reintialize my_color
    const Color my_color = Color(0);
    cout << "Red " << my_color << endl;

    int k = 10, l = 20;
    int const * j = &k;
    // Can not change the value/address of pointer variable
    // *j = l;
    j = &l;

    cout << "Value of k " << k << endl;
    return 0;
}
