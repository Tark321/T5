#ifndef __LERHASH__H
#define __LERHASH__H

#include "item.h"
#include "lista.h"
#include "hashTable.h"
#include "hashFile.h"
#include "address.h"
#include "pessoa.h"
#include "ponto.h"
#include "comercio.h"
#include "quadtree.h"
#include "auxiliar.h"

void saveHashfile(HashTable ht[], QuadTree estabelecimentos, QuadTree enderecos, char nomebase[]);

void readHashfile(HashTable ht[], QuadTree estabelecimentos, QuadTree enderecos, char nomebase[]);

#endif