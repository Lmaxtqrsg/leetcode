#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct stu {
	int id;
	int op, tk, yy;
	int sum;
};
/*bool cmp1(const stu& a, const stu& b) {
	return a.op > b.op;
}
bool cmp2(stu c, stu d) {
	return c.tk > d.tk;
}
bool cmp3(stu e, stu f) {
	return e.yy > f.yy;
}*///不用排序，用for循环比较
bool cmp4(const stu &m, const stu &n) {
	if (m.sum != n.sum)return m.sum > n.sum;
	if (m.yy != n.yy)return m.yy > n.yy;
	if (m.tk != n.tk)return m.tk > n.tk;
	if (m.op != n.op)return m.op > n.op;
	return m.id < n.id;
}
int main() {
	int n;
	cin >> n;
	vector<stu>S(n);
	for (int i = 0; i < n; i++) {
		cin >> S[i].id >> S[i].op >> S[i].tk >> S[i].yy;
		S[i].sum = S[i].tk + S[i].op + S[i].yy;
	}
	/*sort(S.begin(), S.end(), cmp1);
	for (int i = 0; i < 1; i++) {
		cout << S[i].id << " " << S[i].op << "\n";
	}
	sort(S.begin(), S.end(), cmp2);
	for (int i = 0; i < 1; i++) {
		cout << S[i].id << " " << S[i].tk << "\n";
	}
	sort(S.begin(), S.end(), cmp3);
	for (int i = 0; i < 1; i++) {
		cout << S[i].id << " " << S[i].yy << "\n";
	}
	cout << "\n";*/
	int b1 = 0, b2 = 0, b3 = 0;
	for (int i = 0; i < n; i++) {
		if (S[i].op > S[b1].op || (S[i].op == S[b1].op && S[i].id < S[b1].id))b1 = i;
		if (S[i].tk > S[b1].tk || (S[i].tk == S[b1].tk && S[i].id < S[b1].id))b2 = i;
		if (S[i].yy > S[b1].yy || (S[i].yy == S[b1].yy && S[i].id < S[b1].id))b3 = i;
	}
	cout << S[b1].id << " " << S[b1].op << "\n";
	cout << S[b2].id << " " << S[b2].tk << "\n";
	cout << S[b3].id << " " << S[b3].yy << "\n";
	cout << "\n";
	sort(S.begin(), S.end(), cmp4);
	int flag = 0;
	for (int i = 0; i < n; i++) {
		if (S[i].op >= 80 && S[i].tk >= 80 && S[i].yy >= 80) {
			cout << S[i].id << " " << S[i].sum << "\n";
			flag = 1;
		}
	}
	if (!flag)cout << "NULL" << "\n";
	return 0;
}                                                                                                                                                                                                                                                      