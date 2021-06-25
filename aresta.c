#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aresta.h"

typedef struct aresta
{
    double cmp;
    double vm;
    char nome[100];
    char ladoDir[50];
    char ladoEsq[50];
    char vertDestino[100];
}StructAresta;

Aresta criaAresta(double cmp, double vm, char nome[], char ladoDir[], char ladoEsq[], char vertDestino[])
{
    StructAresta* a = (StructAresta*)malloc(sizeof(StructAresta));
    a->vm = vm;
    a->cmp = cmp;
    strcpy(a->nome, nome);
    strcpy(a->ladoDir, ladoDir);
    strcpy(a->ladoEsq, ladoEsq);
    strcpy(a->vertDestino, vertDestino);

    return a;
}

char* getArestaNome(Aresta aresta)
{
    StructAresta* a = (StructAresta*)aresta;
    return a->nome;
}

char* getArestaLadoDir(Aresta aresta)
{
    StructAresta* a = (StructAresta*)aresta;
    return a->ladoDir;
}

char* getArestaLadoEsq(Aresta aresta)
{
    StructAresta* a = (StructAresta*)aresta;
    return a->ladoEsq;
}

char* getArestaVertDestino(Aresta aresta)
{
    StructAresta* a = (StructAresta*)aresta;
    return a->vertDestino;
}

double getArestaCmp(Aresta aresta)
{
    StructAresta* a = (StructAresta*)aresta;
    return a->cmp;
}

double getArestaVm(Aresta aresta)
{
    StructAresta* a = (StructAresta*)aresta;
    return a->vm;
}

double getArestaTempo(Aresta aresta)
{
    StructAresta* a = (StructAresta*)aresta;
    return a->cmp/a->vm;
}
