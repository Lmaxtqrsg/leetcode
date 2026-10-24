/*n 个学生，每人有语文、数学、英语三科成绩。按规则排序后，输出前 5 名的「学号 总分」： ① 总分从高到低　② 总分相同，语文从高到低　③ 都相同，学号小的在前

数据范围： n ≤ 300，每科 0~100，总分 ≤ 300。学号 = 输入顺序（第 1 个输入的学生学号是 1）。*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef struct stu {
	int ma, ch, en;
	int sum;
	int num;
}stu;
bool cmp(stu s1, stu s2) {
	if (s1.sum != s2.sum)return (s1.sum > s2.sum);
	if (s1.ch != s2.ch) return(s1.ch > s2.ch);
	return (s1.num < s2.num);
}
int main() {
	int n;
	cin >> n;
	vector<stu>v;
	for (int i = 0; i < n; i++) {
		stu s;
		cin >> s.ch >> s.ma >> s.en;
		s.sum = s.ch + s.ma + s.en;
		s.num = i + 1;
		v.push_back(s);
	}
	sort(v.begin(), v.end(), cmp);
	for (int i = 0; i < 5; i++) {
		cout << v[i].num << " " << v[i].sum << "\n";
	}
	return 0;
}输入和输出和题目给的一致