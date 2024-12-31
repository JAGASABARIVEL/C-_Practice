#include "iostream"

using namespace std;

 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

void displayTotal(ListNode * total) {
    while (total) {
        cout << total->val;
        total = total->next;
    }
    cout << endl;
}

int main() {
    ListNode l1_6(9), l1_5(9, &l1_6), l1_4(9, &l1_5), l1_3(9, &l1_4), l1_2(9, &l1_3), l1_1(9, &l1_2), l1(9, &l1_1);
    ListNode l2_3(9), l2_2(9, &l2_3), l2_1(9, &l2_2), l2(9, &l2_1);

    displayTotal(&l1), displayTotal(&l2);

    ListNode * templ1 = &l1, *templ2 = &l2, *total = NULL;
    int datal1, datal2;
    int carry = 0;
    while (templ1 || templ2) {
        datal1 =0, datal2 = 0;
        if (templ1) {
            datal1 = templ1->val;
            templ1 = templ1->next;
        }
        if (templ2) {
            datal2 = templ2->val;
            templ2 = templ2->next;
        }
        int sum = datal1 + datal2 + carry;
        carry = 0;
        if (sum >= 10) {
            carry = sum / 10;
            sum = sum % 10;
        }
        
        ListNode * tempnew = new ListNode(sum);
        if (!total) {
            total = tempnew;
            continue;
        }
        ListNode * ttemp = total;
        while (ttemp->next) {
            ttemp = ttemp->next;
        }
        ttemp->next = tempnew;
    }

    if (carry) {
        ListNode * tempnew = new ListNode(carry);
        ListNode * ttemp = total;
        while (ttemp->next) {
            ttemp = ttemp->next;
        }
        ttemp->next = tempnew;
    }

    displayTotal(total);


    return 0;
}