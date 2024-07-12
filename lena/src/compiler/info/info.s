	.file	"info.c"
 # GNU C17 (Rev6, Built by MSYS2 project) version 13.2.0 (x86_64-w64-mingw32)
 #	compiled by GNU C version 13.2.0, GMP version 6.3.0, MPFR version 4.2.1, MPC version 1.3.1, isl version isl-0.26-GMP

 # GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
 # options passed: -municode -m64 -mtune=generic -march=nocona -O3 -std=c17
	.text
	.section .rdata,"dr"
.LC0:
	.ascii "Lena compiler \0"
.LC1:
	.ascii "version \0"
.LC2:
	.ascii "0.4.0\0"
	.text
	.p2align 4
	.globl	version
	.def	version;	.scl	2;	.type	32;	.endef
	.seh_proc	version
version:
	subq	$40, %rsp	 #,
	.seh_stackalloc	40
	.seh_endprologue
 # src\compiler\info\info.c:6:     lccol(LC_COLOR_RED, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$2, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:7:     lcout(X("Lena compiler "));
	leaq	.LC0(%rip), %rcx	 #, tmp82
	call	lcout	 #
 # src\compiler\info\info.c:8:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:9:     lcout(X("version "));
	leaq	.LC1(%rip), %rcx	 #, tmp83
	call	lcout	 #
 # src\compiler\info\info.c:10:     lccol(LC_COLOR_YELLOW, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$12, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:11:     lcout(LENA_VERSION_STR);
	leaq	.LC2(%rip), %rcx	 #, tmp84
 # src\compiler\info\info.c:12: }
	addq	$40, %rsp	 #,
 # src\compiler\info\info.c:11:     lcout(LENA_VERSION_STR);
	jmp	lcout	 #
	.seh_endproc
	.section .rdata,"dr"
.LC3:
	.ascii "\12\12\0"
.LC4:
	.ascii "Build information\12\12\0"
.LC5:
	.ascii "Compiler: \0"
.LC6:
	.ascii "GCC\0"
.LC7:
	.ascii "\12C language standard: \0"
.LC8:
	.ascii "\12\12Target operating system: \0"
.LC9:
	.ascii "Windows NT\0"
.LC10:
	.ascii "\12Target architecture: \0"
.LC11:
	.ascii "x64_86\0"
.LC12:
	.ascii "\12\12Build time: \0"
.LC13:
	.ascii "2024-07-12T11:35:18.982Z\0"
	.text
	.p2align 4
	.globl	version_extented
	.def	version_extented;	.scl	2;	.type	32;	.endef
	.seh_proc	version_extented
