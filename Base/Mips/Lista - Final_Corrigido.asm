.data

array: .space 72

separa: .asciiz "\n-----------------------------\n"

opcao: .space 4
apreAp: .asciiz "\n\n--- Opcoes: Inserir(1), Remover por Atributo(2), Remover por Indice(3), Localizar por Atributo(4), Imprimir(5), Exit(6) --- "
digOpAp: .asciiz "\nDigite sua opcao: "
opInvAp: .asciiz "\nOpcao Invalida!"

nomePes: .space 8
tamNomePes: .byte 8
newline: .asciiz "\n"

id: .space 16
tamId: .byte 4
nome: .space 24
tamNome: .byte 8
salario: .space 8
preenchaAp: .asciiz "\nPreencha os Campos!"
idAp: .asciiz "\nID: "
nomeAp: .asciiz "\nNome: "
salarioAp: .asciiz "\nSalario: "

confAp: .asciiz "\nDeseja realmente fazer isto? Sim(1) ou Nao(0)?"

indice: .space 4
indiceAp: .asciiz "\nDigite o indice: "

atributo: .space 8
atributoAp: .asciiz "\nDigite o id ou nome: "

sucessoAp: .asciiz "\nSucesso!"
naoEncAp: .asciiz "\nN�o encontrado!"
semSpaAp: .asciiz "\nSem Espaco!"
existeSimAp: .asciiz "\nExiste!"
existeNaoAp: .asciiz "\nNao Existe!"



.text 

.globl main

main:
	li $v0, 4
	la, $a0, apreAp
	syscall
	
	li $v0, 4
	la, $a0, digOpAp
	syscall
	
	li $v0, 5
	syscall

	add $t0, $zero, $v0
	
	beq $t0, 1, LPI1
	beq $t0, 2, LPI2
	beq $t0, 3, LPI3
	beq $t0, 4, LPI4
	beq $t0, 5, LPI5
	beq $t0, 6, LPI6
	
	li $v0, 4
	la, $a0, opInvAp
	syscall
	
	j main
	
	LPI1:
		la $a0, array
		add $a1, $zero, $t0
		jal inserir
		
		j main
	LPI2:
		li $v0, 4
		la $a0, atributoAp
		syscall
		
		li $v0, 8
		la $a0, nomePes
		lb, $a1, tamNomePes
		syscall
		
		la $a0, array
		add $a1, $zero, $t0
		jal removerPorAtrib
		
		j main
	LPI3:
		li $v0, 4
		la $a0, indiceAp
		syscall
		
		li $v0, 5
		syscall
	
		add $a3, $zero, $v0
		la $a0, array
		add $a1, $zero, $t0
		jal removerPorIndice
		
		j main
	LPI4:
		
		li $v0, 4
		la $a0, atributoAp
		syscall
		
		li $v0, 8
		la $a0, nomePes
		lb, $a1, tamNomePes
		syscall

		la $a0, array
		add $a1, $zero, $t0
		jal localizarPorAtrib
		
		j main
	LPI5:
		la $a0, array
		add $a1, $zero, $t0
	 	jal imprimir
	 	
	 	j main
	LPI6:	
		la $a0, array
		add $a1, $zero, $t0
		jal exit
		
		j main
		
inserir:

	addi $sp, $sp, -4
	sw $ra, 0($sp)

	jal percorrer
	
	lw $ra, 0($sp)
	
	li $t0, 0
	li $t1, 0
	add $t0, $zero, $v0
	add $t1, $zero, $v1
	
	beqz $t1, LI1
	
	li $t2, 0
	li $t3, 0
	mul $t2, $s0, 5
	mul $t3, $s0, 8
	
	li $v0, 4
	la $a0, preenchaAp
	syscall
	
	li $v0, 4
	la $a0, idAp
	syscall
	
	li $v0, 8
	la $a0, id($t2)
	lb $a1, tamId
	syscall
	li $s0, 0x0A		# atribui \n a $s6
	sb $s0, 3($a0)		# add \n no final da string id 

	sw $a0, 4($t0)
	
	
	
	li $v0, 4
	la $a0, nomeAp
	syscall
	
	li $v0, 8
	la $a0, nome($t3)
	lb $a1, tamNome
	syscall
	sw $a0, 8($t0)
	
	li $v0, 4
	la $a0, salarioAp
	syscall
	
	li $v0, 7
	syscall
	s.d $f0, 16($t0)
	
	
	li $t4, 1
	sw $t4, 0($t0)
	
	li $v0, 4
	la $a0, sucessoAp
	syscall
	
	addi $sp, $sp, 4
	jr $ra
	
	LI1:
	
	li $v0, 4
	la $a0, semSpaAp
	syscall
	
	addi $sp, $sp, 4
	jr $ra
	
	
	
removerPorAtrib:

	addi $sp, $sp, -4
	sw $ra, 0($sp)

	jal percorrer
	lw $ra, 0($sp)
	
	add $t0, $zero, $v0
	add $t1, $zero, $v1
	
	beqz $t1, LRA1
	
	sw $ra, 0($sp)
	
	add $a0, $zero, $t0
	jal print
	lw $ra, 0($sp)
	
	li $v0, 4
	la, $a0, confAp
	syscall
	
	li $v0, 5
	syscall

	add $s5, $zero, $v0
	
	beqz $s5, main
	
	li $t2, 0
	sw $t2, 0($t0)
	
	li $v0, 4
	la $a0, sucessoAp
	syscall
	
	addi $sp, $sp, 4
	jr $ra
	
	LRA1:
	
	li $v0, 4
	la $a0, naoEncAp
	syscall
	
	addi $sp, $sp, 4
	jr $ra

