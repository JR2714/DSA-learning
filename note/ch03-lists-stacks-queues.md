# Phase 2 笔记：表、栈、队列 (Weiss Ch.3)

> 思考题：[L1 ADT 分析](../Chap3_ListsStacksQueues/L1_ADT.md) | [L2 均摊分析](../Chap3_ListsStacksQueues/2_ADT.md) | [L3 中缀转后缀](../Chap3_ListsStacksQueues/3_infixToPostfix.md) | [L4 队列方案B](../Chap3_ListsStacksQueues/4_queueWithoutCurrenSize.md) | [推荐习题清单](../Exercise/chap3ex.md)

> 整理：刘坤（AI 辅助）

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

---

## L3: 栈 ADT — Weiss §3.6 (pp.103–112)

### 栈的定义
- **受限的线性表**：插入删除只在栈顶（top）
- **LIFO**（后进先出）
- 核心操作：`push`（插入）、`pop`（删除栈顶）、`top`（查看栈顶）
- 空栈 pop/top 是 ADT 错误；push 空间不足是实现限制

### 实现
- 任何线性表实现都能做栈——99% 情况直接用 `std::vector`/`std::list`
- **链表实现**：单链表，push=头插，pop=头删
- **数组实现**：`topOfStack` 索引（空栈=-1），push=`++top` 再赋值，pop=取值再 `--top`
- 所有操作 O(1)，非常快的常数（现代 CPU 有栈指令）

### 应用 1：平衡符号检查
- 算法：开符号 push，闭符号 pop 并匹配，栈空时遇闭符号→错，结束时栈非空→错
- O(N) 单次遍历，online 算法

### 应用 2：后缀表达式求值（Reverse Polish Notation）
- 见到数字 → push；见到操作符 → pop 两个，运算，结果 push
- 不需要括号，不需要优先级规则
- **先 pop 出来的是右操作数**，减法/除法必须注意顺序
- O(N) 单次遍历

### 应用 3：中缀转后缀
- 操作数直接输出；操作符暂存栈中（"待处理的操作符"）
- 遇新操作符时，弹出栈中优先级 **≥** 当前操作符的符号（`(` 停止）
- **`≥` 而非 `>`**：保证左结合性。`a-b-c` 正确转为 `a b - c -`（`(a-b)-c`），若用 `>` 则错误转为 `a b c - -`（`a-(b-c)`）
- 左括号：读入时视为最高优先级（阻止弹出），在栈中时视为最低优先级（不被弹出）
- 右括号：弹出直到左括号（左括号不输出）
- O(N)

### 应用 4：函数调用栈
- 每次函数调用：保存寄存器 + 返回地址 → **栈帧（stack frame）/ 活动记录**
- 函数返回：pop 栈帧，恢复寄存器，跳转返回地址
- 递归的本质：每次调用 push 新栈帧
- **栈溢出**：栈帧过多（通常是失控递归——忘了 base case，或用递归处理超长线性结构）

### 练习中的坑

#### `std::stoi` 的行为
- `std::stoi("123")` → 123 ✓
- `std::stoi("123abc")` → 123，不报错，`pos=3`
- `std::stoi("abc")` → 抛 `std::invalid_argument`
- `std::stoi("9999999999999999")` → 抛 `std::out_of_range`
- **正确校验整个 token**：`std::stoi(token, &pos)` + 检查 `pos == token.size()`，否则 `"123abc"` 静默通过

#### for 循环体的边界
- `for(...) { ... }` 后面紧跟的语句是否在循环内，取决于 `}` 的位置
- 缩进不决定控制流——大括号 `{}` 决定
- 教训：写完循环立即确认 `{` 和 `}` 之间包含了正确的语句

#### `if` vs `else if`
- 互斥条件（如 token 是 `+` 或 `-` 或 `*` 或 `/`）应用 `else if` 链
- 独立 `if` 不会出错但传达错误意图：暗示多个分支可能同时成立

---

## L4: 队列 ADT — Weiss §3.7 (pp.112–115)

### 队列的定义
- **FIFO**（先进先出），与栈的 LIFO 对称
- 两个端点：**front（队首）**—dequeue 删除端；**rear（队尾）**—enqueue 插入端
- 核心操作：`enqueue`（入队）、`dequeue`（出队）、`getFront`（查看队首不删除）
- 就像排队买票——先来的先服务

