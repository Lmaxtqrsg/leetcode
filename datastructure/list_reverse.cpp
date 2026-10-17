/* ============================================================
 * 第 2 章 线性表 —— 单链表的原地逆置
 * ------------------------------------------------------------
 * 题目：
 *   设计算法将带头结点的单链表中所有结点的链接方向“原地”逆转，
 *   要求仅利用原表的存储空间，即空间复杂度为 O(1)。
 *
 * 核心思路：
 *   单链表只能往后走，而“掉转方向”要求每个结点记住它的前驱，
 *   所以整个过程同时握住三个位置：
 *       p —— 正在处理的结点（当前结点）
 *       q —— p 的前驱（逆置后它就是新表的首结点）
 *       r —— p 的后继（★ 必须先备份，否则 p->next 一改就丢了）
 *
 *   每轮固定四步，顺序不能变：
 *       ① r = p->next    先存后继
 *       ② p->next = q    掉转方向
 *       ③ q = p          前驱前移
 *       ④ p = r          当前前移
 *
 *   循环结束时 q 指向原表尾，也就是逆置后的首结点，
 *   把它挂回头结点：L->next = q。
 *
 * 三个关键点：
 *   ① L->next = NULL  —— 头结点先摘下来，否则原首结点的 next
 *                        会指回头结点，形成一个环
 *   ② r = p->next     —— 备份必须在前，改指针在后（★ 循环内）
 *   ③ L->next = q     —— 收尾挂接，少了这句整张表就丢了
 *
 * 另一个等价写法（头插法）见文件末尾的 ReverseByHeadInsert。
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
    LNode *r = L;
    for (int i = 0; i < n; i++) {
        LNode *p = new LNode;
        cin >> p->data;
        p->next = NULL;
        r->next = p;
        r = p;
    }
}

/* 核心算法：三指针原地逆置，时间 O(n)，空间 O(1) */
void ReverseList(LinkList &L) {
    LNode *p = L->next;        /* p 指向第一个数据结点 */
    LNode *q = NULL;           /* q 指向已逆置子表的首结点 */
    L->next = NULL;            /* ① 头结点摘下，将来它成为新表的前驱 */

    while (p != NULL) {
        LNode *r = p->next;    /* ① 先备份后继，防止断链 */
        p->next = q;           /* ② 掉转这个结点的方向 */
        q = p;                 /* ③ q 前移，仍指向新子表首结点 */
        p = r;                 /* ④ p 前移，处理下一个 */
    }

    L->next = q;               /* ③ 头结点接上逆置后的首结点 */
}

/* 另一种写法：头插法重建，同样 O(1) 空间
   按顺序取出原表的每个结点，逐个头插到一个空表上，
   顺序自然就反了。main 里默认调用上面的 ReverseList。 */
void ReverseByHeadInsert(LinkList &L) {
    LNode *p = L->next;
    L->next = NULL;
    while (p != NULL) {
        LNode *r = p->next;    /* 先备份 */
        p->next = L->next;     /* 头插到 L 之后 */
        L->next = p;
        p = r;
    }
}

void PrintList(const char *name, LinkList L) {
    cout << name << " : ";
    LNode *p = L->next;
    while (p != NULL) {
        cout << p->data << " ";
        p = p->next;           /* ★ 别忘了推进 */
    }
    cout << endl;
}

int main() {
    LinkList L;
    InitList(L);

    int n;
    cin >> n;
    CreateList(L, n);

    PrintList("before", L);
    ReverseList(L);
    PrintList("after ", L);
    return 0;
}

/* ------------------------------------------------------------
 * 测试输入：
 *   5
 *   1 2 3 4 5
 *
 * 期望输出：
 *   before : 1 2 3 4 5
 *   after  : 5 4 3 2 1
 *
 * 边界：n = 0（空表）与 n = 1（单结点）都要能正常运行，
 *       逆置两次应回到原样。
 * ------------------------------------------------------------ */
