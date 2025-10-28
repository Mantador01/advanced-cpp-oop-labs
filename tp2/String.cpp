#include <iostream>
#include <cstring>  // Pour utiliser des fonctions C standard comme strlen, strcpy

class String {
private:
    char* str;  // Pointeur vers la chaîne de caractères
    size_t length;  // Longueur de la chaîne

public:
    // Constructeur par défaut (chaîne vide)
    String() : str(new char[1]), length(0) {
        str[0] = '\0';  // Chaîne vide
    }

    // Constructeur à partir d'une chaîne C-style
    String(const char* s) : length(strlen(s)) {
        str = new char[length + 1];  // Allocation dynamique
        strcpy(str, s);  // Copie de la chaîne
    }

    // Constructeur à partir d'un seul caractère
    String(char c) : length(1) {
        str = new char[2];  // Un caractère + le caractère de fin '\0'
        str[0] = c;
        str[1] = '\0';
    }

    // Constructeur de copie
    String(const String& other) : length(other.length) {
        str = new char[length + 1];
        strcpy(str, other.str);
    }

    // Opérateur d'affectation
    String& operator=(const String& other) {
        if (this != &other) {  // Vérification de l'auto-affectation
            delete[] str;  // Libérer la mémoire actuelle
            length = other.length;
            str = new char[length + 1];  // Réallouer la mémoire
            strcpy(str, other.str);  // Copier la chaîne
        }
        return *this;
    }

    // Destructeur
    ~String() {
        delete[] str;
    }

    // Conversion en chaîne C-style
    const char* c_str() const {
        return str;
    }

    // Longueur de la chaîne
    size_t size() const {
        return length;
    }

    // Test si la chaîne est vide
    bool empty() const {
        return length == 0;
    }

    // Accès à un caractère (lecture et écriture)
    char& operator[](size_t index) {
        return str[index];
    }

    const char& operator[](size_t index) const {
        return str[index];
    }

    // Concatenation
    String operator+(const String& other) const {
        // Crée une nouvelle chaîne de taille correcte
        size_t new_length = length + other.length;
        char* new_str = new char[new_length + 1];  // Allocation dynamique

        strcpy(new_str, str);  // Copier la première chaîne
        strcat(new_str, other.str);  // Ajouter la deuxième chaîne

        // Crée un objet String à partir de cette nouvelle chaîne
        String result(new_str);

        // Libérer la mémoire temporaire
        delete[] new_str;

        return result;
    }


    // Comparaison d'égalité
    bool operator==(const String& other) const {
        return strcmp(str, other.str) == 0;
    }

    bool operator!=(const String& other) const {
        return !(*this == other);
    }

    // Comparaison lexicographique
    bool operator<(const String& other) const {
        return strcmp(str, other.str) < 0;
    }

    bool operator>(const String& other) const {
        return strcmp(str, other.str) > 0;
    }

    bool operator<=(const String& other) const {
        return !(*this > other);
    }

    bool operator>=(const String& other) const {
        return !(*this < other);
    }

    // Sous-chaîne (de l'index début à fin)
    String substring(size_t start, size_t end) const {
        if (start >= length || end >= length || start > end) {
            return String();  // Retourne une chaîne vide si les indices sont invalides
        }
        size_t sub_length = end - start + 1;
        char* sub_str = new char[sub_length + 1];
        strncpy(sub_str, str + start, sub_length);
        sub_str[sub_length] = '\0';  // Terminaison
        String result(sub_str);
        delete[] sub_str;
        return result;
    }

    // Surcharger l'opérateur << pour afficher
    friend std::ostream& operator<<(std::ostream& os, const String& s) {
        os << s.str;
        return os;
    }

    // Surcharger l'opérateur >> pour l'entrée
    friend std::istream& operator>>(std::istream& is, String& s) {
        char buffer[1000];
        is >> buffer;
        s = String(buffer);  // Utiliser l'affectation
        return is;
    }
};

int main() {
    // Test des constructeurs
    String s1("Bonjour");
    String s2('A');
    String s3;

    // Affichage des chaînes
    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;
    std::cout << "s3 (vide): " << s3 << std::endl;

    // Test de la concaténation
    String s4 = s1 + " monde";
    std::cout << "s4: " << s4 << std::endl;

    // Test des opérateurs de comparaison
    std::cout << "s1 == s2 ? " << (s1 == s2) << std::endl;
    std::cout << "s1 != s2 ? " << (s1 != s2) << std::endl;

    // Test de l'accès par index
    std::cout << "Premier caractère de s1: " << s1[0] << std::endl;

    // Test de la sous-chaîne
    String sub = s1.substring(0, 3);
    std::cout << "Sous-chaîne de s1: " << sub << std::endl;

    // Test de la longueur
    std::cout << "Longueur de s1: " << s1.size() << std::endl;

    // Test d'entrée
    String s5;
    std::cout << "Entrez une chaîne : ";
    std::cin >> s5;
    std::cout << "Vous avez entré : " << s5 << std::endl;

    return 0;
}

