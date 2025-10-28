#include <iostream>
#include <stdexcept>

template <typename T, std::size_t AGRANDISSEMENT = 10>
class Tableau {
private:
    T* elements;
    std::size_t taille;
    std::size_t capacite;
    static int compteur;

    void agrandir() {
        std::size_t nouvelle_capacite = capacite + AGRANDISSEMENT;
        T* nouveaux_elements = new T[nouvelle_capacite];
        for (std::size_t i = 0; i < taille; ++i) {
            nouveaux_elements[i] = elements[i];
        }
        delete[] elements;
        elements = nouveaux_elements;
        capacite = nouvelle_capacite;
    }

public:
    // Définition des classes iterator et oddIterator dans Tableau
    class iterator {
    private:
        T* courant;  // Pointeur vers l'élément actuel

    public:
        iterator(T* element) : courant(element) {}

        T& operator*() const {
            return *courant;
        }

        iterator& operator++() {
            ++courant;
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++courant;
            return temp;
        }

        bool operator==(const iterator& autre) const {
            return courant == autre.courant;
        }

        bool operator!=(const iterator& autre) const {
            return courant != autre.courant;
        }
    };

    class oddIterator {
    private:
        T* courant;  // Pointeur vers l'élément actuel
        std::size_t index; // Index courant pour garder la trace des positions impaires

    public:
        // Constructeur d'oddIterator : initialise l'index à une position paire
        oddIterator(T* element, std::size_t startIndex) : courant(element), index(startIndex) {
            if (index % 2 != 0) {  // Si on commence sur un index impair, on saute un élément
                ++courant;
                ++index;
            }
        }

        // Déréférencement
        T& operator*() const {
            return *courant;
        }

        // Incrémentation (pré-incrémentation), on saute un élément après chaque accès
        oddIterator& operator++() {
            courant += 2; // Saute un élément
            index += 2;
            return *this;
        }

        // Incrémentation (post-incrémentation)
        oddIterator operator++(int) {
            oddIterator temp = *this;
            courant += 2;
            index += 2;
            return temp;
        }

        // Test d'égalité
        bool operator==(const oddIterator& autre) const {
            return courant == autre.courant;
        }

        // Test de différence
        bool operator!=(const oddIterator& autre) const {
            return courant != autre.courant;
        }
    };

    Tableau() : taille(0), capacite(AGRANDISSEMENT) {
        elements = new T[capacite];
        ++compteur;
    }

    Tableau(T* tableau, std::size_t n) : taille(n), capacite(n + AGRANDISSEMENT) {
        elements = new T[capacite];
        for (std::size_t i = 0; i < n; ++i) {
            elements[i] = tableau[i];
        }
        ++compteur;
    }

    Tableau(const Tableau& autre) : taille(autre.taille), capacite(autre.capacite) {
        elements = new T[capacite];
        for (std::size_t i = 0; i < taille; ++i) {
            elements[i] = autre.elements[i];
        }
        ++compteur;
    }

    Tableau& operator=(const Tableau& autre) {
        if (this != &autre) {
            delete[] elements;
            taille = autre.taille;
            capacite = autre.capacite;
            elements = new T[capacite];
            for (std::size_t i = 0; i < taille; ++i) {
                elements[i] = autre.elements[i];
            }
        }
        return *this;
    }

    ~Tableau() {
        delete[] elements;
        --compteur;
    }

    void ajoute(const T& element) {
        if (taille == capacite) {
            agrandir();
        }
        elements[taille++] = element;
    }

    T& operator[](std::size_t index) {
        if (index >= taille) {
            throw std::out_of_range("Index hors limite");
        }
        return elements[index];
    }

    std::size_t tailleActuelle() const {
        return taille;
    }

    std::size_t capacitéActuelle() const {
        return capacite;
    }

    static int getCompteur() {
        return compteur;
    }

    iterator begin() {
        return iterator(elements);
    }

    iterator end() {
        return iterator(elements + taille);
    }

    // Retourne un oddIterator qui commence à l'index 0
    oddIterator oddBegin() {
        return oddIterator(elements, 0);
    }

    // Retourne un oddIterator qui pointe après le dernier élément
    oddIterator oddEnd() {
        return oddIterator(elements + taille, taille);
    }

    friend std::ostream& operator<<(std::ostream& os, const Tableau& tableau) {
        for (std::size_t i = 0; i < tableau.taille; ++i) {
            os << tableau.elements[i] << " ";
        }
        return os;
    }
};

// Initialisation du compteur
template <typename T, std::size_t AGRANDISSEMENT>
int Tableau<T, AGRANDISSEMENT>::compteur = 0;

// Test des méthodes et de l'itérateur
int main() {
    Tableau<int, 6> A;

    // Ajout d'éléments
    for (int i = 0; i < 10; ++i) {
        A.ajoute(i);
    }

    // Test des itérateurs normaux
    Tableau<int, 6>::iterator it = A.begin();
    Tableau<int, 6>::iterator ite = A.end();
    std::cout << "Tous les éléments du tableau : " << std::endl;
    for (; it != ite; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Test des oddIterator pour indices pairs
    Tableau<int, 6>::oddIterator oddIt = A.oddBegin();
    Tableau<int, 6>::oddIterator oddIte = A.oddEnd();
    std::cout << "Éléments aux indices pairs : " << std::endl;
    for (; oddIt != oddIte; ++oddIt) {
        std::cout << *oddIt << " ";
    }
    std::cout << std::endl;

    return 0;
}
