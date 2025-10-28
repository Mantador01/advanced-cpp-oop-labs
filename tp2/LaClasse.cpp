#include <iostream>
#include <chrono>  // Pour mesurer le temps


class LaClasse
{
public:
    // Default constructor
    LaClasse() : l(new int(0))
    {
        std::cout << "LaClasse::LaClasse()\n";
    }

    // Parametrized constructor
    LaClasse(int i) : l(new int(i))
    {
        std::cout << "LaClasse::LaClasse(int)\n";
    }

    // Copy constructor
    LaClasse(const LaClasse& lc) : l(new int(*lc.l))
    {
        std::cout << "LaClasse::LaClasse(const LaClasse&)\n";
    }

    // Move constructor
    LaClasse(LaClasse&& lc) noexcept : l(lc.l)
    {
        lc.l = nullptr; // Make sure the moved object does not hold the resource anymore
        std::cout << "LaClasse::LaClasse(LaClasse&&)\n";
    }

    // Copy assignment operator
    LaClasse& operator=(const LaClasse& lc)
    {
        if (this != &lc)  // Self-assignment check
        {
            *l = *lc.l;
        }
        std::cout << "LaClasse::operator=(const LaClasse&)\n";
        return *this;
    }

    // Move assignment operator
    LaClasse& operator=(LaClasse&& lc) noexcept
    {
        if (this != &lc)  // Self-assignment check
        {
            delete l;    // Release any resource held by this object
            l = lc.l;    // Steal the resource
            lc.l = nullptr;  // Ensure the moved object doesn't hold the resource anymore
        }
        std::cout << "LaClasse::operator=(LaClasse&&)\n";
        return *this;
    }

    // Destructor
    ~LaClasse()
    {
        delete l;
        std::cout << "~LaClasse::LaClasse()\n";
    }

    // Conversion to bool operator
    operator bool() const
    {
        std::cout << "LaClasse::operator bool() const\n";
        return true;
    }

    // Function member
    LaClasse F(LaClasse);

    // Friend function to overload <<
    friend std::ostream& operator<<(std::ostream& os, const LaClasse& lc);

protected: // PASSER EN PROTECTED POUR QUE LES CLASSES DERIVEES PUISSENT Y ACCEDER
    int* l;  // Dynamically allocated resource
};

// // Definition of external function F
// LaClasse F(LaClasse vv)
// {
//     std::cout << " in F \n";
//     return LaClasse(8);  // Returning a new LaClasse object with value 8
// }

// // Member function F
// LaClasse LaClasse::F(LaClasse v)
// {
//     std::cout << " in LaClasse::F \n";
//     return ::F(v);
// }

// // Overloaded << operator for printing
// std::ostream& operator<<(std::ostream& os, const LaClasse& lc)
// {
//     os << " in ostream << LaClasse " << *lc.l << std::endl;
//     return os;
// }

// // Main function to test the class
// int main()
// {
//     // Mesurer plusieurs itérations pour améliorer la précision
//     const int iterations = 10000;  // 1 million d'itérations

//     // Démarrer le chronomètre
//     auto start = std::chrono::high_resolution_clock::now();

//     // Boucle d'itérations pour tester les performances
//     for (int i = 0; i < iterations; ++i)
//     {
//         LaClasse c1;
//         LaClasse c2 = LaClasse();
//         LaClasse cc1(c1);
//         LaClasse cc2 = c1;
//         LaClasse cc3 = LaClasse(c1);
//         LaClasse cv1(5);
//         LaClasse cv2 = 5;
//         LaClasse cv3 = LaClasse(5);
//         LaClasse cv4 = (LaClasse)5;

//         c1 = cc1;
//         c2 = 8;

//         if (cv1)
//         {
//             cv1 = F(10);
//             cv1 = F(c1);
//             cv1 = c1.F(c2);
//         }

//         LaClasse tab[3];
//         LaClasse* pc = new LaClasse(tab[0]);
//         delete pc;
//     }

//     // Arrêter le chronomètre
//     auto end = std::chrono::high_resolution_clock::now();

//     // Calcul du temps écoulé en nanosecondes
//     auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

//     // Afficher le temps d'exécution total
//     std::cout << "Temps d'exécution total: " << duration.count() << " nanosecondes\n";
    
//     // Afficher le temps moyen par itération
//     double avg_duration = static_cast<double>(duration.count()) / iterations;
//     std::cout << "Temps moyen par itération: " << avg_duration << " nanosecondes\n";

//     return 0;
// }

// Classe dérivée
class LaClasseSpecialisee : public LaClasse
{
public:
    // Constructeur par défaut
    LaClasseSpecialisee() : LaClasse(), extra(new int(0))
    {
        std::cout << "LaClasseSpecialisee::LaClasseSpecialisee()\n";
    }

    // Constructeur avec paramètres
    LaClasseSpecialisee(int i, int j) : LaClasse(i), extra(new int(j))
    {
        std::cout << "LaClasseSpecialisee::LaClasseSpecialisee(int, int)\n";
    }

    // Constructeur par copie
    LaClasseSpecialisee(const LaClasseSpecialisee& other) : LaClasse(other), extra(new int(*other.extra))
    {
        std::cout << "LaClasseSpecialisee::LaClasseSpecialisee(const LaClasseSpecialisee&)\n";
    }

    // Opérateur d'affectation
    LaClasseSpecialisee& operator=(const LaClasseSpecialisee& other)
    {
        if (this != &other)
        {
            LaClasse::operator=(other); // Appel au opérateur d'affectation de la classe de base
            *extra = *other.extra;
        }
        std::cout << "LaClasseSpecialisee::operator=(const LaClasseSpecialisee&)\n";
        return *this;
    }

    // Destructeur
    ~LaClasseSpecialisee()
    {
        delete extra;
        std::cout << "~LaClasseSpecialisee::LaClasseSpecialisee()\n";
    }

private:
    int* extra;
};

// Test du comportement des constructeurs, opérateurs et destructeurs
int main()
{
    // Test du constructeur par défaut
    std::cout << "Création de s1\n";
    LaClasseSpecialisee s1;

    // Test du constructeur avec paramètres
    std::cout << "Création de s2 avec paramètres\n";
    LaClasseSpecialisee s2(5, 10);

    // Test du constructeur par copie
    std::cout << "Création de s3 par copie de s2\n";
    LaClasseSpecialisee s3(s2);

    // Test de l'opérateur d'affectation
    std::cout << "Affectation de s1 à s3\n";
    s1 = s3;

    // Destruction des objets à la fin du scope
    std::cout << "Avant de sortir ...\n";

    return 0;
}