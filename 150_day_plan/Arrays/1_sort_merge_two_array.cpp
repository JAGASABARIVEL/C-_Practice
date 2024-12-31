#include "iostream"
#include <vector>

using namespace std;

vector<int> merge(vector<int> left, vector<int> right) {
    int i=0, j=0, k=0;
    vector<int> result;
    while(i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            result.push_back(left[i]);
            i++;
        }
        else if (left[i] > right[j]) {
            result.push_back(right[j]);
            j++;
        }
    }

    while (i < left.size()) {
        result.push_back(left[i]);
        i++;
    }

    while (j < right.size()) {
        result.push_back(right[j]);
        j++;
    }
    return result;
}

vector<int> slice(vector<int> array, int start, int end) {
    vector<int> result;
    for (int i=start; i < end; i++){
        result.push_back(array[i]);
    }
    return result;
}

vector<int> merge_sort(vector<int> array) {
    int array_size = array.size();
    if (array_size <= 1) {
        return array;
    }
    int mid = array_size / 2;
    vector<int> left = merge_sort(slice(array, 0, mid));
    vector<int> right = merge_sort(slice(array, mid, array_size));

    return merge(left, right);
}

int main() {
    int i=0, m = 5, n = 4;
    vector<int> array1 = {4, 5, 3, 1, 2};
    vector<int> array2 = {7, 6, 7, 8};
    vector<int> array(m + n);
    for (i=0; i<m; i++) {
        array[i] =array1[i];
    }
    for (int j=0; j<n; j++) {
        array[i + j] = array2[j];
    }
    array = merge_sort(array);
    for (auto i : array) {
        cout << i << ",";
    }
}