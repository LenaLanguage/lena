	.file	"flags.c"
 # GNU C17 (Rev6, Built by MSYS2 project) version 13.2.0 (x86_64-w64-mingw32)
 #	compiled by GNU C version 13.2.0, GMP version 6.3.0, MPFR version 4.2.1, MPC version 1.3.1, isl version isl-0.26-GMP

 # GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
 # options passed: -municode -m64 -mtune=generic -march=nocona -O3 -std=c17
	.text
	.p2align 4
	.globl	is_postfix
	.def	is_postfix;	.scl	2;	.type	32;	.endef
	.seh_proc	is_postfix
is_postfix:
	pushq	%rbp	 #
	.seh_pushreg	%rbp
	pushq	%rdi	 #
	.seh_pushreg	%rdi
	pushq	%rsi	 #
	.seh_pushreg	%rsi
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$40, %rsp	 #,
	.seh_stackalloc	40
	.seh_endprologue
 # src\compiler\flags\flags.c:20: lbool is_postfix(lc* str, const lc* postfix) {
	movq	%rcx, %rbx	 # tmp94, str
 # src\compiler\flags\flags.c:21:     lsz postfix_size = lssize(postfix),
	movq	%rdx, %rcx	 # postfix,
 # src\compiler\flags\flags.c:20: lbool is_postfix(lc* str, const lc* postfix) {
	movq	%rdx, %rdi	 # tmp95, postfix
 # src\compiler\flags\flags.c:21:     lsz postfix_size = lssize(postfix),
	call	lssize	 #
 # src\compiler\flags\flags.c:22:     str_len = lslen(str);
	movq	%rbx, %rcx	 # str,
 # src\compiler\flags\flags.c:21:     lsz postfix_size = lssize(postfix),
	movq	%rax, %rbp	 # tmp96, postfix_size
 # src\compiler\flags\flags.c:22:     str_len = lslen(str);
	call	lslen	 #
 # src\compiler\flags\flags.c:24:     if (str_len <= lslen(postfix)) {
	movq	%rdi, %rcx	 # postfix,
 # src\compiler\flags\flags.c:22:     str_len = lslen(str);
	movq	%rax, %rsi	 # tmp97, str_len
 # src\compiler\flags\flags.c:24:     if (str_len <= lslen(postfix)) {
	call	lslen	 #
 # src\compiler\flags\flags.c:24:     if (str_len <= lslen(postfix)) {
	cmpq	%rsi, %rax	 # str_len, tmp98
	jb	.L4	 #,
 # src\compiler\flags\flags.c:28: }
	xorl	%eax, %eax	 #
	addq	$40, %rsp	 #,
	popq	%rbx	 #
	popq	%rsi	 #
	popq	%rdi	 #
	popq	%rbp	 #
	ret	
	.p2align 4,,10
	.p2align 3
.L4:
 # src\compiler\flags\flags.c:27:     return lscmp(str + lssizen(str, str_len - postfix_size), postfix);
	subq	%rbp, %rsi	 # postfix_size, str_len
	movq	%rbx, %rcx	 # str,
	movq	%rsi, %rdx	 # str_len, tmp91
	call	lssizen	 #
 # src\compiler\flags\flags.c:27:     return lscmp(str + lssizen(str, str_len - postfix_size), postfix);
	movq	%rdi, %rdx	 # postfix,
 # src\compiler\flags\flags.c:27:     return lscmp(str + lssizen(str, str_len - postfix_size), postfix);
	leaq	(%rbx,%rax), %rcx	 #, tmp92
 # src\compiler\flags\flags.c:28: }
	addq	$40, %rsp	 #,
	popq	%rbx	 #
	popq	%rsi	 #
	popq	%rdi	 #
	popq	%rbp	 #
 # src\compiler\flags\flags.c:27:     return lscmp(str + lssizen(str, str_len - postfix_size), postfix);
	jmp	lscmp	 #
	.seh_endproc
	.section .rdata,"dr"
.LC0:
	.ascii "v\0"
.LC1:
	.ascii "o\0"
.LC2:
	.ascii ".e\0"
.LC3:
	.ascii ".le\0"
