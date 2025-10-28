#include <iostream>
#include <cstring>

class Image {
private:
    int width, height;
    unsigned char* pixels;  // Tableau de pixels contigu

public:
    // Constructeur par défaut
    Image(int w, int h) : width(w), height(h) {
        pixels = new unsigned char[width * height];  // Allocation contiguë
        std::memset(pixels, 0, width * height);      // Initialisation à zéro
    }

    // Destructeur
    ~Image() {
        delete[] pixels;
    }

    // Constructeur par copie
    Image(const Image& other) : width(other.width), height(other.height) {
        pixels = new unsigned char[width * height];
        std::memcpy(pixels, other.pixels, width * height);
    }

    // Opérateur d'affectation par copie
    Image& operator=(const Image& other) {
        if (this != &other) {
            delete[] pixels;
            width = other.width;
            height = other.height;
            pixels = new unsigned char[width * height];
            std::memcpy(pixels, other.pixels, width * height);
        }
        return *this;
    }

    // Constructeur par déplacement
    Image(Image&& other) noexcept : width(other.width), height(other.height), pixels(other.pixels) {
        other.pixels = nullptr;  // Réinitialiser l'ancien objet pour éviter la libération double
    }

    // Opérateur d'affectation par déplacement
    Image& operator=(Image&& other) noexcept {
        if (this != &other) {
            delete[] pixels;
            width = other.width;
            height = other.height;
            pixels = other.pixels;
            other.pixels = nullptr;  // Réinitialiser l'ancien objet
        }
        return *this;
    }
};
