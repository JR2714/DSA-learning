# Phase 2 笔记：表、栈、队列 (Weiss Ch.3)

## L1: ADT 概念 + List ADT (§3.1–3.3)

### ADT（抽象数据类型）
- **定义**：对象集合 + 操作集合。只规定"做什么"，不规定"怎么做"。
- C++ class 实现 ADT，实现细节对调用者透明。
- 这是贯穿整个 DSA 的核心思想：分离规约与实现。

### List ADT
- 形式：A₀, A₁, ..., Aₙ₋₁
- 核心操作：printList, makeEmpty, find, findKth, insert, remove

### 数组 vs 链表

| | vector (数组) | list (链表) |
|---|---|---|
| findKth(i) | O(1) | O(i) |
| insert/remove(0) | O(N) — 平移 | O(1) — 改指针 |
| insert/remove(end) | O(1)* | O(1)* |
| 搜索 | O(N) | O(N) |

> \* 链表尾部删除需双向链表 + tail 指针；单链表仍为 O(N)

### STL 迭代器
- `begin()` → 第一个元素；`end()` → 末尾哨兵（不是最后一个元素）
- `*itr` 解引用；`++itr` 前进；`itr1 == itr2` 比较
- `insert(itr, x)` 在 itr **之前**插入
- `erase(itr)` 删除 itr 所指，**返回下一有效 iterator**，itr 本身失效
- `const_iterator` vs `iterator`：const 容器强制使用 const_iterator；auto 自动推导
- Weiss 图 3.5 `removeEveryOtherItem`：list O(N) vs vector O(N²) 的经典对比（5min vs 0.04s）

---

## 复杂度讨论：removeDuplicates 的真实上界

### 背景
模板函数 `removeDuplicates` 使用嵌套循环 + erase 删重（不用额外数据结构）。初评时我声称 vector 版本是 O(N³)，Jacob 质疑：每个元素最多被删一次，erase 的 O(N) 代价不应与内外循环简单相乘。

```cpp
template <typename Container>
void removeDuplicates(Container& lst) {
    for(auto current = lst.begin(); current != lst.end(); current++) {
        for(auto scanner = std::next(current, 1); scanner != lst.end(); ) {
            if(*current == *scanner)
               scanner = lst.erase(scanner);
            else
                scanner++;
        }
    }
}
```

### 模型设定
- K 个不同值，值 i 出现 M_i 次
- 总元素数 N = Σ M_i
- 保留 K 个（每个值的首次出现），删除 N−K 个

### 逐项分析
处理第 i 个值时（前 i−1 个值的副本已删完）：
- 剩余元素数：R_i = N − Σ_{j=1}^{i−1} (M_j − 1)
- 比较次数 C_i ≤ R_i（扫描当前位置后的所有元素）
- 移位代价 S_i：删除 M_i−1 个副本，第 k 次删除移动当时剩余 d_k 个元素

### 上界推导
- Σ C_i ≤ N(N−1)/2（每对元素最多被比较一次）
- Σ S_i ≤ N(N−1)/2（最多 N 次删除，每次移动不超过 N 个）
- 总工作量 W = Σ(C_i + S_i) ≤ N(N−1) = **O(N²)**

### 紧确性（三个极端案例）

| 案例 | K | M_i | 比较 | 移位 | 总计 |
|------|---|-----|------|------|------|
| 全相同 | 1 | N | ~N | ~N²/2 | ~N²/2 |
| 全不同 | N | 1 | ~N²/2 | 0 | ~N²/2 |
| 每值2次 | N/2 | 2 | ~N²/4 | ~N²/4 | ~N²/2 |

三种极端的主导项均为 N²/2，只是来自比较还是移位的比例不同。

### 结论
- **复杂度紧确界：Θ(N²)**，与输入分布无关
- vector vs list 的区别不在阶数，在**常数因子**：
  - 全相同：vector 大量移位（内存拷贝），远慢于 list
  - 全不同：两者相当（都只做比较，无删除）
- 实际应用：此模板函数对 list 安全；对 vector 建议改用 sort+unique（O(N log N)）

### 教训
- 嵌套循环 + erase 不能简单乘阶数得到 O(N³)
- 要追踪每条数据的"生命周期"：被删后就不再参与后续操作
- 紧确界（Θ）需要同时证上界和下界，构造极端案例是关键

---

## L2: vector 与 list 的底层实现 (§3.4–3.5)

### SimpleVector 实现要点

**三成员结构**：`theSize`, `theCapacity`, `objects*` — 将 C 数组手动维护的三变量封装进类。

