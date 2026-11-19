// 2025 计算机挑战赛 C++ 编程题 2：动物观测区域划分
// 输入：第一行 n k（2<=k<=n<=15000）；第二行 n 个坐标（升序、无重复、长整数）
// 输出：划分成 k 段后，各段 (max-min) 之和的最大值
// 状态：AC（与 2024-P2 修复公路是同一模型的对偶）
//
// 卡点归因：
//   ②建模  用 vector<int> v(n) 后只在 m<2000 时才写 v[i]，被剔除的位置留着 0，
//          而 v.size() 仍是 n，导致 0 被当成观测点（间隔算出 -43）
//   ③语法  for (i < k-2) 少切一刀，应为 k-1
//
// 模型：
//   先剔除坐标 >= 2000 的点；算「一整段」总长 last-first；
//   切成 k 段 = 去掉 k-1 个间隔；求最大 → 去掉最小的 k-1 个间隔。
//   对照 2024-P2（求最小）：代价带 +1、去掉最大的 k-1 个间隔。

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    // 剔除坐标 >= 2000 的点 —— 必须用 push_back，不能预定长度
    vector<long long> v;
    for (int i = 0; i < n; i++) {
        long long m;
        cin >> m;
        if (m < 2000) v.push_back(m);
    }

    int num = (int)v.size();
    if (num == 0) { cout << 0 << "\n"; return 0; }

    long long total = v[num - 1] - v[0];      // 一整段的总长
    if (k == 1) { cout << total << "\n"; return 0; }

    vector<long long> gaps;
    for (int i = 0; i + 1 < num; i++)
        gaps.push_back(v[i + 1] - v[i]);

    sort(gaps.begin(), gaps.end());            // 间隔升序
    int cut = min(k - 1, (int)gaps.size());
    for (int i = 0; i < cut; i++)              // 去掉最小的 k-1 个
        total -= gaps[i];

    cout << total << "\n";
    return 0;
}

// 样例：20 4 / 3 4 6 8 14 15 16 17 21 25 26 27 30 31 40 41 42 43 2100 2300 → 37
