# `cw4-5.cpp` – symulacja rzutów kostką i zliczanie częstości

Program pokazuje, jak użyć tablicy `std::array` do zliczania częstości występowania wyników losowania. W tym przykładzie symulowane są rzuty sześcienną kostką, a tablica przechowuje liczbę wylosowań każdej ścianki.

Program łączy kilka ważnych elementów nowoczesnego C++:

- generator liczb pseudolosowych,
- rozkład jednostajny,
- tablicę do zliczania wyników,
- iteracyjne wykonywanie dużej liczby prób,
- wypisywanie tabeli z wynikami.

## Kod programu

```cpp
// Die-rolling program using an array instead of switch.
#include <iostream>
#include <iomanip>
#include <array>
#include <random>
#include <ctime>
using namespace std;

int main()
{
   // use the default random-number generation engine to
   // produce uniformly distributed pseudorandom int values from 1 to 6
   default_random_engine engine( static_cast< unsigned int >( time(0) ) );
   uniform_int_distribution< unsigned int > randomInt( 1, 6 );

   const size_t arraySize = 7; // ignore element zero
   array< unsigned int, arraySize > frequency = {}; // initialize to 0s

   // roll die 6,000,000 times; use die value as frequency index
   for ( unsigned int roll = 1; roll <= 60000; ++roll )
      ++frequency[ randomInt( engine ) ];

   cout << "Face" << setw( 13 ) << "Frequency" << endl;

   // output each array element's value
   for ( size_t face = 1; face < frequency.size(); ++face )
      cout << setw( 4 ) << face << setw( 13 ) << frequency[ face ]
         << endl;
} // end main
```

## Co pokazuje ten przykład

Program symuluje wielokrotne rzuty kostką do gry. Dla każdego rzutu losowana jest liczba od `1` do `6`, a następnie zwiększany jest licznik odpowiadający tej wartości.

Na końcu program wypisuje tabelę pokazującą, ile razy wypadła każda ścianka kostki.

## Generator liczb losowych

Najpierw tworzony jest obiekt generatora:

```cpp
default_random_engine engine( static_cast< unsigned int >( time(0) ) );
```

### Co to oznacza

- `default_random_engine` to silnik generujący liczby pseudolosowe,
- `time(0)` zwraca aktualny czas w sekundach,
- `static_cast<unsigned int>(time(0))` zamienia tę wartość na typ `unsigned int`,
- uzyskana liczba służy jako **ziarno generatora**.

Dzięki temu przy różnych uruchomieniach programu sekwencja liczb pseudolosowych zwykle będzie inna.

## Rozkład jednostajny

Następnie tworzony jest rozkład:

```cpp
uniform_int_distribution< unsigned int > randomInt( 1, 6 );
```

To oznacza, że wywołanie:

```cpp
randomInt( engine )
```

zwróci pseudolosową liczbę całkowitą od `1` do `6`, przy czym każda z tych wartości ma takie samo prawdopodobieństwo.

To dobrze odpowiada modelowi uczciwej sześciennej kostki.

## Tablica `frequency`

Program deklaruje tablicę:

```cpp
const size_t arraySize = 7;
array< unsigned int, arraySize > frequency = {};
```

Tablica ma 7 elementów o indeksach od `0` do `6`.

### Dlaczego 7 elementów, skoro kostka ma tylko 6 ścianek

Komentarz w programie mówi:

```cpp
// ignore element zero
```

Element `frequency[0]` nie jest używany. Dzięki temu indeksy tablicy mogą bezpośrednio odpowiadać wynikom rzutu kostką:

- `frequency[1]` – liczba wyrzuconych jedynek,
- `frequency[2]` – liczba wyrzuconych dwójek,
- ...
- `frequency[6]` – liczba wyrzuconych szóstek.

Takie rozwiązanie upraszcza kod, bo nie trzeba przeliczać indeksu.

### Inicjalizacja zerami

Deklaracja:

```cpp
array< unsigned int, arraySize > frequency = {};
```

