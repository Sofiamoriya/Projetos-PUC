//JVIDA2_SBCI_Controller.cpp - Projeto JVida
//28/09/2023
//Grupo: SBCI
//Bryan Vinicius Pereira Cunha, Cesar Alexandre Gritti Silva, Isabela Groke Gomes, Sofia Miyuki Moriya De Farias

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "JVIDA2_SBCI_Controller.h"
#include "JVIDA2_SBCI_View.cpp"

//funcao que cria a tabela (matriz onde ocorre a simulacao)
void CriaTab()
{
	for(int i = 1; i<=dim; i++)
		for(int j = 1; j<=dim; j++)
			Tab[i][j] = '.';
	g=0;
}

//funcao que interpreta o return da funcao "MenuPr()"
void ExecutaMenu()
{
	int flag, op;
	do{
		op=MenuPr();
		switch(op)
			{
			case 1:
				system("cls");
				MostraMapa(g);
				break;
			case 2:
				CriaTab();
				LimpalistaMortos();
				LimpalistaVivos();
				system("cls");
				apresentaMensagem("\n\t\t\tMapa limpo:");
				MostraMapa(g);
				break;
			case 3:	
				system("cls");
				MostraMapa(g);
				do{
					apresentaMensagem("Digite a posicao que deseja alterar (formato: linha, coluna): ");
					apresentaMensagem("\tDigite -1 para voltar ao menu");
					flag = 0;
					PedePos();
					if(posX==-1)
					{
						system("cls");
						flag=1;
					}
					else if (posX<=0 || posX>dim || posY<=0 || posY>dim)
					{
						system("cls");
						apresentaMensagem("\n\t posicao invalida, digite novamente");
					}
					else
					{
						AlterCel();
						system("cls");
						apresentaPos();
					}
					MostraMapa(g);
				  }while(flag == 0);
				break;
			case 4:
				system("cls");
				viz=(viz==0)?1:0;
				MostraMapa(g);
				break;
			case 5:
				g=0;
				int c,o;
				system("cls");
				Menu5();
				c=ger+g-1;
				time_t It1,It2;
				It1 = time(NULL);
				It2 = It1;
				if(atraso==0)
				{
					while(g<=c)
					{
						do
						{
							apresentaMensagem("\n\t   Digite 1 para mostrar a proxima geracao\n");
							apresentaMensagem("\t\tDigite 0 para desistir\n");
							scanf("%d",&o);
							if(o==1)
								{
								AvanGer();
								g++;	
								system("cls");
								MostraMapa(g);	
								}	
						}while(o!=1 && o!=0);	
						if(o==0)		
							break;
					};
				}
					
				else
				{
					while(g<=c)
						{
						while(difftime(It2,It1)<atraso)
						It2=time(NULL);
						AvanGer();
						g++;
						system("cls");
						MostraMapa(g); 
						It1 = time(NULL);
						It2 = It1;
						};	
				}
				break;
			case 6:
				carregaConfig();
				gravaCelulas();
				break;
			case 7:
				carregaConfig();
				system("cls");
				escolheGravacao();
				break;
			case 8:
				system("cls");
				limpaGer();	
				break;
			case 9:
				system("cls");
				apresentaregras();
				break;	
			case 0:
				break;
			default:
				system("cls");
				apresentaMensagem("opcao invalida");
			}
	  }while(op != 0);
	
}

//funcao que altera uma celula
void AlterCel()
{
	int c=0;
	TipoCel *aux, *auxant;
	
	auxant=pvivo;
	
	if(Tab[posX][posY] == 'O')
	{
		if((pvivo->col==posY)&&(pvivo->lin==posX))
		{
			pvivo=pvivo->next;
			free(auxant);
			totvivo--;
			c=1;
		}
		else
			do
			{
				aux=auxant->next;
				if(aux->col==posY&&aux->lin==posX)
					{
						auxant->next=aux->next;
						free(aux);
						totvivo--;
						c=1;
					}
				else
				{
					auxant=aux;
				}	
			}while(c==0);
		Tab[posX][posY] = '.';
	}
		
	else
		{
		Tab[posX][posY] = 'O';
		carregaVivo(posX,posY);	
		}
	
	LimpalistaMortos();
	LimpalistaVivos();
	ContaVivosAtuais();
	ContaMortosVivos();
	g = 0;
}

