.globl main

.data
m1:	.word 6
m2:	.word 5
m3:	.word 0

.text
main:
		
	la		$t0, m1
	lw		$t3, 0($t0)
	la		$t0, m2
	lw		$t1, 0($t0)
	li		$t2, 1
	li		$t0, 0
lab:		
	add		$t0, $t0, $t3
	sub		$t0, $t2, $t1
	addi		$t2, $t2, 1
	b		lab
	la		$t0, m3
	sw		$t0, 0($t0)
	nop		
