// Nome: João Paulo Mendes Rodrigues | Número: 21260309

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vars.h"
#include "funcAnimais.h"
#include "auxAnimais.h"
#include "auxAreas.h"
#include "funcExtra.h"

//#################################################################### RECEBE OS DADOS DO UTILIZADOR E VERIFICA SE E POSSIVEL TRANSFERIR O ANIMAL
void verificaTransferAnimais(parea areas, int total_areas, int extra){
	panimal anim, p;
	parea orig, dest;
	int i;
	char area_orig[TAM_STRING], area_dest[TAM_STRING], id_animal[TAM_ID], esp_animal[TAM_STRING];
	
	printf("Qual a area do animal que pretende transferir? "); scanf(" %s", area_orig);
	// verifica se a area existe
	if(( orig = areaExiste(areas, total_areas, area_orig)) != NULL){
		p=orig->popul;
		if(p!=NULL){
			putchar('\n');
			printf("Animais:\n");
			while(p!=NULL){
				printf("ID: %s  Nome: %s  Especie: %s\n", p->id, p->nome, p->esp);
				p=p->prox;
			}
			putchar('\n');
		}else{
			printf("Nao existem animais nesta Area!\n");
			return;
		}
		printf("Qual o id do animal a transferir? "); scanf(" %s", id_animal);
		if(( anim = animalExisteArea(areas, total_areas, area_orig, id_animal)) != NULL){  // verifica se o animal existe na area
			// se existir mais que um animal com o mesmo id
			p=anim->prox;
			while(p!=NULL && strcmp(p->id, id_animal) != 0)
				p=p->prox;
			if(p != NULL){ 
				printf("Qual a especie do animal a transferir? "); scanf(" %s", esp_animal);
				p=orig->popul;
				while(p!=NULL && (strcmp(p->id, id_animal) != 0 || strcmp(p->esp, esp_animal) != 0))
					p=p->prox;
				if(p == NULL){
					printf("O animal com id \"%s\" e de especie \"%s\" nao existe!\n", id_animal, esp_animal);
					return;
				}else
					anim=p;
			}
			// mostra as Areas adjacentes
			if(orig->n_front>0){
				printf("Fronteiras:");
				for(i=0;i<orig->n_front;i++)
					printf(" %s", orig->fronteiras[i]);
				putchar('\n');
			}else{
				printf("A Area \"%s\" nao tem fronteiras!\n", area_orig);
				return;
			}
			printf("Qual a Area destino do animal? "); scanf(" %s", area_dest);
			// verifica se a area e adjacente
			for(i=0;i<orig->n_front;i++){
				if(strcmp(orig->fronteiras[i], area_dest) == 0){
					if((dest = areaExiste(areas, total_areas, area_dest)) != NULL){
						if(extra)
							if(!verificaTipoAreas(orig, dest)){
								printf("Impossivel transferir! O animal nao e compativel com os animais da area \"%s\".\n", area_dest);
								return;
							}
						// verifica se a area destino tem capacidade
						if(pesoAnimaisArea(dest) + anim->peso <= dest->capacidade){
							transferAnimais(anim, orig, dest);
							return; // o animal pode ser transferido
						}else{
							printf("A Area \"%s\" nao tem capacidade para armazenar o animal com id \"%s\"!\n", area_dest, id_animal);
							return;
						}
					}
				}
			}
			printf("A Area \"%s\" nao e adjacente a \"%s\"!\n", area_dest, area_orig);
		}else{
			printf("O animal com id \"%s\" nao existe nesta Area!\n", id_animal);
		}
	}else{
		printf("A Area \"%s\" nao existe!\n", area_orig);
	}
}

