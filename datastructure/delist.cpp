#include <iostream>
using namespace std;
typedef struct LNode {
    int data;
    struct LNode* next;
}LNode, * LinkList;
void Initlist(LinkList& L) {
    L = new LNode;
    L->next = nullptr;
}
void createlist(LinkList& L, int num) {
    LNode* r = L;
    for (int i = 0; i < num; i++) {
        LNode* p = new LNode;
        cin >> p->data;
        p->next = nullptr;
        r->next = p;
        r = p;
    }
}
void delist(LinkList& L, int mink, int maxk) {
    LNode* pre = L;
    LNode* p = L->next;
    while (p && p->data <= mink) {
        pre = p;
        p = p->next;
    }
    while (p && p->data < maxk) {
        LNode* r = p;
        p = p->next;
        delete r;
    }
    pre->next = p;
}
void showlist(LinkList L) {
    if (L->next == nullptr)return;
    LNode* p = L->next;
    while (p) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}
int main() {
    LinkList L;
    Initlist(L);
    int num;
    cin >> num;
    createlist(L, num);
    int mink, maxk;
    cin >> mink >> maxk;
    delist(L, mink, maxk);
    showlist(L);
    return 0;