#ifndef __ARESTA_H
#define __ARESTA_H

typedef void* Aresta;

Aresta criaAresta(double cmp, double vm, char nome[], char ladoDir[], char ladoEsq[], char vertDestino[]);

char* getArestaNome(Aresta aresta);

char* getArestaLadoDir(Aresta aresta);

char* getArestaLadoEsq(Aresta aresta);

char* getArestaVertDestino(Aresta aresta);

double getArestaCmp(Aresta aresta);

double getArestaVm(Aresta aresta);

double getArestaTempo(Aresta aresta);

#endif