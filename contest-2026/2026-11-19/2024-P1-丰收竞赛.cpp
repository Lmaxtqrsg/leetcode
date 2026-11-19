// 2024 计算机挑战赛 C++ 编程题 1：农作物丰收竞赛
// 输入：第一行 N；接下来 N 行是各农民当前的累积得分
// 输出：有多少位农民仍「有可能」夺冠
// 状态：看题解 AC
//
// 题意关键：「有多少人有可能夺冠」= 对每个人独立判断「是否存在一种赛果让他赢」。
//   不是「有没有一种赛果让很多人同时夺冠」。
//   例：3 个 50 分 → 答案 3（虽然每次比赛只有一人实际夺冠）
//
// 卡点归因：
//   ②建模  门槛用成了「最大基数」或「最大基数 + 1」
//          最大基数的人是「基数最大 + 奖励最少」，不一定是最终分最高的人
//          相邻两项 f(i)=a[i]+(N-i) 的差 = (a[i+1]-a[i]) - 1，
//          基数一"平"下来 f 就下降，最高点跑到中间去
//
// 模型：
//   1) 排序
//   2) 逆序配对（大奖励配小基数）后，第 i 人的分数 = a[i] + (N-i)
//   3) mx = 这些分数里的最大值 —— 对手最狠能到几分
//   4) 候选人拿满分奖励 N：a[i]+N >= mx 就能赢，从大到小扫，一断就 break

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<long long> v(N);
    for (int i = 0; i < N; i++) cin >> v[i];

    sort(v.begin(), v.end());

    // 门槛：逆序配对下全场最高分
    long long mx = 0;
    for (int i = 0; i < N; i++)
        mx = max(mx, v[i] + N - i);

    // 从大到小扫，一旦不行后面更小的都不行
    int ans = 0;
    for (int i = N - 1; i >= 0; i--) {
        if (v[i] + N >= mx) ans++;
        else break;
    }

    cout << ans << "\n";
    return 0;
}

// 自测：
//   3 / 8 10 9                → 3
//   6 / 60 55 50 30 20 10     → 2
//   3 / 7 8 10                → 2   （最大基数+1 会错给成 3）
//   5 / 3 5 5 5 7             → 4   （最大基数+1 会错给成 5）
