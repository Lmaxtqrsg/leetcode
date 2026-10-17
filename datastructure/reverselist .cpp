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
void reverselist(LinkList& L) {
    LNode* p = L->next;
    L->next = nullptr;
    LNode* q = nullptr;
    while (p) {
        LNode* r = p->next;
        p->next = q;
        q = p;
        p = r;
    }
    L->next = q;
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
    reverselist(L);
    showlist(L);