.LC4:
	.ascii ".exe\0"
	.text
	.p2align 4
	.globl	flags_recognize
	.def	flags_recognize;	.scl	2;	.type	32;	.endef
	.seh_proc	flags_recognize
flags_recognize:
	pushq	%r13	 #
	.seh_pushreg	%r13
	pushq	%r12	 #
	.seh_pushreg	%r12
	pushq	%rbp	 #
	.seh_pushreg	%rbp
	pushq	%rdi	 #
	.seh_pushreg	%rdi
	pushq	%rsi	 #
	.seh_pushreg	%rsi
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$40, %rsp	 #,
	.seh_stackalloc	40
	.seh_endprologue
 # src\compiler\flags\flags.c:32:     if (str[0] == '-') {
	cmpb	$45, (%rcx)	 #, *str_38(D)
 # src\compiler\flags\flags.c:31: compiler_flag_t flags_recognize(lc* str) {
	movq	%rcx, %rbx	 # tmp154, str
 # src\compiler\flags\flags.c:32:     if (str[0] == '-') {
	jne	.L6	 #,
 # src\compiler\flags\flags.c:33:         if (str[1] == '-') {
	cmpb	$45, 1(%rcx)	 #, MEM[(lc *)str_38(D) + 1B]
	je	.L7	 #,
 # src\compiler\flags\flags.c:47:                 if (lscmp(str + 1, flags_buffer[i]) && (lslen(str) == lslen(flags_buffer[i]) + 1)) {
	leaq	1(%rcx), %rsi	 #, _100
 # src\compiler\flags\flags.c:47:                 if (lscmp(str + 1, flags_buffer[i]) && (lslen(str) == lslen(flags_buffer[i]) + 1)) {
	leaq	.LC0(%rip), %rdi	 #, tmp129
	movq	%rdi, %rdx	 # tmp129,
	movq	%rsi, %rcx	 # _100,
	call	lscmp	 #
 # src\compiler\flags\flags.c:47:                 if (lscmp(str + 1, flags_buffer[i]) && (lslen(str) == lslen(flags_buffer[i]) + 1)) {
	testb	%al, %al	 # tmp155
	jne	.L8	 #,
.L12:
 # src\compiler\flags\flags.c:47:                 if (lscmp(str + 1, flags_buffer[i]) && (lslen(str) == lslen(flags_buffer[i]) + 1)) {
	leaq	.LC1(%rip), %rdi	 #, tmp130
	movq	%rsi, %rcx	 # _100,
	movq	%rdi, %rdx	 # tmp130,
	call	lscmp	 #
 # src\compiler\flags\flags.c:47:                 if (lscmp(str + 1, flags_buffer[i]) && (lslen(str) == lslen(flags_buffer[i]) + 1)) {
	testb	%al, %al	 # tmp156
	jne	.L37	 #,
.L10:
 # src\compiler\flags\flags.c:42:             return COMPILER_FLAG_UNRECOGNIZED;
	movl	$11, %eax	 #, <retval>
.L5:
 # src\compiler\flags\flags.c:74: }
	addq	$40, %rsp	 #,
	popq	%rbx	 #
	popq	%rsi	 #
	popq	%rdi	 #
	popq	%rbp	 #
	popq	%r12	 #
	popq	%r13	 #
	ret	
	.p2align 4,,10
	.p2align 3
