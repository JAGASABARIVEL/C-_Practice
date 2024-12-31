/*
Key words: 
    left,
    right,
    mid = left+right/2
    if, data < a[mid] then, right = mid - 1
    if, data > a[mid] then, left = mid + 1
*/

#include "iostream"

using namespace std;

class Search {

    public:
        int binary_search(int array[], int left, int right, int data) {
            int mid = ( left + right ) / 2;
            if ( data == array[mid] ) {
                return mid;
            }
            else if (data < array[mid]) {
                right = mid - 1;
                return binary_search(array, left, right, data);
            }
            else if (data > array[mid]) {
                left = mid + 1;
                return binary_search(array, left, right, data);
            }
            return -1;
        }
};

int main() {
    int sample_array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, find_number = 4;
    Search s1;
    int find_index = s1.binary_search( sample_array, 0, size(sample_array)-1, find_number );
    cout << "Number "<< find_number <<" is at index " << find_index;
    return 0;
}