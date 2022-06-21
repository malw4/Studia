	.file	"mat_mul_par_papi.c"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"wersja cache blocking+wektoryzacja (4x4x4)"
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
	movl	%ecx, %r15d
	pushq	%r14
	.cfi_offset 14, -32
	movq	%rsi, %r14
	pushq	%r13
	pushq	%r12
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	movq	%rdx, %r12
	pushq	%rbx
	.cfi_offset 3, -56
	movq	%rdi, %rbx
	andq	$-32, %rsp
	subq	$448, %rsp
	movq	%rsi, 24(%rsp)
	movl	%ecx, 108(%rsp)
	call	omp_get_thread_num
	movl	$.LC0, %edi
	call	puts
	testl	%r15d, %r15d
	jle	.L15
	movl	%r15d, %eax
	movl	$108, %edx
	movl	$0, 152(%rsp)
	movq	$0, 120(%rsp)
	imull	%edx, %eax
	cltq
	movq	%rax, 72(%rsp)
	salq	$3, %rax
	movq	%rax, 80(%rsp)
	movq	%r12, %rax
	subq	%r14, %rax
	movq	%rax, 112(%rsp)
	movl	%r15d, %eax
	sall	$2, %eax
	cltq
	movq	%rax, 144(%rsp)
	salq	$3, %rax
	movq	%rax, 328(%rsp)
	movl	%r15d, %eax
	addl	%eax, %eax
	movslq	%eax, %r10
	movq	%r14, %rax
	addq	%rbx, %rax
	movq	%rax, 48(%rsp)
	movslq	%r15d, %rax
	subq	%r12, 48(%rsp)
	movq	%rax, 56(%rsp)
	movl	152(%rsp), %eax
.L3:
	addl	$107, %eax
	movq	24(%rsp), %rdi
	movl	%eax, 156(%rsp)
	movq	120(%rsp), %rax
	movl	$0, 220(%rsp)
	movq	%rdi, 64(%rsp)
	addq	%r10, %rax
	movq	%rax, 32(%rsp)
	addq	56(%rsp), %rax
	movq	%rax, 40(%rsp)
	subq	%r10, %rax
	movq	%rax, 16(%rsp)
	movq	48(%rsp), %rax
	addq	112(%rsp), %rax
	movq	%rax, 8(%rsp)
	movl	220(%rsp), %eax
.L13:
	addl	$107, %eax
	movq	112(%rsp), %rdi
	movl	$0, 208(%rsp)
	movl	%eax, 348(%rsp)
	movq	64(%rsp), %rax
	movq	$0, 96(%rsp)
	movq	$0, 88(%rsp)
	movq	%rax, 160(%rsp)
	addq	%rdi, %rax
	movq	%rax, 136(%rsp)
	movl	208(%rsp), %eax
.L12:
	movq	40(%rsp), %rcx
	addl	$107, %eax
	movq	%r10, %r8
	movq	88(%rsp), %rdi
	movl	%eax, 216(%rsp)
	movq	$0, 200(%rsp)
	movq	%rcx, 176(%rsp)
	movq	32(%rsp), %rcx
	movq	%rdi, %rax
	addq	%r10, %rax
	addq	56(%rsp), %rax
	movq	%rcx, 192(%rsp)
	movq	120(%rsp), %rcx
	movq	%rax, %rbx
	subq	%r10, %rax
	movq	%rcx, 184(%rsp)
	movq	16(%rsp), %rcx
	movq	%rax, %r11
	subq	%rdi, %r11
	subq	%rdi, %rbx
	movq	%rbx, %rdi
	movq	%r11, %r9
	movq	%rcx, 168(%rsp)
	movl	152(%rsp), %ecx
	movl	%ecx, 212(%rsp)
	movq	8(%rsp), %rcx
	subq	96(%rsp), %rcx
	movq	%rcx, 128(%rsp)
