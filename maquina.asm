.data
p: .space 4
d: .space 4
newline: .asciiz "\n"

.text
.globl main

main:
	li $t2, 5
	move $a0, $t2
	jal f_cd
	move  $t1, $v1

	sw  $t1, p

	li $t1, 3
	lw $t2, p
	mul  $t3, $t1, $t2

	li $v0, 1
	move $a0, $t3
	syscall
	li $v0, 4
	la $a0, newline
	syscall

	li $v0,10
	syscall

f_cd: 
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	sw  $a0, d

	lw $t1, d
	li $t2, 2
	mul  $t3, $t1, $t2

	move $v1, $t3
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	jr $ra

