#ifndef IMAGE2_H
#define IMAGE2_H

#include <vector>
#include "Pixel.h"

// Classe Image2 utilisant des pixels polymorphes
class Image2 {
private:
    int width, height;
    std::vector<Pixel*> pixels;  // Pointeurs polymorphes vers des pixels

public:
    Image2(int w, int h, bool couleur = true);  // Initialisation avec des pixels en couleur ou en niveau de gris
    ~Image2();

    // Copie et affectation
    Image2(const Image2& other);
    Image2& operator=(const Image2& other);

    // Déplacement
    Image2(Image2&& other) noexcept;
    Image2& operator=(Image2&& other) noexcept;

    void afficher() const;
};

#endif
