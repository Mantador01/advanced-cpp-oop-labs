
# Explication des exercices précédents

## Exercice 1 : Générateur de multiples en C++

### Objectif :
Dans cet exercice, il s'agissait de créer une classe en C++ qui génère des multiples d'une valeur donnée. L'objectif était d'implémenter un générateur d'entiers qui, à chaque appel de l'opérateur `()`, renvoie le prochain multiple d'une valeur spécifiée lors de l'initialisation de l'objet.

### Implémentation :
La classe `MultipleGenerator` a été construite pour générer des multiples d'une valeur donnée. Le membre `current` de la classe garde en mémoire le dernier multiple généré, et à chaque appel de l'opérateur `()`, on incrémente `current` par la valeur de `multiple`.

### Code de base :
```cpp
#include <iostream>

class MultipleGenerator {
private:
    int multiple;  // Valeur du multiple à générer
    int current;   // État actuel (le prochain multiple à retourner)

public:
    // Constructeur prenant en paramètre la valeur du multiple
    MultipleGenerator(int m) : multiple(m), current(0) {}

    // Surcharge de l'opérateur () pour générer le prochain multiple
    int operator()() {
        current += multiple;  // Augmente de la valeur du multiple
        return current;       // Retourne la nouvelle valeur
    }
};

int main() {
    MultipleGenerator gen5(5);  // Générateur de multiples de 5

    for (int i = 0; i < 5; ++i) {
        std::cout << gen5() << std::endl;  // 5, 10, 15, 20, 25
    }

    return 0;
}
```

### Résultat attendu :
- L'appel à `gen5()` affiche successivement les multiples de 5 : 5, 10, 15, 20, 25.

### Explication :
- **Constructeur** : Le constructeur initialise `multiple` avec la valeur spécifiée (ici 5) et initialise `current` à 0.
- **Opérateur `()`** : Chaque appel de `gen5()` retourne le prochain multiple en augmentant `current` de `multiple`.

---

## Exercice 2 : Gestion des images avec pixels polymorphes en C++

### Objectif :
Cet exercice consiste à implémenter deux versions de la classe `Image` en C++ pour gérer des images de pixels. La première version (`Image`) stocke des pixels de manière contiguë dans la mémoire (optimisée pour les performances et la mémoire). La seconde version (`Image2`) utilise une indirection (pointeurs) pour accéder aux pixels, comme cela se fait dans Java.

Dans une extension de l'exercice, la classe `Image2` devait être modifiée pour prendre en charge des **pixels polymorphes**, c'est-à-dire deux types de pixels : en couleur et en niveau de gris.

### Hiérarchie de classes :

1. **Classe de base `Pixel`** : Classe abstraite avec une méthode virtuelle pure `afficher()`, qui sera implémentée par les classes dérivées.
2. **Classes dérivées** : 
   - `PixelCouleur` : Gère les pixels en couleur (avec des composantes Rouge, Vert, Bleu).
   - `PixelNiveauDeGris` : Gère les pixels en niveaux de gris (une seule composante).

### Implémentation de `Image2` :
La classe `Image2` utilise des pointeurs polymorphes vers des objets `Pixel`. Chaque pixel peut être soit un `PixelCouleur`, soit un `PixelNiveauDeGris`, et est alloué dynamiquement.

### Code de base :

```cpp
#include <iostream>
#include <vector>

// Classe de base Pixel
class Pixel {
public:
    virtual ~Pixel() = default;
    virtual void afficher() const = 0;  // Méthode virtuelle pure
};

// Pixel couleur
class PixelCouleur : public Pixel {
private:
    unsigned char r, g, b;

public:
    PixelCouleur(unsigned char red, unsigned char green, unsigned char blue)
        : r(red), g(green), b(blue) {}

    void afficher() const override {
        std::cout << "Pixel couleur (R=" << (int)r << ", G=" << (int)g << ", B=" << (int)b << ")
";
    }
};

// Pixel niveau de gris
class PixelNiveauDeGris : public Pixel {
private:
    unsigned char niveau;

public:
    PixelNiveauDeGris(unsigned char n) : niveau(n) {}

    void afficher() const override {
        std::cout << "Pixel niveau de gris (" << (int)niveau << ")
";
    }
};

// Classe Image2 avec des pixels polymorphes
class Image2 {
private:
    int width, height;
    std::vector<Pixel*> pixels;

public:
    Image2(int w, int h, bool couleur = true) : width(w), height(h) {
        pixels.resize(width * height);
        for (int i = 0; i < width * height; ++i) {
            if (couleur) {
                pixels[i] = new PixelCouleur(255, 0, 0);  // Initialiser avec des pixels rouges
            } else {
                pixels[i] = new PixelNiveauDeGris(128);  // Initialiser avec des niveaux de gris
            }
        }
    }

    ~Image2() {
        for (Pixel* pixel : pixels) {
            delete pixel;
        }
    }

    void afficher() const {
        for (const Pixel* pixel : pixels) {
            pixel->afficher();
        }
    }
};

int main() {
    // Image avec des pixels en couleur
    Image2 imageCouleur(2, 2, true);
    imageCouleur.afficher();

    // Image avec des pixels en niveau de gris
    Image2 imageGris(2, 2, false);
    imageGris.afficher();

    return 0;
}
```

### Résultat attendu :
- **Image de pixels en couleur** : L'image affiche des pixels en couleur rouge.
- **Image de pixels en niveaux de gris** : L'image affiche des pixels avec des niveaux de gris.

### Discussion sur le surcoût mémoire et en temps d'exécution :
- **Mémoire** : Dans la version `Image2`, chaque pixel est alloué individuellement sur le tas (heap) via des pointeurs. Cela entraîne un surcoût en termes de gestion mémoire, en particulier à cause de la fragmentation.
- **Temps d'exécution** : L'utilisation de pointeurs et du polymorphisme introduit un surcoût en temps d'exécution, car chaque appel à `afficher()` nécessite une résolution dynamique via un pointeur virtuel (table des méthodes virtuelles).

### Comparaison avec Java :
- La version `Image2` en C++ est similaire à ce que fait Java par défaut (tout objet est accédé via une référence/pointeur).
- **C++ reste compétitif** en termes de performance lorsqu'on utilise une gestion manuelle et optimisée de la mémoire (comme dans la première version `Image` avec des pixels contigus).
- En revanche, **Java simplifie la gestion de la mémoire** grâce au garbage collector, mais introduit un surcoût lors de la collecte des objets.

---

