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
    # Base case: if a0 == 0, return 1
    beq a0, x0, base_case

    # Recursive case: save state and call factorial(a0 - 1)
    addi sp, sp, -8          # Allocate space on the stack
    sw s0, 4(sp)             # Save old value of s0
    sw ra, 0(sp)             # Save return address
    mv s0, a0                # Save current a0 (n)
    addi a0, a0, -1          # Prepare for factorial(n-1)
    jal ra, factorial        # Recursive call

    # After returning from recursion, restore state and compute result
    mul a0, a0, s0           # Multiply result by original n
    lw s0, 4(sp)             # Restore old s0
    lw ra, 0(sp)             # Restore return address
    addi sp, sp, 8           # Deallocate space on the stack
    jr ra                    # Return to caller

base_case:
    li a0, 1                 # Return 1 for factorial(0)
    jr ra                    # Return to caller