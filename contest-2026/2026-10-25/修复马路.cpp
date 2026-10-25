#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
bool cmp(long long a, long long b) {
	return (a > b);
}
int main() {
	int n, m;
	cin >> n >> m;
	long long a;
	vector<long long>v;
	for (int i = 0; i < n; i++) {
		cin >> a;
		v.push_back(a);
	}
	if (n < m) {
		cout << "0" << "\n";
		return 0;
	}
	long long span = v[n - 1] - v[0];
	vector<long long>gap;
	for (int i = 0; i + 1 < n; i++) {
		gap.push_back(v[i + 1] - v[i]);
	}
	sort(gap.begin(), gap.end(), cmp);
	long long cut = 0;
	for (int i = 0; i < m - 1; i++)cut += gap[i];
	cout << span - cut + m << endl;
	return 0;
}