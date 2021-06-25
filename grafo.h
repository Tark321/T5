#ifndef __GRAFO_H
#define __GRAFO_H

#include "lista.h"
#include "linha.h"
#include "vertice.h"
#include "aresta.h"
#include "auxiliar.h"
#include "hashTable.h"

typedef void* Grafo;
typedef void* ListAdjc;

/**Cria um grafo utilizando a funcao create, o que na verdade cria uma lista, que sera utilizada
 * para representarmos o grafo, por isso nada 'e passado como parametro, ja que apenas a lista e criada
 * */ 
Grafo criaGrafo();

Vertice getGrafoVertice(ListAdjc adjcList);

Lista getGrafoAresta(ListAdjc adjcList);

ListAdjc getGrafoListAdjc(Grafo grafo, char id[]);

void insereVertice(Grafo grafo, Vertice vertice);

void insereAresta(Grafo grafo, Aresta aresta, char id[]);

void desalocaAdjcList(ListAdjc adjc);

void desalocaGrafo(Grafo grafo);

void desenhaAresta(Grafo grafo, ListAdjc adjc, Aresta aresta, Lista listaQry[]);

void desenhaGrafo(Grafo grafo, Lista listaQry[]);

void removeVerticesIsolados(Grafo grafo);

Grafo criaGrafoNDirecionado(Grafo grafo);

Grafo prim(Grafo grafo);

Lista dijkstra(Grafo grafo, char ini[], char fin[], double* disTotal, double getPeso(Aresta aresta));

#endif