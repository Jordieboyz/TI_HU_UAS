.global print_asciz
.global application
.cpu cortex-m0
.text
.align 1

print_asciz:
	push { r5, lr }
	mov r5, r0
PrintLoop:
	ldrb r0, [ r5 ]
	add r0, r0, #0
	beq printDone
	mov r1, r0
	b upperCheck1
printChar:
	bl  uart_put_char
	add r5, r5, #1
	b   PrintLoop
printDone: 
	pop { r5, pc }


upperCheck1:
	cmp r1, #122
	bls upperCheck2
	b lowerCheck1
upperCheck2:
	cmp r1, #97
	bge upperCase
	b lowerCheck1
upperCase: 
	sub r0, #32
	b printChar

lowerCheck1:
	cmp r1, #90
	bls lowerCheck2
	b printChar
lowerCheck2:
	cmp r1, #65
	bge lowerCase
	b printChar
lowerCase:
	add r0, #32
	b printChar
	
application:
   push { lr }
   bl print_asciz
   pop { pc }

