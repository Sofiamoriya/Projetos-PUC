import LDLC.*;

public class Josephus {
    private static ListaDuplamenteLigadaCircular jose;
    private static ListaDuplamenteLigadaCircular mortos;
    private static int vivo;
    // Método principal, inicia a interface gráfica
    public static void main(String[] args){
        new EntradaGrafica("Problema de Josephus");
    }
    // Método para executar o algoritmo de Josephus
    public static void executarJosephus(int numeroDeIndividuos, int intervalo){
        jose = new ListaDuplamenteLigadaCircular();
        mortos = new ListaDuplamenteLigadaCircular();
        int n = numeroDeIndividuos;// N de indivíduos
        int passo = intervalo;// Intervalo de eliminação
        // Preenche a lista circular jose com os indivíduos
        for (int i = 1; i <= n; i++){
            Elemento conteudo = new Elemento(true, i);
            jose.inserirFim(conteudo);
        }

        int cont;
        int vezes = 0;
        No celula = jose.getFim();
        Elemento teste = null;
        
        for (vezes = 1; vezes <= n; vezes++){
            for (cont = 0; cont < passo; cont++)
                do{
                    celula = celula.getProximo();
                    teste = (Elemento) celula.getConteudo();
                }while (!teste.getvivo());// Enquanto o elemento não estiver vivo
            if (vezes != n)
                {
                teste.setVivo(false);  // Define o elemento como morto
                mortos.inserirFim(teste.getpos());
            } 
        }
        vivo = teste.getpos();// Define o índice do último sobrevivente
    }
    //indice do elemento na lista jose 
    public static Elemento getElemento(int index){
        No atual = jose.getInicio();
        for (int i = 0; i < index; i++) {
            atual = atual.getProximo();
        }
        return (Elemento) atual.getConteudo();
    }
    // Obtém o índice do elemento morto 
    public static int getMorto(int index)
    {
        No atual = mortos.getInicio();
        for (int i = 0; i < index; i++) {
            atual = atual.getProximo();
        }
        return (int)atual.getConteudo();
    }
    
    public static int getVivo()
    {
        return vivo;//último sobrevivente
    }
}
