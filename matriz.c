#include "matriz.h"

typedef struct celula {

    int linha;
    int coluna;
    struct celula *proxColuna;
    struct celula *proxLinha;

} Celula; // criacao da lista 

typedef struct matriz {

    // cada posicao dos vetores abaixo serve como "cabeca" para a lista correspondente:
    Celula **linhas; // vetor com listas referentes as linhas
    Celula **colunas; // vetor com listas referentes as colunas
    int dimensao;

} MatrizEsparsa; 

MatrizEsparsa * alocaMatrizEsparsa(int dimensaoFornecida) {

    MatrizEsparsa * matrizEsparsa = (MatrizEsparsa*) malloc(sizeof(MatrizEsparsa));

    if (matrizEsparsa == NULL) {
        printf("Não há memória disponível.\n");
        exit(1);
    }

    matrizEsparsa->dimensao = dimensaoFornecida;

    // cria o vetor para "cabecas" das listas de linhas
    matrizEsparsa->linhas = (Celula**) malloc( (matrizEsparsa->dimensao) * sizeof(Celula*) );

    if (matrizEsparsa->linhas == NULL) {
        printf("Não há memória disponível.\n");
        free(matrizEsparsa);
        exit(1);
    }

    // cria o vetor para "cabecas" das listas de colunas
    matrizEsparsa->colunas = (Celula**) malloc( (matrizEsparsa->dimensao) * sizeof(Celula*) ); 

    if (matrizEsparsa->colunas == NULL) {
        printf("Não há memória disponível.\n");
        free(matrizEsparsa->linhas);
        free(matrizEsparsa);
        exit(1);
    }

    // printf("Matriz alocada com sucesso.\n");
    return matrizEsparsa;

}

void iniciaListas(MatrizEsparsa *matriz) {

    for(int i = 0; i < matriz->dimensao; i++) { /* itera por cada posicao do vetor de linhas e colunas */

        matriz->linhas[i] = (Celula*) malloc(sizeof(Celula)); /* aloca celula para atuar como cabeca da lista de linhas */
        matriz->linhas[i]->proxColuna = matriz->linhas[i]; /* aponta para si mesmo, respeitando a lista circular */
        matriz->linhas[i]->linha = -1; /* os indices da cabeca sao inicializados como -1 para nao prejudicarem a logica
        de impressao da matriz */
        matriz->linhas[i]->coluna = -1;


        matriz->colunas[i] = (Celula*) malloc(sizeof(Celula));
        matriz->colunas[i]->proxLinha = matriz->colunas[i]; 
        matriz->colunas[i]->linha = -1; 
        matriz->colunas[i]->coluna = -1;

    }

}

bool listaLinhaEhVazia(Celula *pLista) {
    return pLista->proxColuna == pLista;
}

bool listaColunaEhVazia(Celula *pLista) {
    return pLista->proxLinha == pLista;
}

bool retiraUltimoElementoDaLinha(Celula *pLista) { 

    if (listaLinhaEhVazia(pLista)) 
        return false; 

    Celula *celulaAtual = pLista->proxColuna; /* celulaAtual comeca na primeira celula da lista linha */
    Celula *penultimaCelula = pLista; /* penultimaCelula comeca na cabeca */

    /* lista possui somente uma celula */
    if (celulaAtual->proxColuna == pLista) {
        free(celulaAtual);
        penultimaCelula->proxColuna = pLista; /* cabeca da lista passa a apontar para si propria,
        mantendo o padrao da lista circular */
        return true;
    }

    // busca o penultimo elemento
    while (celulaAtual->proxColuna != pLista) {
        penultimaCelula = celulaAtual;
        celulaAtual = celulaAtual->proxColuna;
    }

    // atualiza o ponteiro do penultimo elemento
    penultimaCelula->proxColuna = pLista;
    free(celulaAtual); 
    return true;

}

void liberaCabecas(MatrizEsparsa *matriz) {
    for(int i = 0; i < matriz->dimensao; i++) {
        free(matriz->linhas[i]);
        free(matriz->colunas[i]);
    }
}

void liberaMatriz(MatrizEsparsa *matriz) {

    for(int i = 0; i < matriz->dimensao; i++) 
        while( retiraUltimoElementoDaLinha(matriz->linhas[i]) );

    liberaCabecas(matriz);

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
    if( listaLinhaEhVazia(matriz->linhas[indiceLinha]) ) {
        
        matriz->linhas[indiceLinha]->proxColuna = new;
        new->proxColuna = matriz->linhas[indiceLinha]; /* seguindo o principio da lista circular, o ultimo elemento
        aponta para o primeiro. Como existe apenas um elemento, ele aponta para a cabeca */

    } else {

        Celula *aux = matriz->linhas[indiceLinha];

        while( aux->proxColuna != matriz->linhas[indiceLinha] )
            aux = aux->proxColuna;

        aux->proxColuna = new;
        new->proxColuna = matriz->linhas[indiceLinha]; /* faz o novo elemento apontar para a cabeca,
        respeitando a lista circular */
        aux = NULL;

    }

    // adicionando celula na lista de coluna
    if( listaColunaEhVazia(matriz->colunas[indiceColuna]) ) {

        matriz->colunas[indiceColuna]->proxLinha = new;
        new->proxLinha = matriz->colunas[indiceColuna];

    } else {

        Celula *aux = matriz->colunas[indiceColuna];

        while ( aux->proxLinha != matriz->colunas[indiceColuna] )
            aux = aux->proxLinha;

        aux->proxLinha = new;
        new->proxLinha = matriz->colunas[indiceColuna]; 

    }

    // printf("Celula viva adicionada.\n"); 

}

