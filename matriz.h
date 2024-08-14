#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef matriz_h
#define matriz_h

typedef struct matriz MatrizEsparsa;
typedef struct celula Celula;

MatrizEsparsa * alocaMatrizEsparsa(int dimensaoFornecida);

void leituraDaMatriz(MatrizEsparsa * matriz);

void iniciaListas(MatrizEsparsa *matriz);

bool listaEhVazia(Celula *pLista);

bool retiraUltimoElementoDaLista(Celula **pLista); 

void liberaMatriz(MatrizEsparsa *matriz);

void adicionarCelulaNaMatriz(int indiceLinha, int indiceColuna, MatrizEsparsa *matriz);

void leituraDaMatriz(MatrizEsparsa * matriz);

MatrizEsparsa * desalocaMatrizEsparsa(MatrizEsparsa* matrizEsparsa);

#endif