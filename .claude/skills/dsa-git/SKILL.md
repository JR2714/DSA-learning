---
name: dsa-git
description: "标准化 git 提交流程：分步确认 staging、commit message、push。当用户说提交、git一下、push时使用。"
argument-hint: "[可选：额外要包含或排除的文件路径]"
allowed-tools: Bash
user-invocable: true
---

# DSA Git 提交流程

你是 Jacob 的 git 助手。按以下流程分步执行提交，**每步暂停询问确认，不跳步**。

## 流程

### 1. 检查状态

```bash
git status
```

列出所有变更：已修改、未跟踪文件。向用户报告。

### 2. 确认暂存范围

向用户建议应该纳入本次提交的文件范围：
- 优先纳入 DSA 学习相关的代码和笔记
- 配置文件（`.gitignore`、`.vscode/`、`.claude/`）如果用户明确要求则纳入
- 不相干的文件建议排除

**询问用户确认**后执行 `git add <files>`。

### 3. 展示 diff 并确认提交

```bash
git diff --cached
# 或文件多时先
git diff --cached --stat
```

展示完整 diff。然后**拟好 commit message**，格式：

```
<简短中文概括>

- <具体变更1>
- <具体变更2>
- ...

Co-Authored-By: Claude <noreply@anthropic.com>
```

Commit message 规范：
- 主题行用中文，简洁概括本次改动
- 正文用 `- ` 列出每项具体变更
- 末尾始终追加 `Co-Authored-By: Claude <noreply@anthropic.com>`

**询问用户确认 commit message**后执行 `git commit -m "..."`。

### 4. 确认 push

```bash
git log --oneline -3 && echo "---" && git status
```

展示本地领先状态。如果工作区干净、有未推送提交，**询问用户确认**后执行 `git push`。

## 约束

- **每步必问**：staging 范围、commit message、push 都要分别确认，不要跳步
- 如果用户说"执行"、"可以"、"push"等，只执行当前这一步，不自动跳到下一步
- 如果工作区干净无变更，直接告知用户
