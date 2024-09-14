//JVIDA2_SBCI_Model.cpp - Projeto JVida
//28/09/2023
//Grupo: SBCI
//Bryan Vinicius Pereira Cunha, Cesar Alexandre Gritti Silva, Isabela Groke Gomes, Sofia Miyuki Moriya De Farias

#include "JVIDA2_SBCI_Model.h"

typedef struct cel
{
	int lin,col;
	struct cel *next;
	
}TipoCel;


TipoCel *pvivo, *pmorto, *pvivoprox;

typedef struct c
{
	int lin,col;
}Cel;

typedef struct list
{
	int cont;
	Cel L[400];
	int dimensao;
}TipoLista;

TipoLista Lvivo;

struct arquivo
{
	TipoLista TL;
}LConfig[50];



