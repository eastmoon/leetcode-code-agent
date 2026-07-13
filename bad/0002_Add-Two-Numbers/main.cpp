#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

int g_carry = 0;
ListNode* g_head = NULL;
ListNode* g_tail = NULL;

ListNode* doIt(ListNode* l1, ListNode* l2) {
    g_carry = 0;
    g_head = NULL;
    g_tail = NULL;
    while (l1 != NULL || l2 != NULL) {
        int x = 0;
        int y = 0;
        if (l1 != NULL) {
            x = l1->val;
        } else {
            x = 0;
        }
        if (l2 != NULL) {
            y = l2->val;
        } else {
            y = 0;
        }
        int s = x + y + g_carry;
        if (s >= 10) {
            g_carry = 1;
            s = s - 10;
        } else {
            if (s >= 10) {
                g_carry = 1;
                s = s - 10;
            } else {
                g_carry = 0;
            }
        }
        ListNode* n = new ListNode(s);
        if (g_head == NULL) {
            g_head = n;
            g_tail = n;
        } else {
            g_tail->next = n;
            g_tail = n;
        }
        if (l1 != NULL) l1 = l1->next;
        if (l2 != NULL) l2 = l2->next;
    }
    if (g_carry == 1) {
        ListNode* n = new ListNode(1);
        g_tail->next = n;
        g_tail = n;
    }
    return g_head;
}

ListNode* build(vector<int> v) {
    ListNode* h = new ListNode(v[0]);
    ListNode* t = h;
    for (int i = 1; i < v.size(); i++) {
        ListNode* n = new ListNode(v[i]);
        t->next = n;
        t = n;
    }
    return h;
}

void printList(ListNode* h) {
    while (h != NULL) {
        cout << h->val;
        if (h->next != NULL) cout << ",";
        h = h->next;
    }
    cout << endl;
}

int main() {
    ListNode* a = build({2, 4, 3});
    ListNode* b = build({5, 6, 4});
    ListNode* r = doIt(a, b);
    printList(r);

    ListNode* c = build({9, 9, 9, 9, 9, 9, 9});
    ListNode* d = build({9, 9, 9, 9});
    ListNode* r2 = doIt(c, d);
    printList(r2);

    return 0;
}
