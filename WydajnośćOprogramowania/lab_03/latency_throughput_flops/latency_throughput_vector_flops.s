# mark_description "Intel(R) C Intel(R) 64 Compiler Classic for applications running on Intel(R) 64, Version 2021.5.0 Build 2021";
# mark_description "1109_000000";
# mark_description "-I../utd_time_unix -O3 -march=core-avx2 -S";
	.file "latency_throughput_vector_flops.c"
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
                                # Execution count [8.65e+01]
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
        subq      $1792, %rsp                                   #9.18
        movl      $3, %edi                                      #9.18
        xorl      %esi, %esi                                    #9.18
        call      __intel_new_feature_proc_init                 #9.18
                                # LOE rbx r12 r13 r14 r15
..B1.30:                        # Preds ..B1.1
                                # Execution count [8.65e+01]
        vstmxcsr  (%rsp)                                        #9.18
        vmovupd   .L_2il0floatpacket.2(%rip), %ymm3             #21.16
        vmovdqu   .L_2il0floatpacket.0(%rip), %xmm5             #21.5
        vmovdqu   .L_2il0floatpacket.1(%rip), %xmm4             #21.5
        vmovupd   .L_2il0floatpacket.3(%rip), %ymm6             #21.25
        vmovupd   .L_2il0floatpacket.4(%rip), %ymm2             #22.16
        vmovupd   .L_2il0floatpacket.5(%rip), %ymm1             #23.16
        vmovupd   .L_2il0floatpacket.6(%rip), %ymm0             #24.16
        orl       $32832, (%rsp)                                #9.18
        xorl      %eax, %eax                                    #20.3
        vldmxcsr  (%rsp)                                        #9.18
        .align    16,0x90
                                # LOE rax rbx r12 r13 r14 r15 xmm4 xmm5 ymm0 ymm1 ymm2 ymm3 ymm6
..B1.2:                         # Preds ..B1.2 ..B1.30
                                # Execution count [4.50e+03]
        vcvtdq2pd %xmm4, %ymm10                                 #21.35
        vpaddd    %xmm5, %xmm4, %xmm4                           #21.5
        vmovdqa   %ymm3, %ymm7                                  #21.35
        vmovdqa   %ymm2, %ymm8                                  #22.35
        vmovdqa   %ymm1, %ymm9                                  #23.35
        vfmadd231pd %ymm10, %ymm6, %ymm7                        #21.35
        vfmadd231pd %ymm10, %ymm6, %ymm8                        #22.35
        vfmadd231pd %ymm10, %ymm6, %ymm9                        #23.35
        vfmadd213pd %ymm0, %ymm6, %ymm10                        #24.35
        vmovupd   %ymm7, 1280(%rsp,%rax,8)                      #21.5
        vmovupd   %ymm8, 32(%rsp,%rax,8)                        #22.5
        vmovupd   %ymm9, 448(%rsp,%rax,8)                       #23.5
        vmovupd   %ymm10, 864(%rsp,%rax,8)                      #24.5
        addq      $4, %rax                                      #20.3
        cmpq      $52, %rax                                     #20.3
        jb        ..B1.2        # Prob 98%                      #20.3
                                # LOE rax rbx r12 r13 r14 r15 xmm4 xmm5 ymm0 ymm1 ymm2 ymm3 ymm6
..B1.3:                         # Preds ..B1.2
                                # Execution count [4.50e+03]
        xorl      %eax, %eax                                    #30.3
        vmovupd   .L_2il0floatpacket.7(%rip), %ymm0             #30.3
        xorl      %edx, %edx                                    #30.3
                                # LOE rbx r12 r13 r14 r15 eax edx ymm0 ymm6
..B1.4:                         # Preds ..B1.6 ..B1.3
                                # Execution count [9.00e+05]
        xorl      %ecx, %ecx                                    #31.5
                                # LOE rcx rbx r12 r13 r14 r15 eax edx ymm0 ymm6
..B1.5:                         # Preds ..B1.5 ..B1.4
                                # Execution count [4.68e+07]
        vmovupd   1280(%rsp,%rcx,8), %ymm1                      #32.29
        vfmadd213pd %ymm6, %ymm0, %ymm1                         #32.38
        vmovupd   %ymm1, 1280(%rsp,%rcx,8)                      #32.7
        addq      $4, %rcx                                      #31.5
        cmpq      $52, %rcx                                     #31.5
        jb        ..B1.5        # Prob 98%                      #31.5
                                # LOE rcx rbx r12 r13 r14 r15 eax edx ymm0 ymm6
..B1.6:                         # Preds ..B1.5
                                # Execution count [9.00e+05]
        incl      %eax                                          #30.3
        cmpl      $100000000, %eax                              #30.3
        jb        ..B1.4        # Prob 99%                      #30.3
                                # LOE rbx r12 r13 r14 r15 eax edx ymm0 ymm6