version_extented:
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$32, %rsp	 #,
	.seh_stackalloc	32
	.seh_endprologue
 # src\compiler\info\info.c:6:     lccol(LC_COLOR_RED, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$2, %ecx	 #,
 # src\compiler\info\info.c:36:     lsi64dec(c_version_buffer, (li64)(__STDC_VERSION__));
	leaq	c_version_buffer(%rip), %rbx	 #, tmp90
 # src\compiler\info\info.c:6:     lccol(LC_COLOR_RED, LC_COLOR_BLACK);
	call	lccol	 #
 # src\compiler\info\info.c:7:     lcout(X("Lena compiler "));
	leaq	.LC0(%rip), %rcx	 #, tmp82
	call	lcout	 #
 # src\compiler\info\info.c:8:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:9:     lcout(X("version "));
	leaq	.LC1(%rip), %rcx	 #, tmp83
	call	lcout	 #
 # src\compiler\info\info.c:10:     lccol(LC_COLOR_YELLOW, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$12, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:11:     lcout(LENA_VERSION_STR);
	leaq	.LC2(%rip), %rcx	 #, tmp84
	call	lcout	 #
 # src\compiler\info\info.c:20:     lccol(LC_COLOR_RED, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$2, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:21:     lcout(X("\n\n"));
	leaq	.LC3(%rip), %rcx	 #, tmp85
	call	lcout	 #
 # src\compiler\info\info.c:23:     lccol(LC_COLOR_YELLOW, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$12, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:24:     lcout(X("Build information\n\n"));
	leaq	.LC4(%rip), %rcx	 #, tmp86
	call	lcout	 #
 # src\compiler\info\info.c:26:     lccol(LC_COLOR_CYAN, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$14, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:27:     lcout(X("Compiler: "));
	leaq	.LC5(%rip), %rcx	 #, tmp87
	call	lcout	 #
 # src\compiler\info\info.c:29:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:30:     lcout(LENA_C_COMPILER_STR);
	leaq	.LC6(%rip), %rcx	 #, tmp88
	call	lcout	 #
 # src\compiler\info\info.c:32:     lccol(LC_COLOR_CYAN, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$14, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:33:     lcout(X("\nC language standard: "));
	leaq	.LC7(%rip), %rcx	 #, tmp89
	call	lcout	 #
 # src\compiler\info\info.c:35:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:36:     lsi64dec(c_version_buffer, (li64)(__STDC_VERSION__));
	movl	$201710, %edx	 #,
	movq	%rbx, %rcx	 # tmp90,
	call	lsi64dec	 #
 # src\compiler\info\info.c:37:     lcout(c_version_buffer);
	movq	%rbx, %rcx	 # tmp90,
	call	lcout	 #
 # src\compiler\info\info.c:39:     lccol(LC_COLOR_CYAN, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$14, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:40:     lcout(X("\n\nTarget operating system: "));
	leaq	.LC8(%rip), %rcx	 #, tmp92
	call	lcout	 #
 # src\compiler\info\info.c:42:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:43:     lcout(LENA_BUILD_OS_STR);
	leaq	.LC9(%rip), %rcx	 #, tmp93
	call	lcout	 #
 # src\compiler\info\info.c:45:     lccol(LC_COLOR_CYAN, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$14, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:46:     lcout(X("\nTarget architecture: "));
	leaq	.LC10(%rip), %rcx	 #, tmp94
	call	lcout	 #
 # src\compiler\info\info.c:48:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:49:     lcout(LENA_BUILD_ARCH_STR);
	leaq	.LC11(%rip), %rcx	 #, tmp95
	call	lcout	 #
 # src\compiler\info\info.c:51:     lccol(LC_COLOR_YELLOW, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$12, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:52:     lcout(X("\n\nBuild time: "));
	leaq	.LC12(%rip), %rcx	 #, tmp96
	call	lcout	 #
 # src\compiler\info\info.c:54:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:55:     lcout(LENA_BUILD_TIME_STR);
	leaq	.LC13(%rip), %rcx	 #, tmp97
 # src\compiler\info\info.c:56: }
	addq	$32, %rsp	 #,
	popq	%rbx	 #
 # src\compiler\info\info.c:55:     lcout(LENA_BUILD_TIME_STR);
	jmp	lcout	 #
	.seh_endproc
	.section .rdata,"dr"
.LC14:
	.ascii "Lena Compiler License\12\12\0"
	.align 8
.LC15:
	.ascii "The Lena compiler is licensed under the GNU General Public License version 3 (GPL-3.0).\12This license guarantees end users the freedom to run, study, share, and modify the software.\12\12\0"
.LC16:
	.ascii "GPL-3.0 License\12\0"
	.align 8
.LC17:
	.ascii "Copyright (c) 2024 The Lena Programming language\12\12This program is free software: you can redistribute it and/or modify\12it under the terms of the GNU General Public License as published by\12the Free Software Foundation, either version 3 of the License, or\12(at your option) any later version.\12\12but WITHOUT ANY WARRANTY; without even the implied warranty of\12MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the\12GNU General Public License for more details.\12\12You should have received a copy of the GNU General Public License\12along with this program. If not, see \0"
	.align 8
.LC18:
	.ascii "<https://www.gnu.org/licenses/>\0"
	.align 8
