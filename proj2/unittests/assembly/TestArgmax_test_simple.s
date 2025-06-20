.import ../../src/utils.s
.import ../../src/argmax.s

.data
m0: .word 1 2 7 3 4 5
msg0: .asciiz "expected a0 to be 2 not: "

.globl main_test
.text
# main_test function for testing
main_test:
    # Prologue
    addi sp, sp, -8
    sw ra, 0(sp)
    sw s0, 4(sp)


    # load address to array m0 into a0
    la a0 m0

    # load 6 into a1
    li a1 6

    # call argmax function
    jal ra argmax

    # save all return values in the save registers
    mv s0 a0


    # check that a0 == 2
    li t0 2
    beq s0 t0 a0_eq_2
    # print error and exit
    la a1, msg0
    jal print_str
    mv a1 s0
    jal print_int
    # Print newline
    li a1 '\n'
    jal ra print_char
    # exit with code 8 to indicate failure
    li a1 8
    jal exit2
    a0_eq_2:


    # exit normally
    # Epilogue
    lw ra, 0(sp)
    lw s0, 4(sp)
    addi sp, sp, 8

    jal exit
