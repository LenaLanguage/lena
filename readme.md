# Lena programming language

![Lena logo](.github/img/lena-logo.jpeg)

## Basic information

### Main

* Compiled
* Executes on SHE (Software-Cloneable Hypervisor Executor)
* Syntax obtained from languages: Julia, Rust, assembly languages, C/C++
* Inspired by: Julia, Rust, Java

### File formats *.e.le.na*

* Bytecode executable file format `.e`
* Source code file format: `.le`
* Decrypted bytecode format (not abstract) `.na`

## Explanation of the Lena language and the SHE executor

SHE is a set of programs for running an application in an environment isolated from the operating system.

Lena language algorithm:

1. Open the executable file *.exe* or *.e* which is compiled into `lena`.

Example of compiling *.e* and *.exe* files

```shell
lena app.le -o app.e --non-abstract
```

```shell
lena app.le -o app.exe --non-abstract
```

* *in UNIX-like systems, the .exe format does not need to be specified*

2. *.exe* file, after launch, loads its bytecode into RAM. If the file is in *.e* format, then it is launched with the command:

```shell
she app.e
```

3. The hypervisor executor is able to create local, isolated clones for the execution of each application running in the SHE environment. This is done because, unlike typical VMs, SHE exists in the form of a **driver** or **OS kernel module**. In other words, it is an isolated "OS" within the underlying system.

4. Bytecode is read directly from RAM, often using direct access to physical memory thanks to the rights of the **driver** or **OS kernel module**.

5. The SHE clone removes itself from memory and frees up computer resources after the program exits.

6. The program closes for the user.

## Areas of application

* System Programming

* Game development

* Data manipulation and calculations

## Hello World

```rust
out("Hello world!")
```

## Arrays and macros

```rust

array = (5 times 2000)

; or

array2 = {5, 5, 5, 5, 5} ; ...2000 times
```