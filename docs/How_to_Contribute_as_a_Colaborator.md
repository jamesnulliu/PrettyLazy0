# How to Contribute as a Colaborator
🌍: [[English](./How_to_Contribute_as_a_Colaborator.md)][[中文](./How_to_Contribute_as_a_Colaborator_zh.md)]

This documentation is about a version control strategy based on [Git Flow](https://nvie.com/posts/a-successful-git-branching-model/).

## 1. Clone the Repository

```bash
git clonegit@github.com:jamesnulliu/PrettyLazy0.git

cd PrettyLazy0
```

## 2. Create/Switch to a Branch

On GitHub [branches page](GitHub), **check if there has been an existing branch that is suitable for your contribution**. 

Let's suppose you want to add support for regular expression. You should first check if there is a branch named `feature/regex-support` on [branches page](https://github.com/jamesnulliu/PrettyLazy0/branches).

### 2.1. If There is a Suitable Branch

If there there has already been a branch called `feature/regex-support`, you can directly go to your local machine and switch to this branch.

```bash
# Switch to branch "feature/regex-support"
git checkout feature/regex-support
# Pull the new changes from remote repository
git pull
```

☝**Note**: `git pull` only pulls the changes to the branch you are currently on. So switch to the branch before pulling.

### 2.2. If There is No Suitable Branch

If there is no suitable branch for your contribution, you can create a new branch from `dev` following the [Branch Naming Convention](./Branch_Naming_Convention.md).

Simply put, branch names should follow these naming scheme:

- For a **feature**: `feature/<feature-name>`
- For a **bugfix**: `bugfix/<issue-or-bug-number>`
- For a **hotfix**: `hotfix/<issue-or-bug-number>`
- For a **release**: `release/<version-number>`
- For a **documentation**: `doc/<documenation-name>`

```bash
# Make sure you are on branch "dev"
git checkout dev
# Pull the new changes from remote repository
git pull
# Create a new branch from "dev" called "feature/regex-support"
git checkout -b feature/regex-support
# Push the new branch to remote repo, namely create a remote branch
git push origin feature/regex-support:feature/regex-support
```

Back to the [branches page](https://github.com/jamesnulliu/PrettyLazy0/branches), you should see a new branch called `feature/regex-support`.

## 3. Make Your Contribution

Now you can make your contribution to the project. You can add, modify, or delete files as needed. Once you've made your changes, you should commit them to your local branch and push to remote.

☝**Note**: All changes should be done on branch `feature/regex-support`. Do not make any changes to branch `dev` or `main` directly.

```bash
git checkout feature/regex-support
# Add all changes to the staging area
git add .
# Commit the changes with a descriptive message
git commit  # or: git commit -m "<message>"
# Pull newest changes from remote repo
git pull
# Push the changes to remote repo
git push origin feature/regex-support
```

☝**Note**: If Git warns you conflicts after `pull`, resolve the conflicts accroding to [Appendix: Resolve the Conflicts on Local Machine](#resolve-the-conflicts-on-local-machine). 

After the conflicts are resolved, commit the changes and push to remote repository.

```bash
# Remember to commit changes after resolving conflicts 
git push origin feature/regex-support
```

## 4. Create a Pull Request

After pushing changes to branch `feature/regex-support` on remote repository, you should create a **Pull Request (PR)** from `feature/regex-support` to `dev` on GitHub.

☝**Note**: A PR from `feature/regex-support` to `dev` indicates that you want to **merges the changes from `feature/regex-support` to `dev`**.

Please check [Appendix: Create a Pull Request to Merge Changes from `B` to `A`](#create-a-pull-request-to-merge-changes-from-b-to-a) for details.

---

# Appendix

## Resolve the Conflicts on Local Machine

☝**Note**: You can only resolve the confilcts on your local machine, not on GitHub.

If there are conflicts after `pull` or `merge`, you should resolve them manually. 

First find out which files have conflicts:

```bash
# Check the status of the repository
git status
```

Then open the files with conflicts.

The conflicts are marked with `<<<<<<<`, `=======`, and `>>>>>>>`. You should remove these markers and decide which changes to keep.

After resolving the conflicts, you should commit the changes to the target branch.

```bash
git add .
git commit  # or: git commit -m "<message>"
```


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
# Pull new changes from remote repository
git pull
# "B" is the branch where you made changes.
# Originally, you want to create a PR to merge the changes from "B" to "A";
# But since there are conflicts, now you should first merge "A" to "B" on your local machine.
git checkout B
git pull
git merge A
```

Following this, Git will alert you there are conflicts during the merge process. Unlike GitHub, Git marks the conflicts in your local files on branch `B`. For steps on how to resolve these conflicts, refer to [Appendix: Resolve the Conflicts on Local Machine](#resolve-the-conflicts-on-local-machine).

After the conflicts are resolved, push `B` to remote repository:

```bash
# Remember to commit changes after resolving changes
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
