/*#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main() {
    string s1,s2,s3;
    getline(cin, s1);
    getline(cin, s2);
    getline(cin, s3);
    vector<char>s;
    int num = (int)s3.size();
    for (int i = 0; i < num; i++) {
        int x = s3[i];
        if (x <= 'z' && x >= 'a') {
            x -= 'a';
            s.push_back(s1[x]);
        }
        else if (x <= 'Z' && x >= 'A') {
            x -= 'A';
            s.push_back(s2[x]);
        }
        else s.push_back(s3[i]);
    }
    for (int i = 0; i < (int)s.size(); i++) {
        cout << s[i];
    }
    cout << "\n";
    return 0;
}*/
/*#include <iostream>
#include <string>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s1, s2, s3;
    // 循环读取一组3行，读到末尾自动停止
    while (getline(cin, s1) && getline(cin, s2) && getline(cin, s3))
    {
        for (char ch : s3)
        {
            if (ch >= 'a' && ch <= 'z')
            {
                int idx = ch - 'a';
                cout << s1[idx];
            }
            else if (ch >= 'A' && ch <= 'Z')
            {
                int idx = ch - 'A';
                cout << s2[idx];
            }
            else
            {
                cout << ch;
            }
        }
        cout << '\n';
    }
    return 0;
}*/
/*#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        int x;
        cin >> x;
        int now, maxsum;
        now = maxsum = x;
        for (int i = 1; i < n; i++) {
            cin >> x;
            now = max(x, now + x);
            maxsum = max(maxsum, now);
        }
        cout << maxsum << "\n";
    }
    return 0;
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Node {
    int p, s;
    int total;
};
bool cmp(const Node& a, const Node& b) {
    return a.total < b.total;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    while (cin >> N >> M) {
        vector<Node>a(N);
        for (int i = 0; i < N; i++) {
            cin >> a[i].p >> a[i].s;
            a[i].total = a[i].p + a[i].s;
        }
        sort(a.begin(), a.end(), cmp);
        int ans = 0;
        for (int k = N; k >= 0; k--) {//可以从最大往下找
            long long sum = 0;
            int max_p = 0;
            for (int i = 0; i < k; i++) {
                sum += a[i].total;
                if (max_p < a[i].p)max_p = a[i].p;
            }
            long long cost = sum - max_p / 2;
            if (cost <= M) {
                ans = k;
                break;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}