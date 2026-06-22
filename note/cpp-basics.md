# C++ 基础回顾笔记

> 教材：Mark Allen Weiss, *Data Structures and Algorithm Analysis in C++* (4th Edition)  
> 参考：cppreference.com | 《C++ Primer (5th)》| Effective Modern C++

---

## 第 1 课：指针基础

### 核心概念

**指针**：存储内存地址的变量。

```cpp
int x = 42;
int* p = &x;    // p 存 x 的地址，& 取地址
*p = 100;       // * 解引用，等价于 x = 100
```

**`*` 和 `&` 是互逆运算符**：`*&x` 就是 `x`。

### 指针与数组

数组名退化为指向首元素的指针，`arr[i]` 等价于 `*(arr + i)`。

```cpp
int arr[5] = {10, 20, 30, 40, 50};
int* p = arr;       // p 指向 arr[0]
*(p + 2);           // 等价于 arr[2]，值为 30
```

### 指针算术

`p + n` 前进 `n * sizeof(T)` 字节，两个指针相减得到元素个数。

### `nullptr`（C++11）

空指针字面量。**永远用 `nullptr`，不要用 `NULL` 或 `0`**。

```cpp
int* p = nullptr;
if (!p) { /* p 为空 */ }
```

### `const` 与指针的三种组合

| 写法 | 含义 |
|------|------|
| `const int* p` | 指向的内容只读，p 可改指向 |
| `int* const p` | p 不可改指向，内容可改 |
| `const int* const p` | 都不能改 |

### 开发习惯

- 编译必须加 `-Wall -Wextra`，零警告是底线
- 循环变量类型与比较对象一致（`int` vs `size_t` 会出警告）
- 不在循环中硬编码数组长度
- `i < n` 优于 `i <= n-1`（后者在 n=0、i 为 `size_t` 时下溢）

---

## 第 2 课：引用

### 核心概念

**引用就是别名**。不是对象，是已有变量的另一个名字。

```cpp
int x = 42;
int& r = x;     // r 绑定到 x
r = 100;        // 等价于 x = 100
```

### 引用的铁律

1. **必须初始化**：`int& r;` 编译错误
2. **不可重新绑定**：`r = y;` 只是赋值，不是重新绑定
3. **不存在空引用**

### 三种传参方式

| 方式 | 语法 | 拷贝？ | 改原值？ | 使用场景 |
|------|------|--------|----------|----------|
| 传值 | `T x` | 是 | 否 | 小类型（int、指针） |
| 传引用 | `T& x` | 否 | 是 | 需修改实参 |
| 传 const 引用 | `const T& x` | 否 | 否 | 大对象只读 |

**经验法则**：`sizeof(T) > 16` 字节或非基本类型，优先用 `const T&`。

### const 引用的特殊能力

可以绑定到临时对象并延长其生命周期：

```cpp
const int& r = 42;                    // ✅
const std::string& s = "hello";       // ✅ 隐式构造临时 string
```

### 函数返回引用

**不要返回局部变量的引用！** 返回参数的 const 引用是安全的（调用者负责生命周期）。

### 指针 vs 引用

| 指针 | 引用 |
|------|------|
| 可为 `nullptr` | 不可为空 |
| 可重新绑定 | 不可重新绑定 |
| `*p` 解引用 | 用起来像普通变量 |
| 适合所有权传递、可选参数 | 适合函数参数、别名 |

---

## 第 3 课：动态内存

### 栈 vs 堆

| 特性 | 栈 | 堆 |
|------|----|----|
| 管理 | 编译器自动 | 程序员手动 `new`/`delete` |
| 生命周期 | 作用域结束销毁 | 直到 `delete` |
| 大小 | ~1-8 MB | 系统可用内存 |
| 速度 | 极快 | 较慢 |

```cpp
int x = 42;            // 栈
int* p = new int(42);  // p 在栈上，指向的 int 在堆上
delete p;              // 必须手动释放
```

### `new` / `delete`（单对象）

```cpp
int* p = new int(42);   // 分配并初始化为 42
int* p2 = new int{};    // 值初始化 → 0
delete p;
p = nullptr;            // 防御野指针
```

### `new[]` / `delete[]`（数组）——必须配对！

