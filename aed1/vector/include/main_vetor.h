#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include "vetor.h"
#include <time.h>
#include <math.h>

double calcula_media(double vet[], int quant_testes);

double calcula_desvio_padrao(double vet[], int quant_testes, double media);

int main();

#endif // MAIN_H