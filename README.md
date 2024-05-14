<div align="center">

  <img src="./docs/imgs/PrettyLazy0-logo.png" height=200px></img>
  
  <em>A PL/0 Compiler Implemented with C++</em>

  ![Static Badge](https://img.shields.io/badge/PL%2F0-purple?style=plastic&link=https%3A%2F%2Fgithub.com%2Fjamesnulliu%2FPrettyLazy0%2Fblob%2Fmain%2FLICENSE) ![Static Badge](https://img.shields.io/badge/C%2B%2B-23-blue?style=plastic) ![Static Badge](https://img.shields.io/badge/g%2B%2B-13-blue?style=plastic) ![Static Badge](https://img.shields.io/badge/msvc-19-blue?style=plastic) ![Static Badge](https://img.shields.io/badge/cmake-navy?style=plastic&link=https%3A%2F%2Fgithub.com%2Fjamesnulliu%2FPrettyLazy0%2Fblob%2Fmain%2FLICENSE) ![Static Badge](https://img.shields.io/badge/make-navy?style=plastic&link=https%3A%2F%2Fgithub.com%2Fjamesnulliu%2FPrettyLazy0%2Fblob%2Fmain%2FLICENSE) ![Static Badge](https://img.shields.io/badge/ninja-navy?style=plastic&link=https%3A%2F%2Fgithub.com%2Fjamesnulliu%2FPrettyLazy0%2Fblob%2Fmain%2FLICENSE) [![license - Apache-2.0](https://img.shields.io/badge/license-Apache--2.0-darkgreen?style=plastic)](https://github.com/jamesnulliu/PrettyLazy0/blob/main/LICENSE)

</div>


## Environments

<div align="center">

| OS | Compiler | Build Tools | Make Tools |
|:--:|:--------:|:-----------:|:----------:|
| Linux | g++ >= 13 | cmake >= 3.21 | make |
| Windows | msvc >= 19 | cmake >= 3.21 | ninja |

</div>

Check [Env Setup Guide for Linux](./docs/Env_Setup_Guide_for_Linux.md) or [Env Setup Guide for Windows](./docs/Env_Setup_Guide_for_Windows.md) for details.

## Quick Start

Clone the repository with following command:

```bash
git clone --recursive git@github.com:jamesnulliu/PrettyLazy0.git ./PrettyLazy0

cd PrettyLazy0
```

To build an executable of PrettyLazy0:

```bash
# On Linux:
bash ./scripts/build.sh Release

# On Windows:
pwsh .\scripts\build.ps1 Release
```

## Contribute

Feel free to contribute to this project.

If you are not a collaborator, please check [How to Contribute as a Non-Collaborator](./docs/How_to_Contribute_as_a_Non-Collaborator.md) for contribution rules.

If you are a collaborator, please check [How to Contribute as a Collaborator](./docs/How_to_Contribute_as_a_Collaborator.md) for contribution rules.
