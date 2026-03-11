# `cw2-5.cpp` – spójność danych w klasie

Program pokazuje, dlaczego w klasach warto ukrywać dane i modyfikować je wyłącznie przez metody. Klasa `Employee` przechowuje dwa powiązane ze sobą pola: pełne imię pracownika oraz jego pierwszą literę. Metoda `setName()` dba o to, aby obie te informacje były zawsze ze sobą zgodne.

## Kod programu

```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee // members are private by default
{
    std::string m_name{};
    char m_firstInitial{};

public:
    void setName(std::string_view name)
    {
        m_name = name;
        m_firstInitial = name.front(); // use std::string::front() to get first letter of `name`
    }

    void print() const
    {
        std::cout << "Employee " << m_name << " has first initial " << m_firstInitial << '\n';
    }
};

int main()
{
    Employee e{};
    e.setName("John");
    e.print();

    e.setName("Mark");
    e.print();

    return 0;
}
```

## Co pokazuje ten przykład

Klasa `Employee` zawiera dwa prywatne pola:

* `m_name` – pełne imię pracownika,
* `m_firstInitial` – pierwszą literę imienia.

Te dwie wartości są ze sobą logicznie powiązane. Jeśli imię wynosi `John`, to pierwsza litera powinna być `J`. Jeśli później imię zostanie zmienione na `Mark`, pierwsza litera również powinna zostać automatycznie zmieniona na `M`.

Właśnie dlatego program nie pozwala zmieniać tych pól bezpośrednio z zewnątrz. Zamiast tego udostępnia metodę `setName()`, która aktualizuje oba pola jednocześnie.

## Struktura klasy `Employee`

```cpp
class Employee
{
    std::string m_name{};
    char m_firstInitial{};

public:
    void setName(std::string_view name)
    {
        m_name = name;
        m_firstInitial = name.front();
    }

    void print() const
    {
        std::cout << "Employee " << m_name << " has first initial " << m_firstInitial << '\n';
    }
};
```

W klasie:

* pola są prywatne domyślnie, ponieważ użyto `class`,
* metoda `setName()` służy do ustawiania danych,
* metoda `print()` służy do wyświetlania stanu obiektu.

## Metoda `setName()`

```cpp
void setName(std::string_view name)
{
    m_name = name;
    m_firstInitial = name.front();
}
```

Metoda `setName()` przyjmuje parametr typu `std::string_view`, czyli lekki obiekt reprezentujący widok na tekst. Dzięki temu można wygodnie przekazywać napisy bez konieczności tworzenia niepotrzebnych kopii wejściowego argumentu.

Wewnątrz metody wykonywane są dwie operacje:

1. pełne imię jest zapisywane do pola `m_name`,
2. pierwsza litera tego imienia jest pobierana za pomocą `name.front()` i zapisywana do pola `m_firstInitial`.

Dzięki temu po każdej zmianie imienia oba pola pozostają spójne.

## `std::string_view`

Parametr metody ma typ:

```cpp
std::string_view name
```

`std::string_view` to typ wprowadzony w C++17. Reprezentuje on tylko widok na istniejący ciąg znaków, bez przejmowania jego własności.

W tym przykładzie jego użycie jest wygodne, ponieważ do `setName()` można przekazać na przykład:

* literał tekstowy, jak `"John"`,
* obiekt `std::string`,
* inny fragment tekstu.

Następnie zawartość tego widoku jest kopiowana do pola `m_name`, które jest typu `std::string`.

## `name.front()`

Instrukcja:

```cpp
m_firstInitial = name.front();
```

pobiera pierwszy znak z przekazanego tekstu.

Dla napisu `"John"` będzie to znak `J`, a dla `"Mark"` znak `M`.

Warto pamiętać, że `front()` zakłada, że napis nie jest pusty. W tym przykładzie program działa poprawnie, bo przekazywane imiona nie są puste. W bardziej rozbudowanym programie należałoby dodać sprawdzenie, czy `name` rzeczywiście zawiera co najmniej jeden znak.

## Metoda `print()`

```cpp
void print() const
{
    std::cout << "Employee " << m_name << " has first initial " << m_firstInitial << '\n';
}
```

Metoda `print()` wypisuje aktualny stan obiektu.

Została oznaczona jako `const`, ponieważ nie zmienia danych obiektu – jedynie je odczytuje.

## Funkcja `main()`

```cpp
int main()
{
    Employee e{};
    e.setName("John");
    e.print();

    e.setName("Mark");
    e.print();

    return 0;
}
```

W funkcji `main`:

1. tworzony jest obiekt `Employee e{}`,
2. wywołanie `e.setName("John")` ustawia imię oraz pierwszą literę,
3. `e.print()` wypisuje stan obiektu,
4. następnie imię zostaje zmienione na `Mark`,
5. kolejne wywołanie `print()` pokazuje nowy, nadal spójny stan obiektu.

## Wynik działania programu

Program wypisze:

```text
Employee John has first initial J
Employee Mark has first initial M
```

## Dlaczego ten przykład jest ważny

To ćwiczenie pokazuje ważną zaletę enkapsulacji: klasa może pilnować własnych zależności wewnętrznych.

Gdyby pola `m_name` i `m_firstInitial` były publiczne, można byłoby przypadkowo stworzyć niespójny obiekt, na przykład taki:

```cpp
m_name = "Mark";
m_firstInitial = 'J';
```

Taki stan byłby błędny logicznie. Dzięki prywatnym polom i metodzie `setName()` klasa sama dba o to, by takie sytuacje nie wystąpiły.

## Możliwe ulepszenia

Ten przykład można dalej rozwinąć, na przykład przez:

* dodanie sprawdzenia, czy przekazane imię nie jest puste,
* dodanie gettera `getName()`,
* dodanie gettera `getFirstInitial()`,
* walidację danych wejściowych.

Przykładowo bezpieczniejsza wersja `setName()` mogłaby najpierw sprawdzać, czy `name.empty()` nie jest prawdą.

## Podsumowanie

Program `cw2-5.cpp` pokazuje:

* użycie prywatnych pól klasy,
* aktualizowanie kilku powiązanych danych w jednej metodzie,
* użycie `std::string_view` jako parametru,
* użycie `front()` do pobrania pierwszego znaku,
* utrzymywanie spójności stanu obiektu.

Jest to bardzo dobry przykład pokazujący, że metody klasy nie służą tylko do ukrywania danych, ale także do pilnowania wewnętrznej poprawności obiektu.
