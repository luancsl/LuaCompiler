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

        lw $t2, n
        move $a0, $t2
        jal f_fac
        move  $t1, $v1

        li $v0, 1
        move $a0, $t1
        syscall
        li $v0, 4
        la $a0, newline
        syscall

        li $v0,10
        syscall

f_fac:
        addi $sp, $sp, -16
        sw $ra, 0($sp)
        sw $t1, 4($sp)
        sw $t2, 8($sp)
        sw $t3, 12($sp)
        sw  $a0, n

        lw $t1, n
        li $t2, 1
        sltu  $t3, $t1, $t2
        xori $t3, $t3, 1

        beq  $t3, $zero, L1

        lw $t1, n
        lw $t3, n
        li $t4, 1
        sub  $t5, $t3, $t4

        move $a0, $t5
        jal f_fac
        move  $t2, $v1

        mul  $s1, $t1, $t2

        move $v1, $s1
        lw $ra, 0($sp)
        lw $t1, 4($sp)
        lw $t2, 8($sp)
        lw $t3, 12($sp)
        addi $sp, $sp, 16
        jr $ra

        j L2

L1:
        li $t1, 1
        move $v1, $t1
        lw $ra, 0($sp)
        lw $t1, 4($sp)
        lw $t2, 8($sp)
        lw $t3, 12($sp)
        addi $sp, $sp, 16
        jr $ra

L2: