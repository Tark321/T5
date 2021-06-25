#ifndef __ITEM__H
#define __ITEM__H

#include "lista.h"

typedef void *Item;

/**Cria uma estrutura Item utilizando esta funcao como contructor
 * Recebe uma chave e uma info
 * Retorna um item
 **/
Item createItem(char chave[], Info valor);

/**Aloca memoria para um item, sem inicializacao
 * Retorna uma estrutura item
 * Recebe tamCh e tamRec para utilizacao
 **/
Item alocarItem(int tamCh, int tamRec);

/**Funcao de busca/get para um item
 * Recebe um item como parametro
 * Retorna a chave deste item
 **/
char* getChaveItem(Item item);

/**Funcao de busca/get para um item
 * Recebe um item como parametro
 * Retorna o valor deste item
 **/
Info getValorItem(Item item);

/**Funcao de mudanca/get para um item
 * Recebe um item e a info de mudanca como parametro
 * Muda o valor deste item
 **/
void setValorItem(Item item, Info valor);

/**Funcao de desalocacao de memoria
 * Recebe um item como parametro
 * Desaloca o item e o valor deste
 **/
void desalocaValorItem(Item item);

/**Funcao de desalocacao de memoria
 * Recebe um item como parametro
 * Desaloca apenas o item
 **/
void desalocaItem(Item item);

#endif