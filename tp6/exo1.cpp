#include <iostream>
#include <deque>
#include <set>
#include <list>
#include <algorithm>
#include <iterator>
#include <numeric>

// Générateur de multiples
int generateMultiple(int base, int multiplier) {
    return base * multiplier;
}

int main() {
    // 1. Construisez un deque d de 5 entiers
    std::deque<int> d(5);

    // 2. Remplissez d avec des multiples de 4
    std::generate(d.begin(), d.end(), [n = 0]() mutable { return generateMultiple(++n, 4); });

    // 3. Affichez le contenu de d sur la sortie standard
    std::copy(d.begin(), d.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    // 4. Construisez un ensemble s1 d'entiers à partir de d
    std::set<int> s1(d.begin(), d.end());

    // 5. Videz d de son contenu
    d.clear();

    // 6. Construisez un ensemble s2 d'entiers par insertion successive de 10 multiples de 2
    std::set<int> s2;
    for (int i = 0; i < 10; ++i) {
        s2.insert(i * 2);
    }

    // 7. Construisez un ensemble vide s3
    std::set<int> s3;

    // 8. Remplissez s3 avec 6 multiples de 3
    std::generate_n(std::inserter(s3, s3.begin()), 6, [n = 0]() mutable { return (n++) * 3; });

    // 9. Affichez le contenu des ensembles s1, s2 et s3 en séparant les éléments par des "; "
    auto print_set = [](const std::set<int>& s) {
        std::copy(s.begin(), s.end(), std::ostream_iterator<int>(std::cout, "; "));
        std::cout << std::endl;
    };
    print_set(s1);
    print_set(s2);
    print_set(s3);

    // 10. Rangez le résultat de l'intersection de s1 et de s2 dans une liste l d'entiers
    std::list<int> l;
    std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), std::back_inserter(l));

    // 11. Affichez le contenu de l
    std::copy(l.begin(), l.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    // 12. Affichez directement le résultat de l'union des ensembles s1 et s3
    std::set<int> union_s1_s3;
    std::set_union(s1.begin(), s1.end(), s3.begin(), s3.end(), std::inserter(union_s1_s3, union_s1_s3.begin()));
    std::copy(union_s1_s3.begin(), union_s1_s3.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    return 0;
}
