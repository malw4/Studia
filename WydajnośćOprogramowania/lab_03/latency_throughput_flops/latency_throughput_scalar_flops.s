# mark_description "Intel(R) C Intel(R) 64 Compiler Classic for applications running on Intel(R) 64, Version 2021.5.0 Build 2021";
# mark_description "1109_000000";
# mark_description "-I../utd_time_unix -O3 -S";
	.file "latency_throughput_scalar_flops.c"
	.text
..TXTST0:
.L_2__routine_start_main_0:
# -- Begin  main
	.text
# mark_begin;
       .align    16,0x90
	.globl main
# --- main(void)
main:
..B1.1:                         # Preds ..B1.0
                                # Execution count [0.00e+00]
	.cfi_startproc
..___tag_value_main.1:
..L2:
                                                          #9.18
        pushq     %rbp                                          #9.18
	.cfi_def_cfa_offset 16
        movq      %rsp, %rbp                                    #9.18
	.cfi_def_cfa 6, 16
	.cfi_offset 6, -16
        andq      $-128, %rsp                                   #9.18
        pushq     %r12                                          #9.18
        subq      $120, %rsp                                    #9.18
        movl      $3, %edi                                      #9.18
        xorl      %esi, %esi                                    #9.18
        call      __intel_new_feature_proc_init                 #9.18
	.cfi_escape 0x10, 0x0c, 0x0e, 0x38, 0x1c, 0x0d, 0x80, 0xff, 0xff, 0xff, 0x1a, 0x0d, 0xf8, 0xff, 0xff, 0xff, 0x22
                                # LOE rbx r13 r14 r15
..B1.20:                        # Preds ..B1.1
                                # Execution count [0.00e+00]
        stmxcsr   (%rsp)                                        #9.18
        xorl      %eax, %eax                                    #38.7
        movsd     .L_2il0floatpacket.1(%rip), %xmm1             #19.7
        xorl      %r12d, %r12d                                  #38.7
        movsd     .L_2il0floatpacket.2(%rip), %xmm2             #20.7
        orl       $32832, (%rsp)                                #9.18
        movsd     .L_2il0floatpacket.3(%rip), %xmm3             #21.7
        movsd     %xmm1, 24(%rsp)                               #19.7[spill]
        movsd     %xmm2, 16(%rsp)                               #20.7[spill]
        ldmxcsr   (%rsp)                                        #9.18
        movsd     .L_2il0floatpacket.0(%rip), %xmm0             #18.7
        movsd     %xmm3, 8(%rsp)                                #21.7[spill]
        movsd     .L_2il0floatpacket.5(%rip), %xmm1             #38.7
        movsd     .L_2il0floatpacket.4(%rip), %xmm2             #38.7
                                # LOE rbx r13 r14 r15 eax r12d xmm0 xmm1 xmm2
..B1.2:                         # Preds ..B1.2 ..B1.20
                                # Execution count [1.00e+06]
        mulsd     %xmm1, %xmm0                                  #39.20
        incl      %eax                                          #38.25
        addsd     %xmm2, %xmm0                                  #39.22
        cmpl      $1000000000, %eax                             #38.13
        jl        ..B1.2        # Prob 100%                     #38.13
                                # LOE rbx r13 r14 r15 eax r12d xmm0 xmm1 xmm2
..B1.3:                         # Preds ..B1.2
                                # Execution count [0.00e+00]
        movsd     .L_2il0floatpacket.6(%rip), %xmm1             #41.8
        xorl      %eax, %eax                                    #45.14
        mulsd     %xmm0, %xmm1                                  #41.3
        movsd     %xmm1, 48(%rsp)                               #41.3[spill]
..___tag_value_main.10:
#       time_CPU()
        call      time_CPU                                      #45.14
..___tag_value_main.11:
                                # LOE rbx r13 r14 r15 r12d xmm0
..B1.21:                        # Preds ..B1.3
                                # Execution count [0.00e+00]
        movsd     %xmm0, 40(%rsp)                               #45.14[spill]
                                # LOE rbx r13 r14 r15 r12d
..B1.4:                         # Preds ..B1.21
                                # Execution count [0.00e+00]
        xorl      %eax, %eax                                    #46.20
..___tag_value_main.14:
#       time_clock()
        call      time_clock                                    #46.20
..___tag_value_main.15:
                                # LOE rbx r13 r14 r15 r12d xmm0
