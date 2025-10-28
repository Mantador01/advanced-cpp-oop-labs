#ifndef PIXEL_H
#define PIXEL_H

#include <iostream>

// Classe de base Pixel
class Pixel {
public:
    virtual ~Pixel() = default;
    virtual void afficher() const = 0;  // Méthode virtuelle pure
};

// Classe dérivée PixelCouleur
class PixelCouleur : public Pixel {
private:
    unsigned char r, g, b;

public:
    PixelCouleur(unsigned char red, unsigned char green, unsigned char blue);
    void afficher() const override;
};

// Classe dérivée PixelNiveauDeGris
class PixelNiveauDeGris : public Pixel {
private:
    unsigned char niveau;

public:
    PixelNiveauDeGris(unsigned char n);
    void afficher() const override;
};

#endif
