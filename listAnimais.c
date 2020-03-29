// Nome: João Paulo Mendes Rodrigues | Número: 21260309

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vars.h"
#include "listAnimais.h"
#include "funcExtra.h"

//#################################################################### LISTAGEM COMPLETA DOS ANIMAIS
void showAnimaisTodos(parea p, int total_areas){
	panimal aux;
	int i, s = 0;
	printf("\nLISTAGEM COMPLETA DOS ANIMAIS\n");
	
	for(i=0;i<total_areas;i++){
		aux=p[i].popul;
		if(aux != NULL){
			printf("\n\tArea: %s\n", aux->loc);
			s=1;
		}
		while(aux!=NULL){
			putchar('\n');
			printf("ID:  %s\n", aux->id);
			printf("Nome: %s\n", aux->nome);
			printf("Especie: %s\n", aux->esp);
			putchar('\n');
			aux=aux->prox;
		}
	}
	if(s == 0)
		printf("Nao existe animais registados no Zoo!\n");
}

//#################################################################### LISTAGEM DOS ANIMAIS DE UMA LOCALIZACAO
void showAnimaisLoc(parea p, int total_areas, char loc[]){
	panimal aux;
	int i;
	
	for(i=0;i<total_areas && strcmp(p[i].nome, loc) != 0; i++)
		;
	if(i != total_areas){
		aux=p[i].popul;
		if(aux != NULL){
			printf("\nANIMAIS DA AREA: %s\n", aux->loc);
			while(aux!=NULL){
				putchar('\n');
				printf("ID:  %s\n", aux->id);
				printf("Nome: %s\n", aux->nome);
				printf("Especie: %s\n", aux->esp);
				putchar('\n');
				aux=aux->prox;
			}
		}else
			printf("A area \"%s\" nao tem animais!\n", loc);
	}else
		printf("A area \"%s\" nao existe!\n", loc);
}

//#################################################################### LISTAGEM DOS ANIMAIS DE UMA ESPECIE
void showAnimaisEsp(parea p, int total_areas, char esp[]){
	panimal aux;
	int i, n, s = 0;
	
	for(i=0;i<total_areas;i++){
		n=0;
		aux=p[i].popul;			
		while(aux!=NULL){
			if(strcmp(aux->esp, esp) == 0){
				if(s==0){
					printf("\nANIMAIS DA ESPECIE: %s\n", esp);
					s=1;
				}
				if(n == 0){
					printf("\n\tArea: %s\n", aux->loc);
					n = 1;
				}
				putchar('\n');
				printf("ID:  %s\n", aux->id);
				printf("Nome: %s\n", aux->nome);
				putchar('\n');
			}
			aux=aux->prox;
		}
	}
	if(s == 0)
		printf("Nao existe animais da especie \"%s\"!\n", esp);
	
}

//#################################################################### LISTAGEM DA INFORMACAO COMPLETA DE UM ANIMAL
void showAnimaisInfo(parea areas, int total_areas, char id_anim[], pespecie especies, int extra){
	panimal aux, info;
	int i, j, c=0, s=0;
	char esp[TAM_STRING];
	
	if((info=malloc(sizeof(animal)*LIM_ZOO)) == NULL){
		printf("ERRO: Erro ao alocar memoria!\n");
		return;
	}
	for(i=0;i<total_areas;i++){
		aux=areas[i].popul;			
		while(aux!=NULL){
			if(strcmp(aux->id, id_anim) == 0){
				info[c]=*aux;
				c++;
			}
			aux=aux->prox;
		}
	}
	if(c == 0){
		printf("Nao existe animais com o id \"%s\"!\n", id_anim);
		return;
	}else if(c > 1){
		printf("Qual a especie do animal? "); scanf(" %s", esp);
		for(i=0; i<c; i++)
			if(strcmp(info[i].esp, esp) == 0){
				s=i;
				break;
			}
		if(i == c && s == 0){
			printf("Nao existe animais com o id %s e de especie \"%s\"!\n", id_anim, esp);
			return;
		}
	}
	printf("ID:  %s\n", info[s].id);
	printf("Nome: %s\n", info[s].nome);
	printf("Especie:  %s\n", info[s].esp);
	printf("Peso:  %.1lf\n", info[s].peso);
	printf("Localizacao: %s\n", info[s].loc);
	
	if(extra)
		showTipoEsp(especies, info[s].esp);
	
	if(info[s].familia.pais.pai >0 || info[s].familia.pais.mae >0 || info[s].familia.filhos.n_filhos>0)
		printf("\n\tFamilia\n");
	if(info[s].familia.pais.pai >0){
		printf("Pai - ID: %s\tNome: %s\n", info[s].familia.pais.id_pai, info[s].familia.pais.nome_pai);
	}
	if(info[s].familia.pais.mae >0){
		printf("Mae - ID: %s\tNome: %s\n", info[s].familia.pais.id_mae, info[s].familia.pais.nome_mae);
	}
	if(info[s].familia.filhos.n_filhos>0){
		printf("Filhos:");
		for(j = 0; j < info[s].familia.filhos.n_filhos; j++){
			printf("\n   ID: %s\tNome: %s", info[s].familia.filhos.id_filho[j], info[s].familia.filhos.nome_filho[j]);
		}
		putchar('\n');
	}
	free(info);
}