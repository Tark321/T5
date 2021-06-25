#ifndef __VERTICE_H
#define __VERTICE_H

#include "ponto.h"
#include "texto.h"
#include "lista.h"
#include "texto.h"
#include "circulo.h"

typedef void* Vertice;

/**Esta funcao cria vertices para serem utilizados nos grafos
 * Precisa do id, x, e um y para a criacao
 * retorna o vertice criado
 * */
Vertice criaVertice(char id[], double x, double y);

/**Obtem o id do vertice
 * Precida de um void pointer vertice
 * retorna o id do vertice passado
 * */
char* getVerticeId(Vertice vertice);

/**Obtem o ponto do vertice
 * Precida de um void pointer vertice
 * retorna o ponto do vertice passado
 * */
Ponto getVerticePonto(Vertice vertice);

/**Faz uma mudanca no id do vertice
 * Precida de um void pointer vertice e o novo id
 * retorna nada apenas muda o antigo id para o novo
 * */
void setVerticeId(Vertice vertice, char id[]);

/**Faz uma mudanca no ponto do vertice
 * Precida de um void pointer vertice e o novo ponto
 * retorna nada apenas muda o antigo ponto para o novo
 * */
void setVerticePonto(Vertice vertice, Ponto p);

/**
 * 
 * */
void desenhaVertice(Vertice vertice, Lista listaQry[]);

/** Desaloca o void pointer vertice
 * Precisa do void pointer vertice que sera desalocado
 * */
void desalocaVertice(Vertice vertice);

#endif