#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lerHash.h"

void auxInsert(Info info, Lista l)
{
    insert(l, info);
}

void listToHashfile(Hashfile hf, Lista l)
{
    for(No node = getFirst(l); node != NULL; node = getNext(node))
    {
        fwriteRec(hf, getInfo(node));
    }
}

void listToHashTable(HashTable ht, Lista l)
{
    for(No node = getFirst(l); node != NULL; node = getNext(node))
    {
        insertHTable(ht, getChaveItem(getInfo(node)), getValorItem(getInfo(node)));
    }
}

void saveHashfile(HashTable ht[], QuadTree estabelecimentos, QuadTree enderecos, char nomebase[])
{
    char fileEC[80];
    char fileDes[80];
    char fileP[80];
    char fileEnd[80];
    Hashfile hf[4];

    sprintf(fileEC,"%s-ec.dat", nomebase);
    sprintf(fileDes,"%s-des.dat", nomebase);
    sprintf(fileP,"%s-pes.dat", nomebase);
    sprintf(fileEnd,"%s-end.dat", nomebase);
    
    hf[0] = fcreateHF(fileEC,107,10,getComercioSize,20);
    hf[1] = fcreateHF(fileEnd,107,10,getAddressSize,20);
    hf[2] = fcreateHF(fileDes,107,10,255,20);
    hf[3] = fcreateHF(fileP,107,10,getPessoaSize,20);

    Lista lAux[4];
    Lista lEst = create();
    Lista lEnd = create();

    for(int i = 0; i < 4; i++)
    {
        lAux[i] = create();
    }

    percorreLarguraQt(estabelecimentos, auxInsert, lEst);


    for(No node = getFirst(lEst); node != NULL; node = getNext(node)) 
    {
        insert(lAux[0], createItem(getComercioCnpj(getInfo(node)), getInfo(node)));
    }

    percorreLarguraQt(enderecos, auxInsert, lEnd);

    for(No node = getFirst(lEnd); node != NULL; node = getNext(node)) 
    {
        listInsert(lAux[1], createItem(getAddressCpf(getInfo(node)), getInfo(node)));
    }

    for(int i = 2; i < 4; i++)
    {
        percorreHashTable(ht[i - 1], auxInsert, lAux[i]);
    }

    for(int i = 0; i < 4; i++)
    {
        listToHashfile(hf[i], lAux[i]);
        fcloseHF(hf[i]);
    }

    removeList(lEst, NULL);
    removeList(lEnd, NULL);
    removeList(lAux[0], desalocaItem);
    removeList(lAux[1], desalocaItem);
    removeList(lAux[2], NULL);
    removeList(lAux[3], NULL);
}

void readHashfile(HashTable ht[], QuadTree estabelecimentos, QuadTree enderecos, char nomebase[])
{
    char fileEC[80];
    char fileDes[80];
    char fileP[80];
    char fileEnd[80];

    sprintf(fileEC,"%s-ec.dat", nomebase);
    sprintf(fileDes,"%s-des.dat", nomebase);
    sprintf(fileP,"%s-pes.dat", nomebase);
    sprintf(fileEnd,"%s-end.dat", nomebase);

    Hashfile hf[4];
    hf[0] = fopenHF(fileEC);
    hf[1] = fopenHF(fileEnd);
    hf[2] = fopenHF(fileDes);
    hf[3] = fopenHF(fileP);

    Lista lAux[4];

    for(int i = 0; i < 4; i++)
    {
        lAux[i] = create();
    }
    for(int i = 0; i < 4; i++)
    {
        dumpFileHF(hf[i], lAux[i], auxInsert);
        fcloseHF(hf[i]);
    }

    Lista end = create();
    Lista est = create();

    for(No node = getFirst(lAux[1]); node != NULL; node = getNext(node))
    {
        Address e = getValorItem(getInfo(node));
        setAddressPonto(e, getPontoX(getAddressPonto(e)), getPontoY(getAddressPonto(e)));
        insert(end, e);
    }

    for(No node = getFirst(lAux[0]); node != NULL; node = getNext(node))
    {
        Comercio e = getValorItem(getInfo(node));
        setComercioPonto(e, getPontoX(getComercioPonto(e)), getPontoY(getComercioPonto));
        insert(est, e);
    }

    balancearQt(estabelecimentos, est, getComercioPonto, swapComercio);
    balancearQt(enderecos, end, getAddressPonto, swapAddress);

    for(int i = 1; i < 4; i++)
    {
        listToHashTable(ht[i - 1], lAux[i]);
        removeList(lAux[i], desalocaItem);
    }
    
    removeList(est, NULL);
    removeList(end, NULL);
    removeList(lAux[0], desalocaItem);
}

