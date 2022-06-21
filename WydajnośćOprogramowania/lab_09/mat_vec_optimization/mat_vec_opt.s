# mark_description "Intel(R) C Intel(R) 64 Compiler Classic for applications running on Intel(R) 64, Version 2021.5.0 Build 2021";
# mark_description "1109_000000";
# mark_description "-S -O0 -no-vec -o mat_vec_opt.s";
	.file "mat_vec.c"
	.text
..TXTST0:
.L_2__routine_start_mat_vec_0:
# -- Begin  mat_vec
	.text
# mark_begin;

	.globl mat_vec
# --- mat_vec(double *, double *, double *, int)
mat_vec:
# parameter 1: %rdi
# parameter 2: %rsi
# parameter 3: %rdx
# parameter 4: %ecx
..B1.1:                         # Preds ..B1.0
                                # Execution count [0.00e+00]
	.cfi_startproc
..___tag_value_mat_vec.1:
..L2:
                                                          #7.1
        pushq     %rbp                                          #7.1
	.cfi_def_cfa_offset 16
        movq      %rsp, %rbp                                    #7.1
	.cfi_def_cfa 6, 16
	.cfi_offset 6, -16
        subq      $80, %rsp                                     #7.1
        movq      %rdi, -64(%rbp)                               #7.1
        movq      %rsi, -56(%rbp)                               #7.1
        movq      %rdx, -48(%rbp)                               #7.1
        movl      %ecx, -40(%rbp)                               #7.1
        movl      $0, -80(%rbp)                                 #11.7
                                # LOE rbx rbp rsp r12 r13 r14 r15 rip
..B1.2:                         # Preds ..B1.6 ..B1.1
                                # Execution count [0.00e+00]
        movl      -80(%rbp), %eax                               #11.11
        movl      -40(%rbp), %edx                               #11.13
        cmpl      %edx, %eax                                    #11.13
        jge       ..B1.7        # Prob 50%                      #11.13
                                # LOE rbx rbp rsp r12 r13 r14 r15 rip
..B1.3:                         # Preds ..B1.2
                                # Execution count [0.00e+00]
        pxor      %xmm0, %xmm0                                  #13.24
        movsd     %xmm0, -32(%rbp)                              #13.24
        pxor      %xmm0, %xmm0                                  #14.24
        movsd     %xmm0, -24(%rbp)                              #14.24
        movl      -80(%rbp), %eax                               #15.14
        imull     -40(%rbp), %eax                               #15.14
        movl      %eax, -76(%rbp)                               #15.11
        movl      $0, -72(%rbp)                                 #16.9
                                # LOE rbx rbp rsp r12 r13 r14 r15 rip
..B1.4:                         # Preds ..B1.5 ..B1.3
                                # Execution count [0.00e+00]
        movl      -72(%rbp), %eax                               #16.13
        movl      -40(%rbp), %edx                               #16.15
        cmpl      %edx, %eax                                    #16.15
        jge       ..B1.6        # Prob 50%                      #16.15
                                # LOE rbx rbp rsp r12 r13 r14 r15 rip
