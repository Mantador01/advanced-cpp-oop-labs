Exemple d'une classe Image en Java
java
Copier le code
public class Image {
    private int width;
    private int height;
    private byte[] data;

    // Constructeur
    public Image(int w, int h) {
        this.width = w;
        this.height = h;
        this.data = new byte[width * height];  // Allocation automatique
    }

    // Le garbage collector s'occupe de libérer la mémoire, donc pas de destructeur explicite
}
Avantages en Java
Simplicité : Le garbage collecto