### 循环数组实现（Circular Array）
- 数组 + `front` 索引 + `back` 索引 + `currentSize`
- 每次 back/front 前进用 `(index + 1) % capacity` 绕回，复用 dequeue 释放的空间
- 所有操作 O(1)

### 扩容要点
- 扩容时 front 不一定在 0 位，不能直接 push_back
- **正确做法**：新建 `arr_temp(2*size + 1)`，按逻辑顺序（front → rear 绕回）复制，swap 后重置 front=0, back=currentSize-1
- **`+1` 必要**：capacity=0 时 `2*0 = 0`，arr_temp(0) 无法容纳元素。`+1` 保证最小容量为 1

### 显式 currentSize vs front/back 推导法
- **方案 A（推荐）**：显式 `currentSize`，判空 `size==0`，判满 `size==capacity`，简单不出错
- **方案 B**：不维护 currentSize，用 front/back 关系推导
  - 判空：`front ≡ back+1 (mod n)`
  - 判满：同样是 `front ≡ back+1 (mod n)`——back 绕一圈追上 front
  - front/back 相对位置只有 n 种，但 size 有 n+1 种（0 到 n），鸽巢原理保证必然冲突
  - 因此方案 B 最多放 capacity-1 个元素，预留一个空位区分空/满
- Weiss 原话："This is a very tricky way to go... be very careful"

### 链表实现
- Weiss 留作习题——straightforward，O(1)
- front 指针指向队首（dequeue 端），rear 指针指向队尾（enqueue 端）
- 可用哨兵节点简化边界

### Josephus 问题
- N 人围圈，每次数 M 下淘汰一个
- **队列解法**：每轮把 M-1 人从队首出队再入队（传到队尾），第 M 人只出队不入队
- 时间复杂度 O(N·M)

### 常见错误
| 错误 | 后果 | 修复 |
|------|------|------|
| `size_t back = -1` 误以为错误 | 实际是惯用法：-1 转无符号=最大值，配合 `(back+1)%n` 首次得 0 | 理解无符号回绕 |
| M=0 时 `i < M-1`（size_t） | 0-1 回绕到 SIZE_MAX → 死循环 | 检查 M==0 |
| main 变量命名与函数参数颠倒 | 读代码时极易混淆 | 统一命名或用 `people`/`step` |

---

## 习题 3.1: printLots — list vs vector 的选择

### 题目
给定 list L 和有序整数 list P，打印 L 中位于 P 指定位置的所有元素。

### 解法
```cpp
auto itr = L.begin();
int prev = 0;
for (int idx : P) {
    int steps = idx - prev;
    while (steps--) ++itr;   // 手写 advance，感受 pointer-chasing
    prev = idx;
    cout << *itr << "\n";
}
```

### 复杂度分析
- 每个 `++itr` 在 list 中是 O(1)（追一个指针），但不可随机访问
- 所有 `steps` 之和 = 最后一个 idx ≤ |L|-1，所以总 advance 步数 O(|L|)
- cout 执行 |P| 次
- **总复杂度：O(|L| + |P|)**，不是 O(|P|)

### `std::advance` 没有魔法
```cpp
advance(itr, n);   // 对 list 等价于
while (n--) ++itr;  // 逐节点追指针，O(n)
```
对 vector：`advance` = `itr += n`（一条指针算术），O(1)。

### 关键反思：为什么不用 vector？
| 操作 | vector | list |
|------|--------|------|
| findKth(i) | O(1) — `*(ptr+i)` | O(i) — 逐节点追指针 |
| advance n 步 | O(1) — 指针算术 | O(n) — while 循环 |
| 迭代器类型 | RandomAccess | Bidirectional |

**printLots 本质是 findKth 密集型操作 → vector 更合适。**

### 教训
- 数据结构的选择取决于**操作模式**：频繁按位置访问 → vector；频繁头部插入删除 → list
- STL 的便利函数（`advance`）没有改变底层数据结构的复杂度
- 在"练习要求用 list"和"实际应该用 vector"之间保持清醒——前者是教学，后者是工程判断

---

