### Siddhesh Mahadeshwar
### Username: sdmahade
### Program Description: This program implements and handles a singly-linked list and deals with the data stored
###						 within. 0 calls the first node of the list. 1 calls the entire list. 2 asks for the 
###						 part number memory address, then asks for a change to the quantity, and makes the change. The
###						 updated quanity will be displayed. If the updated quantity total is invalid/less than 0, 
###						 just 0 will be the new quantity.
###						 Each node holds the location to the next node unless it is the last, holds the part number,
###						 quantity, and description. 

### START MAIN, DO NOT MODIFY ###
			.text
mainLoop:			
			li			$v0, 5						# Read integer command from user
			syscall

			bltz		$v0, mainDone				# Negative number ends program
			beq 		$v0, $0, mainFirst			# Command 0 = print first node 	
			addi		$v0, $v0, -1
			beq 		$v0, $0, mainList			# Command 1 = print entire list
			addi		$v0, $v0, -1
			beq 		$v0, $0, mainUpdate			# Command 2 = update item
			
			la			$a0, strInvalid				# Print linked list from first node
			li			$v0, 4
			syscall		
			
mainEnd:
			li      	$v0, 11      				# Print a linefeed
			addi    	$a0, $0, 10 
			syscall
			
			b			mainLoop

mainFirst:
			# Print just the first node
			la			$a0, strFirst				
			li			$v0, 4
			syscall		
			
			la			$a0, first					
			jal			printNode
			b			mainEnd
									
mainList:
			# Print linked list from the first node
			la			$a0, strList				
			li			$v0, 4
			syscall		
			
			la			$a0, first					
			jal			printList
			b			mainEnd
			
mainUpdate:
			# Update a specific item
			li			$v0, 5						# Read part number
			syscall
			move		$a1, $v0					
			
			li			$v0, 5						# Read quantity delta
			syscall
			move		$a2, $v0
			
			la			$a0, strUpdate				
			li			$v0, 4
			syscall		

			la			$a0, first
			jal			updateItem
			
			move		$a0, $v0					# Print result from update procedure
			li			$v0, 1
			syscall
			
			b			mainEnd

mainDone:
			# Terminate execution
			li			$v0, 10						
			syscall
			
			.data
strInvalid:	.asciiz "Invalid command!"
strFirst:   .asciiz "First  : "
strList:    .asciiz "Items  : "
strUpdate:	.asciiz "Update : "
			
			.text
### END MAIN ###

############################################################
# Prints the part number, description, and quantity
# of a given node in the list. Example output: 
#  "#955288 Buzz Lightyear (21)"
# Parameters : $a0 - address of node to print
# Returns    : n/a
############################################################
printNode:
			li 			$t0, 0					# temporary value
			li 			$t1, 0					# temporary 0 value
			move 		$t2, $a0				# move contents of $a0 to $t2
			move 		$t3, $a0				# temp holder of initial a0
			
			printHash:
			# print out the hash "#" symbol through ascii
			li 			$v0, 11				
			addi 		$a0, $0, 35
			syscall
			
			lw 			$t1, 4($t2)				# store value of second word
			
			printPartNumber:		
			# print out the result (first word)
			move 		$a0, $t1				# move contents of t1 into a0
			li 			$v0, 1
			syscall
			
			# print a space
    		li      	$v0, 11     			# syscall 11 prints character in $a0
    		addi    	$a0, $0, 32  			# ASCII code 32 is a space
   		 	syscall
			
			la 			$t1, 12($t2)			# address of 4th word stored in t1 address
			
			printName:
			# print out the result (second word)
			move 		$a0, $t1				# move contents of t1 into a0
			li 			$v0, 4
			syscall
			
			# print a space
    		li      	$v0, 11     			# syscall 11 prints character in $a0
    		addi    	$a0, $0, 32  			# ASCII code 32 is a space
   		 	syscall
			
			lw			$t1, 8($t2)             # load the third word into t1 register
			
			printOpenParenthesis:
			# print out "(" from ascii table of values
			li 			$v0, 11
			addi		$a0, $0, 40
			syscall
			
			# print out the result (third word)
			move 		$a0, $t1				# move contents of t1 into a0
			li 			$v0, 1
			syscall
			
			printCloseParenthesis:
			# print out ")" from ascii table of values
			li 			$v0, 11
			addi		$a0, $0, 41
			syscall
			
			# print a space
    		#li      	$v0, 11     			# syscall 11 prints character in $a0
    		#addi    	$a0, $0, 32  			# ASCII code 32 is a space
   		 	#syscall
			
			move 		$a0, $t3				# restore initial value of a0 from temp variable t3
			jr 			$ra
			
			
						
