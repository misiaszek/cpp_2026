# `cw6-2.cpp` – podstawy wyjątków w C++

Program pokazuje kilka ważnych aspektów obsługi wyjątków w C++:

* ręczne zgłoszenie wyjątku przez `throw`,
* przechwycenie wyjątku konkretnego typu,
* przechwycenie standardowego wyjątku przez referencję do klasy bazowej `std::exception`,
* użycie `vector::at()`, które zgłasza wyjątek przy wyjściu poza zakres,
* różnicę między dopasowanym i niedopasowanym typem w bloku `catch`.

## Kod programu

```cpp
#include <iostream>
#include <vector>
 
int main() {
    try {
        std::cout << "Throwing an integer exception...\n";
        throw 42;
    } catch (int i) {
        std::cout << " the integer exception was caught, with value: " << i << '\n';
    }
 
    try {
        std::cout << "Creating a vector of size 5... \n";
        std::vector<int> v(5);
        std::cout << "Accessing the 11th element of the vector...\n";
        std::cout << v.at(10); // vector::at() throws std::out_of_range
    } catch (const std::exception& e) { // caught by reference to base
        std::cout << " a standard exception was caught, with message '"
                  << e.what() << "'\n";
    }
 
 
   std::vector<int> v(5);
   try {
       v.at(44) = 1;
   } catch (const std::length_error& e) { // caught by reference to base
        std::cout << " a standard exception was caught, with message '"
                  << e.what() << "'\n";
   } catch(...) {
       std::cout << "ex: ...";
   }
}
```

## Co pokazuje ten przykład

Program składa się z trzech części:

1. ręczne zgłoszenie wyjątku typu `int`,
2. obsługa wyjątku standardowego zgłoszonego przez `vector::at()`,
3. przykład niedopasowanego typu w `catch` i przechwycenia go przez `catch(...)`.

## Pierwszy blok `try-catch` – wyjątek typu `int`

Pierwsza część programu to:

```cpp
try {
    std::cout << "Throwing an integer exception...\n";
    throw 42;
} catch (int i) {
    std::cout << " the integer exception was caught, with value: " << i << '\n';
}
```

### Co się tu dzieje

* instrukcja `throw 42;` zgłasza wyjątek typu `int`,
* sterowanie natychmiast opuszcza blok `try`,
* program szuka pasującego bloku `catch`,
* `catch (int i)` pasuje dokładnie do wyjątku typu `int`.

Wartość `42` zostaje więc przechwycona i przypisana do zmiennej `i`.

### Wynik tej części

Program wypisze:

```text
Throwing an integer exception...
 the integer exception was caught, with value: 42
```

## Drugi blok `try-catch` – wyjątek standardowy z `vector::at()`

Druga część programu tworzy wektor:

```cpp
std::vector<int> v(5);
```

Taki wektor ma 5 elementów, więc poprawne indeksy to:

```text
0, 1, 2, 3, 4
```

Następnie program próbuje wykonać:

```cpp
std::cout << v.at(10);
```

Indeks `10` jest poza zakresem, więc metoda `at()` zgłasza wyjątek.

### Jaki wyjątek jest zgłaszany

`std::vector::at()` zgłasza wyjątek typu:

```cpp
std::out_of_range
```

Jest to standardowy wyjątek biblioteki C++.

### Jak jest przechwytywany

Program używa:

```cpp
catch (const std::exception& e)
```

To działa, ponieważ `std::out_of_range` dziedziczy po `std::exception`.

Czyli wyjątek klasy pochodnej może zostać przechwycony przez referencję do klasy bazowej.

To bardzo ważna technika w C++: często przechwytuje się wyjątki standardowe właśnie przez:

```cpp
const std::exception&
```

bo pozwala to obsłużyć wiele różnych wyjątków bibliotecznych w jednym miejscu.

### `e.what()`

W bloku `catch` użyto:

```cpp
e.what()
```

Metoda `what()` zwraca tekstowy opis błędu.

