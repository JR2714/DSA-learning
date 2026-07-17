# Ch.4 Trees — 笔记

> 练习文件：[BST 绘图](../Chap4_Trees/binary_search_tree.md) | [BST 惰性删除](../Chap4_Trees/why_lazy_del_suitable_for_bst.md) | [AVL 高度证明](../Chap4_Trees/biggest_height_of_avl.md) | [AVL 实现](../Chap4_Trees/avl_tree.h)

> 整理：刘坤（AI 辅助）

## L1: 树的初步与二叉搜索树（§4.1–4.3, pp.121–142）

---

### 1. 树的核心概念（§4.1）

**递归定义**：树为空，或由一个根节点 + 零或多个子树组成，每条边从根指向子树的根。

**基础术语**：

| 术语 | 定义 |
|------|------|
| 根 (root) | 树的最顶层节点，无父节点 |
| 叶子 (leaf) | 无子节点的节点 |
| 深度 (depth) | 从根到该节点的路径长度（边数），根深度为 0 |
| 高度 (height) | 从该节点到最深叶子的路径长度，叶子高度为 0 |
| 树的高度 | 根的高度 |
| 路径 (path) | n₁→n₂→...→nₖ，每个 nᵢ 是 nᵢ₊₁ 的父，长度 = k−1 |
| 祖先/后代 | 路径存在即为祖先关系 |

**关键等式**：N 个节点 = N−1 条边（除根外每个节点恰有一条入边）。

**实现：First-Child / Next-Sibling**：每个节点只需两个指针——`firstChild` 指向第一个孩子，`nextSibling` 指向兄弟链表。任意树都能用此方法表示。

---

### 2. 树的三种遍历（§4.1.2 + §4.2.2）

命名规则：**根节点在什么位置处理，就叫什么遍历**。

| 遍历 | 顺序 | 典型应用 |
|------|------|---------|
| **前序 (preorder)** | 根→左→右 | 目录列表（先打印目录名再看内容） |
| **后序 (postorder)** | 左→右→根 | 计算目录大小（先算完子目录再加总） |
| **中序 (inorder)** | 左→根→右 | BST 输出有序序列；表达式树产生中缀表达式 |

**后缀 → 表达式树**：与后缀求值（§3.6.3）同构。操作数压单节点树，运算符弹出两棵树组合（注意：先弹出的是右操作数）。

---

### 3. 二叉搜索树 BST（§4.3）

**BST 性质**：对每个节点 X，左子树所有值 < X，右子树所有值 > X。递归成立。

**核心操作复杂度**：全部 O(d)，d 为深度。平衡时 O(log N)，退化时 O(N)。

#### 3.1 contains（查找）

```cpp
if (t == nullptr) return false;        // 未找到
else if (x < t->element) go left;      // 小往左
else if (t->element < x) go right;     // 大往右
else return true;                       // 相等（用两次 < 判等，只依赖 < 运算符）
```

注意：**先判空**，否则访问 `t->element` 崩溃。可用 while 循环消除尾递归。

#### 3.2 findMin / findMax

- findMin：一路向左，遇 `nullptr` 则当前节点为最小
- findMax：一路向右，同上

#### 3.3 insert（插入）

```cpp
void insert(const Comparable & x, BinaryNode * & t) {
    if (t == nullptr)
        t = new BinaryNode{x, nullptr, nullptr};  // 在此挂载新叶子
    else if (x < t->element)  insert(x, t->left);
    else if (t->element < x)  insert(x, t->right);
    // 相等无操作（重复忽略）
}
```

**关键技巧：指针的引用 `BinaryNode * & t`**。递归到 `nullptr` 时，`t = new BinaryNode{...}` 直接修改了父节点的 `left` 或 `right` 指针——因为 `t` **就是** `parent->left`（或 `parent->right`）的引用，不是副本。这是 Weiss 代码中最精妙的设计之一。

#### 3.4 remove（删除）—— 最复杂的操作

三种情况：

| 情况 | 处理 |
|------|------|
| 叶子 | 直接 `delete` |
| 单孩子 | 父绕过该节点，链接其孩子 |
| **双孩子** | 用**右子树最小值**替换数据，递归删除该最小值（它最多有一个右孩子，化为前两种简单情况） |

