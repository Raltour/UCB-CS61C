.globl factorial

.data
n: .word 8

.text
main:
    la t0, n
    lw a0, 0(t0)
    jal ra, factorial

    addi a1, a0, 0
    addi a0, x0, 1
    ecall # Print Result

    addi a1, x0, '\n'
    addi a0, x0, 1
    ecall # Print newline

    addi a0, x0, 10
    ecall # Exit

factorial:
    # YOUR CODE HERE
    bne a0, x0, recusion
    addi a0, a0, 1
    j return
recusion: 
    addi sp, sp, -8 
    sw s0, 0(sp)
    sw ra, 4(sp)
    mv s0, a0
    addi a0, a0, -1
    jal ra, factorial
    mul a0, a0, s0
    lw s0, 0(sp)
    lw ra, 4(sp)
    addi sp, sp, 8
return:
    jr ra