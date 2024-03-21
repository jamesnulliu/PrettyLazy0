# How to Contribute as a Collaborator
🌍: |[English](./How_to_Contribute_as_a_Collaborator.md)|[中文](./How_to_Contribute_as_a_Collaborator_zh.md)|

This documentation is about a version control strategy based on [Git Flow](https://nvie.com/posts/a-successful-git-branching-model/).

## 1. Clone the Repository

```bash
git clone git@github.com:jamesnulliu/PrettyLazy0.git

cd PrettyLazy0
```

## 2. Create/Switch to a Branch

On GitHub branches page, **check if there has been an existing branch that is suitable for your contribution**. 

Let's suppose you want to add support for regular expression. You should first check if there is a remote branch named `feature/regex-support`.  

To list all remote branches, you should change directory to the local repository and run following commands:

```bash
# List all remote branches. 
git branch -r
```

💡**Note**: 
- There are two ways to check for remote branches:
    1. Go to the **branches page** on github of a repository and check for all existing branches.
    2. On your local machine, change directory to the local repository and run `git branch -r` to list all remote branches.

### 2.1. If There is a Suitable Remote Branch

If there there has already been a remote branch called `feature/regex-support`, you should then check **if the branch exists on your local machine**.

To list all local branches:

```bash
# List all local branches.
git branch
```

If the branch `feature/regex-support` exists on your local machine, you should switch to it and pull the new changes from the remote branch:

```bash
# Switch to branch "feature/regex-support".
git checkout feature/regex-support
# Pull the new changes from the remote branch.
git pull --no-rebase
```

Or, if the branch `feature/regex-support` does not exist on your local machine, you should create a local branch from remote one before pulling the new changes:

```bash
# Fetch the new changes from remote repository.
git fetch
# Create a new branch from "feature/regex-support" called "feature/regex-support" and track the remote branch.
# Note: Leave `origin` unchanged.
git checkout -b feature/regex-support origin/feature/regex-support
# Pull the new changes from the remote branch.
git pull --no-rebase
```

💡**Note**: 
- `git pull` only pulls the changes to the branch you are currently on. So switch to the branch before pulling.
- `--no-rebase` forces to merge the incoming and current changes.
- When your required branch exists in remote repository, there are 2 cases:
    1. If the branch exists on your local machine, switch to it and pull the new changes from remote branch.
    2. If the branch does not exist on your local machine, create a local branch from remote one before pulling the new changes.
- Leave `origin` unchanged in most cases. It is the default name of a remote repository, which actually stores repository's URL.

### 2.2. If There is No Suitable Remote Branch

If there is no suitable branch for your contribution, you can create a new branch from `dev` following the [Branch Naming Convention](./Branch_Naming_Convention.md).

Simply put, branch names should follow these naming scheme:

- For a **feature**: `feature/<feature-name>`
- For a **bugfix**: `bugfix/<issue-or-bug-number>`
- For a **hotfix**: `hotfix/<issue-or-bug-number>`
- For a **release**: `release/<version-number>`
- For a **documentation**: `doc/<documenation-name>`

```bash
# Make sure you are on branch "dev".
git checkout dev
# Pull the new changes from the remote branch.
git pull --no-rebase
# Create a new branch from "dev" called "feature/regex-support".
git checkout -b feature/regex-support
# Push the new branch to remote repo, namely create a remote branch on GitHub.
git push origin feature/regex-support:feature/regex-support
```

Back to the [branches page](https://github.com/jamesnulliu/PrettyLazy0/branches), you should see a new branch called `feature/regex-support`.

## 3. Make Your Contribution

Now you can make your contribution to the project. You can add, modify, or delete files as needed. Once you've made your changes, you should commit them to your local branch and push to remote.

💡**Note**: 
- All changes should be done on branch `feature/regex-support`. Do not make any changes to branch `dev` or `main` directly.

```bash
git checkout feature/regex-support
# Add all changes to the staging area.
git add .
# Commit the changes with a descriptive message.
git commit  # or: git commit -m "<message>"
# In case someone just pushed some changes to "feature/regex-support", pull from remote before your push.
git pull --no-rebase
# Push the changes to remote repo
git push origin feature/regex-support
```

💡**Note**: 
- If Git warns you conflicts after `pull`, resolve the conflicts accroding to [Appendix: Resolve the Conflicts on Local Machine](#resolve-the-conflicts-on-local-machine). 

After the conflicts are resolved, commit the changes and push to remote repository.

```bash
# Remember to commit changes after resolving conflicts.
git push origin feature/regex-support
```

## 4. Create a Pull Request

After pushing changes to remote branch `feature/regex-support`, you should create a **Pull Request (PR)** from `feature/regex-support` to `dev` on GitHub.

💡**Note**: 
- A PR from `feature/regex-support` to `dev` indicates that you want to **merges the changes from `feature/regex-support` to `dev`**.
- Branch `main` is only for stable releases. Do not create a PR from `feature/regex-support` to `main`.

Please check [Appendix: Create a Pull Request to Merge Changes from `B` to `A`](#create-a-pull-request-to-merge-changes-from-b-to-a) for details.

---

# Appendix

## Resolve the Conflicts on Local Machine

☝**Note**: You can only resolve the confilcts on your local machine, not on GitHub.

If there are conflicts after `pull` or `merge`, you should resolve them manually. 

First find out which files have conflicts:

```bash
# Check the status of the repository.
git status
```

Then open the files with conflicts.

The conflicts are marked with `<<<<<<<`, `=======`, and `>>>>>>>`. You should remove these markers and decide which changes to keep.

After resolving the conflicts, you should commit the changes to the target branch.

```bash
git add .
git commit  # or: git commit -m "<message>"
```

💡**Note**: 
- Because the merging process changed local files, do not forget to commit the changes after resolving conflicts.


## Create a Pull Request to Merge Changes from `B` to `A`

Suppose you have commited some changes on branch `B` and pushed to remote repository. And you now want to **create a PR to merge changes from `B` to `A`**.

1. **Navigate to the Repository on GitHub**: Open your web browser and go to the [GitHub page](https://github.com/jamesnulliu/PrettyLazy0/) for the repository you've been working on.

2. **Initiate the Pull Request**: Click on the `Pull requests` tab near the top of the repository's GitHub page. Then, click on the `New pull request` button.

3. **Choose the Base and Compare Branches**: 
    - For the **base branch**, select `A`. This is the branch you want your changes to be pulled into.
    - For the **compare branch**, select your `B`. This is the branch that contains the changes you want to merge.

4. **Review Your Changes**: Review the changes to ensure everything is correct and as intended.

5. **Create the Pull Request**: 
    - Click on the `Create pull request` button. 
    - Provide a title and a detailed description for your PR. **Description is mandatory.**
    - Click on `Create pull request` again to submit your PR.
    
    If GitHub warns you there are conflicts and auto-merging is failed, refer to [Appendix: When Conflicts Happen during PR](#when-conflicts-happen-during-pr) for solution.


6. **Respond to Feedback**: Once your PR is submitted, other team members can review your changes, leave comments, and request additional modifications if necessary. Be prepared to respond to feedback and make further commits to your feature branch if required.

7. **Final Merge**: After your PR has been reviewed and approved by the necessary members of your team, someone with merge permissions will merge your changes into branch `A`. Once the merge is complete, your changes will be part of branch `A`, and your PR will be closed.


## When Conflicts Happen during PR

Suppose you are creating a PR from `B` to `A`.

If GitHub indicates there are conflicts between `B` and `A`,  your PR would not be merged automatically.

In this case, go back to your local machine and merge `A` to `B`:

```bash
git checkout A
# Pull new changes from remote repository.
# Since you haven't changed anything on branch "A", this action is safe.
git pull --no-rebase

# "B" is the branch where you have made changes.
git checkout B
# Originally, you want to create a PR on GitHub to merge the changes from "B" to "A";
# But since there are conflicts, you should first merge "A" to "B" on your local machine.
git merge A
# Becase there are conflicts betwwen new-coming "A" and "B", Git will warn you to resolve them.
```

Following this, Git will alert you there are conflicts during the merge process. Unlike GitHub, Git marks the conflicts in your local files on branch `B`. For steps on how to resolve these conflicts, refer to [Appendix: Resolve the Conflicts on Local Machine](#resolve-the-conflicts-on-local-machine).

After the conflicts are resolved, push `B` to remote repository:

```bash
# Remember to commit changes after resolving conflicts.
git push origin B
```

Go back to GitHub and navigate to the PR you created. 

You should be able to see that the conflicts have been resolved, and the merge conflict warning has disappeared. 


<!-- ##  Delete a Branch

If the branch `feature/regex-support` is no longer needed, you can delete it:

```bash
# [Warning] Make sure this branch is no longer needed before deleting this branch
# Delete the branch "feature/regex-support" locally
git branch -d feature/regex-support
# Delete the branch "feature/regex-support" on remote repo
git push origin --delete feature/regex-support
``` -->

##  Delete a Branch

If branch `feature/regex-support` is no longer needed, you can delete it:

```bash
# [Warning] Make sure this branch is no longer needed before deleting this branch

# Delete the branch "feature/omp-#5" locally
git branch -d feature/regex-support

# Delete the branch "feature/omp-#5" on remote repo
git push origin -d feature/regex-support
```