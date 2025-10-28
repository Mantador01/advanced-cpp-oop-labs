#include <iostream>
#include <cstring> // pour strcmp

// Fonction template d'échange de deux éléments
template <typename T>
void mySwap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// Fonction template qui retourne le minimum de deux éléments
template <typename T>
T myMin(const T& a, const T& b) {
    return (a < b) ? a : b;
}

// Spécialisation de la fonction myMin pour les chaînes de caractères (comparaison lexicographique)
template <>
const char* myMin(const char* const& a, const char* const& b) {
    return (strcmp(a, b) < 0) ? a : b;
}

// Surcharge de la fonction myMin pour les tableaux statiques de même taille
template <std::size_t I>
const char* myMin(const  char(&a)[I], const char(&b)[I]) {
    return (strcmp(a, b) < 0) ? a : b;
}

// Surcharge de la fonction myMin pour les tableaux statiques de tailles différentes
template <std::size_t I, std::size_t J>
const char* myMin(const char(&a)[I], const char(&b)[J]) {
    return (strcmp(a, b) < 0) ? a : b;
}

int main() {
    // Test de la fonction myMin avec des entiers
    std::cout << "Min(5, 6): " << myMin(5, 6) << std::endl;
    std::cout << "Min(6, 5): " << myMin(6, 5) << std::endl;

    // Test de la fonction myMin avec des chaînes littérales
    std::cout << "Min(\"lili\", \"lala\"): " << myMin("lili", "lala") << std::endl;
    std::cout << "Min(\"li\", \"lala\"): " << myMin("li", "lala") << std::endl;

    // Test de la fonction myMin avec des pointeurs de chaînes
    const char *cc = "mumu";
    const char *dd = "ma";
    std::cout << "Min(cc, dd): " << myMin(cc, dd) << std::endl;

    // Test de la fonction myMin avec des tableaux statiques de même taille
    char ee[5] = "toto";
    char ff[5] = "ta";
    std::cout << "Min(ee, ff): " << myMin(ee, ff) << std::endl;

    // Test de la fonction myMin avec un tableau statique et une chaîne littérale
    std::cout << "Min(\"zut\", ff): " << myMin("zut", ff) << std::endl;

    return 0;
}
