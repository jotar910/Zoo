// Nome: João Paulo Mendes Rodrigues | Número: 21260309

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vars.h"
#include "funcExtra.h"
#include "auxAnimais.h"

//#################################################################### PREENCHE LISTA LIGADA DAS ESPECIES
pespecie readEspecies(pespecie especies, char file_especies[]){
	FILE *f;
	pespecie novo;
	
	if( (f=fopen(file_especies, "rt")) != NULL){
		while( fgetc(f) != EOF ){
			fseek(f, -1, SEEK_CUR); // recua uma letra, que foi lida anteriormente no while
			if((novo = malloc(sizeof(especie))) == NULL){
				printf("ERRO: Erro ao alocar memoria!\n");
				fclose(f);
				return especies;
			}
			fscanf(f," %s ", novo->esp);
			fscanf(f," %d ", &novo->tipo1);
			fscanf(f," %d\n", &novo->tipo2);
			
			novo->prox=especies;
			especies=novo;
		}
		fclose(f);
	}
	return especies;
}

//#################################################################### MOSTRA OS TIPOS DA AREA CASO ESTEJA HABITADA (EXTRA)
void showTipoArea(area areas){
	switch (areas.tipo1){
		case 1:
			printf("Ambiente: Terrestre\n");
			break;
		case 2:
			printf("Ambiente: Aquatico\n");	
			break;		
		case 3:
			printf("Ambiente: Aereo\n");	
			break;		
	}
	switch (areas.tipo2){
		case 1:
			printf("Tipo: Carnivoro\n");
			break;
		case 2:
			printf("Tipo: Herbivoro\n");	
			break;	
		case 3:
			printf("Tipo: Omnivoro\n");	
			break;	
	}
}

//#################################################################### MOSTRA OS TIPO DE UMA ESPECIE (EXTRA)
void showTipoEsp(pespecie especies, char esp[]){
	while(especies != NULL){
		if(strcmp(especies->esp, esp) == 0){
			switch (especies->tipo2){
				case 1:
					printf("Tipo: Carnivoro\n");
					break;
				case 2:
					printf("Tipo: Herbivoro\n");	
					break;	
				case 3:
					printf("Tipo: Omnivoro\n");	
					break;	
			}
			break;
		}
		especies = especies->prox;
	}
}

//#################################################################### COMPARA O TIPO DE DUAS AREA (MUDA O TIPO SE VAZIA)
int verificaTipoAreas(parea orig, parea dest){
	if(dest->popul != NULL){
		if(dest->tipo1 != orig->tipo1 || dest->tipo2 != orig->tipo2)
			return 0;
	}else{
		dest->tipo1 = orig->tipo1;
		dest->tipo2 = orig->tipo2;
	}
	return 1;
}

//#################################################################### VERIFICA SE A ESPECIE SE ENCONTRA REGISTADA
int existeEsp(char esp[], pespecie especies){
	for(; especies != NULL; especies = especies->prox)
		if(strcmp(esp, especies->esp) == 0)
			return 1;
	return 0;
}

//#################################################################### GUARDA O TIPO DA AREA
void loadAreaTipo(parea areas, panimal animais, pespecie especies){
	for(; especies!=NULL; especies=especies->prox)
		if(strcmp(animais->esp, especies->esp) == 0){
			areas->tipo1=especies->tipo1;
			areas->tipo2=especies->tipo2;
		}
}

//#################################################################### COMPARAR O TIPO DO ANIMAL COM A ÁREA
int verificaAnimalAreaCmp(parea areas, panimal animais, pespecie especies){
	if(areas->popul == NULL){
		loadAreaTipo(areas, animais, especies);
		return 1;
	}
	for(; especies != NULL && strcmp(especies->esp, animais->esp) != 0; especies = especies->prox)
		;
	if(especies != NULL && especies->tipo1 == areas->tipo1 && especies->tipo2 == areas->tipo2)
		return 1;
	return 0;
}

//#################################################################### CONTA O NUMERO DE ESPECIES EXISTENTES NO ZOO
int contaEspecies(parea areas, int total_areas, char esp[]){
	int i, c = 0;
	panimal p;
	
	for(i=0;i<total_areas;i++){
		for(p=areas[i].popul; p!=NULL; p=p->prox)
			if(strcmp(p->esp, esp)==0)
				c++;
	}
	
	return c;
}

//#################################################################### ELIMINA UMA ESPECIE
pespecie delEsp(pespecie especies, char esp[]){
	pespecie ant = NULL, aux = NULL;
	
	for(ant = NULL, aux = especies; aux!=NULL && strcmp(aux->esp, esp) != 0; ant = aux, aux = aux->prox)
		;
	if(aux != NULL){
		if(ant == NULL)
			especies = aux->prox;
		else
			ant->prox = aux->prox;
		free(aux);			
	}
	
	return especies;
}

//#################################################################### UTILIZADOR INTRODUZ TIPO DA ESPECIE, CASO SEJA COMPATVEL COM AREA -> ADICIONA ESPECIE
pespecie addEspAddArea(pespecie especies, parea loc, panimal info){
	pespecie novo;
	
	if((novo = malloc(sizeof(especie))) == NULL)
		printf("ERRO: Erro ao alocar memoria!\n");
	else{
		printf("\nAdicionar nova especie ao zoo:\n");
		strcpy(novo->esp, info->esp);
		printf("Qual o ambiente da especie \"%s\"?\n1 - Terrestre\t2 - Aquatico\t3 - Aereo\n", info->esp);
		do{
			printf("Ambiente: "); scanf("%d", &novo->tipo1);
		}while(novo->tipo1<1 ||novo->tipo1>3);
		printf("Qual o tipo da especie \"%s\"?\n1 - Carnivoro\t2 - Herbivoro\t3 - Omnivoro\nTipo: ", info->esp);
		do{
			printf("Tipo: "); scanf("%d", &novo->tipo2);
		}while(novo->tipo2<1 ||novo->tipo2>3);
		putchar('\n');
		if(loc->popul != NULL && (loc->tipo1 != novo->tipo1 || loc->tipo2 != novo->tipo2)){
			printf("O animal nao e compativel com os animais da area \"%s\"! Animal e especie nao adicionados.\n", loc->nome);
			free(novo);
		}else{
			//ADICIONA À LISTA LIGADA ESPECIES
			novo->prox=especies;
			especies=novo;
			//ATRIBUI O TIPO À ÁREA
			if(loc->popul == NULL){
				loc->tipo1=especies->tipo1;
				loc->tipo2=especies->tipo2;
			}
			addAnimal(loc, info);
			printf("O animal \"%s\" foi adicionado para a area \"%s\" com o id \"%s\".\n", info->nome, info->loc, info->id);
		}
	}
	return especies;
}
