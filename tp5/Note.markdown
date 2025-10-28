# TP5 C++ Templates - Explications Complètes

## Qu'est-ce qu'une Fonction Template ?

Une fonction *template* est un concept en C++ qui permet de définir une fonction générique pouvant travailler avec des types différents sans avoir à dupliquer le code pour chaque type spécifique. Au lieu de définir des fonctions séparées pour chaque type (comme int, float, char, etc.), on utilise un *template* qui est instancié automatiquement par le compilateur en fonction du type des arguments fournis. Cela permet d'écrire un code plus flexible et réutilisable, réduisant ainsi la redondance et facilitant la maintenance.

Par exemple, une fonction template qui échange les valeurs de deux variables peut être définie comme suit :

```cpp
template <typename T>
void mySwap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}
```

Ici, `T` est un paramètre de type qui sera remplacé par le type approprié (int, float, etc.) lorsque la fonction est appelée.

## Introduction

Ce document contient les explications complètes pour l'exercice 1 du TP5 de Programmation avancée en C++. L'objectif principal de cet exercice est de travailler avec des fonctions *template* permettant de manipuler des types génériques en C++. Nous allons écrire des fonctions pour échanger des valeurs, trouver le minimum entre deux éléments de type quelconque, et étendre cette fonctionnalité pour d'autres types tels que des tableaux statiques.

## Code Complet

Voici le code complet implémentant les fonctions demandées :

```cpp
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
const char* myMin(const char(&a)[I], const char(&b)[I]) {
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
```

## Explications des Fonctions

### 1. Fonction `mySwap`

La fonction `mySwap` est une fonction template qui permet d'échanger deux variables de type quelconque. Voici le prototype :

```cpp
template <typename T>
void mySwap(T& a, T& b);
```
- **Paramètres** : Elle prend deux références `a` et `b` de type générique `T`.
- **Fonctionnement** : La fonction utilise une variable temporaire `temp` pour échanger les valeurs de `a` et `b`.
- **Utilisation** : Cette fonction peut être utilisée avec tout type compatible, comme les entiers, flottants, ou objets personnalisés.

### 2. Fonction `myMin`

La fonction `myMin` est un template qui retourne le minimum entre deux éléments de même type.

```cpp
template <typename T>
T myMin(const T& a, const T& b);
```
- **Paramètres** : Deux références constantes `a` et `b` de type `T`.
- **Fonctionnement** : Elle retourne le plus petit des deux éléments en utilisant l'opérateur `<`.
- **Avantage** : Les références constantes évitent les copies inutiles, ce qui améliore l'efficacité.

### 3. Spécialisation de `myMin` pour les Chaînes de Caractères

Pour les chaînes de caractères, une spécialisation de `myMin` est nécessaire car l'opérateur `<` ne peut pas être utilisé pour comparer directement des `const char*`.

```cpp
template <>
const char* myMin(const char* const& a, const char* const& b);
```
- **Comparaison** : La fonction utilise `strcmp` pour effectuer une comparaison lexicographique des chaînes.
- **Retour** : Retourne la chaîne qui est la plus petite en ordre alphabétique.

### 4. Surcharge pour les Tableaux Statiques

Les surcharges de `myMin` sont ajoutées pour traiter les cas spécifiques des tableaux statiques de tailles égales ou différentes.

- **Tableaux de même taille** :
  ```cpp
  template <std::size_t I>
  const char* myMin(const char(&a)[I], const char(&b)[I]);
  ```
  Utilise `strcmp` pour comparer deux tableaux de même taille.

- **Tableaux de tailles différentes** :
  ```cpp
  template <std::size_t I, std::size_t J>
  const char* myMin(const char(&a)[I], const char(&b)[J]);
  ```
  Utilise également `strcmp` pour comparer des tableaux de tailles différentes.

Ces surcharges permettent de traiter des tableaux statiques directement, sans avoir à les convertir en `const char*`.

## Résultats Attendus à l'Exécution

Lors de l'exécution du programme, les résultats suivants devraient s'afficher :

1. **`myMin(5, 6)`** :
   - Affichage : `Min(5, 6): 5`

2. **`myMin(6, 5)`** :
   - Affichage : `Min(6, 5): 5`

3. **`myMin("lili", "lala")`** :
   - Affichage : `Min("lili", "lala"): lala`

4. **`myMin("li", "lala")`** :
   - Affichage : `Min("li", "lala"): lala`

5. **`myMin(cc, dd)`** (où `cc = "mumu"` et `dd = "ma"`) :
   - Affichage : `Min(cc, dd): ma`

6. **`myMin(ee, ff)`** (où `ee = "toto"` et `ff = "ta"`) :
   - Affichage : `Min(ee, ff): ta`

7. **`myMin("zut", ff)`** (où `ff = "ta"`) :
   - Affichage : `Min("zut", ff): ta`

### Résumé de l'Affichage

```
Min(5, 6): 5
Min(6, 5): 5
Min("lili", "lala"): lala
Min("li", "lala"): lala
Min(cc, dd): ma
Min(ee, ff): ta
Min("zut", ff): ta
```

## Conclusion

Cet exercice permet de se familiariser avec les templates en C++ ainsi qu'avec leur spécialisation et surcharge pour des types particuliers comme les chaînes de caractères et les tableaux statiques. Le recours aux *templates* rend le code plus générique et réutilisable, évitant la redondance et simplifiant la maintenance du code.




------------------------------






