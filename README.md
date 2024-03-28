# PrettyLazy0
A PL/0 Compiler Implemented with C++

## Environments

- Compiler: **g++**>=13 (on Linux) or **MSVC**>=19 (on Windows)
- Other Softwares: **cmake**>=3.21, **make** (on Linux) or **ninja** (on Windows)
- IDE: **vscode** (optional, recommended)

Check [Env Setup Guide](./docs/Env_Setup_Guide.md) for detailed environment setup.

## Quick Start

**Before start, please first make sure you have setup the required [environments](#environments).**


Clone the repository with following command:

```bash
git clone git@github.com:jamesnulliu/PrettyLazy0.git PrettyLazy0

cd PrettyLazy0
```

To build an executable of PrettyLazy0:

```bash
# On Linux:
bash ./scripts/build-linux.sh Release

# On Windows:
pwsh .\scripts\build-windows.ps1 Release
```

To run test case (replace `<what>` with the case to test):

```bash
# On Linux_x64:
bash ./scripts/test-linuxX64-<what>.sh

# On Windows_x64:
bash ./scripts/test-windowsX64-<what>.sh
```

> You can write your own test scrpits based on your need.

## Contribute

Feel free to contribute to this project.

If you are not a collaborator, please check [How to Contribute as a Non-Collaborator](./docs/How_to_Contribute_as_a_Non-Collaborator.md) for contribution rules.

If you are a collaborator, please check [How to Contribute as a Collaborator](./docs/How_to_Contribute_as_a_Collaborator.md) for contribution rules.
