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

Nie zobaczymy żadnego komunikatu o kopiowaniu, ponieważ domyślny konstruktor kopiujący został wygenerowany przez kompilator i nie zawiera żadnego kodu wypisującego tekst.

---

## `cw3-3.cpp` – własny konstruktor kopiujący

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

    // Copy constructor
    Fraction(const Fraction& fraction)
        // Initialize our members using the corresponding member of the parameter
        : m_numerator{ fraction.m_numerator }
        , m_denominator{ fraction.m_denominator }
    {
        std::cout << "Copy constructor called\n"; // just to prove it works
    }

    void print() const
    {
        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
    }
};

int main()
{
    Fraction f { 5, 3 };  // Calls Fraction(int, int) constructor
    Fraction fCopy { f }; // Calls Fraction(const Fraction&) copy constructor

    f.print();
    fCopy.print();

    return 0;
}
```

### Jak wygląda konstruktor kopiujący

Własny konstruktor kopiujący ma zwykle postać:

```cpp
Fraction(const Fraction& fraction)
```

Najważniejsze elementy tej deklaracji to:

* nazwa taka sama jak nazwa klasy,
* brak typu zwracanego,
* jeden parametr będący referencją do stałego obiektu tej samej klasy.

Czyli ogólny wzór wygląda tak:

```cpp
NazwaKlasy(const NazwaKlasy& other)
```

### Dlaczego parametr jest referencją do `const`

Parametr ma typ:

```cpp
const Fraction& fraction
```

z dwóch powodów:

1. **referencja** – aby nie kopiować obiektu przy przekazywaniu argumentu,
2. **const** – ponieważ kopiowanie nie powinno zmieniać obiektu źródłowego.

Gdyby parametr nie był referencją, tylko zwykłym obiektem:

```cpp
Fraction(Fraction fraction)
```

wtedy samo przekazanie argumentu do konstruktora wymagałoby kolejnego kopiowania, co prowadziłoby do błędnego, nieskończonego łańcucha wywołań.

## Co robi konstruktor kopiujący w `cw3-3.cpp`

```cpp
Fraction(const Fraction& fraction)
    : m_numerator{ fraction.m_numerator }
    , m_denominator{ fraction.m_denominator }
{
    std::cout << "Copy constructor called\n";
}
```

Ten konstruktor:

* odczytuje pola obiektu przekazanego jako argument,
* kopiuje je do nowo tworzonego obiektu,
* dodatkowo wypisuje komunikat, aby było widać, że rzeczywiście został wywołany.

### Wynik działania `cw3-3.cpp`

Program wypisze:

```text
Copy constructor called
Fraction(5, 3)
Fraction(5, 3)
```

Komunikat pojawia się przy tworzeniu `fCopy`.

---

## Kiedy wywoływany jest konstruktor kopiujący

Konstruktor kopiujący jest wywoływany wtedy, gdy tworzony jest nowy obiekt na podstawie innego obiektu tej samej klasy.

Typowe sytuacje to:

```cpp
Fraction b{a};
Fraction b(a);
```

Często konstruktor kopiujący może być również używany przy:

* przekazywaniu obiektu przez wartość,
* zwracaniu obiektu przez wartość,
* tworzeniu obiektów tymczasowych.

W nowoczesnym C++ część takich kopii może być optymalizowana przez kompilator, ale sama idea pozostaje ważna.

## Domyślny konstruktor kopiujący a własny konstruktor kopiujący

Jeżeli klasa zawiera tylko proste pola, takie jak:

* `int`
* `double`
* `char`
* `std::string`

to domyślny konstruktor kopiujący bardzo często jest wystarczający.

Własny konstruktor kopiujący pisze się wtedy, gdy:

* chcemy dodać własną logikę kopiowania,
* chcemy śledzić moment kopiowania,
* klasa zarządza zasobem wymagającym specjalnego traktowania.

---

## Można zabronić kopiowania: `= delete`

Jeśli nie chcemy, aby obiekty danej klasy były kopiowane, można jawnie usunąć konstruktor kopiujący:

```cpp
class Fraction
{
public:
    Fraction(const Fraction&) = delete;
};
```

Wtedy instrukcje takie jak:

```cpp
Fraction fCopy{f};
```

spowodują błąd kompilacji.

### Dlaczego czasem usuwa się konstruktor kopiujący

Kopiowanie bywa zabronione wtedy, gdy obiekt reprezentuje coś unikalnego albo zarządza zasobem, którego nie wolno bezpiecznie skopiować w prosty sposób.

Przykłady:

* uchwyt do pliku,
* gniazdo sieciowe,
* mutex,
* obiekt zarządzający pojedynczym zasobem systemowym.

W takich sytuacjach kopiowanie mogłoby prowadzić do błędów logicznych albo do podwójnego zwalniania zasobu.

---

## Dlaczego własny konstruktor kopiujący bywa potrzebny przy wskaźnikach i tablicach

Najważniejszy powód pojawia się wtedy, gdy obiekt przechowuje **surowy wskaźnik** do dynamicznie zaalokowanej pamięci.

Na przykład:

```cpp
class Buffer
{
private:
    int* m_data;
    int m_size;
};
```

Jeśli taka klasa użyje domyślnego konstruktora kopiującego, skopiowany zostanie tylko sam adres zapisany we wskaźniku.

To oznacza, że po kopiowaniu:

* dwa obiekty będą wskazywać na ten sam blok pamięci,
* zmiana danych przez jeden obiekt wpłynie na drugi,
* przy niszczeniu obu obiektów może dojść do podwójnego `delete`, czyli bardzo groźnego błędu.

Takie kopiowanie nazywa się **kopiowaniem płytkim**.

### Kopiowanie płytkie

Przy kopiowaniu płytkim kopiowane są wartości pól dokładnie tak, jak są zapisane. Dla wskaźnika oznacza to skopiowanie adresu, a nie zawartości pamięci, na którą wskaźnik pokazuje.

### Kopiowanie głębokie

Jeżeli klasa ma własny konstruktor kopiujący, można w nim zaalokować nową pamięć i skopiować do niej dane. Wtedy każdy obiekt ma własną, niezależną kopię zasobu.

To nazywa się **kopiowaniem głębokim**.

Schematycznie mogłoby to wyglądać tak:

```cpp
Buffer(const Buffer& other)
    : m_size{ other.m_size }
{
    m_data = new int[m_size];
    for (int i = 0; i < m_size; ++i)
        m_data[i] = other.m_data[i];
}
```

Właśnie dlatego klasy zawierające:

* wskaźniki,
* dynamiczne tablice,
* własne zarządzanie pamięcią,
* uchwyty do zasobów,

często wymagają własnego konstruktora kopiującego albo całkowitego zakazu kopiowania.

---

## Uwaga praktyczna

W nowoczesnym C++ często unika się ręcznego zarządzania pamięcią przez użycie:

* `std::string`,
* `std::vector`,
* `std::unique_ptr`,
* `std::shared_ptr`.

Dzięki temu znacznie rzadziej trzeba pisać własny konstruktor kopiujący ręcznie. Jednak zrozumienie mechanizmu kopiowania nadal jest bardzo ważne.

## Podsumowanie

Programy `cw3-2.cpp` i `cw3-3.cpp` pokazują:

* czym jest konstruktor kopiujący,
* że kompilator może wygenerować konstruktor kopiujący automatycznie,
* jak wygląda własny konstruktor kopiujący,
* dlaczego parametr ma typ `const NazwaKlasy&`,
* że kopiowanie można jawnie zabronić przez `= delete`,
* dlaczego klasy zawierające wskaźniki lub dynamiczne tablice często wymagają własnej logiki kopiowania.

To bardzo ważny temat, ponieważ kopiowanie obiektów jest jedną z podstawowych operacji w C++, a błędne kopiowanie może prowadzić do trudnych do wykrycia błędów związanych z pamięcią i zasobami.