.L6:
 # src\compiler\flags\flags.c:21:     lsz postfix_size = lssize(postfix),
	leaq	.LC2(%rip), %rdi	 #, tmp137
	movq	%rdi, %rcx	 # tmp137,
	call	lssize	 #
 # src\compiler\flags\flags.c:22:     str_len = lslen(str);
	movq	%rbx, %rcx	 # str,
 # src\compiler\flags\flags.c:21:     lsz postfix_size = lssize(postfix),
	movq	%rax, %rbp	 # tmp164, postfix_size
 # src\compiler\flags\flags.c:22:     str_len = lslen(str);
	call	lslen	 #
 # src\compiler\flags\flags.c:24:     if (str_len <= lslen(postfix)) {
	movq	%rdi, %rcx	 # tmp137,
 # src\compiler\flags\flags.c:22:     str_len = lslen(str);
	movq	%rax, %rsi	 # tmp165, str_len
 # src\compiler\flags\flags.c:24:     if (str_len <= lslen(postfix)) {
	call	lslen	 #
 # src\compiler\flags\flags.c:24:     if (str_len <= lslen(postfix)) {
	cmpq	%rsi, %rax	 # str_len, tmp166
	jnb	.L19	 #,
 # src\compiler\flags\flags.c:27:     return lscmp(str + lssizen(str, str_len - postfix_size), postfix);
	movq	%rsi, %rdx	 # str_len, str_len
	movq	%rbx, %rcx	 # str,
	subq	%rbp, %rdx	 # postfix_size, str_len
	call	lssizen	 #
 # src\compiler\flags\flags.c:27:     return lscmp(str + lssizen(str, str_len - postfix_size), postfix);
	movq	%rdi, %rdx	 # tmp137,
 # src\compiler\flags\flags.c:27:     return lscmp(str + lssizen(str, str_len - postfix_size), postfix);
	leaq	(%rbx,%rax), %rcx	 #, tmp142
 # src\compiler\flags\flags.c:27:     return lscmp(str + lssizen(str, str_len - postfix_size), postfix);
	call	lscmp	 #
	movl	%eax, %edx	 #, tmp171
 # src\compiler\flags\flags.c:57:             return COMPILER_FLAG_FILENAME_E;
	movl	$6, %eax	 #, <retval>
 # src\compiler\flags\flags.c:56:         if (is_postfix(str, X(".e"))) {
	testb	%dl, %dl	 # tmp171
	jne	.L5	 #,
.L19:
 # src\compiler\flags\flags.c:21:     lsz postfix_size = lssize(postfix),
	leaq	.LC3(%rip), %rdi	 #, tmp139
	movq	%rdi, %rcx	 # tmp139,
	call	lssize	 #
 # src\compiler\flags\flags.c:22:     str_len = lslen(str);
	movq	%rbx, %rcx	 # str,
 # src\compiler\flags\flags.c:21:     lsz postfix_size = lssize(postfix),
	movq	%rax, %rbp	 # tmp167, postfix_size
 # src\compiler\flags\flags.c:22:     str_len = lslen(str);
	call	lslen	 #
 # src\compiler\flags\flags.c:24:     if (str_len <= lslen(postfix)) {
	movq	%rdi, %rcx	 # tmp139,
 # src\compiler\flags\flags.c:22:     str_len = lslen(str);
	movq	%rax, %rsi	 # tmp168, str_len
 # src\compiler\flags\flags.c:24:     if (str_len <= lslen(postfix)) {
	call	lslen	 #
 # src\compiler\flags\flags.c:24:     if (str_len <= lslen(postfix)) {
	cmpq	%rsi, %rax	 # str_len, tmp169
	jb	.L38	 #,
.L17:
 # src\compiler\flags\flags.c:21:     lsz postfix_size = lssize(postfix),
	leaq	.LC4(%rip), %rdi	 #, tmp144
	movq	%rdi, %rcx	 # tmp144,
	call	lssize	 #
 # src\compiler\flags\flags.c:22:     str_len = lslen(str);
	movq	%rbx, %rcx	 # str,
 # src\compiler\flags\flags.c:21:     lsz postfix_size = lssize(postfix),
	movq	%rax, %rbp	 # tmp172, postfix_size
 # src\compiler\flags\flags.c:22:     str_len = lslen(str);
	call	lslen	 #
 # src\compiler\flags\flags.c:24:     if (str_len <= lslen(postfix)) {
	movq	%rdi, %rcx	 # tmp144,
 # src\compiler\flags\flags.c:22:     str_len = lslen(str);
	movq	%rax, %rsi	 # tmp173, str_len
 # src\compiler\flags\flags.c:24:     if (str_len <= lslen(postfix)) {
	call	lslen	 #
 # src\compiler\flags\flags.c:24:     if (str_len <= lslen(postfix)) {
	cmpq	%rsi, %rax	 # str_len, tmp174
	jb	.L39	 #,
.L20:
 # src\compiler\flags\flags.c:47:                 if (lscmp(str + 1, flags_buffer[i]) && (lslen(str) == lslen(flags_buffer[i]) + 1)) {
	xorl	%edi, %edi	 # i
	jmp	.L22	 #
	.p2align 4,,10
	.p2align 3
