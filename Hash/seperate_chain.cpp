#include "iostream"
#include <vector>
#include <algorithm>

using namespace std;

class Hash {
    public:
        vector<vector<int>> hash_table;
        int Bucket;

        Hash(int bucket) : Bucket(bucket) {
            this->hash_table.resize(this->Bucket);
        }

        int hashFunction(int key) {
            return key % this->Bucket;
        }

        void insertHashEntry(int data) {
            int index = this->hashFunction(data);
            hash_table[index].push_back(data);
        }

        void deleteHashEntry(int data) {
            int index = this->hashFunction(data);
            auto it = find(hash_table[index].begin(), hash_table[index].end(), data);
            if (it != hash_table[index].end()) {
                hash_table[index].erase(it);
            }
        }

        void display() {
            for (int index=0; index<this->Bucket; index++) {
                cout << '|' << index << '|';
                for (auto it=hash_table[index].begin(); it != hash_table[index].end(); it++) {
                    cout << *it << "->";
                }
                cout << " " << "__" << " " << endl;
            }
        }
};

int main() {
    Hash h(5);
    h.insertHashEntry(5);
    h.insertHashEntry(10);
    h.insertHashEntry(15);
    h.insertHashEntry(3);
    h.insertHashEntry(1);

    h.display();
    return 0;
}