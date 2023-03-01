 # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,1000
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
  #
hexasc: 
	andi	$a0,$a0,0xF
	
	addi	$v0,$a0,0x30
	
	bge 	$a0,10,letters
	nop
	
	jr	$ra
	nop
	
	letters:
		addi	$v0,$v0,7
delay:
  
 	bgt  $a0, $0, while_loop
 	nop
  
	jr	$ra
	nop
  		
  	while_loop:
  		addi	$a0,$a0,-1
  		move	$t0,$0
  		
  		test:
  		
  		blt 	$t0,50,for_loop
  		nop
  		
  		j	delay
  		nop
  			
  			for_loop:
  				addi	$t0,$t0,1
  				
  				j	test
  				nop
  	
  	

time2string:
	
	PUSH 	($s0)
	PUSH	($s1)
	PUSH 	($ra)
	
	move	$s1,$a0
	move	$s0,$a1
	
	# First digit, minutes
	srl 	$s0,$a1,12
	andi	$s0,$s0,0xF
	move	$a0,$s0
	jal 	hexasc
	nop
	sb	$v0,0($s1)
	
	# Second digit, minutes
	srl	$s0,$a1,8
	andi	$s0,$s0,0xF
	move	$a0,$s0
	jal	hexasc
	nop
	sb	$v0,1($s1)
	
	# Colon character
	li	$s0,0x3a
	sb	$s0,2($s1)
	
	# First digit, seconds
	srl	$s0,$a1,4
	andi	$s0,$s0,0xF
	move	$a0,$s0
	jal	hexasc
	nop
	sb	$v0,3($s1)
	
	# Second digit, seconds
	move	$s0,$a1
	andi	$s0,$s0,0xF
	move	$a0,$s0
	jal 	hexasc
	nop
	sb	$v0,4($s1)
	
	# Null byte
	li	$s0,0x00
	sb	$s0,5($s1)
	
	#surprise
	lb 	$t0, 0($s1)
	lb	$t1, 1($s1)
	lb	$t2, 3($s1)
	lb	$t3, 4($s1)
	
	beq 	$t0, $t1, seconds
	nop

	POP	($ra)
	POP	($s1)
	POP	($s0)	
	jr	$ra
	nop
	
	seconds:
	beq	$t2, $t3, minutes_equal_zero
	nop
	
	POP	($ra)
	POP	($s1)
	POP	($s0)	
	jr	$ra
	nop
	
	minutes_equal_zero:
	beq	$t0, 0x30, seconds_equal_zero
	nop
	
	POP	($ra)
	POP	($s1)
	POP	($s0)	
	jr	$ra
	nop
	
	seconds_equal_zero:
	beq	$t2, 0x30, hour
	nop
	
	POP	($ra)
	POP	($s1)
	POP	($s0)	
	jr	$ra
	nop
	
	
	
	hour: 
	li	$s0, 0x48
	sb	$s0, 0($s1)
	li	$s0, 0x4f
	sb	$s0, 1($s1)
	li	$s0, 0x55
	sb	$s0, 2($s1)
	li	$s0, 0x52
	sb	$s0, 3($s1)
	li	$s0, 0x00
	sb	$s0, 4($s1)
	
	#surprise
	
	POP	($ra)
	POP	($s1)
	POP	($s0)
	
	
	jr	$ra
	nop