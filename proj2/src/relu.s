.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
# 	a0 (int*) is the pointer to the array
#	a1 (int)  is the # of elements in the array
# Returns:
#	None
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 78.
# ==============================================================================
relu:
    # Check if length <= 0
    li t1, 1
    blt a1, t1, error_exit

loop_start:
    beq a1, x0, loop_end
    lw t0, 0(a0)
    bge t0, x0, skip_update  # If >= 0, skip updating
    sw x0, 0(a0)

skip_update:
    addi a0, a0, 4
    addi a1, a1, -1
    j loop_start

loop_end:
    ret

error_exit:
    li a1, 78
    j exit2  # Assuming exit2 is a function to terminate with error code