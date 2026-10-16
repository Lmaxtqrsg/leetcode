/* ============================================================
 * 第 3 章 栈和队列 —— 顺序栈：入栈/出栈动作模拟
 * ------------------------------------------------------------
 * 题目：
 *   根据输入的入栈出栈动作序列，每次入栈或出栈后输出栈中内容。
 *   I 表示入栈，O 表示出栈。入栈数据从 1 开始依次递增。
 *   输出时左边是栈底、右边是栈顶，空栈时输出 E。
 *   （提示：如果输出不匹配，注意行末的空格）
 *
 * 顺序栈的四个操作：
 *   判空   top == base
 *   判满   top - base == stacksize
 *   入栈   *top++ = e      先赋值，再后移
 *   出栈   top--           只移指针，不取值
 *   个数   top - base
 * ============================================================ */

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

#define MAXSIZE 100             /* ★ 宏定义后面不能有分号 */

typedef struct {
    int *base;                  /* 栈底 */
    int *top;                   /* 栈顶（指向下一个空位） */
    int stacksize;              /* 容量 */
} sqStack;

void InitStack(sqStack &S) {
    S.base = new int[MAXSIZE];
    if (S.base == NULL) exit(1);    /* ★ 判断的是 S.base，不是 S */
    S.top = S.base;                 /* 空栈：top == base */
    S.stacksize = MAXSIZE;
}

void Push(sqStack &S, int e) {
    if (S.top - S.base == MAXSIZE) return;   /* 栈满 */
    *S.top++ = e;
}

void Pop(sqStack &S) {
    if (S.top == S.base) return;             /* 空栈不能出栈 */
    S.top--;
}

/* 输出栈内容：栈底 → 栈顶，数字连着，行末一个空格 */
void ShowStack(sqStack &S) {
    if (S.top == S.base) {                   /* ★ 空栈要输出 E */
        cout << "E" << endl;
        return;                              /* ★ return 后不要写代码 */
    }
    /* ★ if 到这里就结束了，下面属于「非空栈」的处理 */
    for (int *p = S.base; p < S.top; p++) {
        cout << *p;                          /* 数字连着 */
    }
    cout << " " << endl;                     /* 行末一个空格 */
}

int main() {
    sqStack S;
    InitStack(S);

    string seq;
    cin >> seq;

    int nextNum = 1;                         /* 下一个要入栈的数 */

    for (int i = 0; i < (int)seq.size(); i++) {
        char c = seq[i];                     /* ★ 必须赋值！ */

        if (c == 'I') {
            Push(S, nextNum);
            nextNum++;
        }
        else if (c == 'O') {                 /* ★ 用 else if，不用裸 else */
            Pop(S);
        }

        ShowStack(S);                        /* ★ 必须在循环里 */
    }
    return 0;
}

/* ------------------------------------------------------------
 * 测试输入：
 *   IOIOIOIIIIIOIOOOIOOOO
 *
 * 期望输出（前 20 行与题目示例一致）：
 *   1 E 2 E 3 E 4 45 456 4567 45678 5678 56789 6789 789 89
 *   8910 910 10 E E
 * ------------------------------------------------------------ */