.LC19:
	.ascii ".\12\12For the full license text, please refer to the \0"
.LC20:
	.ascii "LICENSE \0"
	.align 8
.LC21:
	.ascii "file included with this software.\12\0"
	.text
	.p2align 4
	.globl	license
	.def	license;	.scl	2;	.type	32;	.endef
	.seh_proc	license
license:
	subq	$40, %rsp	 #,
	.seh_stackalloc	40
	.seh_endprologue
 # src\compiler\info\info.c:60:     lccol(LC_COLOR_RED, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$2, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:61:     lcout(X("Lena Compiler License\n\n"));
	leaq	.LC14(%rip), %rcx	 #, tmp82
	call	lcout	 #
 # src\compiler\info\info.c:63:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:64:     lcout(X("The Lena compiler is licensed under the GNU General Public License version 3 (GPL-3.0).\n\
	leaq	.LC15(%rip), %rcx	 #, tmp83
	call	lcout	 #
 # src\compiler\info\info.c:67:     lccol(LC_COLOR_GREEN, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$4, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:68:     lcout(X("GPL-3.0 License\n"));
	leaq	.LC16(%rip), %rcx	 #, tmp84
	call	lcout	 #
 # src\compiler\info\info.c:69:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:70:     lcout(X("Copyright (c) 2024 The Lena Programming language\n\n\
	leaq	.LC17(%rip), %rcx	 #, tmp85
	call	lcout	 #
 # src\compiler\info\info.c:80:     lccol(LC_COLOR_YELLOW, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$12, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:81:     lcout(X("<https://www.gnu.org/licenses/>"));
	leaq	.LC18(%rip), %rcx	 #, tmp86
	call	lcout	 #
 # src\compiler\info\info.c:83:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:84:     lcout(X(".\n\nFor the full license text, please refer to the "));
	leaq	.LC19(%rip), %rcx	 #, tmp87
	call	lcout	 #
 # src\compiler\info\info.c:85:     lccol(LC_COLOR_CYAN, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$14, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:86:     lcout(X("LICENSE "));
	leaq	.LC20(%rip), %rcx	 #, tmp88
	call	lcout	 #
 # src\compiler\info\info.c:87:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:88:     lcout(X("file included with this software.\n"));
	leaq	.LC21(%rip), %rcx	 #, tmp89
 # src\compiler\info\info.c:89: }
	addq	$40, %rsp	 #,
 # src\compiler\info\info.c:88:     lcout(X("file included with this software.\n"));
	jmp	lcout	 #
	.seh_endproc
	.section .rdata,"dr"
.LC22:
	.ascii "Lena Compiler\12\12\0"
	.align 8
.LC23:
	.ascii "The Lena compiler is a powerful tool designed for the Lena programming language,\12a high-performance system language that combines the efficiency of lower-level\12languages with the ease of use found in higher-level languages.\12Lena is specifically designed to run outside the main operating system,\12allowing it to access nearly all computer resources and achieve performance\12levels comparable to machine code or assembler. This makes Lena an excellent choice\12for developing optimized and resource-intensive applications.\0"
	.text
	.p2align 4
	.globl	help_about
	.def	help_about;	.scl	2;	.type	32;	.endef
	.seh_proc	help_about
help_about:
	subq	$40, %rsp	 #,
	.seh_stackalloc	40
	.seh_endprologue
 # src\compiler\info\info.c:94:     lccol(LC_COLOR_RED, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$2, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:95:     lcout(X("Lena Compiler\n\n"));
	leaq	.LC22(%rip), %rcx	 #, tmp82
	call	lcout	 #
 # src\compiler\info\info.c:97:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:98:     lcout(X("The Lena compiler is a powerful tool designed for the Lena programming language,\n\
	leaq	.LC23(%rip), %rcx	 #, tmp83
 # src\compiler\info\info.c:105: }
	addq	$40, %rsp	 #,
 # src\compiler\info\info.c:98:     lcout(X("The Lena compiler is a powerful tool designed for the Lena programming language,\n\
	jmp	lcout	 #
	.seh_endproc
	.section .rdata,"dr"
