#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"svg.h"

void iniciaSvg(FILE* arqSvg)
{
    char* sombra[6] = {"#FFF00", "#FF9955", "#FF0000", "#FF00CC","#6600FF", "#A02C5A"};

    fprintf(arqSvg, "<svg version=\"1.1\" baseProfile=\"full\" width=\"10000\" height=\"10000\" xmlns=\"http://www.w3.org/2000/svg\">\n\t<defs>\n");


    for(int i = 0; i < 6; i++)
    {
        fprintf(arqSvg, "\t\t<filter id=\"shadow%d\">\n\t\t\t<feDropShadow dx=\"2\" dy=\"2\" stdDeviation=\"0.2\" flood-color=\"%s\"/>\n\t\t</filter>\n", i, sombra[i]);
    }
    fprintf(arqSvg, "\t</defs>\n");
    
}

void desenhaCirculo(Circulo circulo, FILE* arqSvg)
{
    fprintf(arqSvg, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" opacity=\"%lf\"/>\n ", getCirculoX(circulo), getCirculoY(circulo), 
    getCirculoR(circulo), getCirculoCorb(circulo), getCirculoCorp(circulo), getCirculoOp(circulo));
}

void desenhaRetangulo(Retangulo retangulo, FILE* arqSvg)
{
    fprintf(arqSvg, "\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"%s\" stroke=\"%s\" stroke-width =\"1\"/>\n",
    getRetanguloX(retangulo), getRetanguloY(retangulo), getRetanguloW(retangulo), getRetanguloH(retangulo),
    getRetanguloCorp(retangulo), getRetanguloCorb(retangulo));
}

void desenhaRetanguloTracejado(Retangulo retangulo, FILE* arqSvg)
{    
    fprintf(arqSvg, "\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"none\" stroke=\"%s\" stroke-width =\"1\" stroke-dasharray=\"1\" />\n",
    getRetanguloX(retangulo), getRetanguloY(retangulo), getRetanguloW(retangulo), getRetanguloH(retangulo), getRetanguloCorb(retangulo));
}

void desenhaRetanguloArredondado(Retangulo retangulo, FILE* arqSvg)
{
    fprintf(arqSvg, "\n<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"beige\" stroke=\"olive\"  stroke-width=\"%s\" rx=\"20\"/>\n",
    getRetanguloX(retangulo), getRetanguloY(retangulo), getRetanguloW(retangulo), getRetanguloH(retangulo), getRetanguloSw(retangulo));
}

void escreveTexto(Texto texto, FILE* arqSvg)
{
    fprintf(arqSvg,"\t<text x=\"%lf\" y=\"%lf\" stroke=\"%s\" stroke-width=\"0.3\" fill=\"%s\">%s</text>\n",
    getTextoX(texto), getTextoY(texto), getTextoCorb(texto), getTextoCorp(texto), getTextoTxto(texto));
}

void escreveTextoNumerico(TextoNumerico textoNum, FILE* arqSvg)
{
    fprintf(arqSvg,"\t<text x=\"%lf\" y=\"%lf\" stroke=\"%s\" stroke-width=\"0.3\" fill=\"%s\">%lf</text>\n", 
    getTextoNumericoX(textoNum), getTextoNumericoY(textoNum), getTextoNumericoCorb(textoNum),
    getTextoNumericoCorp(textoNum), getTextoNumericoTexto(textoNum));
}

void desenhaQuadra(Quadra quadra, FILE* arqSvg)
{
    int aux;
    double d = getQuadraDensidade(quadra);
    

    if(d <= 500)
    {
        aux = 0;
    }
    else if(d <= 1500)
    {
        aux = 1;
    }
    else if(d <= 3000)
    {
        aux = 2;
    }
    else if(d <= 4500)
    {
        aux = 3;
    }
    else if(d <= 6000)
    {
        aux = 4;
    }
    else
    {
        aux = 5;
    }
    fprintf(arqSvg,"\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"%s\" stroke=\"%s\" stroke-width=\"%s\" filter=\"url(#shadow%d)\"/>\n",
    getQuadraX(quadra), getQuadraY(quadra), getQuadraW(quadra), getQuadraH(quadra), 
    getQuadraCfill(quadra), getQuadraCstrk(quadra), getQuadraSw(quadra), aux);

    if(getQuadraY(quadra) != 0 && getQuadraX(quadra) != 0)
    {
        fprintf(arqSvg, "\t<text x=\"%lf\" y=\"%lf\" fill=\"black\">%s</text>\n", 
        getQuadraX(quadra)+getQuadraW(quadra)/4, getQuadraY(quadra)+getQuadraH(quadra)/2, getQuadraCep(quadra));
    }

}

void desenhaHidrante(Hidrante hidrante, FILE* arqSvg)
{
    double raio = 1;

    fprintf(arqSvg, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" stroke-width=\"%s\" fill=\"%s\"/>\n ", 
    getHidranteX(hidrante), getHidranteY(hidrante), raio, getHidranteCstrk(hidrante), getHidranteSw(hidrante), getHidranteCfill(hidrante));
}

void desenhaSemaforo(Semaforo semaforo, FILE* arqSvg)
{
    double raio = 1;

    fprintf(arqSvg, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" stroke-width=\"%s\" fill=\"%s\"/>\n ", 
    getSemaforoX(semaforo), getSemaforoY(semaforo), raio, getSemaforoCstrk(semaforo), getSemaforoSw(semaforo), getSemaforoCfill(semaforo));
}

