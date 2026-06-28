---
name: learning-progress
description: Tracks which phases/lessons are completed in the Weiss-aligned DSA plan
metadata:
  type: project
  originSessionId: 4e91eb79-44a5-45f9-9c0c-efc8a268fb7d
---

## Phase 0: C++ Programming Overview — Weiss Ch.1 (Week 1)

Started: 2026-06-06 | Completed: 2026-06-09 ✅

### Completed Lessons

- [x] **指针基础** (2026-06-06) — File: `C++_Basic/pointer.cpp`
- [x] **引用** (2026-06-06) — File: `C++_Basic/reference.cpp`
- [x] **动态内存** (2026-06-07) — File: `C++_Basic/dynamic_memory.cpp`
- [x] **类与对象（Rule of Three）** (2026-06-08) — File: `C++_Basic/class_objects.cpp`
- [x] **RAII 与移动语义（Rule of Five）** (2026-06-08) — File: `C++_Basic/class_objects.cpp`
- [x] **模板基础** (2026-06-08) — File: `C++_Basic/template_basics.cpp`
- [x] **STL 概览** (2026-06-09) — File: `C++_Basic/stl_overview.cpp`

### ✅ Phase 0 完成！

## Phase 1: 算法分析 — Weiss Ch.2 (Week 1~2)

Started: 2026-06-10

### Completed Lessons

- [x] **L1: 算法分析基础** (2026-06-10) — §2.1–2.3 + §2.4.1-2.4.2, pp.51–59
  - Big-Oh/Omega/Theta/little-oh 定义与规则
  - 计算模型、最坏/平均情况分析
  - FOR 循环、嵌套循环、顺序语句、If/Else 的分析规则
  - 递归 Fibonacci 的指数复杂度分析
  - 练习文件: `Chap2_AlgorithmAnalysis/L1_taste.md`

- [x] **L2: 最大子序列和 + 对数时间** (2026-06-10~11) — §2.4.3–2.4.5, pp.60–71
  - 最大子序列和四种算法：O(N³) → O(N²) → O(N log N) → O(N)
  - 二分查找（迭代 O(1) 空间 / 递归 O(log N) 空间）
  - 欧几里得 GCD 算法（O(log N)，Fibonacci 为最坏情况）
  - 快速幂（分治 O(log N)，错误实现的陷阱）
  - 练习文件: `Chap2_AlgorithmAnalysis/max_subseq.cpp`, `binary_search.cpp`, `L2_thinking.md`

### ✅ Phase 1 完成！

### 选做习题：Weiss Ch.1–2 (2026-06-12)

- [x] **1.5** 递归求二进制中1的个数 — `C++_Basic/exercise_1.5.cpp`
- [x] **1.6** 全排列（回溯法，swap 交换） — `C++_Basic/exercise_1.6.cpp`
- [x] **2.15** 二分查找变种：Aᵢ = i — `Chap2_AlgorithmAnalysis/ex_2.15.cpp`
- [x] **2.17a** 最小子列和（Kadane翻转）— `Chap2_AlgorithmAnalysis/ex_2.17.cpp`
- [x] **2.17b** 最小正子列和（O(N²) + O(N log N) 用 set 优化）— 同上
- [x] **2.17c** 最大子列积（追踪 max/min，swap 负号）— 同上
- [x] **2.31** `low=mid` 死循环：区间≤2 时 mid=low 不前进 — 理解题
- [ ] 2.1, 2.19（待做）
- [ ] 2.6, 2.8, 2.27（有空做）

推荐习题清单：`chap1-2ex.md`

See [[dsa-learning-plan]] for full phase-to-chapter mapping.

## Phase 2: 表、栈、队列 — Weiss Ch.3 (Week 2~4)

Started: 2026-06-14

### Completed Lessons

- [x] **L1: ADT 概念 + List ADT + STL vector/list** (2026-06-14) — §3.1–3.3, pp.77–86
  - ADT：对象集合 + 操作集合，规约与实现分离
  - 数组 vs 链表：findKth vs insert/erase 的 O(1)/O(N) 互换
  - STL vector (可增长数组) vs list (双向链表)
  - Iterator 抽象：begin/end、const_iterator、erase 后失效
  - 练习：removeDuplicates 模板函数（O(N²) 分析）
  - 复杂度讨论：对于 vector，虽然 erase 单次 O(N)，但每个元素最多被删一次，总移位 O(N²)，非 O(N³)
  - 练习文件：`Chap3_ListsStacksQueues/1_removeDuplicates.cpp`
  - 分析题：`Chap3_ListsStacksQueues/L1_ADT.md`
  - 笔记：`note/ch03-lists-stacks-queues.md`

