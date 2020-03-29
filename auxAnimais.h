// Nome: João Paulo Mendes Rodrigues | Número: 21260309

#ifndef AUXANIMAIS_H
#define AUXANIMAIS_H

//#################################################################### CARREGAR ANIMAIS PARA LISTA LIGADA
void addAnimal(parea p, panimal info);
//#################################################################### PESO DOS ANIMAIS EXISTENTES NA AREA
double pesoAnimaisArea(parea p);
//#################################################################### VERIFICAR SE O ID E UNICO DENTRO DA ESPECIE EM QUALQUER AREA
int idUnico(parea p, int total_areas, panimal info);
//#################################################################### VERIFICA E COMPARA SE O ANIMAL EXISTE NA AREA E DEVOLVE A INFO DO ANIMAL
panimal animalExisteArea(parea areas, int total_areas, char nome_area[], char id_animal[]);
//#################################################################### TRANSFERE UM ANIMAL DE UMA AREA PARA A OUTRA
void transferAnimais(panimal anim, parea orig, parea dest);
//#################################################################### VERIFICA E COMPARA SE O ANIMAL EXISTE
panimal animalExiste(parea areas, int total_areas, char id_animal[]);
//#################################################################### VERIFICAR SE A ESPECIE COM ID EXISTE
panimal espExisteId(parea areas, int total_areas, char id_animal[], char esp_animal[]);
//#################################################################### ELIMINA A INFORMAÇÃO RELATIVA A UM ANIMAL NOS OUTROS ANIMAIS (DA MESMA ESPECIE)
void delInfoAnimal(parea areas, int total_areas, char id_animal[], char esp_animal[]);
//#################################################################### ELIMINA UM ANIMAL
void delAnimal(parea areas, int total_areas, panimal p);
//#################################################################### CONTA O NUMERO DE ANIMAIS COM O MESMO ID IGNORANDO A ESPECIE
int idAnimaisConta(parea p, int total_areas, char id_animal[]);
//#################################################################### GERA AUTOMATICAMENTE O ID PARA OS ANIMAIS
void geraIdAnimais(parea areas, int total_areas, char idAnim[], char esp[]);

#endif /* AUXANIMAIS_H */

