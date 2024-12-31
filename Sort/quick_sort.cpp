#include "iostream"

using namespace std;

class Sort {
    public:

        void sort(int * array, int left, int right) {
            if (left < right) {
                int middle = pivot(array, left, right);
                sort(array, left, middle - 1);
                sort(array, middle + 1, right);
            }
        }

        int pivot(int * array, int left, int right) {
            int pivot_element = array[right], pindex=left;

            for (int start=left; start < right; start++) {
                if (array[start] < pivot_element) {
                    int temp = array[start];
                    array[start] = array[pindex];
                    array[pindex] = temp;
                    pindex++;
                }
            }
            int temp = array[right];
            array[right] = array[pindex];
            array[pindex] = temp;
            return pindex;
        }


        void display(int * sorted_array) {
            for (int i = 0; i < 5; i++ ) {
                cout << sorted_array[i] << "-->";
            }
        }
};

int main() {
    int sample_array[5] = {4, 3, 5, 2, 1};
    Sort s1;
    s1.sort(sample_array, 0, 4);
    s1.display(sample_array);
    return 0;
}