# How to Contribute as a Colaborator

## Clone the Repository

```bash
git clonegit@github.com:jamesnulliu/PrettyLazy0.git

cd PrettyLazy0
```

## Create a New Branch

On github branch page, check **if there is an existing branch that is suitable for your contribution**. 

Let's suppose you want to add support for regular expression. You should first check if there is a branch named `feature/regex-support` on the [branch page](https://github.com/jamesnulliu/PrettyLazy0/branches).

## If There is No Suitable Branch

> If there is a suitable branch, please jump to [If There is Suitable Branch](#if-there-is-suitable-branch).

If there is no suitable branch for your contribution, you can create a new branch from `dev` following the [Branch Nameing Convention](./Branch_Naming_Convention.md).

This can be done on github, **but we recommend you to do it on your local machine according to following steps**.

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

## If There is Suitable Branch

If there there has already been a branch called `feature/regex-support`, you can directly checkout to this branch and pull the newest modifications from remote repo.

```bash
# Note that you should be in directory "PrettyLazy0" now
# Pull the newest modifications from remote repo
git pull
# Make sure you are in branch "feature/regex-support"
git checkout feature/regex-support
```

## Make Your Contribution

Now you can make your contribution to the project. You can add, modify, or delete files as needed. Once you've made your changes, you can commit them to your local branch.

**Note**: All changes should be done on branch `feature/regex-support`. Do not make any changes to branch `dev` or `main` directly.

## Merge Your Contribution to `dev`

Commit the changes to branch `feature/regex-support`:

```bash
# Make sure you are on branch "feature/regex-support"
git checkout feature/regex-support
# Pull newest changes from remote repo
git pull origin feature/regex-support
# Add all changes to the staging area
git add .
# Commit the changes with a descriptive message
git commit  # or: git commit -m "<message>"
# Push the changes on branch "feature/regex-support" to remote repo
git push origin feature/regex-support
```

Then you can merge your changes to branch `dev`:

```bash
# Checkout to branch "dev"
git checkout dev
# Pull newest changes from remote repo
git pull origin dev
# Merge branch "feature/regex-support" to branch "dev"
git merge feature/regex-support
```

Git will notice you if there are conflicts.

## Solve the Conflicts

If there is no conflict, please jump to [Push to `dev`](#push-to-dev).

If there are conflicts, you should solve them manually. 

First find out which files have conflicts:

```bash
# Make sure you are on branch "dev"
git checkout dev
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

## Push to `dev`

After solving the conflicts, you can push the changes to the remote repository.

```bash
git checkout dev
git push origin dev
```

If the branch `feature/regex-support` is no longer needed, you can delete it:

```bash
# [Warning] Make sure this branch is no longer needed before deleting this branch
# Delete the branch "feature/regex-support" locally
git branch -d feature/regex-support
# Delete the branch "feature/regex-support" on remote repo
git push origin --delete feature/regex-support
```

## Create a Pull Request

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

6. **Respond to Feedback**: Once your PR is submitted, other team members can review your changes, leave comments, and request additional modifications if necessary. Be prepared to respond to feedback and make further commits to your feature branch if required. These updates will automatically be included in your open PR.

7. **Final Merge**: After your PR has been reviewed and approved by the necessary members of your team, someone with merge permissions will merge your changes into the `dev` branch. Once the merge is complete, your changes will be part of the `dev` branch, and your PR will be closed.


