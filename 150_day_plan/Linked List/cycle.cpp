#include "iostream"
#include <unordered_set>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

void insert(struct ListNode * head) {
    static struct ListNode * root;
    if (!root) {
        root = head;
        return;
    }
    while (root->next) {
        root = root->next;
    }
    root->next = head;
}

void display(struct ListNode * head) {
    while (head) {
        cout << head->val << ", ";
        head = head->next;
    }
}

bool hasCycle(ListNode *head) {
    struct ListNode * temp = head;
    unordered_set<ListNode *> s;
    while (temp) {
        if (s.find(temp) != s.end()) {
            return true;
        }
        s.insert(temp);
        temp = temp->next;
        if (!temp) {
            return false;
        }
    }
}

int main() {
    ListNode n1(10), n2(20), n3(30), n4(40);
    insert(&n1);
    insert(&n2);
    insert(&n3);
    insert(&n4);
    display(&n1);
    n4.next = &n2;
    cout << hasCycle(&n1);
    return 0;
}