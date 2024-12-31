#include "iostream"
#include <vector>

using namespace std;

class Hash {

    public:
        vector<vector<int>> hash_table;
        int bucket_size;

    Hash(int bucket) : bucket_size(bucket) {
        hash_table.resize(this->bucket_size);
    }

    int hash_function(int key) {
        return key % this->bucket_size;
    }

    void insert_hash_entry(int data) {
        int key = hash_function(data);
        hash_table[key].push_back(data);
    }

    bool get_hash_entry(int data) {
        int key = hash_function(data);
        if (!hash_table[key].size()) {
            return false;
        }
        hash_table[key].pop_back();
        return true;
    }
};

int main() {
    string ransom_note = "aa";
    string magazine = "abc";
    int magazine_size = 26;
    bool can_it_be_made = true;
    Hash * table = new Hash(magazine_size);

    // Insert into hashtable
    for (int i=0; i < magazine.size(); i++) {
        table->insert_hash_entry(magazine[i]);
    }

    // Check if ransom note can be made
    for (i=0; i < ransom_note.size(); i++) {
        if (!table->get_hash_entry(ransom_note[i])) {
            can_it_be_made = false;
            break;
        }
    }
    delete table;
    return can_it_be_made;
}