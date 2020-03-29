// Nome: João Paulo Mendes Rodrigues | Número: 21260309

#ifndef FUNCANIMAIS_H
#define FUNCANIMAIS_H

//#################################################################### RECEBE OS DADOS DO UTILIZADOR E VERIFICA SE E POSSIVEL TRANSFERIR O ANIMAL
void verificaTransferAnimais(parea areas, int total_areas, int extra);
//#################################################################### RECEBE OS DADOS DO UTILIZADOR E VERIFICA SE E POSSIVEL ELIMINAR O ANIMAL
void verificaDelAnimal(parea areas, int total_areas, pespecie especies, int extra);
//#################################################################### RECEBE OS DADOS DO UTILIZADOR E VERIFICA SE E POSSIVEL NASCER O ANIMAL
void verificaNascerAnimal(parea areas, int total_areas);
//#################################################################### LE UM FICHEIRO DE TEXTO INDICADO PELO UTILIZADOR E ADICIONA À LISTA LIGADA DOS ANIMAIS
pespecie addAnimalFich(parea areas, int total_areas, pespecie especies, int extra);

#endif /* FUNCANIMAIS_H */

