	.file	"mat_mul_par_papi.c"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"wersja poprawna niezoptymalizowana"
	.text
	.p2align 4,,15
	.globl	mat_mul_par_papi
	.type	mat_mul_par_papi, @function
mat_mul_par_papi:
.LFB1094:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	.cfi_offset 15, -24
	movq	%rsi, %r15
	pushq	%r14
	.cfi_offset 14, -32
	movq	%rdx, %r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	%rdi, %rbx
	andq	$-32, %rsp
	subq	$80, %rsp
	movl	%ecx, 76(%rsp)
	movq	%rdx, 8(%rsp)
	call	omp_get_thread_num
	movl	$.LC0, %edi
	call	puts
	movl	76(%rsp), %ecx
	testl	%ecx, %ecx
	jle	.L26
	movslq	%ecx, %rax
	movq	%rbx, 24(%rsp)
	salq	$3, %rax
	movl	$0, 32(%rsp)
	movq	%rax, 64(%rsp)
	movl	%ecx, %eax
	shrl	$2, %eax
	movl	$0, 20(%rsp)
	movl	%eax, 44(%rsp)
	sall	$2, %eax
	leal	1(%rax), %ebx
	movl	%eax, 72(%rsp)
	movl	%eax, 36(%rsp)
	addl	$2, %eax
	movl	%ebx, 40(%rsp)
	movl	%eax, 76(%rsp)
	.p2align 4,,10
	.p2align 3
.L3:
	movq	64(%rsp), %rax
	movq	%r15, %rdx
	xorl	%r8d, %r8d
	movl	32(%rsp), %edi
	xorl	%r9d, %r9d
	movq	8(%rsp), %rbx
	addq	%r14, %rax
	movq	%rax, 56(%rsp)
	movl	36(%rsp), %eax
	addl	%edi, %eax
	cltq
	leaq	(%rbx,%rax,8), %r13
	movl	40(%rsp), %eax
	addl	%edi, %eax
	cltq
	leaq	(%rbx,%rax,8), %r12
	movl	76(%rsp), %eax
	addl	%edi, %eax
	leaq	32(%r14), %rdi
	cltq
	leaq	(%rbx,%rax,8), %rbx
	movq	%rdi, 48(%rsp)
	movq	24(%rsp), %rax
	jmp	.L16
	.p2align 4,,10
	.p2align 3
.L29:
	cmpl	$4, %ecx
	jbe	.L15
	movl	72(%rsp), %esi
	testl	%esi, %esi
	je	.L7
	xorl	%esi, %esi
	xorl	%edi, %edi
.L4:
	vmovupd	(%r14,%rsi), %ymm1
	addl	$1, %edi
	vmovupd	(%rdx,%rsi), %ymm2
	vbroadcastsd	(%rax), %ymm0
	vfmadd132pd	%ymm2, %ymm1, %ymm0
	vmovupd	%ymm0, (%r14,%rsi)
	addq	$32, %rsi
	cmpl	%edi, 44(%rsp)
	ja	.L4
	cmpl	%ecx, 72(%rsp)
	je	.L5
.L7:
	movl	36(%rsp), %edi
	vmovsd	(%rax), %xmm0
	vmovsd	0(%r13), %xmm5
	leal	(%rdi,%r8), %esi
	movl	40(%rsp), %edi
	movslq	%esi, %rsi
	vfmadd132sd	(%r15,%rsi,8), %xmm5, %xmm0
	vmovsd	%xmm0, 0(%r13)
	cmpl	%edi, %ecx
	jle	.L5
	cmpl	76(%rsp), %ecx
	leal	(%r8,%rdi), %esi
	vmovsd	(%rax), %xmm0
	movslq	%esi, %rsi
	vmovsd	(%r12), %xmm6
	vfmadd132sd	(%r15,%rsi,8), %xmm6, %xmm0
	vmovsd	%xmm0, (%r12)
	jle	.L5
	movl	76(%rsp), %edi
	vmovsd	(%rax), %xmm0
	vmovsd	(%rbx), %xmm4
	leal	(%r8,%rdi), %esi
	movslq	%esi, %rsi
	vfmadd132sd	(%r15,%rsi,8), %xmm4, %xmm0
	vmovsd	%xmm0, (%rbx)
.L5:
	addl	$1, %r9d
	addq	64(%rsp), %rdx
	addl	%ecx, %r8d
	cmpl	%ecx, %r9d
	je	.L12
	movq	%r10, %rax
.L16:
	leaq	32(%rdx), %rsi
	leaq	8(%rax), %r10
	cmpq	%rsi, %r14
	setnb	%dil
	cmpq	48(%rsp), %rdx
	setnb	%sil
	orl	%esi, %edi
	cmpq	%r10, %r14
	setnb	%sil
	cmpq	%rax, 56(%rsp)
	setbe	%r11b
	orl	%r11d, %esi
	testb	%sil, %dil
	jne	.L29
.L15:
	movq	%r14, %rdi
	xorl	%esi, %esi
	.p2align 4,,10
	.p2align 3
.L6:
	vmovsd	(%rdi), %xmm3
	addq	$8, %rdi
	vmovsd	(%rax), %xmm0
	vfmadd132sd	(%rdx,%rsi,8), %xmm3, %xmm0
	addq	$1, %rsi
	vmovsd	%xmm0, -8(%rdi)
	cmpl	%esi, %ecx
	jg	.L6
	jmp	.L5
	.p2align 4,,10
	.p2align 3
.L12:
	addl	$1, 20(%rsp)
	movq	64(%rsp), %rax
	addl	%ecx, 32(%rsp)
	addq	%rax, 24(%rsp)
	cmpl	%ecx, 20(%rsp)
	je	.L25
	movq	56(%rsp), %r14
	jmp	.L3
.L25:
	vzeroupper
.L26:
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
.LFE1094:
	.size	mat_mul_par_papi, .-mat_mul_par_papi
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-44)"
	.section	.note.GNU-stack,"",@progbits
