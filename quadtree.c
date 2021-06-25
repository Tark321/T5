#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"
#include "auxiliar.h"
#include "quadtree.h"

#define dx 250
#define dy 250

typedef struct no
{
    QtInfo info;
    struct no * NE;
    struct no * NW;
    struct no * SE;
    struct no * SW;
    struct no *parent;
    Ponto ponto;
}StructNode;

typedef struct qt
{
    StructNode *raiz; 
    char* (*fun)(QtInfo);   

}StructTree;


QuadTree criaQt(funcGetChave f)
{
    StructTree *tree = (StructTree*) malloc(sizeof(StructTree));
    tree->raiz = NULL;
    tree->fun = f;

    return tree;
}

char *getChaveQt(QuadTree qt, QtNo pNo)
{
    StructTree *tree = (StructTree*)qt;
    StructNode *no = (StructNode*) pNo;

    return tree->fun(getInfoQt(tree, no));
}

Ponto getPontoQt(QuadTree qt, QtNo pNo)
{
    StructNode *no = (StructNode*) pNo;
    qt = qt;

    return no->ponto;
}

void dentroRetanguloQt(QuadTree qt, StructNode* no, Lista lista, double x1, double y1, double x2, double y2, void* (*fun)(void*, void*))
{
    if(no == NULL)
    {
        return;
    }

    if(pontoInternoRet(getPontoX(no->ponto), getPontoY(no->ponto), x1, y1, x2 - x1, y2 - y1 ))
    {
        if(fun != NULL)
        {
            insert(lista, fun(qt, no));
        }
        else
        {
            insert(lista, no);
        }
    }

    dentroRetanguloQt(qt, no->NE, lista, x1, y1, x2, y2, fun);
    dentroRetanguloQt(qt, no->NW, lista, x1, y1, x2, y2, fun);
    dentroRetanguloQt(qt, no->SE, lista, x1, y1, x2, y2, fun);
    dentroRetanguloQt(qt, no->SW, lista, x1, y1, x2, y2, fun);
}

void dentroCirculoQt(QuadTree qt, StructNode* no, Lista lista, double x, double y, double r, void* (*fun)(void*, void*))
{

    if(no == NULL)
    {
        return;
    }
    
    if(pontoInternoCirc(getPontoX(no->ponto), getPontoY(no->ponto), x, y, r ))
    {
        if(fun != NULL)
        {
            insert(lista, fun(qt, no));
        }
        else
        {
            insert(lista, no);
        }
    }

    dentroCirculoQt(qt, no->NE, lista, x, y, r, fun);
    dentroCirculoQt(qt, no->NW, lista, x, y, r, fun);
    dentroCirculoQt(qt, no->SE, lista, x, y, r, fun);
    dentroCirculoQt(qt, no->SW, lista, x, y, r, fun);
}

Lista chavesDentroRetanguloQt(QuadTree qt, double x1, double y1, double x2, double y2)
{
    StructTree *tree = (StructTree*)qt;
    StructNode *no = tree->raiz;

    Lista lista = create();
    dentroRetanguloQt(qt, no, lista, x1, y1, x2, y2, (void*(*)(void*, void*))getChaveQt);

    return lista;
}

Lista chavesDentroCirculoQt(QuadTree qt, double x, double y, double r)
{
    StructTree *tree = (StructTree*)qt;
    StructNode *no = tree->raiz;

    Lista lista = create();
    dentroCirculoQt(qt, no, lista, x, y, r, (void*(*)(void*, void*))getChaveQt);

    return lista;
}

Lista pontosDentroRetanguloQt(QuadTree qt,double x1, double y1,double x2, double y2)
{
    StructTree *tree = (StructTree*)qt;
    StructNode *no = tree->raiz;

    Lista lista = create();
    dentroRetanguloQt(qt, no, lista, x1, y1, x2, y2, getPontoQt);

    return lista;
}

Lista pontosDentroCirculoQt(QuadTree qt,double x, double y, double r)
{
    StructTree *tree = (StructTree*)qt;
    StructNode *no = tree->raiz;

    Lista lista = create();
    dentroCirculoQt(qt, no, lista, x, y, r, getPontoQt);

    return lista;
}

Lista nosDentroRetanguloQt(QuadTree qt,double x1, double y1,double x2, double y2)
{
    StructTree *tree = (StructTree*)qt;
    StructNode *no = tree->raiz;

    Lista lista = create();
    dentroRetanguloQt(qt, no, lista, x1, y1, x2, y2, NULL);

    return lista;
}