..B1.22:                        # Preds ..B1.4
                                # Execution count [0.00e+00]
        movsd     %xmm0, 32(%rsp)                               #46.20[spill]
                                # LOE rbx r13 r14 r15 r12d
..B1.5:                         # Preds ..B1.22
                                # Execution count [0.00e+00]
        movsd     48(%rsp), %xmm0                               #[spill]
        movsd     8(%rsp), %xmm3                                #[spill]
        movsd     16(%rsp), %xmm4                               #[spill]
        movsd     24(%rsp), %xmm5                               #[spill]
        movsd     .L_2il0floatpacket.5(%rip), %xmm1             #
        movsd     .L_2il0floatpacket.4(%rip), %xmm2             #
                                # LOE rbx r13 r14 r15 r12d xmm0 xmm1 xmm2 xmm3 xmm4 xmm5
..B1.6:                         # Preds ..B1.6 ..B1.5
                                # Execution count [0.00e+00]
        mulsd     %xmm1, %xmm0                                  #50.20
        incl      %r12d                                         #48.22
        mulsd     %xmm1, %xmm5                                  #51.20
        mulsd     %xmm1, %xmm4                                  #52.19
        addsd     %xmm2, %xmm0                                  #50.22
        mulsd     %xmm1, %xmm3                                  #53.19
        addsd     %xmm2, %xmm5                                  #51.22
        addsd     %xmm2, %xmm4                                  #52.21
        addsd     %xmm2, %xmm3                                  #53.21
        cmpl      $100000000, %r12d                             #48.13
        jl        ..B1.6        # Prob 100%                     #48.13
                                # LOE rbx r13 r14 r15 r12d xmm0 xmm1 xmm2 xmm3 xmm4 xmm5
..B1.7:                         # Preds ..B1.6
                                # Execution count [0.00e+00]
        xorl      %eax, %eax                                    #71.14
        movsd     %xmm0, 48(%rsp)                               #[spill]
        movsd     %xmm3, 8(%rsp)                                #[spill]
        movsd     %xmm4, 16(%rsp)                               #[spill]
        movsd     %xmm5, 24(%rsp)                               #[spill]
..___tag_value_main.24:
#       time_CPU()
        call      time_CPU                                      #71.14
..___tag_value_main.25:
                                # LOE rbx r13 r14 r15 xmm0
..B1.23:                        # Preds ..B1.7
                                # Execution count [0.00e+00]
        movsd     %xmm0, (%rsp)                                 #71.14[spill]
                                # LOE rbx r13 r14 r15 xmm0
..B1.8:                         # Preds ..B1.23
                                # Execution count [0.00e+00]
        xorl      %eax, %eax                                    #72.20
        subsd     40(%rsp), %xmm0                               #71.27[spill]
        movsd     %xmm0, (%rsp)                                 #71.27[spill]
..___tag_value_main.29:
#       time_clock()
        call      time_clock                                    #72.20
..___tag_value_main.30:
                                # LOE rbx r13 r14 r15 xmm0
..B1.24:                        # Preds ..B1.8
                                # Execution count [0.00e+00]
        movsd     %xmm0, 40(%rsp)                               #72.20[spill]
                                # LOE rbx r13 r14 r15 xmm0
..B1.9:                         # Preds ..B1.24
                                # Execution count [0.00e+00]
        movsd     .L_2il0floatpacket.7(%rip), %xmm1             #74.33
        movl      $il0_peep_printf_format_0, %edi               #75.3
        addsd     48(%rsp), %xmm1                               #74.35[spill]
        subsd     32(%rsp), %xmm0                               #72.35[spill]
        addsd     24(%rsp), %xmm1                               #74.37[spill]
        movsd     %xmm0, 40(%rsp)                               #72.35[spill]
        addsd     16(%rsp), %xmm1                               #74.39[spill]
        addsd     8(%rsp), %xmm1                                #74.41[spill]
        movsd     %xmm1, 56(%rsp)                               #74.41[spill]
        call      puts                                          #75.3
                                # LOE rbx r13 r14 r15
..B1.10:                        # Preds ..B1.9
                                # Execution count [0.00e+00]
        movsd     56(%rsp), %xmm0                               #76.3[spill]
        movl      $.L_2__STRING.1, %edi                         #76.3
        xorl      %eax, %eax                                    #76.3
        incl      %eax                                          #76.3
