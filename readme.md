# Lena programming language

![Lena logo](.github/img/lena-logo.jpeg)

## Basic information

### Main

* Interpreted / Compiled
* Runs on a Executor or PCHE
* Syntax = Python + Assembly + Rust + C/C++

### File formats

* Code file format: `.le`
* Bytecode file format `.x`
* Decoded bytecode file format `.dx`

## Explanation of PCHE (Programmable Cloning Hypervisor Executor)

PCHE is a complex of programs for ensuring isolated operation of copies of executors for each application in Lena.

Application on this are executed in the following sequence:

0. Launch the executable file obtained after the code has been processed by the compiler.
1. Loading the application bytecode into RAM.
2. Lena system call, indicating the memory address.
3. Lena clones itself with the launch parameter from the current address.
4. The code is executed.
5. The clone deletes itself from memory, and then the system function exits.
6. The program closes.


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
