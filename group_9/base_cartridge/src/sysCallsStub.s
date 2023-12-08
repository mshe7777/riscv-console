.section .text, "ax"
.global GetTicks, GetController
.global initSprite, moveSprites, initSprites, removeSprite, moveSprite, backgroundInit
.global delay, setModeRegister, print, clear
.global threadInitialize
.global setCallbackHandler

GetTicks:
    li      a5, 0x00000001
    ecall
GetController:
    li      a5, 0x00000002
    ecall
initSprite:
    li      a5, 0x00000003
    ecall
moveSprites:
    li      a5, 0x00000004
    ecall
removeSprite:
    li      a5, 0x00000005
    ecall
print:
    li      a5, 0x00000006
    ecall
clear:
    li      a5, 0x00000007
    ecall
delay:
    li      a5, 0x00000008
    ecall
setModeRegister:
    li      a5, 0x00000009
    ecall
moveSprite:
    li      a5, 0x0000000A
    ecall
threadInitialize:
    li      a5, 0x0000000B
    ecall
setCallbackHandler:
    li      a5, 0x0000000C
    ecall
backgroundInit:
    li      a5, 0x0000000D
    ecall