..___tag_value_main.41:
#       printf(const char *__restrict__, ...)
        call      printf                                        #76.3
..___tag_value_main.42:
                                # LOE rbx r13 r14 r15
..B1.11:                        # Preds ..B1.10
                                # Execution count [0.00e+00]
        movsd     56(%rsp), %xmm0                               #77.3[spill]
        movl      $.L_2__STRING.2, %edi                         #77.3
        xorl      %eax, %eax                                    #77.3
        incl      %eax                                          #77.3
..___tag_value_main.44:
#       printf(const char *__restrict__, ...)
        call      printf                                        #77.3
..___tag_value_main.45:
                                # LOE rbx r13 r14 r15
..B1.12:                        # Preds ..B1.11
                                # Execution count [0.00e+00]
        movl      $10, %edi                                     #78.3
        call      putchar                                       #78.3
                                # LOE rbx r13 r14 r15
..B1.13:                        # Preds ..B1.12
                                # Execution count [0.00e+00]
        pxor      %xmm0, %xmm0                                  #79.3
        movl      $.L_2__STRING.4, %edi                         #79.3
        cvtss2sd  .L_2il0floatpacket.10(%rip), %xmm0            #79.3
        movsd     (%rsp), %xmm1                                 #79.3[spill]
        movl      $3, %eax                                      #79.3
        movsd     40(%rsp), %xmm2                               #79.3[spill]
        movsd     %xmm0, 8(%rsp)                                #79.3[spill]
..___tag_value_main.48:
#       printf(const char *__restrict__, ...)
        call      printf                                        #79.3
..___tag_value_main.49:
                                # LOE rbx r13 r14 r15
..B1.14:                        # Preds ..B1.13
                                # Execution count [0.00e+00]
        movsd     8(%rsp), %xmm0                                #81.3[spill]
        movl      $.L_2__STRING.5, %edi                         #81.3
        movsd     (%rsp), %xmm1                                 #81.3[spill]
        movl      $3, %eax                                      #81.3
        movsd     40(%rsp), %xmm2                               #81.3[spill]
..___tag_value_main.53:
#       printf(const char *__restrict__, ...)
        call      printf                                        #81.3
..___tag_value_main.54:
                                # LOE rbx r13 r14 r15
..B1.15:                        # Preds ..B1.14
                                # Execution count [0.00e+00]
        movsd     .L_2il0floatpacket.9(%rip), %xmm0             #83.3
        movl      $.L_2__STRING.6, %edi                         #83.3
        divsd     40(%rsp), %xmm0                               #83.3[spill]
        xorl      %eax, %eax                                    #83.3
        incl      %eax                                          #83.3
..___tag_value_main.57:
#       printf(const char *__restrict__, ...)
        call      printf                                        #83.3
..___tag_value_main.58:
                                # LOE rbx r13 r14 r15
..B1.16:                        # Preds ..B1.15
                                # Execution count [0.00e+00]
        movl      $il0_peep_printf_format_1, %edi               #84.3
        call      puts                                          #84.3
                                # LOE rbx r13 r14 r15
..B1.17:                        # Preds ..B1.16
                                # Execution count [0.00e+00]
        xorl      %eax, %eax                                    #86.1
        addq      $120, %rsp                                    #86.1
	.cfi_restore 12
        popq      %r12                                          #86.1
        movq      %rbp, %rsp                                    #86.1
        popq      %rbp                                          #86.1
	.cfi_def_cfa 7, 8
	.cfi_restore 6
        ret                                                     #86.1
        .align    16,0x90
                                # LOE
	.cfi_endproc
# mark_end;
	.type	main,@function
	.size	main,.-main
..LNmain.0:
	.section .rodata.str1.4, "aMS",@progbits,1
	.align 4
	.align 4
il0_peep_printf_format_0:
	.word	10
	.space 2, 0x00 	# pad
	.align 4
il0_peep_printf_format_1:
	.word	10
	.data
# -- End  main
	.section .rodata, "a"
	.align 8
	.align 8
.L_2il0floatpacket.0:
	.long	0x0c6f7a0b,0x3ff00001
	.type	.L_2il0floatpacket.0,@object
	.size	.L_2il0floatpacket.0,8
	.align 8
.L_2il0floatpacket.1:
	.long	0x18def417,0x3ff00002
	.type	.L_2il0floatpacket.1,@object
	.size	.L_2il0floatpacket.1,8
	.align 8
