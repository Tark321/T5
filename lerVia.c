#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lerVia.h"


void lerVia(char arqVia[], Grafo grafo[])
{
    char comando[2];
    char i[100];
    char j[100];
    char id[100];
    char ldir[100];
    char lesq[100];
    char nome[150];
    double x;
    double y;
    double vm;
    double cmp;
    
    FILE *viaArq = fopen(arqVia, "r");

    if(viaArq == NULL)
    {
        printf("\nERRO\nArquivo .via nao pode ser aberto\n");
        exit(1);
    }


    while(!feof(viaArq))
    {
        fscanf(viaArq, "%s", comando);

        if(strcmp(comando, "v") == 0)
        {
            fscanf(viaArq, "%s %lf %lf", id, &x, &y);
            Vertice vertice = criaVertice(id, x, y);
            insereVertice(grafo, vertice);
        }
        if(strcmp(comando, "e") == 0)
        {
            fscanf(viaArq, "%s %s %s %s %lf %lf %s", i, j, ldir, lesq, &cmp, &vm, nome);
            Aresta aresta = criaAresta(cmp, vm, nome, ldir, lesq, j);
            insereAresta(grafo, aresta, i);
        }
    }

    removeVerticesIsolados(grafo);
    fclose(viaArq);
}