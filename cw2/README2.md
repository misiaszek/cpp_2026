# `cw2-2.cpp` – opis programu

## Przegląd ogólny

Program pokazuje użycie **funkcji członkowskiej** (metody) w strukturze `struct` w C++.  
Struktura `Date` przechowuje datę złożoną z trzech pól: roku, miesiąca i dnia, a dodatkowo zawiera metodę `print()`, która wypisuje zawartość obiektu.

W porównaniu z `cw2-1.cpp` najważniejsza zmiana polega na tym, że funkcja wypisująca datę została przeniesiona do wnętrza struktury. Dzięki temu staje się ona częścią definiowanego typu.

## Kod programu

~~~cpp
// Member function version
#include <iostream>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print() // defines a member function named print
    {
        std::cout << year << '/' << month << '/' << day;
    }
};

int main()
{
    Date today { 2020, 10, 14 }; // aggregate initialize our struct

    today.day = 16; // member variables accessed using member selection operator (.)
    today.print();  // member functions also accessed using member selection operator (.)

    return 0;
}
~~~

## Struktura `Date`

~~~cpp
struct Date
{
    int year {};
    int month {};
    int day {};

    void print()
    {
        std::cout << year << '/' << month << '/' << day;
    }
};
~~~

Struktura `Date` zawiera:

- trzy pola danych:
  - `year` – rok,
  - `month` – miesiąc,
  - `day` – dzień,
- jedną funkcję członkowską:
  - `print()` – wypisuje datę.

Zapis `{}` przy polach oznacza, że jeśli nie zostaną one jawnie zainicjalizowane inną wartością, otrzymają wartość `0`.

Podobnie jak w poprzednim przykładzie, pola i metoda są domyślnie publiczne, ponieważ zostały zdefiniowane w `struct`.

## Funkcja członkowska `print()`

~~~cpp
void print()
{
    std::cout << year << '/' << month << '/' << day;
}
~~~

Funkcja `print()` jest metodą członkowską struktury `Date`.  
Oznacza to, że należy do obiektu tego typu i może bezpośrednio korzystać z jego pól:

- `year`
- `month`
- `day`

Nie trzeba więc przekazywać obiektu jako argumentu, tak jak w `cw2-1.cpp`.

To jedna z istotnych cech C++: typ może zawierać nie tylko dane, ale także operacje związane z tymi danymi.

## Funkcja `main()`

~~~cpp
int main()
{
    Date today { 2020, 10, 14 };

    today.day = 16;
    today.print();

    return 0;
}
~~~

W funkcji `main` tworzony jest obiekt `today` typu `Date`:

~~~cpp
Date today { 2020, 10, 14 };
~~~

Jest to inicjalizacja agregatu, czyli przypisanie kolejnych wartości do kolejnych pól struktury:

- `2020` → `year`
- `10` → `month`
- `14` → `day`

Następnie zmieniana jest wartość pola `day`:

~~~cpp
today.day = 16;
~~~

Na końcu wywoływana jest metoda członkowska:

~~~cpp
today.print();
~~~

Wywołanie odbywa się przy użyciu operatora `.`.  
Ten sam operator służy zarówno do dostępu do pól obiektu, jak i do wywoływania jego metod.

## Wynik działania programu

Program wypisze:

~~~text
2020/10/16
~~~

Podobnie jak w `cw2-1.cpp`, dzień początkowo miał wartość `14`, ale został zmieniony na `16`, dlatego końcowy wynik to `2020/10/16`.

## Najważniejsza różnica względem `cw2-1.cpp`

W `cw2-1.cpp` wypisywanie daty było realizowane przez osobną funkcję zewnętrzną:

~~~cpp
print(today);
~~~

W `cw2-2.cpp` funkcja `print` została przeniesiona do wnętrza struktury i stała się metodą:

~~~cpp
today.print();
~~~

Z punktu widzenia działania programów rezultat jest taki sam.  
Różnica dotyczy organizacji kodu: operacja wypisywania została bezpośrednio powiązana z typem `Date`.

## C++ a C

W **C++** można umieszczać funkcje wewnątrz definicji klasy lub struktury. Takie funkcje nazywa się **funkcjami członkowskimi** albo **metodami**.

Metody:

- są częścią typu,
- mogą bezpośrednio odwoływać się do pól obiektu,
- są wywoływane przy użyciu operatora `.` lub `->`.

W **C** struktury przechowują tylko dane. Nie istnieje tam językowy mechanizm metod powiązanych ze strukturą.  
Aby uzyskać podobny efekt, pisze się zwykłe funkcje zewnętrzne, które przyjmują strukturę albo wskaźnik do niej jako argument.

Dlatego `cw2-2.cpp` pokazuje cechę charakterystyczną dla C++: możliwość łączenia danych i zachowania w obrębie jednego typu.

## Kluczowe pojęcia pokazane w przykładzie

### Funkcja członkowska

Metoda to funkcja zdefiniowana wewnątrz struktury lub klasy. Jest logicznie związana z danym typem.

### Operator `.`

Operator `.` służy zarówno do odczytu i modyfikacji pól, jak i do wywoływania metod:

~~~cpp
today.day = 16;
today.print();
~~~

### Łączenie danych i zachowania

Struktura `Date` nie tylko przechowuje dane, ale również udostępnia operację wykonywaną na tych danych. To ważny krok w stronę programowania obiektowego.

## Podsumowanie

Program `cw2-2.cpp` rozwija poprzedni przykład o metodę członkowską `print()`.  
Pokazuje on, że w C++ struktura może zawierać nie tylko dane, ale również funkcje związane z tymi danymi.

Najważniejsze elementy tego przykładu to:

- definicja struktury z polami,
- dodanie metody członkowskiej,
- inicjalizacja obiektu,
- modyfikacja pola,
- wywołanie metody na obiekcie.

Jest to prosty przykład pokazujący, jak w C++ można organizować kod wokół własnych typów danych w bardziej naturalny sposób niż przy użyciu samych funkcji zewnętrznych.