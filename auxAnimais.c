// Nome: João Paulo Mendes Rodrigues | Número: 21260309

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vars.h"
#include "auxAnimais.h"

//#################################################################### GERA AUTOMATICAMENTE O ID PARA OS ANIMAIS
void geraIdAnimais(parea areas, int total_areas, char idAnim[], char esp[]){
	int i, existe=0;
	char id_def[]="AAAA";
	panimal p;
	
	for(i=0; i< total_areas; i++)
		for(p=areas[i].popul; p!=NULL; p=p->prox)
			if(strcmp(p->esp, esp) == 0)
				if(strcmp(p->id, id_def) >= 0){
					strcpy(id_def, p->id);
					existe = 1;
				}
	strcpy(idAnim, id_def);
	if(existe){
		if(idAnim[3] < 'Z')
			idAnim[3]++;
		else{
			idAnim[3] = 'A';
			if(idAnim[2] < 'Z')
				idAnim[2]++;
			else{
				idAnim[2] = 'A';
				if(idAnim[1] < 'Z')
					idAnim[1]++;
				else{
					idAnim[1] = 'A';
					idAnim[1]++;
				}
			}
		}
	}
		
}

//#################################################################### CONTA O NUMERO DE ANIMAIS COM O MESMO ID IGNORANDO A ESPECIE
int idAnimaisConta(parea p, int total_areas, char id_animal[]){
	panimal aux;
	int i, c=0;
	
	if(p!=NULL){
		for(i=0;i<total_areas;i++){
			aux=(p+i)->popul;
			while(aux!=NULL){
				if(strcmp(aux->id, id_animal) == 0)
					c++;
				aux=aux->prox;
			}
		}
	}
	return c;
}

//#################################################################### PESO DOS ANIMAIS EXISTENTES NA AREA
double pesoAnimaisArea(parea p){
	panimal aux;
	double peso_existente=0;
	aux=p->popul;
	while(aux!=NULL){
		peso_existente+=aux->peso;
		aux=aux->prox;
	}
	return peso_existente;
}

//#################################################################### VERIFICAR SE O ID E UNICO DENTRO DA ESPECIE EM QUALQUER AREA
int idUnico(parea p, int total_areas, panimal info){
	panimal aux;
	int i;
	
	if(p!=NULL){
		for(i=0;i<total_areas;i++){
			aux=(p+i)->popul;
			while(aux!=NULL){
				if(strcmp(aux->id, info->id) == 0 && strcmp(aux->esp, info->esp)==0)
					return 0;
				aux=aux->prox;
			}
		}
	}
	return 1;
}

//#################################################################### VERIFICA E COMPARA SE O ANIMAL EXISTE
panimal animalExiste(parea areas, int total_areas, char id_animal[]){
	panimal p;
	int i;
	
	if(areas==NULL){
		printf("Nao existem Areas registadas!\n");
		return NULL;
	}
	
	for(i=0;i<total_areas;i++){
			p=(areas+i)->popul;
			while(p!=NULL){
				if(strcmp(p->id, id_animal) == 0)
					return p;
				p=p->prox;
			}
	}
	printf("O animal com o id \"%s\" nao existe!\n", id_animal);
	return NULL;
}

//#################################################################### VERIFICA E COMPARA SE O ANIMAL EXISTE NA AREA E DEVOLVE A INFO DO ANIMAL
panimal animalExisteArea(parea areas, int total_areas, char nome_area[], char id_animal[]){
	panimal p;
	int i;
	
	if(areas==NULL){
		printf("Nao existem Areas registadas!\n");
		return NULL;
	}
	
	for(i=0;i<total_areas;i++){
		if(strcmp((areas+i)->nome, nome_area) == 0){
			p=(areas+i)->popul;
			if(p!=NULL){
				while(p!=NULL){
					if(strcmp(p->id, id_animal) == 0)
						return p;
					p=p->prox;
				}
			}else
				printf("Nao existem animais nesta Area!\n");
		}
	}
	return NULL;
}

//#################################################################### VERIFICAR SE A ESPECIE COM ID EXISTE
panimal espExisteId(parea areas, int total_areas, char id_animal[], char esp_animal[]){
	panimal p;
	int i;
	
	if(areas==NULL){
		printf("Nao existem Areas registadas!\n");
		return NULL;
	}
	
	for(i=0;i<total_areas;i++){
			p=(areas+i)->popul;
			while(p!=NULL){
				if(strcmp(p->id, id_animal) == 0 && strcmp(p->esp, esp_animal) == 0)
					return p;
				p=p->prox;
			}
	}
	printf("O animal de id \"%s\" e especie \"%s\" nao existe registado!\n", id_animal, esp_animal);
	return NULL;
}

