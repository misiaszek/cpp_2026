# `cw2-1.cpp` – opis programu

## Przegląd ogólny

Program pokazuje podstawowe użycie struktury (`struct`) w C++. Struktura `Date` służy do przechowywania prostej daty złożonej z trzech pól: roku, miesiąca i dnia.

Przykład demonstruje:

* definiowanie struktury,
* tworzenie obiektu tego typu,
* dostęp do pól za pomocą operatora `.`,
* przekazywanie struktury do funkcji,
* wyświetlanie zawartości obiektu.

## Kod programu

```cpp
#include <iostream>

struct Date
{
    int year {};
    int month {};
    int day {};
};

void print(const Date& date)
{
    std::cout << date.year << '/' << date.month << '/' << date.day;
}

int main()
{
    Date today { 2020, 10, 14 };

    today.day = 16;
    print(today);

    return 0;
}
```

## Struktura `Date`

```cpp
struct Date
{
    int year {};
    int month {};
    int day {};
};
```

Struktura `Date` zawiera trzy pola:

* `year` – rok,
* `month` – miesiąc,
* `day` – dzień.

Zapis `{}` przy każdym polu oznacza, że jeśli dane pole nie otrzyma innej wartości podczas tworzenia obiektu, zostanie zainicjalizowane wartością `0`.

W tym przykładzie pola struktury są dostępne bezpośrednio z zewnątrz, ponieważ w `struct` domyślny poziom dostępu to `public`.

## Funkcja `print()`

```cpp
void print(const Date& date)
{
    std::cout << date.year << '/' << date.month << '/' << date.day;
}
```

Funkcja `print` przyjmuje argument typu `const Date&`, czyli:

* obiekt jest przekazywany przez referencję, więc nie jest kopiowany,
* słowo kluczowe `const` gwarantuje, że funkcja nie zmieni przekazanego obiektu.

Wewnątrz funkcji pola struktury są odczytywane za pomocą operatora `.`:

```cpp
date.year
date.month
date.day
```

Funkcja wypisuje datę w formacie:

```text
rok/miesiąc/dzień
```

## Funkcja `main()`

```cpp
int main()
{
    Date today { 2020, 10, 14 };

    today.day = 16;
    print(today);

    return 0;
}
```

W funkcji `main` tworzony jest obiekt `today` typu `Date`:

```cpp
Date today { 2020, 10, 14 };
```

Jest to przykład inicjalizacji agregatu. Wartości w nawiasach klamrowych są przypisywane kolejno do pól struktury:

* `2020` → `year`
* `10` → `month`
* `14` → `day`

Następnie program modyfikuje jedno z pól:

```cpp
today.day = 16;
```

To pokazuje, że do pól struktury można odwoływać się bezpośrednio i zmieniać ich wartości.

Na końcu obiekt `today` zostaje przekazany do funkcji `print`:

```cpp
print(today);
```

## Wynik działania programu

Program wypisze:

```text
2020/10/16
```

Początkowo dzień miał wartość `14`, ale został zmieniony na `16`, dlatego wypisany wynik zawiera już nową wartość.

## Kluczowe pojęcia pokazane w przykładzie

### Struktura (`struct`)

`struct` pozwala zgrupować kilka powiązanych danych w jednym typie. W tym przykładzie struktura `Date` przechowuje trzy elementy opisujące datę.

### Pola struktury

Zmienne `year`, `month` i `day` są polami struktury. Każdy obiekt typu `Date` posiada własne wartości tych pól.

### Operator `.`

Operator `.` służy do odwoływania się do pól obiektu:

```cpp
today.day = 16;
date.year
```

### Przekazywanie przez referencję do `const`

Parametr:

```cpp
const Date& date
```

oznacza, że funkcja korzysta z istniejącego obiektu bez jego kopiowania i jednocześnie nie może go zmieniać.

### Inicjalizacja agregatu

Zapis:

```cpp
Date today { 2020, 10, 14 };
```

oznacza utworzenie obiektu i przypisanie wartości do jego pól w kolejności ich deklaracji.

## Uwaga o `struct` i `class`

Ten przykład dotyczy struktury, ale warto pamiętać, że w C++ różnica między `struct` a `class` jest mniejsza, niż mogłoby się wydawać.

Najważniejsza różnica domyślna jest taka:

* w `struct` elementy są domyślnie `public`,
* w `class` elementy są domyślnie `private`.

Oznacza to, że `struct` w C++ nie służy wyłącznie do „prostych danych” i również może zawierać metody, konstruktory czy elementy prywatne. W tym przykładzie użyto jednak najprostszego wariantu: struktury z publicznymi polami oraz osobnej funkcji operującej na obiekcie.

## Podsumowanie

Program `cw2-1.cpp` jest prostym wprowadzeniem do pracy ze strukturami w C++. Pokazuje on, jak:

* zdefiniować własny typ danych,
* utworzyć jego obiekt,
* zainicjalizować pola,
* zmienić wartość jednego z pól,
* przekazać obiekt do funkcji,
* wypisać jego zawartość.

Jest to podstawowy przykład ilustrujący, jak w C++ można grupować powiązane dane w jednym typie i operować na nich w czytelny sposób.
