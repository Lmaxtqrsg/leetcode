// 2026-10-27 二叉树：层序遍历 + 深度 + 叶子数（指针版）
// 与数组版功能完全相同，区别只在"怎么找到孩子"：指针靠地址，数组靠下标
//
// 注意三点：
//   1. 必须先 new 出所有结点，再连边（连边时孩子必须已存在）
//   2. new 出来的内存不会自动回收，竞赛里不用管
//   3. 野指针：没 new 就用 -> 会崩

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct Node {
    int id;              // 结点编号
    Node *l, *r;         // 左右孩子指针
    Node(int i) : id(i), l(NULL), r(NULL) {}   // 建结点时把 l、r 置空
};

Node* nd[1005];          // nd[i] 指向"编号 i"的结点

void bfs(Node* root) {
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* u = q.front();
        q.pop();
        cout << u->id << " ";
        if (u->l) q.push(u->l);
        if (u->r) q.push(u->r);
    }
}

int depth(Node* u) {
    if (!u) return 0;
    return 1 + max(depth(u->l), depth(u->r));
}

int leaves(Node* u) {
    if (!u) return 0;
    if (!u->l && !u->r) return 1;
    return leaves(u->l) + leaves(u->r);
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) nd[i] = new Node(i);
    for (int i = 1; i <= n; i++) {
        int l, r;
        cin >> l >> r;
        if (l) nd[i]->l = nd[l];
        if (r) nd[i]->r = nd[r];
    }
    bfs(nd[1]);            cout << "\n";
    cout << depth(nd[1]) << "\n";
    cout << leaves(nd[1]) << "\n";
    return 0;
}