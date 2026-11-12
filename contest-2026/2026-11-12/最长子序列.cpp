#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main() {
	vector<int>p;
	int n;
	cin >> n;
	int x;
	for (int i = 0; i < n; i++) {
		cin >> x;
		if (x < 100)
			p.push_back(x);
	}
	int m = (int)p.size();
	if (m == 0) {
		cout << "0" << endl; return 0;
	}
	vector<int>up(m, 1), down(m, 1);
	for (int i = 1; i < m; i++) {
		for (int j = 0; j < i; j++) {
			if (p[i] > p[j])
				up[i] = max(up[i], down[j] + 1);
			else if (p[i] < p[j]) {
				down[i] = max(down[i], up[j] + 1);
			}
		}
	}
	int ans = 1;
	for (int i = 0; i < m; i++) {
		ans = max(ans, max(up[i], down[i]));
	}
	for (int i = 0; i < m; i++) {
		cout << up[i] << " " << endl;
	}
	for (int i = 0; i < m; i++) {
		cout << down[i] << " " << endl;
	}
	cout << ans << "\n";
	return 0;
}