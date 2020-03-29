// Nome: João Paulo Mendes Rodrigues | Número: 21260309

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "vars.h"
#include "auxAreas.h"

//#################################################################### ADICIONA NOVA AREA AO VETOR DINAMICO
parea addNewArea(parea areas, int *total_areas, parea novo){
	parea p, q;
	int i;
	
	if((q = realloc(areas, sizeof(area) * (*total_areas+1)) ) == NULL){
		printf("ERRO: Erro na realocação de memória!\n");
		return areas;
	}
	p=q;
	for(i = *total_areas; i>0 && strcmp(novo->nome, p[i-1].nome)<0; i--) // começa do fim e compara com o nome do anterior, ordenando alfabéticamente
		p[i]=p[i-1];
	if(strcmp(novo->nome, p[i].nome)!=0){
		p[i]=*novo;
		(*total_areas)++;
	}else
		printf("O nome da Area ja existe. A Area \"%s \" nao foi adicionada!\n", novo->nome);
	return p;
}

//#################################################################### VERIFICA E COMPARA SE A AREA EXISTE E DEVOLVE PONTEIRO
parea areaExiste(parea areas, int total_areas, char pal[]){
	int i;
	
	for(i=0;i<total_areas;i++){
		if(strcmp((areas+i)->nome, pal)==0)
			return (areas+i);
	}
	return NULL;
}

//#################################################################### INFORMACAO DA AREA A ADICIONAR PELO UTILIZADOR
parea addAreasInfo(parea areas, int total_areas, char nomeArea[], parea novo){
	parea areaFront;
	char front[TAM_STRING];
	int i;
	
	strcpy(novo->nome, nomeArea);
	printf("Capacidade da '%s'? ", novo->nome);
	scanf(" %lf", &novo->capacidade);
	do {
		printf("Numero de fronteiras?(0-%d) ", N_FRONT);
		scanf(" %d", &novo->n_front);
	} while (novo->n_front < 0 || novo->n_front > N_FRONT);
	for (i = 0; i < novo->n_front; i++) {
		printf("Fronteira %d: ", i + 1);
		scanf(" %s", front);
		if((areaFront = areaExiste(areas, total_areas, front)) != NULL){
			if(areaFront->n_front < N_FRONT){
				strcpy(novo->fronteiras[i], front);
				// adiciona a area nova à fronteira da outra area
				strcpy(areaFront->fronteiras[areaFront->n_front], novo->nome);
				(areaFront->n_front)++;
			}else{
				printf("A Area \"%s\" nao pode ter mais fronteiras!\n", front);
				i--;
				novo->n_front--;
			}
		}else{
			printf("A Area \"%s\" nao existe!\n", front);
			i--;
			novo->n_front--;
		}
	}
	novo->popul = NULL;
	return novo;
}

//#################################################################### ELIMINAR AREA DAS FRONTEIRAS DAS OUTRAS AREAS VETOR DINAMICO
void delAreaFronteira(parea areas, int total_areas, char nomeArea[]){
	int i, j;
	
	for(i=0; i < total_areas; i++)
		if(areas[i].n_front > 0){
			for(j=0; j < areas[i].n_front && strcmp(areas[i].fronteiras[j], nomeArea) != 0; j++)
				;
			if(j < areas[i].n_front){
				(areas[i].n_front)--;
				for(; j < areas[i].n_front; j++)
					strcpy(areas[i].fronteiras[j], areas[i].fronteiras[j+1]);
			}
		}
}