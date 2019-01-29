.data
n: .space 4
newline: .asciiz "\n"

.text
.globl main

main:
        li $t1, 3
        li $t3, 5
        move $a0, $t3
        jal f_cd
        move  $t2, $v1

        mul  $s2, $t1, $t2

        li $v0, 1
        move $a0, $s2
        syscall
        li $v0, 4
        la $a0, newline
        syscall

        li $v0,10
        syscall

f_cd:
        addi $sp, $sp, -16
        sw $ra, 0($sp)
        sw $t1, 4($sp)
        sw $t2, 8($sp)
        sw $t3, 12($sp)
        sw  $a0, n

        lw $t1, n
        li $t2, 2
        mul  $s1, $t1, $t2

        move $v1, $s1
        lw $ra, 0($sp)
        lw $t1, 4($sp)
        lw $t2, 8($sp)
        lw $t3, 12($sp)
        addi $sp, $sp, 16
        jr $ra