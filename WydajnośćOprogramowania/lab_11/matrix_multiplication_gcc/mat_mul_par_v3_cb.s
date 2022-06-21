	.file	"mat_mul_par_papi.c"
	.text
	.p2align 4,,15
	.type	mat_mul_par_papi._omp_fn.0, @function
mat_mul_par_papi._omp_fn.0:
.LFB1095:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	movq	%rdi, %r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	andq	$-32, %rsp
	subq	$96, %rsp
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movl	24(%rdi), %r15d
	call	omp_get_num_threads
	movl	%eax, %ebx
	call	omp_get_thread_num
	movl	$1272582903, %edx
	leal	107(%r15), %ecx
	movl	%eax, %esi
	movl	%ecx, %eax
	sarl	$31, %ecx
	imull	%edx
	sarl	$5, %edx
	subl	%ecx, %edx
	movl	%edx, %eax
	cltd
	idivl	%ebx
	cmpl	%edx, %esi
	jge	.L23
	addl	$1, %eax
	xorl	%edx, %edx
.L23:
	imull	%eax, %esi
	addl	%esi, %edx
	leal	(%rdx,%rax), %ecx
	cmpl	%ecx, %edx
	jge	.L38
	movl	%edx, %eax
	movl	$108, %edx
	movl	$108, %esi
	imull	%edx, %eax
	movq	%r14, %r13
	movl	%eax, %edx
	movl	%eax, 76(%rsp)
	movl	%ecx, %eax
	movl	$108, %ecx
	imull	%r15d, %edx
	imull	%ecx, %eax
	movslq	%edx, %rdx
	movl	%eax, 52(%rsp)
	movl	%r15d, %eax
	imull	%esi, %eax
	cltq
	leaq	0(,%rax,8), %rbx
	leaq	864(,%rax,8), %rax
	movq	%rbx, 32(%rsp)
	movq	%rax, 40(%rsp)
	leaq	0(,%rdx,8), %rbx
	movslq	%r15d, %rax
	leaq	0(,%rax,8), %r12
	movq	%rbx, 56(%rsp)
	movq	%r12, %r14
.L6:
	testl	%r15d, %r15d
	jle	.L4
	movq	16(%r13), %rax
	movl	$0, 72(%rsp)
	movq	56(%rsp), %rbx
	movq	%r13, 8(%rsp)
	movq	0(%r13), %rdx
	leaq	864(%rbx,%rax), %rbx
	movq	%rbx, 88(%rsp)
	movq	%rax, %rbx
	addq	8(%r13), %rbx
	movq	%rbx, 80(%rsp)
	subq	%rdx, 80(%rsp)
	subq	%rax, %rdx
	movq	%rdx, 64(%rsp)
.L8:
	movq	88(%rsp), %rax
	xorl	%r13d, %r13d
	movq	64(%rsp), %r12
	subq	$864, %rax
	movq	%rax, 24(%rsp)
.L5:
	movq	24(%rsp), %rax
	movl	$108, 48(%rsp)
	movq	88(%rsp), %r10
	leaq	(%rax,%r12), %rdx
	movq	80(%rsp), %rax
	addq	%r12, %rax
	movq	%rax, 16(%rsp)
.L7:
	movq	16(%rsp), %rcx
	leaq	-864(%r10), %rsi
	leaq	(%r12,%r10), %r8
	leaq	32(%rdx), %r9
	.p2align 4,,10
	.p2align 3
.L9:
	leaq	8(%rsi), %rdi
	cmpq	%rdi, %rdx
	setnb	%r11b
	cmpq	%r8, %rsi
	setnb	%al
	orb	%al, %r11b
	je	.L14
	leaq	32(%rcx), %rax
	cmpq	%rax, %rdx
	setnb	%bl
	cmpq	%r9, %rcx
	setnb	%r11b
	xorl	%eax, %eax
	orb	%r11b, %bl
	je	.L14
	.p2align 4,,10
	.p2align 3
.L28:
	vmovupd	(%rdx,%rax), %ymm1
	vmovupd	(%rcx,%rax), %ymm2
	vbroadcastsd	(%rsi), %ymm0
	vfmadd132pd	%ymm2, %ymm1, %ymm0
	vmovupd	%ymm0, (%rdx,%rax)
	addq	$32, %rax
	cmpq	$864, %rax
	jne	.L28
	addq	%r14, %rcx
	cmpq	%r10, %rdi
	je	.L41
.L17:
	movq	%rdi, %rsi
	jmp	.L9
	.p2align 4,,10
	.p2align 3
.L14:
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L21:
	vmovsd	(%rdx,%rax), %xmm3
	vmovsd	(%rsi), %xmm0
	vfmadd132sd	(%rcx,%rax), %xmm3, %xmm0
	vmovsd	%xmm0, (%rdx,%rax)
	addq	$8, %rax
	cmpq	$864, %rax
	jne	.L21
	addq	%r14, %rcx
	cmpq	%r10, %rdi
	jne	.L17
.L41:
	leaq	(%rdi,%r14), %r10
	addq	%r14, %rdx
	subl	$1, 48(%rsp)
	jne	.L7
	addl	$108, %r13d
	addq	$864, %r12
	cmpl	%r13d, %r15d
	jg	.L5
	addl	$108, 72(%rsp)
	movq	40(%rsp), %rax
	addq	$864, 88(%rsp)
	subq	$864, 64(%rsp)
	addq	%rax, 80(%rsp)
	cmpl	72(%rsp), %r15d
	jg	.L8
	movq	8(%rsp), %r13
.L4:
	addl	$108, 76(%rsp)
	movq	32(%rsp), %rax
	addq	%rax, 56(%rsp)
	movl	76(%rsp), %eax
	cmpl	%eax, 52(%rsp)
	jg	.L6
	vzeroupper
.L38:
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1095:
	.size	mat_mul_par_papi._omp_fn.0, .-mat_mul_par_papi._omp_fn.0
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"wersja cache blocking"
	.text
	.p2align 4,,15
	.globl	mat_mul_par_papi
	.type	mat_mul_par_papi, @function
mat_mul_par_papi:
.LFB1094:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movl	%ecx, %r13d
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	movq	%rsi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rdi, %rbx
	subq	$40, %rsp
	.cfi_def_cfa_offset 80
	call	omp_get_thread_num
	movl	$.LC0, %edi
	call	puts
	movq	%rsp, %rsi
	xorl	%edx, %edx
	movl	$mat_mul_par_papi._omp_fn.0, %edi
	movq	%r12, (%rsp)
	movq	%rbp, 8(%rsp)
	movq	%rbx, 16(%rsp)
	movl	%r13d, 24(%rsp)
	call	GOMP_parallel_start
	movq	%rsp, %rdi
	call	mat_mul_par_papi._omp_fn.0
	call	GOMP_parallel_end
	addq	$40, %rsp
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE1094:
	.size	mat_mul_par_papi, .-mat_mul_par_papi
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-44)"
	.section	.note.GNU-stack,"",@progbits
