#include "automato.h"

typedef struct automatoCelular {
    MatrizEsparsa * automato;
    MatrizEsparsa * automatoAuxiliar;
} AutomatoCelular;

AutomatoCelular * alocarReticulado() {
    int dimensao;
    scanf("%d", &dimensao);

    AutomatoCelular *new = (AutomatoCelular*) malloc(sizeof(AutomatoCelular));

    if(new == NULL) {
        printf("Não há memória suficiente.\n");
        exit(1);
    }

    new->automato = alocaMatrizEsparsa(dimensao);
    new->automatoAuxiliar = alocaMatrizEsparsa(dimensao);

    iniciaListas(new->automato);
    iniciaListas(new->automatoAuxiliar);

    return new;
}

AutomatoCelular * desalocarReticulado(AutomatoCelular ** automato) {
    (*automato)->automato = desalocaMatrizEsparsa((*automato)->automato);
    (*automato)->automatoAuxiliar = desalocaMatrizEsparsa((*automato)->automatoAuxiliar);
    free(*automato);
    return NULL;
}

void leituraReticulado(AutomatoCelular * automato) {
    leituraDaMatriz(automato->automato);
}

void evoluirReticulado(AutomatoCelular *automato, int geracoes) {
    while(geracoes > 0) {
        evoluirMatriz(&automato->automato, &automato->automatoAuxiliar);
        geracoes--;
    }
}

void imprimeReticulado(AutomatoCelular * automato) {
    imprimeMatriz(automato->automato);
}
