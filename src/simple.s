.globl main

.data
m1:	.word 6
m2:	.word 5
m3:	.word 0

.text
main:
		
	la		$t0, m1
	lw		$t2, 0($t0)
	la		$t0, m2
	lw		$t0, 0($t0)
	li		$t3, 1
	li		$t1, 0
lab:		
	add		$t1, $t1, $t2
	sub		$t0, $t3, $t0
	addi		$t3, $t3, 1
	b		lab
	la		$t0, m3
	sw		$t1, 0($t0)
	nop		
