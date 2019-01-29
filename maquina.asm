.data
fac: .space 4
p: .space 4
n: .space 4
newline: .asciiz "\n"

.text
.globl main

main:
	li $t2, 5
	move $a0, $t2
	jal f_fac
	sw  $v1, f_fac
	lw $t1, f_fac

	li $v0, 1
	move $a0, $t1
	syscall
	li $v0, 4
	la $a0, newline
	syscall

	li $v0,10
	syscall

f_fac: 
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	sw  $a0, n

	li $t1, 0
	sw  $t1, p

	lw $t1, n
	li $t2, 1
	sltu  $t3, $t1, $t2
	xori $t3, $t3, 1

	beq  $t3, $zero, L1

	j L2

L1: 
	li $t1, 1
	sw  $t1, p

L2: 
