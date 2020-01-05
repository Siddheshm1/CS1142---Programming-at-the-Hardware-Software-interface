	# Siddhesh Mahadeshwar
	# Username: sdmahade
	# Program Description: This program takes in dimensions and the number of vectors that the user would
	#                      like to work with. It then takes in the values to fill in these vectors and then
	#                      adds the vectors that has been asked for by the user. The program can continue to
	#					   run until there is an invalid input.


	.text
	li $t0, 0 										# first integer input: D
	li $t1, 0 										# second integer input: N
	li $t2, 0										# temp register for mflo
	la $t3, 0 										# input word register (temp)
	li $t4, 0										# counter for D
	li $t5, 0										# first index input
	li $t6, 0										# mflo for D*N
	li $t7, 0 										# second index input
	li $t8, 4										# constant 4 value register
	li $t9, 0										# adding contents of vectors
	la $s0, nums
	li $s1, 0										# lw for vector 1
	li $s2, 0										# lw for vector 2
	li $s3, 1 										# constant 1 value register
	li $s4, 999										# constant 1000 value register
	la $s5, 0										# index register for data array
	la $s6, 0										# mflo for second index input
	la $s7, 0										# mflo for first index input
	

	inputForDimensions:
	# takes in input for the first integer
	li 			$v0, 5
	syscall
	move 		$t0, $v0							# moves the input into register $t0
	blt 		$t0, $s3, terminate     			# checks if the first input is greater than 0

	# takes in input for the second integer
	li 			$v0, 5
	syscall
	move 		$t1, $v0							# moves the input into register $t1
	blt 		$t1, $s3, terminate     			# checks if the second input is greater than 0

	mult 		$t0, $t1							# multiply 2 inputs to confirm product is below 1000
	mflo 		$t2									# quotient of mult stored in temp register
	bgt    		$t2, $s4, terminate					# terminate if product is equal to 1000 or more
 	
 				
	loop:
	li 			$v0, 5								# asks the user for input
	syscall
	move 		$t3, $v0							# move the input to temporary storage register
	
	storeDValues:
	sw 			$t3, nums($s5)						# store value from input register to memory
	add			$s5, $s5, 4							# increase array index to make space for next input word
	ble			$s5, 4000, continueLoop				# if less than or equal to 1000 words/4000 space, next branch
	b 			terminate							# if more than 1000 words, terminate
	
	continueLoop: 
	mult 		$t1, $t0
	mflo		$t6
	add 		$t4, $t4, 1							# increase current index counter for D
	ble			$t4, $t6, loop

	outputPT3:
	# take in input for specifying the first index of the vector
	li 			$v0, 5
	syscall
	move 		$t5, $v0							# move input to register
	blt 		$t5, $zero, terminate				# terminate if less than zero
	bgt			$t5, $t1, terminate					# check if the input values are in range
	
	# take in input for specifying the second index of the vector
	li 			$v0, 5
	syscall
	move 		$t7, $v0							# move input to register		
	blt 		$t7, $zero, terminate				# terminate if less than zero
	bgt			$t7, $t1, terminate					# check if the input values are in range
	
	printingV1:
	mult 		$t5, $t8							# multiply first input by 4 to reach vector memory location
	mflo		$s7									# store mflo in register
	mult 		$s7, $t0							# multiply previous total by dimension for correct memory location
	mflo		$s7									# store mflo in same register as before
	
	printingV2:
	mult 		$t7, $t8							# multiply second input by 4 to reach vector memory location
	mflo		$s6									# store mflo in register
	mult		$s6, $t0							# multiply previous total by dimension for correct memory location
	mflo		$s6									# store mflo in same register as before
	
	addingVectors:
	lw 			$s1, nums($s7)						# calling from memory: contents of location for first vector
	lw 			$s2, nums($s6)						# calling from memory: contents of location for second vector
	add			$t6, $t6, 4							# add 4 to memory location for first vector
    add			$t7, $t7, 4							# add 4 to memory location for second vector
	add 		$t9, $s1, $s2						# adding contents of the first int in both vectors
	

	
	printTotals:	
	
	move $a0, $t9
	li $v0, 1  										#print out the result
	syscall	
	
    #li 			$v0, 1							# print int
    #addi 		$a0, $t9, 0							# the int that I want to print
    #syscall 
    
    li      	$v0, 11     						# syscall 11 prints character in $a0
    addi    	$a0, $0, 32  						# ASCII code 32 is a space
    syscall
    
    move		$t4, $zero							# set counter to zero
    add			$t4, $t4, 1							# increment counter
    
    blt 		$t4, $t0, addingVectors
  
    
   

    blt			$t4, $t0, printingV1				# if counter less than D input, loop back
    
    li      	$v0, 11      						# syscall 11 prints character in $a0
    addi    	$a0, $0, 10  						# ASCII code 10 is a line feed
    syscall
    
    move        $s4, $zero							# set s4 to zero
    add 		$s4, $s4, 1							# increment counter for each iteration
    bgt			$s4, $t1, terminate					# terminate if counter greater than 1
    move 		$a0, $zero
    move 		$v0, $zero
    
    b outputPT3
    
	
	terminate:
	li $v0, 10
 	syscall
	

	.data
	.align 2
	nums: .space 4000 

