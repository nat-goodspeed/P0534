@ save LR as PC
push {lr}
@ save hidden,V1-V8,LR
push {a1,v1-v8,lr}

@ store RSP (pointing to context-data) in A1
mov  a1, sp

@ restore RSP (pointing to context-data) from A2
mov  sp, a2

@ restore hidden,V1-V8,LR
pop {a4,v1-v8,lr}

@ return transfer_t from jump
str  a1, [a4, #0]
str  a3, [a4, #4]
@ pass transfer_t as first arg in context function
@ A1 == FCTX, A2 == DATA
mov  a2, a3

@ restore PC
pop {pc}
