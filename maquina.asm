.data
n: .space 4
newline: .asciiz "\n"

.text
.globl main

main:
li $v0, 5
syscall
move $t1, $v0

sw  $t1, n

L1: 

lw $t1, n
li $t2, 1
slt  $t3, $t2, $t1

beq  $t3, $zero, L2

lw $t1, n
li $t2, 2
rem  $t3, $t1, $t2

li $t1, 0
subu  $t2, $t3, $t1
sltu  $t2, $zero, $t2
xori  $t2, $t2, 1

beq  $t2, $zero, L3

lw $t1, n
li $t2, 2
div  $t3, $t1, $t2

sw  $t3, n

j L4

L3: 

li $t1, 3
lw $t2, n
mul  $t3, $t1, $t2

li $t1, 1
add  $t2, $t3, $t1

sw  $t2, n

L4: 

lw $t1, n
li $v0, 1
move $a0, $t1
syscall
li $v0, 4
la $a0, newline
syscall

j L1

L2: 

