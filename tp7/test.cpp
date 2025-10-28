#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>  // Pour std::copy
#include <iterator>   // Pour std::back_insert_iterator

// Définition de la classe Insertor
template <typename Container>
class Insertor {
private:
    Container& conteneur;  // Référence au conteneur dans lequel les éléments seront insérés

public:
    // Constructeur qui initialise la référence au conteneur
    Insertor(Container& c) : conteneur(c) {}

    // Le déréférencement ne retourne pas un élément du conteneur
    const Insertor& operator*() const {
        return *this;
    }

    // L'opérateur d'incrémentation préfixé ne fait rien car l'insertion est toujours à la fin
    const Insertor& operator++() const {
        return *this;
    }

    // L'opérateur d'incrémentation postfixé retourne une copie de l'itérateur avant l'incrémentation
    Insertor operator++(int) const {
        Insertor temp = *this;
        return temp;
    }

    // L'opérateur d'affectation insère l'élément à la fin du conteneur
    Insertor& operator=(const typename Container::value_type& value) {
        try {
            conteneur.ajoute(value);
        } catch (const std::exception& e) {
            std::cerr << "Erreur lors de l'insertion : " << e.what() << std::endl;
            throw;
        }
        return *this;
    }
};

// Classe Tableau donnée
template <typename T, std::size_t AGRANDISSEMENT = 10>
class Tableau {
private:
    T* elements;  // Pointeur vers le tableau dynamique contenant les éléments
    std::size_t taille;  // Nombre d'éléments actuellement dans le tableau
    std::size_t capacite;  // Capacité actuelle du tableau
    static int compteur;  // Compteur statique pour suivre le nombre d'instances

    // Méthode pour agrandir la capacité du tableau
    void agrandir() {
        std::size_t nouvelle_capacite = capacite + AGRANDISSEMENT;  // Nouvelle capacité après agrandissement
        T* nouveaux_elements = new T[nouvelle_capacite];  // Allocation d'un nouveau tableau avec la nouvelle capacité
        for (std::size_t i = 0; i < taille; ++i) {
            nouveaux_elements[i] = elements[i];  // Copie des éléments existants dans le nouveau tableau
        }
        delete[] elements;  // Libération de l'ancien tableau
        elements = nouveaux_elements;  // Mise à jour du pointeur vers le nouveau tableau
        capacite = nouvelle_capacite;  // Mise à jour de la capacité
    }

public:
    using value_type = T;  // Définir un alias pour le type de valeur (utile pour Insertor)

    // Constructeur par défaut qui initialise le tableau avec une capacité initiale
    Tableau() : taille(0), capacite(AGRANDISSEMENT) {
        elements = new T[capacite];  // Allocation du tableau dynamique avec la capacité initiale
    }

    // Constructeur par copie
    Tableau(const Tableau& autre) : taille(autre.taille), capacite(autre.capacite) {
        elements = new T[capacite];
        for (std::size_t i = 0; i < taille; ++i) {
            elements[i] = autre.elements[i];
        }
    }

    // Opérateur d'affectation par copie
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
    }

    // Méthode pour ajouter un élément à la fin du tableau
    void ajoute(const T& valeur) {
        if (taille == capacite) {
            agrandir();  // Agrandir le tableau si la capacité est atteinte
        }
        elements[taille++] = valeur;  // Ajouter l'élément et incrémenter la taille
    }

    // Méthode pour retourner un Insertor
    Insertor<Tableau> insertor() {
        return Insertor<Tableau>(*this);
    }

    // Méthode pour retourner la taille actuelle du tableau
    std::size_t size() const {
        return taille;
    }

    // Surcharge de l'opérateur [] pour accéder aux éléments
    T& operator[](std::size_t index) {
        if (index >= taille) {
            throw std::out_of_range("Index hors limite");
        }
        return elements[index];
    }

    const T& operator[](std::size_t index) const {
        if (index >= taille) {
            throw std::out_of_range("Index hors limite");
        }
        return elements[index];
    }

    // Surcharge de l'opérateur << pour afficher les éléments du tableau
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

// Test de l'Insertor avec un Tableau de vecteurs
int main() {
    Tableau<int, 6> A;

    // Utilisation de l'Insertor
    Insertor<Tableau<int, 6>> ins = A.insertor();
    for (int i = 0; i < 10; ++i) {
        *ins = i;  // Utilisation de l'Insertor pour ajouter des éléments
    }

    // Afficher les éléments du tableau
    std::cout << "Éléments du tableau A : " << A << std::endl;

    // Créer une copie du tableau A
    Tableau<int, 6> A_copy = A;

    // Afficher les éléments du tableau copié
    std::cout << "Éléments du tableau A_copy : " << A_copy << std::endl;

    // Test avec un Tableau de vecteurs
    Tableau<std::vector<int>, 3> B;

    // Utilisation de l'Insertor pour le Tableau de vecteurs
    Insertor<Tableau<std::vector<int>, 3>> insVec = B.insertor();
    for (int i = 0; i < 5; ++i) {
        std::vector<int> vec = {i, i+1, i+2};  // Créer un vecteur d'exemple
        *insVec = vec;  // Utilisation de l'Insertor pour ajouter des vecteurs
    }

    // Afficher les éléments du tableau de vecteurs
    std::cout << "Éléments du tableau de vecteurs B : " << std::endl;
    for (std::size_t i = 0; i < B.size(); ++i) {
        std::cout << "Vecteur " << i << ": ";
        for (int val : B[i]) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    // Créer une copie du tableau de vecteurs B
    Tableau<std::vector<int>, 3> B_copy = B;

    // Afficher les éléments du tableau de vecteurs copié
    std::cout << "Éléments du tableau de vecteurs B_copy : " << std::endl;
    for (std::size_t i = 0; i < B_copy.size(); ++i) {
        std::cout << "Vecteur " << i << ": ";
        for (int val : B_copy[i]) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    // Utilisation de std::copy avec std::back_insert_iterator
    std::vector<int> vec_source = {10, 20, 30, 40, 50};
    std::vector<int> vec_dest;

    std::copy(vec_source.begin(), vec_source.end(), std::back_inserter(vec_dest));

    // Afficher les éléments du vecteur destination
    std::cout << "Éléments du vecteur destination après std::copy : ";
    for (int val : vec_dest) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}