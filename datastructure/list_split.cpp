/* ============================================================
 * 第 2 章 线性表 —— 单链表的分解
 * ------------------------------------------------------------
 * 题目：
 *   设计算法将一个带头结点的单链表 A 分解为两个具有相同结构
 *   的链表 B 和 C，其中 B 表的结点为 A 表中值小于 0 的结点，
 *   C 表的结点为 A 表中值大于 0 的结点（A 中元素为非零整数）。
 *   ★ 要求 B、C 表利用 A 表的结点。
 *
 * 核心思路：
 *   p 遍历 A 的每个数据结点，按正负把它接到 B 或 C 的尾部。
 *   全程不 new 新结点，只是改指针方向。
 *
 * 三个关键点：
 *   ① A->next = NULL   —— 先把 A 清空
 *   ② q = p->next      —— 改指针前先备份后继（★ 循环内）
 *   ③ p->next = NULL   —— 把结点摘干净（★ 循环内）
 *   ④ rb / rc          —— 尾指针必须活在循环外
 * ============================================================ */

#include <iostream>
using namespace std;

typedef struct LNode {
    int data;
    struct LNode *next;
} LNode, *LinkList;

/* 初始化带头结点的空链表 */
void InitList(LinkList &L) {
    L = new LNode;
    L->next = NULL;
}

/* 尾插法建表：读入 n 个整数 */
void CreateList(LinkList &L, int n) {
    LNode *r = L;                 /* 尾指针从头结点开始 */
    for (int i = 0; i < n; i++) {
        LNode *p = new LNode;
        cin >> p->data;
        p->next = NULL;
        r->next = p;
        r = p;
    }
}

/* 核心算法：把 A 拆成 B(<0) 和 C(>0)，复用 A 的结点 */
void DisConpose(LinkList &A, LinkList &B, LinkList &C) {
    LNode *p  = A->next;          /* p 遍历 A 的数据结点 */
    LNode *rb = B;                /* ★ 尾指针定义在循环外，跨轮次保持 */
    LNode *rc = C;                /* ★ */
    A->next = NULL;               /* ① A 清空 */

    while (p != NULL) {
        LNode *q = p->next;       /* ② 先备份下一个 */
        p->next = NULL;           /* ③ 把 p 摘干净 */

        if (p->data < 0) {
            rb->next = p;         /* 接到 B 的尾巴 */
            rb = p;
        } else {
            rc->next = p;         /* 接到 C 的尾巴 */
            rc = p;
        }

        p = q;                    /* ④ 用备份继续 */
    }
}

void PrintList(const char *name, LinkList L) {
    cout << name << " : ";
    LNode *p = L->next;
    while (p != NULL) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

int main() {
    LinkList A, B, C;
    InitList(A);                  /* ★ 必须先建头结点 */
    InitList(B);
    InitList(C);

    int n;
    cin >> n;
    CreateList(A, n);

    PrintList("A", A);

    DisConpose(A, B, C);

    cout << "---- after split ----" << endl;
    PrintList("A", A);
    PrintList("B", B);
    PrintList("C", C);
    return 0;
}

/* ------------------------------------------------------------
 * 测试输入：
 *   6
 *   -1 2 -3 4 -5 6
 *
 * 期望输出：
 *   A : -1 2 -3 4 -5 6
 *   ---- after split ----
 *   A :
 *   B : -1 -3 -5
 *   C : 2 4 6
 * ------------------------------------------------------------ */
