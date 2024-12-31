#include "iostream"

using namespace std;

class Sort {
    public:
        int * sorted_array;

        int * sort(int * array) {
            for (int i=0; i <5; i++) {
                for (int j=0; j<5-i-1; j++) {
                    if (array[j] > array[j+1]) {
                        int temp = array[j];
                        array[j] = array[j+1];
                        array[j+1] = temp;
                    }
                }
            }
            this->sorted_array = array;
            return array;
        }

        void display() {
            for (int i = 0; i < 5; i++ ) {
                cout << this->sorted_array[i] << "-->";
            }
        }
};

int main() {
    int sample_array[5] = {4, 3, 5, 2, 1};
    Sort s1;
    s1.sort(sample_array);
    s1.display();
    return 0;
}