```cpp
int* arr = new int[10]();   // () 值初始化，全部为 0
int* arr2 = new int[5]{1, 2, 3};  // 前 3 个指定，其余 0
delete[] arr;               // 必须 delete[]，不能用 delete
```

**混用的后果**：未定义行为（`new[]` 可能在数组前记录元素个数，`delete` 不读）。

### `new T[n]` vs `new T[n]()`

- `new int[5]` → 垃圾值
- `new int[5]()` → 全部 0
- `new int[5]{}` → 全部 0（C++11）

对基本类型一定要记得初始化。

### 内存泄漏

分配了堆内存但忘了释放，指针变量销毁后堆上的内存永远丢失。

### 野指针 & 双重释放

```cpp
int* p = new int(42);
delete p;
// p 现在是野指针
*p = 10;     // ❌ 未定义行为
delete p;    // ❌ 双重释放

// 防御：
delete p;
p = nullptr;   // 好习惯
```

### 代码风格要点

- `delete[] p;` 不是 `delete []p;`（`delete[]` 是一个运算符）
- `*(p + i - 1)` 二元运算符两侧留空格
- `for (size_t i = 0; i < n; i++)` 循环变量与边界类型一致
- `#include` 中间无空格
- 边界情况 N=0：`new T[0]` 合法但返回的指针不可解引用

---

## 第 4 课：类与对象（Rule of Three）

### 核心概念

类是 C++ 封装数据和行为的核心工具。一个管理动态内存的类必须正确处理 **拷贝控制**。

### 类的基本结构

```cpp
class IntArray {
private:                          // 默认 private
    int* data_;                   // 成员变量用后缀 _ 或 m_ 标记
    size_t size_;

public:
    // 1. 构造函数
    IntArray(size_t n);           // 普通构造
    // 2. 析构函数
    ~IntArray();                  // 清理资源
    // 3. 拷贝构造函数
    IntArray(const IntArray& other);
    // 4. 拷贝赋值运算符
    IntArray& operator=(const IntArray& other);

    // 访问器
    size_t size() const;
    int& operator[](size_t i);
    const int& operator[](size_t i) const;
};
```

### 构造函数 & 初始化列表

**初始化列表** 是初始化成员变量的正确方式（赋值体不是）。

```cpp
IntArray::IntArray(size_t n)
    : data_(new int[n]())        // 初始化列表 — 真正的初始化
    , size_(n)
{
    // 构造函数体 — 此时成员已经初始化完毕
}
```

为什么用初始化列表？
- const 成员、引用成员、无默认构造函数的成员**必须**在初始化列表中初始化
- 效率更高（避免"默认初始化 → 再赋值"的两步操作）
- `new` 分配失败会抛 `std::bad_alloc`，对象不会构造成功

**默认构造函数**：无参（或全有默认值）的构造函数。
```cpp
IntArray() : data_(nullptr), size_(0) {}
```

### 析构函数

对象销毁时自动调用。负责释放对象持有的资源。

```cpp
IntArray::~IntArray() {
    delete[] data_;    // 释放数组内存
    data_ = nullptr;   // 防御性置空（可选，但好习惯）
}
```

### 拷贝构造函数

**何时调用**：
- `IntArray b = a;` （用已有对象初始化新对象）
- `IntArray b(a);` （直接初始化）
- 传值参数 `void f(IntArray arr)` （不推荐——用 const 引用！）
- 返回值 `IntArray f() { IntArray x; return x; }` （可能被优化掉，见 RVO/NRVO）

```cpp
IntArray::IntArray(const IntArray& other)
    : data_(new int[other.size_])       // 分配新内存
    , size_(other.size_)
{
    for (size_t i = 0; i < size_; i++)
        data_[i] = other.data_[i];      // 逐元素拷贝 → 深拷贝
}
```

### 拷贝赋值运算符

**何时调用**：两个对象都已存在，`a = b`。

与拷贝构造的关键区别：**被赋值对象可能已经持有资源，需要先释放**。还必须防范**自赋值**。

