/*#include <iostream>
#include <cstring>
using namespace std;
typedef struct BiNode {
    int data;
    struct BiNode* lch;
    struct BiNode* rch;
}BiNode, * BiTree;

int idx;
void CreateBiTree(BiTree& T, char str[]) {
    char ch = str[idx++];
    if (ch == '#') {
        T = NULL;
    }
    else {
        T = new BiNode;
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            T->data = ch;
        }
        else {
            T->data = ch - '0';
        }
        T->lch = T->rch = NULL;
        CreateBiTree(T->lch, str);
        CreateBiTree(T->rch, str);
    }
}

void CalcuBiTree(BiTree T) {
    if (T == NULL) return;
    CalcuBiTree(T->lch);
    CalcuBiTree(T->rch);
    switch ((char)T->data)
    {
    case '+':
        T->data = T->lch->data + T->rch->data;
        break;
    case '-':
        T->data = T->lch->data - T->rch->data;
        break;
    case '*':
        T->data = T->lch->data * T->rch->data;
        break;
    case '/':
        T->data = T->lch->data / T->rch->data;
        break;
    default:
        break;
    }
}

int main() {
    char s[1000];
    while (scanf("%s", s) != EOF) {
        idx = 0;
        BiTree T;
        CreateBiTree(T, s);
        CalcuBiTree(T);
        cout << T->data << "\n";
    }
    return 0;
}*/
/*#include <iostream>
using namespace std;
typedef struct BiNode {
    char data;
    struct BiNode* lch;
    struct BiNode* rch;
}BiNode, * BiTree;
void CreateBiTree(BiTree& T) {
    char ch;
    cin >> ch;
    if (ch == '#') {
        T = NULL;
    }
    else {
        T = new BiNode;
        T->data = ch;
        T->lch = T->rch = NULL;
        CreateBiTree(T->lch);
        CreateBiTree(T->rch);
    }
}
int getPri(BiTree T) {
    if (T->data == '+' || T->data == '-')return 1;
    if (T->data == '*' || T->data == '/')return 2;
    return 0;
}
void printBiTree(BiTree T, int fa_pri, bool isleft) {
    if (T == NULL) {
        return;
    }
    int cur_pri = getPri(T);
    bool needBracket = false;
    if (cur_pri != 0) {
        if (cur_pri < fa_pri) {
            needBracket = true;
        }
        if (cur_pri == fa_pri && !isleft) {
            needBracket = true;
        }
    }
    if (needBracket)cout << '(';
    printBiTree(T->lch, cur_pri, true);
    cout << T->data;
    printBiTree(T->rch, cur_pri, false);
    if (needBracket)cout << ')';
}
int main() {
    BiTree T;
    CreateBiTree(T);
    printBiTree(T, 0, true);
    return 0;
}*/
/*#include <iostream>
using namespace std;
int Getpri(char x) {
    if (x == '*' || x == '/')return 2;
    if (x == '+' || x == '-')return 1;
    return 0;

}
int calcu(int x, int y, char z) {
    switch (z) {
    case '*':return x * y;
    case '+':return x + y;
    case '-':return x - y;
    case '/':return x / y;
    }
}
int main() {
    int ans;
    int A, B, C;
    char a, b;
    int N;
    cin >> N;
    while (N--) {
        cin >> A >> a >> B >> b >> C;
        int a_pri = Getpri(a);
        int b_pri = Getpri(b);
        if (a_pri >= b_pri) {
            ans = calcu(calcu(A, B, a), C, b);
        }
        else ans = calcu(A, calcu(B, C, b), a);
        cout << ans << "\n";
    }
    return 0;
}*/
/*#include <iostream>
using namespace std;
int main() {
    int N;
    cin >> N;
    int cnt = 0;
    while (N--) {
        int a;
        cin >> a;
        if (a & 12)cnt++;
    }
    cout << cnt << "\n";
    return 0;
}*/
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

struct BiNode { int data; BiNode* lch, * rch; };
int pre[1005], ino[1005];

BiNode* Build(int pl, int pr, int il, int ir) {
    if (pl > pr) return NULL;
    int root = pre[pl];
    int k = il;
    while (ino[k] != root) k++;
    int len = k - il;                              // 左子树结点数
    BiNode* T = new BiNode;
    T->data = root;
    T->lch = Build(pl + 1, pl + len, il, k - 1);
    T->rch = Build(pl + len + 1, pr, k + 1, ir);
    return T;
}

BiNode* Find(BiNode* T, int x) {
    if (!T) return NULL;
    if (T->data == x) return T;
    BiNode* p = Find(T->lch, x);
    return p ? p : Find(T->rch, x);
}

int MaxOf(BiNode* T) {
    if (!T) return -1;
    int mx = T->data;
    if (T->lch) mx = max(mx, MaxOf(T->lch));
    if (T->rch) mx = max(mx, MaxOf(T->rch));
    return mx;
}

int main() {
    string line;
    int n = 0, m = 0, x;

    getline(cin, line);                            // 一行不定长，必须 getline
    stringstream s1(line);
    while (s1 >> x) pre[n++] = x;

    getline(cin, line);
    stringstream s2(line);
    while (s2 >> x) ino[m++] = x;

    int target;
    cin >> target;

    BiNode* root = Build(0, n - 1, 0, m - 1);
    BiNode* p = Find(root, target);
    if (!p) { cout << -1 << "\n"; return 0; }   // x 不在树上
    if (!p->lch) { cout << target << "\n"; return 0; } // 左子树空 → 输出 x 本身
    cout << MaxOf(p->lch) << "\n";
    return 0;
}