Dokładna treść komunikatu zależy od kompilatora i biblioteki standardowej, ale zwykle informuje, że indeks jest poza zakresem.

## Trzeci blok `try-catch` – niedopasowany `catch`

Na końcu programu tworzony jest kolejny wektor:

```cpp
std::vector<int> v(5);
```

Potem wykonywana jest instrukcja:

```cpp
v.at(44) = 1;
```

To znów jest dostęp poza zakresem, więc `at()` ponownie zgłasza wyjątek typu:

```cpp
std::out_of_range
```

### Dlaczego `catch (const std::length_error& e)` nie zadziała

Program najpierw próbuje przechwycić wyjątek tutaj:

```cpp
catch (const std::length_error& e)
```

To **nie pasuje**, ponieważ zgłoszony wyjątek ma typ `std::out_of_range`, a nie `std::length_error`.

Obie te klasy należą do standardowej hierarchii wyjątków, ale są różnymi typami.

Czyli ten blok `catch` zostaje pominięty.

### Dlaczego działa `catch(...)`

Następny blok to:

```cpp
catch(...) {
    std::cout << "ex: ...";
}
```

`catch(...)` przechwytuje dowolny wyjątek, niezależnie od typu. Dlatego tutaj właśnie trafia wyjątek `std::out_of_range`.

W efekcie program wypisze:

```text
ex: ...
```

## Ważna uwaga merytoryczna

Komentarz w kodzie:

```cpp
catch (const std::length_error& e) { // caught by reference to base
```

jest mylący.

To **nie** jest przechwycenie przez referencję do klasy bazowej. To przechwycenie przez referencję do konkretnego typu `std::length_error`.

W dodatku ten typ w tym miejscu nie pasuje do faktycznie zgłaszanego wyjątku `std::out_of_range`.

Poprawny komentarz powinien raczej mówić, że to próba przechwycenia wyjątku konkretnego typu, która w tym przypadku się nie powiedzie.

## Hierarchia wyjątków standardowych

Warto zapamiętać, że wiele wyjątków biblioteki standardowej dziedziczy po `std::exception`.

Przykładowo:

* `std::out_of_range`
* `std::length_error`
* `std::invalid_argument`
* `std::runtime_error`

są wyjątkami standardowymi, ale nie są tym samym typem.

Dlatego:

* `catch (const std::exception& e)` jest ogólne,
* `catch (const std::out_of_range& e)` jest bardziej precyzyjne,
* `catch (const std::length_error& e)` złapie tylko wyjątek dokładnie tego typu lub pochodny od niego.

## Przykładowy wynik działania programu

Program wypisze coś w rodzaju:

```text
Throwing an integer exception...
 the integer exception was caught, with value: 42
Creating a vector of size 5...
Accessing the 11th element of the vector...
 a standard exception was caught, with message '...'
ex: ...
```

Dokładna treść komunikatu z `what()` zależy od implementacji biblioteki standardowej.

## Co warto zapamiętać

Ten przykład dobrze pokazuje kilka zasad:

1. `throw` natychmiast przerywa normalny przebieg programu i szuka pasującego `catch`.
2. Typ w `catch` musi pasować do typu zgłoszonego wyjątku.
3. `catch (const std::exception& e)` pozwala wygodnie obsłużyć wiele wyjątków standardowych.
4. `catch(...)` działa jako ogólna „ostatnia linia obrony”.
5. `vector::at()` jest bezpieczniejsze niż `operator[]`, bo kontroluje zakres.

## Podsumowanie

Program `cw6-2.cpp` pokazuje:

* ręczne zgłoszenie wyjątku przez `throw`,
* przechwycenie wyjątku typu podstawowego `int`,
* przechwycenie wyjątku standardowego przez `const std::exception&`,
* działanie `vector::at()` przy błędnym indeksie,
* znaczenie dopasowania typu w blokach `catch`,
* użycie `catch(...)` do przechwycenia dowolnego wyjątku.

Jest to bardzo dobry
