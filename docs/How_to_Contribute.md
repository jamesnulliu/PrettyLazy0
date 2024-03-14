# How to Contribute

Clone the dev branch:

```bash
git clone --single-branch -b dev git@github.com:jamesnulliu/PrettyLazy0.git PrettyLazy0-dev

cd PrettyLazy0-dev
```

Follow the [Branch Naming Convention](./Branch_Naming_Convention.md) and create your own local branch from `dev`.  
For example:

```bash
git checkout dev  # Make sure you are in branch "dev"

git pull origin dev

# Suppose you want to add support for regular expression
git checkout -b feature/regex-support
```

Make your modifications, and after that, commit the modifications to your local branch:

```bash
git add .
git commit  # or: git commit -m "<message>"
```

Pull the newest modifications from remote repo again to branch `dev`, and then merge changes from `feature/regex-support` to `dev`:

```bash
git checkout dev
git pull origin dev
git merge feature/regex-support
```

Git will notice you if there are conflicts. Solve the conflicts and then commit all changes and push to remote `dev`.

```bash
# Suppose there is no conflicts
git add .
git commit  # or: git commit -m "<message>"
git push origin dev
```

Clean your local branch:

```bash
# [Warning] Make sure this branch is no longer needed before deleting this branch
git branch -d feature/regex-support
```