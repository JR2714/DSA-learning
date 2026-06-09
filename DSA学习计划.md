# 数据结构与算法 学习计划（C++ 版）

> **总时长**：约 16 周（3~4 个月） | **每日投入**：1~2 小时  
> **主语言**：C++（指针、动态内存、RAII、智能指针） | **对比语言**：Python（字符串、递归、高级算法思想）  
> **主教材**：Mark Allen Weiss, *Data Structures and Algorithm Analysis in C++* (4th Edition)  
> **学习顺序**：以 Weiss 教材章节顺序为主线

---

## 目录

1. [前言](#前言)
2. [阶段 0：C++ 基础回顾 — Weiss Ch.1（已完成 ✅）](#阶段-0c-基础回顾--weiss-ch1已完成-)
3. [阶段 1：算法分析 — Weiss Ch.2（第 1~2 周）](#阶段-1算法分析--weiss-ch2第-12-周)
4. [阶段 2：表、栈、队列 — Weiss Ch.3（第 2~4 周）](#阶段-2表栈队列--weiss-ch3第-24-周)
5. [阶段 3：树 — Weiss Ch.4（第 4~6 周）](#阶段-3树--weiss-ch4第-46-周)
6. [阶段 4：散列 — Weiss Ch.5（第 6~7 周）](#阶段-4散列--weiss-ch5第-67-周)
7. [阶段 5：优先队列（堆）— Weiss Ch.6（第 7~8 周）](#阶段-5优先队列堆--weiss-ch6第-78-周)
8. [阶段 6：排序 — Weiss Ch.7（第 8~10 周）](#阶段-6排序--weiss-ch7第-810-周)
9. [阶段 7：不相交集 — Weiss Ch.8（第 10~11 周）](#阶段-7不相交集--weiss-ch8第-1011-周)
10. [阶段 8：图算法 — Weiss Ch.9（第 11~13 周）](#阶段-8图算法--weiss-ch9第-1113-周)
11. [阶段 9：算法设计技术 — Weiss Ch.10（第 13~15 周）](#阶段-9算法设计技术--weiss-ch10第-1315-周)
12. [阶段 10：摊还分析 + 高级数据结构 + 总复习 — Weiss Ch.11~12（第 15~16 周）](#阶段-10摊还分析--高级数据结构--总复习--weiss-ch1112第-1516-周)
13. [附录 A：周计划表](#附录-a周计划表)
14. [附录 B：LeetCode 题号清单（按 Weiss 章节）](#附录-bleetcode-题号清单按-weiss-章节)
15. [附录 C：常见误区与解决](#附录-c常见误区与解决)
16. [附录 D：面试快速复习路线](#附录-d面试快速复习路线)

---

## 前言

### 为什么用 C++ 学数据结构？

- **裸指针与动态内存**：`new`/`delete`、`malloc`/`free` 让你亲眼看到内存从何而来、何时归还，形成对"数据存在哪里"的直觉。
- **析构函数与 RAII**：对象生命周期可控，资源获取即初始化（Resource Acquisition Is Initialization）是 C++ 的核心哲学，理解它对任何语言的内存管理都有帮助。
- **STL 源码层**：`std::vector`、`std::list`、`std::unordered_map` 的底层结构就是你要学的数据结构，学完理论回头看 STL 实现是最高效的验证方式。
- **面试区分度**：用 C++ 写 DSA 在面试中天然展示你对内存的理解深度。

### 为什么以 Weiss 教材顺序为主线？

Weiss 的章节安排体现了严谨的递进逻辑：

1. **先用树（Ch.4）建立结构性质与指针操作的深度理解**——树的遍历、插入、删除需要递归和指针操作，是线性结构到非线性结构的自然过渡
2. **再学散列（Ch.5）理解"空间换时间"**——哈希表以 O(1) 为目标，与树的 O(log n) 形成对比
3. **堆（Ch.6）是树和数组的交叉应用**——完全二叉树的数组存储，是 Ch.4 和 Ch.3 知识的融合
4. **排序（Ch.7）是前面所有知识的综合**——堆排序用 Ch.6，归并排序的分治思想铺垫 Ch.10
5. **不相交集（Ch.8）为 Kruskal 算法做准备**——放在图之前学，图的 MST 算法才能讲透
6. **摊还分析（Ch.11）后置**——涉及二项队列、斐波那契堆等高级结构，需要前面所有基础

### 先决条件

- 能用 C++ 写出带 `main()` 的完整程序并编译运行（g++ / clang++ / MSVC）
- 了解基本语法：循环、分支、函数、数组
- Python 3.x 安装（仅用于对比示例，非必须）

### 推荐开发环境

| 工具 | 用途 |
|------|------|
| GCC 12+ / Clang 16+ | 编译器，推荐启用 `-std=c++17` |
| CMake 3.20+ | 构建系统（小型项目用） |
| Valgrind / AddressSanitizer (`-fsanitize=address`) | 内存错误检测 |
| VS Code / CLion | 编辑器 |
| LeetCode / NowCoder | 在线判题 |

---

## 阶段 0：C++ 基础回顾 — Weiss Ch.1（已完成 ✅）

> **完成日期**：2026-06-06 ~ 2026-06-09  
> **对应 Weiss**：Chapter 1 — Programming: A General Overview

### 已学内容

| 主题 | 对应 Weiss 节 | 要点 |
|------|-------------|------|
| 指针基础 | §1.5 C++ Details | `*`、`&`、指针算术、`nullptr`、指针与数组的关系 |
| 引用 | §1.5 Lvalues/Rvalues/References | 左值引用 `T&`、const 引用、与指针的区别 |
| 动态内存 | §1.4~1.5 | `new`/`delete`、`new[]`/`delete[]`、内存泄漏的概念 |
| 类与对象 | §1.4 C++ Classes | 构造/析构函数、拷贝构造、赋值运算符、The Big-Five |
| RAII | §1.4~1.5 | 资源在构造函数中获取，在析构函数中释放—用类管理动态数组 |
| 模板基础 | §1.6 Templates | 函数模板、类模板—写一个通用的 `DynamicArray<T>` |
| STL 概览 | §1.4 `vector`/`string` + §3.3 | `vector`、`list`、`map`、`unordered_map`、`stack`、`queue` |

### 练习文件

- `C++_Basic/pointer.cpp` — 指针基础
- `C++_Basic/reference.cpp` — 引用
- `C++_Basic/dynamic_memory.cpp` — 动态内存
- `C++_Basic/class_objects.cpp` — 类与对象（Rule of Three/Five）
- `C++_Basic/template_basics.cpp` — 模板基础
- `C++_Basic/stl_overview.cpp` — STL 概览

---

## 阶段 1：算法分析 — Weiss Ch.2（第 1~2 周）

### 学习目标

能用大 O 表示法分析任何一段 C++ 代码的时间/空间复杂度，理解 STL 容器操作背后的复杂度。Weiss Ch.2 是全书的理论基础。

### 对应 Weiss 章节

| 节 | 内容 | 掌握程度 |
|----|------|----------|
| §2.1 Mathematical Background | 指数、对数、级数、模运算 | 精读 |
| §2.2 Model | 计算模型假设 | 理解 |
| §2.3 What to Analyze | 分析什么（时间、空间、最坏/平均） | 精读 |
| §2.4 Running-Time Calculations | 最大子序列和问题、对数时间、最坏情况局限性 | 精读 + 手算 |

### 知识点

- **时间复杂度**：O(1)、O(log n)、O(n)、O(n log n)、O(n²)、O(2ⁿ)
- **空间复杂度**：考虑递归调用栈、临时数组、STL 容器的额外开销
- **最好/最坏/平均情况**：顺序查找最好 O(1) vs 最坏 O(n)；快速排序最好 O(n log n) vs 最坏 O(n²)
- **对数时间识别**：二分查找、欧几里得算法、幂运算
- **STL 复杂度速查**：`vector` 随机访问 O(1)、`list` 插入 O(1)、`map` 查找 O(log n)、`unordered_map` 平均 O(1)

### 核心代码示例

**最大子序列和问题的四种解法（Weiss §2.4.3）：**

```cpp
#include <vector>
#include <algorithm>

// 解法 1：O(n³) 暴力枚举
int max_subseq_sum_cubic(const std::vector<int>& a) {
    int max_sum = 0;
    for (size_t i = 0; i < a.size(); ++i)
        for (size_t j = i; j < a.size(); ++j) {
            int this_sum = 0;
            for (size_t k = i; k <= j; ++k)
                this_sum += a[k];
            if (this_sum > max_sum) max_sum = this_sum;
        }
    return max_sum;
}

// 解法 2：O(n²) 优化内层循环
int max_subseq_sum_quadratic(const std::vector<int>& a) {
    int max_sum = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        int this_sum = 0;
        for (size_t j = i; j < a.size(); ++j) {
            this_sum += a[j];
            if (this_sum > max_sum) max_sum = this_sum;
        }
    }
    return max_sum;
}

// 解法 3：O(n log n) 分治法
int max_subseq_sum_rec(const std::vector<int>& a, int left, int right) {
    if (left == right)
        return std::max(0, a[left]);
    int center = left + (right - left) / 2;
    int max_left  = max_subseq_sum_rec(a, left, center);
    int max_right = max_subseq_sum_rec(a, center + 1, right);

    int left_border = 0, sum = 0;
    for (int i = center; i >= left; --i)
        left_border = std::max(left_border, sum += a[i]);
    int right_border = 0; sum = 0;
    for (int i = center + 1; i <= right; ++i)
        right_border = std::max(right_border, sum += a[i]);

    return std::max({max_left, max_right, left_border + right_border});
}

// 解法 4：O(n) Kadane 算法
int max_subseq_sum_linear(const std::vector<int>& a) {
    int max_sum = 0, this_sum = 0;
    for (int x : a) {
        this_sum += x;
        if (this_sum > max_sum) max_sum = this_sum;
        if (this_sum < 0) this_sum = 0;  // 关键：负前缀丢弃
    }
    return max_sum;
}
```

**二分查找（对数时间分析——Weiss §2.4.4）：**

```cpp
// 迭代版 — O(log n) 时间，O(1) 空间
int binary_search(const std::vector<int>& arr, int target) {
    int lo = 0, hi = arr.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

// 递归版 — O(log n) 时间，O(log n) 空间（栈帧）
int binary_search_rec(const std::vector<int>& arr, int target, int lo, int hi) {
    if (lo > hi) return -1;
    int mid = lo + (hi - lo) / 2;
    if (arr[mid] == target) return mid;
    if (arr[mid] < target) return binary_search_rec(arr, target, mid + 1, hi);
    return binary_search_rec(arr, target, lo, mid - 1);
}
```

### 推荐资源

- **Weiss Ch.2** — 主读
- 《算法导论》第 3 章（渐近符号）
- [bigocheatsheet.com](https://www.bigocheatsheet.com/) — 数据结构与算法复杂度速查表

### 实践任务

| 类型 | 内容 |
|------|------|
| 分析题 | 分析 `vector::push_back` 扩容时的均摊复杂度，写代码验证 |
| 编程题 | 实现二分查找（迭代版 + 递归版），分析各自的空间开销 |
| 编程题 | 用四种方法解最大子序列和问题，benchmark 对比 10^5 规模下的运行时间 |
| 小练习 | 对自己写的每个函数注释时间/空间复杂度 |

### 自检清单

- [ ] 为什么递归版二分查找空间 O(log n)，而迭代版 O(1)？
- [ ] `std::map::operator[]` 与 `std::unordered_map::operator[]` 复杂度各是多少？
- [ ] 最大子序列和的分治法为什么是 O(n log n)？画出递归树解释。
- [ ] 能解释为什么 `vector` 在尾部插入是均摊 O(1) 吗？

---

## 阶段 2：表、栈、队列 — Weiss Ch.3（第 2~4 周）

### 学习目标

用 C++ 指针实现所有基础线性结构，重点体会 **手动内存管理** 的每个细节。Weiss Ch.3 涵盖了 ADT 概念和两种实现方式（数组 vs 链表），以及 STL 中 `vector` 和 `list` 的底层实现。

### 对应 Weiss 章节

| 节 | 内容 | 掌握程度 |
|----|------|----------|
| §3.1 Abstract Data Types | ADT 概念 | 理解 |
| §3.2 The List ADT | 数组实现 + 简单链表 | 精读 + 手写 |
| §3.3 `vector` and `list` in the STL | 迭代器、`const_iterator` | 精读 |
| §3.4 Implementation of `vector` | `vector` 底层实现 | 精读 |
| §3.5 Implementation of `list` | `list` 底层实现 | 精读 |
| §3.6 The Stack ADT | 栈的模型、实现、应用（括号匹配、表达式求值） | 精读 + 手写 |
| §3.7 The Queue ADT | 队列的模型、数组实现（环形缓冲）、应用 | 精读 + 手写 |

### 知识点

| 主题 | 要点 |
|------|------|
| **ADT 概念** | 数据抽象：分离"做什么"与"怎么做" |
| **动态数组** | 扩容策略（1.5x vs 2x）、`realloc` 的陷阱、与 `std::vector` 的对比 |
| **单向链表** | 节点定义、头插/尾插/中间删除、反转（迭代/递归）、检测环（快慢指针） |
| **双向链表** | `prev` 指针维护、哨兵节点（dummy node）简化边界处理 |
| **循环链表** | 尾节点指向头、判断空链表、约瑟夫环问题 |
| **栈** | LIFO、用数组/链表实现、表达式求值（中缀转后缀） |
| **队列** | FIFO、用数组（环形缓冲）/链表实现、双端队列（deque） |

### 核心代码示例

**单链表节点（指针版——注意析构链）：**

```cpp
template <typename T>
struct ListNode {
    T val;
    ListNode* next;
    ListNode(T x) : val(x), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    ListNode<T>* head_;

    void delete_list(ListNode<T>* node) {
        while (node) {
            ListNode<T>* tmp = node->next;
            delete node;
            node = tmp;
        }
    }

public:
    LinkedList() : head_(nullptr) {}
    ~LinkedList() { delete_list(head_); }

    // 禁止拷贝（避免浅拷贝导致 double-free）
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    void push_front(T val) {
        ListNode<T>* node = new ListNode<T>(val);
        node->next = head_;
        head_ = node;
    }

    bool remove(T val) {
        ListNode<T>** indirect = &head_;  // 指针的指针，统一处理头节点删除
        while (*indirect) {
            if ((*indirect)->val == val) {
                ListNode<T>* tmp = *indirect;
                *indirect = (*indirect)->next;
                delete tmp;
                return true;
            }
            indirect = &(*indirect)->next;
        }
        return false;
    }

    ListNode<T>* get_head() const { return head_; }
};
```

**反转单链表（迭代版——O(1) 额外空间）：**

```cpp
ListNode<int>* reverse_list(ListNode<int>* head) {
    ListNode<int>* prev = nullptr;
    ListNode<int>* curr = head;
    while (curr) {
        ListNode<int>* next = curr->next;  // 保存下一个节点
        curr->next = prev;                 // 反转指针
        prev = curr;
        curr = next;
    }
    return prev;  // 新的头节点
}
```

**对比 Python：**

```python
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

def reverse_list(head):
    prev, curr = None, head
    while curr:
        nxt = curr.next
        curr.next = prev
        prev = curr
        curr = nxt
    return prev
```

> C++ 版本的 `delete` 控制是关键——释放旧链表时必须遍历释放每个节点，避免只释放头节点导致其余节点泄漏。

### 推荐资源

- **Weiss Ch.3** — 主读
- LeetCode 探索卡片：[链表](https://leetcode.com/explore/learn/card/linked-list/)

### 实践任务

| 类型 | 内容 |
|------|------|
| 编程题 | 实现**带迭代器的双向链表**（`begin()`/`end()`、`++`、`--`），含拷贝/移动语义 |
| 编程题 | 基于链表实现栈和队列，对比数组版本的性能（用 `std::chrono` 计时） |
| 编程题 | 检测链表环的入口节点（LeetCode 142） |
| 编程题 | 用栈实现中缀表达式转后缀并求值 |
| 小项目 | 实现一个 LRU 缓存（结合哈希表 + 双向链表），注意析构时释放两个结构的节点 |

### 内存调试练习

用 AddressSanitizer 检测常见错误：

```bash
g++ -std=c++17 -fsanitize=address -g linked_list.cpp -o bin/linked_list
./bin/linked_list
```

常见检测到的错误：use-after-free、heap-buffer-overflow、double-free。

### 自检清单

- [ ] 能否无误地写出无内存泄漏的单链表完整实现（含析构、拷贝、移动）？
- [ ] 链表反转的递归版和迭代版空间复杂度各是多少？为什么？
- [ ] 为什么删除链表节点时要用「指针的指针」或「前驱节点」？
- [ ] `valgrind` 或 ASan 能否熟练地检测到内存泄漏和非法访问？

---

## 阶段 3：树 — Weiss Ch.4（第 4~6 周）

### 学习目标

用 C++ 实现 BST → AVL 的完整演化，理解伸展树和 B 树的原理。这是全书最长的章节之一，也是从线性结构到非线性结构的关键转折点。

### 对应 Weiss 章节

| 节 | 内容 | 掌握程度 |
|----|------|----------|
| §4.1 Preliminaries | 树的基本概念、实现方式、树的遍历 | 精读 |
| §4.2 Binary Trees | 二叉树实现、表达式树 | 精读 + 手写 |
| §4.3 The Search Tree ADT—BST | `contains`/`findMin`/`findMax`/`insert`/`remove`、平均情况分析 | 精读 + 手写 |
| §4.4 AVL Trees | 单旋转、双旋转（LL/RR/LR/RL） | 精读 + 手写旋转 |
| §4.5 Splay Trees | 伸展操作（zig/zag/zig-zig/zig-zag） | 理解原理 |
| §4.6 Tree Traversals (Revisited) | 前/中/后序的统一视角 | 精读 |
| §4.7 B-Trees | B 树的插入/分裂、B+ 树简介 | 理解原理 |
| §4.8 Sets and Maps in the Standard Library | `std::set`/`std::map` 及底层实现 | 了解 |

### 知识点

| 主题 | 要点 |
|------|------|
| 树的基本概念 | 节点、深度、高度、满二叉树、完全二叉树、二叉树的性质 |
| 二叉树的遍历 | 前/中/后序（递归 + 迭代栈）、层序（队列）、Morris 遍历（O(1) 空间） |
| 二叉搜索树（BST）| 插入、删除（3 种情况）、查找、验证、第 k 小元素 |
| AVL 树 | 平衡因子、四种旋转（LL/RR/LR/RL）、插入后旋转修复 |
| 伸展树 | 摊还 O(log n)，最近访问的节点移到根 |
| B 树 | m 阶 B 树的插入/分裂、B+ 树的叶子链表——数据库索引原理 |
| STL 关联容器 | `std::set`/`std::map` 基于红黑树，O(log n) |

### 核心代码示例

**BST 节点与析构（后序遍历释放）：**

```cpp
template <typename T>
struct TreeNode {
    T val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(T x) : val(x), left(nullptr), right(nullptr) {}
};

template <typename T>
class BST {
private:
    TreeNode<T>* root_;

    void destroy(TreeNode<T>* node) {
        if (!node) return;
        destroy(node->left);   // 后序遍历确保先释放子树
        destroy(node->right);
        delete node;
    }

    TreeNode<T>* insert(TreeNode<T>* node, T val) {
        if (!node) return new TreeNode<T>(val);
        if (val < node->val)
            node->left = insert(node->left, val);
        else if (val > node->val)
            node->right = insert(node->right, val);
        return node;
    }

    TreeNode<T>* find_min(TreeNode<T>* node) {
        while (node && node->left)
            node = node->left;
        return node;
    }

    TreeNode<T>* remove(TreeNode<T>* node, T val) {
        if (!node) return nullptr;
        if (val < node->val) {
            node->left = remove(node->left, val);
        } else if (val > node->val) {
            node->right = remove(node->right, val);
        } else {
            // 情况 1 & 2：0 或 1 个子节点
            if (!node->left) {
                TreeNode<T>* right = node->right;
                delete node;
                return right;
            }
            if (!node->right) {
                TreeNode<T>* left = node->left;
                delete node;
                return left;
            }
            // 情况 3：两个子节点 → 找后继
            TreeNode<T>* successor = find_min(node->right);
            node->val = successor->val;
            node->right = remove(node->right, successor->val);
        }
        return node;
    }

public:
    BST() : root_(nullptr) {}
    ~BST() { destroy(root_); }

    void insert(T val) { root_ = insert(root_, val); }
    void remove(T val) { root_ = remove(root_, val); }
};
```

**AVL 旋转（四种旋转模式）：**

```cpp
template <typename T>
int height(TreeNode<T>* node) {
    return node ? node->height : -1;
}

template <typename T>
TreeNode<T>* rotate_right(TreeNode<T>* y) {
    TreeNode<T>* x = y->left;
    TreeNode<T>* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = 1 + std::max(height(y->left), height(y->right));
    x->height = 1 + std::max(height(x->left), height(x->right));
    return x;  // 新根
}

template <typename T>
TreeNode<T>* rotate_left(TreeNode<T>* x) {
    TreeNode<T>* y = x->right;
    TreeNode<T>* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = 1 + std::max(height(x->left), height(x->right));
    y->height = 1 + std::max(height(y->left), height(y->right));
    return y;  // 新根
}

// LL: 右旋  |  RR: 左旋
// LR: 先左旋左子树，再右旋根
// RL: 先右旋右子树，再左旋根
```

**对比 Python（中序遍历——语法更简洁）：**

```python
def inorder(node):
    if not node:
        return
    inorder(node.left)
    print(node.val)
    inorder(node.right)

# Python 生成器版本
def inorder_gen(node):
    if node:
        yield from inorder_gen(node.left)
        yield node.val
        yield from inorder_gen(node.right)
```

> C++ 的迭代器实现需要显式维护一个栈或使用 Morris 遍历——这恰是理解底层的好机会。

### 推荐资源

- **Weiss Ch.4** — 主读
- [Visualgo.net BST](https://visualgo.net/en/bst) — 交互式 BST/AVL 演示
- 《算法导论》第 12、13 章（BST、红黑树）

### 实践任务

| 类型 | 内容 |
|------|------|
| 编程题 | 实现完整的 BST（含析构、拷贝、移动），通过 LeetCode 98（验证 BST） |
| 编程题 | 实现 AVL 树的插入（含四种旋转），用层序遍历打印验证平衡性 |
| 编程题 | 二叉树的序列化与反序列化（LeetCode 297）——**注意避免内存泄漏** |
| 编程题 | 实现表达式树：给定后缀表达式，构建表达式树并求值 |
| 小项目 | 实现一个简单的 **B 树**（阶数 m=5），支持插入和范围查询 |

### 自检清单

- [ ] BST 删除节点的三种情况分别如何处理？
- [ ] AVL 树的四种旋转各对应什么不平衡场景？为什么 LR 需要两次旋转？
- [ ] 伸展树的摊还分析为什么是 O(log n)？（直觉理解即可）
- [ ] 为什么树析构必须用后序遍历？用前序会发生什么？
- [ ] B 树相比 BST 在磁盘 I/O 场景下的优势是什么？

---

## 阶段 4：散列 — Weiss Ch.5（第 6~7 周）

### 学习目标

深入理解哈希表原理，并用 C++ 实现一个可用、无内存泄漏的 HashMap。Weiss Ch.5 涵盖了从散列函数设计到开放寻址法、再散列、完美散列的完整讨论。

### 对应 Weiss 章节

| 节 | 内容 | 掌握程度 |
|----|------|----------|
| §5.1 General Idea | 散列的基本思想 | 理解 |
| §5.2 Hash Function | 对整数（取模）、字符串（多项式）的散列函数 | 精读 |
| §5.3 Separate Chaining | 链地址法（每个桶是链表） | 精读 + 手写 |
| §5.4 Hash Tables without Linked Lists | 线性探测、平方探测、双散列 | 精读 + 手写一种 |
| §5.5 Rehashing | 负载因子 > 阈值时扩容、重新散列 | 精读 + 手写 |
| §5.6 Hash Tables in the Standard Library | `std::unordered_map`/`unordered_set` | 了解 |
| §5.7 Worst-Case O(1) Access | 完美散列、Cuckoo 散列、Hopscotch 散列 | 略读 |
| §5.8 Universal Hashing | 全域散列 | 略读 |
| §5.9 Extendible Hashing | 可扩展散列 | 略读 |

### 知识点

| 主题 | 要点 |
|------|------|
| 散列函数 | 对整数（取模）、字符串（多项式散列 djb2）、泛型键的 `std::hash` |
| 冲突解决 | **链地址法**（每个桶是链表）、**开放寻址法**（线性探测、平方探测、双散列） |
| 负载因子与 rehash | 负载因子 > 0.75 时扩容、重新散列所有键 |
| 删除的坑 | 开放寻址法中删除必须用"墓碑"标记（lazy deletion） |
| STL 对照 | `std::unordered_map` 默认用链地址法，bucket 数组 + 正向链表 |

### 核心代码示例

**简化版 HashMap（链地址法，含 rehash）：**

```cpp
template <typename K, typename V>
class HashMap {
private:
    struct Node {
        K key;
        V value;
        Node* next;
        Node(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
    };

    static constexpr double LOAD_FACTOR = 0.75;
    Node** buckets_;
    size_t bucket_count_;
    size_t size_;

    size_t hash(const K& key) const {
        return std::hash<K>{}(key) % bucket_count_;
    }

    void rehash() {
        size_t old_count = bucket_count_;
        Node** old_buckets = buckets_;
        bucket_count_ = bucket_count_ * 2 + 1;  // 保持质数-ish
        buckets_ = new Node*[bucket_count_]();
        size_ = 0;

        for (size_t i = 0; i < old_count; ++i) {
            Node* node = old_buckets[i];
            while (node) {
                insert(node->key, node->value);
                Node* tmp = node->next;
                delete node;
                node = tmp;
            }
        }
        delete[] old_buckets;
    }

public:
    HashMap(size_t initial_buckets = 10007) : bucket_count_(initial_buckets), size_(0) {
        buckets_ = new Node*[bucket_count_]();
    }

    ~HashMap() {
        for (size_t i = 0; i < bucket_count_; ++i) {
            Node* node = buckets_[i];
            while (node) {
                Node* tmp = node->next;
                delete node;
                node = tmp;
            }
        }
        delete[] buckets_;
    }

    void insert(const K& key, const V& value) {
        if (static_cast<double>(size_ + 1) / bucket_count_ > LOAD_FACTOR)
            rehash();
        size_t idx = hash(key);
        Node* node = buckets_[idx];
        while (node) {
            if (node->key == key) { node->value = value; return; }
            node = node->next;
        }
        Node* new_node = new Node(key, value);
        new_node->next = buckets_[idx];
        buckets_[idx] = new_node;
        ++size_;
    }

    V* find(const K& key) {
        size_t idx = hash(key);
        Node* node = buckets_[idx];
        while (node) {
            if (node->key == key) return &node->value;
            node = node->next;
        }
        return nullptr;
    }

    bool remove(const K& key) {
        size_t idx = hash(key);
        Node** indirect = &buckets_[idx];
        while (*indirect) {
            if ((*indirect)->key == key) {
                Node* tmp = *indirect;
                *indirect = (*indirect)->next;
                delete tmp;
                --size_;
                return true;
            }
            indirect = &(*indirect)->next;
        }
        return false;
    }

    size_t size() const { return size_; }
};
```

### 推荐资源

- **Weiss Ch.5** — 主读
- 《算法导论》第 11 章
- [cppreference: std::unordered_map](https://en.cppreference.com/w/cpp/container/unordered_map)

### 实践任务

| 类型 | 内容 |
|------|------|
| 编程题 | 实现链地址法 HashMap（含动态 rehash），负载因子 >= 0.75 自动扩容 |
| 编程题 | 实现开放寻址法的 HashMap（线性探测 + 墓碑标记） |
| 编程题 | 比较链地址法 vs 开放寻址法在不同负载因子下的性能 |
| 编程题 | 两数之和（LeetCode 1）——用 `std::unordered_map` 和手写 HashMap 各做一遍 |

### 自检清单

- [ ] 链地址法与开放寻址法各有什么优缺点？
- [ ] 为什么 rehash 时不能简单地复制节点？
- [ ] 开放寻址法中，删除为什么必须是"软删除"？
- [ ] 为什么桶数通常选质数？
- [ ] 手写的 HashMap 能否通过 valgrind 检查？

---

## 阶段 5：优先队列（堆）— Weiss Ch.6（第 7~8 周）

### 学习目标

用数组实现二叉堆，并理解 `std::priority_queue` 的底层机制。Weiss Ch.6 涵盖二叉堆到二项队列的多层堆结构，为后续排序和摊还分析做准备。

### 对应 Weiss 章节

| 节 | 内容 | 掌握程度 |
|----|------|----------|
| §6.1 Model | 优先队列 ADT 的定义 | 理解 |
| §6.2 Simple Implementations | 朴素实现及其复杂度对比 | 理解 |
| §6.3 Binary Heap | 结构性质、堆序性质、`insert`/`deleteMin`/`buildHeap` | **精读 + 手写** |
| §6.4 Applications | 选择问题、事件模拟 | 理解 |
| §6.5 d-Heaps | d 叉堆 | 了解 |
| §6.6 Leftist Heaps | 左式堆的性质与操作 | 理解原理 |
| §6.7 Skew Heaps | 斜堆 | 了解 |
| §6.8 Binomial Queues | 二项队列的结构、操作、实现 | 理解原理 |
| §6.9 Priority Queues in the Standard Library | `std::priority_queue` | 了解 |

### 知识点

| 主题 | 要点 |
|------|------|
| 堆的性质 | 结构性质（完全二叉树用数组存储）、堆序性质（大/小顶堆） |
| 数组索引 | 父 `(i-1)/2`、左子 `2i+1`、右子 `2i+2` |
| 基本操作 | `insert`（上滤 percolate up）、`deleteMin`（下滤 percolate down）、`buildHeap`（批量建堆 O(n)） |
| 堆排序 | 建堆 + 反复删除 → 在数组上原地排序 |
| `std::priority_queue` | 默认 `std::vector` 底层 + `std::less` 形成大顶堆 |
| 自定义比较器 | `std::greater` 变小顶堆、自定义 `operator()` |
| 对顶堆技巧 | 数据流中位数（一个大顶堆 + 一个小顶堆） |

### 核心代码示例

**数组实现二叉堆（小顶堆）：**

```cpp
template <typename T>
class MinHeap {
private:
    T* data_;
    size_t capacity_;
    size_t size_;

    void sift_up(size_t i) {
        while (i > 0) {
            size_t parent = (i - 1) / 2;
            if (data_[i] >= data_[parent]) break;
            std::swap(data_[i], data_[parent]);
            i = parent;
        }
    }

    void sift_down(size_t i) {
        while (true) {
            size_t left = 2 * i + 1;
            size_t right = 2 * i + 2;
            size_t smallest = i;
            if (left < size_ && data_[left] < data_[smallest])
                smallest = left;
            if (right < size_ && data_[right] < data_[smallest])
                smallest = right;
            if (smallest == i) break;
            std::swap(data_[i], data_[smallest]);
            i = smallest;
        }
    }

    void resize() {
        size_t new_cap = capacity_ * 2;
        T* new_data = new T[new_cap];
        for (size_t i = 0; i < size_; ++i)
            new_data[i] = data_[i];
        delete[] data_;
        data_ = new_data;
        capacity_ = new_cap;
    }

public:
    MinHeap(size_t cap = 16) : capacity_(cap), size_(0) {
        data_ = new T[capacity_];
    }

    ~MinHeap() { delete[] data_; }

    // 批量建堆 O(n)——Floyd 算法（Weiss §6.3）
    MinHeap(T arr[], size_t n) : capacity_(n * 2), size_(n) {
        data_ = new T[capacity_];
        for (size_t i = 0; i < n; ++i) data_[i] = arr[i];
        for (size_t i = n / 2; i > 0; --i)
            sift_down(i - 1);
    }

    void push(T val) {
        if (size_ == capacity_) resize();
        data_[size_] = val;
        sift_up(size_);
        ++size_;
    }

    T top() const {
        if (size_ == 0) throw std::runtime_error("heap empty");
        return data_[0];
    }

    void pop() {
        if (size_ == 0) throw std::runtime_error("heap empty");
        data_[0] = data_[size_ - 1];
        --size_;
        if (size_ > 0) sift_down(0);
    }

    bool empty() const { return size_ == 0; }
    size_t size() const { return size_; }
};
```

### 推荐资源

- **Weiss Ch.6** — 主读
- 《算法导论》第 6 章
- cppreference：[std::priority_queue](https://en.cppreference.com/w/cpp/container/priority_queue)

### 实践任务

| 类型 | 内容 |
|------|------|
| 编程题 | 实现 `MinHeap<T>` 的拷贝构造和移动构造 |
| 编程题 | 数据流中的第 K 大元素（LeetCode 703）——用优先队列 |
| 编程题 | 合并 K 个有序链表（LeetCode 23）——用小顶堆优化到 O(N log K) |
| 小项目 | 实现优先队列的"修改优先级"操作（增加哈希表索引→位置映射），用于 Dijkstra 算法 |

### 自检清单

- [ ] 为什么批量建堆 `buildHeap` 是 O(n) 而不是 O(n log n)？（Weiss §6.3）
- [ ] `deleteMin` 操作把最后一个元素放到堆顶再下滤，为什么正确？
- [ ] 二叉堆 vs 左式堆 vs 二项队列，各自的优势和适用场景？
- [ ] `std::priority_queue` 为什么不支持 `decreaseKey` 操作？

---

## 阶段 6：排序 — Weiss Ch.7（第 8~10 周）

### 学习目标

掌握从 O(n²) 到 O(n log n) 到 O(n) 的全系列排序算法及其 C++ 实现，深入理解下界分析。排序是前面所有知识的综合应用——堆排序用 Ch.6 的堆，归并排序的分治思想铺垫 Ch.10。

### 对应 Weiss 章节

| 节 | 内容 | 掌握程度 |
|----|------|----------|
| §7.1 Preliminaries | 排序预备知识 | 理解 |
| §7.2 Insertion Sort | 插入排序及分析 | 精读 |
| §7.3 Lower Bound for Simple Sorts | 简单排序的 O(n²) 下界 | 理解 |
| §7.4 Shellsort | 希尔排序 | 精读 |
| §7.5 Heapsort | 堆排序（用 Ch.6 的堆） | 精读 + 手写 |
| §7.6 Mergesort | 归并排序（递归 + 迭代） | 精读 + 手写 |
| §7.7 Quicksort | 快速排序（pivot 选择、分区策略、分析、快速选择） | **精读 + 手写** |
| §7.8 General Lower Bound for Sorting | 比较排序的 O(n log n) 下界（决策树） | 理解 |
| §7.9 Decision-Tree Lower Bounds for Selection | 选择问题的下界 | 略读 |
| §7.10 Adversary Lower Bounds | 对手下界 | 略读 |
| §7.11 Linear-Time Sorts | 桶排序、基数排序 | 精读 |
| §7.12 External Sorting | 外部排序（多路归并、多相归并、替换选择） | 理解原理 |

### 知识点

| 主题 | 要点 |
|------|------|
| 插入排序 | O(n²)，近乎有序数组 O(n)，小数组的实际最优选择 |
| 希尔排序 | 递减增量序列，打破 O(n²) 屏障的先驱 |
| 堆排序 | 建堆 O(n) + 反复删除 O(n log n)，不稳定、原地 |
| 归并排序 | 分治法、O(n log n)、需要 O(n) 临时数组、稳定排序、非递归版（自底向上） |
| 快速排序 | 分区（Lomuto vs Hoare）、pivot 选择策略（随机化/三数取中）、最坏情况 O(n²) |
| 排序下界 | 基于比较的排序最少需要 Ω(n log n) 次比较（决策树证明） |
| 线性时间排序 | 桶排序、基数排序——不基于比较，需要额外假设 |
| C++ 排序 | `std::sort` 的内省排序（IntroSort = 快速 + 堆 + 插入排序的混合） |
| 外部排序 | 大文件分块排序 + 多路归并 |

### 核心代码示例

**快速排序（Hoare 分区 + 三数取中 pivot）：**

```cpp
#include <algorithm>

template <typename T>
int partition(T arr[], int lo, int hi) {
    // 三数取中（Weiss §7.7）
    int mid = lo + (hi - lo) / 2;
    if (arr[mid] < arr[lo]) std::swap(arr[lo], arr[mid]);
    if (arr[hi] < arr[lo])  std::swap(arr[lo], arr[hi]);
    if (arr[mid] < arr[hi]) std::swap(arr[mid], arr[hi]);
    T pivot = arr[hi];

    int i = lo - 1;
    for (int j = lo; j < hi; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[hi]);
    return i + 1;
}

template <typename T>
void quicksort(T arr[], int lo, int hi) {
    if (lo >= hi) return;
    int p = partition(arr, lo, hi);
    quicksort(arr, lo, p - 1);
    quicksort(arr, p + 1, hi);
}
```

**归并排序（自底向上迭代版，O(n) 空间，O(1) 栈）：**

```cpp
template <typename T>
void merge(T arr[], T temp[], int lo, int mid, int hi) {
    int i = lo, j = mid + 1, k = lo;
    while (i <= mid && j <= hi)
        temp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= hi)  temp[k++] = arr[j++];
    for (i = lo; i <= hi; ++i) arr[i] = temp[i];
}

template <typename T>
void mergesort_iter(T arr[], int n) {
    T* temp = new T[n];
    for (int size = 1; size < n; size *= 2) {
        for (int lo = 0; lo < n - size; lo += 2 * size) {
            int mid = lo + size - 1;
            int hi = std::min(lo + 2 * size - 1, n - 1);
            merge(arr, temp, lo, mid, hi);
        }
    }
    delete[] temp;
}
```

**快速选择（QuickSelect——Weiss §7.7.6，O(n) 平均时间）：**

```cpp
// 在 arr[lo..hi] 中找第 k 小元素（k 从 0 开始）
template <typename T>
T quickselect(T arr[], int lo, int hi, int k) {
    if (lo == hi) return arr[lo];
    int p = partition(arr, lo, hi);
    if (k == p) return arr[p];
    if (k < p)  return quickselect(arr, lo, p - 1, k);
    return quickselect(arr, p + 1, hi, k);
}
```

### 递归过深时的栈溢出问题

```cpp
// 危险：对于 10^6 个已排序元素，朴素快排会递归 10^6 层 → 栈溢出
// 解决（Weiss §7.7）：
// 1. 先递归较小区间，较大区间用尾递归
// 2. 小区间（<10~20）改用插入排序
// 3. 转迭代版本
```

### 推荐资源

- **Weiss Ch.7** — 主读
- 《算法（第 4 版）》第 2 章（排序）—— 带精美可视化的经典教材
- [Visualgo.net](https://visualgo.net/en/sorting) — 排序可视化

### 实践任务

| 类型 | 内容 |
|------|------|
| 编程题 | 实现插入、希尔、堆、归并、快速、桶/基数排序，**写 benchmark 对比真实耗时**（随机 / 近乎有序 / 大量重复 / 逆序） |
| 编程题 | 实现 QuickSelect，解决 LeetCode 215（数组中第 K 大元素） |
| 编程题 | 用非递归方式实现二叉树的后序遍历（LeetCode 145），体会栈模拟递归 |
| 小项目 | 实现一个**外部排序的原型**：对大文件分块排序 + 多路归并，注意缓冲区管理 |

### 自检清单

- [ ] 高度有序数组快排退化为 O(n²) 的根本原因是什么？pivot 如何选？（Weiss §7.7）
- [ ] 递归版归并排序的总空间消耗是多少（包括栈帧 + 临时数组）？
- [ ] 堆排序为什么是不稳定的？画图说明。
- [ ] 为什么基于比较的排序下界是 Ω(n log n)？（决策树深度）
- [ ] 基数排序的时间复杂度为什么是 O(d·(n+k)) 而非 O(n log n)？它"绕过"了比较下界吗？
- [ ] `std::sort` 为什么用 IntroSort 而非纯快排？

---

## 阶段 7：不相交集 — Weiss Ch.8（第 10~11 周）

### 学习目标

掌握并查集（Union-Find）数据结构，理解灵巧求并 + 路径压缩如何达到几乎 O(1) 的均摊性能。这是 Kruskal 算法的核心组件，必须在图算法之前学好。

### 对应 Weiss 章节

| 节 | 内容 | 掌握程度 |
|----|------|----------|
| §8.1 Equivalence Relations | 等价关系的定义 | 理解 |
| §8.2 The Dynamic Equivalence Problem | 动态等价问题 | 理解 |
| §8.3 Basic Data Structure | 数组表示法（森林） | 精读 |
| §8.4 Smart Union Algorithms | Union-by-Size / Union-by-Rank | 精读 + 手写 |
| §8.5 Path Compression | `find` 时的路径压缩 | 精读 + 手写 |
| §8.6 Worst Case for Union-by-Rank and Path Compression | 反 Ackermann 函数上界 | 了解结论 |
| §8.7 An Application | 迷宫生成 | 了解 |

### 知识点

| 主题 | 要点 |
|------|------|
| 等价关系 | 自反性、对称性、传递性 |
| 基本表示 | 森林的数组表示：`parent[i]`，根节点的 `parent[root] = root` |
| Union-by-Size/Rank | 小树合并到大树，保证深度 O(log n) |
| 路径压缩 | `find(x)` 时将路径上所有节点直接连到根 |
| 复杂度 | 使用两种优化后：均摊 O(α(n)) ≈ O(1)，α 是反 Ackermann 函数 |
| 应用场景 | Kruskal 最小生成树、连通分量、迷宫生成 |

### 核心代码示例

**并查集（Union-by-Rank + 路径压缩）：**

```cpp
class UnionFind {
private:
    int* parent_;
    int* rank_;
    int n_;

public:
    UnionFind(int n) : n_(n) {
        parent_ = new int[n];
        rank_   = new int[n]();
        for (int i = 0; i < n; ++i) parent_[i] = i;
    }

    ~UnionFind() { delete[] parent_; delete[] rank_; }

    // 查找（含路径压缩——Weiss §8.5）
    int find(int x) {
        if (parent_[x] != x)
            parent_[x] = find(parent_[x]);  // 递归压缩
        return parent_[x];
    }

    // 合并（按秩合并——Weiss §8.4）
    void unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return;
        if (rank_[rx] < rank_[ry])
            parent_[rx] = ry;
        else if (rank_[rx] > rank_[ry])
            parent_[ry] = rx;
        else {
            parent_[ry] = rx;
            ++rank_[rx];
        }
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};
```

### 推荐资源

- **Weiss Ch.8** — 主读
- 《算法导论》第 21 章

### 实践任务

| 类型 | 内容 |
|------|------|
| 编程题 | 实现完整的 UnionFind（含 Union-by-Rank + 路径压缩），测试连通分量计数 |
| 编程题 | 冗余连接（LeetCode 684）——并查集的直接应用 |
| 编程题 | 岛屿数量 II（LeetCode 305，会员题）——动态并查集 |
| 编程题 | 对比有无路径压缩的实际运行时间差异（大数据集） |

### 自检清单

- [ ] 为什么只使用 Union-by-Rank 时 `find` 是 O(log n)？
- [ ] 路径压缩为什么能打破 O(log n) 的界限达到 α(n)？
- [ ] 为什么 Union-Find 不能高效地支持"删除"一条边？（即只增不删）
- [ ] 路径压缩的递归实现有栈溢出风险吗？如何用迭代改写？

---

## 阶段 8：图算法 — Weiss Ch.9（第 11~13 周）

### 学习目标

掌握图的两种存储方式及经典图算法的 C++ 实现，注意大规模图的动态内存管理。Weiss Ch.9 是全书最长的章节之一，涵盖从拓扑排序到网络流的完整图论算法链。

### 对应 Weiss 章节

| 节 | 内容 | 掌握程度 |
|----|------|----------|
| §9.1 Definitions | 图的定义与存储方式（邻接表、邻接矩阵） | 精读 |
| §9.2 Topological Sort | 拓扑排序（入度 + 队列 / DFS 后序） | 精读 + 手写 |
| §9.3 Shortest-Path Algorithms | 无权 BFS、Dijkstra、负权边 Bellman-Ford、无环图、全源 Floyd-Warshall | **精读 + 手写** |
| §9.4 Network Flow Problems | 简单最大流算法 | 理解原理 |
| §9.5 Minimum Spanning Tree | Prim、Kruskal（用 Ch.8 并查集） | 精读 + 手写 |
| §9.6 Applications of DFS | 无向图（双连通性、欧拉回路）、有向图（强连通分量） | 理解 |
| §9.7 Introduction to NP-Completeness | NP 完全性简介 | 略读 |

### 知识点

| 主题 | 要点 |
|------|------|
| 图的存储 | **邻接矩阵**（`int**` 或 `vector<vector<int>>`）、**邻接表**（`vector<list<Edge>>` 或 `Node**` 数组） |
| 遍历 | DFS（递归/栈）、BFS（队列）、拓扑排序（Kahn / DFS 后序） |
| 最短路径 | 无权图 BFS O(V+E)、Dijkstra（优先队列优化 O(E log V)）、Bellman-Ford O(VE)（负权边检测）、Floyd-Warshall O(V³)（全源） |
| 最小生成树 | Prim（与 Dijkstra 的相似性）、Kruskal（用 Ch.8 并查集） |
| 网络流 | Ford-Fulkerson 增广路思想 |
| 图的析构 | 邻接表释放每个链表、邻接矩阵释放每一行 |

### 核心代码示例

**邻接表存储图（指针版）：**

```cpp
struct Edge {
    int to;
    int weight;
    Edge* next;
    Edge(int t, int w) : to(t), weight(w), next(nullptr) {}
};

class Graph {
private:
    int V_;
    Edge** adj_;

public:
    Graph(int V) : V_(V) {
        adj_ = new Edge*[V]();
    }

    ~Graph() {
        for (int i = 0; i < V_; ++i) {
            Edge* e = adj_[i];
            while (e) {
                Edge* tmp = e->next;
                delete e;
                e = tmp;
            }
        }
        delete[] adj_;
    }

    void add_edge(int u, int v, int w) {
        Edge* e = new Edge(v, w);
        e->next = adj_[u];
        adj_[u] = e;
    }

    int V() const { return V_; }
    Edge* adj(int u) const { return adj_[u]; }
};
```

**Dijkstra（`std::priority_queue` 优化 O(E log V)）：**

```cpp
#include <queue>
#include <vector>
#include <limits>

std::vector<int> dijkstra(const Graph& g, int src) {
    const int INF = std::numeric_limits<int>::max();
    std::vector<int> dist(g.V(), INF);
    using P = std::pair<int, int>;  // {距离, 顶点}
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;  // 过时记录
        for (Edge* e = g.adj(u); e; e = e->next) {
            if (dist[u] + e->weight < dist[e->to]) {
                dist[e->to] = dist[u] + e->weight;
                pq.push({dist[e->to], e->to});
            }
        }
    }
    return dist;
}
```

**Kruskal 最小生成树（用 Ch.8 UnionFind）：**

```cpp
#include <algorithm>

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const { return w < other.w; }
};

// 返回 MST 的总权重
int kruskal(std::vector<Edge> edges, int V) {
    std::sort(edges.begin(), edges.end());
    UnionFind uf(V);
    int total_weight = 0, edges_used = 0;

    for (const auto& e : edges) {
        if (uf.find(e.u) != uf.find(e.v)) {
            uf.unite(e.u, e.v);
            total_weight += e.w;
            ++edges_used;
            if (edges_used == V - 1) break;  // MST 完成
        }
    }
    return total_weight;
}
```

### 推荐资源

- **Weiss Ch.9** — 主读
- 《算法导论》第 22~26 章
- CS Academy [Graph Editor](https://csacademy.com/app/graph_editor/) — 画图调试
- 《算法（第 4 版）》第 4 章

### 实践任务

| 类型 | 内容 |
|------|------|
| 编程题 | 课程表（LeetCode 207）——拓扑排序（BFS Kahn + DFS 后序两种实现） |
| 编程题 | 网络延迟时间（LeetCode 743）——Dijkstra |
| 编程题 | K 站中转内最便宜的航班（LeetCode 787）——Bellman-Ford |
| 编程题 | 岛屿数量（LeetCode 200）——网格图上的 DFS/BFS |
| 小项目 | 用邻接表 + 并查集实现 Kruskal 算法，输出最小生成树的边集 |

### 自检清单

- [ ] 邻接表 vs 邻接矩阵的空间/时间 trade-off？
- [ ] Dijkstra 算法中，为什么需要 `if (d > dist[u])` 跳过过时记录？
- [ ] 为什么 Dijkstra 不能处理负权边，而 Bellman-Ford 可以？
- [ ] Kruskal 算法中并查集的使用体现了什么设计思想？
- [ ] 如何检测无向图是否有环？有向图呢？

---

## 阶段 9：算法设计技术 — Weiss Ch.10（第 13~15 周）

### 学习目标

掌握五种核心算法范式，并用 C++ 实现经典问题，注重内存效率。Weiss Ch.10 涵盖贪心、分治、DP、随机化、回溯五大范式。

### 对应 Weiss 章节

| 节 | 内容 | 掌握程度 |
|----|------|----------|
| §10.1 Greedy Algorithms | 调度问题、Huffman 编码、近似装箱 | 精读 + 手写 Huffman |
| §10.2 Divide and Conquer | 最近点对、选择问题、算法的理论改进 | 精读 |
| §10.3 Dynamic Programming | 矩阵链乘、最优 BST、全源最短路径 | **精读 + 手写** |
| §10.4 Randomized Algorithms | 跳表、素性测试 | 理解原理 |
| §10.5 Backtracking Algorithms | 收费公路重建、博弈问题 | 精读 + 手写 |

### 知识点

#### 贪心算法（§10.1）
- 活动选择、Huffman 编码、跳跃游戏
- 与 DP 的区别：贪心不需要全局最优，只做局部最优选择
- 贪心成立的判定：最优子结构 + 贪心选择性质

#### 分治算法（§10.2）
- 最大子数组（跨中点分析）、最近点对
- 主定理（Master Theorem）的应用
- 与递归的区别与联系

#### 动态规划（§10.3）
- 重叠子问题 + 最优子结构
- 自顶向下（记忆化搜索） vs 自底向上（填表）
- 状态定义：一维 dp（斐波那契、爬楼梯）、二维 dp（编辑距离、背包、矩阵链）
- 空间优化：滚动数组（二维 → 一维 → 两个变量）
- C++ 注意：用 `new` 分配二维 dp 时小心泄漏

#### 随机化算法（§10.4）
- 跳表（Skip List）的结构与操作
- 随机化快速排序的 pivot 选择

#### 回溯算法（§10.5）
- 组合、排列、子集、N 皇后
- 剪枝策略（预排序、边界条件提前退出）
- C++ 注意：递归深度可能过深→栈溢出

### 核心代码示例

**背包 DP（自底向上 + 空间优化到一维）：**

```cpp
// 0-1 背包：N 件物品，容量 W
int knapsack(const std::vector<int>& wt,
             const std::vector<int>& val, int W) {
    std::vector<int> dp(W + 1, 0);
    for (size_t i = 0; i < wt.size(); ++i) {
        // 必须倒序！否则同一物品会被使用多次
        for (int w = W; w >= wt[i]; --w) {
            dp[w] = std::max(dp[w], dp[w - wt[i]] + val[i]);
        }
    }
    return dp[W];
}
```

**Huffman 编码（贪心 + 优先队列）：**

```cpp
#include <queue>

struct HuffNode {
    char ch;
    int freq;
    HuffNode *left, *right;
    HuffNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(HuffNode* a, HuffNode* b) {
        return a->freq > b->freq;  // 小顶堆
    }
};

HuffNode* build_huffman(const std::unordered_map<char, int>& freq_map) {
    std::priority_queue<HuffNode*, std::vector<HuffNode*>, Compare> pq;
    for (auto& [ch, freq] : freq_map)
        pq.push(new HuffNode(ch, freq));

    while (pq.size() > 1) {
        auto left = pq.top(); pq.pop();
        auto right = pq.top(); pq.pop();
        auto parent = new HuffNode('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }
    return pq.empty() ? nullptr : pq.top();
}
```

**对比 Python 递归记忆化：**

```python
from functools import lru_cache

def knapsack(wt, val, W):
    @lru_cache(None)
    def dp(i, w):
        if i < 0 or w <= 0:
            return 0
        if wt[i] > w:
            return dp(i - 1, w)
        return max(dp(i - 1, w), dp(i - 1, w - wt[i]) + val[i])
    return dp(len(wt) - 1, W)
```

> Python 的 `@lru_cache` 一行搞定记忆化；C++ 需要手动管理 memo 数组——但你对内存的控制更精确。

### 推荐资源

- **Weiss Ch.10** — 主读
- 《算法导论》第 15~16 章（DP、贪心）
- [Labukado 的 DP 教程](https://leetcode.com/discuss/general-discussion/458695/dynamic-programming-patterns)（LeetCode 讨论区）

### 实践任务

| 类型 | 内容 |
|------|------|
| 编程题 | 最长递增子序列（LeetCode 300）——O(n²) DP → O(n log n) 贪心+二分 |
| 编程题 | 编辑距离（LeetCode 72）——二维 DP，尝试空间优化到 O(min(m,n)) |
| 编程题 | 全排列（LeetCode 46）——回溯，体会 `swap` 实现比 `vector<bool> used` 的空间优势 |
| 编程题 | 实现 Huffman 编码的完整程序（含编码/解码） |
| 小项目 | 实现数独求解器（回溯 + 剪枝），用 `bitset<9>` 压缩状态减少内存 |

### 自检清单

- [ ] 0-1 背包中，为什么内层循环必须倒序？
- [ ] 贪心算法 vs 动态规划：分别适用于什么问题？（最优子结构 + 贪心选择性质 vs 重叠子问题）
- [ ] 回溯法中的剪枝如何设计？举例说明。
- [ ] 走迷宫：DFS vs BFS 的内存消耗对比？各自的适用场景？

---

## 阶段 10：摊还分析 + 高级数据结构 + 总复习 — Weiss Ch.11~12（第 15~16 周）

### 学习目标

掌握摊还分析的三种方法，了解红黑树等高级数据结构，将前 14 周的知识转化为面试实战能力。

### 对应 Weiss 章节

| 节 | 内容 | 掌握程度 |
|----|------|----------|
| **Ch.11 Amortized Analysis** | | |
| §11.1 An Unrelated Puzzle | 摊还分析的直觉引入 | 理解 |
| §11.2 Binomial Queues | 二项队列的摊还分析 | 精读（回顾 Ch.6） |
| §11.3 Skew Heaps | 斜堆的摊还分析 | 理解 |
| §11.4 Fibonacci Heaps | 斐波那契堆（`decreaseKey` 的 O(1) 均摊关键） | 理解原理 |
| §11.5 Splay Trees | 伸展树的摊还分析 | 理解（回顾 Ch.4） |
| **Ch.12 Advanced Data Structures** | | |
| §12.1 Top-Down Splay Trees | 自顶向下伸展树 | 略读 |
| §12.2 Red-Black Trees | 红黑树（自底向上插入、自顶向下插入/删除） | **精读** |
| §12.3 Treaps | 树堆 | 了解 |
| §12.4 Suffix Arrays and Suffix Trees | 后缀数组和后缀树 | 了解 |
| §12.5 k-d Trees | k-d 树 | 了解 |
| §12.6 Pairing Heaps | 配对堆 | 了解 |

### 知识点

| 主题 | 要点 |
|------|------|
| **摊还分析三法** | 聚合分析、会计方法、势能方法——Weiss §11 |
| **红黑树** | 5 条性质、插入修复（变色 + 旋转）、与 AVL 树的比较 |
| **后缀数组** | 文本索引结构，O(n) 和 O(n log n) 构造方法 |
| **k-d 树** | 多维搜索、最近邻查询 |
| **实战能力** | LeetCode C++ 模式、内存安全工具、性能分析 |

### 红黑树 vs AVL 树速览

| 性质 | AVL 树 | 红黑树 |
|------|--------|--------|
| 平衡条件 | 严格：\|height(L)-height(R)\| ≤ 1 | 宽松：黑高相等 |
| 查找 | 更快（更平衡） | 稍慢 |
| 插入/删除 | 旋转次数可能更多 | 最多 2~3 次旋转 |
| STL 使用 | — | `std::map`/`std::set` 基于红黑树 |

### 核心代码示例

**红黑树节点结构：**

```cpp
enum class Color { RED, BLACK };

template <typename T>
struct RBNode {
    T val;
    Color color;
    RBNode *left, *right, *parent;
    RBNode(T x) : val(x), color(Color::RED), left(nullptr), right(nullptr), parent(nullptr) {}
};
```

**势能方法分析 `vector::push_back`（摊还 O(1)）：**

```
定义势能 Φ = 2 × size - capacity（假设扩容因子为 2）
- 不扩容时：实际开销 1，ΔΦ = 2，摊还 = 3 = O(1)
- 扩容时：实际开销 O(n)，ΔΦ = 2 - n，摊还 = O(1)
∴ 任何情况下摊还 O(1)
```

### 推荐资源

- **Weiss Ch.11~12** — 主读
- 《算法导论》第 17 章（摊还分析）、第 13 章（红黑树）
- [LeetCode Hot 100](https://leetcode.cn/problem-list/2cktkvj/)
- [NeetCode 150](https://neetcode.io/)

### 实践任务

| 类型 | 内容 |
|------|------|
| 编程题 | 用势能方法分析二叉堆的 `insert` 和 `deleteMin` 摊还复杂度（Weiss §11） |
| 编程题 | LeetCode Hot 100 中选取 30 道覆盖所有题型，限时完成 |
| 编程题 | 在本地调试 3 道题，确保 ASan 无任何报警 |
| 小项目 | 用 CMake 组织 DSA 库（把之前写的链表、堆、哈希表整理成 `.h` + 测试），加上内存检查 CI |

### 自检清单

- [ ] 摊还分析的三种方法分别是什么？各自适用于什么场景？
- [ ] 红黑树相比 AVL 树，为什么插入删除更快但查找稍慢？
- [ ] 斐波那契堆的 `decreaseKey` 为什么是 O(1) 均摊？这对 Dijkstra 有什么影响？
- [ ] 能读懂 ASan/Valgrind 的输出并定位源代码行号吗？
- [ ] 在 LeetCode 中遇到 TLE（超时），第一步分析什么？
- [ ] `std::move` 对 `vector` 的影响是什么？什么时候用？

---

## 附录 A：周计划表

| 周次 | 阶段 | Weiss 章节 | 核心内容 | LeetCode 必做题 |
|------|------|-----------|----------|----------------|
| 1 | 0 | Ch.1 | C++ 指针、动态内存、RAII、模板（✅ 已完成） | — |
| 1~2 | 1 | Ch.2 | 大 O 分析、最大子序列和、STL 复杂度 | 704（二分查找） |
| 2~3 | 2 | Ch.3 | 单链表、双向链表 | 206, 141, 142, 21 |
| 3~4 | 2 | Ch.3 | 栈、队列、表达式求值 | 20, 232, 225, 239 |
| 4~5 | 3 | Ch.4 | BST 完整实现（含析构、拷贝） | 98, 235, 236, 450 |
| 5~6 | 3 | Ch.4 | AVL 旋转、B 树原理 | 108, 110 |
| 6~7 | 4 | Ch.5 | 链地址 HashMap + rehash | 1, 242, 49 |
| 7~8 | 5 | Ch.6 | 二叉堆、优先队列 | 703, 23, 295 |
| 8~9 | 6 | Ch.7 | 插入/希尔/归并/快速排序 | 912, 215 |
| 9~10 | 6 | Ch.7 | 堆排序、桶/基数排序、外部排序 | 347, 451 |
| 10~11 | 7 | Ch.8 | 并查集（Union-by-Rank + 路径压缩） | 684 |
| 11~12 | 8 | Ch.9 | 图存储、DFS/BFS、拓扑排序、Dijkstra | 200, 207, 743 |
| 12~13 | 8 | Ch.9 | Prim、Kruskal、Bellman-Ford | 787, 127 |
| 13~14 | 9 | Ch.10 | 贪心（Huffman）、DP（背包、编辑距离） | 300, 72, 322 |
| 14~15 | 9 | Ch.10 | 分治（最近点对）、回溯（排列/组合） | 46, 78, 51, 53 |
| 15~16 | 10 | Ch.11~12 | 摊还分析、红黑树、后缀数组、实战刷题 | Hot 100 精选 30 题 |

---

## 附录 B：LeetCode 题号清单（按 Weiss 章节）

### 标注说明

- 🧠 = 涉及复杂内存管理，建议本地用 ASan 自测
- 🔁 = 递归实现，注意栈溢出风险
- 📦 = 涉及 STL 容器，理解底层实现有帮助

### Ch.2 — 算法分析

| 题号 | 题目 | 标注 | 练习点 |
|------|------|------|--------|
| 704 | 二分查找 | — | 对数时间分析 |
| 53 | 最大子数组和 | — | Kadane O(n) / 分治 O(n log n) |
| 33 | 搜索旋转排序数组 | — | 二分查找变种 |
| 69 | x 的平方根 | — | 二分答案 |

### Ch.3 — 表、栈、队列

| 题号 | 题目 | 标注 | 练习点 |
|------|------|------|--------|
| 206 | 反转链表 | 🧠 | 迭代 + 递归，注意不泄漏 |
| 141 | 环形链表 | — | 快慢指针 |
| 142 | 环形链表 II | — | 快慢指针 + 数学推导 |
| 21 | 合并两个有序链表 | 🧠 | dummy 节点、递归 |
| 19 | 删除链表倒数第 N 个节点 | — | 双指针间隔 |
| 160 | 相交链表 | — | 双指针消除长度差 |
| 25 | K 个一组翻转链表 | 🧠🔁 | 分组反转、dummy 节点 |
| 146 | LRU 缓存 | 🧠 | 哈希表 + 双向链表 |
| 20 | 有效的括号 | — | 栈的经典应用 |
| 232 | 用栈实现队列 | — | 双栈 |
| 225 | 用队列实现栈 | — | 单队列 / 双队列 |
| 239 | 滑动窗口最大值 | 📦 | 单调队列（deque） |
| 84 | 柱状图中最大的矩形 | 📦 | 单调栈 |
| 42 | 接雨水 | — | 双指针 / 单调栈 |

### Ch.4 — 树

| 题号 | 题目 | 标注 | 练习点 |
|------|------|------|--------|
| 94/144/145 | 二叉树的前/中/后序遍历 | 🔁 | 递归 + 迭代栈 + Morris |
| 102 | 二叉树的层序遍历 | — | BFS 队列 |
| 98 | 验证二叉搜索树 | 🔁 | 中序遍历有序性 |
| 235 | BST 的最近公共祖先 | 🔁 | BST 性质 |
| 236 | 二叉树的最近公共祖先 | 🔁 | 后序遍历 |
| 450 | 删除 BST 中的节点 | 🧠🔁 | 三种删除情况 |
| 108 | 有序数组转 BST | 🔁 | 中点递归 |
| 110 | 平衡二叉树 | 🔁 | 高度计算 + 剪枝 |
| 297 | 二叉树的序列化与反序列化 | 🧠 | 前序 + 空节点标记 |
| 124 | 二叉树最大路径和 | 🔁 | 后序 DP 在树上 |

### Ch.5 — 散列

| 题号 | 题目 | 标注 | 练习点 |
|------|------|------|--------|
| 1 | 两数之和 | 📦 | `unordered_map` 一次遍历 |
| 242 | 有效的字母异位词 | — | 数组代替哈希 |
| 49 | 字母异位词分组 | 📦 | 排序 key / 计数编码 |
| 128 | 最长连续序列 | 📦 | `unordered_set` O(n) |
| 560 | 和为 K 的子数组 | 📦 | 前缀和 + 哈希 |

### Ch.6 — 优先队列（堆）

| 题号 | 题目 | 标注 | 练习点 |
|------|------|------|--------|
| 703 | 数据流中的第 K 大元素 | 📦 | 小顶堆 |
| 295 | 数据流的中位数 | 📦 | 对顶堆 |
| 23 | 合并 K 个升序链表 | 📦 | 小顶堆优化 |
| 218 | 天际线问题 | 📦 | 扫描线 + 堆 |

### Ch.7 — 排序

| 题号 | 题目 | 标注 | 练习点 |
|------|------|------|--------|
| 912 | 排序数组 | 🧠 | 手写快排/归并/堆排 |
| 215 | 数组中的第 K 个最大元素 | — | QuickSelect / 堆 |
| 148 | 排序链表 | 🧠🔁 | 归并排序链表版 |
| 347 | 前 K 个高频元素 | 📦 | 桶排序 / 堆 |
| 451 | 根据字符出现频率排序 | 📦 | 堆 / 桶排序 |

### Ch.8 — 不相交集

| 题号 | 题目 | 标注 | 练习点 |
|------|------|------|--------|
| 684 | 冗余连接 | 🧠 | 并查集直接应用 |
| 547 | 省份数量 | — | 连通分量计数 |
| 200 | 岛屿数量 | 🔁 | 也可用并查集做 |

### Ch.9 — 图算法

| 题号 | 题目 | 标注 | 练习点 |
|------|------|------|--------|
| 200 | 岛屿数量 | 🔁 | 网格图 DFS/BFS |
| 207 | 课程表 | 📦 | 拓扑排序 |
| 210 | 课程表 II | 📦 | 拓扑排序输出序列 |
| 743 | 网络延迟时间 | 📦 | Dijkstra |
| 787 | K 站中转内最便宜的航班 | 📦 | Bellman-Ford / BFS+剪枝 |
| 127 | 单词接龙 | 📦 | BFS 最短路径 |
| 133 | 克隆图 | 🧠 | DFS/BFS + 深拷贝 |

### Ch.10 — 算法设计技术

**动态规划：**

| 题号 | 题目 | 标注 | 练习点 |
|------|------|------|--------|
| 300 | 最长递增子序列 | — | O(n²) → O(n log n) |
| 72 | 编辑距离 | — | 二维 DP，空间优化 |
| 1143 | 最长公共子序列 | — | 二维 DP |
| 322 | 零钱兑换 | — | 完全背包 |
| 416 | 分割等和子集 | — | 0-1 背包变种 |
| 53 | 最大子数组和 | — | 一维 DP / 分治 |
| 152 | 乘积最大子数组 | — | 正负最小值维护 |
| 198 | 打家劫舍 | — | DP + 滚动 |
| 139 | 单词拆分 | 📦 | DP + 哈希 |

**回溯：**

| 题号 | 题目 | 标注 | 练习点 |
|------|------|------|--------|
| 46 | 全排列 | 🔁 | swap 回溯 |
| 78 | 子集 | 🔁 | 选/不选 |
| 51 | N 皇后 | 🔁 | 对角线约束 |
| 39 | 组合总和 | 🔁 | 可重复选择 + 剪枝 |
| 37 | 解数独 | 🔁 | 回溯 + bitset 压缩 |

**贪心：**

| 题号 | 题目 | 标注 | 练习点 |
|------|------|------|--------|
| 55 | 跳跃游戏 | — | 贪心可行性质 |
| 45 | 跳跃游戏 II | — | 贪心最少步数 |

### Ch.11~12 — 高级结构与实战

| 题号 | 题目 | 标注 | 练习点 |
|------|------|------|--------|
| 208 | 实现 Trie | 🧠 | Trie 增删查 |
| 212 | 单词搜索 II | 🔁🧠 | Trie + 回溯 |
| 5 | 最长回文子串 | — | 中心扩展 / Manacher |
| 76 | 最小覆盖子串 | — | 滑动窗口 |
| 28 | 实现 strStr() | — | KMP / Sunday |

---

## 附录 C：常见误区与解决

### 1. 野指针（Dangling Pointer）

**症状**：访问已释放的内存，结果不可预测（crash / 脏数据）。

```cpp
int* p = new int(42);
delete p;
*p = 10;  // 未定义行为！p 是野指针
```

**解决**：释放后立即置为 `nullptr`：

```cpp
delete p;
p = nullptr;
```

> 更好的解决：用 `std::unique_ptr` / `std::shared_ptr`，禁止裸指针管理所有权。

### 2. 内存泄漏（Memory Leak）

**症状**：程序长期运行内存不断增长；valgrind 报告 "definitely lost" 或 "indirectly lost"。

**常见场景**：

```cpp
// 场景 1：提前 return 忘记释放
void func() {
    int* p = new int[100];
    if (error) return;  // 泄漏！
    delete[] p;
}

// 场景 2：异常安全
void func() {
    int* p = new int[100];
    may_throw();  // 如果抛异常，下面的 delete 不执行
    delete[] p;
}

// 场景 3：浅拷贝导致双重释放或泄漏
// 如果 LinkedList 没有自定义拷贝构造 → 默认拷贝只复制指针
// → 两个对象指向同一链表 → 析构时 double-free
```

**解决**：RAII 是正解——用类管理资源，构造获取，析构释放。

### 3. 双重释放（Double Free）

**症状**：程序崩溃，valgrind 报告 "Invalid free() / delete / delete[] / realloc()"。

```cpp
int* p = new int(42);
int* q = p;
delete p;
delete q;  // 崩溃！重复释放同一地址
```

**解决**：严格遵循"谁分配谁释放"，一个资源只有一个所有者。

### 4. `new[]` 与 `delete` 混用

```cpp
int* arr = new int[10];
delete arr;    // 未定义行为！应该用 delete[] arr

int* p = new int;
delete[] p;    // 同样错误！
```

**解决**：`new` ↔ `delete`，`new[]` ↔ `delete[]` 严格配对。

### 5. 栈溢出（Stack Overflow）

**症状**：递归过深导致段错误（segmentation fault）。

```cpp
// 对有序数组的朴素快排 → 递归深度 = 数组长度
// 100 万元素 → 约 8MB 栈空间（100 万帧）→ 溢出
```

**解决**：
- 尾递归优化（编译器不一定做）
- 迭代改写
- 优先递归小区间（快排优化）
- 增大栈空间：`ulimit -s unlimited`（不治本）

### 6. `std::vector` 的迭代器/引用失效

```cpp
std::vector<int> v = {1, 2, 3};
int& ref = v[0];
v.push_back(4);  // 可能触发 realloc → ref 悬垂！
```

**解决**：在 `push_back` 前 `reserve` 足够容量，或用索引代替引用。

### 7. STL 容器的性能误区

| 误区 | 真相 |
|------|------|
| `list` 遍历比 `vector` 快 | `list` 缓存不友好，`vector` 连续内存遍历通常快 3~10 倍 |
| `unordered_map` 总是 O(1) | 最坏 O(n)，hash 碰撞或 rehash 时退化 |
| 递归总是慢 | 小数据集上递归简洁，编译器可能尾递归优化；大数据集选迭代 |

---

## 附录 D：面试快速复习路线

> 适用场景：面试前 2~4 周，已学完上述所有内容，需要快速提炼 C++ DSA 面试考点。

### 第一优先级：必问基础（2 天）

| 考点 | 具体内容 |
|------|----------|
| **智能指针** | `unique_ptr`（独占所有权、`std::move`）、`shared_ptr`（引用计数、`make_shared` 的优势）、`weak_ptr`（打破循环引用） |
| **移动语义** | 右值引用 `T&&`、`std::move` 的含义（类型转换，不移动任何东西）、移动构造/赋值（noexcept 的重要性） |
| **Rule of Five** | 析构、拷贝构造、拷贝赋值、移动构造、移动赋值 — 什么时候需要自定义？`= default` / `= delete` |
| **vector 扩容** | 1.5x vs 2x 因子的内存优劣、`reserve` 预分配、`shrink_to_fit`、`emplace_back` vs `push_back` |

### 第二优先级：必考数据结构（5 天）

| 数据结构 | 面试重点 | 必写代码 |
|----------|----------|----------|
| 链表 | 反转（迭代+递归）、环检测、合并、LRU | `reverseList`、`detectCycle` |
| 栈/队列 | 单调栈（下一个更大元素）、用栈实现队列 | 基本操作 + 边界 |
| 哈希表 | 冲突解决原理、负载因子、rehash | 两数之和、字母异位词分组 |
| 二叉树 | 遍历、LCA、验证 BST、序列化 | 前中后序（递归+迭代） |
| 堆 | `priority_queue` 自定义比较器、Top K、对顶堆 | 数据流中位数 |
| 图 | DFS/BFS、拓扑排序、Dijkstra | 岛屿数量、课程表 |

### 第三优先级：算法思想（5 天）

| 算法 | 面试重点 | 必写代码 |
|------|----------|----------|
| 二分查找 | 边界条件（开/闭区间）、变种（第一个/最后一个等于 target） | `lower_bound` 手写 |
| 排序 | 快排分区、归并合并、稳定性 | 快排 + 堆排 |
| 滑动窗口 | 双指针、窗口收缩条件 | 最小覆盖子串 |
| DP | 背包问题、LIS、编辑距离 | 0-1 背包一维优化 |
| 回溯 | 排列/组合/子集模板 | 全排列（swap 版） |
| 贪心 | 能否贪心的判断标准（最优子结构+贪心选择性质） | 跳跃游戏 |

### C++ 专有考点速记（2 天）

| 考点 | 一句话总结 |
|------|-----------|
| `std::map` vs `std::unordered_map` | 前者红黑树 O(log n) 有序，后者哈希表 O(1) 无序 |
| `emplace_back` vs `push_back` | emplace 原地构造，减少一次移动/拷贝 |
| `reserve` vs `resize` | reserve 只分配容量不构造元素；resize 会构造/删除元素 |
| 迭代器失效 | vector 插入/删除后，之后的迭代器可能全部失效 |
| `std::sort` 原理 | IntroSort：快排 + 堆排（递归过深时切换）+ 小数组插入排序 |
| 字符串 SSO | 短字符串（通常 ≤15 字符）存在栈上，无堆分配 |
| `noexcept` | 标记不抛异常的函数，`vector` 在扩容时对 `noexcept` 移动构造走快速路径 |
| 循环引用 | `shared_ptr` 互相引用导致泄漏 → 用 `weak_ptr` 打破 |

### 刷题清单（面试前必做 30 题）

按出现频率排列：

```
# 数组与双指针（5 道）
1, 15, 11, 42, 283

# 链表（5 道）
206, 141, 21, 19, 146

# 栈与队列（3 道）
20, 232, 239

# 哈希（3 道）
1, 49, 128

# 二叉树（5 道）
94, 102, 236, 98, 124

# 图（2 道）
200, 207

# DP（4 道）
53, 300, 322, 1143

# 回溯（2 道）
46, 78

# 字符串（1 道）
5
```

---

## 附录 E：推荐书单与学习资源汇总

### 书籍（按学习顺序）

| 序号 | 书名 | 用途 | 对应阶段 |
|------|------|------|----------|
| 1 | **《Data Structures and Algorithm Analysis in C++》(4th) Weiss** | **主教材，全部阶段的主线** | 全阶段 |
| 2 | 《C++ Primer（第 5 版）》 | C++ 语法参考，常备案头 | 全阶段 |
| 3 | 《算法导论》（CLRS） | 算法圣经，当参考书查阅细节证明 | 全阶段 |
| 4 | 《算法（第 4 版）》Sedgewick | Java 版但算法讲解极佳，可视化丰富 | Ch.3~10 |
| 5 | 《Effective Modern C++》Meyers | C++11/14 最佳实践 | Ch.1 和面试复习 |
| 6 | 《剑指 Offer（第 2 版）》 | 中文面试经典题集 | Ch.11~12 |

### 在线资源

| 资源 | 链接 | 用途 |
|------|------|------|
| LeetCode 中国 | https://leetcode.cn | 刷题主场地 |
| 牛客网 | https://www.nowcoder.com | 国内面试题库 |
| Visualgo | https://visualgo.net | 算法可视化 |
| cppreference | https://en.cppreference.com | C++ 标准库权威文档 |
| NeetCode | https://neetcode.io | 按模式分类刷题 |
| Codeforces | https://codeforces.com | 竞赛向，进阶练习 |
| Weiss 教材官网 | https://users.cs.fiu.edu/~weiss/ | 源代码下载 |

### 视频

| 视频 | 平台 | 内容 |
|------|------|------|
| MIT 6.006 Introduction to Algorithms | YouTube/OCW | 经典算法课 |
| mycodeschool | YouTube | 数据结构动画讲解 |
| Back To Back SWE | YouTube | 面试向算法讲解 |
| 代码随想录 | Bilibili/网站 | 中文刷题路线，含 C++ 代码 |

---

> **最后的建议**：这个计划是地图，不是牢笼。以 Weiss 教材为主线，意味着每个阶段你都能在书中找到对应的详细讲解和数学证明。如果某个阶段你觉得特别有感觉，可以多花几天深入；如果某个阶段你已经很熟，可以加速通过。最重要的是：**每天至少写一点代码**。数据结构与算法的肌肉记忆只能通过反复写、反复改错来建立。祝学习顺利！