.L10:
	movq	168(%rsp), %rax
	movq	184(%rsp), %rbx
	movq	192(%rsp), %r15
	movq	176(%rsp), %r11
	movq	%rax, %rdx
	subq	%rbx, %rdx
	leaq	0(,%rdx,8), %rcx
	movq	%rcx, 320(%rsp)
	movq	%r15, %rcx
	movq	160(%rsp), %r15
	leaq	8(,%rdx,8), %rax
	subq	%rbx, %rcx
	leaq	0(,%rcx,8), %rsi
	movq	%rax, 296(%rsp)
	movq	%rcx, %r10
	movq	%rsi, 312(%rsp)
	movq	%r11, %rsi
	movq	%rdx, %r11
	subq	%rbx, %rsi
	movq	128(%rsp), %rbx
	movq	%r15, 336(%rsp)
	leaq	8(,%rcx,8), %rax
	movq	%rax, 232(%rsp)
	leaq	8(,%rsi,8), %rax
	movq	%rax, 240(%rsp)
	leaq	16(,%rdx,8), %rax
	leaq	0(,%rsi,8), %r14
	movq	%rax, 248(%rsp)
	leaq	16(,%rcx,8), %rax
	movq	%r14, 304(%rsp)
	movl	208(%rsp), %r14d
	movq	%rax, 256(%rsp)
	leaq	16(,%rsi,8), %rax
	movq	%rax, 264(%rsp)
	leaq	24(,%rdx,8), %rax
	movq	%rax, 272(%rsp)
	leaq	24(,%rcx,8), %rax
	movq	%rax, 280(%rsp)
	leaq	24(,%rsi,8), %rax
	movq	%rax, 288(%rsp)
	movq	200(%rsp), %rax
	movl	%r14d, 344(%rsp)
	movq	136(%rsp), %r14
	addq	%rax, %rbx
	addq	%rax, %r14
	movq	%r14, 224(%rsp)
	.p2align 4,,10
	.p2align 3
.L8:
	movq	320(%rsp), %rax
	leaq	24(%rbx), %r15
	movq	336(%rsp), %rdx
	movl	220(%rsp), %ecx
	addq	%rbx, %rax
	movq	%rax, 440(%rsp)
	movq	312(%rsp), %rax
	addq	%rbx, %rax
	movq	%rax, 432(%rsp)
	movq	304(%rsp), %rax
	addq	%rbx, %rax
	movq	%rax, 424(%rsp)
	leaq	8(%rbx), %rax
	movq	%rax, 416(%rsp)
	movq	296(%rsp), %rax
	addq	%rbx, %rax
	movq	%rax, 408(%rsp)
	movq	232(%rsp), %rax
	addq	%rbx, %rax
	movq	%rax, 360(%rsp)
	movq	240(%rsp), %rax
	addq	%rbx, %rax
	movq	%rax, 368(%rsp)
	leaq	16(%rbx), %rax
	movq	%rax, 376(%rsp)
	movq	248(%rsp), %rax
	addq	%rbx, %rax
	movq	%rax, 384(%rsp)
	movq	256(%rsp), %rax
	addq	%rbx, %rax
	movq	%rax, 392(%rsp)
	movq	264(%rsp), %rax
	addq	%rbx, %rax
	movq	%rax, 400(%rsp)
	movq	272(%rsp), %rax
	leaq	(%rbx,%rax), %r14
	movq	280(%rsp), %rax
	leaq	(%rbx,%rax), %r13
	movq	288(%rsp), %rax
	leaq	(%rbx,%rax), %r12
	movq	224(%rsp), %rax
	movq	%r12, 352(%rsp)
	.p2align 4,,10
	.p2align 3
