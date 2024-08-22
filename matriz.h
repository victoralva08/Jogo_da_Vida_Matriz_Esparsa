#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef matriz_h
#define matriz_h

typedef struct matriz MatrizEsparsa;
typedef struct celula Celula;


MatrizEsparsa * alocaMatrizEsparsa(int dimensaoFornecida);
void iniciaListas(MatrizEsparsa *matriz);

void liberaMatriz(MatrizEsparsa *matriz);

MatrizEsparsa * desalocaMatrizEsparsa(MatrizEsparsa * matrizEsparsa);

void leituraDaMatriz(MatrizEsparsa * matriz);
void imprimeMatriz(MatrizEsparsa * matrizEsparsa);

void evoluirMatriz(MatrizEsparsa **matrizEsparsa, MatrizEsparsa **matrizAuxiliar) ;

#endif