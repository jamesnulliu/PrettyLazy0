# Env Guide

Make sure you are using Ubuntu x64 22/23.

Other operating system is not support yet.

## 1. Install gcc and g++

Install build essentials:

```bash
sudo apt-get install build-essential
```

Check gcc version:

```bash
gcc -v
```

If you are using ubuntu 23, the output version should be 13.

However, if you are using releases lower than 23, you should install gcc-13 and g++-13 mannualy.

```bash
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install gcc-13 g++-13
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-13 130 --slave /usr/bin/g++ g++ /usr/bin/g++-13
```

## 2. Install CMake

```bash
sudo apt-get install cmake
```
