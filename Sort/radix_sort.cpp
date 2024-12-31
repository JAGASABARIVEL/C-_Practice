#include "iostream"

using namespace std;

class Sort {
    public:

        void sort(int * array, int size) {
            int max_digit = max(array, size);
            for (int iterator=1; max_digit / iterator > 0; iterator *= 10) {
                radix_sort(array, iterator);
            }
        }

        void radix_sort(int * array, int iterator) {
            int bucket_array[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            int count_array[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            int temp[5];

            for (int i=0; i<5; i++) {
                bucket_array[(array[i] / iterator) % 10]++;
            }

            for (int j=1; j<10; j++) {
                count_array[j] = bucket_array[j] + count_array[j - 1];
            }

            for (int k=4; k>=0; k--) {
                int digit = (array[k] / iterator) % 10;
                temp[count_array[digit] - 1] = array[k];
                count_array[digit]--;
            }

            for (int l=0; l<5; l++) {
                array[l] = temp[l];
            }
        }

        int max(int * array, int size) {
            int max = array[0];
            for (int i=0; i < 5; i++) {
                if (array[i] > max) {
                    max = array[i];
                }
            }
            return max;
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