.L6:
	movq	440(%rsp), %r12
	addl	$4, %ecx
	vmovapd	(%rdx), %ymm0
	vbroadcastsd	(%rbx), %ymm8
	vbroadcastsd	(%r12), %ymm7
	vfmadd213pd	(%rax), %ymm0, %ymm8
	movq	432(%rsp), %r12
	vfmadd213pd	(%rax,%r11,8), %ymm0, %ymm7
	vbroadcastsd	(%r12), %ymm6
	movq	424(%rsp), %r12
	vfmadd213pd	(%rax,%r10,8), %ymm0, %ymm6
	vbroadcastsd	(%r12), %ymm5
	movq	416(%rsp), %r12
	vfmadd213pd	(%rax,%rsi,8), %ymm0, %ymm5
	vmovapd	(%rdx,%r9,8), %ymm0
	vbroadcastsd	(%r12), %ymm4
	movq	408(%rsp), %r12
	vfmadd132pd	%ymm0, %ymm8, %ymm4
	vbroadcastsd	(%r12), %ymm3
	movq	360(%rsp), %r12
	vfmadd132pd	%ymm0, %ymm7, %ymm3
	vbroadcastsd	(%r12), %ymm2
	movq	368(%rsp), %r12
	vfmadd132pd	%ymm0, %ymm6, %ymm2
	vbroadcastsd	(%r12), %ymm1
	movq	376(%rsp), %r12
	vfmadd132pd	%ymm0, %ymm5, %ymm1
	vmovapd	(%rdx,%r8,8), %ymm0
	vbroadcastsd	(%r12), %ymm8
	movq	384(%rsp), %r12
	vfmadd132pd	%ymm0, %ymm4, %ymm8
	vbroadcastsd	(%r15), %ymm4
	vbroadcastsd	(%r12), %ymm7
	movq	392(%rsp), %r12
	vfmadd132pd	%ymm0, %ymm3, %ymm7
	vbroadcastsd	(%r14), %ymm3
	vbroadcastsd	(%r12), %ymm6
	movq	400(%rsp), %r12
	vfmadd132pd	%ymm0, %ymm2, %ymm6
	vbroadcastsd	0(%r13), %ymm2
	vbroadcastsd	(%r12), %ymm5
	movq	352(%rsp), %r12
	vfmadd132pd	%ymm0, %ymm1, %ymm5
	vmovapd	(%rdx,%rdi,8), %ymm0
	addq	$32, %rdx
	vfmadd132pd	%ymm0, %ymm8, %ymm4
	vfmadd132pd	%ymm0, %ymm7, %ymm3
	vfmadd132pd	%ymm0, %ymm6, %ymm2
	vbroadcastsd	(%r12), %ymm1
	vmovapd	%ymm4, (%rax)
	vmovapd	%ymm3, (%rax,%r11,8)
	vfmadd132pd	%ymm0, %ymm5, %ymm1
	vmovapd	%ymm2, (%rax,%r10,8)
	vmovapd	%ymm1, (%rax,%rsi,8)
	addq	$32, %rax
	cmpl	348(%rsp), %ecx
	jle	.L6
	movq	328(%rsp), %rax
	addq	$32, %rbx
	addl	$4, 344(%rsp)
	addq	%rax, 336(%rsp)
	movl	216(%rsp), %eax
	cmpl	%eax, 344(%rsp)
	jle	.L8
	movq	328(%rsp), %rax
	addl	$4, 212(%rsp)
	addq	%rax, 200(%rsp)
	movq	144(%rsp), %rax
	addq	%rax, 168(%rsp)
	addq	%rax, 184(%rsp)
	addq	%rax, 192(%rsp)
	addq	%rax, 176(%rsp)
	movl	156(%rsp), %eax
	cmpl	%eax, 212(%rsp)
	jle	.L10
	movq	72(%rsp), %rax
	movq	%r8, %r10
	addl	$108, 208(%rsp)
	subq	$864, 96(%rsp)
	addq	%rax, 88(%rsp)
	movq	80(%rsp), %rax
	addq	%rax, 160(%rsp)
	movl	208(%rsp), %eax
	cmpl	%eax, 108(%rsp)
	jg	.L12
	addl	$108, 220(%rsp)
	addq	$864, 64(%rsp)
	movl	220(%rsp), %eax
	cmpl	%eax, 108(%rsp)
	jg	.L13
	movq	80(%rsp), %rax
	addl	$108, 152(%rsp)
	addq	%rax, 112(%rsp)
	movq	72(%rsp), %rax
	addq	%rax, 120(%rsp)
	movl	152(%rsp), %eax
	cmpl	%eax, 108(%rsp)
	jg	.L3
	vzeroupper
.L15:
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
