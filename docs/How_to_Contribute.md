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

After pushing your changes to the `dev` branch on the remote repository, the next step is to create a Pull Request (PR) to propose your changes for review and integration into the main codebase. Here's how to do it:

1. **Navigate to the Repository on GitHub**: Open your web browser and go to the GitHub page for the repository you've been working on. For example, `https://github.com/jamesnulliu/PrettyLazy0`.

2. **Initiate the Pull Request**: Click on the `Pull requests` tab near the top of the repository's GitHub page. Then, click on the `New pull request` button.

3. **Choose the Base and Compare Branches**: 
    - For the **base branch**, select `main`. This is the branch you want your changes to be pulled into.
    - For the **compare branch**, select your `dev`. This is the branch that contains the changes you want to merge.

4. **Review Your Changes**: GitHub will display a comparison between the two branches. Review the changes to ensure everything is correct and as intended.

5. **Create the Pull Request**: 
    - Click on the `Create pull request` button. 
    - Provide a title and a detailed description for your PR. The title should be concise and descriptive, and the description should explain what changes you've made and why. If there are specific issues your PR addresses, include references to those issues.
    - After filling out the information, click on "Create pull request" again to submit your PR.

6. **Respond to Feedback**: Once your PR is submitted, other team members can review your changes, leave comments, and request additional modifications if necessary. Be prepared to respond to feedback and make further commits to your feature branch if required. These updates will automatically be included in your open PR.

7. **Final Merge**: After your PR has been reviewed and approved by the necessary members of your team, someone with merge permissions will merge your changes into the `dev` branch. Once the merge is complete, your changes will be part of the `dev` branch, and your PR will be closed.

Remember, a Pull Request is not only a way to submit your work but also an opportunity for team collaboration and code review. It's an essential practice for maintaining code quality and coherence in a multi-developer environment.

