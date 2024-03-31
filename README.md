<div align="center">

  <img src="./docs/imgs/PrettyLazy0-logo.png" height=250px></img>
  
  <em>A PL/0 Compiler Implemented with C++</em>

  ![Static Badge](https://img.shields.io/badge/PL%2F0-purple?style=plastic&link=https%3A%2F%2Fgithub.com%2Fjamesnulliu%2FPrettyLazy0%2Fblob%2Fmain%2FLICENSE) ![Static Badge](https://img.shields.io/badge/C%2B%2B-20%7C23-blue?style=plastic) ![Static Badge](https://img.shields.io/badge/g%2B%2B-13-blue?style=plastic) ![Static Badge](https://img.shields.io/badge/msvc-19-blue?style=plastic) ![Static Badge](https://img.shields.io/badge/cmake-navy?style=plastic&link=https%3A%2F%2Fgithub.com%2Fjamesnulliu%2FPrettyLazy0%2Fblob%2Fmain%2FLICENSE) ![Static Badge](https://img.shields.io/badge/make-navy?style=plastic&link=https%3A%2F%2Fgithub.com%2Fjamesnulliu%2FPrettyLazy0%2Fblob%2Fmain%2FLICENSE) ![Static Badge](https://img.shields.io/badge/ninja-navy?style=plastic&link=https%3A%2F%2Fgithub.com%2Fjamesnulliu%2FPrettyLazy0%2Fblob%2Fmain%2FLICENSE) [![license - Apache-2.0](https://img.shields.io/badge/license-Apache--2.0-darkgreen?style=plastic)](https://github.com/jamesnulliu/PrettyLazy0/blob/main/LICENSE)

</div>


## Environments
- Linux:
    - Compiler: **g++**>=13
    - Other Softwares: **cmake**>=3.21, **make**
    - IDE: **vscode** (optional, recommended)
- Windows:
    - Compiler: **MSVC**>=19
    - Other Softwares: **cmake**>=3.21, **ninja**
    - IDE: **vscode** (optional, recommended)

Check [Env Setup Guide for Linux](./docs/Env_Setup_Guide_for_Linux.md) or [Env Setup Guide for Windows](./docs/Env_Setup_Guide_for_Windows.md) for details.

## Quick Start

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
