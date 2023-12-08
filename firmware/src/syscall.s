.section .text, "ax"
.global initialize
.global getTicks,getButtonStatus,getCmdInterrupted,getVideoInterrupted,threadInit
.global thread_create,thread_yield,thread_exit
.global Malloc, Free, Memcpy
.global lock, unlock, initLock,destoryLock
.global createCond,destoryCond,condWait,condNotifyOne,condNotifyAll
.global thread_join





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

createCond:
    li a5,16
    ecall

destoryCond:
    li a5,17
    ecall

condWait:
    li a5,18
    ecall

condSignal:
    li a5,19
    ecall

condBroadcast:
    li a5,20
    ecall
sleep:
    li a5,21
    ecall

thread_join:
    li a5,22
    ecall