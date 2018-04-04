#ifndef RESEAUX_H_INCLUDED
#define RESEAUX_H_INCLUDED


class Ecosysteme
{
protected:
    int m_N;  ///Nombre d'individu ou nb de kilos (pour herbe par ex)

public:
    Ecosysteme();
    Ecosysteme(int _N);
    ~Ecosysteme();
};


class Espece : public Ecosysteme
{
protected:
    bool m_animal;
public:

    Espece();
    Espece(bool _animal, int _N);
    ~Espece();


};

class Animal: public Espece
{
    public:
        Animal();

};

class Vegetal: public Espece
{

};
class Ressource : public Ecosysteme
{
private:
public:
     Ressource();
     Ressource(int _N);
    ~Ressource();
};

#endif // RESEAUX_H_INCLUDED
