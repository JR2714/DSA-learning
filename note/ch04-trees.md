# Ch.4 Trees — 笔记

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

- **4.1** BST 插入 `{5,3,7,2,4,6,9,1,8}` 并删除 5 的绘图 → `Chap4_Trees/binary_search_tree.md`
- **4.2** `countLeaves()` 递归 + 迭代（栈模拟）两种实现，O(N) 时间，O(H) 空间 → `Chap4_Trees/binary_search_tree_with_count_leaves.h`
- **4.3** BST 惰性删除分析 → `Chap4_Trees/why_lazy_del_suitable_for_bst.md`
