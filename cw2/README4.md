# `cw2-4.cpp` – gettery i settery w klasie

Program pokazuje, jak udostępniać kontrolowany dostęp do prywatnych pól klasy za pomocą **getterów** i **setterów**. To kolejny krok po enkapsulacji z poprzedniego przykładu: dane nadal są ukryte wewnątrz klasy, ale można je odczytywać i modyfikować przez publiczny interfejs.

## Kod programu

```cpp
#include <iostream>

class Date
{
private:
    int m_year { 2020 };
    int m_month { 10 };
    int m_day { 14 };

public:
    void print()
    {
        std::cout << m_year << '/' << m_month << '/' << m_day << '\n';
    }

    int getYear() const { return m_year; }        // getter for year
    void setYear(int year) { m_year = year; }     // setter for year

    int getMonth() const  { return m_month; }     // getter for month
    void setMonth(int month) { m_month = month; } // setter for month

    int getDay() const { return m_day; }          // getter for day
    void setDay(int day) { m_day = day; }         // setter for day
};

int main()
{
    Date d{};
    d.setYear(2021);
    std::cout << "The year is: " << d.getYear() << '\n';

    return 0;
}
```

## Co pokazuje ten przykład

W klasie `Date` pola `m_year`, `m_month` i `m_day` są nadal umieszczone w sekcji `private`, więc kod zewnętrzny nie ma do nich bezpośredniego dostępu.

Zamiast tego klasa udostępnia metody publiczne:

* `getYear()`, `getMonth()`, `getDay()` – służą do odczytu wartości,
* `setYear()`, `setMonth()`, `setDay()` – służą do zmiany wartości.

To klasyczny przykład użycia **getterów** i **setterów**.

## Struktura klasy

```cpp
class Date
{
private:
    int m_year { 2020 };
    int m_month { 10 };
    int m_day { 14 };

public:
    void print()
    {
        std::cout << m_year << '/' << m_month << '/' << m_day << '\n';
    }

    int getYear() const { return m_year; }
    void setYear(int year) { m_year = year; }

    int getMonth() const { return m_month; }
    void setMonth(int month) { m_month = month; }

    int getDay() const { return m_day; }
    void setDay(int day) { m_day = day; }
};
```

Klasa zawiera:

* trzy prywatne pola danych,
* metodę `print()`, która wypisuje całą datę,
* trzy gettery do odczytu pól,
* trzy settery do modyfikacji pól.

## Gettery

Getter to metoda, która zwraca wartość prywatnego pola.

Przykład:

```cpp
int getYear() const { return m_year; }
```

Ta metoda:

* zwraca aktualną wartość pola `m_year`,
* jest oznaczona jako `const`, więc nie zmienia stanu obiektu.

Analogicznie działają:

* `getMonth()`
* `getDay()`

Dzięki getterom można odczytywać dane klasy bez naruszania zasady enkapsulacji.

## Settery

Setter to metoda, która pozwala zmienić wartość prywatnego pola.

Przykład:

```cpp
void setYear(int year) { m_year = year; }
```

Ta metoda przyjmuje nową wartość i przypisuje ją do pola `m_year`.

Analogicznie działają:

* `setMonth(int month)`
* `setDay(int day)`

W tym przykładzie settery nie sprawdzają poprawności danych. Oznacza to, że można ustawić nawet nielogiczne wartości, na przykład miesiąc równy `50`. To ważna obserwacja: sam setter jeszcze nie gwarantuje poprawności danych, ale daje miejsce, w którym można później dodać walidację.

## Funkcja `main()`

```cpp
int main()
{
    Date d{};
    d.setYear(2021);
    std::cout << "The year is: " << d.getYear() << '\n';

    return 0;
}
```

W funkcji `main`:

1. tworzony jest obiekt `Date d{}`,
2. wywoływany jest setter `setYear(2021)`, który zmienia rok z `2020` na `2021`,
3. następnie wywoływany jest getter `getYear()`, którego wynik zostaje wypisany na ekran.

## Wynik działania programu

Program wypisze:

```text
The year is: 2021
```

Warto zauważyć, że program nie wypisuje całej daty, mimo że klasa ma metodę `print()`. W `main` użyto tylko gettera `getYear()`, więc na ekran trafia wyłącznie rok.

## Dlaczego gettery i settery są ważne

Gdyby pola klasy były publiczne, można byłoby pisać bezpośrednio:

```cpp
d.m_year = 2021;
```

ale przy polach prywatnych jest to zabronione. Zamiast tego korzysta się z metod publicznych.

Takie podejście ma kilka zalet:

* chroni dane przed przypadkową bezpośrednią zmianą,
* pozwala kontrolować sposób odczytu i modyfikacji pól,
* umożliwia dodanie walidacji bez zmieniania kodu używającego klasy,
* oddziela wewnętrzną reprezentację danych od publicznego interfejsu.

Na przykład w przyszłości setter można rozbudować tak:

```cpp
void setMonth(int month)
{
    if (month >= 1 && month <= 12)
        m_month = month;
}
```

Dzięki temu kod korzystający z klasy nadal wywołuje `setMonth(...)`, ale klasa zaczyna pilnować poprawności danych.

## Znaczenie `const` w getterach

Gettery zostały zadeklarowane jako metody `const`, na przykład:

```cpp
int getDay() const
```

Oznacza to, że metoda nie może zmienić stanu obiektu. To naturalne dla funkcji, których zadaniem jest tylko odczyt wartości.

Stosowanie `const` zwiększa czytelność kodu i pomaga kompilatorowi wykrywać błędy.

## Podsumowanie

Program `cw2-4.cpp` pokazuje:

* prywatne pola klasy,
* publiczne gettery i settery,
* odczyt i modyfikację danych przez interfejs klasy,
* praktyczne zastosowanie enkapsulacji.

Jest to ważny etap w nauce programowania obiektowego w C++, ponieważ pokazuje, jak ukryć dane i jednocześnie bezpiecznie udostępnić do nich dostęp za pomocą metod klasy.