.LC24:
	.ascii "File Formats\12\0"
.LC25:
	.ascii "- .e\11: \0"
	.align 8
.LC26:
	.ascii "This is the bytecode file generated by the Lena compiler.\12\0"
.LC27:
	.ascii "- .le\11: \0"
	.align 8
.LC28:
	.ascii "This is the source code file for the Lena programming language.\12\0"
.LC29:
	.ascii "- .na\11: \0"
	.align 8
.LC30:
	.ascii "This file format is used for storing non-abstract representations of Lena programs, often containing decoded bytecode.\12\0"
.LC31:
	.ascii "- .exe\11: \0"
	.align 8
.LC32:
	.ascii "The executable file format generated by the Lena compiler for running applications.\0"
	.text
	.p2align 4
	.globl	help_formats
	.def	help_formats;	.scl	2;	.type	32;	.endef
	.seh_proc	help_formats
help_formats:
	subq	$40, %rsp	 #,
	.seh_stackalloc	40
	.seh_endprologue
 # src\compiler\info\info.c:108:     lccol(LC_COLOR_YELLOW, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$12, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:109:     lcout(X("File Formats\n"));
	leaq	.LC24(%rip), %rcx	 #, tmp82
	call	lcout	 #
 # src\compiler\info\info.c:111:     lccol(LC_COLOR_CYAN, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$14, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:112:     lcout(X("- .e\t: "));
	leaq	.LC25(%rip), %rcx	 #, tmp83
	call	lcout	 #
 # src\compiler\info\info.c:113:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:114:     lcout(X("This is the bytecode file generated by the Lena compiler.\n"));
	leaq	.LC26(%rip), %rcx	 #, tmp84
	call	lcout	 #
 # src\compiler\info\info.c:116:     lccol(LC_COLOR_CYAN, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$14, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:117:     lcout(X("- .le\t: "));
	leaq	.LC27(%rip), %rcx	 #, tmp85
	call	lcout	 #
 # src\compiler\info\info.c:118:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:119:     lcout(X("This is the source code file for the Lena programming language.\n"));
	leaq	.LC28(%rip), %rcx	 #, tmp86
	call	lcout	 #
 # src\compiler\info\info.c:121:     lccol(LC_COLOR_CYAN, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$14, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:122:     lcout(X("- .na\t: "));
	leaq	.LC29(%rip), %rcx	 #, tmp87
	call	lcout	 #
 # src\compiler\info\info.c:123:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:124:     lcout(X("This file format is used for storing non-abstract representations of Lena programs, often containing decoded bytecode.\n"));
	leaq	.LC30(%rip), %rcx	 #, tmp88
	call	lcout	 #
 # src\compiler\info\info.c:126:     lccol(LC_COLOR_CYAN, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$14, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:127:     lcout(X("- .exe\t: "));
	leaq	.LC31(%rip), %rcx	 #, tmp89
	call	lcout	 #
 # src\compiler\info\info.c:128:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:129:     lcout(X("The executable file format generated by the Lena compiler for running applications."));
	leaq	.LC32(%rip), %rcx	 #, tmp90
 # src\compiler\info\info.c:130: }
	addq	$40, %rsp	 #,
 # src\compiler\info\info.c:129:     lcout(X("The executable file format generated by the Lena compiler for running applications."));
	jmp	lcout	 #
	.seh_endproc
	.section .rdata,"dr"
.LC33:
	.ascii "Compilation Flags\12\0"
.LC34:
	.ascii "--version\11: \0"
	.align 8
.LC35:
	.ascii "Displays the current version of the Lena compiler.\12\0"
.LC36:
	.ascii "-v\11\11: \0"
	.align 8
