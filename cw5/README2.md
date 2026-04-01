# `cw5-2.cpp` – sortowanie i wyszukiwanie w tablicy `std::array`

Program pokazuje, jak używać algorytmów z biblioteki standardowej C++ do pracy z tablicą `std::array`. W tym przykładzie dane tekstowe są najpierw wypisywane w kolejności początkowej, następnie sortowane, a na końcu przeszukiwane za pomocą wyszukiwania binarnego.

To bardzo ważny przykład, ponieważ pokazuje współpracę kontenera `std::array` z algorytmami z nagłówka `<algorithm>`.

## Kod programu

```cpp
// Sorting and searching arrays.
#include <iostream>
#include <array>
#include <string>
#include <algorithm> // contains sort and binary_search
using namespace std;

int main()
{
   const size_t arraySize = 7; // size of array colors
   array< string, arraySize > colors = { "red", "orange", "yellow",
      "green", "blue", "indigo", "violet" };

   // output original array
   cout << "Unsorted array:\n";
   for ( string color : colors )
      cout << color << " ";

   sort( colors.begin(), colors.end() ); // sort contents of colors

   // output sorted array
   cout << "\nSorted array:\n";
   for ( string item : colors )
      cout << item << " ";

   // search for "indigo" in colors
   bool found = binary_search( colors.begin(), colors.end(), "indigo" );
   cout << "\n\n\"indigo\" " << ( found ? "was" : "was not" )
      << " found in colors" << endl;

   // search for "cyan" in colors
   found = binary_search( colors.begin(), colors.end(), "cyan" );
   cout << "\"cyan\" " << ( found ? "was" : "was not" )
      << " found in colors" << endl;
} // end main
```

## Co pokazuje ten przykład

Program demonstruje:

* utworzenie tablicy `std::array` z napisami,
* wypisanie zawartości tablicy,
* sortowanie danych funkcją `sort()`,
* wyszukiwanie elementów funkcją `binary_search()`,
* użycie iteratorów `begin()` i `end()`.

## Tablica `colors`

Na początku programu tworzona jest tablica:

```cpp
array< string, arraySize > colors = { "red", "orange", "yellow",
   "green", "blue", "indigo", "violet" };
```

Tablica przechowuje 7 napisów reprezentujących kolory:

* `red`
* `orange`
* `yellow`
* `green`
* `blue`
* `indigo`
* `violet`

Warto zauważyć, że początkowa kolejność nie jest alfabetyczna.

## Wypisywanie tablicy przed sortowaniem

Program najpierw wypisuje zawartość tablicy w oryginalnej kolejności:

```cpp
cout << "Unsorted array:\n";
for ( string color : colors )
   cout << color << " ";
```

Pętla zakresowa przechodzi po wszystkich elementach tablicy i wypisuje każdy napis oddzielony spacją.

## Funkcja `sort()`

Najważniejsza operacja programu to:

```cpp
sort( colors.begin(), colors.end() );
```

Funkcja `sort()` pochodzi z nagłówka `<algorithm>`.

### Co oznaczają `begin()` i `end()`

* `colors.begin()` – iterator wskazujący początek tablicy,
* `colors.end()` – iterator wskazujący pozycję za ostatnim elementem.

Taki zapis oznacza: posortuj wszystkie elementy od początku kontenera do końca.

### Jak działa sortowanie

Dla napisów typu `std::string` domyślne sortowanie odbywa się leksykograficznie, czyli zgodnie z porządkiem alfabetycznym porównującym znaki.

Po sortowaniu tablica `colors` będzie miała kolejność:

* `blue`
* `green`
* `indigo`
* `orange`
* `red`
* `violet`
* `yellow`

## Wypisywanie tablicy po sortowaniu

Po użyciu `sort()` program wypisuje tablicę ponownie:

```cpp
cout << "\nSorted array:\n";
for ( string item : colors )
   cout << item << " ";
```

Teraz elementy są już w kolejności alfabetycznej.

## Funkcja `binary_search()`

Po sortowaniu program wykonuje dwa wyszukiwania:

```cpp
bool found = binary_search( colors.begin(), colors.end(), "indigo" );
```

oraz:

```cpp
found = binary_search( colors.begin(), colors.end(), "cyan" );
```

### Co robi `binary_search()`

Funkcja `binary_search()` również pochodzi z `<algorithm>`. Sprawdza, czy dany element znajduje się w posortowanym zakresie.

Zwraca wartość typu `bool`:

* `true` – jeśli element został znaleziony,
* `false` – jeśli elementu nie ma.

### Bardzo ważny warunek

`binary_search()` zakłada, że dane są już posortowane. Dlatego wywołanie `sort()` przed wyszukiwaniem jest konieczne.

Gdyby próbować użyć `binary_search()` na nieposortowanej tablicy, wynik mógłby być niepoprawny.

## Wyszukiwanie `"indigo"`

Po posortowaniu tablica zawiera napis `"indigo"`, więc:

```cpp
binary_search( colors.begin(), colors.end(), "indigo" )
```

zwróci `true`.

Program wypisze więc:

```text
"indigo" was found in colors
```

## Wyszukiwanie `"cyan"`

Napis `"cyan"` nie występuje w tablicy `colors`, więc:

```cpp
binary_search( colors.begin(), colors.end(), "cyan" )
```

zwróci `false`.

Program wypisze więc:

```text
"cyan" was not found in colors
```

## Wynik działania programu

Program wypisze:

```text
Unsorted array:
red orange yellow green blue indigo violet
Sorted array:
blue green indigo orange red violet yellow

"indigo" was found in colors
"cyan" was not found in colors
```

Układ odstępów i końców linii może się nieznacznie różnić, ale sens wyniku pozostaje taki sam.

## Dlaczego ten przykład jest ważny

To ćwiczenie pokazuje bardzo ważną ideę nowoczesnego C++: kontenery i algorytmy są od siebie oddzielone, ale współpracują przez iteratory.

W tym przypadku:

* `std::array` przechowuje dane,
* `sort()` i `binary_search()` wykonują operacje na tych danych,
* `begin()` i `end()` łączą kontener z algorytmem.

To jeden z fundamentów biblioteki standardowej C++.

## Podsumowanie

Program `cw5-2.cpp` pokazuje:

* użycie `std::array<std::string, N>`,
* wypisywanie elementów tablicy,
* sortowanie napisów funkcją `sort()`,
* wyszukiwanie elementów funkcją `binary_search()`,
* znaczenie iteratorów `begin()` i `end()`,
* konieczność posortowania danych przed użyciem `binary_search()`.

Jest to bardzo dobry przykład pokazujący praktyczne wykorzystanie algorytmów z biblioteki standardowej na kontenerach w C++.