#### 3.5 析构、拷贝、移动

- **析构**：后序遍历，先删孩子再删自己
- **拷贝**：前序 clone，先建根再递归建子树
- **移动**：直接接管 `root` 指针，源树置空

---

### 4. 函数对象替代 Comparable（§4.3.1）

Weiss 用 `Comparator isLessThan` 模板参数替代硬编码 `<` 运算符：

```cpp
template <typename Object, typename Comparator = less<Object>>
class BinarySearchTree { ... };
```

**好处**：
1. 不强制类型自带 `<` 运算符——更灵活
2. 比较逻辑可定制（如只按员工 ID 比较，忽略其他字段）
3. 函数对象便于内联优化——编译期确定调用目标，而非运行时通过函数指针间接调用
4. 可在比较函数中加权不同维度

---

### 5. 练习

- **4.1** BST 插入 `{5,3,7,2,4,6,9,1,8}` 并删除 5 的绘图 → [BST 绘图](../Chap4_Trees/binary_search_tree.md)
- **4.2** `countLeaves()` 递归 + 迭代（栈模拟）两种实现，O(N) 时间，O(H) 空间 → `Chap4_Trees/binary_search_tree_with_count_leaves.h`
- **4.3** BST 惰性删除分析 → [BST 惰性删除分析](../Chap4_Trees/why_lazy_del_suitable_for_bst.md)

## L2. AVL 树（§4.4, pp.144–158）

### 1. 为什么需要平衡

BST 平均 O(log N)，但有序输入退化为链表 → O(N)。AVL 树用**平衡条件**强制树高为 O(log N)。

### 2. 平衡条件

> 对每个节点，|height(left) − height(right)| ≤ 1，空树高度 = −1。

高度上界：约 **1.44 log(N+2) − 1.328**，证明见下。

### 3. 高度上界的证明思路

最小节点数 S(h) 递推：**S(h) = S(h−1) + S(h−2) + 1**，其中 S(0)=1, S(1)=2。

令 T(h+3) = S(h)+1，消去 +1 项得 T(h) = T(h−1) + T(h−2)，这正是 Fibonacci 递推。用 Binet 公式解出 S(h) ≈ φ^(h+3)/√5 − 1，反解 h 即得 1.44 log(N+2) − 1.328。

> 详细推导：`Chap4_Trees/biggest_height_of_avl.md`

### 4. 插入导致的不平衡：四类场景

沿插入路径向上回溯，第一个违反平衡条件的节点记作 **α**（最深的不平衡节点）：

| 案例 | 插入位置 | 修复 |
|------|----------|------|
| Case 1 (LL) | α 的左孩子的左子树 | **单旋转** `rotateWithLeftChild` |
| Case 2 (LR) | α 的左孩子的右子树 | **双旋转** `doubleWithLeftChild` |
| Case 3 (RL) | α 的右孩子的左子树 | **双旋转** `doubleWithRightChild` |
| Case 4 (RR) | α 的右孩子的右子树 | **单旋转** `rotateWithRightChild` |

1/4 对称（外侧 → 单旋），2/3 对称（内侧 → 双旋）。

### 5. 单旋转（Case 1: 左-左）

```
     k2 (α)               k1
    /   \                 /  \
   k1    Z     →        X    k2
  /  \                      /  \
 X    Y                    Y    Z
```

- k1 成为新根，k2 降为 k1 的右孩子
- Y（k1 右子树）移到 k2 左子树——Y 中所有值在 k1 和 k2 之间，BST 性质保证合法
- **旋转后子树高度 = 插入前高度** → 不需要继续向上调整！一次旋转即可

### 6. 双旋转（Case 2: 左-右）

单旋转对内侧插入无效——Y 太深，单旋转只是把它从一侧挪到另一侧。需要**两次单旋转**：

```
      k3 (α)               k3                   k2
     /    \               /   \                /   \
   k1      D     →      k2     D     →       k1     k3
  /  \                 /  \                 /  \   /  \
 A   k2               k1   C               A   B  C   D
    /  \             /  \
   B    C           A    B
  (先右旋 k1)           (再左旋 k3)
```

