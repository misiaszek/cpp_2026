# `cw2-6.cpp` – pierwszy konstruktor klasy

Program wprowadza pojęcie **konstruktora** w C++. Konstruktor to specjalna funkcja składowa klasy, która jest wywoływana automatycznie podczas tworzenia obiektu. W tym przykładzie klasa `Foo` ma konstruktor przyjmujący dwa argumenty: `x` oraz `y`.

## Kod programu

```cpp
#include <iostream>

class Foo
{
private:
    int m_x {};
    int m_y {};

public:
    Foo(int x, int y) // here's our constructor function that takes two initializers
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
    Foo foo{ 6, 7 }; // calls Foo(int, int) constructor
    foo.print();

    return 0;
}
```

## Co pokazuje ten przykład

Klasa `Foo` zawiera dwa prywatne pola danych:

* `m_x`
* `m_y`

oraz:

* konstruktor `Foo(int x, int y)`,
* metodę `print()`.

Najważniejszym nowym elementem jest konstruktor, czyli funkcja o takiej samej nazwie jak klasa.

## Konstruktor

```cpp
Foo(int x, int y)
{
    std::cout << "Foo(" << x << ", " << y << ") constructed\n";
}
```

Konstruktor:

* ma taką samą nazwę jak klasa, czyli `Foo`,
* nie ma typu zwracanego,
* jest uruchamiany automatycznie w chwili tworzenia obiektu.

W tym przykładzie konstruktor przyjmuje dwa argumenty i wypisuje informację na ekran:

```text
Foo(6, 7) constructed
```

To pokazuje, że konstruktor rzeczywiście został wywołany podczas tworzenia obiektu `foo`.

## Ważna obserwacja

Chociaż konstruktor otrzymuje wartości `x` i `y`, to w jego wnętrzu **nie przypisuje ich** do pól `m_x` i `m_y`.

Oznacza to, że pola klasy pozostają zainicjalizowane swoimi wartościami domyślnymi:

```cpp
int m_x {};
int m_y {};
```

Ponieważ użyto `{}`, oba pola zostają zainicjalizowane wartością `0`.

Dlatego konstruktor wypisuje jedną parę wartości, ale obiekt przechowuje inną.

## Metoda `print()`

```cpp
void print() const
{
    std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
}
```

Metoda `print()` wypisuje aktualne wartości pól `m_x` i `m_y` obiektu.

Ponieważ konstruktor nie przypisał do nich wartości `x` i `y`, metoda wypisze:

```text
Foo(0, 0)
```

Metoda jest oznaczona jako `const`, ponieważ nie zmienia stanu obiektu.

## Funkcja `main()`

```cpp
int main()
{
    Foo foo{ 6, 7 };
    foo.print();

    return 0;
}
```

W funkcji `main`:

1. tworzony jest obiekt `foo`,
2. do konstruktora przekazywane są argumenty `6` i `7`,
3. konstruktor wypisuje komunikat,
4. następnie wywoływana jest metoda `print()`, która pokazuje rzeczywisty stan obiektu.

## Wynik działania programu

Program wypisze:

```text
Foo(6, 7) constructed
Foo(0, 0)
```

Pierwsza linia pochodzi z konstruktora i pokazuje wartości argumentów przekazanych przy tworzeniu obiektu.

Druga linia pochodzi z metody `print()` i pokazuje wartości pól `m_x` i `m_y`, które nadal wynoszą `0`.

## Dlaczego ten przykład jest ważny

To ćwiczenie pokazuje bardzo ważną rzecz: **przyjęcie argumentów przez konstruktor nie oznacza jeszcze automatycznego zapisania ich do pól klasy**.

Aby obiekt rzeczywiście przechowywał przekazane wartości, konstruktor musi je jawnie przypisać do pól, na przykład:

```cpp
Foo(int x, int y)
{
    m_x = x;
    m_y = y;
}
```

Dopiero wtedy stan obiektu odpowiadałby przekazanym argumentom.

## Co można poprawić

Obecna wersja konstruktora ma charakter dydaktyczny, ponieważ pokazuje różnicę między:

* argumentami przekazanymi do konstruktora,
* rzeczywistym stanem pól obiektu.

Praktyczna wersja klasy powinna zapisywać te wartości do `m_x` i `m_y`.

Jeszcze lepiej byłoby użyć **listy inicjalizacyjnej konstruktora**, co jest idiomatycznym rozwiązaniem w C++:

```cpp
Foo(int x, int y)
    : m_x{x}, m_y{y}
{
    std::cout << "Foo(" << x << ", " << y << ") constructed\n";
}
```

## Podsumowanie

Program `cw2-6.cpp` pokazuje:

* czym jest konstruktor klasy,
* kiedy konstruktor jest wywoływany,
* że konstruktor może przyjmować argumenty,
* że pola klasy nie zmieniają się same od przyjęcia argumentów,
* różnicę między argumentami konstruktora a stanem obiektu.

Jest to bardzo ważny przykład wprowadzający do świadomego inicjalizowania obiektów w C++.
