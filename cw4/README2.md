# `cw4-2.cpp` – wypełnianie tablicy wartościami obliczanymi w pętli

Program pokazuje, jak utworzyć obiekt `std::array`, a następnie wypełnić jego elementy wartościami wyliczanymi w pętli. W tym przykładzie do tablicy wpisywane są kolejne liczby parzyste od `2` do `10`.

## Kod programu

```cpp
// Set array s to the even integers from 2 to 10.
#include <iostream>
#include <iomanip>
#include <array>
using namespace std;

int main()
{
   // constant variable can be used to specify array size
   const size_t arraySize = 5; // must initialize in declaration <--- !!!

   array< int, arraySize > s; // array s has 5 elements

   for ( size_t i = 0; i < s.size(); ++i ) // set the values
      s[ i ] = 2 + 2 * i;

   cout << "Element" << setw( 13 ) << "Value" << endl;

   // output contents of array s in tabular format
   for ( size_t j = 0; j < s.size(); ++j )
      cout << setw( 7 ) << j << setw( 13 ) << s[ j ] << endl;
} // end main
```

## Co pokazuje ten przykład

Program demonstruje kilka ważnych rzeczy:

- użycie stałej do określenia rozmiaru `std::array`,
- utworzenie tablicy o stałej liczbie elementów,
- wypełnienie tablicy wartościami w pętli,
- wypisanie zawartości tablicy w postaci tabeli.

## Stała `arraySize`

W programie pojawia się deklaracja:

```cpp
const size_t arraySize = 5;
```

Jest to stała, która określa rozmiar tablicy.

Następnie ta stała jest używana tutaj:

```cpp
array< int, arraySize > s;
```

Oznacza to utworzenie tablicy `s`, która przechowuje 5 liczb typu `int`.

### Dlaczego zmienna musi być stała

W przypadku `std::array` liczba elementów jest częścią typu. Oznacza to, że rozmiar tablicy musi być znany już w czasie kompilacji.

Dlatego użyta zmienna:

```cpp
const size_t arraySize = 5;
```

musi mieć stałą wartość ustaloną przy deklaracji.

Gdyby była zwykłą zmienną:

```cpp
size_t arraySize = 5;
```

nie mogłaby zostać użyta jako parametr rozmiaru `std::array`.

## Tablica `std::array`

Deklaracja:

```cpp
array< int, arraySize > s;
```

oznacza tablicę pięciu elementów typu `int`.

W momencie utworzenia program nie podaje jeszcze konkretnych wartości elementów w liście inicjalizacyjnej. Zamiast tego wartości zostają przypisane później, w pętli.

## Wypełnianie tablicy

Do ustawienia wartości elementów służy pętla:

```cpp
for ( size_t i = 0; i < s.size(); ++i )
   s[ i ] = 2 + 2 * i;
```

Dla kolejnych wartości `i` otrzymujemy:

- `i = 0` → `s[0] = 2 + 2 * 0 = 2`
- `i = 1` → `s[1] = 2 + 2 * 1 = 4`
- `i = 2` → `s[2] = 2 + 2 * 2 = 6`
- `i = 3` → `s[3] = 2 + 2 * 3 = 8`
- `i = 4` → `s[4] = 2 + 2 * 4 = 10`

W efekcie tablica zawiera:

```text
2, 4, 6, 8, 10
```

## Użycie `size()`

W obu pętlach program używa:

```cpp
s.size()
```

Metoda `size()` zwraca liczbę elementów tablicy, czyli `5`.

Jest to wygodniejsze i bezpieczniejsze niż ręczne wpisywanie liczby `5` w kilku miejscach programu. Gdyby rozmiar tablicy został później zmieniony, kod pętli nadal działałby poprawnie.

## Wypisywanie wyników

Najpierw program wypisuje nagłówek:

```cpp
cout << "Element" << setw( 13 ) << "Value" << endl;
```

Potem druga pętla wypisuje kolejne indeksy i wartości:

```cpp
for ( size_t j = 0; j < s.size(); ++j )
   cout << setw( 7 ) << j << setw( 13 ) << s[ j ] << endl;
```

Warto zauważyć, że w drugiej pętli użyto zmiennej `j`, a nie `i`. To po prostu inna nazwa licznika pętli.

## `setw()` i formatowanie tabeli

Funkcja `setw()` z nagłówka `<iomanip>` ustawia szerokość kolejnego wypisywanego pola. Dzięki temu wynik ma uporządkowany układ kolumn.

Program wypisuje więc:

- w pierwszej kolumnie indeks elementu,
- w drugiej kolumnie wartość pod tym indeksem.

## Wynik działania programu

Program wypisze:

```text
Element        Value
      0            2
      1            4
      2            6
      3            8
      4           10
```

Dokładne odstępy mogą się nieco różnić, ale znaczenie wyniku pozostaje takie samo.

## Co odróżnia ten przykład od poprzedniego

W `cw4-1.cpp` wartości tablicy były wpisane bezpośrednio przy deklaracji:

```cpp
array<int, 5> n = { 32, 27, 64, 18, 95 };
```

Tutaj natomiast tablica jest najpierw tworzona, a dopiero później wypełniana w pętli według wzoru matematycznego.

To bardzo ważna technika, ponieważ wiele tablic w programach nie zawiera danych wpisanych ręcznie, lecz wartości obliczane dynamicznie według pewnej reguły.

## Podsumowanie

Program `cw4-2.cpp` pokazuje:

- użycie stałej `const size_t` do określenia rozmiaru `std::array`,
- tworzenie tablicy o stałej liczbie elementów,
- wypełnianie tablicy w pętli,
- generowanie kolejnych liczb parzystych,
- użycie `size()` do sterowania pętlami,
- estetyczne wypisywanie wyników w tabeli.

Jest to prosty, ale bardzo ważny przykład pokazujący, jak programowo generować zawartość tablicy zamiast wpis