```cpp
IntArray& IntArray::operator=(const IntArray& other) {
    if (this == &other)                 // ⚠️ 自赋值检查！
        return *this;

    delete[] data_;                     // 1. 释放旧资源

    size_ = other.size_;
    data_ = new int[size_];             // 2. 分配新资源
    for (size_t i = 0; i < size_; i++)
        data_[i] = other.data_[i];      // 3. 拷贝数据

    return *this;                       // 4. 返回 *this（支持链式赋值 a = b = c）
}
```

### Rule of Three（三法则）

> 如果一个类**需要自定义析构函数、拷贝构造函数或拷贝赋值运算符中的任何一个**，那么它几乎肯定需要自定义**全部三个**。

**为什么？** 因为需要自定义这三者之一，通常意味着类管理了某种资源（堆内存、文件句柄、锁等）。编译器默认生成的版本做的是**浅拷贝**（逐成员拷贝），对于指针只拷贝地址，导致多个对象指向同一块内存 → 双重释放。

```cpp
// 编译器默认生成的行为 —— 通常是错的！
IntArray b = a;  // b.data_ 和 a.data_ 指向同一块内存
                 // 析构时双重释放 → 未定义行为 ☠️
```

### 拷贝构造 vs 拷贝赋值（一图区分）

```
IntArray a(5);       // 构造函数
IntArray b = a;      // 拷贝构造 — b 是新对象
IntArray c(a);       // 拷贝构造 — c 是新对象
c = a;               // 拷贝赋值 — c 已存在
```

### `= default` 和 `= delete`（C++11）

```cpp
IntArray(const IntArray&) = delete;             // 禁止拷贝
IntArray& operator=(const IntArray&) = delete;  // 禁止拷贝赋值
~IntArray() = default;                          // 使用编译器默认生成
```

### const 成员函数

不修改对象状态的函数应标记为 `const`：

```cpp
size_t size() const { return size_; }
```

const 对象只能调用 const 成员函数。这是 const 正确性的一部分。

### 开发习惯

- 成员变量用后缀 `_` 与局部变量区分（如 `data_`, `size_`）
- 构造函数优先用初始化列表，不在函数体内赋值
- 管理资源的类必须实现或禁止 Rule of Three
- 拷贝赋值先检查自赋值，再释放旧资源
- 拷贝赋值返回 `*this`（引用），支持链式赋值
- `const` 成员函数不会修改对象——写一个不加 const 的 getter 是坏习惯
- 拷贝构造中 `new T[n]()` 后立刻循环赋值 → 双重初始化，去掉 `()`
- 遍历对象用**自己的** `size()`，别用其他对象的——即使它们相等，语义不对

---

## 第 5 课：RAII 与移动语义

### RAII（Resource Acquisition Is Initialization）

> 构造时获取资源，析构时释放资源。对象的生命周期 = 资源的持有期。

```cpp
// IntArray 就是 RAII 的典范
IntArray::IntArray(size_t n) : data_(new int[n]()), size_(n) {}  // 获取
IntArray::~IntArray() { delete[] data_; }                         // 释放
```

**为什么重要**：
- 异常安全：即使抛异常，局部对象的析构函数保证执行
- 不会忘记释放：离开作用域自动释放
- C++ 核心惯用法：智能指针、容器、文件流都基于 RAII

### 左值 vs 右值

| 概念 | 说明 | 例子 |
|------|------|------|
| 左值 (lvalue) | 有名字、可取址、可持久 | `x`, `arr[3]`, `*p` |
| 右值 (rvalue) | 临时的、即将消亡 | `42`, `x+y`, `std::string("hi")` |

### 右值引用 `T&&`

C++11 引入，专门绑定到右值：

```cpp
int&& r = 42;            // ✅ 绑定到右值
int x = 10;
int&& r2 = std::move(x); // ✅ std::move 把左值转成右值引用
// int&& r3 = x;         // ❌ 不能绑左值
```

**`std::move` 不移动任何东西**——它只做类型转换：左值 → 右值引用，表示"这个对象我不再需要了，你可以偷它的资源"。定义在 `<utility>`。

### 移动构造函数

"偷"资源而不是拷贝——**O(1) 而非 O(n)**：

