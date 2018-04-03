#include "reseaux.h"

///Consctructeurs et destructeurs de la classe ecosysteme
 Ecosysteme::Ecosysteme()
           :m_N(0)
{

}



Ecosysteme::Ecosysteme(int _N)
           :m_N(_N)
{

}

Ecosysteme::~Ecosysteme()
{

}

///Consctructeurs et destructeurs de la classe espece
Espece::Espece()
       :Ecosysteme(), m_animal(true)
{

}

Espece::Espece(bool _animal, int _N)
       :Ecosysteme(_N),m_animal(_animal)
{

}


Espece::~Espece()
{

}

///Consctructeurs et destructeurs de la classe ressource

Ressource::Ressource()
          :Ecosysteme()
{

}

Ressource::Ressource(int _N)
          :Ecosysteme(_N)
{

}


Ressource::~Ressource()
{

}
