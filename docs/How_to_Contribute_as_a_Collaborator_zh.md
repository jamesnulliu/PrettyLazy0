# 如何作为合作者做出贡献
🌍: |[English](./How_to_Contribute_as_a_Collaborator.md)|[中文](./How_to_Contribute_as_a_Collaborator_zh.md)|

这份文档是一种基于Git Flow的版本控制方法。
(https://nvie.com/posts/a-successful-git-branching-model/).

## 1. 克隆仓库

```bash
git clone git@github.com:jamesnulliu/PrettyLazy0.git

cd PrettyLazy0
```

## 2. 创建/切换分支

在GitHub的分支页面上，查看是否已经有适合你的贡献的现有分支。

假如你想对正则表达式添加支持，你应首先检查是否存在名为 feature/regex-support 的远程分支。

要列出所有远程分支，你应该在本地仓库目录下运行以下命令：

```bash
# List all remote branches. 
git branch -r
```

💡**注意**: 
- 有两种方法检查远程分支:
    1. 访问github仓库的分支页面查看所有现有分支。
    2. 在本地机器上，切换目录至本地仓库并运行 git branch -r 来列出所有远程分支。

### 2.1. 如果存在合适的远程分支

如果已存在名为 feature/regex-support 的远程分支，则应检查 **该分支是否已经存在于本地机器上**。

列出所有本地分支:

```bash
# List all local branches.
git branch
```

如果分支 feature/regex-support 在本地机器上已存在，应切换至该分支并从远程分支拉取新更改:

```bash
# 切换至分支 "feature/regex-support"。
git checkout feature/regex-support
# 从远程分支拉取新的更改。
git pull --no-rebase
```

若本地机器上不存在分支 feature/regex-support，则应在拉取新更改前从远程分支创建一个本地分支:

```bash
# 从远程仓库拉取新更改。
git fetch
# 创建一个新的分支命名为 "feature/regex-support" 并跟踪远程分支。
# 注意：保留 `origin` 不变。
git checkout -b feature/regex-support origin/feature/regex-support
# 从远程分支拉取新更改。
git pull --no-rebase
```

💡**注意**: 
- `git pull` 只拉取当前分支的更改。因此，在拉取前需切换至该分支。
- `--no-rebase` 选项强制合并接收到的更改与当前更改。
- 当所需分支存在于远程仓库时，有两种情况:
    1. 如果分支在本地机器上已存在，切换至该分支并从远程分支拉取新更改。
    2. 如果分支在本地机器上不存在，从远程创建一个本地分支然后拉取新更改。
- 在大多数情况下，保留 `origin` 不变。它是远程仓库的默认名称，实际上存储了仓库的URL。

### 2.2. 如果不存在合适的远程分支

如果没有适合你贡献的分支，可以根据分支命名规范从 `dev` 创建一个新分支。 [Branch Naming Convention](./Branch_Naming_Convention.md).

简单来说，分支命名应遵循以下规则:

- 对于 **功能**: `feature/<feature-name>`
- 对于 **bug修复**: `bugfix/<issue-or-bug-number>`
- 对于 **紧急修复**: `hotfix/<issue-or-bug-number>`
- 对于 **发布**: `release/<version-number>`
- 对于 **文档**: `doc/<documenation-name>`

```bash
# 确保你在 "dev" 分支上。
git checkout dev
# 从远程分支拉取新的更改。
git pull --no-rebase
# 从 "dev" 创建一个名为 "feature/regex-support" 的新分支。
git checkout -b feature/regex-support
# 将新分支推送至远程仓库，即在GitHub上创建一个远程分支。
git push origin feature/regex-support:feature/regex-support
```

返回到 [分支页面](https://github.com/jamesnulliu/PrettyLazy0/branches), 你应该能看到一个新的叫做 `feature/regex-support`的分支。

## 3. 做出你的贡献

现在你可以开始对项目做出贡献了。你可以添加、修改或删除文件。一旦你完成了更改，应该将它们提交到你的本地分支并推送到远程。

💡**注意**: 
- 所有更改应在 `feature/regex-support`分支上完成。 不要直接对 `dev` 或 `main` 分支做出任何更改。

```bash
git checkout feature/regex-support
# 将所有更改添加到暂存区。
git add .
# 用描述性信息提交更改。
git commit  # 或: git commit -m "<message>"
# 如果有人刚刚推送了一些更改到 "feature/regex-support"，在你推送前从远程拉取。
git pull --no-rebase
# 将更改推送到远程仓库
git push origin feature/regex-support
```

💡**注意**: 
- 如果在 `pull`之后Git警告你有冲突，根据 [附录：在本地机器上解决冲突](#resolve-the-conflicts-on-local-machine)来解决冲突。 

解决冲突后，提交更改并推送到远程仓库。

```bash
# 解决冲突后记得提交更改。
git push origin feature/regex-support
```

## 4. 创建拉取请求

在向远程分支 `feature/regex-support` 推送更改后，你应该在GitHub上从 `feature/regex-support` 向 `dev` 创建一个**拉取请求（PR）**。

💡**注意**: 
- 从 `feature/regex-support` 向 `dev` 创建PR意味着你想要 **将 `feature/regex-support` 的更改合并到 `dev` 中**。
- `main` 分支仅用于稳定的发布。不要从 `feature/regex-support` 向 `main`创建PR。

具体详情请查看 [创建拉取请求以将更改从`B` 合并到 `A`](#create-a-pull-request-to-merge-changes-from-b-to-a)。

---

# 附录

## 在本地机器上解决冲突

☝**注意**: 你只能在本地机器上解决冲突，而不能在GitHub上解决。

如果在 `pull` 或 `merge` 后产生冲突, 你应该手动解决它们。

首先找出哪些文件有冲突：

```bash
# 检查仓库状态。
git status
```

然后打开有冲突的文件。

冲突标记为 `<<<<<<<`, `=======`, 和 `>>>>>>>`。你应该移除这些标记并决定保留哪些更改。

解决冲突后，你应该将更改提交到目标分支。

```bash
git add .
git commit  # 或: git commit -m "<message>"
```

💡**注意**: 
- 因为合并过程改变了本地文件，不要忘记在解决冲突后提交更改。


## 创建拉取请求以将更改从 `B` 合并到 `A`

假设你在分支 `B` 上提交了一些更改并推送到了远程仓库。现在你想要 **创建一个PR将 `B` 的更改合并到 `A`**。

1. **前往GitHub仓库页面**：在你的浏览器中打开你一直在工作的 [GitHub页面](https://github.com/jamesnulliu/PrettyLazy0/)。

2. **开始拉取请求**: 点击仓库GitHub页面顶部的 `Pull requests` 标签。然后，点击 `New pull request` 按钮。

3. **选择基础与比较分支**：
    - 对于 **基础分支**, 选择 `A`。这是你想将更改合并进去的分支。
    - 对于 **比较分支**, 选择你的 `B`。这是包含你想合并更改的分支。

4. **审核你的更改**：确保一切更改都是正确且符合预期的。

5. **创建拉取请求**:
    - 点击 `Create pull request` 按钮。 
    - 为你的PR提供一个标题和详细描述。 **描述是必填项**。
    - 再次点击 `Create pull request` 提交你的PR。
    
    如果GitHub警告说存在冲突且自动合并失败，请参考 [附录：PR过程中发生冲突时](#when-conflicts-happen-during-pr) 寻找解决方法。


6. **响应反馈**: 一旦你的PR被提交，其他团队成员可以审阅你的更改、留下评论，并在必要时请求进一步修改。做好准备回应他人的反馈，并在需要时对你的功能分支进行更多提交。

7. **最终合并**: 在你的PR经过主要团队成员审阅并获得批准后，拥有合并权限的人会将你的更改合并到分支 `A`中。合并完成后，你的更改将成为分支 `A` 的一部分，你的PR将被关闭。


## PR过程中发生冲突时

假设你正在从 `B` 向 `A` 创建PR。

如果GitHub指出 `B` 与 `A` 之间存在冲突，那么你的PR将无法自动合并。

在这种情况下，回到你的本地机器并将 `A` 合并到 `B`：

```bash
git checkout A
# 从远程仓库拉取新更改。
# 由于你在分支 "A" 上没有做任何更改，这个操作是安全的。
git pull --no-rebase
# "B" 是你已经做出更改的分支。
git checkout B
# 本来，你想在GitHub上创建PR将 "B" 的更改合并到 "A"；
# 但由于存在冲突，你现在需要首先在本地机器上将 "A" 合并到 "B"。
git merge A
# 由于 "A" 和 "B" 之间存在冲突，Git会警告你需要解决它们。
```

遵循这一步骤，Git将在合并过程中在本地分支 `B` 的文件中标记出冲突。关于如何解决这些冲突的步骤，请参考[附录：在本地机器上解决冲突](#resolve-the-conflicts-on-local-machine)。

解决冲突后，将 `B` 推送到远程仓库：

```bash
# 解决冲突后记得提交更改。
git push origin B
```

返回GitHub并导航到你创建的PR。

此时，你应该能看到冲突已经被解决，合并冲突警告已经消失。


<!-- ##  Delete a Branch

If the branch `feature/regex-support` is no longer needed, you can delete it:

```bash
# [Warning] Make sure this branch is no longer needed before deleting this branch
# Delete the branch "feature/regex-support" locally
git branch -d feature/regex-support
# Delete the branch "feature/regex-support" on remote repo
git push origin --delete feature/regex-support
``` -->

##  删除分支

如果分支 `feature/regex-support` 不再需要，你可以将其删除：

```bash
# [警告] 在确认这个分支不再需要之前，请勿删除它

# 在本地删除分支 "feature/regex-support"
git branch -d feature/regex-support

# 在远程仓库中删除分支 "feature/regex-support"
git push origin -d feature/regex-support
```
