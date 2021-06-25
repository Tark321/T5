#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vertice.h"

typedef struct vert
{
    char id[100];
    Ponto ponto;
}StructVertice;

Vertice criaVertice(char id[], double x, double y)
{
    StructVertice* v = (StructVertice*) malloc(sizeof(StructVertice));
    strcpy(v->id, id);
    v->ponto = criaPonto(x, y);

    return v;
}

char* getVerticeId(Vertice vertice)
{
    StructVertice* v = (StructVertice*) vertice;
    return v->id;
}

Ponto getVerticePonto(Vertice vertice)
{
    StructVertice* v = (StructVertice*) vertice;
    return v->ponto;
}

void setVerticeId(Vertice vertice, char id[])
{
    StructVertice* v = (StructVertice*) vertice;
    strcpy(v->id, id);
}

void setVerticePonto(Vertice vertice, Ponto p)
{
    StructVertice* v = (StructVertice*) vertice;
    v->ponto = p;
}

void desenhaVertice(Vertice vertice, Lista listaQry[])
{
    StructVertice* v = (StructVertice*) vertice;
    Circulo c = criaCirculo("0", 10, getPontoX(v->ponto), getPontoY(v->ponto), "2", "blue", "blue", 1);
    insert(listaQry[3], c); 
    Texto t = criaTexto("0", getPontoX(v->ponto), getPontoY(v->ponto), "black", "black", v->id);
    insert(listaQry[4], t);
}
void desalocaVertice(Vertice vertice)
{
    StructVertice* v = (StructVertice*) vertice;
    free(v->ponto);
    free(v);
}