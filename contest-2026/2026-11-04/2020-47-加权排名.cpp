// 2020 计算机挑战赛 C++ 操作题 47：加权总分排名
// 输入：第一行 n（3<=n<=500）；接下来 n 行：学号 物理 化学 生物（每科 0~100）
// 输出：前 3 名，每行 "学号 加权总分"，保留 1 位小数
// 规则：加权分 = 物理*40% + 化学*35% + 生物*25%，四舍五入到小数点后 1 位
//       总分相同 → 物理 → 化学 → 生物 优先级递减
// 状态：看题解 AC（cmp 分层写法、四舍五入的整数缩放均由提示修正）
// 复杂度：O(n log n)
//
// 卡点归因：
//   ②建模  四舍五入 → 想不到「整数缩放」，第一反应是 double + printf("%.1f")
//   ③语法  cmp 只写了 a.sum > b.sum 分支，漏了 a.sum < b.sum → 双向都返回 true
//   ③语法  cmp 末尾漏 return；且写成 a.num > b.sum，拿学号比总分
//   ③语法  return a.sum 返回 int 当 bool
//   ③语法  setprecision 写在被格式化的值后面，且 int 忘了转 (double)，两个错叠加
//   ③语法  double % int 编译不过
//
// 关键：全程不碰浮点
//   w = ph*40 + ch*35 + bi*25      加权分 ×100，整数
//   k = (w + 5) / 10               加权分 ×10，四舍五入（仅对非负成立）
//   输出用 k/10 和 k%10 手工拼小数点，避免任何舍入分歧
//
// cmp 三原则：
//   ① 每层用 != 判断「能不能在这里分出胜负」
//   ② 能分就把 > / < 说清楚，不能只写 > 分支
//   ③ 最后一层不再判断，直接 return 比较表达式（保证每条路径都有返回值）

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct stu {
    int num;
    int ph, ch, bi;
    int sum;        // 加权分 ×10，四舍五入后的整数
};

bool cmp(const stu &a, const stu &b) {
    if (a.sum != b.sum) return a.sum > b.sum;       // 总分降序
    if (a.ph  != b.ph)  return a.ph  > b.ph;        // 物理优先
    if (a.ch  != b.ch)  return a.ch  > b.ch;        // 化学
    return a.bi > b.bi;                             // 生物（最后一层不再判断）
}

int main() {
    int n;
    if (!(cin >> n)) return 0;

    vector<stu> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].num >> v[i].ph >> v[i].ch >> v[i].bi;
        v[i].sum = (v[i].ph * 40 + v[i].ch * 35 + v[i].bi * 25 + 5) / 10;
    }

    sort(v.begin(), v.end(), cmp);

    for (int i = 0; i < n && i < 3; i++) {
        cout << v[i].num << " " << v[i].sum / 10 << "." << v[i].sum % 10 << "\n";
    }

    return 0;
}

// 样例：5 个学生，前 3 名应输出
//   20200002 90.9 / 20200001 85.9 / 20200003 84.0
// 边界自测（0.25 / 0.35 / 1.05 三个 .x5 值）：
//   0 1 0 → 0.4 ； 0 0 1 → 0.3 ； 0 3 0 → 1.1 ； 0 2 0 → 0.7
//   用浮点 printf("%.1f") 会得到 0.3 / 0.2 / 1.1 / 0.7，错两个。
