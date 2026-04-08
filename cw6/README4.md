# `cw6-4.cpp` – kompozycja obiektów i organizacja kodu w plikach nagłówkowych

Ten przykład rozwija wcześniejszy program o kompozycji i pokazuje bardziej realistyczny sposób organizacji kodu w C++. Program składa się z kilku plików:

* `main.cpp`
* `Creature.h`
* `Point2D.h`

Dzięki temu kod jest podzielony na logiczne części: klasa punktu, klasa stwora oraz program główny korzystający z tych klas.

Program pokazuje jednocześnie dwa ważne zagadnienia:

1. **kompozycję obiektów** – obiekt `Creature` zawiera obiekt `Point2D`,
2. **użycie plików nagłówkowych** oraz zabezpieczeń przed wielokrotnym dołączeniem przy pomocy `#ifndef`, `#define` i `#endif`.

## Plik `main.cpp`

```cpp
#include <string>
#include <iostream>
#include "Creature.h"
#include "Point2D.h"

int main()
{
    std::cout << "Enter a name for your creature: ";
    std::string name;
    std::cin >> name;
    Creature creature{ name, { 4, 7 } };

    while (true)
    {
        // print the creature's name and location
        std::cout << creature << '\n';

        std::cout << "Enter new X location for creature (-1 to quit): ";
        int x{ 0 };
        std::cin >> x;
        if (x == -1)
            break;

        std::cout << "Enter new Y location for creature (-1 to quit): ";
        int y{ 0 };
        std::cin >> y;
        if (y == -1)
            break;

        creature.moveTo(x, y);
    }

    return 0;
}
```

## Plik `Creature.h`

```cpp
#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
#include <string>
#include <string_view>
#include "Point2D.h"

class Creature
{
private:
    std::string m_name;
    Point2D m_location;

public:
    Creature(std::string_view name, const Point2D& location)
        : m_name{ name }, m_location{ location }
    {
    }

    friend std::ostream& operator<<(std::ostream& out, const Creature& creature)
    {
        out << creature.m_name << " is at " << creature.m_location;
        return out;
    }

    void moveTo(int x, int y)
    {
        m_location.setPoint(x, y);
    }
};
#endif
```

## Plik `Point2D.h`

```cpp
#ifndef POINT2D_H
#define POINT2D_H

#include <iostream>

class Point2D
{
private:
    int m_x;
    int m_y;

public:
    // A default constructor
    Point2D()
        : m_x{ 0 }, m_y{ 0 }
    {
    }

    // A specific constructor
    Point2D(int x, int y)
        : m_x{ x }, m_y{ y }
    {
    }

    // An overloaded output operator
    friend std::ostream& operator<<(std::ostream& out, const Point2D& point)
    {
        out << '(' << point.m_x << ", " << point.m_y << ')';
        return out;
    }

    // Access functions
    void setPoint(int x, int y)
    {
        m_x = x;
        m_y = y;
    }

};

#endif
```

## Co pokazuje ten przykład

Program demonstruje:

* podział programu na kilka plików,
* definiowanie klas w plikach nagłówkowych,
* dołączanie nagłówków przez `#include`,
* kompozycję: `Creature` zawiera `Point2D`,
* przeciążenie operatora `<<` dla obu klas,
* zmianę stanu obiektu złożonego przez metodę `moveTo()`,
* zabezpieczenie nagłówków przed wielokrotnym dołączeniem.

## Kompozycja w tym programie

Najważniejsza relacja znajduje się w klasie `Creature`:

```cpp
Point2D m_location;
```

To oznacza, że każdy obiekt `Creature` **zawiera w sobie** obiekt `Point2D`.

Czyli:

* `Creature` jest obiektem bardziej złożonym,
* `Point2D` jest jego częścią składową,
* położenie stwora jest reprezentowane przez osobny obiekt punktu.

To właśnie jest **kompozycja**.

### Relacja „ma”

W tym przykładzie możemy powiedzieć:

* stwór **ma** położenie,
* położenie jest obiektem klasy `Point2D`.

