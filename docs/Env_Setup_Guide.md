# Env Setup Guide

Make sure you are using Ubuntu x64 22/23.

Other operating systems are not supported yet.

## 1. Install gcc and g++

Install build essentials:

```bash
sudo apt-get install build-essential
```

Check gcc version:

```bash
gcc -v  # or g++ -v
```

If you are using ubuntu 23, the outputs would imply the installed gcc version is "13.x.x".

If the version is lower than 13, please check [this article](https://github.com/jamesnulliu/My_Notes/blob/main/Linux/Use_Cxx20_in_Ubuntu22.md).


## 2. Install CMake

```bash
sudo apt-get install cmake
```

## 3. \[Optional\] Install VSCode

```bash
sudo snap install code --classic
```

Install **C/C++ Extension Pack** provided by Microsoft. This should include C/C++ extension and CMake Tools extionsion.

Now you should be able to build, run and debug the project with the buttons on the status bar on the left-bottom of the window.

<img src="imgs/cmake.png"></img>