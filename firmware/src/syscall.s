.section .text, "ax"
.global getTicks,getButtonStatus,getCmdInterrupted,getVideoInterrupted

getTicks:
    li a3,0
    ecall

getButtonStatus:
    li a3,1
    ecall

getCmdInterrupted:
    li a3,2
    ecall


getVideoInterrupted:
    li a3,3
    ecall

  