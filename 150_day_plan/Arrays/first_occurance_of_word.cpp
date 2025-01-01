#include "iostream"
#include <vector>

using namespace std;

int main() {
    string haystack = "a", needle = "a";
    if (needle.size() > haystack.size())
        return -1;

    int max_size = needle.size() > 0 ? haystack.size() - needle.size() + 1: haystack.size() - needle.size();
    for (int i=0; i<max_size; i++) {
        string new_string;
        for (int j=i, k=0; k<needle.size(); j++, k++) {
            new_string.push_back(haystack[j]);
        }
        if (new_string == needle) {
            cout << "Found " << i << endl;
            return i;
        }
        new_string = "";
    }
    cout << "Could not find " << endl;
    return -1;
}