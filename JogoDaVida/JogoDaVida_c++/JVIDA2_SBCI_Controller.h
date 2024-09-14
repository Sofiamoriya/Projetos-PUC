//JVIDA2_SBCI_Controller.h - Projeto JVida
//28/09/2023
//Grupo: SBCI
//Bryan Vinicius Pereira Cunha, Cesar Alexandre Gritti Silva, Isabela Groke Gomes, Sofia Miyuki Moriya De Farias


//funcao que cria a tabela (matriz onde ocorre a simulacao)
void CriaTab();
//funcao que altera uma celula
void AlterCel();
//funcao que avanca uma geracao
void AvanGer();
//funcao que interpreta o return da funcao "MenuPr()"
void ExecutaMenu();

void fclear();
//funcao que coloca na lista dinamica as celulas vivas atuais
void carregaVivo(int ii, int jj);
//funcao que coloca na lista dinamica as celulas mortas vizinhas atuais
void carregaMVA(int ii, int jj);
//funcao que coloca na lista dinamica as celulas vivas da proxima geracao
void carregaProxV(int ii, int jj);
//funcao que transfere as celulas da proxima geracao para a matriz
void transfere();
//funcao que verifica quais celulas sao mortas vizinhas
void ContaMortosVivos();
//funcao que verifica quais celulas estao vivas
void ContaVivosAtuais();
//funcao que limpa a lista dos mortos-vizinhos
void LimpalistaMortos();
//funcao que limpa a lista dos vivos atuais
void LimpalistaVivos();
//funcao que grava as celulas vivas da configuracao
void gravaCelulas();
//funcao que carrega o arquivo com as configuracoes salvas
void carregaConfig();
//funcao que transfere as celulas salvas para a lista dinamica de celulas vivas
void recuperaCelulas();
//funcao que limpa as o deposito de geracoes iniciais
void limpaGer();
//funcao que exclui as configuracoes salvas
void deletaConfig();
//funcao que apresenta as regras
void apresentaregras();