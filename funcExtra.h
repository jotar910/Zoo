// Nome: João Paulo Mendes Rodrigues | Número: 21260309

#ifndef FUNCEXTRA_H
#define FUNCEXTRA_H

//#################################################################### MOSTRA OS TIPOS DA AREA CASO ESTEJA HABITADA (EXTRA)
void showTipoArea(area areas);
//#################################################################### MOSTRA OS TIPOS DE UMA ESPECIE (EXTRA)
void showTipoEsp(pespecie especies, char esp[]);
//#################################################################### PREENCHE LISTA LIGADA DAS ESPECIES
pespecie readEspecies(pespecie especies, char file_especies[]);
//#################################################################### COMPARA O TIPO DE DUAS AREA (MUDA O TIPO SE VAZIA)
int verificaTipoAreas(parea orig, parea dest);
//#################################################################### VERIFICA SE A ESPECIE SE ENCONTRA REGISTADA
int existeEsp(char esp[], pespecie especies);
//#################################################################### GUARDA O TIPO DA AREA
void loadAreaTipo(parea areas, panimal animais, pespecie especies);
//#################################################################### VERIFICA SE O TIPO DO ANIMAL É COMPATIVEL COM A AREA
int verificaAnimalAreaCmp(parea areas, panimal animais, pespecie especies);
//#################################################################### CONTA O NUMERO DE ESPECIES EXISTENTES NO ZOO
int contaEspecies(parea areas, int total_areas, char esp[]);
//#################################################################### ELIMINA UMA ESPECIE ATRAVES DO NOME DA ESPECIE
pespecie delEsp(pespecie especies, char esp[]);
//#################################################################### UTILIZADOR INTRODUZ TIPO DA ESPECIE, CASO SEJA COMPATVEL COM AREA -> ADICIONA ESPECIE
pespecie addEspAddArea(pespecie especies, parea loc, panimal info);

#endif /* FUNCEXTRA_H */