//#################################################################### RECEBE OS DADOS DO UTILIZADOR E VERIFICA SE E POSSIVEL ELIMINAR O ANIMAL
void verificaDelAnimal(parea areas, int total_areas, pespecie especies, int extra){
	char sn, id_anim[TAM_ID], esp_anim[TAM_STRING];
	panimal anim;
	printf("Qual o id do animal que pretende eliminar? "); scanf(" %s", id_anim);
	printf("Tem a certeza que pretende eliminar o animal \"%s\"? (s ou n) ", id_anim);
	scanf(" %c", &sn);
	if( sn != 's'  && sn != 'S')
		return;
	if((anim = animalExiste(areas, total_areas, id_anim)) == NULL)
		return;
	if(idAnimaisConta(areas, total_areas, id_anim) > 1){ // existe mais que um animal com o mesmo id
		printf("Qual a especie do animal de id \"%s\"? ", id_anim); scanf(" %s", esp_anim);
		if((anim = espExisteId(areas, total_areas, id_anim, esp_anim)) == NULL)
			return;
	}
	
	strcpy(esp_anim, anim->esp);
	delInfoAnimal(areas, total_areas, anim->id, anim->esp);
	delAnimal(areas, total_areas, anim);
	if(extra)
		if(!contaEspecies(areas, total_areas, esp_anim))
			especies = delEsp(especies, esp_anim);
	printf("O animal de id \"%s\" foi eliminado com sucesso.\n", id_anim);
	return;	
}

//#################################################################### RECEBE OS DADOS DO UTILIZADOR E VERIFICA SE E POSSIVEL NASCER O ANIMAL
void verificaNascerAnimal(parea areas, int total_areas){
	int n_prog;
	double peso;
	char id_pai[TAM_STRING], id_mae[TAM_STRING], esp_pai[TAM_STRING], esp_mae[TAM_STRING];
	parea area_cria;
	panimal pai, mae, cria;
	
	// QUANTOS PROGENITORES?
	do{
		printf("Quantos progenitores tem o animal a nascer? (1 ou 2) "); scanf(" %d", &n_prog);
	}while(n_prog<1 || n_prog>2);
	// INDEPENDENTEMENTE DO NUM DE PROGENITORES PREENCHER E VERFCAR MAE
	printf("Qual o id da mae? "); scanf(" %s", id_mae);
	if((mae = animalExiste(areas, total_areas, id_mae)) == NULL)
		return;	
	if(idAnimaisConta(areas, total_areas, id_mae) > 1){ // existe mais que um animal com o mesmo id
		printf("Qual a especie do animal de id \"%s\"? ", id_mae); scanf(" %s", esp_mae);
		if((mae = espExisteId(areas, total_areas, id_mae, esp_mae)) == NULL)
			return;
	}
	
	if(n_prog > 1){
		//SE EXISTIR 2 PROGENITORES PREENCHER PAI (MAE JA PREENCHIDA)
		printf("Qual o id do pai? "); scanf(" %s", id_pai);
		if((pai = animalExiste(areas, total_areas, id_pai)) == NULL)
			return;	
		if(idAnimaisConta(areas, total_areas, id_pai) > 1){ // existe mais que um animal com o mesmo id
			printf("Qual a especie do animal de id \"%s\"? ", id_pai); scanf(" %s", esp_pai);
			if((pai = espExisteId(areas, total_areas, id_pai, esp_pai)) == NULL)
				return;
		}
		if(strcmp(pai->loc, mae->loc) != 0){
			printf("O pai e a mae nao pertencem a mesma Area!\n");
			return;
		}
	}
	
	if((cria = malloc(sizeof(animal))) == NULL){
		printf("ERRO: Erro ao alocar memoria!\n");
		return;
	}
	
	// GUARDA A AREA ONDE A CRIA VAI NASCER SEGUNDO A LOCALIZAÇÃO DA MAE
	for(area_cria = areas; area_cria != NULL && strcmp(area_cria->nome, mae->loc) != 0; area_cria++)
		;
	
	printf("Antes: %.1lf\n\n", pesoAnimaisArea(area_cria));
	// progenitores já verificados, agora preencher a informação da cria
	printf("Qual o nome da cria? "); scanf(" %199[^\n]", cria->nome);
	strcpy(cria->esp, mae->esp);
	geraIdAnimais(areas, total_areas, cria->id, cria->esp);
	strcpy(cria->loc, mae->loc);
	cria->familia.pais.mae = 1;
	strcpy(cria->familia.pais.id_mae, mae->id);
	strcpy(cria->familia.pais.nome_mae, mae->nome);
	strcpy(mae->familia.filhos.id_filho[mae->familia.filhos.n_filhos], cria->id);
	strcpy(mae->familia.filhos.nome_filho[mae->familia.filhos.n_filhos], cria->nome);
	mae->familia.filhos.n_filhos++;
	if(n_prog > 1){
		cria->familia.pais.pai = 1;
		strcpy(cria->familia.pais.id_pai, pai->id);
		strcpy(cria->familia.pais.nome_pai, pai->nome);
		strcpy(pai->familia.filhos.id_filho[pai->familia.filhos.n_filhos], cria->id);
		strcpy(pai->familia.filhos.nome_filho[pai->familia.filhos.n_filhos], cria->nome);
		pai->familia.filhos.n_filhos++;
		peso=(mae->peso*0.2) + (pai->peso*0.2);
		mae->peso-=mae->peso*0.2;
		pai->peso-=pai->peso*0.2;
	}else{
		cria->familia.pais.pai = 0;
		peso=(mae->peso*0.4);
		mae->peso-=mae->peso*0.4;
	}
	cria->peso = peso;
	cria->familia.filhos.n_filhos = 0;
	cria->prox = NULL;
	addAnimal(area_cria, cria);
	printf("Depois: %.1lf\n\n", pesoAnimaisArea(area_cria));
	printf("Animal adicionado com sucesso!\n");
	free(cria);
}

