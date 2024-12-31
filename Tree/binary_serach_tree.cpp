#include "iostream"

using namespace std;

class Node {
    public:
        int data;
        Node * left;
        Node * right;

        Node(int data) {
            this->data = data;
            this->left = NULL;
            this->right = NULL;
        }
};

class BinarySerachTree {
    
    public:
        Node * root = NULL;

        BinarySerachTree(Node * node) {
            root = node;
        }

        bool add(Node * node) {
            Node * temp = root;

            while (true) {

                if (node->data < temp->data) {
                    if (!temp->left) {
                        temp->left = node;
                        return true;
                    }
                    temp = temp->left;
                }

                else if(node->data > temp->data) {
                    if (!temp->right) {
                        temp->right = node;
                        return true;
                    }
                    temp = temp->right;
                }
                else {
                    return false;
                }
            }
        }

        void display(Node * node) {
            if (!node) {
                return;
            }
            display(node->left);
            cout << node->data << " --> ";
            display(node->right);
        }
};

int main() {
    Node n1(10), n2(5), n3(20);
    BinarySerachTree bst(&n1);
    bst.add(&n2);
    bst.add(&n3);
    bst.display(bst.root);

    return 0;
}