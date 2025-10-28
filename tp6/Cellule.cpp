#include <iostream>
#include <stdexcept>

// Classe Cellule : représente un élément de la liste
template <typename T>
class Cellule {
public:
    T valeur;           // Valeur de la cellule
    Cellule* suivante;  // Pointeur vers la cellule suivante

    // Constructeur
    Cellule(const T& val, Cellule* suiv = nullptr) : valeur(val), suivante(suiv) {}
};

// Classe ListeTriee : représente la liste triée chaînée
template <typename T>
class ListeTriee {
private:
    Cellule<T>* tete;  // Pointeur vers la première cellule
    Cellule<T>* queue; // Pointeur vers la dernière cellule

    // Méthode privée pour copier une liste
    void copier(const ListeTriee& autre) {
        if (autre.tete == nullptr) {
            tete = queue = nullptr;
        } else {
            tete = new Cellule<T>(autre.tete->valeur);
            Cellule<T>* courant = tete;
            Cellule<T>* autreCourant = autre.tete->suivante;
            while (autreCourant != nullptr) {
                courant->suivante = new Cellule<T>(autreCourant->valeur);
                courant = courant->suivante;
                autreCourant = autreCourant->suivante;
            }
            queue = courant;
        }
    }

public:
    // Constructeur par défaut : crée une liste vide
    ListeTriee() : tete(nullptr), queue(nullptr) {}

    // Constructeur par copie
    ListeTriee(const ListeTriee& autre) {
        copier(autre);
    }

    // Opérateur d'affectation (copie)
    ListeTriee& operator=(const ListeTriee& autre) {
        if (this != &autre) {
            vider(); // Vider la liste actuelle
            copier(autre); // Copier l'autre liste
        }
        return *this;
    }

    // Destructeur : libère la mémoire allouée
    ~ListeTriee() {
        vider();
    }

    // Méthode pour vider la liste (utilisée dans le destructeur)
    void vider() {
        Cellule<T>* courant = tete;
        while (courant != nullptr) {
            Cellule<T>* temp = courant;
            courant = courant->suivante;
            delete temp;
        }
        tete = queue = nullptr;
    }

    // Méthode pour ajouter un élément dans la liste triée
    void ajouter(const T& val) {
        Cellule<T>* nouvelleCellule = new Cellule<T>(val);
        // Si la liste est vide
        if (tete == nullptr) {
            tete = queue = nouvelleCellule;
        } else if (val < tete->valeur) {
            // Insertion en tête
            nouvelleCellule->suivante = tete;
            tete = nouvelleCellule;
        } else {
            // Insertion dans l'ordre
            Cellule<T>* courant = tete;
            Cellule<T>* precedent = nullptr;
            while (courant != nullptr && courant->valeur < val) {
                precedent = courant;
                courant = courant->suivante;
            }
            nouvelleCellule->suivante = courant;
            if (precedent != nullptr) {
                precedent->suivante = nouvelleCellule;
            }
            if (courant == nullptr) {
                queue = nouvelleCellule; // Mise à jour de la queue si ajouté en fin
            }
        }
    }

    // Méthode pour afficher la liste
    void afficher() const {
        Cellule<T>* courant = tete;
        while (courant != nullptr) {
            std::cout << courant->valeur << " ";
            courant = courant->suivante;
        }
        std::cout << std::endl;
    }
};

int main() {
    // Création d'une liste triée d'entiers
    ListeTriee<int> liste;

    // Ajout d'éléments
    liste.ajouter(5);
    liste.ajouter(2);
    liste.ajouter(8);
    liste.ajouter(3);

    // Affichage de la liste
    std::cout << "Liste triée : ";
    liste.afficher();

    // Test du constructeur par copie
    ListeTriee<int> copieListe = liste;
    std::cout << "Liste copiée : ";
    copieListe.afficher();

    // Test de l'opérateur d'affectation
    ListeTriee<int> autreListe;
    autreListe = liste;
    std::cout << "Liste après affectation : ";
    autreListe.afficher();

    return 0;
}
 