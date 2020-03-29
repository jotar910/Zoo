// Nome: João Paulo Mendes Rodrigues | Número: 21260309

#include <stdio.h>
#include <stdlib.h>
#include "menus.h"

int MenuExtra() {
	int op;
	char st[2];
	printf("\t\t--- Menu Funcao Extra ---\n");
	printf("1 - Modo Normal\n");
	printf("2 - Modo Extra\n");
	printf("\n");
	do {
		printf("\nOpcao: ");
		scanf(" %s", st);
		op=atoi(st);
	} while (op < 1 || op > 2);
	printf("\n");
	if(op == 1)
		return 0;
	return 1;
}

int MenuAnimaisListagem() {
	int op;
	char st[2];
	printf("\n\n\t\t--- Menu Listar Animais ---\n");
	printf("1 - Listar Todos os Animais\n");
	printf("2 - Listar Animais de uma Area\n");
	printf("3 - Listar Animais de uma Especie\n");
	printf("4 - Listar Informacao Completa de um Animal\n");
	printf("5 - Voltar\n");
	printf("6 - Terminar\n");
	printf("\n");
	do {
		printf("\nOpcao: ");
		scanf(" %s", st);
		op=atoi(st);
	} while (op < 1 || op > 6);
	printf("\n");
	return op;
}

int MenuAnimais() {
	int op;
	char st[2];
	printf("\n\n\t\t--- Menu Animais ---\n");
	printf("1 - Listar Animais\n");
	printf("2 - Transferir Animais\n");
	printf("3 - Eliminar Animal\n");
	printf("4 - Nascimento de um Animal\n");
	printf("5 - Carregar Ficheiro de Animais\n");
	printf("6 - Voltar\n");
	printf("7 - Terminar\n");
	printf("\n");
	do {
		printf("\nOpcao: ");
		scanf(" %s", st);
		op=atoi(st);
	} while (op < 1 || op > 7);
	printf("\n");
	return op;
}

int MenuAreas() {
	int op;
	char st[2];
	printf("\n\n\t\t--- Menu Areas ---\n");
	printf("1 - Listar Areas\n");
	printf("2 - Adicionar Areas\n");
	printf("3 - Eliminar Area\n");
	printf("4 - Voltar\n");
	printf("5 - Terminar\n");
	printf("\n");
	do {
		printf("\nOpcao: ");
		scanf(" %s", st);
		op=atoi(st);
	} while (op < 1 || op > 5);
	printf("\n");
	return op;
}

int Menu() {
	int op;
	char st[2];
	printf("\n\n\t\t--- Menu Principal ---\n");
	printf("1 - Menu Areas\n");
	printf("2 - Menu Animais\n");
	printf("3 - Terminar\n");
	printf("\n");
	do {
		printf("\nOpcao: ");
		scanf(" %s", st);
		op=atoi(st);
	} while (op < 1 || op > 3);
	printf("\n");
	return op;
}

