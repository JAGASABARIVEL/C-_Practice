#include "iostream"
#include <vector>

using namespace std;

struct ListNode {
   int val;
   ListNode *next;
   ListNode() : val(0), next(nullptr) {}
   ListNode(int x) : val(x), next(nullptr) {}
   ListNode(int x, ListNode *next) : val(x), next(next) {}
};

int main() {

    ListNode n5(5, NULL), n4(3, &n5);//, n3(3, &n4), n2(2, &n3), n1(1, &n2);
    ListNode * head = &n4;int left = 1, right = 2;

    if (head == nullptr) {
        //return nullptr;
    }
    vector<ListNode *> cache;
    // to simulate the position without starting from index :)
    cache.push_back(nullptr);
    ListNode * temp = head;
    while (temp != nullptr) {
        cache.push_back(temp);
        temp = temp->next;
    }

    for (int i=right; i>left; i--) {
        cache[i]->next = cache[i - 1];
    }

    ListNode * cache_temp;
    if (left > 1) {
        cache[left - 1]->next = cache[right];
        cache_temp = cache[1];
    }
    else {
        cache_temp = cache[right];
    }

    if (right < cache.size() - 1) {
        cache[left]->next = cache[right + 1];
    }
    else {
        cache[left]->next = nullptr;
    }

    
    
    // Display
    while (cache_temp != nullptr) {
        cout << cache_temp->val << ", ";
        cache_temp = cache_temp->next;
    }

    return 0;
}