// #include <iostream>

// // Classe abstraite Expression
// class Expression { // Elle est abstraite car elle a des méthodes vituelles pure !! = on ne peux pas instancier directement cette classe, elle sert de classe de base
// public:
//     // Méthode d'évaluation
//     virtual int eval() const = 0; // méthode virtuel pure gràçe au " = 0 " donc les classes dérivées doivent fournir une implémentation de cette méthode. 
//     // virtual = peut être redéfini dans les classes dérivées

//     // Méthode de clonage
//     virtual Expression* clone() const = 0; // retourne un pointeur vers un objet de type Expression.
//     // clone() permet de dupliquer une instance d'une classe dérivée. En raison du polymorphisme, la classe Expression ne sait pas comment cloner une instance exacte, donc chaque classe dérivée doit implémenter sa propre version de clone().
    
//     // Destructeur virtuel
//     virtual ~Expression() {}
// protected:
//     // Constructeur protégé
//     Expression() {}
//     // Constructeur de copie protégé
//     Expression(const Expression&) {}
//     // Opérateur d'affectation protégé
//     Expression& operator=(const Expression&) { return *this; }
// };

// // Classe Constante, dérivée de Expression
// class Constante : public Expression {
// public:
//     // Constructeur prenant un entier en paramètre
//     Constante(int valeur) : m_valeur(valeur) {}
//     // Méthode d'évaluation
//     virtual int eval() const override { return m_valeur; }
//     // Méthode de clonage
//     virtual Expression* clone() const override { return new Constante(*this); }
//     // Destructeur
//     virtual ~Constante() {}
// protected:
//     // Constructeur de copie protégé
//     Constante(const Constante& other) : m_valeur(other.m_valeur) {}
//     // Opérateur d'affectation protégé
//     Constante& operator=(const Constante& other) {
//         m_valeur = other.m_valeur;
//         return *this;
//     }
// private:
//     int m_valeur;
// };

// // Classe ExpressionBinaire, dérivée de Expression
// class ExpressionBinaire : public Expression {
// public:
//     // Destructeur virtuel
//     virtual ~ExpressionBinaire() {
//         delete m_gauche;
//         delete m_droite;
//     }
// protected:
//     // Constructeur protégé prenant deux expressions en paramètre
//     ExpressionBinaire(const Expression& gauche, const Expression& droite)
//         : m_gauche(gauche.clone()), m_droite(droite.clone()) {}
//     // Constructeur de copie protégé
//     ExpressionBinaire(const ExpressionBinaire& other)
//         : m_gauche(other.m_gauche->clone()), m_droite(other.m_droite->clone()) {}
//     // Opérateur d'affectation protégé
//     ExpressionBinaire& operator=(const ExpressionBinaire& other) {
//         if (this != &other) {
//             delete m_gauche;
//             delete m_droite;
//             m_gauche = other.m_gauche->clone();
//             m_droite = other.m_droite->clone();
//         }
//         return *this;
//     }
//     Expression* m_gauche;
//     Expression* m_droite;
// };

// // Classe Plus, dérivée de ExpressionBinaire
// class Plus : public ExpressionBinaire {
// public:
//     // Constructeur prenant deux expressions en paramètre
//     Plus(const Expression& gauche, const Expression& droite)
//         : ExpressionBinaire(gauche, droite) {}
//     // Méthode d'évaluation
//     virtual int eval() const override {
//         return m_gauche->eval() + m_droite->eval();
//     }
//     // Méthode de clonage
//     virtual Expression* clone() const override {
//         return new Plus(*this);
//     }
//     // Destructeur
//     virtual ~Plus() {}
// protected:
//     // Constructeur de copie protégé
//     Plus(const Plus& other) : ExpressionBinaire(other) {}
//     // Opérateur d'affectation protégé
//     Plus& operator=(const Plus& other) {
//         ExpressionBinaire::operator=(other);
//         return *this;
//     }
// };

// // Classe Moins, dérivée de ExpressionBinaire
// class Moins : public ExpressionBinaire {
// public:
//     // Constructeur prenant deux expressions en paramètre
//     Moins(const Expression& gauche, const Expression& droite)
//         : ExpressionBinaire(gauche, droite) {}
//     // Méthode d'évaluation
//     virtual int eval() const override {
//         return m_gauche->eval() - m_droite->eval();
//     }
//     // Méthode de clonage
//     virtual Expression* clone() const override {
//         return new Moins(*this);
//     }
//     // Destructeur
//     virtual ~Moins() {}
// protected:
//     // Constructeur de copie protégé
//     Moins(const Moins& other) : ExpressionBinaire(other) {}
//     // Opérateur d'affectation protégé
//     Moins& operator=(const Moins& other) {
//         ExpressionBinaire::operator=(other);
//         return *this;
//     }
// };

