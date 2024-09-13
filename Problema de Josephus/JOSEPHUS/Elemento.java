public class Elemento {
    private boolean vivo;// Indica se o elemento está vivo ou morto
    private int pos;// Posicao do elemento
    //inicializa o elemento
    public Elemento(boolean vivo, int pos) {
        this.vivo = vivo;
        this.pos = pos;
    }
        //estado do elemento (vivo ou morto)
    public boolean getvivo() {
        return this.vivo;
    }
        //define o elemento vivo ou morto
    public void setVivo(boolean vivo) {
        this.vivo = vivo;
    }
    //posicao do elemento
    public int getpos() {
        return this.pos;
    }
}
