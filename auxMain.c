#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "lerGeo.h"
#include "lista.h"
#include "lerPm.h"
#include "lerEc.h"
#include "lerVia.h"
#include "lerQry.h"
#include "quadtree.h"
#include "hashTable.h"

char *concatenacao(char dir_entrada[])
{	
	char* arqGeoConcatenado = NULL;
    char* aux = strrchr(dir_entrada,'/');
    if(aux == NULL)
	{
		arqGeoConcatenado=strtok(dir_entrada,".");
        return(arqGeoConcatenado);
    }
	arqGeoConcatenado=strtok(&aux[1],".");
	return(arqGeoConcatenado);

}


void auxMain(char arq_geoNome[], char dir_saida[], char dir_entrada[], char arq_consulta[], char arq_pmNome[],
char arq_ecNome[], char arq_viaNome[])
{
    
    char *arqEc = NULL;
    char *arqPm = NULL;
    char *saida = NULL;
    char *arqVia = NULL;
    char *arqGeo = NULL;
    char *arqQry = NULL;
    char *nomeGeo = NULL;
    char *nomeQry = NULL;
    char *saidaQry = NULL;   
    char *nomeSvgGeo = NULL;
    
    QuadTree treeObjeto[12];

    char* (*getId[12])(void*) = {getCirculoI, getRetanguloI, getTextoI, getQuadraCep, getHidranteId, getSemaforoId,
    getRadiobaseId, NULL, NULL, getComercioCnpj, getAddressCpf, getCasosCEP};

    for(int i = 0; i < 12; i++)
    {
        treeObjeto[i] = criaQt(getId[i]);
    }

    Lista listaObjeto[15];

    for(int i = 0; i < 15; i++)
    {
        listaObjeto[i] = create();
    }

    Lista listasQry[11];

    for (int i = 0; i < 11; i++)
    {
        listasQry[i] = create();
    }

    HashTable listaHash[4];

    for(int i = 0; i < 4; i++)
    {
        listaHash[i] = createTable(1200);
    }

    Grafo grafo = criaGrafo();


    if(arq_geoNome == NULL || dir_saida == NULL)
    {
        printf("\nERRO\nArgumento essencial nao inserido\n");
        exit(1);
    }
    else if (dir_entrada != NULL) 
    {
        if(dir_entrada[strlen(dir_entrada) - 1] != '/')
        {
            arqGeo = (char *)malloc((strlen(arq_geoNome)+strlen(dir_entrada)+2)*sizeof(char));
    	    sprintf(arqGeo,"%s/%s",dir_entrada,arq_geoNome);

            if(arq_pmNome != NULL)
            {
                arqPm = (char *)malloc((strlen(arq_pmNome)+strlen(dir_entrada)+2)*sizeof(char));
    	        sprintf(arqPm,"%s/%s",dir_entrada,arq_pmNome);
            }
            if(arq_ecNome != NULL)
            {
                arqEc = (char *)malloc((strlen(arq_ecNome)+strlen(dir_entrada)+2)*sizeof(char));
    	        sprintf(arqEc,"%s/%s",dir_entrada,arq_ecNome);
            }
            if(arq_viaNome != NULL)
            {
                arqVia = (char *)malloc((strlen(arq_viaNome)+strlen(dir_entrada)+2)*sizeof(char));
                sprintf(arqVia,"%s/%s",dir_entrada,arq_viaNome);
            }
            
        }
		else
        {
            arqGeo = (char *)malloc((strlen(arq_geoNome)+strlen(dir_entrada)+1)*sizeof(char));
    	    sprintf(arqGeo,"%s%s",dir_entrada,arq_geoNome);

            if(arq_pmNome != NULL)
            {
                arqPm = (char *)malloc((strlen(arq_pmNome)+strlen(dir_entrada)+1)*sizeof(char));
    	        sprintf(arqPm,"%s%s",dir_entrada,arq_pmNome);
            }

            if(arq_ecNome != NULL)
            {
                arqEc = (char *)malloc((strlen(arq_ecNome)+strlen(dir_entrada)+1)*sizeof(char));
    	        sprintf(arqEc,"%s%s",dir_entrada,arq_ecNome);
            }
            if(arq_viaNome != NULL)
            {
                arqVia = (char *)malloc((strlen(arq_viaNome)+strlen(dir_entrada)+1)*sizeof(char));
                sprintf(arqVia,"%s%s",dir_entrada,arq_viaNome);
            }
        }
        if(arq_consulta!= NULL)
        {
            arqQry = (char *)malloc((strlen(arq_consulta)+strlen(dir_entrada)+2)*sizeof(char));
            sprintf(arqQry,"%s/%s",dir_entrada,arq_consulta);
        }
	} 
    else 
    {
		arqGeo = (char *)malloc((strlen(arqGeo)+1)*sizeof(char));
    	strcpy(arqGeo, arq_geoNome);

        if(arq_pmNome != NULL)
        {
            arqPm = (char *)malloc((strlen(arqPm)+1)*sizeof(char));
    	    strcpy(arqPm, arq_pmNome);
        }

        if(arq_ecNome != NULL)
        {
            arqEc = (char *)malloc((strlen(arqEc)+1)*sizeof(char));
    	    strcpy(arqEc, arq_ecNome);
        }
        if(arq_viaNome != NULL)
        {
            arqVia = (char *)malloc((strlen(arq_viaNome)+1)*sizeof(char));
            strcpy(arqVia, arq_viaNome);
        }

        if(arq_consulta != NULL)
        {
            arqQry = (char *)malloc((strlen(arq_consulta)+1)*sizeof(char));
            strcpy(arqQry, arq_consulta);
        }
	}

    nomeGeo = concatenacao(arq_geoNome);

    if (dir_saida[strlen(dir_saida) - 1] == '/')
    {
        saida = (char*)malloc((strlen(nomeGeo) + strlen(dir_saida) + 1)*sizeof(char));
        sprintf(saida,"%s%s",dir_saida,nomeGeo);
    }
    else
    {
        saida = (char*)malloc((strlen(nomeGeo) + strlen(dir_saida) + 2)*sizeof(char));
        sprintf(saida,"%s/%s",dir_saida,nomeGeo);
    }

    nomeSvgGeo = (char*)malloc((strlen(saida) + 5)*sizeof(char));
    sprintf(nomeSvgGeo,"%s.svg",saida);

    lerGeo(arqGeo, nomeSvgGeo, treeObjeto, listaObjeto, listaHash);

    if(arq_pmNome != NULL)
    {
        lerPm(arqPm, treeObjeto, listaObjeto, listaHash);
    }
    if(arq_ecNome != NULL)
    {
        lerEc(arqEc, treeObjeto, listaObjeto, listaHash);
    }
    if(arq_viaNome != NULL)
    {
        lerVia(arqVia, grafo);
    } 
    if (arq_consulta!= NULL)
    {
        nomeQry = concatenacao(arq_consulta);
        saidaQry = (char*)malloc((strlen(nomeQry) + strlen(saida) + 2)*sizeof(char));
        sprintf(saidaQry,"%s-%s",saida,nomeQry);

        lerQry (saidaQry,treeObjeto,listaHash, arqQry, listasQry);
    }


    for(int i = 0; i < 12; i++)
    {
        desalocaQt(treeObjeto[i]);

    }  

    // for(int i = 0; i < 15; i++)
    // {
    //     if(listaObjeto[i] != NULL)
    //     {
    //         removeList(listaObjeto[i], NULL);
    //     }
    // }

    for(int i = 0; i < 11; i++)
    {
        removeList(listasQry[i], NULL);
    }

    
    // for(int i = 0; i < 4; i++)
    // {
    //     deleteHTable(listaHash[i], 0);
    // }

    free(arqGeo);
    free(arqQry);
    free(nomeSvgGeo);
    free(nomeGeo);
    free(nomeQry);
    free(saidaQry);   
    free(saida);
    free(dir_entrada);
    free(dir_saida);
    free(arq_ecNome);
    free(arq_pmNome);
    free(arqEc);
    free(arqPm);

}
