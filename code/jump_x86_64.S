leaq  -0x38(%rsp), %rsp

movq  %r12, 0x8(%rsp)
movq  %r13, 0x10(%rsp)
movq  %r14, 0x18(%rsp)
movq  %r15, 0x20(%rsp)
movq  %rbx, 0x28(%rsp)
movq  %rbp, 0x30(%rsp)

movq  %rsp, %rax

movq  %rdi, %rsp

movq  0x38(%rsp), %r8

movq  0x8(%rsp), %r12
movq  0x10(%rsp), %r13
movq  0x18(%rsp), %r14
movq  0x20(%rsp), %r15
movq  0x28(%rsp), %rbx
movq  0x30(%rsp), %rbp

leaq  0x40(%rsp), %rsp

movq  %rsi, %rdx
movq  %rax, %rdi

jmp  *%r8
