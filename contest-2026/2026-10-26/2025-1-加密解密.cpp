// 2025 计算机挑战赛 C++ 编程题 1：加密解密
// 状态：独立 AC（2026-10-26）
// 思路：加密是每组向右循环移 1 位，所以解密是每组向左循环移 1 位
//      存组首 -> 后面的往前挪一格 -> 组首放到组尾
// 边界：最后一组不足 k 个，保持原样；k = 1 时循环不执行，自动正确
// 复杂度：时间 O(N)，空间 O(1)

#include <iostream>
using namespace std;

int a[1000005];                      // 大数组开全局，避免栈溢出

int main() {
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) cin >> a[i];

    int k;
    cin >> k;

    int groups = N / k;              // 完整组数（不是 N - k）
    for (int g = 0; g < groups; g++) {
        int start = g * k;
        int first = a[start];        // 空1：存组首
        for (int j = start; j < start + k - 1; j++)
            a[j] = a[j + 1];         // 空2：后面往前挪一格（起点必须是 start）
        a[start + k - 1] = first;    // 空3：组首丢到组尾
    }

    for (int i = 0; i < N; i++) {
        if (i) cout << " ";
        cout << a[i];
    }
    cout << "\n";
    return 0;
}