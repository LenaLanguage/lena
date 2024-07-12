	.file	"compiler.c"
 # GNU C17 (Rev6, Built by MSYS2 project) version 13.2.0 (x86_64-w64-mingw32)
 #	compiled by GNU C version 13.2.0, GMP version 6.3.0, MPFR version 4.2.1, MPC version 1.3.1, isl version isl-0.26-GMP

 # GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
 # options passed: -municode -m64 -mtune=generic -march=nocona -O3 -std=c17
	.text
	.p2align 4
	.globl	compile_files
	.def	compile_files;	.scl	2;	.type	32;	.endef
	.seh_proc	compile_files
compile_files:
	.seh_endprologue
 # src\compiler\compiler.c:50: }
	xorl	%eax, %eax	 #
	ret	
	.seh_endproc
	.globl	executable_exe
	.bss
	.align 8
executable_exe:
	.space 8
	.globl	target
	.align 8
target:
	.space 8
	.ident	"GCC: (Rev6, Built by MSYS2 project) 13.2.0"
