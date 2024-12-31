/*
Keywords:
    node,
    head
*/

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

class CircularLinkedList {
    public:
        Node * head;
        CircularLinkedList(Node * node) {
            head = node;
            head->next = head;
        }
        void append(Node * node) {
            Node * temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            node->next = head; // Pointing the new node's next to head
            temp->next = node; // Pointing the current node that's pointing to head to newly appended node.
        }
        void display() {
            Node * temp = head;
            while (temp->next != head) {
                (temp==head) ? cout << temp->data << "(Head) -->" : cout<< temp-> data << "-->";
                temp = temp->next;
            }
            cout <<temp-> data << "--> Head";
        }
};

int main() {
    Node n1(1, 10), n2(2, 20), n3(3, 30), n4(4, 40), n5(5, 50);
    CircularLinkedList c1(&n1);
    c1.append(&n2);
    c1.append(&n3);
    c1.append(&n4);
    c1.append(&n5);
    c1.display();
    return 0;
}