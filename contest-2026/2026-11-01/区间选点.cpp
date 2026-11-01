// 区间选点（经典贪心，与 2025#2 同族但不是原题）
// 题：n 个闭区间，选最少的点，使每个区间至少含一个点
// 输入：n，然后 n 行 l r
// 输出：最少点数
// 状态：独立 AC（2026-11-01）——贪心策略在引导下推出，扫描骨架给过 2 个空
//
// 策略：按右端点升序排序；每次取当前区间的右端点作为点，
//       跳过所有"左端点 <= 该点"的区间（因为排序后它们的右端点都 >= 该点）

#include <iostream>
#include <algorithm>
using namespace std;

struct seg { int l, r; };
seg a[100005];                      // n <= 1e5，开全局

bool cmp(seg x, seg y) { return x.r < y.r; }   // 按右端点升序

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i].l >> a[i].r;
    sort(a, a + n, cmp);

    int i = 0, ans = 0;
    while (i < n) {
        ans++;                          // 放一个新点
        int p = a[i].r;                 // 点放在当前区间的右端点
        while (i < n && a[i].l <= p) i++;   // 跳过所有包含该点的区间
    }
    cout << ans << "\n";
    return 0;
}