// #include <iostream>

// // Compteur global pour suivre les clonages
// static int clone_count = 0;

// // Classe de base pour les expressions
// class Expression {
// public:
//     virtual ~Expression() {}
//     virtual int eval() const = 0;
//     virtual Expression* clone() const = 0;
//     virtual Expression* cloneTemporary() = 0;  // Méthode de clonage pour les rvalue references
// };

// // Classe pour les constantes
// class Constante : public Expression {
//     int valeur;
// public:
//     Constante(int v) : valeur(v) {}

//     virtual int eval() const override {
//         return valeur;
//     }

//     virtual Expression* clone() const override {
//         ++clone_count;  // Incrémente le compteur de clonages
//         return new Constante(*this);
//     }

//     virtual Expression* cloneTemporary() override {
//         ++clone_count;  // Incrémente le compteur de clonages
//         return new Constante(std::move(*this));
//     }
// };

// // Classe de base pour les expressions binaires
// class ExpressionBinaire : public Expression {
// protected:
//     Expression* gauche;
//     Expression* droite;
// public:
//     ExpressionBinaire(const Expression& g, const Expression& d)
//         : gauche(g.clone()), droite(d.clone()) {}

//     ExpressionBinaire(Expression&& g, Expression&& d)
//         : gauche(g.cloneTemporary()), droite(d.cloneTemporary()) {}

//     virtual ~ExpressionBinaire() {
//         delete gauche;
//         delete droite;
//     }

//     ExpressionBinaire(const ExpressionBinaire& other)
//         : gauche(other.gauche->clone()), droite(other.droite->clone()) {}

//     ExpressionBinaire& operator=(const ExpressionBinaire& other) {
//         if (this != &other) {
//             delete gauche;
//             delete droite;
//             gauche = other.gauche->clone();
//             droite = other.droite->clone();
//         }
//         return *this;
//     }
// };

// // Classe pour les additions
// class Plus : public ExpressionBinaire {
// public:
//     Plus(const Expression& g, const Expression& d) : ExpressionBinaire(g, d) {}

//     Plus(Expression&& g, Expression&& d) : ExpressionBinaire(std::move(g), std::move(d)) {}

//     virtual int eval() const override {
//         return gauche->eval() + droite->eval();
//     }

//     virtual Expression* clone() const override {
//         ++clone_count;  // Incrémente le compteur de clonages
//         return new Plus(*this);
//     }

//     virtual Expression* cloneTemporary() override {
//         ++clone_count;  // Incrémente le compteur de clonages
//         return new Plus(std::move(*this));
//     }
// };

// // Classe pour les multiplications
// class Mult : public ExpressionBinaire {
// public:
//     Mult(const Expression& g, const Expression& d) : ExpressionBinaire(g, d) {}

//     Mult(Expression&& g, Expression&& d) : ExpressionBinaire(std::move(g), std::move(d)) {}

//     virtual int eval() const override {
//         return gauche->eval() * droite->eval();
//     }

//     virtual Expression* clone() const override {
//         ++clone_count;  // Incrémente le compteur de clonages
//         return new Mult(*this);
//     }

//     virtual Expression* cloneTemporary() override {
//         ++clone_count;  // Incrémente le compteur de clonages
//         return new Mult(std::move(*this));
//     }
// };

// // Programme utilisateur pour tester les classes
// int main() {
//     // Test avec des références constantes (copies)
//     const Expression& expr1 = Mult(
//         Plus(Constante(5), Constante(-2)),
//         Plus(Constante(1), Constante(3))
//     );

//     std::cout << "Evaluation de expr1: " << expr1.eval() << std::endl;

//     // Affichage du nombre de clonages
//     std::cout << "Nombre de clonages (nouveau code) : " << clone_count << std::endl;

//     return 0;
// }

#include <iostream>

// Compteur global pour suivre les clonages
static int clone_count = 0;

// Classe de base pour les expressions
class Expression {
public:
    virtual ~Expression() {}
    virtual int eval() const = 0;
    virtual Expression* clone() const = 0;
    virtual Expression* cloneTemporary() = 0;  // Méthode de clonage pour les rvalue references
};

// Classe pour les constantes
class Constante : public Expression {
    int valeur;
public:
    Constante(int v) : valeur(v) {}

    virtual int eval() const override {
        return valeur;
    }

    virtual Expression* clone() const override {
        ++clone_count;  // Incrémente le compteur de clonages
        return new Constante(*this);
    }

    virtual Expression* cloneTemporary() override {
        ++clone_count;  // Incrémente le compteur de clonages
        return new Constante(*this);
    }
};

// Classe de base pour les expressions binaires
class ExpressionBinaire : public Expression {
protected:
    Expression* gauche;
    Expression* droite;
public:
    ExpressionBinaire(const Expression& g, const Expression& d)
        : gauche(g.clone()), droite(d.clone()) {}

    ExpressionBinaire(Expression&& g, Expression&& d)
        : gauche(g.cloneTemporary()), droite(d.cloneTemporary()) {}

    virtual ~ExpressionBinaire() {
        delete gauche;
        delete droite;
    }

    ExpressionBinaire(const ExpressionBinaire& other)
        : gauche(other.gauche->clone()), droite(other.droite->clone()) {}

    ExpressionBinaire& operator=(const ExpressionBinaire& other) {
        if (this != &other) {
            delete gauche;
            delete droite;
            gauche = other.gauche->clone();
            droite = other.droite->clone();
        }
        return *this;
    }
};

// Classe pour les additions
class Plus : public ExpressionBinaire {
public:
    Plus(const Expression& g, const Expression& d) : ExpressionBinaire(g, d) {}

    Plus(Expression&& g, Expression&& d) : ExpressionBinaire(std::move(g), std::move(d)) {}

    virtual int eval() const override {
        return gauche->eval() + droite->eval();
    }

    virtual Expression* clone() const override {
        ++clone_count;  // Incrémente le compteur de clonages
        return new Plus(*this);
    }

    virtual Expression* cloneTemporary() override {
        ++clone_count;  // Incrémente le compteur de clonages
        return new Plus(*this);
    }
};

// Classe pour les multiplications
class Mult : public ExpressionBinaire {
public:
    Mult(const Expression& g, const Expression& d) : ExpressionBinaire(g, d) {}

    Mult(Expression&& g, Expression&& d) : ExpressionBinaire(std::move(g), std::move(d)) {}

    virtual int eval() const override {
        return gauche->eval() * droite->eval();
    }

    virtual Expression* clone() const override {
        ++clone_count;  // Incrémente le compteur de clonages
        return new Mult(*this);
    }

    virtual Expression* cloneTemporary() override {
        ++clone_count;  // Incrémente le compteur de clonages
        return new Mult(*this);
    }
};

// Programme utilisateur pour tester les classes
int main() {
    // Test avec des références constantes (copies)
    const Expression& expr1 = Mult(
        Plus(Constante(5), Constante(-2)),
        Plus(Constante(1), Constante(3))
    );

    std::cout << "Evaluation de expr1: " << expr1.eval() << std::endl;

    // Affichage du nombre de clonages
    std::cout << "Nombre de clonages (nouveau code) : " << clone_count << std::endl;

    return 0;
}
