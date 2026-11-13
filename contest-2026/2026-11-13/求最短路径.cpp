#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		vector<bool>has(9, false);
		for (int i = 0; i < n; i++) {
			int x;
			cin >> x;
			has[x] = true;
		}
		vector<int>v;
		for (int i = 1; i <= 8; i++) {
			if (has[i]) v.push_back(i);
		}
		if (v.size() <= 1) {
			cout << "0" << "\n";
			continue;
		}
		int maxgap = v.front() + 8 - v.back();
		for (int i = 1; i < (int)v.size(); i++) {
			maxgap = max(maxgap, v[i] - v[i - 1]);
		}
		cout << 8 - maxgap << "\n";
	}
	return 0;
}
