#include "iostream"
#include  "cmath"

using namespace std;

class MinHeap {
    public:
        int * array;
        int capacity, heap_size;
        
        MinHeap(int capacity) {
            this->capacity = capacity;
            this->heap_size = 0;
            this->array = new int[capacity];
            cout << "Min heap created with capacity " << capacity << endl;
        }

        int parent(int i) {
            return (i - 1) / 2;
        }

        int left(int i) {
            return (2 * i) + 1;
        }

        int right(int i) {
            return (2 * i) + 2;
        }

        int insert(int data) {
            if (heap_size == capacity) {
                cout << "Heap size overflow";
                return -1;
            }
            heap_size++;
            int i = heap_size - 1;
            array[i] = data;
            
            while (i != 0 && array[parent(i)] > array[i]) {
                int temp = array[parent(i)];
                array[parent(i)] = array[i];
                array[i] = temp;
                i = parent(i);
            }
            return 0;
        }

        int getMin() {
            return array[0];
        }

        void minHeapify(int i) {
            int smallest = i;
            int left = this->left(i);
            int right = this->right(i);

            if (left < this->heap_size && array[left] < array[smallest]) {
                smallest = left;
            }

            if (right < this->heap_size && array[right] < array[smallest]) {
                smallest = right;
            }

            if (i != smallest) {
                int temp = array[smallest];
                array[smallest] = array[i];
                array[i] = temp;
                minHeapify(smallest);
            }
        }

        int extractMin() {
            int root = array[0];
            
            array[0] = array[this->heap_size - 1];
            heap_size = heap_size - 1;
            
            minHeapify(0);
            return root;
        }

        void deleteKey(int key) {
            decreaseKey(key, INT_MIN);
            this->extractMin();
        }

        void decreaseKey(int key, int value) {
            int i = key;
            array[key] = value;
            while (i != 0 && array[this->parent(i)] > array[i]) {
                int temp = array[this->parent(i)];
                array[this->parent(i)] = array[i];
                array[i] = temp;

                i = this->parent(i);
            }
        }

        void sort() {
            int temp_array[this->capacity], i=0;
            while (heap_size != 0) {
                temp_array[i] = extractMin();
                i = i + 1;
            }
            for (int j = 0; j < i; j++) {
                cout << temp_array[j] << ",";
            }
            cout << endl;
        }


};

int main() {
    int option, capacity;
    cout << "Enter the capacity of the min heap" << endl;
    cin >> capacity;
    MinHeap m(capacity);
    do {
        cout << "Select the option from the below menu" << endl;
        cout << "1. Insert" << endl << "2. Get Min" << endl << "3. Display" << endl << "4. Extract Min" << endl << "5. Delete Key" << endl << "6. Sort" << endl << "7. Clear" << endl << "0. Exit" << endl;
        cin >> option;
        if (option == 1) {
            int data;
            cout << "Enter the data " << endl;
            cin >> data;
            m.insert(data);
        }
        else if (option == 2) {
            int min = m.getMin();
            cout << "Min value is " << min << endl;
        }
        else if (option == 3) {
            cout << "Displaying the Min heap tree" << endl;
        }
        else if (option == 4) {
            int min = m.extractMin();
            cout << "Extract min value " << min << endl;
        }
        else if (option == 5) {
            int key;
            cout << "Enter the index to delete " << endl;
            cin >> key;
            m.deleteKey(key);
        }
        else if (option == 6) {
            cout << "Below is the sorted array\n" << endl;
            m.sort();
        }
        else if (option == 7) {
            system("cls");
        } 
    } while (option != 0);
    return 0;
}