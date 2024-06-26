# The Lena programming language

![Lena logo](.github/img/lena-logo.jpeg)

## Basic information

### Main

* Compiled
* Runs on SHE (Software-Cloneable Hypervisor Executor)
* Syntax = Julia + Rust + Assembler + C/C++
* Influenced by Julia, Rust, Java

### File formats *.e.le.na*

* Bytecode executable file format `.e`
* Code file format: `.le`
* Not abstracted code file format `.na`

## Explanation of SHE (Software-Cloneable Hypervisor Executor)

SHE is a complex of programs for ensuring isolated operation of copies of executors for each application in Lena.

Application on this are executed in the following sequence:

0. Launch the executable file obtained after the code has been processed by the compiler.
1. Loading the application bytecode into RAM.
2. Lena system call, indicating the memory address.
3. Lena clones itself with the launch parameter from the current address.
4. The code is executed on SHE.
5. The clone deletes itself from memory, and then the system function exits.
6. The program closes.

## Areas of application

* System programming

* Game development

* Computing and working with data

## Hello World

```rust

/* Hello World example */
out("Hello World!")
```

## Arrays

```rust

array = (5 times 2000)

; Or

array2 = {5, 5, 5, 5, 5} ; ... 2000 times
```
