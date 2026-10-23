// 题目：读入 n 个整数，输出三行 —— 和 / 最大值 / 平均值（保留两位小数）
// 数据范围：1 <= n <= 100，|a_i| <= 1e9  =>  和最大 100 * 1e9 = 1e11，必须 long long
// 状态：看题解 AC（2026-10-23）
// 复杂度：时间 O(n)，空间 O(1)
//
// 踩过的坑：
//   1. 曾经把"n 个数"硬编码成 3 个数        -> n 是变量就必须循环
//   2. 曾经用 int 存 sum，1e11 溢出          -> long long
//   3. 曾经写 sum / num，整数除法截断        -> (double)sum / num
//   4. 曾经把 mx 定义在循环里 / 每轮重置 mx  -> 循环外定义一次，只更新不覆盖
//   5. 曾经漏掉 cin >> n 和 mx 的输出        -> 提交前数一遍输出行数

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int num;
    cin >> num;                         // 先读个数，必须在循环之前

    long long sum = 0;                  // 和最大 1e11，int 装不下
    int mx = -2100000000;               // 初值要小于数据下界 -1e9

    for (int i = 0; i < num; i++) {
        int x;
        cin >> x;
        sum += x;                       // 累加
        if (mx < x) mx = x;             // 只更新，绝不无条件赋值
    }

    cout << sum << "\n";                // 第一行：和
    cout << mx << "\n";                 // 第二行：最大值
    cout << fixed << setprecision(2)    // 固定小数点后两位
         << (double)sum / num << "\n";  // 第三行：先转 double 再除，否则截断

    return 0;
}