Lista nosDentroCirculoQt(QuadTree qt,double x, double y, double r)
{
    StructTree *tree = (StructTree*)qt;
    StructNode *no = tree->raiz;

    Lista lista = create();
    dentroCirculoQt(qt, no, lista, x, y, r, NULL);

    return lista;
}

void percorreProfundidade(QuadTree qt, StructNode *no, funcVisita f, ExtraInfo ei)
{
    if(no == NULL)
    {
        return;
    }

    f(getInfoQt(qt, no), ei);

    percorreProfundidade(qt, no->NE, f, ei);
    percorreProfundidade(qt, no->NW, f, ei);
    percorreProfundidade(qt, no->SE, f, ei);
    percorreProfundidade(qt, no->SW, f, ei);
}

void percorreProfundidadeQt(QuadTree qt, funcVisita f,ExtraInfo ei)
{
    StructTree *tree = (StructTree*)qt;
    StructNode *no = tree->raiz;

    percorreProfundidade(qt, no, f, ei);
}

void percorreLarguraQt(QuadTree qt,funcVisita f, ExtraInfo ei)
{
    StructTree *tree = (StructTree*)qt;
    StructNode *aux;

    if(tree->raiz == NULL)
    {
        return;
    }

    Fila fila = criaFila();
    insereFila(fila, tree->raiz);

    do{
        aux = retiraFila(fila);

            if(aux->NE != NULL)
            {
                insereFila(fila, aux->NE);
            }
            if(aux->NW != NULL)
            {
                insereFila(fila, aux->NW);
            }
            if(aux->SE != NULL)
            {
                insereFila(fila, aux->SE);
            }
            if(aux->SW != NULL)
            {
                insereFila(fila, aux->SW);
            }
        f(getInfoQt(tree, aux), ei);
    }while(!filaIsEmpty(fila));

    removeFila(fila);

}

void insere(StructTree* qt, StructNode* no)
{
    StructNode *aux = qt->raiz;
    Ponto auxP;
    Ponto p;
    no->NE = NULL;
    no->NW = NULL;
    no->SE = NULL;
    no->SW = NULL;
    no->parent = NULL;

    if(aux == NULL)
    {
        qt->raiz = no;
        return;
    }
    
    while(no->parent == NULL)
    {
        auxP = aux->ponto;
        p = no->ponto;
            if(getPontoX(p) >= getPontoX(auxP))
            {
                if(getPontoY(p) >= getPontoY(auxP))
                {
                    if(aux->NE == NULL)
                    {
                        aux->NE = no;
                        no->parent = aux;              
                    }
                    else
                    {
                        aux = aux->NE;
                    }  
                }
                else
                {
                    if(aux->SE == NULL)
                    {
                        aux->SE = no;
                        no->parent = aux;
                    }
                    else
                    {
                        aux = aux->SE;
                    }
                    
                }      
            }
            else
            {
                if(getPontoY(p) >= getPontoY(auxP))
                {
                    if(aux->NW == NULL)
                    {
                        aux->NW = no;
                        no->parent = aux;
                    }
                    else
                    {
                        aux = aux->NW;
                    }
                    
                }
                else
                {
                    if(no->SW == NULL)
                    {
                        aux->SW = no;
                        no->parent = aux;
                    }
                    else
                    {
                        aux = aux->SW;
                    }
                }     
            }
    }

}

QtNo insereQt(QuadTree qt, Ponto p, QtInfo pInfo)
{     
    if(p == NULL)
    {
        return NULL;
    }

    StructNode *no = (StructNode*) malloc(sizeof(StructNode));
    StructTree *tree = (StructTree*) qt;
    no->ponto = p;
    no->info = pInfo;
    insere(tree, no);
    return no;
    
}