//funcao que avanca uma geracao
void AvanGer()
{
	int i, j;
	int qtd = 0;
	TipoCel *aux;
	
	for(i = 1; i<=dim; i++)                   
			for(j = 1; j<=dim; j++)
				for(int l = (i-1); l <=(i+1); l++)
					for(int c = (j-1); c <=(j+1); c++)
						if ((l != 0) && (l != (dim + 1)))
							if ((c != 0) && (c != (dim + 1)))
								if((Tab[i][j] == 'O') && (Tab[l][c] != 'O'))
									Tab[l][c] = '+';

	{
		aux = pvivo;
		while(totvivo>0)	                               
		{
			i= aux->lin; j=aux->col;
			for(int l = (i-1); l <=(i+1); l++)
				for(int c = (j-1); c <=(j+1); c++)
					if ((l != 0) && (l != (dim + 1)))
						if ((c != 0) && (c != (dim + 1)))
							if(Tab[l][c] == 'O')
								qtd ++;	
		
			if(qtd == 4|| qtd==3)  
			        carregaProxV(i,j);
			pvivo = aux->next;
			free(aux);
			aux = pvivo;
			totvivo--;
			qtd=0;
		}
	
	}
	
	aux=pmorto;
		{
			while(totmorto>0)	
			{
		 		i= aux->lin, j=aux->col;
					for(int l = (i-1); l <=(i+1); l++)
						for(int c = (j-1); c <=(j+1); c++)
							if ((l != 0) && (l != (dim + 1)))
								if ((c != 0) && (c != (dim + 1)))
									if(Tab[l][c] == 'O')
									qtd ++;				
			
			if(qtd ==3)
				carregaProxV(i,j);
			pmorto=aux->next;
			free(aux);
			aux=pmorto;
			totmorto--;
			qtd=0;
			}
		}
		
		transfere();
		LimpalistaVivos();
		LimpalistaMortos();
		ContaVivosAtuais();
		ContaMortosVivos();
			
}


void fclear()
{
	int ch;
	while((ch=fgetc(stdin))!=EOF&&ch!='\n');
}
  
//funcao que coloca na lista dinamica as celulas vivas atuais
void carregaVivo(int ii, int jj)
{
	TipoCel* aux = (TipoCel*)malloc(sizeof(TipoCel));
	if(aux==NULL)
	{
		apresentaMensagem("Sem espaco na memoria para inclusao de celula viva\n");
		return;
	}
	aux->lin=ii;
	aux->col=jj;
	if(totvivo==0)
	{
		pvivo=aux;
		pvivo->next=NULL;
	}
	else
	{
		aux->next=pvivo;
		pvivo=aux;
	}
	totvivo++;
}

//funcao que coloca na lista dinamica as celulas mortas vizinhas atuais
void carregaMVA(int ii, int jj)
{
	TipoCel* aux = (TipoCel*)malloc(sizeof(TipoCel));
	if(aux==NULL)
	{
		apresentaMensagem("Sem espaco na memoria para inclusao de celula morta\n");
		return;
	}
	aux->lin=ii;
	aux->col=jj;
	if(totmorto==0)
	{
		pmorto=aux;
		pmorto->next=NULL;
	}
	else
	{
		aux->next=pmorto;
		pmorto=aux;
	}
	totmorto++;
}

//funcao que coloca na lista dinamica as celulas vivas da proxima geracao
void carregaProxV(int ii, int jj)
{
	TipoCel* aux = (TipoCel*)malloc(sizeof(TipoCel));
	if(aux==NULL)
	{
		apresentaMensagem("Sem espaco na memoria para inclusao de celula viva da proxima geracao\n");
		return;
	}
	aux->lin=ii;
	aux->col=jj;
	if(totvivoprox==0)
	{
		pvivoprox=aux;
		pvivoprox->next=NULL;
	}
	else
	{
		aux->next=pvivoprox;
		pvivoprox=aux;
	}
	totvivoprox++;
}

//funcao que transfere as celulas da proxima geracao para a matriz
void transfere()
{
	TipoCel *aux;
	for(int i = 1; i<=dim; i++)
		for(int j = 1; j<=dim; j++)
			Tab[i][j] = '.';
			
	aux = pvivoprox;
	while(totvivoprox>0)
	{
		Tab[aux->lin][aux->col]='O';
		pvivoprox=aux->next;
		free(aux);
		aux = pvivoprox;
		totvivoprox--;
	}	
}

//funcao que verifica quais celulas sao mortas vizinhas
void ContaMortosVivos()
{
	TipoCel *auxant, *aux;
	int i,j,m,c;
	
	for(i = 1; i<=dim; i++)                   
		for(j = 1; j<=dim; j++)
			for(int l = (i-1); l <=(i+1); l++)
				for(int c = (j-1); c <=(j+1); c++)
					if ((l != 0) && (l != (dim + 1)))
						if ((c != 0) && (c != (dim + 1)))
							if((Tab[i][j] == 'O') && (Tab[l][c] != 'O'))
								Tab[l][c] = '+';


	for(i = 1; i<=dim; i++)                   
		for(j = 1; j<=dim; j++)
			if(Tab[i][j]=='+')
				carregaMVA(i,j);
					
}

//funcao que verifica quais celulas estao vivas
void ContaVivosAtuais()
{
	for(int i = 1; i<=dim; i++)                   
		for(int j = 1; j<=dim; j++)
			if(Tab[i][j]=='O')
				carregaVivo(i,j);
}

