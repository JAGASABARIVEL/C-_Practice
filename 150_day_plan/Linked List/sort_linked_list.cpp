#include "iostream"

using namespace std;

 struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode * merge(ListNode * left, ListNode * right) {
    ListNode * dummy = new ListNode(0);
    ListNode * sort_temp = dummy;
    while (left != NULL && right != NULL) {
        if (left->val <= right->val) {
            sort_temp->next = left;
            left = left->next;
        }
        else {
            sort_temp->next = right;
            right = right->next;
        }
        sort_temp = sort_temp->next;
    }
    sort_temp->next = (left != NULL) ? left : right;
    return dummy->next;
}

ListNode * sort(ListNode * list) {
    if (list == nullptr || list->next == nullptr) {
        return list;
    }
    ListNode *fast = list, *slow = list, *prev;
    while (fast != nullptr && fast->next != nullptr) {
        prev = slow;
        slow=slow->next;
        fast=fast->next->next;
    }
    prev->next = nullptr;

    ListNode * left = sort(list);
    ListNode * right = sort(slow);
    return merge(left, right);
}


void printList(ListNode * head) {
    while (head != NULL) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    ListNode l1(2, NULL);
    ListNode l4(1, NULL);
    ListNode * list1 = &l1, * list2 = &l4;

    

    //printList(head);
    sort(head);
    printList(head);

    return 0;
}