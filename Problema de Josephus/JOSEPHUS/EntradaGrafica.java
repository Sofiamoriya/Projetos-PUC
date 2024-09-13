import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class EntradaGrafica extends JFrame implements ActionListener {
    private JTextField tc, tc2, tc3;//entradas 
    private JLabel[][] grid;//matriz
    private JLabel ordem, morto; // último sobrevivente e o indivíduo executado
    private JButton convS, convE, convR, convA, convSair;//botões
    private Color alive = Color.GREEN; //cor dos vivos
    private Color dead = Color.RED; //cor dos mortos 
    private Color transparent = new Color(0, 0, 0, 0); // transparente
    int numRoletadores;//variavel Numero de individuos
    int intervalo;//variavel intervalo
    int tempoEspera;//variavel Tempo de Espera
    Simulacao inicio;//simula eliminação de Josephus

    public static void main(String[] args) {
        new EntradaGrafica("Problema de Josephus");
    }

    EntradaGrafica(String titulo) {
        super(titulo);
        setSize(800, 800);//tamanho 
        setLocation(400, 220);//
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        Container c = getContentPane();
        c.setLayout(new BorderLayout());
        
        //UTILIZADO GridBagLayout como layout e dividimos em Norte, Centro e Sul.
        //usando grid x e grid y em estilo de coordenadas no plano cartesiano para adicionarmos no melhor formato nossa interface 
        // Painel Norte
        JPanel northPanel = new JPanel(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);
        gbc.fill = GridBagConstraints.HORIZONTAL;
        //No Norte temos as entradas num de individuos,tempo de espera, intervalo, as legendas de vermelho para Mortos, Verde para Vivos  
        // E a indicacao do ultimo sobrevivente encontrado.  
        //Label Numero de Individuos
        gbc.gridx = 0;
        gbc.gridy = 0;
        northPanel.add(new JLabel("Numero de Individuos", JLabel.CENTER), gbc);//variavel do numero de individuos
        gbc.gridx = 1;
        //caixa de texto Numero de Individuos
        tc = new JTextField();
        tc.addActionListener(this); 
        northPanel.add(tc, gbc);

        //Label Numero de Individuos
        gbc.gridx = 0;
        gbc.gridy = 1;
        northPanel.add(new JLabel("Intervalo", JLabel.CENTER), gbc);//variavel do intervalo
        gbc.gridx = 1;
        //caixa de texto Intervalo
        tc2 = new JTextField();
        tc2.addActionListener(this); 
        northPanel.add(tc2, gbc);
        //Label Tempo de Espera
        gbc.gridx = 0;
        gbc.gridy = 2;
        northPanel.add(new JLabel("Tempo de espera", JLabel.CENTER), gbc);//variavel do tempo de espera
        gbc.gridx = 1;
        //caixa de texto Tempo de Espera
        tc3 = new JTextField();
        tc3.addActionListener(this); 
        northPanel.add(tc3, gbc);

        gbc.gridx = 0;
        gbc.gridy = 3;
        
        northPanel.add(new JLabel("Vivo:", JLabel.RIGHT), gbc);//Label/legenda dos vivos

        gbc.gridx = 1;
        JLabel explainColoralive = new JLabel();
        explainColoralive.setPreferredSize(new Dimension(40, 20)); // Aumenta o tamanho dos quadrados de cor
        explainColoralive.setOpaque(true);
        explainColoralive.setBackground(alive);
        explainColoralive.setBorder(BorderFactory.createLineBorder(Color.BLACK));
        northPanel.add(explainColoralive, gbc);

        gbc.gridx = 0;
        gbc.gridy = 4;
        northPanel.add(new JLabel("Morto:", JLabel.RIGHT), gbc);//legenda dos mortos

        gbc.gridx = 1;
        JLabel explainColordead = new JLabel();
        explainColordead.setPreferredSize(new Dimension(40, 20)); // Aumenta o tamanho dos quadrados de cor
        explainColordead.setOpaque(true);
        explainColordead.setBackground(dead);
        explainColordead.setBorder(BorderFactory.createLineBorder(Color.BLACK));
        northPanel.add(explainColordead, gbc);

        gbc.gridx = 0;
        gbc.gridy = 5;
        morto = new JLabel("Individuo executado:", JLabel.CENTER);//exibe o individuo executado
        northPanel.add(morto, gbc);

        gbc.gridx = 1;
        ordem = new JLabel("", JLabel.CENTER);
        northPanel.add(ordem, gbc);

        c.add(northPanel, BorderLayout.NORTH);

        // Painel Centro
        //Não utilizamos imagens na matriz, pois estas ficariam muito pequenas pela quantidade de quadrados em nossa interface 30x30.
        JPanel centerPanel = new JPanel(new GridLayout(30, 30));
        grid = new JLabel[30][30];
        int p = 1;
        for (int i = 0; i < 30; i++) {
            for (int j = 0; j < 30; j++) {
                grid[i][j] = new JLabel("");
                grid[i][j].setPreferredSize(new Dimension(20, 20)); // Aumenta o tamanho dos quadrados no grid
                grid[i][j].setBorder(BorderFactory.createLineBorder(Color.LIGHT_GRAY));
                grid[i][j].setOpaque(true); // Definir opacidade como verdadeira
                grid[i][j].setBackground(transparent); // Definir cor de fundo transparente
                centerPanel.add(grid[i][j]);
                grid[i][j].setToolTipText("(" + p + ")");
                p++;
            }
        }
        c.add(centerPanel, BorderLayout.CENTER);

        // Painel Sul
        JPanel southPanel = new JPanel(new GridBagLayout());
        gbc.gridy = 0;
        gbc.gridx = 1;
        //Botao Sobre
        convS = new JButton("Sobre");
        convS.addActionListener(this);
        convS.setToolTipText("Detalha o problema do Josephus e os autores por tras deste projeto");
        southPanel.add(convS);
        
        //Bot~ão Executar
        gbc.gridx = 1;
        convE = new JButton("Executar");
        convE.addActionListener(this);
        convE.setToolTipText("Executa o problema de Josephus com as entradas dadas");
        southPanel.add(convE, gbc);

        //Botao Reiniciar
        gbc.gridx = 2;
        convR = new JButton("Reiniciar/Atualizar");
        convR.addActionListener(this);
        convE.setToolTipText("Executa com as entradas anteriores e atualiza o número de indivíduos caso tenha valor de variáveis alteradas ");
        southPanel.add(convR, gbc);
        //Botao Alterar
        gbc.gridx = 3;
        convA = new JButton("Alterar");
        convA.addActionListener(this);
        convA.setToolTipText("Clique neste botão para alterar o valor das variáveis");
        southPanel.add(convA, gbc);
        //Botão Sair
        gbc.gridx = 4;
        convSair = new JButton("Sair");
        convSair.addActionListener(this);
        convSair.setToolTipText("Fecha o programa");
        southPanel.add(convSair, gbc);
        c.add(southPanel, BorderLayout.SOUTH);

        setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent ae) {
        String cmd = ae.getActionCommand();

        switch (cmd) {
            //ação do botão Sobre, que informa sobre a origem, autores e função do projeto
            case "Sobre":
                JOptionPane.showMessageDialog(this,"Josephus VFINAL:\n Esta aplicacao implementa o algortimo de Josephus com ListaDuplamentCircular\n Led-Laboratorio de Estrutura de Dinamicas\n Alunos:\n Carlos Gabriel Gouveia\n Cesar Alexandre Gritti Silva\n Juan Fernando Coucolis Ishino\n Sofia Miyuki Moriya de Farias\n Depto. de Computação - PUCSP\n");
                validate();
                repaint();
                break;
                //ação do botão Executar
            case "Executar"://executa o programa, usando as vari´áveis dadas pelo usuario, executa os vivos de verde para vermelho e encontra o último sobrevivente
                try {
                    morto.setText("Individuo executado:");
                    ordem.setText("");
                    tc.setEditable(false);
                    tc2.setEditable(false);
                    tc3.setEditable(false);
                    numRoletadores = Integer.parseInt(tc.getText());
        
                    // Verificação adicional para valores de numeros de indiv´íduos acima de 900 
                    if (numRoletadores > 900) {
                        throw new IllegalArgumentException("O número de indivíduos não pode ser superior a 900. Clique em Alterar para fazer tal ação." );
                    }
                    intervalo = Integer.parseInt(tc2.getText()); 
                    if(intervalo > numRoletadores){
                        throw new IllegalArgumentException("O intervalo do número de indivíduos não pode ser maior que o próprio número de indivíduos. Clique em Alterar para adicionar um valor válido.");
                    }
                    tempoEspera = Integer.parseInt(tc3.getText());
                    Josephus.executarJosephus(numRoletadores, intervalo);
                    atualizarGridVivos(numRoletadores);
                    inicio = new Simulacao();
                    inicio.start();
                    convE.setEnabled(false);
                    convA.setEnabled(false);
                    convR.setEnabled(false);
                } catch (NumberFormatException ex) {
                    JOptionPane.showMessageDialog(this, "Por favor, insira valores válidos e clique no botão Alterar para fazer tal ação.");
                } catch (IllegalArgumentException ex) {
                    JOptionPane.showMessageDialog(this, ex.getMessage());
                }
                break;
                //ação do botão Reiniciar/atualizar
                                        //reinicia a matriz com as mesmas entradas para analisar o processo executado novamente, caso as variáveis não tenham sido alteradas    
            case "Reiniciar/Atualizar"://atualiza número de individuos caso as variaveis tenham sido alteradas ou desejamos ver o resultado antes de Executar  
                morto.setText("Individuo executado:");
                ordem.setText("");
                convE.setEnabled(true);
                // Atualiza os valores das entradas com os novos valores inseridos
                 try {
                    numRoletadores = Integer.parseInt(tc.getText());
                    if (numRoletadores > 900) {
                        throw new IllegalArgumentException("O número de indivíduos não pode ser superior a 900. Clique em Alterar para fazer tal ação." );
                    }
                    intervalo = Integer.parseInt(tc2.getText()); 
                    if(intervalo > numRoletadores){
                        throw new IllegalArgumentException("O intervalo do número de indivíduos não pode ser maior que o próprio número de indivíduos. Clique em Alterar para adicionar um valor válido.");
                    }
                    tempoEspera = Integer.parseInt(tc3.getText());
                } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(this, "Por favor, insira valores válidos.");
                }
                catch (IllegalArgumentException ex) {
                    JOptionPane.showMessageDialog(this, ex.getMessage());
                return;
                }
                atualizarGridVivos(numRoletadores);
                break;
                //ação do botão Alterar, disponibiliza a alteraç~ão das entradas numero de individuos(tc), intervalo(tc2) e tmepo d eespera(tc3)
            case "Alterar":
                morto.setText("Individuo executado:");
                ordem.setText("");
                convE.setEnabled(false);
                for (int i = 0; i < 30; i++) {
                    for (int j = 0; j < 30; j++) {
                        grid[i][j].setBackground(transparent); // Cor transparente
                        grid[i][j].setOpaque(true); // Definir opacidade como verdadeira
                    }
                }
                tc.setEditable(true);
                tc2.setEditable(true);
                tc3.setEditable(true);
                repaint(); // Redesenha a interface
                break;
                //ação do botão sair
            case "Sair":
                System.exit(0);
                break;
                
            
        }
    }    
    
    // Atualiza o grid com todos os indivíduos (vivos e mortos)
    private void atualizarGrid(int numRoletadores) {
                for (int i = 0; i < numRoletadores; i++) {
            Elemento e = Josephus.getElemento(i);
            int row = i / 30;
            int col = i % 30;
            if (e != null && e.getvivo()) {
                grid[row][col].setBackground(alive);
                grid[row][col].setOpaque(true);
            } else {
                grid[row][col].setBackground(dead);
                grid[row][col].setOpaque(true);
            }
        }
        repaint(); // Redesenha a interface
    }
    // Atualiza o grid marcando apenas os indivíduos vivos
    private void atualizarGridVivos(int numRoletadores) {
        for (int i = 0; i < numRoletadores; i++) {
            int row = i / 30;
            int col = i % 30;
            grid[row][col].setBackground(alive);
            grid[row][col].setOpaque(true); // Definir opacidade como verdadeira
        }
        repaint(); // Redesenha a interface
    }
    
    // Atualiza grid marcando o indivíduo morto e exibe o último sobrevivente
    private void atualizarGridMortos(int morto) {
        int row = (morto - 1) / 30;
        int col = (morto - 1) % 30;
        grid[row][col].setBackground(dead);
        grid[row][col].setOpaque(true); // Definir opacidade como verdadeira
        String m = "" + morto;
        ordem.setText(m);
        repaint(); // Redesenha a interface
    }

    //Encontra o último sobrevivente do problema de josephus 
    private class Simulacao extends Thread {
        public void run() {
            int i = 1;
            try {
                while (i < numRoletadores) {
                    int j;
                    j = Josephus.getMorto(i - 1);
                    atualizarGridMortos(j);
                    i++;
                    this.sleep(tempoEspera);
                }
                morto.setText("Individuo sobrevivente");
                ordem.setText("" + Josephus.getVivo());
                convA.setEnabled(true);
                convR.setEnabled(true);
            } catch (InterruptedException e) {
                System.out.println("ERRO INESPERADO");
                System.exit(0);
            }
        }
    }
}

