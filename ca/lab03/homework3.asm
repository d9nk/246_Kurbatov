.data
nl: .asciz "\n"

.text
.globl main

main:
    li a7, 5
    ecall
    mv t0, a0

    li a7, 5
    ecall
    mv t1, a0

#1
    addi t2, t0, 5
    addi t3, t1, -7
    sub t2, t2, t3
    mv a0, t2
    li a7, 1
    ecall
    jal nl_p

#2
    srli t2, t0, 2
    addi t3, t1, -1
    slli t3, t3, 3
    add t2, t2, t3
    mv a0, t2
    li a7, 1
    ecall
    jal nl_p

#3
    sll t2, t0, t1
    addi t2, t2, -10
    mv a0, t2
    li a7, 1
    ecall
    jal nl_p

#4
    sra t2, t0, t1
    addi t2, t2, 10
    mv a0, t2
    li a7, 1
    ecall
    jal nl_p

#5
    slli t2, t0, 2
    sub t2, t2, t1
    addi t2, t2, 5
    srai t2, t2, 1
    mv a0, t2
    li a7, 1
    ecall
    jal nl_p

#6
    slli t2, t0, 2
    slli t3, t0, 1
    add t2, t2, t3
    slli t3, t1, 1
    add t3, t3, t1
    sub t2, t2, t3
    mv a0, t2
    li a7, 1
    ecall
    jal nl_p

#7
    slli t2, t0, 1
    mul t2, t2, t0
    slli t3, t1, 1
    add t3, t3, t1
    sub t2, t2, t3
    addi t2, t2, 4
    mv a0, t2
    li a7, 1
    ecall
    jal nl_p

#8
    addi t2, t0, 5
    div t2, t2, t1
    addi t3, t1, -1
    li t4, 10
    div t4, t4, t3
    add t2, t2, t4
    mv a0, t2
    li a7, 1
    ecall
    jal nl_p

#9
    div t2, t0, t1
    mul t2, t2, t1
    rem t3, t0, t1
    add t2, t2, t3
    mv a0, t2
    li a7, 1
    ecall
    jal nl_p

#10
    li t2, -1
    slli t2, t2, 2
    and t2, t0, t2
    mv a0, t2
    li a7, 1
    ecall
    jal nl_p

#11
    li t2, -1
    srli t2, t2, 30
    or t2, t0, t2
    mv a0, t2
    li a7, 1
    ecall
    jal nl_p

#12
    li t2, 1
    sll t2, t2, t1
    or t2, t0, t2
    mv a0, t2
    li a7, 1
    ecall
    jal nl_p

#13
    li t2, 1
    sll t2, t2, t1
    not t2, t2
    and t2, t0, t2
    mv a0, t2
    li a7, 1
    ecall
    jal nl_p

#14
    slt t2, t1, t0
    xori t2, t2, 1
    mv a0, t2
    li a7, 1
    ecall
    jal nl_p

#15
    addi t2, t1, 3
    slt t3, t0, t2
    slt t4, t2, t0
    or t2, t3, t4
    mv a0, t2
    li a7, 1
    ecall
    jal nl_p

#16
    li t2, -5
    slt t3, t2, t0
    li t2, 5
    slt t4, t1, t2
    and t2, t3, t4
    mv a0, t2
    li a7, 1
    ecall

    li a7, 10
    ecall

nl_p:
    la a0, nl
    li a7, 4
    ecall
    ret