代码只有两行：
```cpp
void doubleWithLeftChild(AvlNode *& k3) {
    rotateWithRightChild(k3->left);  // 先转孩子
    rotateWithLeftChild(k3);         // 再转自己
}
```

### 7. 核心实现

**节点结构**：`data + left + right + height`。存高度（而非平衡因子），空节点高度 = −1。

**高度辅助函数**：
```cpp
int height(AvlNode *t) const {
    return t == nullptr ? -1 : t->height;
}
```

**balance() 核心逻辑**：
```cpp
void balance(AvlNode *& t) {
    if (t == nullptr) return;
    if (height(t->left) - height(t->right) > 1) {
        // 左子树过高 → 判断内外侧
        if (height(t->left->left) >= height(t->left->right))
            rotateWithLeftChild(t);     // LL → 单旋
        else
            doubleWithLeftChild(t);     // LR → 双旋
    } else if (height(t->right) - height(t->left) > 1) {
        // 右子树过高 → 对称判断
        if (height(t->right->right) >= height(t->right->left))
            rotateWithRightChild(t);    // RR → 单旋
        else
            doubleWithRightChild(t);    // RL → 双旋
    }
    t->height = max(height(t->left), height(t->right)) + 1;
}
```

判断内外侧的技巧：比较**孙子树高度**。`height(left->left) >= height(left->right)` → 外侧（LL）→ 单旋；否则内侧（LR）→ 双旋。

**指针引用 `*&`**：旋转函数通过引用参数直接改写父节点中的指针，递归实现因此非常简洁。

### 8. 删除

BST 删除的最后一步调用 `balance()`。与插入的区别：
- 插入判断用 `>`：`height(left->left) > height(left->right)` → 单旋
- 删除判断用 `>=`：`height(left->left) >= height(left->right)` → 单旋

等号是因为删除场景中 Y 可能和 X 一样深（插入时不可能），此时单旋仍能修复。

### 9. 踩过的坑

- **`FindMin` 条件反转**：写成 `if(!node) while(!node->left)`，导致找最小值失败，删除双孩子节点时破坏 BST 性质
- **`Contain` 缺 `return`**：递归调用 `Contain(x, node->left)` 忘记写 `return`，结果是未定义行为
- **`operator=` 自赋值缺 `return`**：`if(this != &other)` 分支外无 `return *this`
- **`const` 缺失**：私有 `Contain` 没加 `const`，公有 `const` 版调用时会编译失败（模板惰性实例化掩盖了此问题）

### 10. 练习

- **练习文件**：`Chap4_Trees/avl_tree.h`（完整实现，含插入/删除/旋转/拷贝/移动）
- **测试文件**：`Chap4_Trees/test_avl_tree.cpp`
- **高度证明**：`Chap4_Trees/biggest_height_of_avl.md`

## L3: 伸展树与 B-树（§4.5–4.7, pp.158–173）

### 1. 伸展树 Splay Tree（§4.5）

#### 1.1 动机：摊还分析

AVL 保证每个操作 O(log N) **最坏情况**。伸展树走另一条路：允许个别操作 O(N)，但任意 M 个连续操作总时间 O(M log N)，即 **摊还 O(log N)**。

核心洞察：BST 的 O(N) 最坏情况不可怕——可怕的是**一连串**坏操作。只要每次访问把节点推到根，就不可能反复"踩坑"。

#### 1.2 简单旋转——行不通（§4.5.1）

思路：每次访问后沿路径从底向上单旋转，把节点推到根。

**为什么失败**：插入 1..N 得全左链。访问 1（代价 N）→ 单旋推 1 到根，但把其他节点（如 3）推得几乎和 1 原来一样深。访问 2，再 3…总代价 Ω(N²)。单旋转只对被访问节点有利，对路径上其他节点有害。

#### 1.3 Splaying 三种情况（§4.5.2）

沿路径自底向上旋转。设 X 是当前旋转节点，P 是父节点，G 是祖父节点：

| 情况 | 条件 | 操作 |
|------|------|------|
| **zig** | P 是根 | 单旋转 X 与 P，结束 |
| **zig-zag** | X 和 P 方向不同（一个左孩一个右孩） | **AVL 双旋转**：先 X 绕 P，再 X 绕 G |
| **zig-zig** | X 和 P 方向相同（同为左孩或同为右孩） | **先转 P 绕 G，再转 X 绕 P** |

