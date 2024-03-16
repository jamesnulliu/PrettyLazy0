# Branch Naming Convention
🌍: \[[English](./Branch_Naming_Convention.md)\]\[[中文](./Branch_Naming_Convention_zh.md)\]

In order to facilitate clear communication and organization within the team, we adhere to the following branch naming conventions:

## Types of Branches

- **Feature Branches**: Branches created for new features or enhancements.
- **Bugfix Branches**: Branches for fixing bugs.
- **Hotfix Branches**: Urgent fixes for issues in production.
- **Release Branches**: Preparing for a new release.
- **Docmentation Branches**: Improve project documentation.

## Naming Scheme

### General Format

`<type>/<short-description>`

### Types

- For a **feature**: `feature/<feature-name>`
- For a **bugfix**: `bugfix/<issue-or-bug-number>`
- For a **hotfix**: `hotfix/<issue-or-bug-number>`
- For a **release**: `release/<version-number>`
- For a **documentation**: `doc/<documenation-name>`

### Description

- Use dashes to separate words.
- The `<feature-name>` or `<short-description>` should be concise and descriptive.
- For bugfix and hotfix branches, use the issue or bug tracker number if applicable.

## Examples

- Feature Branch: `feature/login-authentication`
- Bugfix Branch: `bugfix/42-fix-login-error`
- Hotfix Branch: `hotfix/17-fix-payment-issue`
- Release Branch: `release/1.0.0`
- Documentation Branch: `doc/Env-Setup-Guide`

## Notes

- Avoid using generic names like `tmp` for branches. Always use meaningful names that reflect the purpose of the branch.
- Delete the branch from the remote repository after it has been merged and is no longer needed.
- Keep the branch up-to-date with the base branch (use `git merge dev` on your branch) to minimize merge conflicts.

By following these guidelines, we aim to maintain a clean, organized, and efficient workflow.