..B1.7:                         # Preds ..B1.6
                                # Execution count [0.00e+00]
        vmovupd   .L_2il0floatpacket.8(%rip), %ymm0             #36.17
        xorl      %eax, %eax                                    #35.3
                                # LOE rax rbx r12 r13 r14 r15 edx ymm0
..B1.8:                         # Preds ..B1.8 ..B1.7
                                # Execution count [0.00e+00]
        lea       1280(%rsp,%rax,8), %rcx                       #36.5
        vmulpd    (%rcx), %ymm0, %ymm1                          #36.5
        vmovupd   %ymm1, (%rcx)                                 #36.5
        addq      $4, %rax                                      #35.3
        cmpq      $52, %rax                                     #35.3
        jb        ..B1.8        # Prob 50%                      #35.3
                                # LOE rax rbx r12 r13 r14 r15 edx ymm0
..B1.9:                         # Preds ..B1.8
                                # Execution count [0.00e+00]
        xorl      %eax, %eax                                    #41.14
        movl      %edx, (%rsp)                                  #41.14[spill]
        vzeroupper                                              #41.14
..___tag_value_main.7:
#       time_CPU()
        call      time_CPU                                      #41.14
..___tag_value_main.8:
                                # LOE rbx r12 r13 r14 r15 xmm0
..B1.31:                        # Preds ..B1.9
                                # Execution count [0.00e+00]
        movl      (%rsp), %edx                                  #[spill]
        vmovsd    %xmm0, 16(%rsp)                               #41.14[spill]
                                # LOE rbx r12 r13 r14 r15 edx
..B1.10:                        # Preds ..B1.31
                                # Execution count [0.00e+00]
        xorl      %eax, %eax                                    #42.20
        movl      %edx, (%rsp)                                  #42.20[spill]
..___tag_value_main.11:
#       time_clock()
        call      time_clock                                    #42.20
..___tag_value_main.12:
                                # LOE rbx r12 r13 r14 r15 xmm0
..B1.32:                        # Preds ..B1.10
                                # Execution count [0.00e+00]
        movl      (%rsp), %edx                                  #[spill]
        vmovsd    %xmm0, 8(%rsp)                                #42.20[spill]
                                # LOE rbx r12 r13 r14 r15 edx
..B1.11:                        # Preds ..B1.32
                                # Execution count [0.00e+00]
        vmovupd   .L_2il0floatpacket.9(%rip), %ymm0             #48.38
        vmovupd   .L_2il0floatpacket.7(%rip), %ymm1             #48.38
                                # LOE rbx r12 r13 r14 r15 edx ymm0 ymm1
..B1.12:                        # Preds ..B1.14 ..B1.11
                                # Execution count [0.00e+00]
        xorl      %eax, %eax                                    #46.5
                                # LOE rax rbx r12 r13 r14 r15 edx ymm0 ymm1
..B1.13:                        # Preds ..B1.13 ..B1.12
                                # Execution count [0.00e+00]
        lea       1280(%rsp,%rax,8), %rcx                       #48.29
        vmovupd   (%rcx), %ymm2                                 #48.29
        vfmadd213pd %ymm0, %ymm1, %ymm2                         #48.38
        vmovupd   %ymm2, (%rcx)                                 #48.7
        addq      $4, %rax                                      #46.5
        cmpq      $52, %rax                                     #46.5
        jb        ..B1.13       # Prob 50%                      #46.5
                                # LOE rax rbx r12 r13 r14 r15 edx ymm0 ymm1
..B1.14:                        # Preds ..B1.13
                                # Execution count [0.00e+00]
        incl      %edx                                          #44.3
        cmpl      $100000000, %edx                              #44.3
        jb        ..B1.12       # Prob 50%                      #44.3
                                # LOE rbx r12 r13 r14 r15 edx ymm0 ymm1
..B1.15:                        # Preds ..B1.14
                                # Execution count [0.00e+00]
        xorl      %eax, %eax                                    #65.14
        vzeroupper                                              #65.14
..___tag_value_main.16:
#       time_CPU()
        call      time_CPU                                      #65.14
..___tag_value_main.17:
                                # LOE rbx r12 r13 r14 r15 xmm0
..B1.16:                        # Preds ..B1.15
                                # Execution count [0.00e+00]
        xorl      %eax, %eax                                    #66.20
        vsubsd    16(%rsp), %xmm0, %xmm0                        #65.27[spill]
        vmovsd    %xmm0, (%rsp)                                 #65.27[spill]
..___tag_value_main.19:
#       time_clock()
        call      time_clock                                    #66.20
