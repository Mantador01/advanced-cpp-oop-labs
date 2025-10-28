#include "Pixel.h"

PixelCouleur::PixelCouleur(unsigned char red, unsigned char green, unsigned char blue)
    : r(red), g(green), b(blue) {}

void PixelCouleur::afficher() const {
    std::cout << "Pixel couleur (R=" << (int)r << ", G=" << (int)g << ", B=" << (int)b << ")\n";
}

PixelNiveauDeGris::PixelNiveauDeGris(unsigned char n) : niveau(n) {}

void PixelNiveauDeGris::afficher() const {
    std::cout << "Pixel niveau de gris (" << (int)niveau << ")\n";
}
