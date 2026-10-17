/* ============================================================
 * 第 2 章 线性表 —— 删除递增有序表中指定区间的元素
 * ------------------------------------------------------------
 * 题目：
 *   设计算法删除递增有序链表中值大于 mink 且小于 maxk 的所有
 *   元素（mink 和 maxk 是给定参数，其值可以与表中元素相同，
 *   也可以不同）。
 *
 * 核心思路：
 *   “递增有序”是这道题的钥匙 —— 满足 mink < data < maxk 的结点
 *   在表中一定连续成段。所以不必边走边删，而是：
 *       ① 定位左边界：跳过所有 data <= mink 的结点，pre 停在
 *          最后一个 <= mink 的结点上（若没有，就是头结点）
 *       ② 连续删除：从 p 开始，只要 data < maxk 就删掉
 *       ③ 一次挂接：pre->next = p，中间整段被摘下
 *
 *   严格不等号决定了两个端点都要保留：
 *       左边用 data <= mink 跳过  —— 等于 mink 的留下
 *       右边用 data <  maxk 删除  —— 等于 maxk 的留下
 *
 * 三个关键点：
 *   ① pre = L         —— 单链表删除必须知道前驱，所以要多一个 pre
 *   ② r = p; p = p->next; delete r;
 *                     —— 先取后继再释放，顺序反了就断链（★ 循环内）
 *   ③ 一次挂接        —— 不要每删一个就改一次 pre->next
 *
 * 时间复杂度：最坏 O(n)（mink 很大时要一直走到表尾）
 * 空间复杂度：O(1)，只多了 pre、p、r 三个指针
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

/* 尾插法建表：读入 n 个整数（必须递增输入） */
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

/* 核心算法：删除 mink < data < maxk 的结点，时间 O(n)，空间 O(1) */
void DeleteRange(LinkList &L, int mink, int maxk) {
    LNode *pre = L;                 /* pre 是 p 的前驱，初值为头结点 */
    LNode *p = L->next;             /* p 是扫描指针 */

    while (p != NULL && p->data <= mink) {   /* ① 定位左边界 */
        pre = p;
        p = p->next;
    }

    while (p != NULL && p->data < maxk) {    /* ② 连续删除整段 */
        LNode *r = p;               /*    先记下要删的结点 */
        p = p->next;                /*    再取后继 */
        delete r;                   /*    最后释放 */
    }

    pre->next = p;                  /* ③ 一次挂接 */
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
    LinkList L;
    InitList(L);

    int n;
    cin >> n;
    CreateList(L, n);

    int mink, maxk;
    cin >> mink >> maxk;

    PrintList("before", L);
    DeleteRange(L, mink, maxk);
    PrintList("after ", L);
    return 0;
}

/* ------------------------------------------------------------
 * 测试输入：
 *   5
 *   1 3 5 7 9
 *   3 7
 *
 * 期望输出：
 *   before : 1 3 5 7 9
 *   after  : 1 3 7 9
 *
 * ★ 边界一定要测这三种：
 *   1) mink 等于表中元素：1 3 5 7 9, mink=3 maxk=7  -> 1 3 7 9
 *   2) maxk 等于表中元素：1 3 5 7 9, mink=2 maxk=5  -> 1 9
 *   3) mink == maxk（区间为空）：1 3 5 7 9, mink=5 maxk=5 -> 不变
 *
 * 曾经踩的坑：左边界写成 data < mink（少了个等号），
 * 等于 mink 的结点没被跳过，被第二段当成待删结点删掉了。
 * ------------------------------------------------------------ */