..___tag_value_main.20:
                                # LOE rbx r12 r13 r14 r15 xmm0
..B1.17:                        # Preds ..B1.16
                                # Execution count [0.00e+00]
        xorl      %eax, %eax                                    #69.3
        vsubsd    8(%rsp), %xmm0, %xmm0                         #66.35[spill]
        vmovsd    %xmm0, 16(%rsp)                               #66.35[spill]
        vxorpd    %ymm0, %ymm0, %ymm0                           #68.14
                                # LOE rax rbx r12 r13 r14 r15 ymm0
..B1.18:                        # Preds ..B1.18 ..B1.17
                                # Execution count [0.00e+00]
        vmovupd   1280(%rsp,%rax,8), %ymm1                      #70.12
        vmovupd   448(%rsp,%rax,8), %ymm2                       #70.34
        vaddpd    32(%rsp,%rax,8), %ymm1, %ymm3                 #70.5
        vaddpd    864(%rsp,%rax,8), %ymm2, %ymm4                #70.5
        vaddpd    %ymm4, %ymm3, %ymm5                           #70.5
        addq      $4, %rax                                      #69.3
        vaddpd    %ymm0, %ymm5, %ymm0                           #70.5
        cmpq      $52, %rax                                     #69.3
        jb        ..B1.18       # Prob 50%                      #69.3
                                # LOE rax rbx r12 r13 r14 r15 ymm0
..B1.19:                        # Preds ..B1.18
                                # Execution count [0.00e+00]
        movl      $il0_peep_printf_format_0, %edi               #73.3
        vextractf128 $1, %ymm0, %xmm1                           #68.14
        vaddpd    %xmm1, %xmm0, %xmm2                           #68.14
        vunpckhpd %xmm2, %xmm2, %xmm3                           #68.14
        vaddsd    %xmm3, %xmm2, %xmm4                           #68.14
        vmovsd    %xmm4, 8(%rsp)                                #68.14[spill]
        vzeroupper                                              #73.3
        call      puts                                          #73.3
                                # LOE rbx r12 r13 r14 r15
..B1.20:                        # Preds ..B1.19
                                # Execution count [0.00e+00]
        movl      $.L_2__STRING.1, %edi                         #74.3
        vmovsd    8(%rsp), %xmm0                                #74.3[spill]
        xorl      %eax, %eax                                    #74.3
        incl      %eax                                          #74.3
..___tag_value_main.26:
#       printf(const char *__restrict__, ...)
        call      printf                                        #74.3
..___tag_value_main.27:
                                # LOE rbx r12 r13 r14 r15
..B1.21:                        # Preds ..B1.20
                                # Execution count [0.00e+00]
        movl      $.L_2__STRING.2, %edi                         #75.3
        vmovsd    8(%rsp), %xmm0                                #75.3[spill]
        xorl      %eax, %eax                                    #75.3
        incl      %eax                                          #75.3
..___tag_value_main.29:
#       printf(const char *__restrict__, ...)
        call      printf                                        #75.3
..___tag_value_main.30:
                                # LOE rbx r12 r13 r14 r15
..B1.22:                        # Preds ..B1.21
                                # Execution count [0.00e+00]
        movl      $10, %edi                                     #76.3
        call      putchar                                       #76.3
                                # LOE rbx r12 r13 r14 r15
..B1.23:                        # Preds ..B1.22
                                # Execution count [0.00e+00]
        vxorpd    %xmm0, %xmm0, %xmm0                           #77.3
        movl      $.L_2__STRING.4, %edi                         #77.3
        vcvtss2sd .L_2il0floatpacket.12(%rip), %xmm0, %xmm0     #77.3
        vmovsd    %xmm0, 8(%rsp)                                #77.3[spill]
        movl      $3, %eax                                      #77.3
        vmovsd    (%rsp), %xmm1                                 #77.3[spill]
        vmovsd    16(%rsp), %xmm2                               #77.3[spill]
..___tag_value_main.33:
#       printf(const char *__restrict__, ...)
        call      printf                                        #77.3
..___tag_value_main.34:
                                # LOE rbx r12 r13 r14 r15
..B1.24:                        # Preds ..B1.23
                                # Execution count [0.00e+00]
        movl      $.L_2__STRING.5, %edi                         #79.3
        vmovsd    8(%rsp), %xmm0                                #79.3[spill]
        movl      $3, %eax                                      #79.3
        vmovsd    (%rsp), %xmm1                                 #79.3[spill]
        vmovsd    16(%rsp), %xmm2                               #79.3[spill]
..___tag_value_main.38:
#       printf(const char *__restrict__, ...)
        call      printf                                        #79.3
..___tag_value_main.39:
                                # LOE rbx r12 r13 r14 r15
