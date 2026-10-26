// 2026-10-26 课内同步：二叉树前中后序递归遍历
// 输入：n，接下来 n 行是结点 i 的左、右儿子编号（0 表示空），根固定为 1
// 输出：前序 / 中序 / 后序，各一行
// 要点：三种遍历只差 cout 的位置（前序在递归前，中序在中间，后序在递归后）

#include <iostream>
using namespace std;

const int N = 1005;
int lc[N], rc[N], n;

void pre(int u) {                     // 根 左 右
    if (u == 0) return;
    cout << u << " ";
    pre(lc[u]);
    pre(rc[u]);
}
void in(int u) {                      // 左 根 右
    if (u == 0) return;
    in(lc[u]);
    cout << u << " ";
    in(rc[u]);
}
void post(int u) {                    // 左 右 根
    if (u == 0) return;
    post(lc[u]);
    post(rc[u]);
    cout << u << " ";
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> lc[i] >> rc[i];
    pre(1);  cout << "\n";
    in(1);   cout << "\n";
    post(1); cout << "\n";
    return 0;
}