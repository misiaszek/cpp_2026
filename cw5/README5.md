# `cw5-5.cpp` – tablica wielowymiarowa `std::array`

Program pokazuje, jak utworzyć i wypisać **dwuwymiarową tablicę** zbudowaną z `std::array`. W tym przykładzie tablica ma:

* `2` wiersze,
* `3` kolumny.

## Kod programu

```cpp
// Initializing multidimensional arrays.
#include <iostream>
#include <array>
using namespace std;

const size_t rows = 2;
const size_t columns = 3;
void printArray( const array< array< int, columns >, rows> & );

int main()
{
   array< array< int, columns >, rows > array1 = { 1, 2, 3, 4, 5, 6 };
   array< array< int, columns >, rows > array2 = { 1, 2, 3, 4, 5 };

   cout << "Values in array1 by row are:" << endl;
   printArray( array1 );

   cout << "\nValues in array2 by row are:" << endl;
   printArray( array2 );
} // end main

// output array with two rows and three columns
void printArray( const array< array< int, columns >, rows> & a )
{
   // loop through array's rows
   for ( auto const &row : a )
   {
      // loop through columns of current row
      for ( auto const &element : row )
         cout << element << ' ';

      cout << endl; // start new line of output
   } // end outer for
} // end function printArray
```

## Co pokazuje ten przykład

Najważniejszy typ w programie to:

```cpp
array< array< int, columns >, rows >
```

Oznacza on:

* zewnętrzną tablicę o liczbie elementów równej `rows`,
* gdzie każdy element tej tablicy jest kolejną tablicą,
* a każda wewnętrzna tablica ma `columns` elementów typu `int`.

Czyli w praktyce jest to tablica 2 × 3.

## `array1`

Deklaracja:

```cpp
array< array< int, columns >, rows > array1 = { 1, 2, 3, 4, 5, 6 };
```

ustawia wszystkie 6 elementów kolejno.

Logicznie tablica ma postać:

```text
1 2 3
4 5 6
```

czyli:

* pierwszy wiersz: `1 2 3`
* drugi wiersz: `4 5 6`

## `array2`

Deklaracja:

```cpp
array< array< int, columns >, rows > array2 = { 1, 2, 3, 4, 5 };
```

podaje tylko 5 wartości zamiast 6.

Brakujący element zostanie automatycznie dopełniony wartością `0`.

Dlatego `array2` będzie miała postać:

```text
1 2 3
4 5 0
```

To ważna własność inicjalizacji listowej: jeśli nie podamy wszystkich wartości, pozostałe elementy są dopełniane wartościami domyślnymi.

## Funkcja `printArray()`

Funkcja:

```cpp
void printArray( const array< array< int, columns >, rows> & a )
```

przyjmuje tablicę przez referencję do `const`, więc:

* nie kopiuje całej tablicy,
* nie może jej zmieniać.

Wewnątrz funkcji użyto dwóch pętli zakresowych.

### Pętla po wierszach

```cpp
for ( auto const &row : a )
```

Każda iteracja pobiera jeden wiersz tablicy.

### Pętla po elementach wiersza

```cpp
for ( auto const &element : row )
   cout << element << ' ';
```

Ta pętla przechodzi po elementach aktualnego wiersza i wypisuje je.

Dzięki temu program wypisuje tablicę w układzie wierszowym.

## Wynik działania programu

Program wypisze:

```text
Values in array1 by row are:
1 2 3
4 5 6

Values in array2 by row are:
1 2 3
4 5 0
```

## Co warto zapamiętać

Ten przykład pokazuje trzy ważne rzeczy:

1. `std::array` może być zagnieżdżone, więc można tworzyć tablice wielowymiarowe.
2. Przy inicjalizacji listowej elementy są wypełniane kolejno.
3. Jeśli zabraknie wartości inicjalizujących, pozostałe elementy dostaną wartość domyślną.

## Podsumowanie

Program `cw5-5.cpp` pokazuje:

* tworzenie tablicy dwuwymiarowej z `std::array`,
* inicjalizację pełną i niepełną,
* automatyczne dopełnianie brakujących elementów zerami,
* przekazywanie tablicy do funkcji przez `const` referencję,
* wypisywanie danych za pomocą zagnieżdżonych pętli zakresowych.

To dobry przykład pokazujący, jak w nowoczesnym C++ reprezentować prostą macierz lub tabelę danych bez używania surowych tablic w stylu C.
