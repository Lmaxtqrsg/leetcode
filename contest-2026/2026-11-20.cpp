/*#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
	int N;
	cin >> N;
	vector<int>v(N);
	for (int i = 0; i < N; i++) {
		cin >> v[N];应该是v[i]呀
	}
	sort(v.begin(), v.end());
	int mx = 0;
	for (int i = 0; i < N; i++) {
		mx=max(mx,v[i] + N - i);
	}
	int ans = 0;
	for (int i = N-1; i >0; i++) {i--呀，i>=0呀
		if (v[i] + N > mx) { ans++; }应该是>=mx
		else break;
	}
	cout << ans << "\n";
	return 0;
}*/
/*#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
bool cmp(int a, int b) {
	return a > b;
}
int main() {
	int n,m;
	cin >> n >> m;
	vector<long long>v(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
	}
	vector<long long>gaps;
	for (int i = 0; i+1 < n; i++) {
		gaps.push_back(v[i + 1] - v[i] );
	}
	long long dis = v[n - 1] - v[0];
	long long cut = 0;
	sort(gaps.begin(), gaps.end(), cmp);
	for (int i = 0; i < m - 1; i++) {
		cut += gaps[i];
	}
	cout << dis - cut+m<< "\n";
	return 0;
}*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int vi[10005] = { 0 }; int wi[10005] = { 0 };
int main() {
	int  n, W;
	cin >> n >> W;
	int v, w, m;
	int pos = 0;
	vector<int>dp(W + 1, 0);//不是n+1,是W+1
	for (int i = 1; i <= n; i++) {
		cin >> v >> w >> m;
		if (m * w >= W) {
			for (int j = w; j <= W; j++) {
				dp[j] = max(dp[j], dp[j - w] + v);
			}
		}
		else {
			int k = 1;
			while (k < m) {
				vi[++pos] = k * v;
				wi[pos] = k * w;
				m -= k;
				k *= 2;
			}
			if (m) {
				vi[++pos] = m * v;
				wi[pos] = m * w;
			}
		}
	}
	for (int i = 1; i <= pos; i++) {
		for (int j = W; j >= wi[i]; j--) {//少了个j--
			dp[j] = max(dp[j], dp[j - wi[i]] + vi[i]);
		}
	}
	cout << dp[W] << "\n";//不是dp[W-1]，因为是从下标从1开始，所以应该是dp[W]
	return 0;
}