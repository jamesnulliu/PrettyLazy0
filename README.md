# PrettyLazy0
A PL/0 Compiler Implemented with C++

## Environments

- System: Ubuntu x64 22/23
- Compiler: gcc-13, g++-13
- Other Softwares: cmake>=3.21
- IDE: vscode (optional, recommended)

Check [Env Setup Guide](./docs/Env_Setup_Guide.md) for detailed environment setup.

## Quick Start

**Before start, please first make sure you have setup the required environments.**

Clone this repository with following command:

```bash
git clone --single-branch -b main git@github.com:jamesnulliu/PrettyLazy0.git PrettyLazy0-main

cd PrettyLazy0-main
```

To build an executable of PrettyLazy0:

```bash
bash scripts/build.sh
```

To run test case:

```bash
bash scrpts/test.sh
```

To add the executable (namely `plazy`) to user PATH variable:

```bash
export PATH="$PATH:$(pwd)/bin"
```

## Contribute

Contribution is welcomed. Please check [How to Contribute](./docs/How_to_Contribute.md) for contribution rules.