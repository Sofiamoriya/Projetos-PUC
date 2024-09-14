//JVIDA2_SBCI_Model.h - Projeto JVida
//28/09/2023
//Grupo: SBCI
//Bryan Vinicius Pereira Cunha, Cesar Alexandre Gritti Silva, Isabela Groke Gomes, Sofia Miyuki Moriya De Farias

//tabela principal
char Tab[61][61];
//dimensoes da tabela
int dim;
//coordenadas da celula a ser manipulada
int posX, posY;
//variavel que verifica se o usuario deseja ver os vizinhos mortos das celulas vivas
int viz = 0;
//variaveis que contrlam o atraso e a geracao que deve ser atingida apos o 'processo'
int atraso, ger;
//variavel que armazena qual e a geracao atual
int g;
//variaveis que contam a quantidade de vivos atuais, mortos atuais e os que ficarao vivos na proxima geracao
int totvivo=0, totmorto=0, totvivoprox=0;
//variavel que indica a quantidade de configuracoes salvas
int qtconf;
//variavel que controla as recuperacoes das configuracoes
int ultrec = -1;