**reserve 的 swap 惯用法**：
```cpp
Object *newArray = new Object[newCapacity];
for(int i = 0; i < theSize; ++i)
    newArray[i] = std::move(objects[i]);  // 移动避免深拷贝
std::swap(objects, newArray);             // 异常安全
delete[] newArray;                        // 释放的是旧数组！
theCapacity = newCapacity;
```
`delete[] newArray` 释放旧数组——因为 swap 后 newArray 已指向原 objects。

**push_back 的后置 ++**：`objects[theSize++] = x` — 先用旧 theSize 索引，再自增。与迭代器 `*itr++` 同一惯用法。前缀 `++theSize` 会导致索引错位。

**扩容因子 ×2**：见下方均摊分析。

**迭代器是裸指针**：vector 的迭代器可直接用 `typedef Object* iterator`，因为指针在连续内存上天然支持 `++`, `*`, `==`, `!=`。

### SList 实现要点

**哨兵节点（Header Node）**：永久存在的空节点，不存数据，`head->next` 指向第一个数据节点（或 nullptr）。

**哨兵消除所有头部特判**：
- 无哨兵：push_front 需修改 head 指针本身，属于特殊情况
- 有哨兵：push_front = insert_after(head)，和中间插入完全一致

**单节点 erase_after 的正确语义**：
```cpp
bool erase_after(Node* node) {
    if(node != nullptr && node->next != nullptr) {
        Node* toDelete = node->next;
        node->next = toDelete->next;  // 跳过
        delete toDelete;
        return true;
    }
    return false;  // 没有后继 → 什么都不做
}
```
三个关键点：(1) 只删一个，(2) 空指针检查，(3) 返回 bool 让析构可以 `while(erase_after(head)){}` 循环清空。

**print() 的循环条件**：`while(p != nullptr)`，不是 `while(p->next != nullptr)`。后者在空链表（p=nullptr）时解引用崩溃，且在非空链表漏打最后一个节点。

**Node 是 private 但 begin() 返回 Node\***：这是 API 矛盾——外部无法声明 `Node*` 变量。正确做法是提供公开的 iterator typedef。

### 哨兵节点的设计哲学

**问题**：链表操作（insert/erase）需要访问"目标位置的前驱"。对于头节点的插入/删除，没有前驱。

**三种解决方案**：

| 方案 | 做法 | 代价 |
|------|------|------|
| 特判 | 每个操作分"头"和"非头"两条路径 | 代码膨胀，容易出错 |
| 指针的指针 | `Node** indirect = &head` 统一处理 | 概念负担重，不适用于双向链表 |
| 哨兵节点 | 恒有"前驱"的哑元节点 | 一个永久节点的内存 + 析构时多删一个 |

**哨兵的本质**：用一个恒不用存数据的节点，换取"永远不会在头部没有前驱"的不变式。所有节点——包括第一个数据节点——在 insert/erase 的视角下都和中间节点没有区别。

Weiss 在双向链表中用了**两个哨兵**（header + tail），带来的好处更显著：不仅头部操作统一，尾部操作也不需要特判——tail 哨兵保证了最后一个数据节点后面永远有节点，`pop_back` 就是 `erase(--end())`，和中间删除一样。

### 均摊分析直觉

**为什么 ×2 扩容是 O(1) 均摊？**

常量扩容（每次 +C）：
- N 次 push_back 触发 N/C 次扩容
- 第 k 次扩容复制 O(k·C) 个元素
- 总复制：O(N²)，均摊 O(N) ❌

翻倍扩容（每次 ×2）：
- 扩容发生在 size = 1, 2, 4, 8, ..., 2^k
- 第 k 次扩容复制 2^k 个
- 总复制：1 + 2 + 4 + ... + 2^k = 2·2^k - 1 ≤ 2N
- 总复制 O(N)，均摊 O(1) ✓

**直觉**：每次扩容的代价被后续大量"廉价"push_back 摊平。扩容间隔是指数增长的——越大，下次扩容越远。

**shrink_to_fit 破坏均摊保证**：反复 `push_back → shrink_to_fit` 将积累的"信用额度"（空闲 capacity）一笔勾销，导致每次 push_back 都是 O(N)。

### 常见错误记录

| 错误 | 后果 | 修复 |
|------|------|------|
| 拷贝构造未 delete | 浅拷贝 → double-free | `= delete` 或实现深拷贝 |
| `erase_after` 循环删到底 | 语义错误，一次删整链 | 只删 `node->next` 一个 |
| `while(p->next)` 代替 `while(p)` | 空链表崩溃 + 漏打尾节点 | `while(p != nullptr)` |
| 忘记在 insert/erase 中维护 size | size() 返回错误值 | 每个修改操作都更新 theSize |
| 单链表加 tail 哨兵 | 多余的堆分配，tail 无法反向遍历 | 单链表只需 header 哨兵 |