.L23:
 # src\compiler\flags\flags.c:68:             if (str[i] == (lc)('.')) {
	cmpb	$46, (%rbx,%rsi)	 #, *_23
	je	.L29	 #,
 # src\compiler\flags\flags.c:67:         for (lu8 i = 0; i < lslen(str); ++i) {
	addl	$1, %edi	 #, i
.L22:
 # src\compiler\flags\flags.c:67:         for (lu8 i = 0; i < lslen(str); ++i) {
	movq	%rbx, %rcx	 # str,
 # src\compiler\flags\flags.c:67:         for (lu8 i = 0; i < lslen(str); ++i) {
	movzbl	%dil, %esi	 # i, _25
 # src\compiler\flags\flags.c:67:         for (lu8 i = 0; i < lslen(str); ++i) {
	call	lslen	 #
 # src\compiler\flags\flags.c:67:         for (lu8 i = 0; i < lslen(str); ++i) {
	cmpq	%rax, %rsi	 # tmp179, _25
	jb	.L23	 #,
 # src\compiler\flags\flags.c:73:     return COMPILER_FLAG_FILENAME;
	movl	$9, %eax	 #, <retval>
	jmp	.L5	 #
	.p2align 4,,10
	.p2align 3
.L7:
 # src\compiler\flags\flags.c:38:                 if (lscmp(str + 2, flags_buffer[i]) && (lslen(str) == lslen(flags_buffer[i]) + 2)) {
	leaq	2(%rcx), %r12	 #, _120
	movl	$2, %esi	 #, ivtmp.14
	leaq	flags_buffer(%rip), %rbp	 #, tmp153
.L15:
 # src\compiler\flags\flags.c:38:                 if (lscmp(str + 2, flags_buffer[i]) && (lslen(str) == lslen(flags_buffer[i]) + 2)) {
	movq	0(%rbp,%rsi,8), %rdi	 # MEM[(lc * *)&flags_buffer + ivtmp.14_20 * 8], _4
 # src\compiler\flags\flags.c:38:                 if (lscmp(str + 2, flags_buffer[i]) && (lslen(str) == lslen(flags_buffer[i]) + 2)) {
	movq	%r12, %rcx	 # _120,
	movq	%rdi, %rdx	 # _4,
	call	lscmp	 #
 # src\compiler\flags\flags.c:38:                 if (lscmp(str + 2, flags_buffer[i]) && (lslen(str) == lslen(flags_buffer[i]) + 2)) {
	testb	%al, %al	 # tmp161
	jne	.L40	 #,
.L14:
 # src\compiler\flags\flags.c:36:                 i <= COMPILER_DD_FLAG_MAX; ++i) {
	addq	$1, %rsi	 #, ivtmp.14
	cmpq	$6, %rsi	 #, ivtmp.14
	jne	.L15	 #,
	jmp	.L10	 #
	.p2align 4,,10
	.p2align 3
.L38:
 # src\compiler\flags\flags.c:27:     return lscmp(str + lssizen(str, str_len - postfix_size), postfix);
	movq	%rsi, %rdx	 # str_len, str_len
	movq	%rbx, %rcx	 # str,
	subq	%rbp, %rdx	 # postfix_size, str_len
	call	lssizen	 #
 # src\compiler\flags\flags.c:27:     return lscmp(str + lssizen(str, str_len - postfix_size), postfix);
	movq	%rdi, %rdx	 # tmp139,
 # src\compiler\flags\flags.c:27:     return lscmp(str + lssizen(str, str_len - postfix_size), postfix);
	leaq	(%rbx,%rax), %rcx	 #, tmp147
 # src\compiler\flags\flags.c:27:     return lscmp(str + lssizen(str, str_len - postfix_size), postfix);
	call	lscmp	 #
	movl	%eax, %edx	 #, tmp176
 # src\compiler\flags\flags.c:60:             return COMPILER_FLAG_FILENAME_LE;
	movl	$8, %eax	 #, <retval>
 # src\compiler\flags\flags.c:59:         if (is_postfix(str, X(".le"))) {
	testb	%dl, %dl	 # tmp176
	je	.L17	 #,
 # src\compiler\flags\flags.c:74: }
	addq	$40, %rsp	 #,
	popq	%rbx	 #
	popq	%rsi	 #
	popq	%rdi	 #
	popq	%rbp	 #
	popq	%r12	 #
	popq	%r13	 #
	ret	
	.p2align 4,,10
	.p2align 3
