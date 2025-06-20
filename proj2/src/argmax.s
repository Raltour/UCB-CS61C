.globl argmax

.text
# =================================================================
# FUNCTION: Given a int vector, return the index of the largest
#	element. If there are multiple, return the one
#	with the smallest index.
# Arguments:
# 	a0 (int*) is the pointer to the start of the vector
#	a1 (int)  is the # of elements in the vector
# Returns:
#	a0 (int)  is the first index of the largest element
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 77.
# =================================================================
argmax:

    li t2, 1
    blt a1, t2, error_exit

    lw t0, 0(a0)
    mv t1, a1
    mv t4, x0

loop_start:
    beq a1, x0, loop_end
    lw t3, 0(a0)
    bge t0, t3, loop_continue
    mv t0, t3
    sub t4, t1, a1

loop_continue:
    addi a0, a0, 4
    addi a1, a1, -1
    j loop_start

loop_end:
    mv a0, t4
    ret

error_exit:
    li a1, 77
    j exit2 #I don't know which function I should call here.