# Explication de l'implémentation de la classe `Tableau`

Cette implémentation de la classe `Tableau` en C++ a été faite pour répondre aux exigences de l'énoncé, qui nous demande de créer une classe générique pour un tableau dynamique. Voici une explication détaillée de la réponse apportée à chaque question posée dans l'énoncé.

## Constructeurs utiles

### Constructeur par défaut
Le constructeur par défaut alloue dynamiquement un tableau avec une capacité initiale de `AGRANDISSEMENT` éléments. Cette capacité sera étendue automatiquement lorsque le tableau est plein.

```cpp
Tableau() : taille(0), capacite(AGRANDISSEMENT) {
    elements = new T[capacite];
    ++compteur;
}
```

Ce constructeur initialise un tableau vide avec une capacité prédéfinie par `AGRANDISSEMENT`. Il met aussi à jour le compteur des instances de `Tableau`.

### Constructeur à partir d'un tableau classique
Ce constructeur permet de créer un `Tableau` à partir d'un tableau C-ANSI classique (c'est-à-dire un tableau contigu en mémoire). La capacité est ajustée pour inclure `AGRANDISSEMENT` cases supplémentaires.

```cpp
Tableau(T* tableau, std::size_t n) : taille(n), capacite(n + AGRANDISSEMENT) {
    elements = new T[capacite];
    for (std::size_t i = 0; i < n; ++i) {
        elements[i] = tableau[i];
    }
    ++compteur;
}
```

Ce constructeur initialise la capacité du tableau à la taille du tableau donné plus `AGRANDISSEMENT`, afin d'assurer de la place pour de futures expansions.

### Constructeur par copie
Ce constructeur permet de créer une copie d'un `Tableau` existant en utilisant une copie en profondeur, c'est-à-dire en dupliquant chaque élément du tableau.

```cpp
Tableau(const Tableau& autre) : taille(autre.taille), capacite(autre.capacite) {
    elements = new T[capacite];
    for (std::size_t i = 0; i < taille; ++i) {
        elements[i] = autre.elements[i];
    }
    ++compteur;
}
```

L'utilisation d'une copie en profondeur est importante pour s'assurer que les deux objets `Tableau` ne partagent pas le même bloc mémoire.

## Fonction membre `ajoute`
Cette fonction ajoute un nouvel élément à la fin du tableau. Si la capacité est atteinte, la fonction appelle une méthode privée d'agrandissement pour étendre dynamiquement la capacité.

```cpp
void ajoute(const T& element) {
    if (taille == capacite) {
        agrandir();
    }
    elements[taille++] = element;
}
```

Cette fonction utilise la fonction privée `agrandir` lorsque la taille atteinte égale la capacité.

### Fonction privée `agrandir`
La fonction privée `agrandir` est appelée automatiquement lorsque la capacité du tableau est atteinte. Elle augmente la capacité de `AGRANDISSEMENT` éléments.

```cpp
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
```

Cette méthode copie les éléments dans un nouveau tableau avec une capacité augmentée, puis libère la mémoire précédente.

## Opérateur `[]`
L'opérateur `[]` est redéfini pour permettre un accès à un élément spécifique du tableau, tout en vérifiant les dépassements de limites.

```cpp
T& operator[](std::size_t index) {
    if (index >= taille) {
        throw std::out_of_range("Index hors limite");
    }
    return elements[index];
}
```

Cet opérateur renvoie une référence sur l'élément à la position donnée, avec une vérification des dépassements d'index.

## Opérateur d'affectation
Cet opérateur permet de copier un `Tableau` en utilisant une copie en profondeur.

```cpp
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
```

Cet opérateur commence par vérifier l'auto-affectation et fait ensuite une copie en profondeur des éléments de `autre`.

## Destructeur
Le destructeur libère la mémoire allouée dynamiquement pour éviter les fuites de mémoire.

```cpp
~Tableau() {
    delete[] elements;
    --compteur;
}
```

Le destructeur libère les éléments et diminue le compteur d'instances.

## Opérations d'entrées/sorties
L'opérateur `<<` est redéfini pour permettre l'affichage du contenu du tableau.

```cpp
friend std::ostream& operator<<(std::ostream& os, const Tableau& tableau) {
    for (std::size_t i = 0; i < tableau.taille; ++i) {
        os << tableau.elements[i] << " ";
    }
    return os;
}
```

Cet opérateur parcourt tous les éléments du tableau et les affiche.

## Compteur d'instances
Le compteur d'instances permet de connaître le nombre d'instances de `Tableau` existantes.

```cpp
static int getCompteur() {
    return compteur;
}
```

Cela permet de vérifier le nombre d'objets `Tableau` en vie à un moment donné.

## Test des méthodes dans `main`
Dans la fonction `main`, nous testons chaque fonctionnalité de la classe `Tableau` : ajout d'éléments, utilisation du constructeur par copie, affichage, et vérification du nombre d'instances.

```cpp
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

    // Test du constructeur par copie
    Tableau<int> t2 = t;
    std::cout << "Tableau copié: " << t2 << std::endl;

    // Affichage du nombre d'instances
    std::cout << "Nombre d'instances: " << Tableau<int>::getCompteur() << std::endl;

    return 0;
}
```

Cette fonction montre l'utilisation de la classe `Tableau`, notamment l'ajout d'éléments, l'accès aux éléments avec `[]`, la copie, et la vérification du compteur d'instances. Cela permet de vérifier que chaque partie de la classe fonctionne correctement.

