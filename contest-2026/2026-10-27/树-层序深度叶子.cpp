// 2026-10-27 二叉树：层序遍历 + 深度 + 叶子数（数组版）
// 输入：n，接下来 n 行是结点 i 的左右儿子编号（0 表示空），根为 1
// 输出：层序 / 深度 / 叶子数
// 复杂度：三个函数都是 O(n)
// 状态：独立 AC（2026-10-27）
//
// 踩过的坑：
//   1. 队列里放的是"结点编号"，不是 root++
//   2. q.pop() 不返回被删元素，必须先 q.front() 存下来
//   3. 入队前要判 if (lc[u])，否则会把 0 塞进去
//   4. depth 空结点返回 0 而不是 1

#include <iostream>
#include <queue>        // queue
#include <algorithm>    // max
using namespace std;

const int N = 1005;
int lc[N], rc[N], n;

// 层序遍历：BFS + 队列
void bfs(int root) {
    queue<int> q;
    q.push(root);                 // 队列里放"结点编号"
    while (!q.empty()) {
        int u = q.front();        // 看队首
        q.pop();                  // 弹出队首
        cout << u << " ";         // 访问
        if (lc[u]) q.push(lc[u]); // 左孩子入队
        if (rc[u]) q.push(rc[u]); // 右孩子入队
    }
}

// 深度 = 1 + 左右子树里较深的那个
int depth(int u) {
    if (u == 0) return 0;
    return 1 + max(depth(lc[u]), depth(rc[u]));
}

// 叶子 = 左右孩子都没有
int leaves(int u) {
    if (u == 0) return 0;
    if (lc[u] == 0 && rc[u] == 0) return 1;
    return leaves(lc[u]) + leaves(rc[u]);
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> lc[i] >> rc[i];
    bfs(1);              cout << "\n";
    cout << depth(1) << "\n";
    cout << leaves(1) << "\n";
    return 0;
}