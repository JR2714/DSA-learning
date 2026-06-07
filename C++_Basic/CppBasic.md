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