QtInfo removeNoQt(QuadTree qt,QtNo pNo)
{
    StructTree *tree = (StructTree*)qt;
    StructNode *no = (StructNode*) pNo;
    StructNode *aux;
    QtInfo info;
    Fila fila = criaFila();

    if(no->parent == NULL)
    {
       for(int i=0; i < 4; i++)
       {
            if(no->NE != NULL)
            {
                insereFila(fila, no->NE);
            }
            if(no->NW != NULL)
            {
                insereFila(fila, no->NW);
            }
            if(no->SE != NULL)
            {
                insereFila(fila, no->SE);
            }
            if(no->SW != NULL)
            {
                insereFila(fila, no->SW);
            }
       }

        tree->raiz = NULL;        
    }
    else
    {
        for(int i=0; i < 4; i++)
        {
            if(no->NE != NULL)
            {
                if(no->parent->NE != NULL)
                {
                    insereFila(fila, no->NE);
                }
                else
                {
                    no->parent->NE = no->NE;
                    no->NE->parent = no->parent;
                }      
            }
            if(no->NW != NULL)
            {
                if(no->parent->NW != NULL)
                {
                    insereFila(fila, no->NW);
                }
                else
                {
                    no->parent->NW = no->NW;
                    no->NW->parent = no->parent;
                }      
            } 
            if(no->SE!= NULL)
            {
                if(no->parent->SE != NULL)
                {
                    insereFila(fila, no->SE);
                }
                else
                {
                    no->parent->SE = no->SE;
                    no->SE->parent = no->parent;
                }      
            } 
            if(no->SW != NULL)
            {
                if( no->parent->SW != NULL)
                {
                    insereFila(fila, no->SW);
                }
                else
                {
                     no->parent->SW = no->SW;
                     no->SW->parent = no->parent;
                }      
            } 
        }

        for(int i = 0; i < 4; i++)
        {
            if(no->parent->NE == no)
            {
                no->parent->NE = NULL;
                break;
            }
            if(no->parent->NW == no)
            {
                no->parent->NW = NULL;
                break;
            }
            if(no->parent->SE == no)
            {
                no->parent->SE = NULL;
                break;
            }
            if(no->parent->SW == no)
            {
                no->parent->SW = NULL;
                break;
            }
        }
    }

    while(!filaIsEmpty(fila))
    {
        aux = retiraFila(fila);
        if(aux->NE != NULL)
        {
            insereFila(fila, aux->NE);
        }
        if(aux->NW != NULL)
        {
            insereFila(fila, aux->NW);
        }
        if(aux->SE != NULL)
        {
            insereFila(fila, aux->SE);
        }
        if(aux->SW != NULL)
        {
            insereFila(fila, aux->SW);
        }

        if(aux != NULL)
        {
            insere(tree, aux);
        }
        else 
        {
            break;
        }
    }

    info = getInfoQt(tree, no);
    free(fila);
    free(no);

    return info;

}

QtNo getNoQt(QuadTree qt, double x, double y)
{
    StructTree *tree = (StructTree*)qt;
    StructNode *aux = tree->raiz;
    Ponto ponto;

    while(aux != NULL)
    {
        ponto = aux->ponto;

        if(x == getPontoX(ponto) && getPontoY(ponto))
        {
            return aux;
        }
        if(x > getPontoX(ponto))
        {
            if(y > getPontoY(ponto))
            {
                aux = aux->NE;
            }
            else
            {
                aux = aux->SE;
            }
        }
        else
        {
            if(y > getPontoY(ponto))
            {
                aux = aux->NW;
            }
            else
            {
                aux = aux->SW;
            }   
        }  
    }

     return NULL; 
}

QtInfo getInfoQt(QuadTree qt, QtNo pNo)
{
    StructNode *no = (StructNode*)pNo;
    qt = qt;

    return no->info;
}

void desalocaNo(StructNode *no)
{
    if(no == NULL)
    {
        return;
    }

    desalocaNo(no->NE);
    desalocaNo(no->NW);
    desalocaNo(no->SE);
    desalocaNo(no->SW);

    if(no->ponto != no->info)
    {
      free(no->ponto);
    }

  free(no->info);
  free(no);
}

void desalocaQt(QuadTree qt)
{
    StructTree* tree = (StructTree*)qt;
    desalocaNo(tree->raiz);
    free(qt);
}

QtNo getNoById(QuadTree qt, char chave[])
{
    StructTree* tree = (StructTree*) qt;

    if(tree->raiz == NULL)
    {
        return NULL;
    }

    return getNoIdQt(qt, tree->raiz, chave);
}

