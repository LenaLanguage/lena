# Lena programming language

![Lena logo](images/lena-logo.jpeg)

## Basic information

### Main

* Interpreted / Compiled
* Runs on a Virtual Machine or DIVM
* Syntax = Python + Assembly + Rust + C/C++

### File formats

* Code file format: `.le`
* Bytecode file format `.x`
* Decoded bytecode file format `.xx`

## Explanation of DIVM

DIVM is a deep integration technology for virtual machine. Programs on this are executed in the following sequence:

0. Launch the executable file obtained after the code has been processed by the compiler.
1. Loading the application bytecode into RAM.
2. Lena system call, indicating the memory address.
3. Lena clones itself with the launch parameter from the current address.
4. The code is executed.
5. The clone deletes itself from memory, and then the system function exits.
6. The program closes.

### Points worth paying attention to

* DIVM has full control over the device, which eliminates any overhead at runtime
* Rule of unity of Lena clones. During DIVM execution, it can create many clones for different applications. But in fact, for each application launch, only one main `Lena General Core` is used.

## Areas of application

* Neural networks

* Education

* Computing and working with data

* Thread-oriented programming

## Hello World

```rust

/* Hello World example 1 */
cout << "Hello World!"

; Or

/* Hello World example 2 */
"Hello World!" >> cout

```

## Arrays

```rust

array = (5 times 2000)

; Or

array2 = {5, 5, 5, 5, 5} ; ... 2000 times

```
