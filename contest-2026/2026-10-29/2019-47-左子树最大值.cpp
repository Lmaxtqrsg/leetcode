// 2019 计算机挑战赛 C++ 编程题 47：求 x 的左子树中的最大值
// 输入：第一行先序序列 / 第二行中序序列 / 第三行整数 x（无 n）
// 输出：x 左子树最大值；左子树为空输出 x 本身；x 不在树上输出 -1
// 状态：看题解 AC（build 区间 + find/maxOf 分解由提示给出）
//
// 卡点归因：
//   build 的 4 个区间端点想不出来（建模）
//   findmax(T) 写成传自己 → 死递归；调用处应传 p->left（语法）

#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

int pre[1005], in[1005];

typedef struct BiNode {
    int data;
    struct BiNode* left;
    struct BiNode* right;
} BiNode, *BiTree;

BiTree build(int pl, int pr, int il, int ir) {
    if (pl > pr) return NULL;
    int root = pre[pl];
    int k = il;
    while (in[k] != root) k++;
    int len = k - il;
    BiTree T = new BiNode;
    T->data  = root;
    T->left  = build(pl + 1,       pl + len, il,    k - 1);
    T->right = build(pl + len + 1, pr,       k + 1, ir);
    return T;
}

// 找到值为 x 的结点，返回它的指针；找不到返回 NULL
BiNode* locatex(BiTree T, int x) {
    if (T == NULL) return NULL;
    if (T->data == x) return T;
    BiNode* p = locatex(T->left, x);
    if (p) return p;                      // 左子树找到就直接返回
    return locatex(T->right, x);
}

// 求一棵非空子树的最大值（调用前保证 T 非空）
int findmax(BiTree T) {
    int mx = T->data;
    if (T->left)  mx = max(mx, findmax(T->left));
    if (T->right) mx = max(mx, findmax(T->right));
    return mx;
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

    int x;
    cin >> x;

    BiTree T = build(1, np, 1, ni);
    BiNode* p = locatex(T, x);

    if (p == NULL)            cout << -1 << "\n";        // x 不在树上
    else if (p->left == NULL) cout << p->data << "\n";   // 左子树为空
    else                      cout << findmax(p->left) << "\n";
    return 0;
}