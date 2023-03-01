	addi $a0, $0, 8 #set $a0 to n
	beq $a0, $0 zero #checks if n = 0
	add $v0, $0, $a0 #answer = n
	add $v1, $0, $a0 #$v1 = sum
	add $a2, $a0, $0 #$a2 = i i =n
	
loop:
	addi $a2, $a2, -1 #i =n-1 && i--
	add $v0, $0, $v1 #answer = sum
	beq $a2, $0, finished #for i =n-1; i>0
	add $v1, $0, $0 #sum = 0
	add $a3, $0, $0 #j = 0
inner_loop:
	beq $a3, $a2, loop#j =0; j<i
	add $v1, $v1, $v0 #sum+=answer
	addi $a3, $a3, 1 #j++
	
	beq $0, $0, inner_loop
						
zero:
	addi $v0, $0, 1	#if n = 0 adds 1	
finished:

stop:
	beq $0, $0, stop