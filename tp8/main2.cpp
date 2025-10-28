#include <iostream>
#include <type_traits>

// Définition de la classe Tuple
template <typename... Types>
class Tuple;

template <>
class Tuple<> {};

template <typename Head, typename... Tail>
class Tuple<Head, Tail...> {
public:
    Tuple() = default;

    Tuple(Head head, Tail... tail) : head_(head), tail_(tail...) {}

    Head head_;
    Tuple<Tail...> tail_;
};

// Longueur d'une liste de types
template <typename... Types>
struct Length;

template <>
struct Length<> {
    static constexpr std::size_t value = 0;
};

template <typename Head, typename... Tail>
struct Length<Head, Tail...> {
    static constexpr std::size_t value = 1 + Length<Tail...>::value;
};

// Type en ième position
template <std::size_t index, typename... Types>
struct TypeAt;

template <typename Head, typename... Tail>
struct TypeAt<0, Head, Tail...> {
    using type = Head;
};

template <std::size_t index, typename Head, typename... Tail>
struct TypeAt<index, Head, Tail...> {
    using type = typename TypeAt<index - 1, Tail...>::type;
};

// Recherche d'un type dans une liste de types
template <typename T, typename... Types>
struct IndexOf;

template <typename T>
struct IndexOf<T> {
    static constexpr int value = -1; // Type non trouvé
};

template <typename T, typename... Tail>
struct IndexOf<T, T, Tail...> {
    static constexpr int value = 0;
};

template <typename T, typename Head, typename... Tail>
struct IndexOf<T, Head, Tail...> {
private:
    static constexpr int temp = IndexOf<T, Tail...>::value;
public:
    static constexpr int value = temp == -1 ? -1 : 1 + temp;
};

// Fonction get pour accéder aux éléments du Tuple
template <std::size_t index, typename... Types>
auto& get(Tuple<Types...>& tuple) {
    if constexpr (index == 0) {
        return tuple.head_;
    } else {
        return get<index - 1>(tuple.tail_);
    }
}

// Exemple d'utilisation
int main() {
    Tuple<char, int, double> t('a', 42, 3.14);

    // Longueur du Tuple
    std::cout << "Length: " << Length<char, int, double>::value << std::endl;

    // Type en ième position
    using Type = TypeAt<1, char, int, double>::type;
    std::cout << "Type at index 1: " << typeid(Type).name() << std::endl;

    // Recherche d'un type dans le Tuple
    std::cout << "Index of int: " << IndexOf<int, char, int, double>::value << std::endl;
    std::cout << "Index of float: " << IndexOf<float, char, int, double>::value << std::endl;

    // Accès et modification d'un élément du Tuple
    get<2>(t) = 2.71828;
    std::cout << "Value at index 2: " << get<2>(t) << std::endl;

    return 0;
}