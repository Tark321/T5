#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashTable.h"

typedef struct ht
{
    Lista *table;
    int tamanho;
}HashStruct;

HashTable createTable(int tamanho)
{
    HashStruct* ht = (HashStruct*) malloc(sizeof(HashStruct));
    ht->tamanho = tamanho;
    ht->table = (Lista*) malloc(sizeof(Lista) * tamanho);

    for(int i = 0; i < tamanho; i++)
    {
        ht->table[i] = create();
    }

    return ht;
}

int hashKey(char key[], int tam)
{
    int som = 0;
    int index;
    int j = strlen(key);

    for(int i=0; i < j; i++)
    {
        som = som + key[i];
    }

    index = som%tam;

    return index;

}

void insertHTable(HashTable t, char key[], Item value)
{
    HashStruct *ht = (HashStruct*) t;
    Item item = createItem(key, value); 
    int index = hashKey(key, ht->tamanho);
    insert(ht->table[index], item);
}

void deleteItemTable(HashTable t, char key[], int flag)
{
    HashStruct *ht = (HashStruct*) t;
    int index = hashKey(key, ht->tamanho);
    void (*desaloca[2])(Item) = {desalocaItem, desalocaValorItem};
    
    for(No aux = getFirst(ht->table[index]); aux != NULL; aux = getNext(aux))
    {
        Item i =  getInfo(aux);
        
        if (strcmp(getChaveItem(i), key) == 0) 
        {
            removerNo(ht->table[index], aux, desaloca[flag]);
            return;
        }
    }
    
}

Item getValue(HashTable t, char key[])
{
    HashStruct *ht = (HashStruct*) t;
    int index = hashKey(key, ht->tamanho);

    for(No aux = getFirst(ht->table[index]); aux != NULL; aux = getNext(aux))
    {
        Item i = getInfo(aux);

        if(strcmp(getChaveItem(i), key) == 0) 
        {
            return getValorItem(i);
        }
    }

    return NULL;
}

void mudaValor(HashTable t, char key[], Info novo)
{
    HashStruct *ht = (HashStruct*) t;
    int index = hashKey(key, ht->tamanho);

    for(No aux = getFirst(ht->table[index]); aux != NULL; aux = getNext(aux))
    {
        Item i = getInfo(aux);
        if(strcmp(getChaveItem(i), key) == 0) 
        {
            setValorItem(i, novo);
            return;
        }
    }
}

void deleteHTable(HashTable t, int flag)
{
    HashStruct *ht = (HashStruct*) t;
    void (*desaloca[2])(Item) = {desalocaItem, desalocaValorItem};

    for(int i=0; i < ht->tamanho; i++)
    {
        removeList(ht->table, desaloca[flag]);      
    }

    if(ht->table != NULL) 
    {
        free(ht->table);
    }

    free(ht);
}

void printHashTable(HashTable t)
{
    HashStruct *ht = (HashStruct*) t;

    for(int i = 0; i < ht->tamanho; i++)
    {
        No aux = getFirst(ht->table[i]);
        while (aux != NULL) 
        {
            Item i = getInfo(aux);
            printf("%s: %s\n", getChaveItem(i), (char*)getValorItem(i));
            aux = getNext(aux);
        }
    } 
}

void percorreHashTable(HashTable t, void (*f)(void*, void*), Info extraInf)
{
    HashStruct *ht = (HashStruct*) t;

    for(int i = 0; i < ht->tamanho; i++)
    {
        No aux = getFirst(ht->table[i]);
        while(aux != NULL)
        {
            Item i = getInfo(aux);
            f(i,extraInf);
            aux = getNext(aux);
        }
    }
}
