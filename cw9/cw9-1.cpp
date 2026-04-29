#include <iostream>

class Bazowa
{
public:
    void metoda()
    {
        std::cout << "Bazowa::metoda" << std::endl;
    }
};

class Pochodna
    : public Bazowa
{
public:
    void metoda() //Przesłaniamy metode z klasy bazowej
    {
        std::cout << "Pochodna::metoda" << std::endl;
    }
};

int main()
{
    Bazowa b;
    Pochodna p;
   
    b.metoda();
    p.metoda();
   
    Bazowa * bptr = & p; //rzutowanie w górę
    bptr->metoda();
}
