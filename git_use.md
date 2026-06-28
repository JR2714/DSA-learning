# Git 基础入门

## 核心概念

Git 跟踪的是文件的快照，不是文件本身。每次 `commit` 相当于拍一张项目所有文件的照片，可以随时回到过去任何一张照片。

三个区域：

```
工作目录 (working)  →  暂存区 (staging)  →  仓库 (repository)
   你的文件              git add 后            git commit 后
```

---

## 一、配置

```bash
git config --global user.name "JR2714"        # 只做一次
git config --global user.email "你的邮箱"       # 只做一次
```

---

## 二、核心日常操作

### git status — 看状态
最常用的命令，任何时候不知道该干吗就打它：

```bash
git status
# 红色文件名 = 有改动但没暂存
# 绿色文件名 = 已暂存，等提交
# nothing to commit = 没东西要提交
```

### git diff — 看具体改了什么

```bash
git diff              # 工作区 vs 暂存区（还没 add 的改动）
git diff --staged      # 暂存区 vs 仓库（add 了但没 commit 的）
```

### git add — 把改动加入暂存区

```bash
git add file.cpp       # 加单个文件
git add *.cpp          # 加所有 cpp 文件
git add -p             # 逐块选择加哪些，很实用
```

### git commit — 拍快照

```bash
git commit -m "修复了内存泄漏"          # 提交 + 消息
git commit -am "..."                   # 跳过 add，直接提交所有已跟踪文件的改动
```

### git push — 推到 GitHub

```bash
git push                # 推到关联的远程分支
```

### git log — 看提交历史

```bash
git log --oneline       # 精简版，一行一条
git log --graph --all   # 图形化看分支
```

---

## 三、.gitignore

不是所有文件都该入仓。`.gitignore` 里的文件会被 Git 完全无视：

```gitignore
# 编译产物
*.out
test

# IDE
.vscode/

# 系统文件
.DS_Store
Thumbs.db
```

---

## 四、撤销操作

```bash
git restore file.cpp          # 撤销工作区的改动（回到上次 commit 的状态）
git restore --staged file.cpp # 从暂存区撤出（但保留改动在文件里）
git reset --soft HEAD~1       # 撤销最近一次 commit，改动回到暂存区
git reset --hard HEAD~1       # 撤销最近一次 commit，改动全部丢弃（危险）
```

---

## 五、分支

```bash
git branch feature-x          # 新建分支
git switch feature-x          # 切换到该分支
git switch -c feature-x       # 新建 + 切换，一步到位
git merge feature-x           # 把 feature-x 合到当前分支
```

---

## 日常流程

DSA 学习每天做完题之后：

```bash
cd ~/DSA
git status                     # 看看改了什么
git diff                       # 看看改的具体内容
git add *.cpp *.md             # 把源码和笔记加进去
git commit -m "Day 3: 链表反转"  # 提交
git push                       # 推到 GitHub
```
