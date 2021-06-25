#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "item.h"

typedef struct item{
    char* chave;
    Info valor;
}StructItem;

Item createItem(char chave[], Info valor)
{
    StructItem* i = malloc(sizeof(StructItem));
    i->chave = malloc(sizeof(char) * (strlen(chave) + 1));
    strcpy(i->chave,chave);
    i->valor = valor;
    return i;
}

Item alocarItem(int tamCh, int tamRec)
{
    StructItem* i = malloc(sizeof(StructItem));
    i->chave = malloc(sizeof(char) * tamCh);
    i->valor = malloc(tamRec);
    return i;
}

char* getChaveItem(Item item)
{
    StructItem* i = (StructItem*) item;
    return i->chave;
}

Info getValorItem(Item item)
{
    StructItem* i = (StructItem*) item;
    return i->valor;
}

void setValorItem(Item item, Info valor)
{
    StructItem* i = (StructItem*) item;
    i->valor = valor;
}

void desalocaValorItem(Item item)
{
    StructItem* i = (StructItem*) item;
    free(i->chave);
    free(i->valor);
    free(i);
}

void desalocaItem(Item item)
{
    StructItem* i = (StructItem*) item;
    free(i->chave);
    free(i);
}
