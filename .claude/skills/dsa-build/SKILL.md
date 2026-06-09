---
name: dsa-build
description: "用标准化参数编译并运行 C++ 程序：c++17、所有警告、ASan 内存检查，输出到 ./bin/。当用户需要编译运行代码时使用。"
argument-hint: "<source.cpp>"
allowed-tools: Bash
user-invocable: true
---

# DSA 标准化编译运行

用统一的编译参数编译并运行 C++ 程序。

## 编译命令

```bash
g++ -std=c++17 -Wall -Wextra -fsanitize=address -g <source> -o bin/<output>
```

- `<source>`：源文件路径（如 `C++_Basic/pointer.cpp`）
- `<output>`：可执行文件名（不含路径，默认取源文件名去 .cpp）

## 运行命令

```bash
./bin/<output>
```

## 执行步骤

1. 确认 `./bin/` 目录存在（不存在则创建）
2. 执行编译，展示编译输出
3. 若编译通过，运行程序并展示输出
4. 若 ASan 报告任何内存错误，明确指出

## 示例

```
/dsa-build C++_Basic/stl_overview.cpp
```

等效于：
```bash
mkdir -p bin
g++ -std=c++17 -Wall -Wextra -fsanitize=address -g C++_Basic/stl_overview.cpp -o bin/stl_overview
./bin/stl_overview
```
