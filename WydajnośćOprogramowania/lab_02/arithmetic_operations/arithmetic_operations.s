	.file	"arithmetic_operations.c"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC2:
	.string	"Result of arithmetic operations: %lf (x=%lf)\n"
	.align 8
.LC3:
	.string	"Wynik operacji arytmetycznych: %lf\n"
	.align 8
.LC4:
	.string	"Time for executing %d arithmetic operations:\n\t CPU - %lf, wallclock - %lf\n"
	.align 8
.LC5:
	.string	"Czas wykonania %d operacji arytmetycznych:\n\t CPU - %lf, zegar - %lf\n"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC7:
	.string	"Wydajno\305\233\304\207: %lf GFlops\n"
	.section	.rodata.str1.8
	.align 8
.LC8:
	.string	"Result of arithmetic operations: %lf\n"
	.align 8
.LC9:
	.string	"Time for executing %d arithmetic operations (with conditional branches):\n\t CPU - %lf, wallclock - %lf\n"
	.align 8
.LC10:
	.string	"Czas wykonania %d operacji arytmetycznych (ze skokami warunkowymi):\n\t CPU - %lf, zegar - %lf\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB20:
	.cfi_startproc
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	xorl	%eax, %eax
	call	time_CPU
	xorl	%eax, %eax
	movsd	%xmm0, (%rsp)
	call	time_clock
	movsd	%xmm0, 16(%rsp)
	movl	$5000000, %eax
	movsd	.LC0(%rip), %xmm0
	movsd	.LC1(%rip), %xmm1
	movapd	%xmm0, %xmm2
	.p2align 4,,10
	.p2align 3
.L3:
	mulsd	%xmm0, %xmm2
	subl	$1, %eax
	addsd	%xmm1, %xmm2
	jne	.L3
	xorl	%eax, %eax
	movsd	%xmm2, 24(%rsp)
	call	time_CPU
	movapd	%xmm0, %xmm5
	xorl	%eax, %eax
	subsd	(%rsp), %xmm5
	movsd	%xmm5, 8(%rsp)
	call	time_clock
	movapd	%xmm0, %xmm4
	movl	$10, %edi
	subsd	16(%rsp), %xmm4
	movsd	%xmm4, (%rsp)
	call	putchar
	movsd	24(%rsp), %xmm2
	movl	$.LC2, %edi
	xorpd	%xmm1, %xmm1
	movl	$2, %eax
	movapd	%xmm2, %xmm0
	movsd	%xmm2, 16(%rsp)
	call	printf
	movsd	16(%rsp), %xmm2
	movl	$.LC3, %edi
	movl	$1, %eax
	movapd	%xmm2, %xmm0
	call	printf
	movl	$10, %edi
	call	putchar
	movsd	(%rsp), %xmm1
	movl	$10000000, %esi
	movsd	8(%rsp), %xmm0
	movl	$.LC4, %edi
	movl	$2, %eax
	call	printf
	movsd	(%rsp), %xmm1
	movl	$10000000, %esi
	movsd	8(%rsp), %xmm0
	movl	$.LC5, %edi
	movl	$2, %eax
	call	printf
	movsd	.LC6(%rip), %xmm3
	movl	$.LC7, %edi
	movl	$1, %eax
	divsd	(%rsp), %xmm3
	movapd	%xmm3, %xmm0
	movsd	%xmm3, 24(%rsp)
	call	printf
	movl	$10, %edi
	call	putchar
	movl	$10, %edi
	call	putchar
	movsd	16(%rsp), %xmm2
	movl	$.LC8, %edi
	movl	$1, %eax
	movapd	%xmm2, %xmm0
	call	printf
	movsd	16(%rsp), %xmm2
	movl	$.LC3, %edi
	movl	$1, %eax
	movapd	%xmm2, %xmm0
	call	printf
	movl	$10, %edi
	call	putchar
	movsd	(%rsp), %xmm1
	movl	$10000000, %esi
	movsd	8(%rsp), %xmm0
	movl	$.LC9, %edi
	movl	$2, %eax
	call	printf
	movsd	(%rsp), %xmm1
	movl	$10000000, %esi
	movsd	8(%rsp), %xmm0
	movl	$.LC10, %edi
	movl	$2, %eax
	call	printf
	movsd	24(%rsp), %xmm3
	movl	$.LC7, %edi
	movl	$1, %eax
	movapd	%xmm3, %xmm0
	call	printf
	movl	$10, %edi
	addq	$40, %rsp
	.cfi_def_cfa_offset 8
	jmp	putchar
	.cfi_endproc
.LFE20:
	.size	main, .-main
	.globl	num_iter
	.section	.rodata
	.align 4
	.type	num_iter, @object
	.size	num_iter, 4
num_iter:
	.long	10000000
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	208632331
	.long	1072693249
	.align 8
.LC1:
	.long	2696277389
	.long	1051772663
	.align 8
.LC6:
	.long	1202590843
	.long	1065646817
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-44)"
	.section	.note.GNU-stack,"",@progbits
