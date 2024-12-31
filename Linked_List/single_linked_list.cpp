#include "iostream"
using namespace std;

class Node {
    public:
        int key, data;
        Node * next;
        Node(int key, int data) {
            this->key = key;
            this->data = data;
            this->next = NULL;
        }
};

class SingleLinkedList {
    public:
        Node * head;
        SingleLinkedList(Node * node) {
            head = node;
        }

        void appendNode(Node * node) {
            Node * temp = head;
            while (temp->next != NULL) {
                cout << temp->data << endl;
                temp = temp->next;
            }
            cout << "temp->data " << temp->data << endl;
            temp->next = node;
            cout << "head->next " << head->next << endl;
            cout << "temp->next" << temp->next << endl;
        }

        void display() {
            Node * temp = head;
            while (temp->next != NULL) {
                cout <<  temp->data << " --> ";
                temp = temp->next;
            }
        }
};

int main() {
    Node n1(1, 10), n2(2, 20), n3(3, 30), n4(4, 40);
    SingleLinkedList s1(&n1);
    s1.appendNode(&n2);
    s1.appendNode(&n3);
    s1.appendNode(&n4);
    s1.display();
    
    return 0;
}