#include <iostream>
#include <stdexcept>

template <typename T, std::size_t AGRANDISSEMENT = 10>
class Tableau {
private:
    T* elements;        // Pointeur vers le tableau dynamique
    std::size_t taille;  // Nombre d'éléments insérés dans le tableau
    std::size_t capacite; // Capacité actuelle du tableau
    static int compteur;  // Compteur d'instances de tableau

    // Fonction privée pour agrandir la capacité du tableau
    void agrandir() {
        std::size_t nouvelle_capacite = capacite + AGRANDISSEMENT;
        T* nouveaux_elements = new T[nouvelle_capacite];

        for (std::size_t i = 0; i < taille; ++i) {
            nouveaux_elements[i] = elements[i];  // Copier les anciens éléments
        }

        delete[] elements;  // Libérer l'ancienne mémoire
        elements = nouveaux_elements;
        capacite = nouvelle_capacite;
    }

public:
    // Constructeur par défaut
    Tableau() : taille(0), capacite(AGRANDISSEMENT) {
        elements = new T[capacite];
        ++compteur;
    }

    // Constructeur à partir d'un tableau classique
    Tableau(T* tableau, std::size_t n) : taille(n), capacite(n + AGRANDISSEMENT) {
        elements = new T[capacite];
        for (std::size_t i = 0; i < n; ++i) {
            elements[i] = tableau[i];
        }
        ++compteur;
    }

    // Constructeur par copie
    Tableau(const Tableau& autre) : taille(autre.taille), capacite(autre.capacite) {
        elements = new T[capacite];
        for (std::size_t i = 0; i < taille; ++i) {
            elements[i] = autre.elements[i];
        }
        ++compteur;
    }

    // Opérateur d'affectation
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

    // Destructeur
    ~Tableau() {
        delete[] elements;
        --compteur;
    }

    // Ajouter un élément à la fin du tableau
    void ajoute(const T& element) {
        if (taille == capacite) {
            agrandir();
        }
        elements[taille++] = element;
    }

    // Opérateur [] pour accéder aux éléments
    T& operator[](std::size_t index) {
        if (index >= taille) {
            throw std::out_of_range("Index hors limite");
        }
        return elements[index];
    }

    // Fonction pour obtenir la taille actuelle
    std::size_t tailleActuelle() const {
        return taille;
    }

    std::size_t capacitéActuelle() const {
        return capacite;
    }

    // Fonction pour obtenir le nombre d'instances de tableau
    static int getCompteur() {
        return compteur;
    }

    // Affichage du contenu du tableau
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

// Test des méthodes
int main() {
    Tableau<int> t;

    // Ajout d'éléments
    for (int i = 0; i < 20; ++i) {
        t.ajoute(i);
    }

    // Affichage du tableau
    std::cout << "Tableau: " << t << std::endl;

    // Test de l'accès via []
    std::cout << "Element à l'indice 5: " << t[5] << std::endl;

    // Test d'un rajout apres capacité atteinte
    std::cout << "Capacité actuelle: " << t.capacitéActuelle() << std::endl;
    t.ajoute(21);
    std::cout << "Capacité après rajout d'une unité: " << t.capacitéActuelle() << std::endl;

    // Test du constructeur par copie
    Tableau<int> t2 = t;
    std::cout << "Tableau copié: " << t2 << std::endl;

    // Affichage du nombre d'instances
    std::cout << "Nombre d'instances: " << Tableau<int>::getCompteur() << std::endl;

    return 0;
}