..B1.5:                         # Preds ..B1.4
                                # Execution count [0.00e+00]
        movl      -72(%rbp), %eax                               #17.12
        movslq    %eax, %rax                                    #17.10
        imulq     $8, %rax, %rax                                #17.10
        addq      -56(%rbp), %rax                               #17.10
        movsd     (%rax), %xmm0                                 #17.10
        movsd     %xmm0, -16(%rbp)                              #17.7
        movl      $1, %eax                                      #18.7
        addl      -72(%rbp), %eax                               #18.14
        movslq    %eax, %rax                                    #18.10
        imulq     $8, %rax, %rax                                #18.10
        addq      -56(%rbp), %rax                               #18.10
        movsd     (%rax), %xmm0                                 #18.10
        movsd     %xmm0, -8(%rbp)                               #18.7
        movl      -72(%rbp), %eax                               #20.18
        addl      -76(%rbp), %eax                               #20.18
        movslq    %eax, %rax                                    #20.13
        imulq     $8, %rax, %rax                                #20.13
        addq      -64(%rbp), %rax                               #20.13
        movsd     (%rax), %xmm0                                 #20.13
        movsd     -16(%rbp), %xmm1                              #20.21
        mulsd     %xmm1, %xmm0                                  #20.21
        movl      -72(%rbp), %eax                               #20.29
        addl      -76(%rbp), %eax                               #20.29
        incl      %eax                                          #20.31
        movslq    %eax, %rax                                    #20.24
        imulq     $8, %rax, %rax                                #20.24
        addq      -64(%rbp), %rax                               #20.24
        movsd     (%rax), %xmm1                                 #20.24
        movsd     -8(%rbp), %xmm2                               #20.34
        mulsd     %xmm2, %xmm1                                  #20.34
        addsd     %xmm1, %xmm0                                  #20.34
        movsd     -32(%rbp), %xmm1                              #20.7
        addsd     %xmm0, %xmm1                                  #20.7
        movsd     %xmm1, -32(%rbp)                              #20.7
        movl      $1, %eax                                      #21.7
        addl      -80(%rbp), %eax                               #21.20
        imull     -40(%rbp), %eax                               #21.23
        addl      -72(%rbp), %eax                               #21.25
        movslq    %eax, %rax                                    #21.15
        imulq     $8, %rax, %rax                                #21.15
        addq      -64(%rbp), %rax                               #21.15
        movsd     (%rax), %xmm0                                 #21.15
        movsd     -16(%rbp), %xmm1                              #21.28
        mulsd     %xmm1, %xmm0                                  #21.28
        movl      $1, %eax                                      #21.7
        addl      -80(%rbp), %eax                               #21.36
        imull     -40(%rbp), %eax                               #21.39
        addl      -72(%rbp), %eax                               #21.41
        incl      %eax                                          #21.43
        movslq    %eax, %rax                                    #21.31
        imulq     $8, %rax, %rax                                #21.31
        addq      -64(%rbp), %rax                               #21.31
        movsd     (%rax), %xmm1                                 #21.31
        movsd     -8(%rbp), %xmm2                               #21.46
        mulsd     %xmm2, %xmm1                                  #21.46
        addsd     %xmm1, %xmm0                                  #21.46
        movsd     -24(%rbp), %xmm1                              #21.7
        addsd     %xmm0, %xmm1                                  #21.7
        movsd     %xmm1, -24(%rbp)                              #21.7
        movl      $2, %eax                                      #16.17
        addl      -72(%rbp), %eax                               #16.17
        movl      %eax, -72(%rbp)                               #16.17
        jmp       ..B1.4        # Prob 100%                     #16.17
                                # LOE rbx rbp rsp r12 r13 r14 r15 rip
..B1.6:                         # Preds ..B1.4
                                # Execution count [0.00e+00]
        movl      -80(%rbp), %eax                               #23.7
        movslq    %eax, %rax                                    #23.5
        imulq     $8, %rax, %rax                                #23.5
        addq      -48(%rbp), %rax                               #23.5
        movsd     -32(%rbp), %xmm0                              #23.12
        movsd     %xmm0, (%rax)                                 #23.5
        movl      $1, %eax                                      #24.5
        addl      -80(%rbp), %eax                               #24.9
        movslq    %eax, %rax                                    #24.5
        imulq     $8, %rax, %rax                                #24.5
        addq      -48(%rbp), %rax                               #24.5
        movsd     -24(%rbp), %xmm0                              #24.12
        movsd     %xmm0, (%rax)                                 #24.5
        movl      $2, %eax                                      #11.15
        addl      -80(%rbp), %eax                               #11.15
        movl      %eax, -80(%rbp)                               #11.15
        jmp       ..B1.2        # Prob 100%                     #11.15
                                # LOE rbx rbp rsp r12 r13 r14 r15 rip
..B1.7:                         # Preds ..B1.2
                                # Execution count [0.00e+00]
        leave                                                   #27.1
	.cfi_restore 6
        ret                                                     #27.1
                                # LOE
	.cfi_endproc
# mark_end;
	.type	mat_vec,@function
	.size	mat_vec,.-mat_vec
..LNmat_vec.0:
	.data
# -- End  mat_vec
	.data
	.section .note.GNU-stack, ""
# End