..B1.25:                        # Preds ..B1.24
                                # Execution count [0.00e+00]
        vmovsd    .L_2il0floatpacket.11(%rip), %xmm0            #81.3
        movl      $.L_2__STRING.6, %edi                         #81.3
        xorl      %eax, %eax                                    #81.3
        incl      %eax                                          #81.3
        vdivsd    16(%rsp), %xmm0, %xmm0                        #81.3[spill]
..___tag_value_main.41:
#       printf(const char *__restrict__, ...)
        call      printf                                        #81.3
..___tag_value_main.42:
                                # LOE rbx r12 r13 r14 r15
..B1.26:                        # Preds ..B1.25
                                # Execution count [0.00e+00]
        movl      $il0_peep_printf_format_1, %edi               #82.3
        call      puts                                          #82.3
                                # LOE rbx r12 r13 r14 r15
..B1.27:                        # Preds ..B1.26
                                # Execution count [0.00e+00]
        xorl      %eax, %eax                                    #86.1
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
	.align 32
	.align 32
.L_2il0floatpacket.2:
	.long	0x0c6f7a0b,0x3ff00001,0x0c6f7a0b,0x3ff00001,0x0c6f7a0b,0x3ff00001,0x0c6f7a0b,0x3ff00001
	.type	.L_2il0floatpacket.2,@object
	.size	.L_2il0floatpacket.2,32
	.align 32
.L_2il0floatpacket.3:
	.long	0x9abcaf48,0x3e7ad7f2,0x9abcaf48,0x3e7ad7f2,0x9abcaf48,0x3e7ad7f2,0x9abcaf48,0x3e7ad7f2
	.type	.L_2il0floatpacket.3,@object
	.size	.L_2il0floatpacket.3,32
	.align 32
.L_2il0floatpacket.4:
	.long	0x18def417,0x3ff00002,0x18def417,0x3ff00002,0x18def417,0x3ff00002,0x18def417,0x3ff00002
	.type	.L_2il0floatpacket.4,@object
	.size	.L_2il0floatpacket.4,32
	.align 32
.L_2il0floatpacket.5:
	.long	0x254e6e22,0x3ff00003,0x254e6e22,0x3ff00003,0x254e6e22,0x3ff00003,0x254e6e22,0x3ff00003
	.type	.L_2il0floatpacket.5,@object
	.size	.L_2il0floatpacket.5,32
	.align 32
.L_2il0floatpacket.6:
	.long	0x31bde82d,0x3ff00004,0x31bde82d,0x3ff00004,0x31bde82d,0x3ff00004,0x31bde82d,0x3ff00004
	.type	.L_2il0floatpacket.6,@object
	.size	.L_2il0floatpacket.6,32
	.align 32
.L_2il0floatpacket.7:
	.long	0x02af31dc,0x3ff00000,0x02af31dc,0x3ff00000,0x02af31dc,0x3ff00000,0x02af31dc,0x3ff00000
	.type	.L_2il0floatpacket.7,@object
	.size	.L_2il0floatpacket.7,32
	.align 32
.L_2il0floatpacket.8:
	.long	0xe826d695,0x3e112e0b,0xe826d695,0x3e112e0b,0xe826d695,0x3e112e0b,0xe826d695,0x3e112e0b
	.type	.L_2il0floatpacket.8,@object
	.size	.L_2il0floatpacket.8,32
	.align 32
.L_2il0floatpacket.9:
	.long	0xa0b5ed8d,0x3eb0c6f7,0xa0b5ed8d,0x3eb0c6f7,0xa0b5ed8d,0x3eb0c6f7,0xa0b5ed8d,0x3eb0c6f7
	.type	.L_2il0floatpacket.9,@object
	.size	.L_2il0floatpacket.9,32
	.align 16
.L_2il0floatpacket.0:
	.long	0x00000004,0x00000004,0x00000004,0x00000004
	.type	.L_2il0floatpacket.0,@object
	.size	.L_2il0floatpacket.0,16
	.align 16
.L_2il0floatpacket.1:
	.long	0x00000000,0x00000001,0x00000002,0x00000003
	.type	.L_2il0floatpacket.1,@object
	.size	.L_2il0floatpacket.1,16
	.align 8
.L_2il0floatpacket.10:
	.long	0x40000000,0x42035f1b
	.type	.L_2il0floatpacket.10,@object
	.size	.L_2il0floatpacket.10,8
	.align 8
.L_2il0floatpacket.11:
	.long	0xcccccccd,0x4024cccc
	.type	.L_2il0floatpacket.11,@object
	.size	.L_2il0floatpacket.11,8
	.align 4
.L_2il0floatpacket.12:
	.long	0x501af8da
	.type	.L_2il0floatpacket.12,@object
	.size	.L_2il0floatpacket.12,4
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
