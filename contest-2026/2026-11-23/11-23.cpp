/*#include <iostream>
#include <string>
using namespace std;
int main() {
	string s;
	cin >> s;
	int num = (int)s.size();
	int cnt = 0;
	for (int i = 0; i < num; i++) {
		if (s[i] == '@')cnt++;
		else break;
	}
	for (int i = cnt; i < num; i++) {
		cout << s[i];
	}
	for (int i = 0; i < cnt; i++) {
		cout << '@';
	}
	cout << "\n";
	return 0;
}*/
/*#include <iostream>
#include <algorithm>
using namespace std;
int main() {
	int m, n;
	cin >> m>>n;
	if (m < n) {
		swap(m, n);
	}
	if (m - n < n) {
		n = m - n;
	}
	long long ans = m;
	for (int i = 2; i <= n; i++) {
		ans =ans *(m-i+1) / i;
	}
	cout << ans << "\n";
	return 0;
}*/
/*#include <iostream>
using namespace std;
int main() {
	int n;
	cin >> n;
	int a[105][105];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> a[i][j];
		}
	}
	long long  sum = 0;
	for (int i = 0; i < n - 1; i++)sum += a[0][i];
	for (int j = 0; j < n - 1; j++)sum += a[j][n - 1];
	for (int k = n - 1; k > 0; k--)sum += a[n - 1][k];
	for (int m = n - 1; m > 0; m--)sum += a[m][0];
	cout << sum << "\n";
	return 0;
}*/