.LC37:
	.ascii "A shorthand for --version, displaying the compiler's version information.\12\0"
.LC38:
	.ascii "--help\11\11: \0"
	.align 8
.LC39:
	.ascii "Provides a detailed help message, including usage instructions and available flags.\12\0"
.LC40:
	.ascii "--license\11: \0"
	.align 8
.LC41:
	.ascii "Shows the licensing information for the Lena compiler.\12\0"
.LC42:
	.ascii "--non-abstract\11: \0"
	.align 8
.LC43:
	.ascii "Generates a bytecode map for the compiled program, providing a detailed view of the bytecode structure.\12\0"
.LC44:
	.ascii "-o\11\11: \0"
	.align 8
.LC45:
	.ascii "Specifies the output file name for the compiled program.\0"
	.text
	.p2align 4
	.globl	help_flags
	.def	help_flags;	.scl	2;	.type	32;	.endef
	.seh_proc	help_flags
help_flags:
	subq	$40, %rsp	 #,
	.seh_stackalloc	40
	.seh_endprologue
 # src\compiler\info\info.c:133:     lccol(LC_COLOR_YELLOW, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$12, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:134:     lcout(X("Compilation Flags\n"));
	leaq	.LC33(%rip), %rcx	 #, tmp82
	call	lcout	 #
 # src\compiler\info\info.c:136:     lccol(LC_COLOR_GREEN, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$4, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:137:     lcout(X("--version\t: "));
	leaq	.LC34(%rip), %rcx	 #, tmp83
	call	lcout	 #
 # src\compiler\info\info.c:138:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:139:     lcout(X("Displays the current version of the Lena compiler.\n"));
	leaq	.LC35(%rip), %rcx	 #, tmp84
	call	lcout	 #
 # src\compiler\info\info.c:141:     lccol(LC_COLOR_GREEN, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$4, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:142:     lcout(X("-v\t\t: "));
	leaq	.LC36(%rip), %rcx	 #, tmp85
	call	lcout	 #
 # src\compiler\info\info.c:143:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:144:     lcout(X("A shorthand for --version, displaying the compiler's version information.\n"));
	leaq	.LC37(%rip), %rcx	 #, tmp86
	call	lcout	 #
 # src\compiler\info\info.c:146:     lccol(LC_COLOR_GREEN, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$4, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:147:     lcout(X("--help\t\t: "));
	leaq	.LC38(%rip), %rcx	 #, tmp87
	call	lcout	 #
 # src\compiler\info\info.c:148:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:149:     lcout(X("Provides a detailed help message, including usage instructions and available flags.\n"));
	leaq	.LC39(%rip), %rcx	 #, tmp88
	call	lcout	 #
 # src\compiler\info\info.c:151:     lccol(LC_COLOR_GREEN, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$4, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:152:     lcout(X("--license\t: "));
	leaq	.LC40(%rip), %rcx	 #, tmp89
	call	lcout	 #
 # src\compiler\info\info.c:153:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:154:     lcout(X("Shows the licensing information for the Lena compiler.\n"));
	leaq	.LC41(%rip), %rcx	 #, tmp90
	call	lcout	 #
 # src\compiler\info\info.c:156:     lccol(LC_COLOR_GREEN, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$4, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:157:     lcout(X("--non-abstract\t: "));
	leaq	.LC42(%rip), %rcx	 #, tmp91
	call	lcout	 #
 # src\compiler\info\info.c:158:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:159:     lcout(X("Generates a bytecode map for the compiled program, providing a detailed view of the bytecode structure.\n"));
	leaq	.LC43(%rip), %rcx	 #, tmp92
	call	lcout	 #
 # src\compiler\info\info.c:161:     lccol(LC_COLOR_GREEN, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$4, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:162:     lcout(X("-o\t\t: "));
	leaq	.LC44(%rip), %rcx	 #, tmp93
	call	lcout	 #
 # src\compiler\info\info.c:163:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:164:     lcout(X("Specifies the output file name for the compiled program."));
	leaq	.LC45(%rip), %rcx	 #, tmp94
 # src\compiler\info\info.c:165: }
	addq	$40, %rsp	 #,
 # src\compiler\info\info.c:164:     lcout(X("Specifies the output file name for the compiled program."));
	jmp	lcout	 #
	.seh_endproc
	.section .rdata,"dr"