.L_2il0floatpacket.2:
	.long	0x254e6e22,0x3ff00003
	.type	.L_2il0floatpacket.2,@object
	.size	.L_2il0floatpacket.2,8
	.align 8
.L_2il0floatpacket.3:
	.long	0x31bde82d,0x3ff00004
	.type	.L_2il0floatpacket.3,@object
	.size	.L_2il0floatpacket.3,8
	.align 8
.L_2il0floatpacket.4:
	.long	0xa0b5ed8d,0x3eb0c6f7
	.type	.L_2il0floatpacket.4,@object
	.size	.L_2il0floatpacket.4,8
	.align 8
.L_2il0floatpacket.5:
	.long	0x02af31dc,0x3ff00000
	.type	.L_2il0floatpacket.5,@object
	.size	.L_2il0floatpacket.5,8
	.align 8
.L_2il0floatpacket.6:
	.long	0xe826d695,0x3e112e0b
	.type	.L_2il0floatpacket.6,@object
	.size	.L_2il0floatpacket.6,8
	.align 8
.L_2il0floatpacket.7:
	.long	0xbe48a58a,0x402a0012
	.type	.L_2il0floatpacket.7,@object
	.size	.L_2il0floatpacket.7,8
	.align 8
.L_2il0floatpacket.8:
	.long	0x00000000,0x41c7d784
	.type	.L_2il0floatpacket.8,@object
	.size	.L_2il0floatpacket.8,8
	.align 8
.L_2il0floatpacket.9:
	.long	0x9999999a,0x3fe99999
	.type	.L_2il0floatpacket.9,@object
	.size	.L_2il0floatpacket.9,8
	.align 4
.L_2il0floatpacket.10:
	.long	0x4e3ebc20
	.type	.L_2il0floatpacket.10,@object
	.size	.L_2il0floatpacket.10,4
	.align 4
	.globl num_iter
num_iter:
	.long	100000000
	.type	num_iter,@object
	.size	num_iter,4
	.section .rodata.str1.4, "aMS",@progbits,1
	.space 2, 0x00 	# pad
	.align 4
.L_2__STRING.1:
	.long	1970496850
	.long	1864397932
	.long	1918967910
	.long	1835562089
	.long	1667855461
	.long	1701867296
	.long	1769234802
	.long	980643439
	.long	1718363424
	.word	10
	.type	.L_2__STRING.1,@object
	.size	.L_2__STRING.1,38
	.space 2, 0x00 	# pad
	.align 4
.L_2__STRING.2:
	.long	1768847703
	.long	1886330987
	.long	1667330661
	.long	1629514090
	.long	1836349810
	.long	1668904037
	.long	1668902522
	.long	622869096
	.long	681580
	.type	.L_2__STRING.2,@object
	.size	.L_2__STRING.2,36
	.align 4
.L_2__STRING.6:
	.long	1633974615
	.long	-982552982
	.long	981976219
	.long	1718363424
	.long	1816545056
	.long	175337583
	.byte	0
	.type	.L_2__STRING.6,@object
	.size	.L_2__STRING.6,25
	.section .rodata.str1.32, "aMS",@progbits,1
	.align 32
	.align 32
.L_2__STRING.4:
	.long	1701669204
	.long	1919903264
	.long	1702389024
	.long	1769239907
	.long	622880622
	.long	1629513324
	.long	1752459634
	.long	1769235821
	.long	1886330979
	.long	1952543333
	.long	1936617321
	.long	537463354
	.long	542462019
	.long	1814372397
	.long	1998597222
	.long	1668050017
	.long	1801678700
	.long	622865696
	.long	681580
	.type	.L_2__STRING.4,@object
	.size	.L_2__STRING.4,76
	.space 20, 0x00 	# pad
	.align 32
.L_2__STRING.5:
	.long	1935768131
	.long	1803122464
	.long	1851879023
	.long	622879081
	.long	1864394348
	.long	1634887024
	.long	543779427
	.long	1954116193
	.long	2037671277
	.long	2037283427
	.long	171599971
	.long	1346576393
	.long	539828309
	.long	744909861
	.long	1734703648
	.long	757101153
	.long	1718363424
	.word	10
	.type	.L_2__STRING.5,@object
	.size	.L_2__STRING.5,70
	.data
	.section .note.GNU-stack, ""
# End
