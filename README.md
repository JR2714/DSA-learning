# DSA: Data Structures & Algorithm Analysis

基于 Mark Allen Weiss《**Data Structures and Algorithm Analysis in C++**》（第 4 版）的个人 DSA 学习仓库。按章节顺序推进，每章包含练习代码和分析笔记。

## 进度

| Phase | 章节 | 内容 | 状态 |
|-------|------|------|------|
| 0 | Ch.1 | C++ 复习（指针/引用/动态内存/类/模板/STL） | 完成 |
| 1 | Ch.2 | 算法分析（Big-Oh / 最大子序列和 / 二分查找 / 快速幂） | 完成 |
| 2 | Ch.3 | 表、栈、队列（ADT / vector & list 实现 / 栈应用 / 循环队列） | 完成 |
| 3 | Ch.4 | 树（BST / AVL / Splay 树 / B-Tree） | 进行中 |

详见 [DSAplan.md](DSAplan.md)。

## 目录结构

```
C++_Basic/                  # Phase 0 — C++ 基础复习
Chap2_AlgorithmAnalysis/    # Phase 1 — 算法分析练习
Chap3_ListsStacksQueues/    # Phase 2 — 表、栈、队列练习
Chap4_Trees/                # Phase 3 — 树练习
Exercise/                   # Ch.1–3 选做习题
note/                       # 自动总结的章节学习记录
Weiss_code/                 # Weiss 官方源码（仅本地参考）
bin/                        # 编译产物（gitignored）
```

## 学习方法与工具

本仓库的学习过程中使用了 AI（DeepSeek）作为辅助工具：

- **学习计划框架**：AI 帮助梳理 Weiss 教材的章节脉络和知识点大纲，经本人逐项审阅调整
- **笔记整理**：部分章节笔记由 AI 辅助将零散的学习记录整理为结构化文档，内容经本人核实补充
- **少量测试框架**：个别测试代码的框架由 AI 生成初版，测试逻辑和验证用例由本人设计审查

所有核心代码实现、习题解答、算法分析均由本人独立完成。AI 在此的角色是效率工具而非思考替代——每一行代码都经过我的理解和验证。

- **教材**：Mark Allen Weiss, *Data Structures and Algorithm Analysis in C++*, 4th Edition
- **官方源码**：[users.cs.fiu.edu/~weiss/](https://users.cs.fiu.edu/~weiss/)
- **学习计划**：[DSAplan.md](DSAplan.md)