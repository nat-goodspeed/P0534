# reserve space on stack
subi  %r1, %r1, 92

stw  %r13, 0(%r1)  # save R13
stw  %r14, 4(%r1)  # save R14
stw  %r15, 8(%r1)  # save R15
stw  %r16, 12(%r1)  # save R16
stw  %r17, 16(%r1)  # save R17
stw  %r18, 20(%r1)  # save R18
stw  %r19, 24(%r1)  # save R19
stw  %r20, 28(%r1)  # save R20
stw  %r21, 32(%r1)  # save R21
stw  %r22, 36(%r1)  # save R22
stw  %r23, 40(%r1)  # save R23
stw  %r24, 44(%r1)  # save R24
stw  %r25, 48(%r1)  # save R25
stw  %r26, 52(%r1)  # save R26
stw  %r27, 56(%r1)  # save R27
stw  %r28, 60(%r1)  # save R28
stw  %r29, 64(%r1)  # save R29
stw  %r30, 68(%r1)  # save R30
stw  %r31, 72(%r1)  # save R31
stw  %r3,  76(%r1)  # save hidden

# save CR
mfcr  %r0
stw   %r0, 80(%r1)
# save LR
mflr  %r0
stw   %r0, 84(%r1)
# save LR as PC
stw   %r0, 88(%r1)

# store RSP (pointing to context-data) in R6
mr  %r6, %r1

# restore RSP (pointing to context-data) from R4
mr  %r1, %r4

lwz  %r13, 0(%r1)  # restore R13
lwz  %r14, 4(%r1)  # restore R14
lwz  %r15, 8(%r1)  # restore R15
lwz  %r16, 12(%r1)  # restore R16
lwz  %r17, 16(%r1)  # restore R17
lwz  %r18, 20(%r1)  # restore R18
lwz  %r19, 24(%r1)  # restore R19
lwz  %r20, 28(%r1)  # restore R20
lwz  %r21, 32(%r1)  # restore R21
lwz  %r22, 36(%r1)  # restore R22
lwz  %r23, 40(%r1)  # restore R23
lwz  %r24, 44(%r1)  # restore R24
lwz  %r25, 48(%r1)  # restore R25
lwz  %r26, 52(%r1)  # restore R26
lwz  %r27, 56(%r1)  # restore R27
lwz  %r28, 60(%r1)  # restore R28
lwz  %r29, 64(%r1)  # restore R29
lwz  %r30, 68(%r1)  # restore R30
lwz  %r31, 72(%r1)  # restore R31
lwz  %r3,  76(%r1)  # restore hidden

# restore CR
lwz   %r0, 80(%r1)
mtcr  %r0
# restore LR
lwz   %r0, 84(%r1)
mtlr  %r0
# load PC
lwz   %r0, 88(%r1)
# restore CTR
mtctr %r0

# adjust stack
addi  %r1, %r1, 92

# return transfer_t 
stw  %r6, 0(%r3)
stw  %r5, 4(%r3)

# jump to context
bctr
