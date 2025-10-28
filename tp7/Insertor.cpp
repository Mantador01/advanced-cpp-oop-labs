#include <iostream>
#include <stdexcept>

// Définition de la classe Insertor
template <typename Container>
class Insertor {
private:
    Container& conteneur;

public:
    Insertor(Container& c) : conteneur(c) {}

    // Le déréférencement ne retourne pas un élément du conteneur
    Insertor& operator*() {
        return *this;
    }

    // L'opérateur d'incrémentation ne fait rien car l'insertion est toujours à la fin
    Insertor& operator++() {
        return *this;
    }

    Insertor operator++(int) {
        return *this;
    }

    // L'opérateur d'affectation insère l'élément à la fin du conteneur
    Insertor& operator=(const typename Container::value_type& value) {
        conteneur.ajoute(value);
        return *this;
    }
};

// Classe Tableau donnée
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
    using value_type = T;  // Définir un alias pour le type de valeur (utile pour Insertor)

    Tableau() : taille(0), capacite(AGRANDISSEMENT) {
        elements = new T[capacite];
        ++compteur;
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

    std::size_t tailleActuelle() const {
        return taille;
    }

    std::size_t capacitéActuelle() const {
        return capacite;
    }

    T& operator[](std::size_t index) {
        if (index >= taille) {
            throw std::out_of_range("Index hors limite");
        }
        return elements[index];
    }

    // Retourner un Insertor pour ce conteneur
    Insertor<Tableau> insertor() {
        return Insertor<Tableau>(*this);
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

// Test de l'Insertor
int main() {
    Tableau<int, 6> A;

    // Utilisation de l'Insertor
    Insertor<Tableau<int, 6>> ins = A.insertor();
    for (int i = 0; i < 10; ++i) {
        *ins = i;  // Utilisation de l'Insertor pour ajouter des éléments
    }

    // Afficher les éléments du tableau
    std::cout << "Éléments du tableau : " << A << std::endl;

    return 0;
}
