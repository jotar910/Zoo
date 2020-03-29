// Nome: João Paulo Mendes Rodrigues | Número: 21260309

#ifndef MEMLOADSAVE_H
#define MEMLOADSAVE_H

//#################################################################### CARREGA AREAS PARA VETOR DINAMICO NO INICIO DO PROGRAMA
parea loadAreas(parea areas, int *total_areas, char file_areas[]);
//#################################################################### LE OS ANIMAIS DE UM FICHEIRO BINARIO
void readAnimais(parea areas, int total_areas, char file_animais[], pespecie especies, int extra);
//#################################################################### GUARDA A INFORMAÇÃO DO ZOO NOS RESPETIVOS FICHEIRO
void saveZoo(parea areas, int total_areas, pespecie especies, int extra);

#endif /* MEMLOADSAVE_H */