Jest to relacja typu **has-a**, czyli typowa dla kompozycji.

## Dlaczego to jest kompozycja, a nie dziedziczenie

`Creature` nie jest szczególnym rodzajem `Point2D`.

Nie możemy powiedzieć:

* „stwór jest punktem”

bo to nie miałoby sensu.

Możemy natomiast powiedzieć:

* „stwór ma lokalizację będącą punktem”.

Dlatego tutaj poprawnym modelem jest kompozycja, a nie dziedziczenie.

## Inicjalizacja obiektu składowego

Konstruktor klasy `Creature` ma postać:

```cpp
Creature(std::string_view name, const Point2D& location)
    : m_name{ name }, m_location{ location }
{
}
```

To oznacza, że podczas tworzenia obiektu `Creature`:

* inicjalizowane jest pole `m_name`,
* inicjalizowany jest również obiekt `m_location`.

Pole `m_location` jest typu `Point2D`, więc konstruktor klasy `Creature` korzysta z przekazanego argumentu `location`, aby poprawnie utworzyć tę część obiektu.

To bardzo ważna cecha kompozycji: obiekty składowe są tworzone razem z obiektem złożonym.

## Jak działa `main()`

W programie głównym użytkownik wpisuje nazwę stwora:

```cpp
std::string name;
std::cin >> name;
```

Następnie tworzony jest obiekt:

```cpp
Creature creature{ name, { 4, 7 } };
```

Drugi argument `{ 4, 7 }` tworzy obiekt `Point2D` o współrzędnych:

* `x = 4`
* `y = 7`

Czyli od początku stwór ma nazwę nadaną przez użytkownika i pozycję `(4, 7)`.

## Jak działa wypisywanie obiektu `Creature`

W klasie `Creature` przeciążono operator `<<`:

```cpp
friend std::ostream& operator<<(std::ostream& out, const Creature& creature)
{
    out << creature.m_name << " is at " << creature.m_location;
    return out;
}
```

Warto zauważyć bardzo ważną rzecz:

```cpp
out << creature.m_location;
```

Tutaj wypisywany jest obiekt `Point2D`. Jest to możliwe, ponieważ także w klasie `Point2D` przeciążono operator `<<`.

To pokazuje współpracę klas:

* `Creature` korzysta z obiektu `Point2D`,
* operator wypisywania `Creature` korzysta z operatora wypisywania `Point2D`.

## Jak działa zmiana położenia

Metoda klasy `Creature`:

```cpp
void moveTo(int x, int y)
{
    m_location.setPoint(x, y);
}
```

nie zmienia bezpośrednio pól `m_x` i `m_y`, bo należą one do innego obiektu.

Zamiast tego `Creature` deleguje zmianę położenia do swojego obiektu składowego `m_location` przez metodę:

```cpp
m_location.setPoint(x, y);
```

To dobry przykład współpracy obiektu z jego częścią składową.

## Czas życia obiektów w kompozycji

Ponieważ `Point2D m_location;` jest zwykłym polem klasy `Creature`, to:

* `m_location` powstaje razem z obiektem `Creature`,
* `m_location` jest niszczony razem z obiektem `Creature`.

Nie jest to osobny obiekt zarządzany z zewnątrz przez wskaźnik. To integralna część obiektu `Creature`.

To jest jedna z najważniejszych cech kompozycji.

## Pliki nagłówkowe `.h`

W tym programie klasy zostały zapisane w osobnych plikach nagłówkowych:

* `Creature.h`
* `Point2D.h`

Plik nagłówkowy zwykle zawiera:

* deklarację klasy,
* definicje krótkich metod,
* deklaracje funkcji,
* potrzebne `#include`.

Dzięki temu program jest czytelniejszy i łatwiej go rozwijać.

### Dlaczego dzielimy kod na pliki

Podział na pliki pozwala:

* oddzielić logikę różnych klas,
* łatwiej utrzymywać kod,
* wielokrotnie używać tych samych klas w różnych programach,
* ograniczyć chaos w jednym dużym pliku.

## `#include` – dołączanie nagłówków