//#################################################################### LE UM FICHEIRO DE TEXTO INDICADO PELO UTILIZADOR E ADICIONA À LISTA LIGADA DOS ANIMAIS 1
pespecie addAnimalFich(parea areas, int total_areas, pespecie especies, int extra){
	FILE *f;
	parea loc;
	panimal info;
	char nomeFich[TAM_STRING];
	
	printf("Nome do Ficheiro: "); scanf(" %s", nomeFich);
	strcat(nomeFich, ".txt");
	
	if((f = fopen(nomeFich, "rt")) == NULL){
		printf("ERRO: Impossivel abrir o ficheiro \"%s\" de texto para leitura\n", nomeFich);
		return NULL;
	}
	if((info = malloc(sizeof(animal))) == NULL){
		printf("ERRO: Erro ao alocar memoria!\n");
		fclose(f);
		return NULL;
	}
	
	while(fgetc(f) != EOF){
		fseek(f, -1, SEEK_CUR);
		fscanf(f," %s ", info->esp);
		fscanf(f," %199[^0-9] ", info->nome);
		fscanf(f," %lf ", &info->peso);
		fscanf(f," %s", info->loc);
		if((loc = areaExiste(areas, total_areas, info->loc)) != NULL){
			if(info->peso <= loc->capacidade-pesoAnimaisArea(loc)){
				strcpy(info->id, "");
				geraIdAnimais(areas, total_areas, info->id, info->esp);
				info->familia.pais.pai=0;
				info->familia.pais.mae=0;
				info->familia.filhos.n_filhos=0;
				info->prox=NULL;
				if(extra){
					if(!contaEspecies(areas, total_areas, info->esp))
						especies = addEspAddArea(especies, loc, info);
					else{
						addAnimal(loc, info);
						printf("O animal \"%s\" foi adicionado para a area \"%s\" com o id \"%s\".\n", info->nome, info->loc, info->id);
					}
				}else{
					addAnimal(loc, info);
					printf("O animal \"%s\" foi adicionado para a area \"%s\" com o id \"%s\".\n", info->nome, info->loc, info->id);
				}
			}else
				printf("A area \"%s\" nao tem capacidade para o animal \"%s\"!\n", info->loc, info->nome);
		}else
			printf("A area \"%s\" nao existe! O animal \"%s\" nao foi adicionado.\n", info->loc, info->nome);
	}
	
	free(info);
	fclose(f);
	return especies;
}