#include "iostream"

using namespace std;

class Sort {

    public:
        void merge(int * array, int left, int middle, int right) {
            int i = left, j = middle + 1, k = left, temp[5];
    
            while (i <= middle && j <= right) {
    
                if (array[i] <= array[j]) {
                    temp[k] = array[i];
                    k++;
                    i++;
                }
    
                else {
                    temp[k] = array[j];
                    k++;
                    j++;
                }
            }
    
            while (i <= middle) {
                temp[k] = array[i];
                k++;
                i++;
            }
    
            while (j <= right) {
                temp[k] = array[j];
                k++;
                j++;
            }
    
            for (int p=left; p <= right; p++) {
                array[p] = temp[p];
            }
        }
    
        void sort(int * array, int left, int right) {
    
            if (left < right) {
                int middle = (left + right) / 2;
                sort(array, left, middle);
                sort(array, middle + 1, right);
                merge(array, left, middle, right);
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
    s1.sort(sample_array, 0, 4);
    s1.display(sample_array);
    return 0;
}