.L39:
 # src\compiler\flags\flags.c:27:     return lscmp(str + lssizen(str, str_len - postfix_size), postfix);
	movq	%rsi, %rdx	 # str_len, str_len
	movq	%rbx, %rcx	 # str,
	subq	%rbp, %rdx	 # postfix_size, str_len
	call	lssizen	 #
 # src\compiler\flags\flags.c:27:     return lscmp(str + lssizen(str, str_len - postfix_size), postfix);
	movq	%rdi, %rdx	 # tmp144,
 # src\compiler\flags\flags.c:27:     return lscmp(str + lssizen(str, str_len - postfix_size), postfix);
	leaq	(%rbx,%rax), %rcx	 #, tmp150
 # src\compiler\flags\flags.c:27:     return lscmp(str + lssizen(str, str_len - postfix_size), postfix);
	call	lscmp	 #
	movl	%eax, %edx	 #, tmp178
 # src\compiler\flags\flags.c:63:             return COMPILER_FLAG_FILENAME_EXE;
	movl	$7, %eax	 #, <retval>
 # src\compiler\flags\flags.c:62:         if (is_postfix(str, X(".exe"))) {
	testb	%dl, %dl	 # tmp178
	jne	.L5	 #,
	jmp	.L20	 #
	.p2align 4,,10
	.p2align 3
.L40:
 # src\compiler\flags\flags.c:38:                 if (lscmp(str + 2, flags_buffer[i]) && (lslen(str) == lslen(flags_buffer[i]) + 2)) {
	movq	%rbx, %rcx	 # str,
	call	lslen	 #
 # src\compiler\flags\flags.c:38:                 if (lscmp(str + 2, flags_buffer[i]) && (lslen(str) == lslen(flags_buffer[i]) + 2)) {
	movq	%rdi, %rcx	 # _4,
 # src\compiler\flags\flags.c:38:                 if (lscmp(str + 2, flags_buffer[i]) && (lslen(str) == lslen(flags_buffer[i]) + 2)) {
	movq	%rax, %r13	 # tmp162, _7
 # src\compiler\flags\flags.c:38:                 if (lscmp(str + 2, flags_buffer[i]) && (lslen(str) == lslen(flags_buffer[i]) + 2)) {
	call	lslen	 #
 # src\compiler\flags\flags.c:38:                 if (lscmp(str + 2, flags_buffer[i]) && (lslen(str) == lslen(flags_buffer[i]) + 2)) {
	addq	$2, %rax	 #, tmp136
 # src\compiler\flags\flags.c:38:                 if (lscmp(str + 2, flags_buffer[i]) && (lslen(str) == lslen(flags_buffer[i]) + 2)) {
	cmpq	%rax, %r13	 # tmp136, _7
	jne	.L14	 #,
 # src\compiler\flags\flags.c:39:                     return (compiler_flag_t)(i);
	movzbl	%sil, %eax	 # ivtmp.14, <retval>
	jmp	.L5	 #
	.p2align 4,,10
	.p2align 3
.L8:
 # src\compiler\flags\flags.c:47:                 if (lscmp(str + 1, flags_buffer[i]) && (lslen(str) == lslen(flags_buffer[i]) + 1)) {
	movq	%rbx, %rcx	 # str,
	call	lslen	 #
 # src\compiler\flags\flags.c:47:                 if (lscmp(str + 1, flags_buffer[i]) && (lslen(str) == lslen(flags_buffer[i]) + 1)) {
	movq	%rdi, %rcx	 # tmp129,
 # src\compiler\flags\flags.c:47:                 if (lscmp(str + 1, flags_buffer[i]) && (lslen(str) == lslen(flags_buffer[i]) + 1)) {
	movq	%rax, %rbp	 # tmp157, _39
 # src\compiler\flags\flags.c:47:                 if (lscmp(str + 1, flags_buffer[i]) && (lslen(str) == lslen(flags_buffer[i]) + 1)) {
	call	lslen	 #
 # src\compiler\flags\flags.c:47:                 if (lscmp(str + 1, flags_buffer[i]) && (lslen(str) == lslen(flags_buffer[i]) + 1)) {
	addq	$1, %rax	 #, tmp132
 # src\compiler\flags\flags.c:47:                 if (lscmp(str + 1, flags_buffer[i]) && (lslen(str) == lslen(flags_buffer[i]) + 1)) {
	cmpq	%rax, %rbp	 # tmp132, _39
	jne	.L12	 #,
	xorl	%eax, %eax	 # <retval>
	jmp	.L5	 #
	.p2align 4,,10
	.p2align 3
