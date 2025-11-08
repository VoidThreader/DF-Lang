# DF-Lang
A derivative of Brainfuck called "Dumbfuck".

## Table of Contents
* [Installation](#installation)
    * [Building on Windows](#building-on-windows)
    * [Building on Unix-like systems](#building-on-unix-like-systems)
* [Usage](#usage)
* [Syntax](#syntax)
* [Example Program](#example-program)
* [LICENSE](#license)

# Installation
Compile the interpreter from source, mortal.

## Building on Windows

### Install Build Essentials
(You can skip this part if you already have it installed)
1. Install [MSYS2](https://www.msys2.org/)
2. Run the installer, it will walk you through installation. A terminal will pop up after installation is finished.
3. Paste the command in the terminal to install the MinGW-w64 toolchain required for compilation:
    ```bash
    pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
    ```
4. Accept the default packages, enter `Y` when prompted to begin installation.
5. Add to path: `C:\msys64\ucrt64\bin`
6. Verify installation:
    ```bash
    gcc --version
    ```

### Compiling the Source Code
1. Clone the repository using `git`:
    ```bash
    git clone https://github.com/VoidThreader/DF-Lang.git
    ```
2. Go to the DF-Lang directory
    ```
    cd DF-Lang
    ```
2. In your terminal, run:
    ```bash
    gcc -O3 -o dumbfuck src/main.c
    ```
4. The compiled program can now run `.df` files.

## Building on Unix-like systems
Check if you have a compiler present in your system:
```bash
gcc --version
```
or
```bash
clang --version
```
If not, then you'll need to install the compiler.

### Installing a Compiler
On your terminal, run:
* Debian/Ubuntu
```bash
sudo apt update
sudo apt install build-essential
```
* Fedora
```bash
sudo dnf groupinstall "Development Tools"
```
* Arch Linux
```bash
sudo pacman -S base-devel
```
* macOS
```bash
xcode-select --install
```

### Compiling the Source Code
1. Clone the repository using `git`:
    ```bash
    git clone https://github.com/VoidThreader/DF-Lang.git
    ```
2. Go to the DF-Lang directory
    ```
    cd DF-Lang
    ```
2. In your terminal, run:
    * Linux
    ```bash
    gcc -O3 -o dumbfuck src/main.c
    ```
    * macOS
    ```
    clang -O3 -o dumbfuck src/main.c
    ```
4. The compiled program can now run `.df` files.

# Usage
To run a Dumbfuck (`.df`) program on your terminal:\
* Bash:
```bash
./dumbfuck dumbfuckfile.df -d
```
* Powershell:
```powershell
.\dumbfuck dumbfuckfile.df -d
```
---
* dumbfuckfile.df — Dumbfuck program to run.
* -d — Debug mode flag used for debugging the program (optional).

# Syntax
Dumbfuck uses an accumulator for its program.
```
| Instruction | Description                                                             |
| ----------- | ----------------------------------------------------------------------- |
|     `+`     | Increment accumulator by 1                                              |
|     `-`     | Decrement accumulator by 1                                              |
|     `*`     | Square the accumulator                                                  |
|     `<`     | Left shift accumulator by 1                                             |
|     `>`     | Right shift accumulator by 1                                            |
|     `!`     | Reset accumulator to 0                                                  |
|     `.`     | Output current accumulator value (default char, number in debug)        |
```
* Other characters are treated as comments.
* The accumulator's stored value's output is its decimal value in the [ASCII Table](https://www.ascii-code.com/).
* If the debug flag is enabled, it outputs the accumulator's value as an integer.

# Example Program
Here is an example program that prints out "Hello, world!" in Dumbfuck:
```
+<<<*++++++++.
!+++++*<<+.
+++++++.
.
+++.
!+++*++<<.
!+<<<<<.
<<---------.
--------.
+++.
------.
--------.
!+<<<<<+.
!+<<<++.
```
Run the program:
```bash
./dumbfuck hello.df
```
Output:
```
Hello, world!
```

# LICENSE
[GPL](https://choosealicense.com/licenses/gpl-3.0/)