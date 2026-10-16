/* ============================================================
 * 第 2 章 线性表 —— 一趟遍历找值最大的结点
 * ------------------------------------------------------------
 * 题目：
 *   设计一个算法，通过一趟遍历确定长度为 n 的单链表中值最大
 *   的结点。
 *
 * 为什么强调「一趟」：
 *   链表不能随机访问，访问第 k 个元素必须从头走 k 步。
 *   遍历是链表最贵的操作，能省一趟就省一趟。
 *
 * 三个关键点：
 *   ① 先判空       —— 空表时 L->next 是 NULL，解引用会崩
 *   ② 从 L->next 开始 —— 头结点不存数据
 *   ③ p = p->next 放在 if 外面 —— 走不走和「要不要更新」无关
 * ============================================================ */

#include <iostream>
using namespace std;

typedef struct LNode {
    int data;
    struct LNode *next;
} LNode, *LinkList;

void InitList(LinkList &L) {
    L = new LNode;
    L->next = NULL;
}

void CreateList(LinkList &L, int n) {
    LNode *r = L;
    for (int i = 0; i < n; i++) {
        LNode *p = new LNode;
        cin >> p->data;
        p->next = NULL;
        r->next = p;
        r = p;
    }
}

/* 版本一：返回最大值 */
int MaxValue(LinkList L) {
    if (L->next == NULL) return 0;          /* ① 空表保护 */
    LNode *p = L->next;                     /* ② 第一个数据结点 */
    int max = p->data;
    p = p->next;
    while (p != NULL) {
        if (p->data > max) max = p->data;   /* 只更新 max */
        p = p->next;                        /* ③ 末尾一定推进 */
    }
    return max;
}

/* 版本二：返回最大结点（题目字面要求） */
LNode* MaxNode(LinkList L) {
    if (L->next == NULL) return NULL;

    LNode *best = L->next;                  /* 假设第一个最大 */
    LNode *p    = L->next->next;            /* 从第二个开始比 */

    while (p != NULL) {
        if (p->data > best->data) {
            best = p;                       /* ★ 只记结点，不记值 */
        }
        p = p->next;
    }
    return best;
}

int main() {
    LinkList L;
    InitList(L);

    int n;
    cin >> n;
    CreateList(L, n);

    cout << "maxValue = " << MaxValue(L) << endl;

    LNode *m = MaxNode(L);
    if (m != NULL) {                        /* ★ 拿到指针先判空 */
        cout << "maxNode  = " << m->data << endl;   /* ★ 加 ->data */
    } else {
        cout << "list is empty" << endl;
    }
    return 0;
}

/* ------------------------------------------------------------
 * 测试输入：
 *   5
 *   3 7 2 9 4
 *
 * 期望输出：
 *   maxValue = 9
 *   maxNode  = 9
 *
 * 边界测试（n = 0）：
 *   输入  0
 *   输出  maxValue = 0
 *         list is empty
 * ------------------------------------------------------------ */
