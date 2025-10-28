
# TP2 : Capsules RAII, Construction et Affectation par Déplacement

## Objectif

L'objectif de cet exercice est de modifier la classe `LaClasse` pour qu'elle suive le principe de **RAII** (Resource Acquisition Is Initialization), et d'ajouter un **constructeur par déplacement** ainsi qu'un **opérateur d'affectation par déplacement**.

Nous allons gérer une ressource allouée dynamiquement (un tableau d'entiers) et assurer que cette ressource soit libérée automatiquement lorsque l'objet est détruit. Cela garantit qu'aucune fuite de mémoire ne se produit et que l'efficacité du programme est maintenue grâce aux déplacements.

## Principe RAII

Le principe de **RAII** implique que l'acquisition d'une ressource doit se faire lors de l'initialisation de l'objet (dans le constructeur), et sa libération doit se faire lors de la destruction de l'objet (dans le destructeur).

Cela permet de garantir que les ressources allouées dans le tas (comme de la mémoire dynamique) sont automatiquement libérées lorsque l'objet qui les possède est détruit.

## Code

Voici le code modifié de la classe `LaClasse` :

```cpp
#include <iostream>

class LaClasse {
private:
    int* data;  // Pointeur vers une ressource (par exemple, un tableau d'entiers)
    size_t size;

public:
    // Constructeur par défaut
    LaClasse() : data(nullptr), size(0) {
        std::cout << "LaClasse::LaClasse() - Default Constructor\n";
    }

    // Constructeur avec taille
    LaClasse(size_t s) : size(s) {
        data = new int[size];  // Allocation dynamique
        std::cout << "LaClasse::LaClasse(size_t) - Constructor with size\n";
    }

    // Constructeur de copie
    LaClasse(const LaClasse& other) : size(other.size) {
        if (other.data) {
            data = new int[size];  // Allouer un nouvel espace
            std::copy(other.data, other.data + size, data);  // Copier les données
        } else {
            data = nullptr;
        }
        std::cout << "LaClasse::LaClasse(const LaClasse&) - Copy Constructor\n";
    }

    // Constructeur par déplacement (Move constructor)
    LaClasse(LaClasse&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;  // L'autre objet ne doit plus pointer sur la ressource
        other.size = 0;
        std::cout << "LaClasse::LaClasse(LaClasse&&) - Move Constructor\n";
    }

    // Opérateur d'affectation par déplacement (Move assignment operator)
    LaClasse& operator=(LaClasse&& other) noexcept {
        if (this != &other) {  // Auto-affectation
            delete[] data;  // Libérer les ressources actuelles

            data = other.data;
            size = other.size;

            other.data = nullptr;
            other.size = 0;

            std::cout << "LaClasse::operator=(LaClasse&&) - Move Assignment Operator\n";
        }
        return *this;
    }

    // Destructeur
    ~LaClasse() {
        delete[] data;  // Libérer la mémoire
        std::cout << "~LaClasse() - Destructor\n";
    }

    // Affichage de la taille de l'objet
    void print() const {
        std::cout << "LaClasse with size: " << size << std::endl;
    }
};

int main() {
    std::cout << "Creating object c1\n";
    LaClasse c1(10);  // Crée un objet avec un tableau de 10 entiers
    c1.print();
    std::cout << std::endl;

    std::cout << "Creating object c2 using move constructor\n";
    LaClasse c2 = std::move(c1);  // Utilise le constructeur par déplacement
    c2.print();
    std::cout << std::endl;

    std::cout << "Creating object c3 using move assignment\n";
    LaClasse c3;
    c3 = std::move(c2);  // Utilise l'opérateur d'affectation par déplacement
    c3.print();
    std::cout << std::endl;

    std::cout << "End of the program\n";
    return 0;
}
```

## Explications

### 1. **Constructeur par défaut** 
   - Initialise le pointeur `data` à `nullptr` et la taille à `0`.

### 2. **Constructeur avec taille** 
   - Alloue un tableau dynamique de taille `size` et initialise le pointeur `data`.

### 3. **Constructeur de copie** 
   - Effectue une copie profonde des données (il alloue un nouvel espace mémoire et copie les données de l'objet à copier).

### 4. **Constructeur par déplacement** 
   - Transfère la propriété de la ressource de l'objet source (`other`) vers l'objet courant. L'objet source est laissé dans un état sûr (`nullptr` pour éviter les double-free).

### 5. **Opérateur d'affectation par déplacement** 
   - Libère d'abord la ressource actuelle de l'objet (si nécessaire), puis transfère la propriété des ressources de l'objet source (`other`), tout en s'assurant que l'objet source est laissé dans un état sûr.

### 6. **Destructeur** 
   - Libère les ressources dynamiques (le tableau alloué dans le tas).

### Principe RAII
Le modèle RAII permet de gérer automatiquement les ressources, notamment celles allouées dynamiquement. Grâce au destructeur, les ressources sont toujours libérées lorsque l'objet sort du scope ou est détruit, évitant ainsi les fuites mémoire.

### Sortie du programme (exemple) :

```plaintext
Creating object c1
LaClasse::LaClasse(size_t) - Constructor with size
LaClasse with size: 10

Creating object c2 using move constructor
LaClasse::LaClasse(LaClasse&&) - Move Constructor
LaClasse with size: 10

Creating object c3 using move assignment
LaClasse::operator=(LaClasse&&) - Move Assignment Operator
LaClasse with size: 10

~LaClasse() - Destructor
~LaClasse() - Destructor
~LaClasse() - Destructor
End of the program
```

### Conclusion

Nous avons modifié la classe `LaClasse` pour qu'elle respecte le principe RAII et pour qu'elle gère efficacement les ressources dynamiques. Le constructeur par déplacement et l'opérateur d'affectation par déplacement permettent d'optimiser la gestion de ces ressources en évitant des copies inutiles.
