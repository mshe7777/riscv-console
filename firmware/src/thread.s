.section .text, "ax"
.global get_gp, ContextInitialize, ContextSwitch, call_th_ent, set_tp,startFirst

ContextInitialize:
    addi sp,sp,-4
    sw gp,0(sp)
    mv gp,a3
    addi a0,a0,-56
    sw   a1,52(a0)
    sw   gp,48(a0)
    sw   zero,44(a0)
    sw   zero,40(a0)
    sw   zero,36(a0)
    sw   zero,32(a0)
    sw   zero,28(a0)
    sw   zero,24(a0)
    sw   a2,20(a0)
    sw   zero,16(a0)
    sw   zero,12(a0)
    sw   zero,8(a0)
    sw   zero,4(a0)
    sw   zero,0(a0)
    lw  gp,0(sp)
    addi sp,sp,4
    ret

ContextSwitch:
    # csrci   mstatus, 0x8
    addi sp,sp,-56
    sw   ra,52(sp)
    sw   gp,48(sp)
    sw   tp,44(sp)
    sw   t0,40(sp)
    sw   t1,36(sp)
    sw   t2,32(sp)
    sw   s0,28(sp)
    sw   s1,24(sp)
    sw   a0,20(sp)
    sw   a1,16(sp)
    sw   a2,12(sp)
    sw   a3,8(sp)
    sw   a4,4(sp)
    sw   a5,0(sp)
    sw   sp,0(a0)
    mv   sp,a1
    lw   ra,52(sp)
    lw   gp,48(sp)
    lw   tp,44(sp)
    lw   t0,40(sp)
    lw   t1,36(sp)
    lw   t2,32(sp)
    lw   s0,28(sp)
    lw   s1,24(sp)
    lw   a0,20(sp)
    lw   a1,16(sp)
    lw   a2,12(sp)
    lw   a3,8(sp)
    lw   a4,4(sp)
    lw   a5,0(sp)
    addi sp,sp,56
    csrsi mstatus, 0x8
    ret

startFirst:
    # csrci   mstatus, 0x8
    mv   sp,a0
    lw   ra,52(sp)
    lw   gp,48(sp)
    lw   tp,44(sp)
    lw   t0,40(sp)
    lw   t1,36(sp)
    lw   t2,32(sp)
    lw   s0,28(sp)
    lw   s1,24(sp)
    lw   a0,20(sp)
    lw   a1,16(sp)
    lw   a2,12(sp)
    lw   a3,8(sp)
    lw   a4,4(sp)
    lw   a5,0(sp)
    addi sp,sp,56
    # csrsi mstatus, 0x8
    ret

get_gp:
    mv a0,gp
    ret
# ContextSwitch:
#     addi    sp,sp,-52
#     sw      ra,48(sp)
#     sw      tp,44(sp)
#     sw      t0,40(sp)
#     sw      t1,36(sp)
#     sw      t2,32(sp)
#     sw      s0,28(sp)
#     sw      s1,24(sp)
#     sw      a0,20(sp)
#     sw      a1,16(sp)
#     sw      a2,12(sp)
#     sw      a3,8(sp)
#     sw      a4,4(sp)
#     sw      a5,0(sp)
#     sw      sp,0(a0) #a0
#     mv      sp,a1
#     lw      ra,48(sp)
#     lw      tp,44(sp)
#     lw      t0,40(sp)
#     lw      t1,36(sp)
#     lw      t2,32(sp)
#     lw      s0,28(sp)
#     lw      s1,24(sp)
#     lw      a0,20(sp)
#     lw      a1,16(sp)
#     lw      a2,12(sp)
#     lw      a3,8(sp)
#     lw      a4,4(sp)
#     lw      a5,0(sp)
#     addi    sp,sp,52
#     ret
call_th_ent:
    addi    sp,sp,-4
    sw      ra, 0(sp)
    mv      gp, a2
    jalr    a1       # a1 should be the entry parameter
    .option push
    .option norelax
    la      gp, __global_pointer$
    .option pop
    lw      ra, 0(sp)
    addi    sp, sp, 4
    ret

set_tp:
    mv tp,a0
    ret
get_tp:
    mv a0,tp
    ret
    # context_switch:
    # /*context_snapshot context_shot
    # call printContextSnapshot 
    # context_project context_shot*/

    # /* csrci   mstatus, 0x8*/ /* disable interrupt */
    # addi    sp,sp,-18*4 /* context size 18: see port_riscv.h */
    # sw      ra,0*4(sp)
    # sw      gp,2*4(sp)
    # sw      tp,3*4(sp)
    # sw      t0,4*4(sp)
    # sw      t1,5*4(sp)
    # sw      t2,6*4(sp)
    # sw      s0,7*4(sp)
    # sw      s1,8*4(sp)
    # sw      a0,9*4(sp)
    # sw      a1,10*4(sp)
    # sw      a2,11*4(sp)
    # sw      a3,12*4(sp)
    # sw      a4,13*4(sp)
    # sw      a5,14*4(sp)

    # csrr    t0, mepc
    # sw      t0,15*4(sp) /* write mepc into context */

    # csrr    t0, mcause
    # sw      t0,16*4(sp) /* write mcause into context */

    # csrr    t0, mstatus
    # sw      t0,17*4(sp) /* write mstatus into context */

    # sw      sp,0(a0)
    # mv      sp,a1

    # lw      t0,15*4(sp)
    # csrw    mepc, t0  /* read mepc from context, write to register */

    # lw      t0,16*4(sp)
    # csrw    mcause, t0  /* read mcause from context, write to register */

    # lw      t0,17*4(sp)
    # csrw    mstatus, t0  /* read mstatus from context, write to register */

    # lw      ra,0*4(sp)
    # lw      gp,2*4(sp)
    # lw      tp,3*4(sp)
    # lw      t0,4*4(sp)
    # lw      t1,5*4(sp)
    # lw      t2,6*4(sp)
    # lw      s0,7*4(sp)
    # lw      s1,8*4(sp)
    # lw      a0,9*4(sp)
    # lw      a1,10*4(sp)
    # lw      a2,11*4(sp)
    # lw      a3,12*4(sp)
    # lw      a4,13*4(sp)
    # lw      a5,14*4(sp)
    # addi    sp,sp,18*4

    # /*context_snapshot context_shot
    # call printContextSnapshot
    # context_project context_shot */
    # /* csrsi   mstatus, 0x8*/ /* enable interrupt */
    # ret