.data
fac: .space 4
n: .space 4

.text
.globl main

main:
li $v0, 5
syscall
move $t1, $v0

sw  $t1, n

li $t2, 1
sw  $t2, fac

L1: 

lw $t1, n
li $t2, 1
slt  $t3, $t2, $t1

beq  $t3, $zero, L2

lw $t3, fac
lw $t4, n
mul  $t5, $t3, $t4

sw  $t5, fac

lw $t1, n
li $t2, 1
sub  $t3, $t1, $t2

sw  $t3, n

j L1

L2: 

lw $t1, fac
li $v0, 1
move $a0, $t1
syscall

