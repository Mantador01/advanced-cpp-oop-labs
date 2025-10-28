#include "Image2.h"

Image2::Image2(int w, int h, bool couleur) : width(w), height(h) {
    pixels.resize(width * height);
    for (int i = 0; i < width * height; ++i) {
        if (couleur) {
            pixels[i] = new PixelCouleur(255, 0, 0);  // Initialiser avec des pixels rouges
        } else {
            pixels[i] = new PixelNiveauDeGris(128);  // Initialiser avec un niveau de gris de 128
        }
    }
}

Image2::~Image2() {
    for (Pixel* pixel : pixels) {
        delete pixel;  // Libérer chaque pixel
    }
}

Image2::Image2(const Image2& other) : width(other.width), height(other.height) {
    pixels.resize(width * height);
    for (int i = 0; i < width * height; ++i) {
        if (PixelCouleur* p = dynamic_cast<PixelCouleur*>(other.pixels[i])) {
            pixels[i] = new PixelCouleur(*p);
        } else if (PixelNiveauDeGris* p = dynamic_cast<PixelNiveauDeGris*>(other.pixels[i])) {
            pixels[i] = new PixelNiveauDeGris(*p);
        }
    }
}

Image2& Image2::operator=(const Image2& other) {
    if (this != &other) {
        for (Pixel* pixel : pixels) {
            delete pixel;
        }
        width = other.width;
        height = other.height;
        pixels.resize(width * height);
        for (int i = 0; i < width * height; ++i) {
            if (PixelCouleur* p = dynamic_cast<PixelCouleur*>(other.pixels[i])) {
                pixels[i] = new PixelCouleur(*p);
            } else if (PixelNiveauDeGris* p = dynamic_cast<PixelNiveauDeGris*>(other.pixels[i])) {
                pixels[i] = new PixelNiveauDeGris(*p);
            }
        }
    }
    return *this;
}

Image2::Image2(Image2&& other) noexcept : width(other.width), height(other.height), pixels(std::move(other.pixels)) {
    other.pixels.clear();
}

Image2& Image2::operator=(Image2&& other) noexcept {
    if (this != &other) {
        for (Pixel* pixel : pixels) {
            delete pixel;
        }
        width = other.width;
        height = other.height;
        pixels = std::move(other.pixels);
        other.pixels.clear();
    }
    return *this;
}

void Image2::afficher() const {
    for (const Pixel* pixel : pixels) {
        pixel->afficher();
    }
}