## 习题 3.4 & 3.5: 有序链表交集 ∩ 与并集 ∪

### 题目

给定两个已排序列表 L₁ 和 L₂，只用基本列表操作计算 L₁ ∩ L₂（3.4）和 L₁ ∪ L₂（3.5）。

### 算法：双指针归并

两个函数共享同一核心结构——一个 itr 跟踪 L₂ 位置，外层遍历 L₁，内层消费 L₂ 中小于当前 L₁ 元素的节点。

```
交集 ∩                              并集 ∪
for i in L₁:                        for i in L₁:
  while *itr < i: ++itr               while *itr < i:
  if *itr == i: push(i)                 去重 push(*itr); ++itr
                                      去重 push(i)
                                    while itr != end:        ← 并集特有
                                      去重 push(*itr++)       ← 消费 L₂ 尾部
```

- **复杂度**：O(|L₁| + |L₂|)，每个迭代器只前进不后退
- **空间**：O(|result|)
- `const Comparable&` 遍历避免拷贝
- itr 单调前进——不回头，这是 O(N+M) 的关键

### 去重策略

两个函数都用 `result.empty() || x != result.back()` 保证输出无连续重复（输入已排序时等价于全局去重）。这个模式在并集中出现了三次：（1）内层消费 L₂，（2）外层 push L₁，（3）尾部追加 L₂。

### 本次审查踩过的坑

见 [[iterator-list-pitfalls]]，三个坑全踩了：迭代器不检查 end、空列表 back()、while 条件混入去重导致丢尾。

---

## 习题 3.24: 移动语义与 Rule of Five（两栈共享数组）

### 移动语义：`&&` 如何避免多余的构造

**问题**：假设函数只接受 `const T&`：
```cpp
void push(const T& x) {
    arr_[size_] = x;    // 一定是拷贝
}
```
调用者传递临时对象 `push(999)` 或显式 `push(std::move(obj))` 时，x 仍然走拷贝——即便原对象马上就没用了。

**解决**：增加一个接收 `T&&` 的重载：
```cpp
void push(T&& x) {                    // ① T&& 让编译器知道：这是"接受临时值"的版本
    arr_[size_] = std::move(x);       // ② 函数体内接管 x 的内存，而非复制
}
```
- 编译器自动选择：传左值 → `push(const T&)`；传右值（临时对象、`std::move()` 结果）→ `push(T&&)`。
- **本质**：`std::move` 不移动任何东西——它是一个 cast，把对象标记为"可被掠夺"。紧接着的 `operator=` 才是真正搬走资源的操作。
- **好处**：无需构造一份临时副本再丢进容器——直接接管原对象的内存（对 `T` 为 `std::string` 这类持有堆内存的类型尤其有效）。

### 移动构造：直接接管指针

```cpp
DoubleStacks(DoubleStacks&& other) noexcept
:arr_{other.arr_}             // ① 直接抄指针——不分配新数组
,left_size_{other.left_size_}
,right_size_{other.right_size_}
,N_{other.N_} {
    other.arr_ = nullptr;     // ② 原对象置空，防止析构时 delete
    other.N_ = other.left_size_ = other.right_size_ = 0;
}
```
三步逻辑：(1) 接管资源（指针赋值），(2) 接管元数据（size/N），(3) 让原对象进入"空壳"状态（`nullptr + 0`）。`noexcept` 确保 `std::vector<DoubleStacks>` 扩容时优先走移动而非拷贝。

### 拷贝赋值：copy-and-swap 惯用法

```cpp
DoubleStacks& operator=(const DoubleStacks& other) {
    if(this == &other) return *this;   // ① 自赋值检查
    DoubleStacks temp(other);           // ② 先分配新内存、复制数据（拷贝构造）
    std::swap(*this, temp);             // ③ 交换指针和元数据
    return *this;                       // ④ temp 析构，释放旧资源
}
```

**为什么是"先分配再 swap"而非"先 delete 再分配"？**

| 方案 | 步骤 | 异常安全性 |
|------|------|-----------|
| 先 delete 再 new | `delete[] arr_` → `arr_ = new T[...]` → 复制 | ❌ 若 new 抛异常，`arr_` 已悬空，对象不可用 |
| copy-and-swap | `temp = copy(other)` → `swap(*this, temp)` | ✓ temp 构造失败 → `*this` 毫发无损；构造成功 → swap 不抛异常 |

