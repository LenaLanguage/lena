	.file	"lena.c"
 # GNU C17 (Rev6, Built by MSYS2 project) version 13.2.0 (x86_64-w64-mingw32)
 #	compiled by GNU C version 13.2.0, GMP version 6.3.0, MPFR version 4.2.1, MPC version 1.3.1, isl version isl-0.26-GMP

 # GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
 # options passed: -municode -m64 -mtune=generic -march=nocona -O3 -std=c17
	.text
	.section .rdata,"dr"
.LC0:
	.ascii "Output file: \0"
.LC1:
	.ascii " must be provided after \0"
.LC2:
	.ascii "-o \0"
.LC3:
	.ascii "flag.\12\12\0"
.LC4:
	.ascii "File: \0"
	.align 8
.LC5:
	.ascii " cannot be an output file format or a source code file.\12\12\0"
.LC6:
	.ascii "Too few flags to compile.\12\12\0"
	.align 8
.LC7:
	.ascii "Unrecognized flag, it will be useful for you to read:\12\12\0"
	.align 8
.LC8:
	.ascii "No flags provided. Please specify flags to compile your program.\12\0"
.LC9:
	.ascii "\12\0"
	.text
	.p2align 4
	.globl	compile
	.def	compile;	.scl	2;	.type	32;	.endef
	.seh_proc	compile
compile:
	pushq	%r15	 #
	.seh_pushreg	%r15
	pushq	%r14	 #
	.seh_pushreg	%r14
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
	subq	$88, %rsp	 #,
	.seh_stackalloc	88
	.seh_endprologue
 # src\lena.c:16: lm compile(lu32 argc, lc* argv[]) {
	movq	%rdx, %rsi	 # tmp144, argv
	movl	%ecx, %ebx	 # tmp143, argc
 # src\lena.c:17:     if (llibs_init() != L_OK) {
	call	llibs_init	 #
	movl	%eax, %edx	 #, tmp145
 # src\lena.c:18:         return L_EXIT_FAILURE;
	movl	$1, %eax	 #, <retval>
 # src\lena.c:17:     if (llibs_init() != L_OK) {
	testl	%edx, %edx	 # tmp145
	jne	.L1	 #,
 # src\lena.c:21:     if (argc > 1) {
	cmpl	$1, %ebx	 #, argc
	jbe	.L3	 #,
 # src\lena.c:23:         if (argc >= 4) {
	cmpl	$3, %ebx	 #, argc
	jbe	.L30	 #,
	leal	-2(%rbx), %eax	 #, tmp112
	leaq	8(%rsi), %r15	 #, ivtmp.8
 # src\lena.c:33:             lbool is_non_abstract = false;
	xorl	%r14d, %r14d	 # is_non_abstract
 # src\lena.c:31:             lu8 source_code_file_index = 0;
	xorl	%r12d, %r12d	 # source_code_file_index
	leaq	16(%rsi,%rax,8), %rbp	 #, _107
 # src\lena.c:28:             lbool is_target = false;
	xorl	%r13d, %r13d	 # is_target
 # src\lena.c:26:             lc* target = NULL;
	movq	$0, 56(%rsp)	 #, %sfp
 # src\lena.c:42:                     switch(flag) {
	leaq	.L8(%rip), %rdi	 #, tmp142
.L14:
 # src\lena.c:36:                 flag = flags_recognize(argv[i]);
	movq	(%r15), %rcx	 # MEM[(lc * *)_4], MEM[(lc * *)_4]
 # src\lena.c:36:                 flag = flags_recognize(argv[i]);
	movq	%r15, %rsi	 # ivtmp.8, _4
 # src\lena.c:36:                 flag = flags_recognize(argv[i]);
	call	flags_recognize	 #
	movl	%eax, %ebx	 # tmp146,
 # src\lena.c:37:                 if (!is_compilation_flag(flag)) {
	movl	%ebx, %ecx	 # flag,
	call	is_compilation_flag	 #
 # src\lena.c:37:                 if (!is_compilation_flag(flag)) {
	testb	%al, %al	 # _6
	je	.L5	 #,
 # src\lena.c:42:                     switch(flag) {
	cmpl	$10, %ebx	 #, flag
	ja	.L5	 #,
	movslq	(%rdi,%rbx,4), %rdx	 #, tmp119
	addq	%rdi, %rdx	 # tmp142, tmp120
	jmp	*%rdx	 # tmp120
	.section .rdata,"dr"
	.align 4
.L8:
	.long	.L5-.L8
	.long	.L12-.L8
	.long	.L5-.L8
	.long	.L5-.L8
	.long	.L5-.L8
	.long	.L24-.L8
	.long	.L9-.L8
	.long	.L9-.L8
	.long	.L10-.L8
	.long	.L9-.L8
	.long	.L7-.L8
	.text
	.p2align 4,,10
	.p2align 3