.LC46:
	.ascii "Usage Examples\12\0"
.LC47:
	.ascii "lena \0"
.LC48:
	.ascii "main.le \0"
.LC49:
	.ascii "-o \0"
.LC50:
	.ascii "app.e \0"
.LC51:
	.ascii "--non-abstract\12\0"
	.align 8
.LC52:
	.ascii "This command compiles main.le into a bytecode file app.e and generates a non-abstract bytecode map.\12\12\0"
.LC53:
	.ascii "app \0"
.LC54:
	.ascii "or \0"
.LC55:
	.ascii "app.exe\12\0"
	.align 8
.LC56:
	.ascii "This command compiles main.le into a executable file app (.exe).\0"
	.text
	.p2align 4
	.globl	help_usage
	.def	help_usage;	.scl	2;	.type	32;	.endef
	.seh_proc	help_usage
help_usage:
	pushq	%rdi	 #
	.seh_pushreg	%rdi
	pushq	%rsi	 #
	.seh_pushreg	%rsi
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$32, %rsp	 #,
	.seh_stackalloc	32
	.seh_endprologue
 # src\compiler\info\info.c:168:     lccol(LC_COLOR_YELLOW, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$12, %ecx	 #,
 # src\compiler\info\info.c:172:     lcout(X("lena "));
	leaq	.LC47(%rip), %rdi	 #, tmp83
 # src\compiler\info\info.c:174:     lcout(X("main.le "));
	leaq	.LC48(%rip), %rsi	 #, tmp84
 # src\compiler\info\info.c:176:     lcout(X("-o "));
	leaq	.LC49(%rip), %rbx	 #, tmp85
 # src\compiler\info\info.c:168:     lccol(LC_COLOR_YELLOW, LC_COLOR_BLACK);
	call	lccol	 #
 # src\compiler\info\info.c:169:     lcout(X("Usage Examples\n"));
	leaq	.LC46(%rip), %rcx	 #, tmp82
	call	lcout	 #
 # src\compiler\info\info.c:171:     lccol(LC_COLOR_RED, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$2, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:172:     lcout(X("lena "));
	movq	%rdi, %rcx	 # tmp83,
	call	lcout	 #
 # src\compiler\info\info.c:173:     lccol(LC_COLOR_CYAN, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$14, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:174:     lcout(X("main.le "));
	movq	%rsi, %rcx	 # tmp84,
	call	lcout	 #
 # src\compiler\info\info.c:175:     lccol(LC_COLOR_GREEN, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$4, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:176:     lcout(X("-o "));
	movq	%rbx, %rcx	 # tmp85,
	call	lcout	 #
 # src\compiler\info\info.c:177:     lccol(LC_COLOR_CYAN, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$14, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:178:     lcout(X("app.e "));
	leaq	.LC50(%rip), %rcx	 #, tmp86
	call	lcout	 #
 # src\compiler\info\info.c:179:     lccol(LC_COLOR_GREEN, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$4, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:180:     lcout(X("--non-abstract\n"));
	leaq	.LC51(%rip), %rcx	 #, tmp87
	call	lcout	 #
 # src\compiler\info\info.c:181:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:182:     lcout(X("This command compiles main.le into a bytecode file app.e and generates a non-abstract bytecode map.\n\n"));
	leaq	.LC52(%rip), %rcx	 #, tmp88
	call	lcout	 #
 # src\compiler\info\info.c:184:     lccol(LC_COLOR_RED, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$2, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:185:     lcout(X("lena "));
	movq	%rdi, %rcx	 # tmp83,
	call	lcout	 #
 # src\compiler\info\info.c:186:     lccol(LC_COLOR_CYAN, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$14, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:187:     lcout(X("main.le "));
	movq	%rsi, %rcx	 # tmp84,
	call	lcout	 #
 # src\compiler\info\info.c:188:     lccol(LC_COLOR_GREEN, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$4, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:189:     lcout(X("-o "));
	movq	%rbx, %rcx	 # tmp85,
	call	lcout	 #
 # src\compiler\info\info.c:190:     lccol(LC_COLOR_CYAN, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$14, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:191:     lcout(X("app "));
	leaq	.LC53(%rip), %rcx	 #, tmp92
	call	lcout	 #
 # src\compiler\info\info.c:194:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:195:     lcout(X("or "));
	leaq	.LC54(%rip), %rcx	 #, tmp93
	call	lcout	 #
 # src\compiler\info\info.c:197:     lccol(LC_COLOR_RED, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$2, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:198:     lcout(X("lena "));
	movq	%rdi, %rcx	 # tmp83,
	call	lcout	 #
 # src\compiler\info\info.c:199:     lccol(LC_COLOR_CYAN, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$14, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:200:     lcout(X("main.le "));
	movq	%rsi, %rcx	 # tmp84,
	call	lcout	 #
 # src\compiler\info\info.c:201:     lccol(LC_COLOR_GREEN, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$4, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:202:     lcout(X("-o "));
	movq	%rbx, %rcx	 # tmp85,
	call	lcout	 #
 # src\compiler\info\info.c:203:     lccol(LC_COLOR_CYAN, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$14, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:204:     lcout(X("app.exe\n"));
	leaq	.LC55(%rip), %rcx	 #, tmp97
	call	lcout	 #
 # src\compiler\info\info.c:206:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:207:     lcout(X("This command compiles main.le into a executable file app (.exe)."));
	leaq	.LC56(%rip), %rcx	 #, tmp98
 # src\compiler\info\info.c:208: }
	addq	$32, %rsp	 #,
	popq	%rbx	 #
	popq	%rsi	 #
	popq	%rdi	 #
 # src\compiler\info\info.c:207:     lcout(X("This command compiles main.le into a executable file app (.exe)."));
	jmp	lcout	 #
	.seh_endproc
	.section .rdata,"dr"
