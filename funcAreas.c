// Nome: João Paulo Mendes Rodrigues | Número: 21260309

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "vars.h"
#include "funcAreas.h"
#include "auxAreas.h"
#include "funcExtra.h"

//#################################################################### ADICIONAR AREA AO VETOR DINAMICO
parea addAreas(parea areas, int *total_areas){
	parea novo;
	char nomeArea[TAM_STRING];

	printf("Nome? "); scanf(" %s", nomeArea);
	
	if(areaExiste(areas, *total_areas, nomeArea) == NULL){ // verifica se a área já existe (NULL = não existe)
		if((novo = malloc(sizeof(area))) == NULL){
			printf("ERRO: Erro ao alocar memoria!\n");
			return areas;
		}
		novo=addAreasInfo(areas, *total_areas, nomeArea, novo);
		areas=addNewArea(areas, total_areas, novo);
		printf("Area inserida com sucesso.\n");
		free(novo);
	}else
		printf("Area ja se encontra registada!\n");
	return areas;
}

//#################################################################### ELIMINAR AREA DO VETOR DINAMICO
parea delAreas(parea areas, int *total_areas){
	int i;
	char sn, nomeArea[TAM_STRING];
	parea p;
	
	printf("\n\tEliminar Area\nNome da Area: ");
	scanf(" %s", nomeArea);
	printf("Tem a certeza que pretende eliminar a area \"%s\"? (s ou n) ", nomeArea);
	scanf(" %c", &sn);
	if( sn != 's'  && sn != 'S')
		return areas;
	for(i=0;i < *total_areas && strcmp(nomeArea, areas[i].nome) != 0; i++)
		;
	if(areas[i].popul != NULL && i < *total_areas)
		printf("Nao foi possivel eliminar a area \"%s\" porque ainda habitam animais!\n", nomeArea);
	else{
		if(i == *total_areas)
			printf("A area \"%s\" nao existe!\n", nomeArea);
		else{
			delAreaFronteira(areas, *total_areas, nomeArea);
			(*total_areas)--;
			for(;i < *total_areas; i++){
				areas[i]=areas[i+1];
			}
			if((p = realloc(areas, sizeof(area) * (*total_areas)) ) == NULL){
				if((areas = malloc(sizeof(area))) == NULL)
					printf("ERRO: Erro na realocacao de memoria!\n");
			}else{
				areas = p;
				printf("A area \"%s\" foi eliminada com sucesso.\n", nomeArea);
			}
		}
	}
	return areas;
}

//#################################################################### MOSTRA VETOR DINAMICO AREAS
void showAreas(parea areas, int total_areas, int extra){
	int i, j;
	
	if(total_areas == 0){
		printf("Nao existem areas registadas!\n");
		return;
	}
	printf("\nAREAS:\n");
	
	for(i=0;i<total_areas;i++){
		printf("\nNome: %s;\nCapacidade: %.1lf;\n", (areas+i)->nome, (areas+i)->capacidade);
		if((areas+i)->n_front > 0){
			printf("Fronteiras:", (areas+i)->n_front);
			for(j=0;j<(areas+i)->n_front;j++)
				printf(" %s", (areas+i)->fronteiras+j);
			printf(";\n");
		}
		if(extra && areas[i].popul != NULL)
			showTipoArea(areas[i]);
	}
}