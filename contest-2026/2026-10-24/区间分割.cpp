#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
	int n, k;
	cin >> n >> k;
	vector<long long>v;
	long long  a;
	for (int i = 0; i < n; i++) {
		cin >> a;
		if (a < 2000) v.push_back(a);
	}
	int m = (int)v.size();
	if (m < k) {
		cout << "0" << "\n";
		return 0;
	}
	long long span;
	span = v[m - 1] - v[0];
	vector<long long>gap;
	for (int i = 0; i + 1 < m; i++) {
		gap.push_back(v[i + 1] - v[i]);
	}
	sort(gap.begin(), gap.end());
	long long cut = 0;
	for (int i = 0; i < k - 1; i++) cut += gap[i];
	cout << span - cut << endl;
	return 0;
}