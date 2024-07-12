	.file	"errors.c"
 # GNU C17 (Rev6, Built by MSYS2 project) version 13.2.0 (x86_64-w64-mingw32)
 #	compiled by GNU C version 13.2.0, GMP version 6.3.0, MPFR version 4.2.1, MPC version 1.3.1, isl version isl-0.26-GMP

 # GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
 # options passed: -municode -m64 -mtune=generic -march=nocona -O3 -std=c17
	.text
	.section .rdata,"dr"
.LC0:
	.ascii "[\0"
.LC1:
	.ascii "Lena\0"
.LC2:
	.ascii "]: \0"
	.text
	.p2align 4
	.globl	greeting
	.def	greeting;	.scl	2;	.type	32;	.endef
	.seh_proc	greeting
greeting:
	subq	$40, %rsp	 #,
	.seh_stackalloc	40
	.seh_endprologue
 # src\compiler\errors\errors.c:5:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\errors\errors.c:6:     lcout(X("["));
	leaq	.LC0(%rip), %rcx	 #, tmp82
	call	lcout	 #
 # src\compiler\errors\errors.c:7:     lccol(LC_COLOR_RED, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$2, %ecx	 #,
	call	lccol	 #
 # src\compiler\errors\errors.c:8:     lcout(X("Lena"));
	leaq	.LC1(%rip), %rcx	 #, tmp83
	call	lcout	 #
 # src\compiler\errors\errors.c:9:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\errors\errors.c:10:     lcout(X("]: "));
	leaq	.LC2(%rip), %rcx	 #, tmp84
 # src\compiler\errors\errors.c:11: }
	addq	$40, %rsp	 #,
 # src\compiler\errors\errors.c:10:     lcout(X("]: "));
	jmp	lcout	 #
	.seh_endproc
	.section .rdata,"dr"
.LC3:
	.ascii "][\0"
	.text
	.p2align 4
	.globl	greeting_extended
	.def	greeting_extended;	.scl	2;	.type	32;	.endef
	.seh_proc	greeting_extended
greeting_extended:
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$32, %rsp	 #,
	.seh_stackalloc	32
	.seh_endprologue
 # src\compiler\errors\errors.c:15:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
 # src\compiler\errors\errors.c:14: void greeting_extended(const lc* str) {
	movq	%rcx, %rbx	 # tmp87, str
 # src\compiler\errors\errors.c:15:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\errors\errors.c:16:     lcout(X("["));
	leaq	.LC0(%rip), %rcx	 #, tmp83
	call	lcout	 #
 # src\compiler\errors\errors.c:17:     lccol(LC_COLOR_RED, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$2, %ecx	 #,
	call	lccol	 #
 # src\compiler\errors\errors.c:18:     lcout(X("Lena"));
	leaq	.LC1(%rip), %rcx	 #, tmp84
	call	lcout	 #
 # src\compiler\errors\errors.c:19:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\errors\errors.c:20:     lcout(X("]["));
	leaq	.LC3(%rip), %rcx	 #, tmp85
	call	lcout	 #
 # src\compiler\errors\errors.c:21:     lccol(LC_COLOR_YELLOW, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$12, %ecx	 #,
	call	lccol	 #
 # src\compiler\errors\errors.c:22:     lcout(str);
	movq	%rbx, %rcx	 # str,
	call	lcout	 #
 # src\compiler\errors\errors.c:23:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\compiler\errors\errors.c:24:     lcout(X("]: "));
	leaq	.LC2(%rip), %rcx	 #, tmp86
 # src\compiler\errors\errors.c:25: }
	addq	$32, %rsp	 #,
	popq	%rbx	 #
 # src\compiler\errors\errors.c:24:     lcout(X("]: "));
	jmp	lcout	 #
	.seh_endproc
	.ident	"GCC: (Rev6, Built by MSYS2 project) 13.2.0"
	.def	lccol;	.scl	2;	.type	32;	.endef
	.def	lcout;	.scl	2;	.type	32;	.endef
