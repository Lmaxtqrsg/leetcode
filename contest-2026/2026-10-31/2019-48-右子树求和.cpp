// 2019 计算机挑战赛 C++ 编程题 48：求 x 的右子树中所有结点值的和
// 输入：第一行先序序列 / 第二行中序序列 / 第三行整数 x（注意：没有 n）
// 输出：右子树结点和；右子树为空输出 0；x 不在树上输出 -1
// 状态：独立 AC（2026-10-31，修正两处后）
//
// 卡点归因：
//   1. find 里写成 if (!p) return p;  → 条件反了，左子树找到反而不返回
//   2. main 三个分支写成并列 if       → p 为 NULL 时解引用崩溃；且 sum 在分支外输出垃圾值
//   教训：互斥分支必须 else if；每个分支自己输出，不要共用变量

#include <iostream>
#include <sstream>
using namespace std;

typedef struct BiNode {
    int data;
    struct BiNode* lchild;
    struct BiNode* rchild;
} BiNode, *BiTree;

int pre[1005], in[1005];

BiTree build(int pl, int pr, int il, int ir) {
    if (pl > pr) return NULL;
    int root = pre[pl];
    int k = il;
    while (in[k] != root) k++;              // 在中序里找根的位置
    int len = k - il;                       // 左子树结点数
    BiTree T = new BiNode;
    T->data   = root;
    T->lchild = build(pl + 1,       pl + len, il,    k - 1);
    T->rchild = build(pl + len + 1, pr,       k + 1, ir);
    return T;
}

// 找到值为 x 的结点，返回指针；找不到返回 NULL
BiTree find(BiTree T, int x) {
    if (T == NULL) return NULL;
    if (T->data == x) return T;
    BiNode* p = find(T->lchild, x);
    if (p) return p;                        // 左子树找到了就直接返回
    return find(T->rchild, x);
}

// 子树所有结点之和；空树返回 0
int Sum(BiTree T) {
    if (T == NULL) return 0;
    return T->data + Sum(T->lchild) + Sum(T->rchild);
}

int main() {
    string line1, line2;
    getline(cin, line1);                    // 读第一行：先序
    stringstream ss(line1);
    int v, np = 0;
    while (ss >> v) pre[++np] = v;

    getline(cin, line2);                    // 读第二行：中序
    stringstream ss1(line2);
    int ip = 0;
    while (ss1 >> v) in[++ip] = v;

    int x;
    cin >> x;

    BiTree T = build(1, np, 1, ip);
    BiTree p = find(T, x);

    if (p == NULL)              cout << -1 << "\n";              // x 不在树上
    else if (p->rchild == NULL) cout << 0  << "\n";              // 右子树为空
    else                        cout << Sum(p->rchild) << "\n";  // 右子树求和
    return 0;
}