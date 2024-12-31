#include "iostream"

using namespace std;

class Node {
    public:
        int height;
        int data;
        Node * left;
        Node * right;

        Node(int data) {
            this->height = 1;
            this->data = data;
            this->left = NULL;
            this->right = NULL;
        }
};

class AVL {
    public:

        int height(Node * node) {
            if (node == NULL) {
                return 0;
            }
            return node->height;
        }

        int getBalance(Node * node) {
            return height(node->left) - height(node->right);
        }

        Node * rightRotate(Node * y) {
            Node * x = y->left;
            Node * t = x->right;

            x->right = y;
            y->left = t;

            x->height = 1 + max(height(x->left), height(x->right));
            y->height = 1 + max(height(y->left), height(y->right));

            return x;
        }

        Node * leftRotate(Node * y) {
            Node * x = y->right;
            Node * t = x->left;

            x->left = y;
            y->right = t;

            x->height = 1 + max(height(x->left), height(x->right));
            y->height = 1 + max(height(y->left), height(y->right));

            return x;
        }

        Node * insert(Node * node, int data) {

            if (node == NULL) {
                return new Node(data)
            }

            if (data < node->data) {
                node->left = insert(node->left, data);
            }

            else if (data > node->data) {
                node->right = insert(node->right, data);
            }

            else {
                return node;
            }


        }
}

int main() {
    return 0;
}