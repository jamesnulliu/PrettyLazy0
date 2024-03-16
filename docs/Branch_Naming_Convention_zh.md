# 分支命名规范
🌍: \[[English](./Branch_Naming_Convention.md)\]\[[中文](./Branch_Naming_Convention_zh.md)\]

为了便于小组内交流清晰和工作编排，我们建议使用以下分支命名规范：

## 分支的种类

- **特性分支**：新特性或者新优化。
- **漏洞修复分支**：修复已发现的漏洞。
- **热修复分支**： 紧急修复产品中重要漏洞。
- **发布分支**：即将发布的正式版。
- **文档分支**：完善项目的说明文档。

## 命名方法

### 通用格式

`<type>/<short-description>`

### 各类模板

- 对于**特性分支**：`feature/<feature-name>`
- 对于**漏洞修复分支**：`bugfix/<issue-or-bug-number>`
- 对于**热修复分支**：`hotfix/<issue-or-bug-number>`
- 对于**发布分支**：`release/<version-number>`
- 对于**文档分支**：`doc/<documenation-name>`

### 描述

- 使用短划线`-`来分割单词。
- `<type>/<short-description>`中的描述应当简洁易懂。
- 对于漏洞修复分支和热修复分支，应在适宜情况下使用问题或者漏洞跟踪编号。

### 示范

- 特性分支: `feature/login-authentication`
- 漏洞修复分支: `bugfix/42-fix-login-error`
- 热修复分支: `hotfix/17-fix-payment-issue`
- 发布分支: `release/1.0.0`
- 文档分支: `doc/Env-Setup-Guide`

## 注意

- 避免使用过于普通的字眼作为分支的名称，例如`temp`。建议使用有实际意义的名称，从而体现出这一分支的用途。
- 当一个分支已经合并，或者该分支不再使用，请在远程仓库中删除它。
- 保持分支与基本分支例如`main`或者`dev`的同步，可以有效减少合并冲突的发生。

请注意遵守以上规范，让我们的工作流程清晰化、层次化、高效化。