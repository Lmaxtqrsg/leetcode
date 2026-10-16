/* ============================================================
 * 第 3 章 栈和队列 —— 循环队列：入队/出队动作模拟
 * ------------------------------------------------------------
 * 题目：
 *   根据输入的入队出队动作序列，每次入队或出队后输出队中内容。
 *   I 表示入队，O 表示出队。入队数据从 1 开始依次递增。
 *   输出时左边是队头、右边是队尾，空队时输出 E。
 *
 * 循环队列的核心公式：
 *   元素个数 = (rear - front + MAXSIZE) % MAXSIZE
 *   判空     = (rear == front)
 *   判满     = ((rear + 1) % MAXSIZE == front)   牺牲一个单元
 *   入队改 rear，出队改 front
 * ============================================================ */

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

#define MAXSIZE 100

typedef struct {
    int *base;
    int front;                  /* 队头 */
    int rear;                   /* 队尾（指向下一个空位） */
} sqQueue;

void InitQueue(sqQueue &Q) {
    Q.base = new int[MAXSIZE];
    if (Q.base == NULL) exit(1);
    Q.front = Q.rear = 0;
}

void EnQueue(sqQueue &Q, int e) {
    if ((Q.rear + 1) % MAXSIZE == Q.front) return;   /* 判满 */
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAXSIZE;
}

void DeQueue(sqQueue &Q) {
    if (Q.rear == Q.front) return;                   /* 判空 */
    Q.front = (Q.front + 1) % MAXSIZE;
}

/* 输出队列内容：队头 → 队尾，数字连着，行末一个空格 */
void ShowQueue(sqQueue Q) {          /* 值传递：循环会改 Q.front，不影响外面 */
    if (Q.rear == Q.front) {
        cout << "E" << endl;
        return;
    }
    /* ★ if 到这里就结束了！下面的循环必须在 if 外面 */

    int count = (Q.rear - Q.front + MAXSIZE) % MAXSIZE;   /* ★ 先把个数算好 */
    for (int i = 0; i < count; i++) {                     /* ★ 从 0，跑 count 次 */
        cout << Q.base[Q.front];                          /* 数字连着 */
        Q.front = (Q.front + 1) % MAXSIZE;
    }
    cout << " " << endl;                                  /* 行末一个空格 */
}

int main() {
    sqQueue Q;
    InitQueue(Q);

    string seq;
    cin >> seq;

    int nextNum = 1;

    for (int i = 0; i < (int)seq.size(); i++) {
        char c = seq[i];

        if (c == 'I') {
            EnQueue(Q, nextNum);
            nextNum++;
        }
        else if (c == 'O') {
            DeQueue(Q);
        }

        ShowQueue(Q);                /* ★ 必须在循环里 */
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
 *
 * ⚠️ 关于 count：不能把 (rear-front+MAXSIZE)%MAXSIZE 直接写进
 *    for 的循环条件里，因为循环体会修改 front，导致条件每轮变小，
 *    结果少输出一半。必须先算好 count 固定住。
 * ------------------------------------------------------------ */
