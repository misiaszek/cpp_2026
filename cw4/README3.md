# `cw4-3.cpp` – obliczanie sumy elementów tablicy

Program pokazuje, jak przejść po wszystkich elementach tablicy `std::array` i obliczyć ich sumę. Jest to jeden z najczęstszych i najważniejszych wzorców pracy z tablicami: iteracja po elementach oraz akumulowanie wyniku w osobnej zmiennej.

## Kod programu

```cpp
// Compute the sum of the elements of an array.
#include <iostream>
#include <array>
using namespace std;

int main()
{
   const size_t arraySize = 4; // specifies size of array
   array< int, arraySize > a = { 10, 20, 30, 40 };
   int total = 0;

   // sum contents of array a
   for ( size_t i = 0; i < a.size(); ++i )
      total += a[ i ];

   cout << "Total of array elements: " << total << endl;
} // end main
```

## Co pokazuje ten przykład

Program demonstruje:

- utworzenie tablicy `std::array`,
- inicjalizację jej elementów konkretnymi wartościami,
- użycie zmiennej pomocniczej do przechowywania sumy,
- przejście po całej tablicy za pomocą pętli `for`,
- dodawanie kolejnych elementów do zmiennej `total`.

## Tablica `a`

W programie znajduje się deklaracja:

```cpp
const size_t arraySize = 4;
array< int, arraySize > a = { 10, 20, 30, 40 };
```

Oznacza to utworzenie tablicy `a`, która przechowuje 4 liczby całkowite:

- `a[0] = 10`
- `a[1] = 20`
- `a[2] = 30`
- `a[3] = 40`

Stała `arraySize` określa rozmiar tablicy. Ponieważ `std::array` ma rozmiar będący częścią typu, wartość ta musi być znana już w czasie kompilacji.

## Zmienna `total`

Instrukcja:

```cpp
int total = 0;
```

wprowadza zmienną, która będzie przechowywać sumę wszystkich elementów tablicy.

Bardzo ważne jest, aby taka zmienna została na początku ustawiona na `0`, ponieważ suma ma być budowana stopniowo przez dodawanie kolejnych wartości.

## Sumowanie w pętli

Najważniejszy fragment programu to:

```cpp
for ( size_t i = 0; i < a.size(); ++i )
   total += a[ i ];
```

Pętla przechodzi kolejno po wszystkich indeksach tablicy:

- `i = 0`
- `i = 1`
- `i = 2`
- `i = 3`

W każdej iteracji wykonywana jest instrukcja:

```cpp
total += a[i];
```

Jest to skrócony zapis równoważny:

```cpp
total = total + a[i];
```

## Jak zmienia się `total`

Przebieg obliczeń wygląda tak:

1. na początku:

```text
total = 0
```

2. po dodaniu `a[0] = 10`:

```text
total = 10
```

3. po dodaniu `a[1] = 20`:

```text
total = 30
```

4. po dodaniu `a[2] = 30`:

```text
total = 60
```

5. po dodaniu `a[3] = 40`:

```text
total = 100
```

Końcowa suma wszystkich elementów tablicy wynosi więc `100`.

## Wynik działania programu

Program wypisze:

```text
Total of array elements: 100
```

## Dlaczego ten przykład jest ważny

To ćwiczenie pokazuje bardzo podstawową, ale niezwykle ważną technikę programistyczną: **akumulację wyniku**.

Polega ona na tym, że:

- tworzymy zmienną przechowującą wynik częściowy,
- przechodzimy po kolejnych elementach danych,
- po każdej iteracji aktualizujemy wynik.

Ten sam schemat stosuje się nie tylko do sumowania, ale również do:

- liczenia średniej,
- znajdowania maksimum lub minimum,
- zliczania elementów spełniających warunek,
- budowania bardziej złożonych obliczeń na tablicach i kontenerach.

## Użycie `a.size()`

W warunku pętli pojawia się:

```cpp
a.size()
```

Metoda `size()` zwraca liczbę elementów tablicy. Dzięki temu program nie wpisuje na sztywno liczby `4` w warunku pętli.

To rozwiązanie jest wygodniejsze i bezpieczniejsze, ponieważ jeśli rozmiar tablicy zostanie zmieniony, pętla nadal będzie działać poprawnie.

## Podsumowanie

Program `cw4-3.cpp` pokazuje:

- deklarację i inicjalizację tablicy `std::array`,
- użycie zmiennej `total` do przechowywania sumy,
- iterację po wszystkich elementach tablicy,
- sumowanie wartości za pomocą operatora `+=`,
- wypisanie końcowego wyniku.

Jest to jeden z najważniejszych podstawowych przykładów pracy z tablicami, ponieważ uczy przetwarzania całego zbioru danych krok po kroku i budowania wyniku na
