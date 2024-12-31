#include "iostream"

using namespace std;

class Sort {
    public:
        int * sorted_array;

        int * sort(int * array) {
            
            for (int i=1; i < 5; i++) {
                int j = i - 1, key = array[i];
                while (j >= 0 && array[j] > key) {
                    array[j + 1] = array[j];
                    j = j - 1;
                }
                array[j+1] = key;
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