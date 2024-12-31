#include "iostream"

using namespace std;

class Node {
    public:
        int key, data;
        Node *prev, *next;
        Node(int key, int data) {
            this->data = data;
            this->key = key;
            this->prev = NULL;
            this->next = NULL;
        }
};

class DoubleLinkedList {
    public:
        Node * head;
        DoubleLinkedList(Node * node) {
            head = node;
        }

        void append(Node * node) {
            Node * temp = head;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            node->prev = temp;
            temp->next = node;
        }

        void prepend(Node * node) {
            node->next = head;
            head = node;
            // Telling older head's previous node pointer to point to new head;
            head->next->prev = head;
        }

        void display(bool reversed=false) {
            Node * temp = head;
            if (reversed) {
                cout << "\nReversed = \"True\"" << endl;
                // Traversing to end of the list
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                // Then start printing from the last node
                while (temp != NULL) {
                    cout << temp->data << "-->";
                    temp = temp->prev;
                }
            }
            else if(!reversed) {
                cout << "\nReversed = \"False\"" << endl;
                // Traversing to end of the list
                while (temp != NULL) {
                    cout << temp->data << "-->";
                    temp = temp->next;
                }
            }
        }
};

int main() {
    Node n1(1, 10), n2(2, 20), n3(3, 30), n4(4, 40), n5(5, 50);
    DoubleLinkedList d1(&n1);
    d1.append(&n2);
    d1.append(&n3);
    d1.append(&n4);

    d1.display();
    d1.display(true);

    d1.prepend(&n5);

    d1.display();
    d1.display(true);
    return 0;
}
