#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

int main() {

    int dimensao;
    MatrizEsparsa *matriz;
    scanf("%d", &dimensao);

    matriz = alocaMatrizEsparsa(dimensao);

    matriz = desalocaMatrizEsparsa(matriz);

    return 0;
}