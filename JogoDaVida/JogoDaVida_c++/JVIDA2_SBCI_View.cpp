//JVIDA2_SBCI_View.cpp - Projeto JVida
//28/09/2023
//Grupo: SBCI
//Bryan Vinicius Pereira Cunha, Cesar Alexandre Gritti Silva, Isabela Groke Gomes, Sofia Miyuki Moriya De Farias

#include "JVIDA2_SBCI_View.h"


//funcao que apresenta o menu principal
int MenuPr()
{
	int op;
	
	fclear();
	printf("\n1-Apresentar o mapa\n");
	printf("2-Limpar o mapa\n");
	printf("3-Incluir/Excluir c%clulas vivas\n",130);
	printf("4-Mostrar/Esconder os mortos-vizinhos\n");
	printf("5-Iniciar o Processo\n");
	printf("6-Gravar uma gera%c%co\n", 135,198);
	printf("7-Recuperar uma gera%c%co inicial cadastrada\n", 135,198);
    printf("8-Limpar o cadastro de gera%c%ces iniciais cadastradas (n gera%c%ces)\n",135,228,135,228);
    printf("9-Regras de evolu%c%co das celulas\n",135,198);
    printf("0-Sair\n");
    printf("Escolha uma op%c%co: ", 135,198);
	scanf("%d", &op);
	return op;
    
}

//funcao que inicia a simulacao
void Iniciar()
{
	do{
		system("cls");
		printf("\t\tJogo da Vida\t\t\n\n\n");
	    printf("Escolha as dimens%ces da matriz (entre 10 e 60): ", 228);
	    scanf("%d",&dim);
	    
	  }while(dim>60 || dim<10);
	  
	//funcao que cria a tabela (matriz onde ocorre a simulacao)
	CriaTab();
}

//funcao que mostra o mapa
void MostraMapa(int g)
{
	
	int i, j;
	TipoCel *aux;
	
	//se houver algum '+' na tabela, ele sera substituido por '.'
	for(i = 1; i<=dim; i++)
			for(j = 1; j<=dim; j++)
				if(Tab[i][j] == '+')
					Tab[i][j] = '.';
					
	//caso o usuario deseje ver os vizinhos, os '+' serao colocados no lugar correto		
	if(viz == 1)
		for(i = 1; i<=dim; i++)
			for(j = 1; j<=dim; j++)
				for(int l = (i-1); l <=(i+1); l++)
					for(int c = (j-1); c <=(j+1); c++)
						if ((l != 0) && (l != (dim + 1)))
							if ((c != 0) && (c != (dim + 1)))
								if((Tab[i][j] == 'O') && (Tab[l][c] != 'O'))
									Tab[l][c] = '+';
									
	
	//apresenta a matriz, com as devidas correcoes
	printf("\n\t\t  Gera%c%co %d\n",135,198,g);
	printf("\n");
	printf("  ");
	for(int a=1;a<=dim;a++)
	
		if(a<10)
			printf(" 0%d",a);	
		else
			printf(" %d",a);
	for(i=1;i<=dim;i++)
	{
		if(i<10)
			printf("\n0%d ",i);
		else
			printf("\n%d ",i);
		for(j=1;j<=dim;j++)
			printf(" %c ",Tab[i][j]);
			
			
	}
	MostraLvivo();
	MostraLmorto();
}

//funcao que apresenta uma mensagem
void apresentaMensagem(char msg[100])
{
	printf("%s\n",msg);
}

//funcao que pede a posicao da celula
void PedePos()
{
	posX = -1;
	posY = -1;
	fclear();
	printf("\t\tPosicao:");
	scanf("%d, %d", &posX, &posY);
}

//funcao que apresenta a posicao da celula alterada
void apresentaPos()
{
	printf("a posi%c%co (%d, %d) foi atualizada\n", 135, 198, posX, posY);
}

//funcao que apresenta um menu caso o usuario escolha 5 no menu
void Menu5()
{
	MostraMapa(g);
	printf("Digite a quantidade de gera%c%ces que deseja simular: ",135,228);
	scanf("%d",&ger);
	printf("Digite a velocidade de sucess%co das gera%c%ces(segundos): ",198,135,228);
	scanf("%d",&atraso);
}

//funcao que apresenta na tela a lista de celulas vivas atuais
void MostraLvivo()
{
	int c=0;
	TipoCel *aux;
	aux=pvivo;
	if(totvivo>0)
	{
		printf("\n\n");
		printf("C%clulas vivas: ",130);
		while(aux->next!=NULL)
		{
			printf("(%2.d,%2.d)  ",aux->lin,aux->col);
			aux=aux->next;
			c++;
			if(c%10==0)
				printf("\n\t\t ");
			
		}
		printf("(%2.d,%2.d)\n",aux->lin,aux->col);
	}
	printf("\n");
}

//funcao que apresenta na tela a lista de mortos-vizinhos
void MostraLmorto()
{
	int c=0;
	TipoCel *aux;
	aux=pmorto;
	if(totmorto>0)
	{
		printf("C%clulas mortas-vizinhas: ",130);
		while(aux->next!=NULL)
		{
			printf("(%2.d,%2.d)  ",aux->lin,aux->col);
			aux=aux->next;
			c++;
			if(c%10==0)
				printf("\n\t\t\t ");
		}
		printf("(%2.d,%2.d)  ",aux->lin,aux->col);
	}
	printf("\n\n");
}

//funcao que permite ao usuario escolher a gravacao que deseja recuperar
void escolheGravacao()
{
	int opcao;
	do
	{
		recuperaCelulas();
		if(qtconf==0)
			return;
		
		printf("Digite 1 para escolher a gera%c%co acima\n",135,198);
		printf("Digite 2 para mostrar a pr%cxima gera%c%co cadastrada\n",162,135,198);
		printf("Op%c%co:",135,198);
		scanf("%d",&opcao);
		system("cls");
		if(opcao!=1&&opcao!=2)
			printf("\t\tOp%c%co Inv%clida\n",135,198,160);	
		
		
	}while(opcao!=1);
	MostraMapa(g);
	
}

//funcao que faz uma pergunta ao usuario e retorna a opcao escolhida
int rconfirma(char pergunta[500])
{
	int resposta;
	printf("%s",pergunta);
	printf("\nDigite 1 para confirmar e 0 para cancelar:");
	scanf("%d",&resposta);
	system("cls");
	return resposta;
	
}