**关键洞察**：分配风险最大的操作（`new`、元素复制）全部在 `temp` 身上完成。`temp` 崩溃？函数退出，`*this` 原封不动。`temp` 成功？`swap` 只是交换指针和三个 `size_t`，不可能失败。

### 移动赋值：直接接管

```cpp
DoubleStacks& operator=(DoubleStacks&& other) noexcept {
    if(this == &other) return *this;
    delete[] arr_;               // ① 释放自己已有的资源
    arr_ = other.arr_;           // ② 接管 other 的资源
    // ... size/N_ 同理 ...
    other.arr_ = nullptr;        // ③ 让 other 变空壳
    return *this;
}
```
移动赋值的代价：一次 `delete[]` + 四次值拷贝。拷贝赋值的代价：一次完整的内存分配 + 完整复制 + swap。移动的常量因子远小于拷贝。

### 初始化列表顺序与 `-Wreorder`

成员初始化的顺序**永远**由声明顺序决定，与初始化列表中的书写顺序无关：
```cpp
private:
    T* arr_;             // ← 第 1 个初始化
    size_t left_size_;   // ← 第 2 个
    size_t right_size_;  // ← 第 3 个
    size_t N_;           // ← 第 4 个
```
```cpp
// ❌ 写成了 arr_, N_, left_size_, right_size_ → -Wreorder
// ✓ 改成 arr_, left_size_, right_size_, N_       → 无警告
```
即使功能碰巧正确（因为 `left_size_` 不依赖 `this->N_`），顺序不一致就是警告。养成习惯：初始化列表顺序 = 声明顺序。

### 拷贝构造函数：只复制有效元素

```cpp
for(size_t i = 0; i < left_size_; ++i)
    arr_[i] = other.arr_[i];
for(size_t i = 0; i < right_size_; ++i)
    arr_[N_ - i - 1] = other.arr_[N_ - i - 1];
```
两段循环只复制左右栈各自占用的区间，跳过中间空闲槽位。与"一股脑复制全部 N_ 个"相比，当 N_ 很大而元素很少时省掉了不必要的拷贝。

---

## 习题 3.25a: findMin O(1) 栈 — 双栈法

### 题目
设计支持栈 push/pop 和 findMin 的数据结构，全部操作 O(1) 最坏时间。

### 解法：维护最小值栈
- 主栈 `stack_` 存所有元素
- 辅助栈 `min_` 与主栈同步增长/收缩，`min_[i]` = `stack_[0..i]` 的最小值
- `push(x)`: `min_.push_back(min_.empty() || x < min_.back() ? x : min_.back())`
- `pop()`: 两个栈同时 `pop_back()`
- `findMin()`: 返回 `min_.back()`
- 均摊 O(1)，最坏也是 O(1)（每次 push 只做一次比较 + push_back）

### 审查收获：getter 函数的返回类型应为 `const T&`

**问题**：最初 `min()` 返回 `T`（按值返回）：
```cpp
T min() const {
    T val = min_.back();   // 拷贝 1：从 vector 到局部变量
    return val;            // 拷贝 2（或移动）：从局部变量到调用方
}
```
对 `int` 无影响，但对重 `T`（如 `std::string`）每次调用触发两次拷贝。

**改进**：返回 `const T&`（const 引用）：
```cpp
const T& min() const {
    return min_.back();    // 零拷贝：直接透传 vector 内部的引用
}
```

**为什么是 `const T&` 而非 `T&`？**
- 函数是 `const` 成员函数，内部 `min_` 被视为 const，`min_.back()` 返回 `const T&`
- 返回非 const `T&` = 允许调用方通过引用修改内部数据 → 破坏封装（能改最小值但主栈不变）

**调用方的选择权**：
```cpp
const auto& m = s.min();   // 零拷贝，只读别名
auto m = s.min();          // 独立副本，可修改，发生一次拷贝
```
`auto` 会剥掉引用和顶层 const，所以 `auto m` 得到的是 `T`（独立副本），可以随便改。

