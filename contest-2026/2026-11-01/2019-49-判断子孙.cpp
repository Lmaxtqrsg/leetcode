// 2019 计算机挑战赛 C++ 编程题 49：判断 y 是否为 x 的子孙
// 输入：第一行先序 / 第二行中序 / 第三行 x y（无 n）
// 输出：是子孙输出 1；不是或 x/y 不在树上输出 -1
// 约定：x == y 时不算自己的子孙，输出 -1
// 状态：独立 AC（2026-11-01）
//
// 卡点归因：
//   1. ss1(line1) 用了第一行，且写进 pre[] → in[] 全 0，build 找不到根
//   2. new 注释掉了却保留 p->lchild 赋值 → 野指针写入，直接崩
//   教训：注释掉创建时，顺手删掉所有依赖它的行

#include <iostream>
#include <sstream>
using namespace std;

typedef struct BiNode {
    int data;
    struct BiNode* lchild;
    struct BiNode* rchild;
} BiNode, *BiTree;

int pre[1005], in[1005];

// 找到值为 num 的结点，返回指针；找不到返回 NULL
BiTree find(BiTree T, int num) {
    if (T == NULL) return NULL;
    if (T->data == num) return T;
    BiTree p = find(T->lchild, num);
    if (p) return p;                    // 左子树找到了就直接返回
    return find(T->rchild, num);
}

BiTree build(int pl, int pr, int il, int ir) {
    if (pl > pr) return NULL;
    int root = pre[pl];
    int k = il;
    while (in[k] != root) k++;
    int len = k - il;
    BiNode* p = new BiNode;
    p->data = root;
    p->lchild = p->rchild = NULL;
    p->lchild = build(pl + 1,       pl + len, il,    k - 1);
    p->rchild = build(pl + len + 1, pr,       k + 1, ir);
    return p;
}

int main() {
    string line1, line2;
    getline(cin, line1);
    stringstream ss(line1);
    int v, np = 0;
    while (ss >> v) pre[++np] = v;

    getline(cin, line2);
    stringstream ss1(line2);
    int ip = 0;
    while (ss1 >> v) in[++ip] = v;

    int x, y;
    cin >> x >> y;

    if (x == y) { cout << -1 << "\n"; return 0; }   // 自己不算自己的子孙

    BiTree T = build(1, np, 1, ip);
    BiNode* p = find(T, x);
    BiNode* q = find(T, y);
    if (p == NULL || q == NULL) { cout << -1 << "\n"; return 0; }

    BiNode* u = find(p, y);              // 因为 x != y，从 p 开始找等价于在子树里找
    cout << (u ? 1 : -1) << "\n";
    return 0;
}