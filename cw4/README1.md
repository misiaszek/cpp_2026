# `cw4-1.cpp` – inicjalizacja i wypisywanie tablicy `std::array`

Program pokazuje podstawowe użycie kontenera `std::array` w C++. Demonstruje on:

- deklarację tablicy o stałym rozmiarze,
- inicjalizację jej elementów przy pomocy listy inicjalizacyjnej,
- odczyt rozmiaru tablicy metodą `size()`,
- dostęp do elementów przez operator `[]`,
- wypisywanie danych w postaci prostej tabeli z użyciem `setw()`.

## Kod programu

```cpp
// Initializing an array in a declaration.
#include <iostream>
#include <iomanip>
#include <array>
using namespace std;

int main()
{
   // use list initializer to initialize array n
   array< int, 5 > n = { 32, 27, 64, 18, 95 };

   cout << "Element" << setw( 13 ) << "Value" << endl;

   // output each array element's value
   for ( size_t i = 0; i < n.size(); ++i )
      cout << setw( 7 ) << i << setw( 13 ) << n[ i ] << endl;
} // end main

//Inicjalizacja samych wartosci 0
//array< int, 5 > n = {}; // initialize elements of array n to 0
```

## Co pokazuje ten przykład

Najważniejszym elementem programu jest deklaracja:

```cpp
array< int, 5 > n = { 32, 27, 64, 18, 95 };
```

Oznacza ona utworzenie obiektu `n`, który jest tablicą pięciu liczb całkowitych typu `int`.

Typ `std::array<int, 5>` oznacza:

- `int` – typ przechowywanych elementów,
- `5` – liczbę elementów tablicy.

Wartości w nawiasach klamrowych inicjalizują kolejne elementy tablicy:

- `n[0] = 32`
- `n[1] = 27`
- `n[2] = 64`
- `n[3] = 18`
- `n[4] = 95`

## `std::array`

`std::array` to kontener z biblioteki standardowej, który reprezentuje tablicę o stałym rozmiarze.

W odróżnieniu od zwykłej tablicy w stylu C:

```cpp
int n[5] = { 32, 27, 64, 18, 95 };
```

`std::array` jest pełnoprawnym obiektem i udostępnia wygodne metody, takie jak:

- `size()` – zwraca liczbę elementów,
- `at()` – dostęp do elementu z kontrolą zakresu,
- `front()` – pierwszy element,
- `back()` – ostatni element.

W tym programie użyta została metoda:

```cpp
n.size()
```

która zwraca rozmiar tablicy, czyli `5`.

## Pętla `for`

Program wypisuje elementy tablicy za pomocą pętli:

```cpp
for ( size_t i = 0; i < n.size(); ++i )
    cout << setw( 7 ) << i << setw( 13 ) << n[ i ] << endl;
```

Zmiennej `i` używa się tutaj jako indeksu tablicy.

Kolejne przebiegi pętli odpowiadają elementom:

- `n[0]`
- `n[1]`
- `n[2]`
- `n[3]`
- `n[4]`

Typ `size_t` jest odpowiedni do przechowywania indeksów i rozmiarów obiektów w C++.

## Dostęp do elementów: `n[i]`

Operator:

```cpp
n[i]
```

umożliwia odczyt elementu tablicy o indeksie `i`.

W tym przykładzie program wypisuje każdą parę:

- numer elementu,
- wartość przechowywaną pod tym indeksem.

## Formatowanie wyjścia: `setw()`

Do wyrównania kolumn użyto funkcji `setw()` z nagłówka `<iomanip>`:

```cpp
cout << "Element" << setw( 13 ) << "Value" << endl;
```

oraz:

```cpp
cout << setw( 7 ) << i << setw( 13 ) << n[ i ] << endl;
```

`setw()` ustawia szerokość następnego wypisywanego pola. Dzięki temu wynik ma formę czytelnej tabeli.

## Wynik działania programu

Program wypisze:

```text
Element        Value
      0           32
      1           27
      2           64
      3           18
      4           95
```

Dokładne odstępy zależą od sposobu formatowania, ale sens wyniku pozostaje taki sam: po lewej stronie znajduje się indeks elementu, a po prawej jego wartość.

## Inicjalizacja zerami

Na końcu programu znajduje się komentarz:

```cpp
//array< int, 5 > n = {}; // initialize elements of array n to 0
```

Taki zapis oznacza, że wszystkie elementy tablicy zostaną zainicjalizowane wartością `0`.

Czyli po takiej deklaracji tablica zawierałaby:

```text
0, 0, 0, 0, 0
```

To wygodny sposób tworzenia tablicy z wyzerowanymi elementami.

## Dlaczego ten przykład jest ważny

Program wprowadza kilka podstawowych pojęć potrzebnych do pracy z tablicami w nowoczesnym C++:

- użycie `std::array` zamiast surowej tablicy w stylu C,
- iterowanie po elementach tablicy,
- odczytywanie rozmiaru tablicy bez ręcznego liczenia,
- estetyczne wypisywanie danych.

To dobry pierwszy krok przed bardziej zaawansowaną pracą z kolekcjami danych.

## Podsumowanie

Program `cw4-1.cpp` pokazuje:

- deklarację `std::array<int, 5>`,
- inicjalizację wartościami przy pomocy listy inicjalizacyjnej,
- użycie `size()` do pobrania liczby elementów,
- dostęp do elementów przez `operator[]`,
- formatowanie tekstu przez `setw()`.

Jest to prosty, ale bardzo ważny przykład pokazujący, jak w C++ przechowywać kilka wartości tego samego typu w uporządkowanej strukturze danych i wygodnie je wypisywać.
