#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<pair<int, int>> v;
	for (int i = 0; i < n; i++) {
		int l, r;
		cin >> l >> r;
		v.push_back({ l, r });                       // 空1：往尾部加一个
	}
	sort(v.begin(), v.end());                       // 空2、空3：排序区间
	for (int i = 0; i < (int)v.size(); i++)
		cout << v[i].first << " " << v[i].second << "\n";   // 空4、空5
	return 0;
}输入 3，1 2 ，1 3 ，3 1，期望输出：1 2 1 3 3 1；实际输出：1 2 1 3 3 1