//funcao que limpa a lista dos mortos-vizinhos
void LimpalistaMortos()
{
	TipoCel *aux,*aux2;
	if(totmorto>0)
	{
		aux = pmorto;
		while(aux->next!=NULL)
		{
		aux2 = aux->next;
		free(aux);
		aux = aux2;
		}
		free(aux);
		pmorto = NULL;
		totmorto=0;
	}
	
}

//funcao que limpa a lista dos vivos atuais
void LimpalistaVivos()
{
	TipoCel *aux,*aux2;
	if(totvivo>0)
	{
		aux = pvivo;
	while(aux->next!=NULL)
	{
		aux2 = aux->next;
		free(aux);
		aux = aux2;
	}
	free(aux);
	pvivo=NULL;
	totvivo=0;
	}
}

//funcao que grava as celulas vivas da configuracao
void gravaCelulas()
{
	int k,i,ni;
	k= qtconf;
	if(totvivo==0)
	  return;
	  
	TipoCel *aux;
	aux = pvivo;
	ni=0;
	do{
			Lvivo.L[ni].lin = aux->lin;
			Lvivo.L[ni].col = aux->col;
			ni++;
			aux = aux->next;
	  }while(aux!=NULL);
	Lvivo.dimensao = dim;
	Lvivo.cont = totvivo;
	LConfig[k].TL = Lvivo;
	
	FILE *fp;
	if((fp = fopen("CONFIG_INIC","w"))==NULL)
	{
		apresentaMensagem("ERRO: O arquivo CONFIG_INIC nao pode ser aberto para gravacao");
		return;
	}
	for(i = 0; i<=qtconf;i++)
	{
		if(fwrite(&LConfig[i],sizeof(TipoLista),1,fp)!=1)
		{
			apresentaMensagem("Erro na gravacao do arquivo CONFIG_INIC");
			fclose(fp);
			return;
		}
	}
	fclose(fp);
	qtconf++;
	system("cls");
	apresentaMensagem("Configuracao gravada OK");
}

//funcao que carrega o arquivo com as configuracoes salvas
void carregaConfig()
{
	int k;
	FILE *fp;
	if((fp = fopen("CONFIG_INIC","r"))!=NULL)
	{
		qtconf = 0;
		k = 0;
		while(!feof(fp))
		{
			if(fread(&LConfig[k],sizeof(TipoLista),1,fp)!=1)
			{
				fclose(fp);
				return;
			}
			qtconf++;
			k++;
		}
		fclose(fp);
	}
}

//funcao que transfere as celulas salvas para a lista dinamica de celulas vivas
void recuperaCelulas()
{
	int i,j,k,ni;
	TipoCel *aux;
	if(qtconf==0)
	{
		apresentaMensagem("Nao existe configuracao a recuperar");
		return;
	}
	k = ultrec+1;
	if(k>=qtconf)
		k=0;
	Lvivo = LConfig[k].TL;
	ultrec = k;
	
	LimpalistaMortos();
	LimpalistaVivos();
	dim = Lvivo.dimensao;
	CriaTab();
	
	for(ni=0;ni<Lvivo.cont;ni++)
		carregaVivo(Lvivo.L[ni].lin,Lvivo.L[ni].col);
		
	if(totvivo>0)
	{
		aux = pvivo;
		do
		{
			Tab[aux->lin][aux->col]='O';
			aux = aux->next;
		}while(aux!=NULL);
		ContaMortosVivos();
		MostraMapa(g);
	}	
	
}

//funcao que limpa as o deposito
void limpaGer()
{
	if(qtconf>0)
	{
		if(rconfirma("Confirma exclusao das configuracoes iniciais? ")==0)
			return;
	}
	qtconf = 0;
	ultrec = -1;
	deletaConfig();
	apresentaMensagem("O deposito de geracoes iniciais esta vazio");
	
}

//funcao que exclui as configuracoes salvas
void deletaConfig()
{
	if(remove("CONFIG_INIC")!=0)
	{
		apresentaMensagem("ERRO: O arquivo CONFIG_INIC nao pode ser removido");
		return;
	}
	qtconf = 0;
	apresentaMensagem("O arquivo CONFIG_INIC foi removido OK");
}

//funcao que apresenta as regras do jogo da vida
void apresentaregras()
{
apresentaMensagem(" REGRAS ");
apresentaMensagem("1-Escolher as celulas originais que a partir delas pode comecar a surgir as proximas geracoes.");
apresentaMensagem("2-Qualquer celula viva com menos de dois vizinhos morre de solidao.");
apresentaMensagem("3-Qualquer celula viva com mais de tres vizinhos morre de superpopulacao.");
apresentaMensagem("4-Qualquer celula com exatamente tres vizinhos vivos se torna uma celula viva.");
apresentaMensagem("5-Qualquer celula com dois vizinhos vivos continua no mesmo estado para a proxima geracao.");
}