############################################################
# Prints list of items from given starting node in null 
# terminated linked list. Each node is printed via printNode
# procedure. Items separated by a comma and space.
#  
# Parameters : $a0 - address of node to start printing from
# Returns    : n/a
############################################################
printList:
			li 			$t8, 0					# temp register for $ra
			move		$t8, $ra				# more $ra into $t8
			li      	$t7, 0					# temp register for a0
			li 			$t4, 0					# initialize temp variable to be manipulated
			move 		$t5, $a0				# stores the a0 value temporarily
			la			$t4, 0($a0)				# load word at a0
			
printList2:
			move    	$t7, $a0
			jal 	 	printNode				# jump and link to printNode
			
			
			#move 		$a0, $t7
			lw 			$a0, 0($t7)
			beq			$a0, -1, end
			
		
			# print out a comma
			li 			$v0, 11
			addi		$a0, $0, 44
			syscall
			
			#print a space
    		li      	$v0, 11     			# syscall 11 prints character in $a0
    		addi    	$a0, $0, 32  			# ASCII code 32 is a space
   		 	syscall
			
			move 		$a0, $t7				# move temp stored $t7 back into $a0
			
			lw 			$a0, 0($a0)				# load address from first node
			la			$t4, 0($a0)				# load word at a0
			beq			$a0, -1, end			# if a0 is -1, we are at the last node, so exit loop
			b 			printList2
			
			end:	
			move 		$ra, $t8				# restore value of $ra
			jr			$ra						# jump register 
			
			
			
			

############################################################
# Finds the first item in the list matching a part  
# number and changes its quanity by a certain amount.
# Quantity is not allowed to go below 0.
#
# Parameters : $a0 - address of first node in list
#              $a1 - part number to match
#              $a2 - delta to apply to quantity
# Returns    : $v0 - new quantity, -1 if item not found
############################################################
updateItem:
			
			move 		$t2, $a0				# move contents of a0 into t2

loop:
			move		$t2, $a0				# move contents of a0 into t2
			lw 			$t9, 4($t2)				# load word "part number"
			beq			$t9, $a1, endLoop		# if "part number" == number to matc, jump to endLoop
			lw 			$a0, 0($a0)				# load address from first node
			la			$t4, 0($a0)				# load word at a0
			bne	 		$a0,-1, loop			# branch back to loop if address not equal to -1
			b			endEndLoop				# otherwise, branch unconditionally to endEndLoop
endLoop:
			lw 			$t9, 8($t2)				# load word "quantity"
			add			$a2, $a2, $t9			# add quantity with updated quantity changes
			blt         $a2, 0, exception		# if changed quantity is less than 0, branch to handle exception
			b			continue				# otherwise, branch unconditionally to continue
exception:
			move		$a2, $zero				# move 0 into changed quantity
continue:
			sw			$a2, 8($t2)				# store word
			move 		$v0, $a2				# move changed quantity into v0
			jr 			$ra

endEndLoop:
			li			$v0, -1					# return the updated value
			jr			$ra
											
### START DATA ###
# You can (and should!) modify the linked list in order to test your procedures.
# However, the first node should retain the label first.
.data
first:  	.word     	node2       				# Next pointer
			.word     	955288	     				# Part number
			.word     	21							# Quantity
        	.asciiz   	"Buzz Lightyear" 			# Description
        
node2:		.word     	node3
			.word     	955285
			.word     	2
        	.asciiz   	"Genie"

node3:  	.word     	-1
			.word     	951275
			.word     	5
        	.asciiz   	"Chick-Fil-A Cow"
### END DATA ###
		
		
