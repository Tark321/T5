#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grafo.h"

typedef struct grafo
{
    Vertice inicio;
    Lista aresta;
}StructAdjacencia;

Grafo criaGrafo()
{
    Lista grafo = create();
    return grafo;
}

Vertice getGrafoVertice(ListAdjc adjcList)
{
    StructAdjacencia* l = (StructAdjacencia*) adjcList;
    return l->inicio;
}

Lista getGrafoAresta(ListAdjc adjcList)
{
    StructAdjacencia* l = (StructAdjacencia*) adjcList;
    return l->aresta;
}

ListAdjc getGrafoListAdjc(Grafo grafo, char id[])
{
    No no;
    for(no = getFirst(grafo); no != NULL; no = getNext(no))
    {
        StructAdjacencia* l = getInfo(no);

        if(strcmp(id, getVerticeId(l->inicio)) == 0)
        {
            return l;
        }
    }

    return NULL;
}

void insereVertice(Grafo grafo, Vertice vertice)
{
    StructAdjacencia* l = (StructAdjacencia*)malloc(sizeof(StructAdjacencia));
    l->inicio = vertice;
    l->aresta = create();
    insert(grafo, l);
}

void insereAresta(Grafo grafo, Aresta aresta, char id[])
{
    StructAdjacencia* l = getGrafoListAdjc(grafo, id);

    if(l == NULL)
    {
        printf("VERTICE INVALIDO\n");
        return;
    }

    insert(l->aresta, aresta);
}

void desalocaAdjcList(ListAdjc adjc)
{
    StructAdjacencia* l = (StructAdjacencia*) adjc;
    removeList(l->aresta, NULL);
    desalocaVertice(l->inicio);
    free(adjc);
}

void desalocaGrafo(Grafo grafo)
{
    removeList(grafo, desalocaAdjcList);
}

void desenhaAresta(Grafo grafo, ListAdjc adjc, Aresta aresta, Lista listaQry[])
{
    StructAdjacencia* l = (StructAdjacencia*) adjc;
    StructAdjacencia* lAux = (StructAdjacencia*)getGrafoListAdjc(grafo, getArestaVertDestino(aresta));
    double x1 = getPontoX(getVerticePonto(l->inicio));
    double y1 = getPontoY(getVerticePonto(l->inicio));
    double x2 = getPontoX(getVerticePonto(lAux->inicio));
    double y2 = getPontoY(getVerticePonto(lAux->inicio));
    Linha linha = criaLinha(x1, y1, x2, y2, "red");
    insert(listaQry[2], linha);
}

void desenhaGrafo(Grafo grafo, Lista listaQry[])
{
    for(No noAux = getFirst(grafo); noAux != NULL; noAux = getNext(noAux))
    {
        ListAdjc aux = getInfo(noAux);
        for(No auxList = getFirst(getGrafoAresta(aux)); auxList != NULL; auxList = getNext(auxList))
        {
            desenhaAresta(grafo, aux, getInfo(auxList), listaQry);
        }

        desenhaVertice(getGrafoVertice(aux), listaQry);
    }
}

void removeVerticesIsolados(Grafo grafo)
{
    Lista visit = create();
    for(No node = getFirst(grafo); node != NULL; node = getNext(node))
    {
        StructAdjacencia *l = getInfo(node);
        if(getTamanhoLista(l->aresta) && !stringNaLista(visit, getVerticeId(l->inicio)))
        {
            char *id = malloc(sizeof(char) * (strlen(getVerticeId(l->inicio)) + 1));
            strcpy(id, getVerticeId(l->inicio));
            insert(visit, id);
        }
        for(No snode = getFirst(l->aresta); snode != NULL; snode = getNext(snode))
        {
            StructAdjacencia *aux = getInfo(snode);
            char *saux = getArestaVertDestino(aux);
            if(!stringNaLista(visit, saux))
            {
                char *id = malloc(sizeof(char) * (strlen(saux) + 1));
                strcpy(id, saux);
                insert(visit, id);
            }
        }
    }

    No tnode = getFirst(grafo);

    while(tnode != NULL)
    {
        StructAdjacencia *l = getInfo(tnode);
        if(!stringNaLista(visit, getVerticeId(l->inicio)))
        {
            No aux = tnode;
            tnode = getNext(tnode);
            removerNo(grafo, aux, desalocaAdjcList);
            continue;
        }
        tnode = getNext(tnode);
    }

    removeList(visit, free);
}

Grafo criaGrafoNDirecionado(Grafo grafo)
{
    Grafo g = criaGrafo();

    for(No no = getFirst(grafo); no != NULL; no = getNext(no))
    {
        ListAdjc l = getInfo(no);
        Vertice v = criaVertice(getVerticeId(getGrafoVertice(l)), getPontoX(getVerticePonto(getGrafoVertice(l))), getPontoY(getVerticePonto(getGrafoVertice(l))));
        insereVertice(g, v);
    }
    for(No no = getFirst(grafo); no != NULL; no = getNext(no))
    {
        ListAdjc l = getInfo(no);
        for(No no = getFirst(getGrafoAresta(l)); no != NULL; no = getNext(no))
        {
            Aresta aresta = getInfo(no);
            Aresta ar1 = criaAresta(getArestaCmp(aresta), getArestaVm(aresta), getArestaNome(aresta), 
            getArestaLadoDir(aresta), getArestaLadoEsq(aresta), getArestaVertDestino(aresta));

            Aresta ar2 = criaAresta(getArestaCmp(aresta), getArestaVm(aresta), getArestaNome(aresta), 
            getArestaLadoDir(aresta), getArestaLadoEsq(aresta), getVerticeId(getGrafoVertice(l)));
            
            insereAresta(g, ar1, getVerticeId(getGrafoVertice(l)));
            insereAresta(g, ar2, getArestaVertDestino(aresta));
        }
    }

    return g;
}