```cpp
IntArray::IntArray(IntArray&& other) noexcept   // ⚠️ 必须 noexcept
    : data_(other.data_)                         // 直接接管指针
    , size_(other.size_)
{
    other.data_ = nullptr;                       // 留空，让 other 可安全析构
    other.size_ = 0;
}
```

### 移动赋值运算符

```cpp
IntArray& IntArray::operator=(IntArray&& other) noexcept {
    if (this == &other)           // 自赋值检查
        return *this;
    delete[] data_;               // 释放自己的旧资源
    data_ = other.data_;          // 偷
    size_ = other.size_;
    other.data_ = nullptr;        // 留空
    other.size_ = 0;
    return *this;
}
```

### Rule of Five（五法则）

> Rule of Three + 移动构造 + 移动赋值 = **Rule of Five**

1. `~T()` — 析构
2. `T(const T&)` — 拷贝构造
3. `T& operator=(const T&)` — 拷贝赋值
4. `T(T&&) noexcept` — **移动构造**
5. `T& operator=(T&&) noexcept` — **移动赋值**

### `noexcept` 为什么必须

```cpp
IntArray(IntArray&&) noexcept = default;
```

STL 容器（如 `std::vector`）扩容时，如果移动构造不是 `noexcept`，就**退化到拷贝**（为了强异常保证）。不加 `noexcept` → 移动优化永不被调用。

### 编译器何时自动生成移动操作

| 你定义了 | 编译器行为 |
|----------|-----------|
| 什么都没定义 | 全 5 个都生成 |
| 定义了拷贝/析构之一 | **不生成移动操作**，退化到拷贝 |
| 定义了移动操作 | 拷贝操作被 `= delete` |

### `const T&&` 的陷阱

```cpp
const IntArray cia(3);
a = std::move(cia);  // std::move(cia) → const IntArray&&
// const T&& 不能绑定到 T&&（非 const），只能绑定到 const T&
// → 调用的是拷贝赋值，不是移动赋值！
```

### 常见错误

**❌ 手动调用析构函数**
```cpp
obj.~IntArray();  // 永远不要对栈对象这样做！
// 离开作用域时自动析构 → 双重析构 → double free
```

RAII 的整个目的就是让你**忘记手动释放**。编译器全自动管理。

### 开发习惯

- 管资源的类必须实现 Rule of Five（或 `= delete` 禁止）
- 移动操作必须加 `noexcept`
- 移动后原对象必须处于"可安全析构"状态（通常是 `nullptr` + 零值）
- `std::move` 需 `#include <utility>`
- 永远不要手动调用析构函数——用 `{}` 嵌套作用域控制生命周期
- 析构函数中 `delete[]` 后置 `nullptr` 是防御性编程（防止野指针复用）

---

## 第 6 课：模板基础

### 为什么需要模板

不用模板 → 每种类型写一个类 → 代码重复：

```cpp
class IntArray { int* data_; ... };
class DoubleArray { double* data_; ... };
// 换汤不换药，维护噩梦
```

模板让你**写一套代码**，编译器为每个类型**自动生成**一份。

### 函数模板

```cpp
template <typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}

int x = max(10, 20);                  // T = int，自动推导
double y = max(3.14, 2.71);           // T = double
```

编译器在**编译期**根据调用自动推导 `T`，为每个用到的类型生成真实函数——这叫**模板实例化**。

### 类模板

```cpp
template <typename T>
class Array {
    T* data_;           // 原来是 int* data_
    size_t size_;
public:
    Array(size_t n);
    ~Array();
    // ... Rule of Five ...
};
```

**类外定义成员函数的语法**：

```cpp
template <typename T>         // 每个函数前都要写
Array<T>::Array(size_t n)     // 类名必须带 <T>
    : data_(new T[n]())       // new T[n]() 对任意 T 都是值初始化
    , size_(n)
{}
```

三条记忆点：
1. 每个类外成员函数前加 `template <typename T>`
2. 类名后必须带 `<T>`
3. 函数体内的 `T` 就是用户指定的类型

### `typename` vs `class`

```cpp
template <typename T>   // ✅ 现代推荐
template <class T>      // ✅ 等价，C++98 遗留
```

在模板参数声明中**完全等价**。用 `typename` 更清晰表达"任意类型"。

### 模板成员函数的参数名