//#################################################################### CARREGAR ANIMAL PARA A LISTA LIGADA
void addAnimal(parea areas, panimal info){
	panimal novo, aux, ant;
	
	if((novo=malloc(sizeof(animal))) == NULL){
		printf("ERRO: Erro na alocação de memória!\n");
		return;
	}
	*novo=*info;
	if(areas->popul == NULL){
		novo->prox=NULL;
		areas->popul = novo;
	}else{
		ant = NULL;
		aux = areas->popul;
		while(aux!=NULL && strcmp(novo->id, aux->id)>=0){ // ordenado alfabeticamente pelo id
			if(strcmp(novo->id, aux->id)==0){
				while(aux!=NULL && strcmp(novo->esp, aux->esp)>0){ // ordenado alfabeticamente pela especie
					ant=aux;
					aux=aux->prox;
				}
				break;
			}else{
				ant=aux;
				aux=aux->prox;
			}
		}
		if(ant==NULL){
			novo->prox=aux;
			areas->popul = novo;
		}else{
			ant->prox=novo;
			novo->prox=aux;
		}
	}
}

//#################################################################### TRANSFERE UM ANIMAL DE UMA AREA PARA A OUTRA
void transferAnimais(panimal anim, parea orig, parea dest){
	panimal ant, p;
	
	ant = NULL;
	p = orig->popul;
	while(p!=NULL && p!=anim){
		ant = p;
		p = p->prox;
	}
	if(ant == NULL)
		orig->popul=p->prox;
	else
		ant->prox=p->prox;

	ant=NULL;
	p=dest->popul;
	if(p==NULL){
		anim->prox=NULL;
		dest->popul=anim;
	}else{
		while(p!=NULL && strcmp(anim->id, p->id)>=0){ // ordenado alfabeticamente pelo id
			if(strcmp(anim->id, p->id)==0){
				while(p!=NULL && strcmp(anim->esp, p->esp)>0){ // ordenado alfabeticamente pela especie
					ant=p;
					p=p->prox;
				}
				break;
			}else{
				ant=p;
				p=p->prox;
			}
		}
		if(ant==NULL){
			anim->prox=p;
			dest->popul=anim;
		}else{
			anim->prox=p;
			ant->prox=anim;
		}
	}
	strcpy(anim->loc, dest->nome);
	printf("O animal com id \"%s\" foi transferido para a Area \"%s\".\n", anim->id, dest->nome);
}

//#################################################################### ELIMINA A INFORMAÇÃO RELATIVA A UM ANIMAL NOS OUTROS ANIMAIS (DA MESMA ESPECIE)
void delInfoAnimal(parea areas, int total_areas, char id_animal[], char esp_animal[]){
	panimal p;
	int i, j, s;
	
	if(areas == NULL){
		printf("Nao existem Areas registadas!\n");
		return;
	}
	
	for(i=0;i<total_areas;i++){
		p=(areas+i)->popul;
		while(p!=NULL){
			if(strcmp(p->esp, esp_animal) == 0){
				if(p->familia.pais.pai == 1 && strcmp(p->familia.pais.id_pai, id_animal) == 0)
					p->familia.pais.pai = 0;
				else if(p->familia.pais.mae == 1 && strcmp(p->familia.pais.id_mae, id_animal) == 0)
					p->familia.pais.mae = 0;
				else if(p->familia.filhos.n_filhos>0){
					for(j=0, s=0; j < p->familia.filhos.n_filhos && !s; j++)
						if(strcmp(p->familia.filhos.id_filho[j], id_animal) == 0)
							s=1;
					if(s == 1){
						(p->familia.filhos.n_filhos)--;
						for(j--; j < p->familia.filhos.n_filhos; j++){
							strcpy(p->familia.filhos.id_filho[j], p->familia.filhos.id_filho[j+1]);
							strcpy(p->familia.filhos.nome_filho[j], p->familia.filhos.nome_filho[j+1]);
						}
					}
				}
			}
			p=p->prox;
		}
	}
	
}

//#################################################################### ELIMINA UM ANIMAL
void delAnimal(parea areas, int total_areas, panimal p){
	panimal ant = NULL, aux = NULL;
	int i;
	
	if(areas == NULL){
		printf("Nao existem Areas registadas!\n");
		return;
	}
	
	for(i=0;i<total_areas;i++){
		for(ant = NULL, aux = (areas+i)->popul; aux!=NULL && (strcmp(p->id, aux->id) != 0 || strcmp(p->esp, aux->esp) != 0); ant = aux, aux = aux->prox)
			;
		if(aux != NULL){
			if(ant == NULL)
				areas[i].popul=aux->prox;
			else
				ant->prox=aux->prox;
			free(aux);
			return;			
		}
	}
}
