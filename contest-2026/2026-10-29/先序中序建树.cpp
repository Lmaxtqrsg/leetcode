// 2026-10-29 由先序 + 中序序列还原二叉树，输出后序
// 输入：n / n 个先序 / n 个中序（值互不相同）
// 输出：后序，一行
// 复杂度：O(n^2)
// 状态：看题解 AC（区间切分由老师给框架）
//
// 核心三条：
//   1. 先序第一个 = 根
//   2. 中序里根的左边是左子树，右边是右子树
//   3. 左子树结点数 len = k - il，用它去切先序
//
// 自检公式：同一棵子树，pr - pl == ir - il（先序长度必须等于中序长度）

#include <iostream>
#include <sstream>
using namespace std;

int pre[1005], in[1005];

typedef struct BiNode {
    int data;
    struct BiNode* left;
    struct BiNode* right;
} BiNode, *BiTree;

BiTree build(int pl, int pr, int il, int ir) {
    if (pl > pr) return NULL;              // 空区间 → 空树

    int root = pre[pl];                    // 先序第一个是根
    int k = il;
    while (in[k] != root) k++;             // 在中序里找根

    int len = k - il;                      // 左子树结点数

    BiTree T = new BiNode;
    T->data  = root;
    T->left  = build(pl + 1,       pl + len, il,    k - 1);
    T->right = build(pl + len + 1, pr,       k + 1, ir);
    return T;
}

void postOrder(BiTree T) {
    if (T == NULL) return;
    postOrder(T->left);
    postOrder(T->right);
    cout << T->data << " ";
}

int main() {
    string line1, line2;
    getline(cin, line1);
    stringstream ss(line1);
    int v, np = 0;
    while (ss >> v) pre[++np] = v;

    getline(cin, line2);
    stringstream ss2(line2);
    int ni = 0;
    while (ss2 >> v) in[++ni] = v;

    BiTree T = build(1, np, 1, ni);
    postOrder(T);
    cout << "\n";
    return 0;
}