// // Classe Mult, dérivée de ExpressionBinaire
// class Mult : public ExpressionBinaire {
// public:
//     // Constructeur prenant deux expressions en paramètre   
//     Mult(const Expression& gauche, const Expression& droite)
//         : ExpressionBinaire(gauche, droite) {}
//     // Méthode d'évaluation
//     virtual int eval() const override {
//         return m_gauche->eval() * m_droite->eval();
//     }
//     // Méthode de clonage
//     virtual Expression* clone() const override {
//         return new Mult(*this);
//     }
//     // Destructeur
//     virtual ~Mult() {}
// protected:
//     // Constructeur de copie protégé
//     Mult(const Mult& other) : ExpressionBinaire(other) {}
//     // Opérateur d'affectation protégé
//     Mult& operator=(const Mult& other) {
//         ExpressionBinaire::operator=(other);
//         return *this;
//     }
// };

// // Programme utilisateur pour tester les classes
// int main()
// {
//     int a = 5;
//     const Expression& e = Mult(
//         Plus(Constante(a), Constante(-2)),
//         Plus(Constante(1), Constante(3))
//     );

//     std::cout << e.eval() << std::endl; // Affiche le résultat de l'évaluation
//     return 0;
// }

#include <iostream>

// Compteur global pour suivre les clonages
static int clone_count = 0;

// Classe abstraite Expression
class Expression {
public:
    virtual int eval() const = 0;
    virtual Expression* clone() const = 0;

    virtual ~Expression() {}
protected:
    Expression() {}
    Expression(const Expression&) {}
    Expression& operator=(const Expression&) { return *this; }
};

// Classe Constante, dérivée de Expression
class Constante : public Expression {
public:
    Constante(int valeur) : m_valeur(valeur) {}

    virtual int eval() const override { return m_valeur; }

    virtual Expression* clone() const override {
        ++clone_count;  // Incrémente le compteur de clonages
        return new Constante(*this);
    }

    virtual ~Constante() {}
protected:
    Constante(const Constante& other) : m_valeur(other.m_valeur) {}

    Constante& operator=(const Constante& other) {
        m_valeur = other.m_valeur;
        return *this;
    }
private:
    int m_valeur;
};

// Classe ExpressionBinaire, dérivée de Expression
class ExpressionBinaire : public Expression {
public:
    virtual ~ExpressionBinaire() {
        delete m_gauche;
        delete m_droite;
    }
protected:
    ExpressionBinaire(const Expression& gauche, const Expression& droite)
        : m_gauche(gauche.clone()), m_droite(droite.clone()) {}

    ExpressionBinaire(const ExpressionBinaire& other)
        : m_gauche(other.m_gauche->clone()), m_droite(other.m_droite->clone()) {}

    ExpressionBinaire& operator=(const ExpressionBinaire& other) {
        if (this != &other) {
            delete m_gauche;
            delete m_droite;
            m_gauche = other.m_gauche->clone();
            m_droite = other.m_droite->clone();
        }
        return *this;
    }
    Expression* m_gauche;
    Expression* m_droite;
};

// Classe Plus, dérivée de ExpressionBinaire
class Plus : public ExpressionBinaire {
public:
    Plus(const Expression& gauche, const Expression& droite)
        : ExpressionBinaire(gauche, droite) {}

    virtual int eval() const override {
        return m_gauche->eval() + m_droite->eval();
    }

    virtual Expression* clone() const override {
        ++clone_count;  // Incrémente le compteur de clonages
        return new Plus(*this);
    }

    virtual ~Plus() {}
protected:
    Plus(const Plus& other) : ExpressionBinaire(other) {}

    Plus& operator=(const Plus& other) {
        ExpressionBinaire::operator=(other);
        return *this;
    }
};

// Classe Mult, dérivée de ExpressionBinaire
class Mult : public ExpressionBinaire {
public:
    Mult(const Expression& gauche, const Expression& droite)
        : ExpressionBinaire(gauche, droite) {}

    virtual int eval() const override {
        return m_gauche->eval() * m_droite->eval();
    }

    virtual Expression* clone() const override {
        ++clone_count;  // Incrémente le compteur de clonages
        return new Mult(*this);
    }

    virtual ~Mult() {}
protected:
    Mult(const Mult& other) : ExpressionBinaire(other) {}

    Mult& operator=(const Mult& other) {
        ExpressionBinaire::operator=(other);
        return *this;
    }
};

// Programme utilisateur pour tester les classes
int main() {
    int a = 5;
    const Expression& e = Mult(
        Plus(Constante(a), Constante(-2)),
        Plus(Constante(1), Constante(3))
    );

    std::cout << e.eval() << std::endl;

    // Affichage du nombre de clonages
    std::cout << "Nombre de clonages (ancien code) : " << clone_count << std::endl;

    return 0;
}
