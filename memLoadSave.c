// Nome: João Paulo Mendes Rodrigues | Número: 21260309

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vars.h"
#include "memLoadSave.h"
#include "auxAreas.h"
#include "auxAnimais.h"
#include "funcExtra.h"

//#################################################################### CARREGA AREAS PARA VETOR DINAMICO NO INICIO DO PROGRAMA
parea loadAreas(parea areas, int *total_areas, char file_areas[]){
	FILE *f;
	parea novo;
	int i;
	
	if( (f=fopen(file_areas, "rt")) == NULL){
		printf("ERRO: Impossivel abrir o ficheiro %s.\n", file_areas);
		return NULL;
	}else if((novo = malloc(sizeof(area))) == NULL){
		printf("ERRO: Erro ao alocar memoria!\n");
		fclose(f);
		return NULL;
	}else{
		while( fgetc(f) != EOF ){
			fseek(f, -1, SEEK_CUR); // recua uma letra, que foi lida anteriormente no while

			fscanf(f," %s ", novo->nome);
			fscanf(f," %lf ", &novo->capacidade);
			fscanf(f," %d", &novo->n_front);

			for(i = 0; i < novo->n_front; i++)
				fscanf(f," %199[^\n ]", novo->fronteiras[i]);
			
			fscanf(f,"\n");
			novo->popul=NULL;
			if(areaExiste(areas, *total_areas, novo->nome) == NULL)
				areas=addNewArea(areas, total_areas, novo);
		}
		free(novo);
		fclose(f);
		if(areas == NULL)
			if((areas = malloc(sizeof(area))) == NULL)
				printf("ERRO: Impossivel alocar memoria para areas.\n");
			else
				printf("\nO zoo nao contem nenhuma area!\n\n");
		return areas;
	}
}

//#################################################################### LE OS ANIMAIS DE UM FICHEIRO BINARIO
void readAnimais(parea areas, int total_areas, char file_animais[], pespecie especies, int extra){
	FILE *f;
	panimal info;
	int i, tipo_cmp;
	
	if( (f=fopen(file_animais, "rb")) == NULL)
		return;
	
	if( (info = malloc(sizeof(animal))) == NULL){
		printf("ERRO: Erro a alocar memoria!\n");
		fclose(f);
		return;
	}
	
	while(fread(info, sizeof(animal),1,f) == 1){
		for(i=0;i<total_areas;i++){
			if(strcmp(info->loc, (areas+i)->nome)==0){ //ver se exite a área em 'info->area'
				
				tipo_cmp = 1;
				if(extra)
					if((tipo_cmp = existeEsp(info->esp, especies)) == 1)
						tipo_cmp = verificaAnimalAreaCmp(areas+i, info, especies);
				
				if(tipo_cmp && info->peso + pesoAnimaisArea(areas+i) <= (areas+i)->capacidade){ //verificar capacidade da area e se ainda é possivel inserir o animal
					if(idUnico(areas, total_areas, info) == 1){ //identificador único do animal dentro da espécie (qualquer area)
						addAnimal(areas+i, info);
						break;
					}
				}
			}
		}
	}
	
	free(info);
	fclose(f);
}

//#################################################################### GUARDA A INFORMAÇÃO DO ZOO NOS RESPETIVOS FICHEIRO
void saveZoo(parea areas, int total_areas, pespecie especies, int extra){
	FILE *fArea, *fAnimal, *fEspecie;
	int i, j;
	panimal animais, aux;
	pespecie aux_esp;
	
	if(extra){
		if((fEspecie = fopen(FILE_ESPECIES, "wt")) == NULL){
			printf("ERRO: Impossivel abrir o ficheiro texto \"%s\" para escrita.", FILE_ESPECIES);
			return;
		}
		while(especies != NULL){
			fprintf(fEspecie,"%s %d %d\n", especies->esp, especies->tipo1, especies->tipo2);
			aux_esp = especies;
			especies = especies->prox;
			free(aux_esp);
		}
		fclose(fEspecie);
	}
	
	if((fArea = fopen(FILE_AREAS, "wt")) == NULL){
		printf("ERRO: Impossivel abrir o ficheiro texto \"%s\" para escrita.", FILE_AREAS);
		return;
	}
	if((fAnimal = fopen(FILE_ANIMAIS, "wb")) == NULL){
		printf("ERRO: Impossivel abrir o ficheiro binario \"%s\" para escrita.", FILE_ANIMAIS);
		fclose(fArea);
		return;
	}
	
	for(i=0; i<total_areas;i++){
		fprintf(fArea,"%s %lf %d", areas[i].nome, areas[i].capacidade, areas[i].n_front);
		for(j = 0; j < areas[i].n_front; j++)
			fprintf(fArea," %s", areas[i].fronteiras[j]);
		fprintf(fArea,"\n");
		
		for(animais=areas[i].popul; animais!=NULL;){
			fwrite(animais, sizeof(animal), 1, fAnimal);
			aux=animais;
			animais=animais->prox;
			free(aux);
		}
	}
	free(areas);
	
	fclose(fAnimal);
	fclose(fArea);
	
	printf("Guardado com sucesso!\n\n");
}
