#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "qry5.h"


void mm(HashTable hash[], char cpf[], char r[], Lista listaQry[], Ponto registradores[], FILE* saida)
{
    int indice = getIndice(r);
    Address a = getValue(hash[3], cpf);

    if(a == NULL)
    {
        printf("MORADOR INVALIDO");
        fprintf(saida, "\nCPF INVALIDO\n");
        return;
    }

    Ponto pa = getAddressPonto(a);
    setPontoX(registradores[indice], getPontoX(pa));
    setPontoY(registradores[indice], getPontoY(pa));

    Linha linha = criaLinha(getPontoX(pa), getPontoY(pa), getPontoX(pa), 0, "black");
    insert(listaQry[2], linha);

    Texto texto = criaTexto("0", getPontoX(pa), 0, "white", "black", r);
    insert(listaQry[4], texto);
}

void e(FILE* saida, HashTable hash[], Lista listaQry[], char r[], char cep[], Ponto registradores[], char face[], double num)
{
    int indice = getIndice(r);
    Quadra q = getValue(hash[0], cep);

    if(q == NULL)
    {
        printf("QUADRA INVALIDA");
        fprintf(saida, "\nCEP INVALIDO\n");
        return;
    }


    Ponto pq = getQuadraPonto(q);
    double x = getPontoX(pq);
    double y = getPontoY(pq);
    double w = getQuadraW(q);
    double h = getQuadraH(q);

    if(strcmp(face, "N") == 0)
    {
        x = x + num;
        y = y + h;
    }
    else if(strcmp(face, "S") == 0)
    {
        x = x + num;
    }
    else if(strcmp(face, "L") == 0)
    {
        y = y + num;
    }
    else if(strcmp(face, "O") == 0)
    {
        x = x + w;
        y = y + num;
    }

    setPontoX(registradores[indice], x);
    setPontoY(registradores[indice], y);

    Linha linha = criaLinha( x, y, x, 0, "black");
    insert(listaQry[2], linha);

    
}

void gg(FILE* saida, Ponto registradores[], QuadTree treeObjeto[], Lista listaQry[], char r[], char id[])
{
    int achou = 0;
    int indice = getIndice(r);
    double x;
    double y;
    Info info;
    switch(id[0])
    {
        case 'h':
            info = getInfoByIdQt(treeObjeto[4], id);
            x = getHidranteX(info);
            y = getHidranteY(info);
            fprintf(saida, "HIDRANTE\n");
            achou = 1;
            break;

        case 's':
            info = getInfoByIdQt(treeObjeto[5], id);
            x = getSemaforoX(info);
            y = getSemaforoY(info);
            fprintf(saida, "SEMAFARO\n");
            achou = 1;
            break;

        case 'r':
            info = getInfoByIdQt(treeObjeto[6], id);
            x = getRadiobaseX(info);
            y = getRadiobaseY(info);
            fprintf(saida, "RADIO BASE\n");
            achou = 1;
            break;
    }

   if(achou != 1)
    {
        fprintf(saida, "\nOBJETO NAO ENCONTRADO\n");
        return;
    }
    else
    {
        setPontoX(registradores[indice], x);
        setPontoY(registradores[indice], y);

        Linha linha = criaLinha(x, y, x, 0, "black");
        insert(listaQry[2], linha);

        Texto texto = criaTexto("0", x, 0, "white", "black", r);
        insert(listaQry[4], texto);
    }
}

void xy(Ponto registradores[], Lista listaQry[], char r[], double x, double y)
{
    int indice = getIndice(r);

    setPontoX(registradores[indice], x);
    setPontoY(registradores[indice], y);

    Linha linha = criaLinha(x, y, x, 0, "black");
    insert(listaQry[2], linha);

    Texto texto = criaTexto("0", x, 0, "white", "black", r);
    insert(listaQry[4], texto);
}

void cvv(Grafo grafo, char nomeSvg[], char sfx[], Lista listaQry[])
{
    Grafo via = criaGrafoNDirecionado(grafo);
    Grafo ciclo = prim(via);

    if(ciclo == NULL)
    {
        exit(1);
    }

    char* arqsvg = malloc(sizeof(char*) * (strlen(nomeSvg) + strlen(sfx) + 6));
    sprintf(arqsvg, "%s-%s.svg", nomeSvg, sfx);
    FILE* svg = fopen(arqsvg, "w");
    iniciaSvg(svg);
    desenhaGrafo(grafo, listaQry);
    desenhaGrafo(ciclo, listaQry);
    finalizaSvg(svg);

    fclose(svg);
    free(arqsvg);

}

// void p(Grafo grafo, Ponto registradores[], char sfx[], char cmc[], char cmr[], FILE* saida, char nomeSvg[], char r1[], char r2[])
// {
//     int indice1 = getIndice(r1);
//     int indice2 = getIndice(r2);

//     Vertice vi = getGrafoVertice(getInfo(getFirst(grafo)));
//     Vertice vf = getGrafoVertice(getInfo(getFirst(grafo)));

//     char idi[100];
//     char idf[100];
//     strcpy(idi, getVerticeId(vi));
//     strcpy(idf, getVerticeId(vf));

//     Ponto inicial = registradores[indice1];
//     Ponto final = registradores[indice2];

//     double xi = getPontoX(inicial);
//     double yi = getPontoY(inicial);
//     double xf = getPontoX(final);
//     double yf = getPontoY(final);

//     double mc;
//     double mr;

//     double menor1 = distancia(xi, yi, getPontoX(getVerticePonto(vi)), getPontoY(getVerticePonto(vi)));
//     double menor2 = distancia(xf, yf, getPontoX(getVerticePonto(vf)), getPontoY(getVerticePonto(vf)));

//     for(No node = getNext(getFirst(grafo)); node != NULL; node = getNext(node))
//     {
//         ListAdjc l = getInfo(node);

//         if(menor1 > distancia(getPontoX(getGrafoVertice(getInfo(node))), getPontoY(getGrafoVertice(getInfo(node))), xi, yi))
//         {
//             strcpy(idi, getVerticeId(getGrafoVertice(getInfo(node))));
//             menor1 = distancia(getPontoX(getGrafoVertice(getInfo(node))), getPontoY(getGrafoVertice(getInfo(node))), xi, yi);
//         }
//         if(menor2 > distancia(getPontoX(getGrafoVertice(getInfo(node))), getPontoY(getGrafoVertice(getInfo(node))),xf, yf))
//         {
//             strcpy(idf, getVerticeId(getGrafoVertice(getInfo(node))));
//             menor2 = distancia(getPontoX(getGrafoVertice(getInfo(node))), getPontoY(getGrafoVertice(getInfo(node))),xf, yf);
//         }
//     }

//     Lista mcPath = dijkstra(grafo, idi, idf, &mc, getArestaCmp);
//     Lista mrPath = dijkstra(grafo, idi, idf, &mr, getArestaTempo);

//     if(strcmp(sfx, "-") != 0)
//     {
        
//     }
// }