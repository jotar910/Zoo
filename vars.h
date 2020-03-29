// Nome: João Paulo Mendes Rodrigues | Número: 21260309

#ifndef STRUCTS_H
#define STRUCTS_H

#define FILE_AREAS "areasZoo.txt"
#define FILE_ANIMAIS "animaisZoo.dat"
#define FILE_ESPECIES "espZoo.txt"
#define LIM_ZOO 500
#define TAM_ID 5
#define TAM_STRING 200
#define N_FRONT 3
#define N_FILHOS 20

typedef struct areas area, *parea;
typedef struct animais animal, *panimal;
typedef struct especies especie, *pespecie;

struct areas{
    char nome[TAM_STRING];
    double capacidade;
    int n_front;
    char fronteiras[N_FRONT][TAM_STRING];
    int tipo1, tipo2;
    panimal popul;
};

struct animais{
    char esp[TAM_STRING], id[TAM_ID], nome[TAM_STRING];
    double peso;
    char loc[TAM_STRING];
    struct{
        struct{
            int pai;
            char id_pai[TAM_ID], nome_pai[TAM_STRING];
            int mae;
            char id_mae[TAM_ID], nome_mae[TAM_STRING];
        } pais;
        
        struct{
            int n_filhos;
            char id_filho[N_FILHOS][TAM_ID], nome_filho[N_FILHOS][TAM_STRING];
        } filhos;
    } familia;
    panimal prox;
};

struct especies{
    char esp[TAM_STRING];
    int tipo1, tipo2;
    pespecie prox;
};

#endif /* STRUCTS_H */

