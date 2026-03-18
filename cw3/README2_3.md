# `cw3-2.cpp` i `cw3-3.cpp` – konstruktor kopiujący

Te dwa programy pokazują, czym jest **konstruktor kopiujący**, kiedy kompilator tworzy go automatycznie oraz po co czasem pisze się własną wersję tego konstruktora.

Pierwszy przykład pokazuje sytuację, w której konstruktor kopiujący nie został zdefiniowany ręcznie. Drugi przykład pokazuje klasę z własnym konstruktorem kopiującym.

## `cw3-2.cpp` – domyślny konstruktor kopiujący

### Kod programu

```cpp
#include <iostream>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    // Default constructor
    Fraction(int numerator=0, int denominator=1)
        : m_numerator{numerator}, m_denominator{denominator}
    {
    }

    void print() const
    {
        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
    }
};

int main()
{
    Fraction f { 5, 3 };  // Calls Fraction(int, int) constructor
    Fraction fCopy { f }; // What constructor is used here?

    f.print();
    fCopy.print();

    return 0;
}
```

### Co dzieje się w tym programie

Obiekt:

```cpp
Fraction f { 5, 3 };
```

jest tworzony przez konstruktor:

```cpp
Fraction(int numerator=0, int denominator=1)
```

Następnie pojawia się instrukcja:

```cpp
Fraction fCopy { f };
```

To nie jest zwykłe przypisanie, tylko **inicjalizacja nowego obiektu na podstawie istniejącego obiektu tej samej klasy**. W takiej sytuacji używany jest właśnie **konstruktor kopiujący**.

Ponieważ klasa `Fraction` nie definiuje własnego konstruktora kopiującego, kompilator generuje **domyślny konstruktor kopiujący** automatycznie.

## Czym jest domyślny konstruktor kopiujący

Jeśli programista nie napisze własnego konstruktora kopiującego, kompilator może wygenerować go sam.

Działa on w przybliżeniu tak, jakby klasa miała konstruktor w postaci:

```cpp
Fraction(const Fraction& other)
    : m_numerator{ other.m_numerator }
    , m_denominator{ other.m_denominator }
{
}
```

Taki konstruktor wykonuje **kopiowanie składowe po składowej**. Oznacza to, że każdy element obiektu źródłowego jest kopiowany do odpowiadającego mu elementu nowego obiektu.

W klasie `Fraction` oba pola są typu `int`, więc takie kopiowanie jest całkowicie poprawne i wystarczające.

### Wynik działania `cw3-2.cpp`

Program wypisze:

```text
Fraction(5, 3)
Fraction(5, 3)
```

Nie zobaczymy żadnego komunikatu o kopiowaniu, ponieważ domyślny
