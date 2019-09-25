	# Siddhesh Mahadeshwar
    # Username: sdmahade
    # The program takes in non-negative inputs from the user and continues to do so until a negative integer is entered.
    # When a negative integer is entered, the program will output the minimum number, maximum number, the number of even 
    # numbers, the number of odd numbers, and the sum of all squared values of each inputed integer
    
    .text
    li 			$t0, 0 					# reg. location for the smallest number in the sequence
    li 			$t1, 0 					# reg. location for the largest number in the sequence
    li 			$t2, 0					# reg. location for the count of integers that were even
    li 			$t3, 0					# reg. location for the count of integers that were odd
    li 			$t4, 0					# reg. location for the the sum of the squared value of each of the integers
    li 			$t5, 0 					# reg. location for temporary values for comparison
    li 			$t6, 0					# permenant 0  register
    li 			$t7, 0					# temp
    li			$s0, 0					# indexing for .data 
    li 			$s1, 0					# temp register
    li 			$s2, 2					# register to hold 2 for mod function
    li 			$s3, 0					# temp for mflo
    
    li			$v0, 5					# asks for int input
    syscall		
    move 		$t0, $v0				# moves the input to the smallest number register 
    move		$t1, $v0				# moves the input to the largest number register
    move		$t5, $v0				# moves the input to the temporary register
    bltz 		$t5, endComplete  		# checks if the input is negative
   	b 			temp
    
    
    loop:
    
    # Reads an integer from the user
    li 			$v0, 5					# syscall 5 requests reading an integer, placing result in $v0 
    syscall
    move		$t5, $v0  				# Read in number should now be copied into $t5

    temp:
    blt 		$t5, $t6, done  		# checks if the input is negative
    mult 	 	$t5, $t5				# squares the input value
    mflo		$s1						# stores the quotient in this register
    add 		$t4, $t4, $s1			# adds the contents of squares values register with new squared values
   
    bgt 		$t5, $t1, max			# checks if input is larger or equal to current Min. If yes, move to Max label
    ble 		$t5, $t0, min			# checks if input is smaller or equal to current Max, If yes, move to Even label
    b			test
    
    
    # label to handle the minimum number operations
    min: 
     move		$t0, $t5				# input is smaller than Min, so replace Min with input
    b 			test					# branch to the test label
    
    
    # label to handle the maximum numbers
    max:
    move		$t1, $t5				# input is larger than Max, so replace Max with input
    
    # label to test if the input is odd or even
    test:
    div			$t5, $s2				# diving input by 2
    mfhi 		$s3						# send remainder to temp register
    beqz  		$s3, even				# if s3 holds a zero, the number is even
    b 			odd

    # label to handle even numbers
    even:
    add		$t2, $t2, 1					# increments the count of even numbers by 1
    b 			loop

    # label to handle odd numbers
  	odd:
  	add		$t3, $t3, 1					# increments the count of odd numbers by 1
    b 			loop
    
    # label to terminate the program immediately
    endComplete:
   	li 			$v0, 10 			
   	syscall
    
    
    done:
    # printing min value
    li 			$v0, 1					# print int
    addi 		$a0, $t0, 0				# the int that I want to print
    syscall 	
    #Line feed code
    li $v0, 11
    addi $a0, $0, 0xA
    syscall
    
    
    #printing max value					
    li 			$v0, 1					# print int
    addi 		$a0, $t1, 0				# the int that I want to print
    syscall 	
    #Line feed code
    li $v0, 11
    addi $a0, $0, 0xA
    syscall
    
    
    # printing number of even numbers
    li 			$v0, 1					# print int
    addi 		$a0, $t2, 0				# the int that I want to print
    syscall 	
    #Line feed code
    li $v0, 11
    addi $a0, $0, 0xA
    syscall
    
    
    #printing number of odd numbers				
    li 			$v0, 1					# print int
    addi 		$a0, $t3, 0				# the int that I want to print
    syscall 	
    #Line feed code
    li $v0, 11
    addi $a0, $0, 0xA
    syscall
    
    				
    # printing sum of all inputs squared 		
    li 			$v0, 1					# print int
    addi 		$a0, $t4, 0				# the int that I want to print
    syscall 	
    #Line feed code
    li $v0, 11
    addi $a0, $0, 0xA
    syscall
    		
    .data 
    .align 2
    