.L37:
 # src\compiler\flags\flags.c:47:                 if (lscmp(str + 1, flags_buffer[i]) && (lslen(str) == lslen(flags_buffer[i]) + 1)) {
	movq	%rbx, %rcx	 # str,
	call	lslen	 #
 # src\compiler\flags\flags.c:47:                 if (lscmp(str + 1, flags_buffer[i]) && (lslen(str) == lslen(flags_buffer[i]) + 1)) {
	movq	%rdi, %rcx	 # tmp130,
 # src\compiler\flags\flags.c:47:                 if (lscmp(str + 1, flags_buffer[i]) && (lslen(str) == lslen(flags_buffer[i]) + 1)) {
	movq	%rax, %rbx	 # tmp159, _115
 # src\compiler\flags\flags.c:47:                 if (lscmp(str + 1, flags_buffer[i]) && (lslen(str) == lslen(flags_buffer[i]) + 1)) {
	call	lslen	 #
 # src\compiler\flags\flags.c:47:                 if (lscmp(str + 1, flags_buffer[i]) && (lslen(str) == lslen(flags_buffer[i]) + 1)) {
	addq	$1, %rax	 #, tmp134
 # src\compiler\flags\flags.c:47:                 if (lscmp(str + 1, flags_buffer[i]) && (lslen(str) == lslen(flags_buffer[i]) + 1)) {
	cmpq	%rax, %rbx	 # tmp134, _115
	jne	.L10	 #,
	movl	$1, %eax	 #, <retval>
 # src\compiler\flags\flags.c:48:                     return (compiler_flag_t)(i);
	jmp	.L5	 #
	.p2align 4,,10
	.p2align 3
.L29:
 # src\compiler\flags\flags.c:69:                 return COMPILER_FLAG_FILENAME_OTHER;
	movl	$10, %eax	 #, <retval>
	jmp	.L5	 #
	.seh_endproc
	.p2align 4
	.globl	is_compilation_flag
	.def	is_compilation_flag;	.scl	2;	.type	32;	.endef
	.seh_proc	is_compilation_flag
is_compilation_flag:
	.seh_endprologue
 # src\compiler\flags\flags.c:80:     || flag == COMPILER_FLAG_DD_NON_ABSTRACT);
	leal	-5(%rcx), %eax	 #, tmp88
	cmpl	$5, %eax	 #, tmp88
	setbe	%al	 #, tmp90
 # src\compiler\flags\flags.c:79:     || flag == COMPILER_FLAG_D_OUT 
	cmpl	$1, %ecx	 #, flag
	sete	%dl	 #, tmp92
 # src\compiler\flags\flags.c:77:     return (lbool)
	orl	%edx, %eax	 # tmp92, tmp87
 # src\compiler\flags\flags.c:81: }
	ret	
	.seh_endproc
	.section .rdata,"dr"
.LC5:
	.ascii "version\0"
.LC6:
	.ascii "help\0"
.LC7:
	.ascii "license\0"
.LC8:
	.ascii "non-abstract\0"
	.align 32
flags_buffer:
	.quad	.LC0
	.quad	.LC1
	.quad	.LC5
	.quad	.LC6
	.quad	.LC7
	.quad	.LC8
	.ident	"GCC: (Rev6, Built by MSYS2 project) 13.2.0"
	.def	lssize;	.scl	2;	.type	32;	.endef
	.def	lslen;	.scl	2;	.type	32;	.endef
	.def	lssizen;	.scl	2;	.type	32;	.endef
	.def	lscmp;	.scl	2;	.type	32;	.endef
