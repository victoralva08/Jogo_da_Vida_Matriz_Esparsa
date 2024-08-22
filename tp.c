/* Victor Ferreira Alvarenga */

#include "matriz.h"
#include "automato.h"

int main() {
    int geracoes;
    AutomatoCelular * automato;

    automato = alocarReticulado();
    scanf("%d", &geracoes);
    
    leituraReticulado(automato);

    evoluirReticulado(automato, geracoes);

    imprimeReticulado(automato);

    automato = desalocarReticulado(&automato);
    
    return 0;
}