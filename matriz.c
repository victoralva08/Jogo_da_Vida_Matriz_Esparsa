#include "matriz.h"

typedef struct celula {

    int linha;
    int coluna;
    struct Celula *proxLinha;
    struct Celula *proxColuna;

} Celula; // criacao da lista 

typedef struct matriz {

    // cada posicao dos vetores abaixo serve como "cabeca" para a lista correspondente:
    Celula ** linhas; // vetor com listas referentes as linhas
    Celula ** colunas; // vetor com listas referentes as colunas
    int dimensao;

} MatrizEsparsa; 

MatrizEsparsa * alocaMatrizEsparsa(int dimensaoFornecida) {

    MatrizEsparsa * matrizEsparsa = (MatrizEsparsa*) malloc(sizeof(MatrizEsparsa));

    if (matrizEsparsa == NULL) {
        printf("Não há memória disponível.");
        exit(1);
    }

    matrizEsparsa -> dimensao = dimensaoFornecida;

    // cria o vetor para "cabecas" das listas de linhas
    matrizEsparsa -> linhas = (Celula**) malloc( (matrizEsparsa -> dimensao) * sizeof(Celula*) );

    if (matrizEsparsa -> linhas == NULL) {
        printf("Não há memória disponível.");
        free(matrizEsparsa);
        exit(1);
    }

    // cria o vetor para "cabecas" das listas de colunas
    matrizEsparsa -> colunas = (Celula**) malloc( (matrizEsparsa -> dimensao) * sizeof(Celula*) ); 

    if (matrizEsparsa -> colunas == NULL) {
        printf("Não há memória disponível.");
        free(matrizEsparsa -> linhas);
        free(matrizEsparsa);
        exit(1);
    }

    return matrizEsparsa;

}

void iniciaListas(MatrizEsparsa *matriz) {

    for(int i = 0; i < matriz->dimensao; i++) {
        matriz->linhas[i] = NULL;
        matriz->colunas[i] = NULL;
    }

}

bool listaEhVazia(Celula *pLista) {
    return pLista == NULL;
}

bool retiraUltimoElementoDaLista(Celula **pLista) { // verificar se eh O(n)!!!

    if (listaEhVazia(*pLista)) 
        return false; 

    Celula *celulaAtual = *pLista;
    Celula *penultimaCelula = NULL;

    // lista possui somente uma celula
    if (celulaAtual->proxLinha == *pLista) {
        free(celulaAtual);
        *pLista = NULL; // cabeca da lista eh atualizado para NULL para indicar que a lista esta vazia
        return true;
    }

    // busca o penultimo elemento
    while (celulaAtual->proxLinha != *pLista) {
        penultimaCelula = celulaAtual;
        celulaAtual = celulaAtual->proxLinha;
    }

    // atualiza o ponteiro do penúltimo elemento
    penultimaCelula->proxLinha = *pLista;
    free(celulaAtual); 
    return true;

}

void liberaMatriz(MatrizEsparsa *matriz) {

    for(int i = 0; i < matriz->dimensao; i++) {
        while( retiraUltimoElementoDaLista( &matriz->linhas[i] ) );
        while( retiraUltimoElementoDaLista( &matriz->colunas[i] ) );
    }

    free(matriz->linhas);
    free(matriz->colunas);
    free(matriz);

}

void adicionarCelulaNaMatriz(int indiceLinha, int indiceColuna, MatrizEsparsa *matriz) {

    Celula *new = (Celula*) malloc(sizeof(Celula));

    if(new == NULL) {
        printf("Não há memória disponível.\n");
        exit(1);
    }

    new->linha = indiceLinha;
    new->coluna = indiceColuna;

    // adicionando celula na lista de linha
    if( listaEhVazia(matriz->linhas[indiceLinha]) ) {
        
        matriz->linhas[indiceLinha] = new;
        new->proxLinha = new; /* seguindo o principio da lista circular, o ultimo elemento
        aponta para o primeiro. Como existe apenas um elemento, ele aponta para si proprio. */

    } else {

        Celula *aux = matriz->linhas[indiceLinha];

        while( aux->proxLinha != matriz->linhas[indiceLinha] )
            aux = aux->proxLinha;

        aux->proxLinha = new;
        new->proxLinha = matriz->linhas[indiceLinha]; /* faz o novo elemento apontar para o primeiro elemento,
        respeitando a lista circular */
        aux = NULL;

    }

    // adicionando celula na lista de coluna
    if( listaEhVazia(matriz->colunas[indiceColuna]) ) {

        matriz->colunas[indiceColuna] = new;
        new->proxColuna = new;

    } else {

        Celula *aux = matriz->colunas[indiceColuna];

        while ( aux->proxColuna != matriz->colunas[indiceColuna] )
            aux = aux->proxColuna;

        aux->proxColuna = new;
        new->proxColuna = matriz->colunas[indiceColuna]; 
        aux = NULL;

    }

}

void leituraDaMatriz(MatrizEsparsa * matriz) {

    int estadoCelula;

    for(int i = 0; i < matriz->dimensao; i++)
        for(int j = 0; j < matriz->dimensao; j++) {
            scanf("%d", &estadoCelula);
            if(estadoCelula == 1) // apenas as celulas vivas sao armezenadas na matriz
                adicionarCelulaNaMatriz(i, j, matriz);
        }

}

MatrizEsparsa * desalocaMatrizEsparsa(MatrizEsparsa* matrizEsparsa) {
    
    for (int i = 0; i < matrizEsparsa->dimensao; i++) {
        Celula* atual = matrizEsparsa->linhas[i];
        while (atual != NULL) {
            Celula* temp = atual;
            atual = atual->proxLinha;
            free(temp);
        }
    }

    // Liberar os arrays de linhas e colunas
    free(matrizEsparsa->linhas);
    free(matrizEsparsa->colunas);

    // Liberar a estrutura matriz
    free(matrizEsparsa);

    return NULL;
}

