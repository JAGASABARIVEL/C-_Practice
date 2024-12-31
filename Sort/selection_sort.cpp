#include "iostream"

using namespace std;

class Sort {
    public:
        int * sorted_array;
        int * sort(int array[]) {
            for (int i=0; i < 5; i++) {
                int min = i;
                for (int j=i+1; j < 5; j++) {
                    if (array[j] < array[min]) {
                        min = j;
                    }
                }
                if (min != i) {
                    int temp = array[i];
                    array[i] = array[min];
                    array[min] = temp;
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