.section .text, "ax"
.global initialize
.global getTicks,getButtonStatus,getCmdInterrupted,getVideoInterrupted,threadInit
.global thread_create,thread_yield,thread_exit
.global set_small_sprite,set_medium_sprite,set_large_sprite,set_background
.global Malloc, Free, Memcpy





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

    