.L3:
 # src\lena.c:154:         greeting();
	call	greeting	 #
 # src\lena.c:155:         lcout(X("No flags provided. Please specify flags to compile your program.\n"));
	leaq	.LC8(%rip), %rcx	 #, tmp139
	call	lcout	 #
.L15:
 # src\lena.c:159:     lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\lena.c:160:     lcout(X("\n"));
	leaq	.LC9(%rip), %rcx	 #, tmp140
	call	lcout	 #
 # src\lena.c:161:     return L_EXIT_SUCCESS;
	xorl	%eax, %eax	 # <retval>
.L1:
 # src\lena.c:162: }
	addq	$88, %rsp	 #,
	popq	%rbx	 #
	popq	%rsi	 #
	popq	%rdi	 #
	popq	%rbp	 #
	popq	%r12	 #
	popq	%r13	 #
	popq	%r14	 #
	popq	%r15	 #
	ret	
	.p2align 4,,10
	.p2align 3
.L9:
 # src\lena.c:53:                         if (is_target) {
	testb	%r13b, %r13b	 # is_target
	je	.L13	 #,
 # src\lena.c:54:                             target = argv[i];
	movq	(%r15), %rax	 # MEM[(lc * *)_4], target
	movq	%rax, 56(%rsp)	 # target, %sfp
	jmp	.L11	 #
	.p2align 4,,10
	.p2align 3
.L30:
 # src\lena.c:36:                 flag = flags_recognize(argv[i]);
	addq	$8, %rsi	 #, _4
.L5:
 # src\lena.c:115:             compiler_flag_t flag = flags_recognize(argv[file_index]);
	movq	(%rsi), %rcx	 # *prephitmp_32, *prephitmp_32
	call	flags_recognize	 #
 # src\lena.c:116:             if (is_compilation_flag(flag)) {
	movl	%eax, %ecx	 # flag,
 # src\lena.c:115:             compiler_flag_t flag = flags_recognize(argv[file_index]);
	movl	%eax, %ebx	 # tmp148, flag
 # src\lena.c:116:             if (is_compilation_flag(flag)) {
	call	is_compilation_flag	 #
 # src\lena.c:116:             if (is_compilation_flag(flag)) {
	testb	%al, %al	 # tmp149
	jne	.L31	 #,
 # src\lena.c:123:                 switch (flag) {
	cmpl	$3, %ebx	 #, flag
	je	.L17	 #,
	ja	.L18	 #,
	testl	%ebx, %ebx	 # flag
	je	.L19	 #,
	cmpl	$2, %ebx	 #, flag
	jne	.L21	 #,
 # src\lena.c:126:                     version();
	call	version	 #
 # src\lena.c:127:                     break;
	jmp	.L15	 #
	.p2align 4,,10
	.p2align 3
.L7:
 # src\lena.c:87:                         greeting();
	call	greeting	 #
 # src\lena.c:88:                         lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\lena.c:89:                         lcout(X("File: "));
	leaq	.LC4(%rip), %rcx	 #, tmp130
	call	lcout	 #
 # src\lena.c:90:                         lccol(LC_COLOR_CYAN, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$14, %ecx	 #,
	call	lccol	 #
 # src\lena.c:91:                         lcout(argv[i]);
	movq	(%r15), %rcx	 # MEM[(lc * *)_4], MEM[(lc * *)_4]
	call	lcout	 #
 # src\lena.c:92:                         lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\lena.c:93:                         lcout(X(" cannot be an output file format or a source code file.\n\n"));
	leaq	.LC5(%rip), %rcx	 #, tmp132
	call	lcout	 #
 # src\lena.c:95:                         help_formats();
	call	help_formats	 #
.L11:
 # src\lena.c:35:             for (lu32 i = 1; i < argc; ++i) {
	addq	$8, %r15	 #, ivtmp.8
	cmpq	%rbp, %r15	 # _107, ivtmp.8
	jne	.L14	 #,
 # src\lena.c:104:             compile_files  (
	movl	$0, 32(%rsp)	 #,
	movq	56(%rsp), %r9	 # %sfp,
	leaq	72(%rsp), %rdx	 #, tmp134
	movzbl	%r12b, %ecx	 # source_code_file_index, source_code_file_index
	movq	$0, 40(%rsp)	 #,
	movzbl	%r14b, %r8d	 # is_non_abstract,
	call	compile_files	 #
	jmp	.L15	 #
	.p2align 4,,10
	.p2align 3
.L10:
 # src\lena.c:75:                         source_code_files[source_code_file_index] = argv[i];
	movq	(%r15), %rdx	 # MEM[(lc * *)_4], MEM[(lc * *)_4]
	movzbl	%r12b, %eax	 # source_code_file_index, source_code_file_index
 # src\lena.c:76:                         ++source_code_file_index;
	addl	$1, %r12d	 #, source_code_file_index
 # src\lena.c:75:                         source_code_files[source_code_file_index] = argv[i];
	movq	%rdx, 72(%rsp,%rax,8)	 # MEM[(lc * *)_4], source_code_files[_11]
 # src\lena.c:77:                         break;
	jmp	.L11	 #
	.p2align 4,,10
	.p2align 3