**zig-zig 的顺序很关键**——先转父节点再转自己，不是像简单旋转那样先转自己。

#### 1.4 Splaying 的效果

不只把访问节点推到根——路径上大多数节点深度**约减半**（浅节点最多下移两层）。

> Weiss p.163: "When access paths are long...the rotations tend to be good for future operations. When accesses are cheap, the rotations are not as good and can be bad."

#### 1.5 删除

1. find(x) → x splay 到根
2. 删除根 → TL（左子树）和 TR（右子树）
3. 找 TL 最大元素 → splay 到 TL 根（此时该根无右孩子）
4. TR 挂为该根右孩子

#### 1.6 优势与劣势

- ✅ 不需维护高度/平衡信息，代码比 AVL 简单
- ✅ 访问局部性好时效果好
- ❌ 严格分析困难（Ch.11 用摊还分析证明）
- ❌ 无 O(log N) 单次最坏保证

### 2. 树遍历重温（§4.6）

| 遍历 | 顺序 | 应用 |
|------|------|------|
| **inorder** | 左→节点→右 | 按排序输出 BST |
| **preorder** | 节点→左→右 | 标注深度、复制树 |
| **postorder** | 左→右→节点 | 计算高度、删除树 |
| **level-order** | 按深度 d=0,1,2... | 使用**队列**，非递归 |

三种递归遍历均为 O(N)，每节点常数工作。代码极简洁——只传节点指针，不声明多余变量。

### 3. B-树（§4.7）

#### 3.1 动机：磁盘 I/O

> 10 亿条指令 ≈ 120 次磁盘访问。磁盘访问极其昂贵。

BST 10M 记录 → ~32 次磁盘访问 ≈ 5 秒。目标：3-4 次。

**思路**：增加分支因子 M → 降低高度 → log_M(N) 替代 log_2(N)。

#### 3.2 定义（阶 M 的 B 树，实际是 B+ 树）

1. 数据项存在叶子
2. 非叶节点存 M−1 个 key；key i 是子树 i+1 的最小 key
3. 根是叶子或有 2～M 个孩子
4. 非叶节点（除根）有 ⌈M/2⌉～M 个孩子
5. 所有叶子同深度，有 ⌈L/2⌉～L 个数据项

**M 和 L 由磁盘块大小决定**。例：块 8192B，key 32B → M=228；record 256B → L=32。

#### 3.3 为什么是 ⌈M/2⌉？

- **太小或不设**：退化为二叉树，高度回到 log_2(N)
- **太大（> ⌈M/2⌉）**：删除合并时两个最小节点之和 > M，溢出，规则不自洽
- ⌈M/2⌉ 恰好是从分裂自然产生的最小值：M+1 个孩子分裂为 ⌈(M+1)/2⌉ 和 ⌊(M+1)/2⌋，较小一半 = ⌈M/2⌉

#### 3.4 插入

- 叶子未满 → 直接插入
- 叶子满 → **分裂**成两半（各 ≥ ⌈L/2⌉），更新父节点
- 父节点也满 → 向上传播分裂
- 根分裂 → 创建新根（树**唯一长高**的方式）

#### 3.5 删除

- 删除后低于 ⌈L/2⌉ → **领养**（借邻居一项）或**合并**（与邻居合并）
- 合并导致父失去孩子 → 同样策略向上传播
- 根只剩一个孩子 → 删除根，孩子成新根（树**唯一变矮**的方式）

#### 3.6 根的特殊豁免

根最少 2 个孩子：B-树从空树开始，根一开始是叶子。第一次分裂产生两个子节点和一个新根。若根也要求 ⌈M/2⌉ 个孩子，空树插入第一条数据就不可能满足。

### 4. 练习

- **练习 1**：[`Chap4_Trees/find_in_splay.md`](../Chap4_Trees/find_in_splay.md) — Splay 手推，find(2) zig-zig + find(9) zig-zag+zig
- **练习 2**：[`Chap4_Trees/why_the_rule_of_Btree.md`](../Chap4_Trees/why_the_rule_of_Btree.md) — B-树半满规则分析（退化风险 + 合并自洽性 + 根例外）