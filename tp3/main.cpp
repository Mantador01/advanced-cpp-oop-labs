#include "Image2.h"

int main() {
    // Image avec des pixels en couleur
    Image2 imageCouleur(2, 2, true);
    imageCouleur.afficher();

    // Image avec des pixels en niveau de gris
    Image2 imageGris(2, 2, false);
    imageGris.afficher();

    return 0;
}
