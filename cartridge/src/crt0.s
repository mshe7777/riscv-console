.section .init, "ax"
.global _start
_start:
    .cfi_startproc
    .cfi_undefined ra
    .option push
    .option norelax
    la gp, __global_pointer$
    .option pop
    la sp, __stack_top
    add s0, sp, zero
    jal ra, init
    nop
    jal zero, main
    .cfi_endproc
    .end


# .section .text, "ax"
# .global Malloc, Free, Memcpy

# Memcpy:
#     li a5,9
#     ecall

# Malloc:
#     li a5,10
#     ecall

# Free:
#     li a5,11
#     ecall