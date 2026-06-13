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
