# `cw4-4.cpp` – tekstowy wykres słupkowy

Program pokazuje, jak na podstawie danych zapisanych w tablicy utworzyć prosty **tekstowy wykres słupkowy**. Każdy element tablicy reprezentuje liczbę ocen należących do określonego przedziału punktowego, a program wypisuje te dane w postaci wierszy z gwiazdkami `*`.

## Kod programu

```cpp
// Bar chart printing program.
#include <iostream>
#include <iomanip>
#include <array>
using namespace std;

int main()
{
   const size_t arraySize = 11;
   array< unsigned int, arraySize > n =
      { 0, 0, 0, 0, 0, 0, 1, 2, 4, 2, 1 };

   cout << "Grade distribution:" << endl;

   // for each element of array n, output a bar of the chart
   for ( size_t i = 0; i < n.size(); ++i )
   {
      // output bar labels ("0-9:", ..., "90-99:", "100:" )
      if ( 0 == i )
         cout << "  0-9: ";
      else if ( 10 == i )
         cout << "  100: ";
      else
         cout << i * 10 << "-" << ( i * 10 ) + 9 << ": ";

      // print bar of asterisks
      for ( unsigned int stars = 0; stars < n[ i ]; ++stars )
         cout << '*';

      cout << endl; // start a new line of output
   } // end outer for
} // end main
```

## Co pokazuje ten przykład

Program demonstruje:

- przechowywanie danych statystycznych w tablicy,
- interpretowanie indeksów tablicy jako przedziałów ocen,
- budowanie etykiet tekstowych zależnych od indeksu,
- użycie zagnieżdżonych pętli,
- tworzenie prostego wykresu słupkowego w konsoli.

## Tablica `n`

Najważniejsza deklaracja programu to:

```cpp
array< unsigned int, arraySize > n =
   { 0, 0, 0, 0, 0, 0, 1, 2, 4, 2, 1 };
```

Tablica `n` ma 11 elementów. Każdy element oznacza liczbę ocen należących do określonego przedziału:

- `n[0]` – liczba ocen z zakresu `0–9`,
- `n[1]` – liczba ocen z zakresu `10–19`,
- `n[2]` – liczba ocen z zakresu `20–29`,
- ...
- `n[9]` – liczba ocen z zakresu `90–99`,
- `n[10]` – liczba ocen równych `100`.

W tym konkretnym przykładzie dane oznaczają, że:

- nie ma ocen od `0` do `59`,
- jest `1` ocena w przedziale `60–69`,
- są `2` oceny w przedziale `70–79`,
- są `4` oceny w przedziale `80–89`,
- są `2` oceny w przedziale `90–99`,
- jest `1` ocena równa `100`.

## Dlaczego użyto `unsigned int`

Elementy tablicy mają typ:

```cpp
unsigned int
```

co oznacza nieujemne liczby całkowite. Ma to sens, ponieważ liczba ocen w danym przedziale nie może być ujemna.

## Nagłówek wykresu

Program najpierw wypisuje tytuł:

```cpp
cout << "Grade distribution:" << endl;
```

Dzięki temu wiadomo, że dalsze wiersze będą przedstawiały rozkład ocen.

## Pętla zewnętrzna – przechodzenie po przedziałach

Najważniejsza część programu zaczyna się tutaj:

```cpp
for ( size_t i = 0; i < n.size(); ++i )
```

Pętla zewnętrzna przechodzi po wszystkich elementach tablicy `n`. Każda iteracja odpowiada jednemu przedziałowi ocen.

Dla każdego `i` program:

1. wypisuje etykietę przedziału,
2. wypisuje odpowiednią liczbę gwiazdek `*`.

## Tworzenie etykiet przedziałów

Wewnątrz pętli znajduje się instrukcja warunkowa:

```cpp
if ( 0 == i )
   cout << "  0-9: ";
else if ( 10 == i )
   cout << "  100: ";
else
   cout << i * 10 << "-" << ( i * 10 ) + 9 << ": ";
```

### Przypadek `i == 0`

Dla pierwszego elementu etykieta ma postać:

```text
0-9:
```

### Przypadek `i == 10`

Ostatni element nie oznacza zakresu `100-109`, lecz dokładnie ocenę `100`, dlatego program wypisuje:

```text
100:
```

### Pozostałe przypadki

Dla indeksów od `1` do `9` etykieta jest wyliczana ze wzoru:

- początek przedziału: `i * 10`,
- koniec przedziału: `(i * 10) + 9`.

Na przykład:

- `i = 6` → `60-69:`,
- `i = 7` → `70-79:`,
- `i = 8` → `80-89:`.

## Pętla wewnętrzna – rysowanie gwiazdek

Po wypisaniu etykiety program wykonuje drugą pętlę:

```cpp
for ( unsigned int stars = 0; stars < n[ i ]; ++stars )
   cout << '*';
```

Ta pętla odpowiada za narysowanie słupka wykresu.

Liczba gwiazdek zależy od wartości `n[i]`:

- jeśli `n[i] == 0`, nie pojawi się żadna gwiazdka,
- jeśli `n[i] == 1`, pojawi się `*`,
- jeśli `n[i] == 4`, pojawi się `****`.

Czyli każdy słupek ma długość równą liczbie ocen w danym przedziale.

## Zagnieżdżone pętle

Ten program jest dobrym przykładem użycia **pętli zagnieżdżonych**:

- pętla zewnętrzna przechodzi po kolejnych przedziałach ocen,
- pętla wewnętrzna rysuje słupek gwiazdek dla aktualnego przedziału.

To bardzo często spotykany schemat, gdy chcemy dla każdego elementu zbioru wykonać dodatkową serię operacji.

## Wynik działania programu

Program wypisze wykres w przybliżeniu taki jak poniżej:

```text
Grade distribution:
  0-9:
10-19:
20-29:
30-39:
40-49:
50-59:
60-69: *
70-79: **
80-89: ****
90-99: **
  100: *
```

Każda gwiazdka odpowiada jednej ocenie należącej do danego przedziału.

## Dlaczego ten przykład jest ważny

Program pokazuje, że tablica nie musi przechowywać tylko pojedynczych danych do prostego wypisania. Może też reprezentować **rozkład statystyczny**, czyli informację o tym, ile razy występują pewne wartości w różnych zakresach.

To bardzo ważna idea, ponieważ podobne techniki wykorzystuje się przy:

- histogramach,
- analizie wyników,
- statystyce,
- wizualizacji danych,
- zliczaniu częstości występowania wartości.

## Podsumowanie

Program `cw4-4.cpp` pokazuje:

- użycie tablicy `std::array` do przechowywania liczności przedziałów,
- interpretowanie indeksu tablicy jako zakresu ocen,
- budowanie etykiet tekstowych zależnych od indeksu,
- użycie pętli zagnieżdżonych,
- tworzenie prostego wykresu słupkowego z gwiazdek.

Jest to bardzo dobry przykład łączący pracę z tablicą, instrukcjami warunkowymi oraz wizualizacją danych w postaci tekstowej.

