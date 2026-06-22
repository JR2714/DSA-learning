---
name: iterator-list-pitfalls
description: Recurring bug patterns with STL iterators and list operations — from Ch.3 exercise reviews
metadata: 
  node_type: memory
  type: reference
  originSessionId: 92d98ad7-fcec-4f12-ab94-7d7c92f5a2de
---

## 迭代器与 list 常见陷阱

审查 3.1/3.4/3.5 的习题中反复出现的 bug 模式。

### 1. 迭代器解引用前不检查 `!= end()`

```cpp
while(*itr < i) ++itr;       // ✗ itr 可能已是 end()
if(*itr == i) push_back(i);  // ✗ 同上
```

`end()` 解引用是 UB。ASan 不一定能抓到（`list::end()` 可能是合法哨兵节点内存），换 STL 实现就崩。

**修法**：`while(itr != end() && *itr < i)` + `if(itr != end() && *itr == i)`。

### 2. 空容器 `.back()` 是 UB

```cpp
list<int> result;
if(x != result.back()) ...  // ✗ result 为空时 UB
```

`back()` / `front()` 对空容器无定义。这种 bug 常在首轮循环触发——前面的 while 没 push 任何东西就落到后续判断。

**修法**：`if(result.empty() || x != result.back())`。

### 3. while 条件混入业务逻辑 → 提前退出或丢尾

```cpp
while(itr != end() && *itr != result.back())  // 去重在条件里
    result.push_back(*itr++);
```

当 `*itr == back()` 时条件为假，**整个循环退出**，跳过 itr 之后所有元素。去重逻辑应放在**循环体内**用 `if`，循环条件只负责遍历。

**修法**：
```cpp
while(itr != end()) {
    if(result.empty() || *itr != result.back())
        result.push_back(*itr);
    ++itr;  // 无论如何都前进
}
```

### 教训

- 这三个模式常组合出现——有 while + 迭代器 + 去重的地方，三个坑都要检查
- ASan 的沉默不代表安全——`list::end()` 解引用在 libstdc++ 上可能落在哨兵节点的合法内存上
- [[code-review-standards]]