void leituraDaMatriz(MatrizEsparsa * matriz) {

    int estadoCelula;

    for(int i = 0; i < matriz->dimensao; i++)
        for(int j = 0; j < matriz->dimensao; j++) {
            scanf("%d", &estadoCelula);
            if(estadoCelula == 1) { /* apenas as celulas vivas sao armezenadas na matriz */
                // printf("Leu celula viva.\n");
                adicionarCelulaNaMatriz(i, j, matriz);
            }
        }

}

MatrizEsparsa * desalocaMatrizEsparsa(MatrizEsparsa * matrizEsparsa) {
    liberaMatriz(matrizEsparsa);
    return NULL;
}

bool celulaEhViva(MatrizEsparsa * matrizEsparsa, int indiceLinha, int indiceColuna) {

    Celula *aux = matrizEsparsa->linhas[indiceLinha]->proxColuna;

    while(aux != matrizEsparsa->linhas[indiceLinha]) {
        if(aux->linha == indiceLinha && aux->coluna == indiceColuna) /* se nao ha correspondencia entre a coluna
        e o indice de coluna da celula, eh porque ela nao existe naquela posicao. Portanto, a posicao possui uma celula morta. */
            return true;
        aux = aux->proxColuna;
    }

    return false;

}

void imprimeMatriz(MatrizEsparsa *matrizEsparsa) {

    for(int i = 0; i < matrizEsparsa->dimensao; i++) {
        for(int j = 0; j < matrizEsparsa->dimensao; j++) {
            if(celulaEhViva(matrizEsparsa, i, j))
                printf("1 ");
            else
                printf("0 ");
        }
        printf("\n");
    }

}

void copiaMatriz(MatrizEsparsa **matrizPrincipal, MatrizEsparsa **matrizAuxiliar) {

    /* "reseta" a matriz principal para receber a nova configuracao da matriz auxiliar */
    liberaMatriz(*matrizPrincipal);

    *matrizPrincipal = alocaMatrizEsparsa((*matrizAuxiliar)->dimensao);
    if (*matrizPrincipal == NULL) {
        printf("Erro ao alocar matriz principal.\n");
        exit(1);
    }

    iniciaListas(*matrizPrincipal);

    /* copia celulas vivas da matriz auxiliar para a nova matriz principal */
    for(int indiceLinha = 0; indiceLinha < (*matrizAuxiliar)->dimensao; indiceLinha++) {

        Celula *celulaAtual = (*matrizAuxiliar)->linhas[indiceLinha]->proxColuna;
        
        while (celulaAtual != (*matrizAuxiliar)->linhas[indiceLinha]) {
            adicionarCelulaNaMatriz(celulaAtual->linha, celulaAtual->coluna, *matrizPrincipal);
            celulaAtual = celulaAtual->proxColuna;
        }

    }

    /* em seguida, a matriz auxiliar eh resetada para a evolucao seguinte: */
    liberaMatriz(*matrizAuxiliar);

    *matrizAuxiliar = alocaMatrizEsparsa((*matrizPrincipal)->dimensao);
    if (*matrizAuxiliar == NULL) {
        printf("Erro ao alocar matriz auxiliar.\n");
        exit(1);
    }
    iniciaListas(*matrizAuxiliar);
}

void evoluirMatriz(MatrizEsparsa **matrizEsparsa, MatrizEsparsa **matrizAuxiliar) {
    
    for(int indiceLinha = 0; indiceLinha < (*matrizEsparsa)->dimensao; indiceLinha++) {
        for(int indiceColuna = 0; indiceColuna < (*matrizEsparsa)->dimensao; indiceColuna++) {

            int cont = 0;
            
            for(int k = indiceLinha-1; k <= indiceLinha+1; k++) /* itera pelas linhas adjacentes */
                if(k >= 0 && k < (*matrizEsparsa)->dimensao) /* verifica se as celulas adjacentes estao numa posicao valida na matriz */
                    for(int l = indiceColuna-1; l <= indiceColuna+1; l++) /* itera pelas colunas adjacentes */
                        if(l >= 0 && l < (*matrizEsparsa)->dimensao)
                            if(celulaEhViva(*matrizEsparsa, k, l))
                                cont++;

            if(celulaEhViva(*matrizEsparsa, indiceLinha, indiceColuna)) {
                cont--; /* subtrai a propria celula da contagem de celulas vivas adjacentes */
                if(cont == 2 || cont == 3) /* se deve estar viva, a celula eh adicionada na nova matriz auxiliar */
                    adicionarCelulaNaMatriz(indiceLinha, indiceColuna, *matrizAuxiliar);
            } else
                if(cont == 3) /* caso a celula morta tem tres vizinhos vivos, torna-se viva */
                    adicionarCelulaNaMatriz(indiceLinha, indiceColuna, *matrizAuxiliar);

        }

    }

    /* atualiza a matriz original com a matriz auxiliar */
    copiaMatriz(matrizEsparsa, matrizAuxiliar);

}