```cpp
template <typename T>
class Array { ... };

// 成员函数定义时，参数名可以不同！
template <typename L>     // L 也可以！
size_t Array<L>::size() { ... }
```

编译器按**位置**匹配模板参数，不按名称。但实践中应统一用 `T`——否则读者来回猜。

### 编译模型

模板的声明和定义**必须在同一文件中**（头文件）。编译器必须看到完整定义才能在实例化时生成代码。不像普通函数可以 `.h` 声明 + `.cpp` 定义。

### 非类型模板参数

```cpp
template <typename T, size_t N>
class StaticArray {
    T data_[N];  // 栈上数组，编译期固定大小
};

StaticArray<int, 100> arr;  // 100 是编译期常量
```

这就是 `std::array` 的原理——无堆分配。

### 值初始化 `new T[n]()`

```cpp
new int[5]()       // 全部 0
new double[5]()    // 全部 0.0
new string[5]()    // 全部 ""
```

`()` 对基本类型清零，对类类型调用默认构造函数。模板编程中确保安全初始化的关键手段。

### 开发习惯

- 模板声明和定义都放头文件
- 类模板成员函数前统一写 `template <typename T>`
- 参数名统一用 `T`，不玩花样
- `new T[n]()` 的值初始化对模板是安全底线
- 测试模板至少用 3 种类型：基本类型（`int`）、浮点（`double`）、类类型（`std::string`）
- 模板化不改变 Rule of Five 的要求——仍应测试拷贝/移动
- `const` 正确性在模板化时容易丢失——每个成员函数都要复查

---

## 第 7 课：STL 概览

### STL 四大组件

| 组件 | 作用 | 例子 |
|------|------|------|
| **容器** | 存储数据 | `vector`, `list`, `map`, `set` |
| **算法** | 操作数据 | `sort`, `find`, `unique` |
| **迭代器** | 连接容器和算法 | `begin()`, `end()` |
| **函数对象** | 自定义行为 | lambda, `std::greater<>` |

### 序列容器速查

| 容器 | 底层 | 随机访问 | 头插入 | 尾插入 | 中间插入 |
|------|------|----------|--------|--------|----------|
| `vector` | 动态数组 | O(1) | O(n) | O(1)* | O(n) |
| `list` | 双向链表 | ❌ | O(1) | O(1) | O(1)** |
| `deque` | 分段数组 | O(1) | O(1) | O(1) | O(n) |

*vector 尾插入是**均摊** O(1)（扩容时偶尔 O(n)）
**list 中间插入是 O(1)，但找到插入位置需要 O(n) 遍历

**选择原则**：默认用 `vector`，有特殊需求再看别的。

### 关联容器速查

```cpp
std::set<int> s = {3, 1, 4, 1};  // {1, 3, 4} 自动排序去重
std::map<std::string, int> ages;  // 有序键值对（红黑树）
ages["Jacob"] = 22;

std::unordered_set<int> us;       // 哈希表，无序，O(1) 平均
std::unordered_map<std::string, int> um; // 哈希表
```

### 容器适配器

- `std::stack<T>` — LIFO，`push()`/`pop()`/`top()`
- `std::queue<T>` — FIFO，`push()`/`pop()`/`front()`
- `std::priority_queue<T>` — 最大元素先出（堆）

### 核心算法 `#include <algorithm>`

```cpp
std::sort(v.begin(), v.end());                         // O(n log n)
std::sort(v.begin(), v.end(), [](int a, int b) {       // lambda 自定义
    return a > b;  // 降序
});
auto it = std::find(v.begin(), v.end(), 4);            // O(n)
std::binary_search(v.begin(), v.end(), 4);             // O(log n)，需已排序

// remove-erase idiom（去重标准做法）
std::sort(v.begin(), v.end());
auto it = std::unique(v.begin(), v.end());  // 把重复元素移到末尾，返回新 end
v.erase(it, v.end());                        // 真正删除
```

### 迭代器 = 泛化指针

```cpp
auto it = v.begin();   // 指向第一个元素
*it;                   // 解引用
++it;                  // 前进
v.end();               // 尾后（不指向任何元素）
// 所有算法都用 [begin, end) 半开区间
```