QtNo getNoIdQt(QuadTree qt, QtNo no, char chave[])
{
    StructNode* node = (StructNode*) no;
    StructTree* tree = (StructTree*) qt;

    if(strcmp(tree->fun(getInfoQt(qt, node)), chave) == 0)
    {
        return node;
    }

    QtNo aux;

    if(node->NE != NULL)
    {
        aux = getNoIdQt(qt,node->NE,chave);

            if(aux != NULL)
            {
                return aux;
            }
    }
     if(node->NW!= NULL)
    {
        aux = getNoIdQt(qt,node->NW,chave);

            if(aux != NULL)
            {
                return aux;
            }
    }
     if(node->SE != NULL)
    {
        aux = getNoIdQt(qt,node->SE,chave);

            if(aux != NULL)
            {
                return aux;
            }
    }
    if(node->SW != NULL)
    {
        aux = getNoIdQt(qt,node->SW,chave);

            if(aux != NULL)
            {
                return aux;
            }
    }
    
    return NULL;
}

QtInfo getInfoById(QuadTree qt, QtNo no, char* chave)
{
    StructNode* node = (StructNode*) no;
    StructTree* quadtree = (StructTree*) qt;

    if(strcmp(quadtree->fun(getInfoQt(qt, node)), chave) == 0)
    {
        return getInfoQt(qt, node);
    }
    QtInfo aux;

    if(node->NE != NULL)
    {
        aux = getInfoById(qt,node->NE,chave);

            if(aux != NULL)
            {
                return aux;
            }
    }
     if(node->NW != NULL)
    {
        aux = getInfoById(qt,node->NW,chave);

            if(aux != NULL)
            {
                return aux;
            }
    }
     if(node->SE != NULL)
    {
        aux = getInfoById(qt,node->SE,chave);

            if(aux != NULL)
            {
                return aux;
            }
    }
     if(node->SW != NULL)
    {
        aux = getInfoById(qt,node->SW,chave);

            if(aux != NULL)
            {
                return aux;
            }
    }
    
    return NULL;
}

QtInfo getInfoByIdQt(QuadTree qt, char* chave)
{
    StructTree* tree = (StructTree*) qt;
    if(tree->raiz == NULL || chave == NULL ||  qt == NULL)
    {
        printf("\nInfo nao pode ser encontrada\n");
        return NULL;
    }

    return getInfoById(qt, tree->raiz, chave);
}

void printNosQt(StructTree* qt, StructNode* no, FILE* svg, double* x, double y, Lista ant)
{
    // if( no == NULL)
    // {
    //     printf("NO NAO PODE SER DESENHADO\n");
    //     return;
    // }
    if(no != NULL)
    {

        Lista atual = create();
    
        printNosQt(qt, no->NE, svg, x, y + dy, atual);
        printNosQt(qt, no->NW, svg, x, y + dy, atual);

        double aux = *x;

        if(ant != NULL)
        {
            insert(ant, criaPonto(aux, y - 10));
            fprintf(svg, "<rect x=\"%lf\" y=\"%lf\" width=\"240\" height=\"14\" fill=\"none\" stroke=\"blue\" />\n", aux, y - 10);
            fprintf(svg, "\t<text x=\"%lf\" y=\"%lf\">%s: %lf, %lf</text>\n", aux, y, qt->fun(getInfoQt(qt, no)), getPontoX(no->ponto), getPontoY(no->ponto));
        }
        else
        {
            fprintf(svg, "<rect x=\"%lf\" y=\"%lf\" width=\"240\" height=\"14\" fill=\"none\" stroke=\"red\" />\n", aux, y - 10);
            fprintf(svg, "\t<text x=\"%lf\" y=\"%lf\">%s: %lf, %lf</text>\n", aux, y, qt->fun(getInfoQt(qt, no)), getPontoX(no->ponto), getPontoY(no->ponto));
            fprintf(svg, "\t<cricle cx=\"%lf\" cy=\"%lf\" \"5\" fill=\"tomato\" stroke=\"tomato\"/>\n", aux, y - 10);
        }

        printNosQt(qt, no->NE, svg, x, y + dy, atual);
        printNosQt(qt, no->NW, svg, x, y + dy, atual);
        printNosQt(qt, no->SE, svg, x, y + dy, atual);
        printNosQt(qt, no->SW, svg, x, y + dy, atual);

        for(No no = getFirst(atual); no != NULL; no = getNext(no))
        {
            fprintf(svg, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke: blue; stroke-width: 1\" />\n", aux, y + 2, getPontoX(getInfo(no)), getPontoY(getInfo(no)));
        }

        removeList(atual, free);
    }
}

void desenharQt(QuadTree qt, FILE* svg)
{
    StructTree* tree = (StructTree*) qt;
    double *x = (double*) malloc(sizeof(double));
    *x = 0;
    printNosQt(tree, tree->raiz, svg, x, dy, NULL);
    free(x);
}