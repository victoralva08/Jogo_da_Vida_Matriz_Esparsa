#include <stdio.h>
#include "matriz.h"

#ifndef automatoCelular_h
#define automatoCelular_h

typedef struct automatoCelular AutomatoCelular;

AutomatoCelular * alocarReticulado() ;

AutomatoCelular * desalocarReticulado(AutomatoCelular ** automato);

void leituraReticulado(AutomatoCelular * automato);

void evoluirReticulado(AutomatoCelular *automato, int geracoes);

void imprimeReticulado(AutomatoCelular * automato) ;

#endif