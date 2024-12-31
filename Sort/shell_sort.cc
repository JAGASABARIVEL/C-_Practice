#include "iostream"

using namespace std;

class Sort {
    public:
        void sort(int * array, int size) {
            for (int gap=size/2; gap > 0; gap=gap/2) {
                for (int i=gap; i < size; i++) {
                    int temp = array[i], j=i;                    
                    for (; j >= gap && array[j - gap] > temp; j -= gap) {
                        array[j] = array[j - gap];
                    }
                    array[j] = temp;
                }
            }
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
    s1.sort(sample_array, 5);
    s1.display(sample_array);
    return 0;
}