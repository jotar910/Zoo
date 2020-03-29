// Nome: João Paulo Mendes Rodrigues | Número: 21260309

#ifndef LISTANIMAIS_H
#define LISTANIMAIS_H

//#################################################################### LISTAGEM COMPLETA DOS ANIMAIS
void showAnimaisTodos(parea p, int total_areas);
//#################################################################### LISTAGEM DOS ANIMAIS DE UMA LOCALIZACAO
void showAnimaisLoc(parea p, int total_areas, char loc[]);
//#################################################################### LISTAGEM DOS ANIMAIS DE UMA ESPECIE
void showAnimaisEsp(parea p, int total_areas, char esp[]);
//#################################################################### LISTAGEM DA INFORMACAO COMPLETA DE UM ANIMAL
void showAnimaisInfo(parea p, int total_areas, char id_anim[], pespecie especies, int extra);

#endif /* LISTANIMAIS_H */

