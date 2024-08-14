#include <stdio.h>
#include <stdlib.h>
#include "automato.h"

void lerQuantidades(int *tam, int *geracoes) 
{
    scanf("%d %d", tam, geracoes);
}

int ** alocarReticulado(int tam) 
{
    int ** matriz = (int **) malloc(sizeof(int*) * tam);

    if(matriz == NULL) {
        printf("Memoria insuficiente!\n");
        exit(1);
    }

    for (int i = 0; i < tam; i++) {
        matriz[i] = malloc(sizeof(int) * tam);

        if (matriz[i] == NULL) {

            for(int j = 0; j < i; j++)
                free(matriz[j]);

            free(matriz);

            printf("Memoria insuficiente!\n");
            exit(1);

        }
    }

    return matriz;
}

void desalocarReticulado(int **automato, int tam)
{
    for (int i = 0; i < tam; i++)
        free(automato[i]);
    free(automato);
}

void leituraReticulado(int **automato, int tam)
{
    for (int i = 0; i < tam; i++)
        for (int j = 0; j < tam; j++)
            scanf("%d", &automato[i][j]);
}

void evoluirReticulado(int **automato, int **matrizAuxiliar, int geracoes, int tam, int cont)
{
    for (int linha = 0; linha < tam; linha++) {
        for (int coluna = 0; coluna < tam; coluna++) { // iterando pelos elementos da matriz
            
            cont = 0;

            for (int k = linha - 1; k <= linha + 1; k++) {

                if (k >= 0 && k < tam) { // verifica se k esta dentro dos limites de dimensão da matriz

                    for (int l = coluna - 1; l <= coluna + 1; l++) {

                        if (l >= 0 && l < tam) { // verifica se l esta dentro dos limites de dimensão da matriz
                            if (automato[k][l] == 1) {
                                cont++;
                            }
                        }

                    }

                }

            }

            if (automato[linha][coluna] == 1) { // caso a celula esteja viva

                cont--; /* subtrai de cont a contagem da propria celula, pois so importam as celulas adjacentes */

                if (cont == 2 || cont == 3) {
                    matrizAuxiliar[linha][coluna] = 1;
                } else {
                    matrizAuxiliar[linha][coluna] = 0;
                }
            } else { // caso a celula esteja morta
                if (cont == 3) {
                    matrizAuxiliar[linha][coluna] = 1;
                } else {
                    matrizAuxiliar[linha][coluna] = 0;
                }
            }

        }
    }

    /* atribuicao dos elementos da matrizAuxiliar para o automato principal */
    for (int i = 0; i < tam; i++) 
        for (int j = 0; j < tam; j++)    
            automato[i][j] = matrizAuxiliar[i][j];

    geracoes--;

    if (geracoes != 0) /* enquanto nao alcancar a geracao zero, a funcao chamara a si mesmo recurssivamente */
        evoluirReticulado(automato, matrizAuxiliar, geracoes, tam, cont);
}

void imprimeReticulado(int **automato, int tam)
{
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++)
            printf("%d ", automato[i][j]);
        printf("\n");
    }
}