W `main.cpp` pojawia się:

```cpp
#include "Creature.h"
#include "Point2D.h"
```

To oznacza dołączenie definicji klas z tych plików do programu.

Cudzysłowy `"..."` oznaczają zwykle pliki użytkownika znajdujące się w projekcie, a nie standardowe nagłówki biblioteki.

W `Creature.h` z kolei znajduje się:

```cpp
#include "Point2D.h"
```

To jest konieczne, ponieważ klasa `Creature` zawiera pole typu `Point2D`, więc kompilator musi znać definicję tej klasy.

## `#ifndef`, `#define`, `#endif` – strażnicy nagłówków

Na początku `Creature.h` znajduje się:

```cpp
#ifndef CREATURE_H
#define CREATURE_H
```

A na końcu:

```cpp
#endif
```

Podobnie w `Point2D.h`:

```cpp
#ifndef POINT2D_H
#define POINT2D_H
...
#endif
```

To są tzw. **include guards**, czyli strażnicy nagłówków.

### Po co się ich używa

Gdyby ten sam plik nagłówkowy został dołączony więcej niż raz, kompilator mógłby zobaczyć wielokrotnie tę samą definicję klasy, co prowadziłoby do błędów kompilacji.

Na przykład:

* `main.cpp` dołącza `Creature.h`,
* `Creature.h` dołącza `Point2D.h`,
* a `main.cpp` dodatkowo też dołącza `Point2D.h`.

Bez zabezpieczenia `Point2D.h` mógłby zostać przetworzony dwa razy.

### Jak działa `#ifndef`

Instrukcja:

```cpp
#ifndef POINT2D_H
```

znaczy:

* jeśli symbol `POINT2D_H` nie jest jeszcze zdefiniowany, wykonaj dalszą część pliku.

Następnie:

```cpp
#define POINT2D_H
```

ustawia ten symbol.

Przy kolejnym dołączeniu tego samego pliku warunek `#ifndef POINT2D_H` będzie już fałszywy, więc zawartość pliku zostanie pominięta.

### Schemat działania

Typowy schemat strażnika nagłówka wygląda tak:

```cpp
#ifndef NAZWA_NAGLOWKA_H
#define NAZWA_NAGLOWKA_H

// zawartość pliku

#endif
```

To jeden z podstawowych mechanizmów organizacji kodu w C++.

## Uwaga praktyczna

W `main.cpp` dołączono zarówno `Creature.h`, jak i `Point2D.h`:

```cpp
#include "Creature.h"
#include "Point2D.h"
```

Ponieważ `Creature.h` już sam dołącza `Point2D.h`, ten drugi `#include` w `main.cpp` nie jest konieczny do poprawnego działania programu. Nie szkodzi on jednak właśnie dzięki strażnikom nagłówków.

To dobry praktyczny przykład pokazujący, po co `#ifndef` i `#define` są potrzebne.

## Wynik działania programu

Jeśli użytkownik wpisze na przykład nazwę:

```text
Smok
```

program utworzy obiekt na pozycji `(4, 7)` i wypisze coś w rodzaju:

```text
Enter a name for your creature: Smok
Smok is at (4, 7)
Enter new X location for creature (-1 to quit):
```

Po podaniu nowych współrzędnych program będzie aktualizował położenie stwora i wypisywał jego nowy stan.

## Podsumowanie

Program `cw6-4.cpp` pokazuje:

* kompozycję obiektów (`Creature` zawiera `Point2D`),
* relację „obiekt ma inny obiekt jako część”,
* inicjalizację obiektu składowego przez listę inicjalizacyjną,
* współpracę klas przez metody i przeciążony operator `<<`,
* organizację programu w osobnych plikach nagłówkowych,
* użycie `#include` do dołączania klas,
* użycie `#ifndef`, `#define` i `#endif` do ochrony przed wielokrotnym dołączeniem plików.

Jest to bardzo dobry, bardziej realistyczny przykład pokazujący jednocześnie programowanie obiektowe i podstawy organizacji większego projektu w C++.
