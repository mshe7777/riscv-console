.section .init, "ax"
.global _start
# _start:
#     .cfi_startproc
#     .cfi_undefined ra
#     .option push
#     .option norelax
#     la gp, __global_pointer$
#     .option pop
#     la sp, __stack_top
#     add s0, sp, zero
#     jal ra, init
#     nop
#     mv      a0, gp
#     jal     ra, 
#     nop
#     jal zero, main
#     .cfi_endproc
#     .end
_start:
    .cfi_startproc
    .cfi_undefined ra
    .option push
    .option norelax
    la      gp, __global_pointer$
    .option pop
    la      sp, __stack_top
    addi	sp, sp, -4
    sw      ra, 0(sp)
    add     s0, sp, zero
    jal     ra, init
    nop
    mv      a0, gp
    jal     ra, initialize
    nop
    jal     ra, main
    lw      ra,0(sp)
    addi	sp, sp, 4
    ret
    .cfi_endproc


.section .text, "ax"
.global initialize
.global getTicks,getButtonStatus,getCmdInterrupted,getVideoInterrupted,threadInit
.global thread_create,thread_yield,thread_exit
.global Malloc, Free, Memcpy
.global lock, unlock, initLock,destoryLock
.global set_gp, get_gp

set_gp:
    mv gp,a0
    ret
get_gp:
    mv a0,gp
    ret



initialize:
    li a5,0
    ecall

getTicks:
    li a5,1
    ecall

getButtonStatus:
    li a5,2
    ecall

getCmdInterrupted:
    li a5,3
    ecall


getVideoInterrupted:
    li a5,4
    ecall

threadInit:
    li a5,5
    ecall


thread_create:
    li a5,6
    ecall

thread_yield:
    li a5,7
    ecall

thread_exit:
    li a5,8
    ecall


Memcpy:
    li a5,9
    ecall

Malloc:
    li a5,10
    ecall

Free:
    li a5,11
    ecall

lock:
    li a5,12
    ecall

unlock:
    li a5,13
    ecall

initLock:
    li a5,14
    ecall

destoryLock:
    li a4,15
    ecall