removerPorIndice:

	addi $sp, $sp, -4
	sw $ra, 0($sp)
	
	jal percorrer
	lw $ra, 0($sp)
	
	add $t0, $zero, $v0
	add $t1, $zero, $v1
	
	beqz $t1, LRI1
	
	sw $ra, 0($sp)
	
	add $a0, $zero, $t0
	jal print
	lw $ra, 0($sp)
	
	li $v0, 4
	la, $a0, confAp
	syscall
	
	li $v0, 5
	syscall

	add $s5, $zero, $v0
	
	beqz $s5, main
	
	li $t2, 0
	sw $t2, 0($t0)
	
	li $v0, 4
	la $a0, sucessoAp
	syscall
	
	addi $sp, $sp, 4
	jr $ra
	
	LRI1:
	
	li $v0, 4
	la $a0, naoEncAp
	syscall
	
	addi $sp, $sp, 4
	jr $ra

localizarPorAtrib:
	
	addi $sp, $sp, -4
	sw $ra, 0($sp)

	jal percorrer
	
	lw $ra, 0($sp)
	
	add $t0, $zero, $v0
	add $t1, $zero, $v1
	
	beqz $t1, LLA1
	
	li $v0, 4
	la $a0, existeSimAp
	syscall
	
	addi $sp, $sp, 4
	jr $ra
	
	LLA1: 
	
	li $v0, 4
	la $a0, existeNaoAp
	syscall
	
	addi $sp, $sp, 4
	jr $ra
	
imprimir:
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	
	jal percorrer
	
	lw $ra, 0($sp)
	addi $sp, $sp, -4
	
	jr $ra


comparaString:
	
	li $s4, 0
	li $s5, 0
	li $t6, 1
	LC1:
	lb $s4, 0($a0)
	lb $s5, 0($a1)
	
	beq $s4, $zero, LC3
	beq $s5, $zero, LC3
	beq $s4, $s5, LC2
	li $t6, 0
	LC2:
	addi $a0, $a0, 1
	addi $a1, $a1, 1
	j LC1
	LC3:
	add $v0, $zero, $t6
	jr $ra
	
	
	
percorrer:
	addi $sp, $sp, -12
	sw $a0, 0($sp)
	sw $a1, 4($sp)
	sw $ra, 8($sp)
	
	li $t0, 0
	li $t1, 0
	li $t2, 0
	li $t3, 0
	li $t4, 0
	li $v0, 0
	li $v1, 0
	add $s7, $zero, $a0
	LP1:	
	subi $t2, $t1, 3
	bgez $t2, LP3
	mul $t3, $t1, 24
	add $t3, $s7, $t3
	
	beq $a1, 1, lugVazio
	beq $a1, 2, encontraAtrib
	beq $a1, 3, encontraIndice
	beq $a1, 4, encontraAtrib
	beq $a1, 5, imp
	
	LP2:
	addi $t1, $t1, 1
	j LP1
	
	LP3: 
	addi $sp, $sp, 12
	jr $ra
	
	lugVazio:
		lw $t4, 0($t3)
		bne $t4, 0, LP2
		
		add $v0, $zero, $t3
		li, $v1, 1 
		add $s0, $zero, $t1
		j LP3
		
	imp:
		lw $t4, 0($t3)
		bne $t4, 1, LP2
		
		add $a0, $zero, $t3
		jal print
		
		lw $a0, 0($sp)
		lw $a1, 4($sp)
		lw $ra, 8($sp)

		
		j LP2
		
	encontraAtrib:
		
		lw $t4, 0($t3)
		bne $t4, 1, LP2
		
		li $a1, 0
		
		la $a0, nomePes
		lw $a1, 8($t3)
		jal comparaString	
		
		lw $a0, 0($sp)
		lw $a1, 4($sp)
		lw $ra, 8($sp)

		bnez $v0, LP4
		
		la $a0, nomePes
		lw $a1, 4($t3)
		jal comparaString
	
		lw $a0, 0($sp)
		lw $a1, 4($sp)
		lw $ra, 8($sp)
			
		beqz $v0, LP2
		
		LP4:
		li $v1, 1
		add $v0, $zero, $t3 
		
		j LP3
		
	encontraIndice:
	
		lw $t5, 0($t3)
		bne $t5, 1, LP2
		
		seq $t4, $t0, $a3
		addi $t0, $t0, 1
		
		bne $t4, 1, LP2
		
		li $v1, 1
		add $v0, $zero, $t3 
		
		j LP3
	
	

	
exit: 
	li $v0,10
	syscall
	
print:

	add $t0, $zero, $a0

	li $v0, 4
	la $a0, separa
	syscall
		
	li $v0, 4
	la $a0, idAp
	syscall
	li $v0, 4
	lw $a0, 4($t0)
	syscall
		
	li $v0, 4
	la $a0, nomeAp
	syscall
	li $v0, 4
	lw $a0, 8($t0)
	syscall
		
	li $v0, 4
	la $a0, salarioAp
	syscall
	li $v0, 3
	l.d $f12, 16($t0)
	syscall
		
	li $v0, 4
	la $a0, separa
	syscall
	
	jr $ra
	
	
