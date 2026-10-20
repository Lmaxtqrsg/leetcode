# 数据结构作业

武汉轻工大学 · 计算机科学与技术 · 大二上（2026 秋）

## 目录

### 第 2 章 线性表

| 文件 | 题目 | 要点 |
|---|---|---|
| [`list_split.cpp`](list_split.cpp) | 单链表分解为 B(<0) 和 C(>0) | 复用 A 的结点，尾指针放循环外 |
| [`list_max.cpp`](list_max.cpp) | 一趟遍历找值最大的结点 | 先判空，p = p->next 放 if 外 |
| [`list_reverse.cpp`](list_reverse.cpp) | 单链表原地逆置（O(1) 空间） | 三指针，先备份后继再改指针 |
| [`list_delete_range.cpp`](list_delete_range.cpp) | 删除递增有序表中 (mink, maxk) 的元素 | 利用有序性，定位后整段摘除 |
| [`list_bigint_add.cpp`](list_bigint_add.cpp) | 顺序表实现大整数加法 | 头插使低位在前；`carry` 写进循环条件 |

### 第 3 章 栈和队列

| 文件 | 题目 | 要点 |
|---|---|---|
| [`stack_io_sim.cpp`](stack_io_sim.cpp) | 顺序栈：按 I/O 序列模拟 | top 指向下一个空位 |
| [`queue_io_sim.cpp`](queue_io_sim.cpp) | 循环队列：按 I/O 序列模拟 | 个数 = (rear-front+MAXSIZE)%MAXSIZE |
| [`palindrome_stack.cpp`](palindrome_stack.cpp) | 用栈判断回文串 | 前半入栈，后半出栈对比 |

## 编译运行

用 Visual Studio 打开单个 `.cpp` 文件，按 `Ctrl+F5`。

或命令行（Developer Command Prompt）：

```
cl /nologo /EHsc /utf-8 文件名.cpp /Fe:文件名.exe
文件名.exe
```

## 踩过的坑

| 坑 | 说明 |
|---|---|
| `#define` 后面多了分号 | `new int[20;]` 语法错误，连带引发几十个错误 |
| `return` 后面写了代码 | 死代码，函数在非空时什么都不做 |
| 循环条件依赖循环体修改的变量 | `for(i=0; i<(rear-front)%n; i++)` 会少输出一半 |
| 尾指针写在循环里 | 每轮被重置，链表永远只有一个结点 |
| 循环里忘了 `p = p->next` | 死循环 |
| 没有头结点 | 野指针，程序崩溃 |
| `cout << p` | 输出的是地址，不是值 |

## 四个通用模板

### 链表遍历

```cpp
if (L->next == NULL) { /* 先判空 */ }
LNode* p = L->next;              // 从第一个「数据结点」开始
while (p != NULL) {
    // ... 处理 p ...
    p = p->next;                 // ★ 末尾一定推进
}
```

### 链表逆置（原地，O(1) 空间）

```cpp
LNode *q = NULL;                 // 反转后的前驱
LNode *p = L->next;
while (p) {
    LNode *r = p->next;          // ★ 先备份后继
    p->next = q;                 // 掉转方向
    q = p;                       // 前驱前移
    p = r;                       // 当前前移
}
L->next = q;                     // ★ 挂回头结点
```

### 循环队列

```cpp
元素个数 = (rear - front + MAXSIZE) % MAXSIZE
判空     = (rear == front)
判满     = ((rear + 1) % MAXSIZE == front)   // 牺牲一个单元
入队改 rear，出队改 front
```

### 变量该定义在哪

> 问自己：「这个变量的值，下一轮还需要吗？」
>
> - **需要** → 定义在**循环外**（尾指针 `rb`、`rc`）
> - **不需要** → 定义在**循环内**（备份指针 `q`、`r`）