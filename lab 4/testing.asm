main:
    add $t0, $zero, $zero     # $t0 = 0 (initialize product)
    addi $t1, $a0, -1         # $t1 = n - 1
loop:
    beq $t1, $zero, end_loop  # if n - 1 = 0, exit loop
    addi $t2, $a0, -1         # $t2 = n - 1
inner_loop:
    beq $t2, $zero, outer_loop # if n - 1 = 0, exit inner loop
    add $t0, $t0, $a0         # multiply product by n
    addi $t2, $t2, -1         # decrement inner loop counter
    j inner_loop              # jump to start of inner loop
outer_loop:
    add $v0, $t0, $a0         # multiply product by n
    j stop_loop               # jump to stop loop
end_loop:
    addi $v0, $a0, 5          # $v0 = n! (initialize result)
stop_loop:
    j stop_loop               # stop loop