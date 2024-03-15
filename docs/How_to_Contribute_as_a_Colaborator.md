# How to Contribute as a Colaborator
🌍: \[[English](./How_to_Contribute_as_a_Colaborator.md)\]\[[中文](./How_to_Contribute_as_a_Colaborator_zh.md)\]

## 1. Clone the Repository

```bash
git clonegit@github.com:jamesnulliu/PrettyLazy0.git

cd PrettyLazy0
```

## 2. Create a New Branch

On github branch page, **check if there has been an existing branch that is suitable for your contribution**. 

Let's suppose you want to add support for regular expression. You should first check if there is a branch named `feature/regex-support` on the [branch page](https://github.com/jamesnulliu/PrettyLazy0/branches).

### 2.1. If There is a Suitable Branch

If there there has already been a branch called `feature/regex-support`, you can directly checkout to this branch and pull the newest changes from remote repo.

```bash
# Note that you should be in directory "PrettyLazy0" now
# Pull the newest changes from remote repo
git pull
# Make sure you are in branch "feature/regex-support"
git checkout feature/regex-support
```
### 2.2. If There is No Suitable Branch

If there is no suitable branch for your contribution, you can create a new branch from `dev` following the [Branch Nameing Convention](./Branch_Naming_Convention.md).

This could be done on github, **but we recommend you to do it on your local machine according to following steps**.

```bash
# Note that you should be in directory "PrettyLazy0" now
# Pull the newest modifications from remote repo
git pull
# Make sure you are in branch "dev"
git checkout dev
# Create a new branch from "dev" called "feature/regex-support"
git checkout -b feature/regex-support
# Push the new branch to remote repo
git push origin feature/regex-support:feature/regex-support
```

Now back to the [branch page](https://github.com/jamesnulliu/PrettyLazy0/branches), you should see a new branch called `feature/regex-support`.

## 3. Make Your Contribution

Now you can make your contribution to the project. You can add, modify, or delete files as needed. Once you've made your changes, you should commit them to your local branch.

**Note**: All changes should be done on branch `feature/regex-support`. Do not make any changes to branch `dev` or `main` directly.

```bash
# Add all changes to the staging area
git add .
# Commit the changes with a descriptive message
git commit  # or: git commit -m "<message>"
# Pull newest changes from remote repo
git pull origin feature/regex-support
# Push the changes on branch "feature/regex-support" to remote repo
git push origin feature/regex-support
```

**Note**: If conflicts happen after `pull` command, solve the conflicts accroding to [5. Solve the Conflicts](#5-solve-the-conflicts). `push` to remote repository after the conficts are solved.

## 4. Merge Your Changes to `dev`

After commiting changes in branch `feature/regex-support`, you can merge your changes to branch `dev`:

```bash
# Checkout to branch "dev"
git checkout dev
# Pull newest changes from remote repo
git pull origin dev
# Merge branch "feature/regex-support" to branch "dev"
git merge feature/regex-support
# Push to remote branch "dev"
git push origin dev
```

**Note**: If conflicts happen after `pull` command, solve the conflicts accroding to [Solve the Conflicts](#5-solve-the-conflicts). `push` to remote repository after the conficts are solved.

## 5. Solve the Conflicts

If there are conflicts after `pull` or `merge`, you should solve them manually. 

First find out which files have conflicts:

```bash
# Check the status of the repository
git status
```

Then open the files with conflicts and solve them manually. 

The conflicts are marked with `<<<<<<<`, `=======`, and `>>>>>>>`. You should remove these markers and decide which changes to keep.

After solving the conflicts, you should add the files to the staging area and commit the changes.

```bash
git add .
git commit  # or: git commit -m "<message>"
```

## \[Optional\] 6. Delete a Branch

If the branch `feature/regex-support` is no longer needed, you can delete it:

```bash
# [Warning] Make sure this branch is no longer needed before deleting this branch
# Delete the branch "feature/regex-support" locally
git branch -d feature/regex-support
# Delete the branch "feature/regex-support" on remote repo
git push origin --delete feature/regex-support
```

## 7. Create a Pull Request

After pushing your changes to the `dev` branch on the remote repository, the next step is to create a Pull Request (PR) to propose your changes for review and integration into the main codebase.

1. **Navigate to the Repository on GitHub**: Open your web browser and go to the [GitHub page](https://github.com/jamesnulliu/PrettyLazy0/) for the repository you've been working on.

2. **Initiate the Pull Request**: Click on the `Pull requests` tab near the top of the repository's GitHub page. Then, click on the `New pull request` button.

3. **Choose the Base and Compare Branches**: 
    - For the **base branch**, select `main`. This is the branch you want your changes to be pulled into.
    - For the **compare branch**, select your `dev`. This is the branch that contains the changes you want to merge.

4. **Review Your Changes**: Review the changes to ensure everything is correct and as intended.

5. **Create the Pull Request**: 
    - Click on the `Create pull request` button. 
    - Provide a title and a detailed description for your PR. 
    - Click on `Create pull request` again to submit your PR.

6. **Respond to Feedback**: Once your PR is submitted, other team members can review your changes, leave comments, and request additional modifications if necessary. Be prepared to respond to feedback and make further commits to your feature branch if required.

7. **Final Merge**: After your PR has been reviewed and approved by the necessary members of your team, someone with merge permissions will merge your changes into the `dev` branch. Once the merge is complete, your changes will be part of the `dev` branch, and your PR will be closed.