.LC57:
	.ascii "SHE Executor\12\0"
	.align 8
.LC58:
	.ascii "The SHE (Software-Clonable Hypervisor Executor) is a separate application that operates independently of the Lena compiler. It functions as an external device on Windows and as a kernel submodule on Linux. SHE provides Lena applications with unparalleled access to system resources and exceptional performance, ensuring that Lena programs run efficiently and securely, with advanced memory and safety checks.\12\0"
	.text
	.p2align 4
	.globl	help_about_she
	.def	help_about_she;	.scl	2;	.type	32;	.endef
	.seh_proc	help_about_she
help_about_she:
	subq	$40, %rsp	 #,
	.seh_stackalloc	40
	.seh_endprologue
 # src\compiler\info\info.c:211:     lccol(LC_COLOR_YELLOW, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$12, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:212:     lcout(X("SHE Executor\n"));
	leaq	.LC57(%rip), %rcx	 #, tmp82
	call	lcout	 #
 # src\compiler\info\info.c:214:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:215:     lcout(X("The SHE (Software-Clonable Hypervisor Executor) is a separate application that operates independently of the Lena compiler. It functions as an external device on Windows and as a kernel submodule on Linux. SHE provides Lena applications with unparalleled access to system resources and exceptional performance, ensuring that Lena programs run efficiently and securely, with advanced memory and safety checks.\n"));
	leaq	.LC58(%rip), %rcx	 #, tmp83
 # src\compiler\info\info.c:216: }
	addq	$40, %rsp	 #,
 # src\compiler\info\info.c:215:     lcout(X("The SHE (Software-Clonable Hypervisor Executor) is a separate application that operates independently of the Lena compiler. It functions as an external device on Windows and as a kernel submodule on Linux. SHE provides Lena applications with unparalleled access to system resources and exceptional performance, ensuring that Lena programs run efficiently and securely, with advanced memory and safety checks.\n"));
	jmp	lcout	 #
	.seh_endproc
	.p2align 4
	.globl	help
	.def	help;	.scl	2;	.type	32;	.endef
	.seh_proc	help