powoduje wyzerowanie wszystkich elementów tablicy.

Na początku więc mamy:

```text
frequency[0] = 0
frequency[1] = 0
...
frequency[6] = 0
```

## Symulacja rzutów

Najważniejsza pętla programu to:

```cpp
for ( unsigned int roll = 1; roll <= 60000; ++roll )
   ++frequency[ randomInt( engine ) ];
```

Pętla wykonuje się `60000` razy. W każdej iteracji:

1. losowana jest liczba od `1` do `6`,
2. odpowiedni licznik w tablicy `frequency` zostaje zwiększony o `1`.

### Jak działa ta instrukcja

```cpp
++frequency[ randomInt( engine ) ];
```

Jeśli losowanie zwróci na przykład `4`, wykonane zostanie:

```cpp
++frequency[4];
```

czyli liczba wylosowanych czwórek wzrośnie o `1`.

## Uwaga do komentarza w kodzie

W komentarzu programu zapisano:

```cpp
// roll die 6,000,000 times
```

ale rzeczywista pętla wykonuje się:

```cpp
roll <= 60000
```

czyli **60 000 razy**, a nie 6 000 000 razy.

To oznacza, że komentarz nie zgadza się z kodem i najprawdopodobniej jest pozostałością po wcześniejszej wersji programu.

Merytorycznie należy więc przyjąć, że program wykonuje **60 000 rzutów**.

## Wypisywanie wyników

Po zakończeniu losowań program wypisuje nagłówek:

```cpp
cout << "Face" << setw( 13 ) << "Frequency" << endl;
```

Następnie w pętli:

```cpp
for ( size_t face = 1; face < frequency.size(); ++face )
   cout << setw( 4 ) << face << setw( 13 ) << frequency[ face ]
      << endl;
```

wypisywane są kolejne wartości dla ścianek od `1` do `6`.

Program pomija indeks `0`, ponieważ nie reprezentuje on żadnego wyniku rzutu.

## Przykładowy wynik działania programu

Ponieważ program korzysta z losowania, wyniki będą się różnić przy każdym uruchomieniu. Przykładowo można otrzymać coś w rodzaju:

```text
Face    Frequency
   1         9962
   2        10041
   3         9925
   4        10038
   5        10006
   6        10028
```

Liczby nie muszą być identyczne, ale powinny być do siebie zbliżone, ponieważ każda ścianka ma takie samo prawdopodobieństwo wypadnięcia.

## Dlaczego wyniki są tylko zbliżone

Mimo że rozkład jest jednostajny, pojedyncza symulacja nie daje dokładnie takich samych wyników dla wszystkich ścianek. Wynika to z losowego charakteru prób.

Przy dużej liczbie rzutów częstości zwykle zbliżają się do wartości oczekiwanej. Dla 60 000 rzutów każda ścianka powinna wypaść średnio około:

```text
60000 / 6 = 10000
```

razy.

## Dlaczego ten przykład jest ważny

Program pokazuje bardzo praktyczne zastosowanie tablicy: **zliczanie częstości występowania wartości**.

To klasyczny wzorzec używany w wielu sytuacjach, na przykład przy:

- histogramach,
- analizie wyników eksperymentów,
- zliczaniu znaków lub słów,
- statystyce,
- symulacjach Monte Carlo.

Dodatkowo program wprowadza nowoczesny sposób losowania w C++ z użyciem nagłówka `<random>`.

## Podsumowanie

Program `cw4-5.cpp` pokazuje:

- użycie generatora pseudolosowego,
- użycie rozkładu jednostajnego `uniform_int_distribution`,
- inicjalizację tablicy zerami,
- zliczanie wyników losowania w tablicy,
- powiązanie wartości losowania z indeksem tablicy,
- wypisanie tabeli częstości występowania wyników.

Jest to bardzo dobry przykład łączący tablice, pętle i losowość, a także pokazujący, jak w prosty sposób budować statystykę wyników na podstawie wielu prób.

