#include "iostream"
#include <vector>
#include <unordered_map>

using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node* random;
    Node(int _val) : val(_val), next(NULL), random(NULL) {}
    Node(int _val, Node* _next) : val(_val), next(_next), random(NULL) {}
};

int main() {

    Node n5(1, NULL), n4(10, &n5), n3(11, &n4), n2(13, &n3), n1(7, &n2);
    Node * head = &n1;

    vector<Node *> nodes;
    unordered_map<int, int> mapping_index;
    Node * temp = head;
    Node * copy = nullptr;

    while (temp != NULL) {
        Node * cache = new Node(temp->val);
        nodes.push_back(cache);
        if (copy == nullptr) {
            copy = cache;
            temp = temp->next;
            continue;
        }
        Node * copy_temp = copy;
        while (copy_temp->next != nullptr) {
            copy_temp = copy_temp->next;
        }
        copy_temp->next = cache;
        temp = temp->next;
    }

    temp = head;
    int i = 0;
    while (temp != nullptr) {
        if (temp->random == nullptr) {
            mapping_index[i] = -1;
            i += 1;
            temp = temp->next;
            continue;
        }
        Node * temp_temp = head;
        int j=0;
        while (temp_temp != nullptr) {
            if (temp->random == temp_temp) {
                mapping_index[i] = j;
                break;
            }
            temp_temp = temp_temp->next;
            j += 1;
        }
        i += 1;
        temp = temp->next;
    }

    for (auto map_index : mapping_index) {
        if (map_index.second == -1) {
            nodes[map_index.first]->random = nullptr;
            continue;
        }
        nodes[map_index.first]->random = nodes[map_index.second];
    }
    return 0;
}