help:
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$32, %rsp	 #,
	.seh_stackalloc	32
	.seh_endprologue
 # src\compiler\info\info.c:94:     lccol(LC_COLOR_RED, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$2, %ecx	 #,
 # src\compiler\info\info.c:220:     lcout(X("\n\n"));
	leaq	.LC3(%rip), %rbx	 #, tmp84
 # src\compiler\info\info.c:94:     lccol(LC_COLOR_RED, LC_COLOR_BLACK);
	call	lccol	 #
 # src\compiler\info\info.c:95:     lcout(X("Lena Compiler\n\n"));
	leaq	.LC22(%rip), %rcx	 #, tmp82
	call	lcout	 #
 # src\compiler\info\info.c:97:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:98:     lcout(X("The Lena compiler is a powerful tool designed for the Lena programming language,\n\
	leaq	.LC23(%rip), %rcx	 #, tmp83
	call	lcout	 #
 # src\compiler\info\info.c:220:     lcout(X("\n\n"));
	movq	%rbx, %rcx	 # tmp84,
	call	lcout	 #
 # src\compiler\info\info.c:221:     help_formats();
	call	help_formats	 #
 # src\compiler\info\info.c:222:     lcout(X("\n\n"));
	movq	%rbx, %rcx	 # tmp84,
	call	lcout	 #
 # src\compiler\info\info.c:223:     help_flags();
	call	help_flags	 #
 # src\compiler\info\info.c:224:     lcout(X("\n\n"));
	movq	%rbx, %rcx	 # tmp84,
	call	lcout	 #
 # src\compiler\info\info.c:225:     help_usage();
	call	help_usage	 #
 # src\compiler\info\info.c:226:     lcout(X("\n\n"));
	movq	%rbx, %rcx	 # tmp84,
	call	lcout	 #
 # src\compiler\info\info.c:211:     lccol(LC_COLOR_YELLOW, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$12, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:212:     lcout(X("SHE Executor\n"));
	leaq	.LC57(%rip), %rcx	 #, tmp88
	call	lcout	 #
 # src\compiler\info\info.c:214:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\info\info.c:215:     lcout(X("The SHE (Software-Clonable Hypervisor Executor) is a separate application that operates independently of the Lena compiler. It functions as an external device on Windows and as a kernel submodule on Linux. SHE provides Lena applications with unparalleled access to system resources and exceptional performance, ensuring that Lena programs run efficiently and securely, with advanced memory and safety checks.\n"));
	leaq	.LC58(%rip), %rcx	 #, tmp89
 # src\compiler\info\info.c:228: }
	addq	$32, %rsp	 #,
	popq	%rbx	 #
 # src\compiler\info\info.c:215:     lcout(X("The SHE (Software-Clonable Hypervisor Executor) is a separate application that operates independently of the Lena compiler. It functions as an external device on Windows and as a kernel submodule on Linux. SHE provides Lena applications with unparalleled access to system resources and exceptional performance, ensuring that Lena programs run efficiently and securely, with advanced memory and safety checks.\n"));
	jmp	lcout	 #
	.seh_endproc
	.globl	c_version_buffer
	.bss
	.align 32
c_version_buffer:
	.space 65
	.ident	"GCC: (Rev6, Built by MSYS2 project) 13.2.0"
	.def	lccol;	.scl	2;	.type	32;	.endef
	.def	lcout;	.scl	2;	.type	32;	.endef
	.def	lsi64dec;	.scl	2;	.type	32;	.endef
