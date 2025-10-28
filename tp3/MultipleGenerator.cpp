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
    // Exemple d'utilisation avec un générateur de multiples de 5
    MultipleGenerator gen5(5);

    // Affichage des 5 premiers multiples de 5
    for (int i = 0; i < 5; ++i) {
        std::cout << gen5() << std::endl;  // Appel de l'opérateur () sur l'objet
    }

    // Exemple d'utilisation avec un générateur de multiples de 3
    MultipleGenerator gen3(3);
    for (int i = 0; i < 5; ++i) {
        std::cout << gen3() << std::endl;  // Appel de l'opérateur () sur l'objet
    }

    return 0;
}