- [x] **L2: vector 与 list 的底层实现** (2026-06-16) — §3.4–3.5, pp.86–102
  - Vector: size/capacity/data 三成员，reserve swap 惯用法，×2 扩容均摊 O(1)
  - Vector 迭代器即裸指针（RandomAccessIterator）
  - List: 哨兵节点消除边界特例，双向链表节点结构
  - List 插入：`p->prev = p->prev->next = new Node{x, p->prev, p}`
  - const_iterator → iterator IS-A 继承，protected + friend 访问控制
  - shrink_to_fit + push_back 对抗序列破坏均摊保证
  - 练习：`Chap3_ListsStacksQueues/2_coding.cpp` (SimpleVector)
  - 练习：`Chap3_ListsStacksQueues/2_SList.cpp` (带哨兵单链表)
  - 分析题：`Chap3_ListsStacksQueues/2_ADT.md`

- [x] **L3: 栈 ADT** (2026-06-20) — §3.6, pp.103–112
  - Stack ADT：LIFO，push/pop/top，空栈 pop 是 ADT 错误
  - 链表实现（头插头删）vs 数组实现（topOfStack 索引）
  - 应用：平衡符号、后缀求值、中缀转后缀、函数调用栈
  - 中缀转后缀：`≥` 保证左结合性，`>` 破坏之
  - 练习：`Chap3_ListsStacksQueues/3_isBalanced.cpp`（平衡符号）
  - 练习：`Chap3_ListsStacksQueues/3_evalPostfix.cpp`（后缀求值）
  - 分析题：`Chap3_ListsStacksQueues/3_infixToPostfix.md`（≥ vs >）
  - 笔记：`note/ch03-lists-stacks-queues.md`

- [x] **L4: 队列 ADT** (2026-06-21~22) — §3.7, pp.112–115
  - Queue ADT：FIFO，enqueue(rear) / dequeue(front)
  - 循环数组实现：`(index+1) % capacity` 绕回
  - 扩容：按逻辑顺序复制，`+1` 兼容 capacity=0
  - 显式 currentSize vs front/back 推导法：鸽巢原理决定后者必须留空位
  - `size_t back = -1` 惯用法 + M=0 回绕死循环的教训
  - 练习：`Chap3_ListsStacksQueues/4_queueByArray.h`（循环数组 Queue）
  - 练习：`Chap3_ListsStacksQueues/4_Josephus.cpp`（约瑟夫问题）
  - 分析题：`Chap3_ListsStacksQueues/4_queueWithoutCurrenSize.md`（方案 B 的容量限制）
  - 笔记：`note/ch03-lists-stacks-queues.md`

### Ch.3 选做习题

- [x] **3.1 printLots** (2026-06-22) — list 按位置打印，track-prev + 手写 `++itr`，O(L+P)
  - 核心收获：`advance` 对 list 无魔法（逐节点追指针），对 vector 是 O(1)
  - 数据结构选择取决于操作模式：findKth 密集型 → vector 优于 list
  - 练习文件：`Exercise/ex_3_1.cpp`
  - 笔记：`note/ch03-lists-stacks-queues.md`

- [x] **3.4 L₁ ∩ L₂** (2026-06-22) — 有序链表交集，双指针归并 O(N+M)
- [x] **3.5 L₁ ∪ L₂** (2026-06-22) — 有序链表并集，同模板 + 尾部追加
- [x] 3.24 双栈单数组
- [x] **3.25a findMin O(1) 栈** (2026-06-24) — 双栈维护最小值，push/pop/findMin 均 O(1)
  - 审查问题：min() 返回 T 而非 const T& 导致不必要拷贝；push() 非强异常保证
  - 练习文件：`Exercise/ex_3_25a.cpp`
- [x] **3.2 只改链接交换相邻节点** (2026-06-25) — 单链表 + 双链表双实现
- [x] **3.20 惰性删除** (2026-06-28~29) — 哨兵双链表 + `in_list` 标记 + `release()` 半数阈值清除
- [ ] 3.28 双端队列（Deque）

**Next: Ch.3 剩余习题 / Weiss Ch.4 Trees**
