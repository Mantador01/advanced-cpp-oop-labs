// #include <tuple>
#include <iostream>

template <typename T1, typename TL>
struct TypeList {
    using Head = T1;
    using Tail = TL;
};

struct NullType {};




template <typename TL>
struct Length;

template <typename T1, typename TL>
struct Length<TypeList<T1, TL>> {
    static constexpr int value = 1 + Length<TL>::value;
};

template <>
struct Length<NullType> {
    static constexpr int value = 0;
};


/// ----> ici on fait la meme chose mais avec des templates variadiques

template <typename ... T1>
class length2;

template<typename T1, typename ... Rest>
class length2<T1, Rest...> {
    static constexpr int value = 1 + Length<length2<Rest...>>::value;
};

template<>
class length2<> {
    static constexpr int value = 0;
};

template <typename T1>
class length2<T1> {
    static constexpr int value = 1;
};

/// Donc on au lieu de faire type <T1, type <T2, type <T3, type <T4, NullType>>>>> on peut faire type <T1, T2, T3, T4>


template <typename TL, int index>
struct TypeAt;

template <typename T1, typename TL>
struct TypeAt<TypeList<T1, TL>, 0> {
    using type = T1;
};

template <typename T1, typename TL, int index>
struct TypeAt<TypeList<T1, TL>, index> {
    using type = typename TypeAt<TL, index - 1>::type;
};




template <typename TL, typename T>
struct IndexOf;

template <typename T>
struct IndexOf<NullType, T> {
    static constexpr int value = -1;
};

template <typename T1, typename TL>
struct IndexOf<TypeList<T1, TL>, T1> {
    static constexpr int value = 0;
};

template <typename T1, typename TL, typename T>
struct IndexOf<TypeList<T1, TL>, T> {
private:
    static constexpr int temp = IndexOf<TL, T>::value;

public:
    static constexpr int value = (temp == -1 ? -1 : 1 + temp);
};

// template <typename... Types>
//     class Tuple;

//     template <>
//     class Tuple<> {};

//     template <typename Head, typename... Tail>
//     class Tuple<Head, Tail...> {
//     public:
//         Tuple() = default;

//         Tuple(Head head, Tail... tail) : head_(head), tail_(tail...) {}

//         Head head_;
//         Tuple<Tail...> tail_;
//     };

//     template <std::size_t index, typename TupleType>
//     struct TupleElement;

//     template <typename Head, typename... Tail>
//     struct TupleElement<0, Tuple<Head, Tail...>> {
//         using type = Head;
//     };

//     template <std::size_t index, typename Head, typename... Tail>
//     struct TupleElement<index, Tuple<Head, Tail...>> {
//         using type = typename TupleElement<index - 1, Tuple<Tail...>>::type;
//     };

//     template <std::size_t index, typename... Types>
//     typename TupleElement<index, Tuple<Types...>>::type& get(Tuple<Types...>& tuple) {
//         if constexpr (index == 0) {
//             return tuple.head_;
//         } else {
//             return get<index - 1>(tuple.tail_);
//         }
//     }

// auto ou decltype 

#include <iostream>

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

template <std::size_t index, typename TupleType>
struct TupleElement;

template <typename Head, typename... Tail>
struct TupleElement<0, Tuple<Head, Tail...>> {
    using type = Head;
};

template <std::size_t index, typename Head, typename... Tail>
struct TupleElement<index, Tuple<Head, Tail...>> {
    using type = typename TupleElement<index - 1, Tuple<Tail...>>::type;
};

template <std::size_t index, typename... Types>
auto& get(Tuple<Types...>& tuple) {
    if constexpr (index == 0) {
        return tuple.head_;
    } else {
        return get<index - 1>(tuple.tail_);
    }
}





int main() {
    Tuple<char, int, double> t('a', 42, 3.14);
    get<2>(t) = 2.71828;
    
    std::cout << get<2>(t) << std::endl;
    return 0;
}