.L24:
 # src\lena.c:42:                     switch(flag) {
	movl	%eax, %r14d	 # _6, is_non_abstract
	jmp	.L11	 #
	.p2align 4,,10
	.p2align 3
.L12:
 # src\lena.c:45:                         is_target = true;
	movl	%eax, %r13d	 # _6, is_target
	jmp	.L11	 #
	.p2align 4,,10
	.p2align 3
.L18:
 # src\lena.c:123:                 switch (flag) {
	cmpl	$4, %ebx	 #, flag
	jne	.L21	 #,
 # src\lena.c:141:                     license();
	call	license	 #
 # src\lena.c:142:                     break;
	jmp	.L15	 #
	.p2align 4,,10
	.p2align 3
.L13:
 # src\lena.c:57:                             greeting();
	call	greeting	 #
 # src\lena.c:58:                             lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\lena.c:59:                             lcout(X("Output file: "));
	leaq	.LC0(%rip), %rcx	 #, tmp122
	call	lcout	 #
 # src\lena.c:60:                             lccol(LC_COLOR_CYAN, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$14, %ecx	 #,
	call	lccol	 #
 # src\lena.c:61:                             lcout(argv[i]);
	movq	(%r15), %rcx	 # MEM[(lc * *)_4], MEM[(lc * *)_4]
	call	lcout	 #
 # src\lena.c:62:                             lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\lena.c:63:                             lcout(X(" must be provided after "));
	leaq	.LC1(%rip), %rcx	 #, tmp124
	call	lcout	 #
 # src\lena.c:64:                             lccol(LC_COLOR_GREEN, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$4, %ecx	 #,
	call	lccol	 #
 # src\lena.c:65:                             lcout(X("-o "));
	leaq	.LC2(%rip), %rcx	 #, tmp125
	call	lcout	 #
 # src\lena.c:66:                             lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
	xorl	%edx, %edx	 #
	movl	$1, %ecx	 #,
	call	lccol	 #
 # src\lena.c:67:                             lcout(X("flag.\n\n"));
	leaq	.LC3(%rip), %rcx	 #, tmp126
	call	lcout	 #
 # src\lena.c:69:                             help_formats();
	call	help_formats	 #
	jmp	.L11	 #
	.p2align 4,,10
	.p2align 3
.L31:
 # src\lena.c:118:                 greeting();
	call	greeting	 #
 # src\lena.c:119:                 lcout(X("Too few flags to compile.\n\n"));
	leaq	.LC6(%rip), %rcx	 #, tmp137
	call	lcout	 #
 # src\lena.c:120:                 help_usage();
	call	help_usage	 #
	jmp	.L15	 #
	.p2align 4,,10
	.p2align 3
.L17:
 # src\lena.c:136:                     help();
	call	help	 #
 # src\lena.c:137:                     break;
	jmp	.L15	 #
	.p2align 4,,10
	.p2align 3
.L21:
 # src\lena.c:146:                     greeting();
	call	greeting	 #
 # src\lena.c:147:                     lcout(X("Unrecognized flag, it will be useful for you to read:\n\n"));
	leaq	.LC7(%rip), %rcx	 #, tmp138
	call	lcout	 #
 # src\lena.c:148:                     help_flags();
	call	help_flags	 #
 # src\lena.c:149:                     break;
	jmp	.L15	 #
	.p2align 4,,10
	.p2align 3
.L19:
 # src\lena.c:131:                     version_extented();
	call	version_extented	 #
 # src\lena.c:132:                     break;
	jmp	.L15	 #
	.seh_endproc
	.ident	"GCC: (Rev6, Built by MSYS2 project) 13.2.0"
	.def	llibs_init;	.scl	2;	.type	32;	.endef
	.def	flags_recognize;	.scl	2;	.type	32;	.endef
	.def	is_compilation_flag;	.scl	2;	.type	32;	.endef
	.def	greeting;	.scl	2;	.type	32;	.endef
	.def	lcout;	.scl	2;	.type	32;	.endef
	.def	lccol;	.scl	2;	.type	32;	.endef
	.def	version;	.scl	2;	.type	32;	.endef
	.def	help_formats;	.scl	2;	.type	32;	.endef
	.def	compile_files;	.scl	2;	.type	32;	.endef
	.def	license;	.scl	2;	.type	32;	.endef
	.def	help_usage;	.scl	2;	.type	32;	.endef
	.def	help;	.scl	2;	.type	32;	.endef
	.def	help_flags;	.scl	2;	.type	32;	.endef
	.def	version_extented;	.scl	2;	.type	32;	.endef
