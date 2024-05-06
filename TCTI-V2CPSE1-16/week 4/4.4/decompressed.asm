.global _start
.cpu cortex-m0
.text
.align 2

_start:
	push { lr }
	
	// pointer to start msg/buff
	ldr r0, =msg
	ldr r1, =buff
	bl hwlib_cout
	pop { pc }

hwlib_cout: 
	push { r4, r5, lr}
	
	// copy start of pointer msg/buff
	mov r4, r0
	mov r5, r1
loop:
	// get char (byte (of msg)) in r0
	ldrb r0, [ r4 ]

	// check '\0'
	add r0, r0, #0
	beq end_loop

	//check '@'
	cmp r0, #64
	bne go
	bl decom
go:
	strb r0, [ r5 ]
	bl print_char

	// increment pointers msg/buff
	add r4, r4, #1
	add r5, r5, #1
	b loop
end_loop:
	pop { r4, r5, pc }

decom:
	//offset (first char after '@')
	add r4, r4, #1
	ldrb r1, [ r4 ]
	sub r1, r1, #47

	//length (second char after '@')
	add r4, r4, #1
	ldrb r7, [ r4 ]
	sub r7, r7, #48
	
	mov r6, r5

	//pointer substracted with offset
	sub r6, r6, r1



decom_loop:
	ldrb r0, [ r6 ]
	strb r0, [ r5 ]

	bl print_char	

	//increment (copied)buff pointer
	add r6, r6, #1
	
	//decrement length
	sub r7, r7, #1

	// check legnth = 0?
	cmp r7, #0
	beq go
	
	// increment buff pointer
	add r5, r5, #1
	b decom_loop

.bss
buff:
.skip 4100