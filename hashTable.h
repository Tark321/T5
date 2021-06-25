#ifndef __HASHTABLE_H
#define __HASHTABLE_H

#include "lista.h"
#include "item.h"

typedef void *InfoTable;
typedef void *HashTable;

HashTable createTable(int tamanho);

int hashKey(char key[], int tam);

void insertHTable(HashTable t, char key[], Item value);

void deleteItemTable(HashTable t, char key[], int flag);

Item getValue(HashTable t, char key[]);

void mudaValor(HashTable t, char key[], Info novo);

void deleteHTable(HashTable t, int flag);

void printHashTable(HashTable t);

void percorreHashTable(HashTable t, void (*f)(void*, void*), Info extraInf);

#endif