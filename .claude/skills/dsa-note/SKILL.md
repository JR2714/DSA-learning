---
name: dsa-note
description: "保存 DSA 学习过程中的记忆或笔记。当用户说记住这个、保存笔记、记录一下、更新进度时使用。"
argument-hint: "[要记录的内容描述]"
allowed-tools: Read, Write, Edit, Bash, Grep, Glob
user-invocable: true
---

# DSA 笔记与记忆管理

你是 Jacob 的学习助手。当需要持久化保存信息时，按以下流程操作。

## 步骤 1：判断类型

首先向用户确认要保存的内容属于哪种：

| 类型 | 说明 | 存放位置 |
|------|------|---------|
| **记忆** | 跨对话需要的持久事实：偏好变更、资源路径、约定调整、学习进度更新 | `~/.claude/projects/-home-jacob-DSA/memory/` |
| **学习笔记** | 当前 Phase 的知识总结：概念理解、算法要点、常见错误、调试技巧 | 需询问用户（见步骤 2） |

## 步骤 2：笔记存放位置（仅笔记类型）

如果内容是学习笔记，**必须询问用户**写在哪里：

> 笔记写在哪里？
> 1. 已有文件：`C++_Basic/CppBasic.md`（C++ 复习笔记）
> 2. 新建 Phase 专属笔记：如 `notes/phase1-analysis.md`
> 3. 其他位置（请指定）

不要在未确认路径的情况下写入。

## 步骤 3：写入记忆（仅记忆类型）

如果是记忆类型，按以下规范操作：

1. **先查重**：读取 `~/.claude/projects/-home-jacob-DSA/memory/MEMORY.md`，检查是否已有相关记忆
2. **更新而非新建**：如果已有文件覆盖同一主题，编辑现有文件而非创建新文件
3. **命名规范**：新文件用 `kebab-case.md`，`name` 字段用简短的英文 slug
4. **必要字段**：
   ```markdown
   ---
   name: <kebab-case-slug>
   description: <一句话描述>
   metadata:
     type: user | feedback | project | reference
   ---
   <内容>
   ```
5. **链接相关记忆**：在内容中使用 `[[other-memory-name]]` 链接到相关记忆
6. **更新索引**：在 `MEMORY.md` 中添加一行 `- [Title](file.md) — 一句话描述`

## 步骤 4：更新学习进度（如涉及）

如果保存的内容涉及进度变更（如 Phase 完成），同步更新：
- `~/.claude/projects/-home-jacob-DSA/memory/learning-progress.md`
- 如有需要，`/home/jacob/DSA/DSA学习计划.md` 中对应 Phase 的完成标记

## 步骤 5：确认

写入完成后，简短告知用户保存了什么、存在哪里。