### 范围 based for 循环（C++11）

```cpp
for (const auto& x : container)  // 推荐：不拷贝，不可改
for (auto& x : container)        // 不拷贝，可修改
for (auto x : container)         // 拷贝，尽量避免
```

### 结构化绑定（C++17）

```cpp
std::map<std::string, int> ages;
for (const auto& [name, age] : ages)  // 直接解包 pair
    std::cout << name << " -> " << age << "\n";
```

### `std::array` vs `std::vector` vs C 数组

| | C 数组 `T[N]` | `std::array<T,N>` | `std::vector<T>` |
|---|---|---|---|
| 大小 | 编译期固定 | 编译期固定 | 运行时可变 |
| 内存 | 栈 | 栈 | 堆 |
| 边界检查 | ❌ | `at()` ✅ | `at()` ✅ |
| 赋值/传参 | 退化指针 | 正常值语义 | 正常值语义 |

### 开发习惯

- 循环变量用 `size_t` 与 `.size()` 返回类型一致
- 遍历容器优先 `const auto&`，避免意外拷贝
- 会用 `set` 去重，也要会用 `sort` + `unique` + `erase`
- `std::endl` = `\n` + flush；不需要立即刷新时用 `\n`
- 头文件显式包含：用到 `std::string` 就 `#include <string>`，不依赖间接包含
- 遍历循环中不硬编码长度，始终用 `.size()`

---

## 选做习题：Weiss Ch.1 精选

### 1.5 — 递归求二进制中 1 的个数

**题目**：递归函数返回 N 的二进制表示中 1 的个数。提示：N/2 的 1 的个数 + (N 为奇数时加 1)。

**最终代码**（简化版）：
```cpp
int numOfOne(int N) {
    if (N == 0) return 0;
    return numOfOne(N / 2) + (N % 2);
}
```

**反思**：
- `N % 2` 在偶数时等于 0、奇数时等于 1，恰好就是应该加的值——不需要 if/else 分两种 case
- `const int&` 对基本类型是反模式：引用比 int 本身还大，多一次间接寻址
- 理解了背后的二进制原理后才算真正做完这题

#### 关联知识：二进制与补码

- **计算机只有二进制**：源码 `38`、`0b100110`、`0x26` 生成同样的机器码
- **补码（Two's Complement）** 是现代标准：负数 = 正数取反 + 1，最高位权重为负
- **`N % 2` 对负数有陷阱**：`-5 % 2 = -1`，不是 1。想通用就用 `unsigned` 或 `N & 1`
- 位运算 `N & 1` / `N >> 1` 对 `unsigned` 完全安全

### 1.6 — 全排列（回溯法）

**题目**：输出字符串所有排列。`permute(const string& str)` 为驱动，`permute(string& str, int low, int high)` 递归。

**核心想法**：逐位确定。`low` 是"当前要确定的椅子"，`[low, high]` 是待排列区。

```
abc, low=0
├─ i=0: swap(a,a) → abc → 递归 low=1 → 打印 abc, acb → swap(a,a) 恢复
├─ i=1: swap(a,b) → bac → 递归 low=1 → 打印 bac, bca → swap(a,b) 恢复
└─ i=2: swap(a,c) → cba → 递归 low=1 → 打印 cba, cab → swap(a,c) 恢复
```

**最终代码结构**：
```cpp
void permute(string& str, int low, int high) {
    if (low == high)
        cout << str << endl;
    else
        for (int i = low; i <= high; i++) {
            swap(str[low], str[i]);        // 选字符 i 坐椅子 low
            permute(str, low + 1, high);   // 递归排后面的椅子
            swap(str[low], str[i]);        // 回溯：恢复原样！
        }
}
```

**关键理解**：
- **第三个 swap 是灵魂**——不恢复的话，后续循环从被污染的字符串出发，输出错乱
- **回溯 = 试探 + 撤销**。每步做选择，递归探索，返回时撤销选择
- Weiss 第二个声明有 `const`，但交换法需要修改字符串——驱动函数做一份拷贝解决
- `std::swap` 定义在 `<utility>`，显式包含更规范
- 这是 Ch.10 回溯/分支限界的预备知识，空间 O(N) 的优雅解法
