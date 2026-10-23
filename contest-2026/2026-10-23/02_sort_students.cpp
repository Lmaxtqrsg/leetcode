// 题目：读入 n 个学生的姓名和分数，按分数从高到低输出姓名；
//       分数相同的，按姓名字典序从小到大输出。每人一行。
// 数据范围：1 <= n <= 1e5，0 <= 分数 <= 100，姓名不含空格
// 状态：独立 AC（2026-10-23）
// 复杂度：时间 O(n log n)，空间 O(n)
//
// 踩过的坑：
//   1. 曾经把 cmp 写进 struct        -> cmp 是独立的函数，struct 只放数据
//   2. 曾经不会写签名 bool cmp(struct) -> 直接写 bool cmp(stu a, stu b)，不用 struct 关键字
//   3. 曾经同分比较方向写反（用 >）   -> 题目要"从小到大"就用 <
//   4. 曾经数组开 stu S[20]          -> 按数据范围开 n_max + 5
//   5. 曾经读入顺序按记忆写成"分数 姓名" -> 严格按题面"姓名 分数"
//   6. 曾经把 4MB 数组开在 main 里   -> 栈溢出，一进 main 就崩，现象是"没法输入"

#include <iostream>
#include <string>
#include <algorithm>                // sort 在这里
using namespace std;

struct stu {
    int score;
    string name;
};

// cmp 返回 true 表示 a 应排在 b 前面
bool cmp(stu a, stu b) {
    if (a.score != b.score) return a.score > b.score;   // 分数不同：降序
    return a.name < b.name;                             // 分数相同：姓名升序
}

stu S[100005];                      // 全局变量：不受 1MB 栈限制，放得下 1e5 个

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> S[i].name >> S[i].score;   // 注意顺序：先姓名，后分数
    }

    sort(S, S + n, cmp);            // 区间左闭右开：S[0] 到 S[n-1]

    for (int i = 0; i < n; i++) {
        cout << S[i].name << "\n";  // 只输出姓名，不带分数；用 "\n" 比 endl 快
    }

    return 0;
}
