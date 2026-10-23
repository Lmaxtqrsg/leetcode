/* ============================================================
 * 第 2 章 线性表 —— 顺序表实现大整数加法
 * ------------------------------------------------------------
 * 题目：
 *   用顺序表存放两个位数很长的非负整数（long long 装不下），
 *   实现它们的加法。输入按「高位 → 低位」逐位给出。
 *
 * 数据结构：
 *   sqList 里约定 data[0] 存个位、data[1] 存十位……
 *   所以每读一位就「头插」一次：后来的高位把前面的高位往后挤，
 *   读完后 data[0] 正好落在最低位（个位）上。
 *
 * 核心思路：
 *   两个数都是逆序（低位在前）存放的，那就从 i = 0 开始逐位相加，
 *   carry 记进位，和直接写回 A。一直加到两个表都走完、且没有进位为止。
 *
 * 关键点：
 *   ① 头插的搬移循环必须从 length 开始倒着走，否则会覆盖掉还没搬的元素
 *   ② 循环条件里带上 carry：999 + 1 = 1000，最高位还要再进一位
 *   ③ 结果同样是逆序存放的，输出要从 length - 1 倒着打
 *   ④ MAXSIZE 要比输入位数多留 1 格，给最后的进位用
 *
 * 注意：
 *   本算法不主动去前导零，00000 + 00001 会原样输出 00001。
 *   OJ 数据一般不带前导零，所以不处理。
 * ============================================================ */

#include <iostream>
using namespace std;

#define MAXSIZE 100

typedef struct sqList {
    int data[MAXSIZE];
    int length;
} sqList;

/* 初始化空表 */
void InitList(sqList &L) {
    L.length = 0;
}

/* 头插：e 放到 data[0]，原有元素整体后移一位
 * 输入 1,2,3,4,5 → 存储 5,4,3,2,1（data[0] 是个位） */
void InsertHead(sqList &L, int e) {
    for (int j = L.length; j > 0; j--) {
        L.data[j] = L.data[j - 1];
    }
    L.data[0] = e;
    L.length++;
}

/* 大整数加法：结果就地存回 A */
void Add(sqList &A, sqList &B) {
    int carry = 0;
    int i;
    for (i = 0; i < A.length || i < B.length || carry; i++) {
        int sum = carry;
        if (i < A.length) sum += A.data[i];
        if (i < B.length) sum += B.data[i];
        A.data[i] = sum % 10;
        carry = sum / 10;
    }
    A.length = i;
}

/* 内部是逆序存放的，相加结果也是逆序，所以从后往前输出 */
void Print(sqList &L) {
    for (int i = L.length - 1; i >= 0; i--) {
        cout << L.data[i];
    }
    cout << endl;
}

int main() {
    sqList A, B;
    InitList(A);
    InitList(B);

    int n, x;
    cin >> n;                       /* A 的位数 */
    for (int i = 0; i < n; i++) {
        cin >> x;
        InsertHead(A, x);
    }

    cin >> n;                       /* B 的位数 */
    for (int i = 0; i < n; i++) {
        cin >> x;
        InsertHead(B, x);
    }

    Add(A, B);
    Print(A);
    return 0;
}

/* ------------------------------------------------------------
 * 测试输入：
 *   5
 *   1 2 3 4 5
 *   3
 *   6 7 8
 *
 * 期望输出：
 *   13023
 * ------------------------------------------------------------ */