Grafo prim(Grafo grafo)
{
    HashTable hashVist = createTable(1200);
    Grafo agm = criaGrafo();
    Vertice vertice;
    Aresta aresta;
    int primeiro;
    double menorCmp;
    char visitFlag[10] = "visitok";
    char *ini;
    char *fin;
    

    for(No no = getFirst(grafo); no != NULL; no = getNext(no))
    {
        ListAdjc l = getInfo(no);
        Vertice v = getGrafoVertice(l);
        Vertice vert = criaVertice(getVerticeId(v), getPontoX(getVerticePonto(v)), getPontoY(getVerticePonto(v)));
        insereVertice(agm, vert);
    }

    vertice = getGrafoVertice(getInfo(getFirst(grafo)));
    insertHTable(hashVist, getVerticeId(vertice), visitFlag);

    while(1)
    {
        primeiro = 1;

        for(No aux1 = getFirst(grafo); aux1 !=  NULL; aux1 = getNext(aux1))
        {
            StructAdjacencia *l = getInfo(aux1);
            vertice = l->inicio;

            if(getValue(hashVist, getVerticeId(vertice)) != NULL)
            {
                for(No aux2 = getFirst(l->aresta); aux2 != NULL; aux2 = getNext(aux2))
                {
                    if(getValue(hashVist, getArestaVertDestino(getInfo(aux2))) == NULL)
                    {
                        if(primeiro)
                        {
                            ini = getVerticeId(vertice);
                            aresta = getInfo(aux2);
                            fin = getArestaVertDestino(aresta);
                            menorCmp = getArestaCmp(aresta);
                            primeiro = 0;
                        }
                        else if(menorCmp > getArestaCmp(getInfo(aux2)))
                        {
                            ini = getVerticeId(vertice);
                            aresta = getInfo(aux2);
                            fin = getArestaVertDestino(aresta);
                            menorCmp = getArestaCmp(aresta);
                        }
                    }
                }
            }
        }
        if(primeiro)
        {
            break;
        }
        Aresta a1 = criaAresta(getArestaCmp(aresta), getArestaVm(aresta), getArestaNome(aresta), 
        getArestaLadoDir(aresta), getArestaLadoEsq(aresta), fin);
        Aresta a2 = criaAresta(getArestaCmp(aresta), getArestaVm(aresta), getArestaNome(aresta), 
        getArestaLadoDir(aresta), getArestaLadoEsq(aresta), ini);

        insereAresta(agm, a1, ini);
        insereAresta(agm, a2, fin);

        insertHTable(hashVist, fin, visitFlag);
    }
    //deleteHTable(hashVist);
    return agm;
}

Lista dijkstra(Grafo grafo, char ini[], char fin[], double* disTotal, double getPeso(Aresta aresta))
{
    Lista restante = create();
    HashTable distancia = createTable(1200);
    HashTable anterior = createTable(1200);
    double *aux = malloc(sizeof(double));
    *aux = 0;

    insertHTable(distancia, ini, aux);

    for(No no = getFirst(grafo); no != NULL; no = getNext(no))
    {
        insert(restante, getVerticeId(getGrafoVertice(getInfo(no))));
    }

    while(1)
    {
        ListAdjc l = getGrafoListAdjc(grafo, ini);
        double *dAnt = (double*) getValue(distancia, ini);

        for(No no = getFirst(getGrafoAresta(l)); no != NULL; no = getNext(no))
        {
            Aresta aresta = getInfo(no);
            char* idaux = getArestaVertDestino(aresta);
            double *dist = getValue(distancia, idaux);
            if(stringNaLista(restante, idaux))
            {
                if(dist == NULL)
                {
                    double *distTemp = malloc(sizeof(double));
                    *distTemp = getPeso(aresta) + *dAnt;
                    insertHTable(distancia, idaux, distTemp);
                    char* tempId = malloc(sizeof(char) * (strlen(ini) + 1));
                    strcpy(tempId, ini);
                    insertHTable(anterior, idaux, tempId);
                }
                else if(*dist > getPeso(aresta) + *dAnt)
                {
                    *dist = getPeso(aresta) + *dAnt;
                    free(getValue(anterior, idaux));
                    char* tempId = getValue(anterior, idaux);
                    strcpy(tempId, ini);
                    mudaValor(anterior, idaux, tempId);
                }
            }
        }

        if(strcmp(ini, fin) == 0)
        {
            *disTotal = *(double*)getValue(distancia, fin);
            break;
        }
        double menor;
        int flag = 1;
        char idAnt[100];
        strcpy(idAnt, ini);
        No no = getFirst(restante);

        while(no != NULL)
        {
            if(strcmp(getInfo(no), idAnt) == 0)
            {
                No visitado = no;
                no = getNext(no);
                removerNo(restante, visitado, NULL);
                continue;
            }
            double *valor = getValue(distancia, getInfo(no));
            if(valor != NULL && (flag || menor > *valor))
            {
                menor = *valor;
                ini = getInfo(no);
                flag = 0;
            }
            no = getNext(no);
        }

        if(flag)
        {
            *disTotal = 0;
            deleteHTable(distancia, 1);
            deleteHTable(anterior, 1);
            removeList(restante, NULL);
            printf("CAMINHO INEXISTENTE");
            return NULL;
        }
        
    }

    Lista path = create();

    while(fin != NULL)
    {
        char *pathAux = malloc(sizeof(char) * (strlen(fin) + 1));
        strcpy(pathAux, fin);
        insert(path, pathAux);
        fin = getValue(anterior, fin);
    }

    deleteHTable(distancia, 1);
    deleteHTable(anterior, 1);
    removeList(restante, NULL);

    return path;
    
    
}
