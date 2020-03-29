// Nome: João Paulo Mendes Rodrigues | Número: 21260309

#ifndef AUXAREAS_H
#define AUXAREAS_H

//#################################################################### ADICIONA NOVA AREA AO VETOR DINAMICO
parea addNewArea(parea areas, int *total_areas, parea novo);
//#################################################################### VERIFICA E COMPARA SE A AREA EXISTE E DEVOLVE PONTEIRO
parea areaExiste(parea areas, int total_areas, char pal[]);
//#################################################################### INFORMACAO DA AREA A ADICIONAR PELO UTILIZADOR
parea addAreasInfo(parea areas, int total_areas, char nomeArea[], parea novo);
//#################################################################### ELIMINAR AREA DAS FRONTEIRAS DAS OUTRAS AREAS VETOR DINAMICO
void delAreaFronteira(parea areas, int total_areas, char nomeArea[]);

#endif /* AUXAREAS_H */

