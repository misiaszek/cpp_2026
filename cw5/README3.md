# `cw5-3.cpp` – iteratory `begin()` i `end()` w `std::vector`

Program pokazuje, jak przechodzić po elementach kontenera `std::vector` za pomocą iteratorów. Jest to klasyczny sposób pracy z kontenerami biblioteki standardowej C++, oparty na parze iteratorów zwracanych przez metody `begin()` i `end()`.

## Kod programu

```cpp
// vector::begin/end
#include <iostream>
#include <vector>

int main ()
{
  std::vector<int> myvector;
  for (int i=1; i<=5; i++) myvector.push_back(i);

  std::cout << "myvector contains:";
  for (std::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
  //for (auto it = myvector.begin() ; it != myvector.end(); ++it)

    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}
```

## Co pokazuje ten przykład

Program demonstruje:

* utworzenie pustego wektora `std::vector<int>`,
* dodawanie elementów metodą `push_back()`,
* pobieranie iteratora na początek kontenera przez `begin()`,
* pobieranie iteratora za koniec kontenera przez `end()`,
* przechodzenie po wszystkich elementach przy użyciu iteratora,
* odczyt wartości wskazywanej przez iterator przy pomocy operatora `*`.

## Wektor `myvector`

Na początku programu tworzony jest pusty wektor:

```cpp
std::vector<int> myvector;
```

`std::vector<int>` to dynamiczny kontener przechowujący elementy typu `int`. W przeciwieństwie do `std::array`, jego rozmiar może się zmieniać w czasie działania programu.

## Dodawanie elementów: `push_back()`

Następnie wykonywana jest pętla:

```cpp
for (int i=1; i<=5; i++) myvector.push_back(i);
```

W każdej iteracji do wektora dopisywana jest kolejna liczba:

* `1`
* `2`
* `3`
* `4`
* `5`

Po zakończeniu pętli wektor zawiera więc:

```text
1 2 3 4 5
```

Metoda `push_back()` dodaje nowy element na końcu wektora.

## Iteratory `begin()` i `end()`

Najważniejszy fragment programu to:

```cpp
for (std::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
```

### `begin()`

```cpp
myvector.begin()
```

zwraca iterator wskazujący pierwszy element wektora.

### `end()`

```cpp
myvector.end()
```

zwraca iterator wskazujący pozycję **za ostatnim elementem** wektora.

To bardzo ważne: `end()` nie wskazuje ostatniego elementu, tylko miejsce tuż za końcem kontenera. Dlatego iterator `end()` służy jako warunek zakończenia pętli i nie należy go dereferencjonować.

## Typ iteratora

W programie iterator został zapisany jawnie jako:

```cpp
std::vector<int>::iterator it
```

Oznacza to iterator dla wektora przechowującego liczby całkowite.

Taki zapis jest poprawny, ale dość długi. Dlatego w komentarzu pokazano krótszą wersję:

```cpp
//for (auto it = myvector.begin() ; it != myvector.end(); ++it)
```

W nowoczesnym C++ bardzo często używa się właśnie `auto`, ponieważ kompilator sam potrafi wywnioskować odpowiedni typ iteratora.

## Przechodzenie po elementach

Pętla działa tak długo, jak długo iterator `it` nie osiągnie pozycji `end()`:

```cpp
it != myvector.end()
```

W każdej iteracji wykonywane jest:

```cpp
++it
```

czyli przejście do następnego elementu.

## Dereferencja iteratora: `*it`

Wewnątrz pętli program wypisuje:

```cpp
std::cout << ' ' << *it;
```

Operator `*` oznacza tutaj **dereferencję iteratora**, czyli odczyt elementu, na który iterator aktualnie wskazuje.

Jeśli `it` wskazuje pierwszy element, to `*it` daje wartość `1`. Potem kolejno `2`, `3`, `4` i `5`.

## Wynik działania programu

Program wypisze:

```text
myvector contains: 1 2 3 4 5
```

## Dlaczego ten przykład jest ważny

To ćwiczenie pokazuje podstawowy sposób współpracy z kontenerami biblioteki standardowej C++ przez iteratory.

Iteratory są bardzo ważne, ponieważ:

* pozwalają przechodzić po elementach kontenera,
* są używane przez wiele algorytmów z `<algorithm>`,
* działają w podobny sposób dla wielu różnych kontenerów, nie tylko dla `std::vector`.

Ten przykład stanowi więc ważny krok do zrozumienia bardziej zaawansowanych operacji na kontenerach.

## Jawny typ iteratora a `auto`

W programie pokazano dwa warianty zapisu:

### Jawny typ

```cpp
std::vector<int>::iterator it = myvector.begin();
```

### Krótszy zapis z `auto`

```cpp
auto it = myvector.begin();
```

Oba zapisy działają poprawnie. W praktyce współczesny kod C++ bardzo często używa `auto`, bo zapis jest krótszy i czytelniejszy.

## Podsumowanie

Program `cw5-3.cpp` pokazuje:

* tworzenie i wypełnianie wektora `std::vector`,
* użycie `push_back()` do dodawania elementów,
* pobieranie iteratorów przez `begin()` i `end()`,
* iterowanie po kontenerze za pomocą klasycznej pętli `for`,
* dereferencję iteratora przez `*it`,
* możliwość użycia `auto` zamiast pełnego typu iteratora.

Jest to bardzo ważny przykład, ponieważ iteratory są jednym z podstawowych mechanizmów pracy z kontenerami i algorytmami w C++.
