# Lena programming language -> Deeply integrated virtual machine

## Basic information

1) A deeply integrated virtual machine differs from a regular one in the way programs are executed; lena-vm has more privileges than a regular virtual machine like a JVM.

2) Byte code does not have a typical human representation and is unreadable. In order to read the code for lena-vm, you need to use the [Light universal interface tools](https://github.com/robotsvision/light-uii).

## Opcode list (words in Hexadecimal)

Every code takes 2 bytes

* \[0000\] = global_end()
* \[0001\] = global_start()
* \[0002\] = config_end()
* \[0003\] = config_start()

Configuration

* \[0004\] = exe_name(size:i16, name:string)
* \[0005\] = exe_type(type:i16)
* \[0006\] = exe_arch(arch:i16)

...
