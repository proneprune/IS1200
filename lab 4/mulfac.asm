	addi $a0, $0, 3 #set a0 = n
	add $v0, $0, $a0 #set v0 = a0
	beq $a0, $0, zero#check if n = 0
loop:
	addi $a0, $a0, -1 #set a0 to n-1
	beq $a0, $0, finished #checks if n =0 and breaks the loop
	mul $v0, $v0, $a0 #if n = 5 multiplies ((((5*4)*3)*2)*1)
	beq $0, $0, loop #loops back to loop
	
zero:
	addi $v0, $0, 1#if n =0 add 1

finished:
	beq $0, $0, finished