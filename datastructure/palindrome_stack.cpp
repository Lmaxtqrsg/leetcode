/* ============================================================
 * 第 3 章 栈和队列 —— 用栈判断回文
 * ------------------------------------------------------------
 * 题目：
 *   利用栈判断一个字符串是否为回文串。
 *
 * 思路：
 *   ① 把前半部分字符压入栈
 *   ② 从后半部分开始，依次出栈并和原串对比
 *   ③ 全部相等 -> 回文；有一个不等 -> 不是
 *
 * 为什么取 (n+1)/2 个入栈：
 *   · 奇数 n=5：入栈 3 个（前 3 个），出栈从下标 2 开始
 *     中间那个字符会和自己比一次，不影响结果
 *   · 偶数 n=4：入栈 2 个（前 2 个），出栈从下标 2 开始
 *
 * 复杂度：时间 O(n)，空间 O(n)（栈）
 * ============================================================ */

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

#define MAXSIZE 100

typedef struct {
    int *base;
    int *top;
    int smaxsize;
} sqStack;

void InitStack(sqStack &S) {
    S.base = new int[MAXSIZE];
    if (!S.base) exit(1);
    S.top = S.base;
    S.smaxsize = MAXSIZE;
}

bool Push(sqStack &S, int e) {
    if ((S.top - S.base) >= S.smaxsize) return false;   /* 栈满 */
    *S.top++ = e;
    return true;
}

bool Pop(sqStack &S, char &e) {
    if (S.top == S.base) return false;                  /* 栈空 */
    e = (char)*--S.top;
    return true;
}

void DestroyStack(sqStack &S) {
    delete[] S.base;
    S.base = nullptr;
    S.top = nullptr;
    S.smaxsize = 0;
}

/* 用栈判断 seq 是否回文 */
bool IsPalindrome(sqStack &S, const string &seq) {
    int num  = (int)seq.size();
    int half = (num + 1) / 2;      /* 前半部分字符数（奇数含中间） */
    bool ok  = true;

    /* ① 前半部分入栈 */
    for (int i = 0; i < half; i++) {
        if (!Push(S, seq[i])) { ok = false; break; }
    }

    /* ② 后半部分和出栈字符对比 */
    if (ok) {
        for (int i = num / 2; i < num; i++) {
            char c;
            if (!Pop(S, c) || c != seq[i]) { ok = false; break; }
        }
    }
    return ok;
}

int main() {
    sqStack S;
    InitStack(S);

    string seq;
    if (!(cin >> seq)) return 0;

    if ((int)(seq.size() + 1) / 2 > MAXSIZE) {
        cout << "序列过长，超过栈容量" << endl;
        return 0;
    }

    if (IsPalindrome(S, seq)) cout << "回文" << endl;
    else                      cout << "非回文" << endl;

    DestroyStack(S);
    return 0;
}

/* ------------------------------------------------------------
 * 测试：
 *   abcba -> 回文
 *   abba  -> 回文
 *   abca  -> 非回文
 *   a     -> 回文
 * ------------------------------------------------------------ */