# `cw2-7.cpp` – lista inicjalizacyjna konstruktora

Program pokazuje poprawny sposób inicjalizacji pól klasy za pomocą **listy inicjalizacyjnej konstruktora**.

## Kod programu

```cpp
#include <iostream>

class Foo
{
private:
    int m_x {};
    int m_y {};

public:
    Foo(int x, int y)
        : m_x { x }, m_y { y } // here's our member initialization list
    {
        std::cout << "Foo(" << x << ", " << y << ") constructed\n";
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
    }
};

int main()
{
    Foo foo{ 6, 7 };
    foo.print();

    return 0;
}
```

## Opis

W przeciwieństwie do poprzedniego przykładu, konstruktor nie tylko przyjmuje argumenty `x` i `y`, ale od razu używa ich do zainicjalizowania pól `m_x` i `m_y`.

Służy do tego lista inicjalizacyjna:

```cpp
: m_x { x }, m_y { y }
```

Dzięki temu obiekt od momentu utworzenia ma poprawny stan.

## Wynik działania programu

Program wypisze:

```text
Foo(6, 7) constructed
Foo(6, 7)
```

Pierwsza linia pochodzi z konstruktora, a druga z metody `print()`.

## Podsumowanie

Ten przykład pokazuje, że lista inicjalizacyjna konstruktora jest właściwym sposobem przekazywania wartości do pól klasy podczas tworzenia obiektu. Dzięki niej stan obiektu od razu odpowiada argumentom podanym przy jego tworzeniu.