**这是 STL 的惯用做法**：`std::vector::back()`、`std::vector::front()` 都返回引用，把要不要拷贝的选择交给调用方。

### `push()` 的异常安全性
当前实现：
```cpp
void push(const T& x) {
    stack_.push_back(x);      // ① 先压主栈
    min_.push_back(...);      // ② 再压辅助栈 — 若抛 bad_alloc，两栈失同步
}
```
① 成功后 ② 失败（如 `std::bad_alloc`），`stack_` 已增长而 `min_` 未增长 → 破坏不变量。对 `int` 无关紧要（push_back 不抛），但对泛型 `T` 是隐藏风险。

修复方向（非必须，认知即可）：
- `reserve` 预分配确保不抛
- 或先算值、用 scope guard 回滚

---

## 习题 3.2: 只改链接交换相邻节点

### 题目
交换链表中相邻两个元素，只调整链接（不改 data 字段）。

### 实现
- **SList（单链表）**：`swap_after(prev)` 交换 `prev->next` 和 `prev->next->next`。哨兵节点使 `swap_first_two()` = `swap_after(head)`，与中间交换统一。
- **DList（双链表）**：双向遍历优化——`i < theSize/2` 从头走，否则从尾走。6 指针更新。

### 收获
- 单链表交换相邻节点只需操作前驱——`prev→A→B→C` 变为 `prev→B→A→C`，三步指针重连。
- DList 6 指针更新涉及 `a_prev`, `b_next` 两个"邻居锚点" + 两个节点的内部连接。
- 双向遍历优化：从尾走时定位到第 `i+1` 个节点，`b = a->prev` 获取第 `i` 个，保持 if/else 分支后 a/b 角色统一。

---

## 习题 3.20: 惰性删除列表

### 题目
实现惰性删除：删除操作只标记节点 `in_list = false`，不物理移除；当已删节点数达到阈值时批量清除。

### 设计
- **哨兵双链表**：`head`/`tail` 哨兵 `in_list = false`，永不参与数据操作。
- **双重计数**：`the_size`（活节点数）、`deleted_size`（标记删除数）。
- **阈值触发**：`the_size == deleted_size` 时自动调用 `release()` 物理清除。
- **Rule of Five**：拷贝/移动构造+赋值+析构全部实现。

### 遍历中前进与跳过的顺序（关键 bug）

**错误模式**（先跳过后前进）：
```cpp
for(size_t j = 0; j < i; ++j) {
    while(!curr->in_list) curr = curr->next;  // 跳过已删
    curr = curr->next;                         // 前进
}
```
问题：最后一步前进后不检查 `in_list`，`delete_node(curr)` 可能落在一个已标记删除的节点上——重复删除 → 计数错乱。

**正确模式**（先前进后跳过）：
```cpp
for(size_t j = 0; j < i; ++j) {
    curr = curr->next;                    // 先前进
    while(!curr->in_list) curr = curr->next;  // 再跳过已删
}
```
保证每次迭代结束 `curr` 一定指向活节点。

### 移动语义与析构安全

**被移走对象的析构**：移动构造/赋值后 `other.head = other.tail = nullptr`。析构函数 `clear()` 中 `head->next` 对 nullptr 解引用 → SEGV。

**修复**：`clear()` 中加 `if(head)` guard，移空对象 safe to destroy：
```cpp
void clear() {
    if(head) {
        Node* curr = head->next;
        // ...
    }
}
// 析构函数中 delete nullptr 合法
```

### 拷贝构造的计数错误

**错误做法**：初始 `the_size{other.the_size}`，然后 `push_back` 每轮 `++the_size` → 最终 `the_size = 原值 + 总节点数`。

**正确做法**：初始化为 0（`init()`），节点逐个 push_back 并复制 `in_list` 标记，最后直接赋值：
```cpp
the_size = other.the_size;
deleted_size = other.deleted_size;
```
覆盖掉 push_back 累积的中间值。

### 审查教训
- 模板类中未实例化的成员函数不会触发编译错误——`other.tial` 拼写错误直到移动赋值被调用才暴露。
- ASan 是最后防线，但逻辑错误（计数错乱、删错节点）不会触发——需要构造特定测试场景（惰性删除 + 再次 delete_the 跨过已删节点）。
