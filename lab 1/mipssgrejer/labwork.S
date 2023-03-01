  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #
  .global hexasc, delay, time2string
.text
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
  		
  		blt 	$t0,1500,for_loop
  		nop
  		
  		j	delay
  		nop
  			
  			for_loop:
  				addi	$t0,$t0,1
  				
  				j	test
  				nop
  	
  	

time2string:
	
	PUSH 	"$s0"
	PUSH	"$s1"
	PUSH 	"$ra"
	
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

	POP	"$ra"
	POP	"$s1"
	POP	"$s0"	
	jr	$ra
	nop
	
	seconds:
	beq	$t2, $t3, minutes_equal_zero
	nop
	
	POP	"$ra"
	POP	"$s1"
	POP	"$s0"	
	jr	$ra
	nop
	
	minutes_equal_zero:
	beq	$t0, 0x30, seconds_equal_zero
	nop
	
	POP	"$ra"
	POP	"$s1"
	POP	"$s0"	
	jr	$ra
	nop
	
	seconds_equal_zero:
	beq	$t2, 0x30, hour
	nop
	
	POP	"$ra"
	POP	"$s1"
	POP	"$s0"	
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
	
	POP	"$ra"
	POP	"$s1"
	POP	"$s0"
	
	
	jr	$ra
	nop