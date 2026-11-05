// 2021 计算机挑战赛 C++ 操作题 47 / 48 / 49：表达式求值（三题共用一份代码）
// 输入：第一行 N（组数）；接下来 N 行，每行形如 A@B#C（紧凑串，无空格）
// 输出：每组一行，表达式的计算结果
// 状态：看题解 AC（calc 函数与 N 组循环由提示补齐）
// 复杂度：O(N)
//
// 三道题只是运算符集合不同，靠 prec() 一张表区分：
//   2021-47：+ - *            → 1+2*3=7 / 3*2-1=5 / 5+7-9=3
//   2021-48：& | ^            → 1&2|3=3 / 3|2^1=3 / 5^7|9=11
//   2021-49：+ * %            → 1+2*3=7 / 3%2+1=2 / 5+7%9=12
//
// 卡点归因：
//   ②建模  第一版只把表达式 cout 出来，不知道要「算」——缺 calc 这一步
//   ②建模  没读 N 组，把第一行的 3 当成了 A
//   ③语法  prec(op1,op2,...) 写在 cin 之前，用未初始化的字符判断优先级
//
// 关键：三个数两个运算符，不需要双栈，判断优先级 + 两个分支即可
//   prec(op1) >= prec(op2) → 先算左边 (A op1 B) op2 C
//   否则                    → 先算右边 A op1 (B op2 C)
//   注意是 >= 不是 >，等于时按左结合：(5+7)-9 = 3

#include <iostream>
using namespace std;

int prec(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '&') return 3;
    if (op == '|') return 1;
    if (op == '^') return 2;
    return 0;
}

long long calc(long long a, char c, long long b) {
    switch (c) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '%': return a % b;
        case '/': return a / b;
        case '^': return a ^ b;
        case '&': return a & b;
        case '|': return a | b;
    }
    return 0;
}

int main() {
    int N;
    cin >> N;

    while (N--) {
        long long A, B, C;
        char op1, op2;
        cin >> A >> op1 >> B >> op2 >> C;      // cin 逐位解析紧凑串，多位数也支持

        long long ans;
        if (prec(op1) >= prec(op2)) {
            ans = calc(calc(A, op1, B), op2, C);   // 先算左边
        } else {
            ans = calc(A, op1, calc(B, op2, C));   // 先算右边
        }

        cout << ans << "\n";
    }
    return 0;
}