void desenhaRadioBase(Radiobase radiobase, FILE* arqSvg)
{
    double raio = 1;
    double x = getRadiobaseX(radiobase);
    double y = getRadiobaseY(radiobase);
    getRadiobaseX(radiobase);

    fprintf(arqSvg, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" stroke-width=\"%s\" fill=\"%s\"/>\n ", x, y, raio, getRadiobaseCstrk(radiobase), getRadiobaseSw(radiobase), getRadiobaseCfill(radiobase));
}

void desenhaPosto(Posto posto, FILE* arqSvg)
{
    fprintf(arqSvg, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%d\" stroke=\"%s\" fill=\"%s\"/>\n ", 
    getPontoX(posto), getPontoY(posto), 5, "green", "blue");
}

void desenhaLinha(Linha linha, FILE* arqSvg)
{
    fprintf(arqSvg, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\"/>\n", 
    getLinhaX1(linha), getLinhaY1(linha), getLinhaX2(linha), getLinhaY2(linha), getLinhaCor(linha));

}

void desenhaLinhaTracejada(Linha linha, FILE* arqSvg)
{
    fprintf(arqSvg, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"black\" stroke-width=\"2\" stroke-dasharray=\"5\" />\n ", 
    getLinhaX1(linha),getLinhaY1(linha), getLinhaX2(linha), getLinhaY2(linha));
}

void desenhaCirculoTransparente(Circulo circulo, FILE* arqSvg)
{
    fprintf(arqSvg, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" opacity=\"0.5\"/>\n ", 
    getCirculoX(circulo),getCirculoY(circulo), getCirculoR(circulo), getCirculoCorb(circulo), getCirculoCorp(circulo));
}

void finalizaSvg(FILE* arqSvg)
{
    fprintf(arqSvg, "</svg>");
}

void desenhaGeoSvg(FILE* arqSvg, QuadTree treeObjeto[], Lista l)
{
    No no;

    void (*desenhar[8])(void*, FILE*) = {desenhaCirculo, desenhaRetangulo, escreveTexto, desenhaQuadra, desenhaHidrante, desenhaSemaforo, desenhaRadioBase, desenhaPosto};

    for(int i = 0; i < 8; i++)
    {
        percorreLarguraQt(treeObjeto[i],(void(*)(void*, void*))desenhar[i], arqSvg);
    }

    if(l != NULL)
    {
        for(no = getFirst(l); no != NULL; no = getNext(no))
        {
            fprintf(arqSvg,"\t<use xlink:href=\"#%d\"/>", *(int*)getInfo(no));
        }
    }
}

void gerarSvgQry(QuadTree treeObjeto[], FILE *saidaSvg, Lista listasQry[])
{
    desenhaGeoSvg(saidaSvg, treeObjeto, NULL);

    int i=0;

    if(i==0)
    {
        No node;
        for(node = getFirst(listasQry[i]); node != NULL; node = getNext(node))
        {
            Info textNum = getInfo(node);
            if(textNum != NULL)
            {
                escreveTextoNumerico(textNum, saidaSvg);
            }
        } 
        i++;
    }
    if(i==1)
    {
        No node;
        for(node = getFirst(listasQry[i]); node != NULL; node = getNext(node))
        {
            Info r = getInfo(node);
            if( r != NULL)
            {
                desenhaRetangulo(r, saidaSvg);  
            }         
        } 
        i++;
    }
    if(i==2)
    {
        No node;
        for(node = getFirst(listasQry[i]); node != NULL; node = getNext(node))
        {
            Info lin = getInfo(node);
            if(lin != NULL)
            {
                desenhaLinha(lin, saidaSvg);
            }
        } 
        i++;
    }
    if(i==3)
    {
        No node;
        for(node = getFirst(listasQry[i]); node != NULL; node = getNext(node))
        {
            Info c = getInfo(node);
            if(c != NULL)
            {
                desenhaCirculo(c, saidaSvg);
            }
        } 
        i++;
    }
    if(i==4)
    {
        No node;
        for(node = getFirst(listasQry[i]); node != NULL; node = getNext(node))
        {
            Info t = getInfo(node);
            if( t != NULL)
            {
                escreveTexto(t, saidaSvg);
            }
        } 
        i++;
    }
    if(i==5)
    {
        No node;
        for(node = getFirst(listasQry[i]); node != NULL; node = getNext(node))
        {
            Info r = getInfo(node);
            if(r != NULL)
            {
                desenhaRetanguloTracejado(r, saidaSvg);
            }
        } 
        i++;
    }
    if(i==6)
    {
        No node;
        for(node = getFirst(listasQry[i]); node != NULL; node = getNext(node))
        {
            Info r = getInfo(node);
            if(r != NULL)
            {
                desenhaRetanguloArredondado(r, saidaSvg);
            }
        } 
        i++;
    }
    if(i==7)
    {
        No node;
        for(node = getFirst(listasQry[i]); node != NULL; node = getNext(node))
        {
            Info lin = getInfo(node);
            if( lin != NULL)
            {
                desenhaLinhaTracejada(lin, saidaSvg);
            }
        } 
        i++;
    }
    if(i==8)
    {

        No node;
        for(node = getFirst(listasQry[i]); node != NULL; node = getNext(node))
        {
            Info c = getInfo(node);
            if(c != NULL)
            {
                desenhaCirculoTransparente(c, saidaSvg);
            }
        }
    }
}