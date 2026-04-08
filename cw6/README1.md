# `cw6-1.cpp` – bezpieczny dostęp do elementów `std::vector` przez `at()`

Program pokazuje użycie metody `at()` w kontenerze `std::vector`. Jest to bezpieczniejszy sposób dostępu do elementów niż operator `[]`, ponieważ `at()` sprawdza, czy podany indeks mieści się w dozwolonym zakresie. Jeśli indeks jest niepoprawny, zgłaszany jest wyjątek `std::out_of_range`.

## Kod programu

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> data = { 1, 2, 4, 5, 5, 6 };

    // Set element 1
    data.at(1) = 88;

    // Read element 2
    std::cout << "Element at index 2 has value " << data.at(2) << '\n';

    std::cout << "data size = " << data.size() << '\n';

    try {
        // Set element 6
        data.at(6) = 666;
    } catch (std::out_of_range const& exc) {
        std::cout << exc.what() << '\n';
    }

    try { data.at(6) = 666; } catch (...) { std::cout << "no!\n"; }

    // Print final values
    std::cout << "data:";
    for (int elem : data)
        std::cout << " " << elem;
    std::cout << '\n';
}
```

## Co pokazuje ten przykład

Program demonstruje:

* utworzenie wektora `std::vector<int>`,
* odczyt i modyfikację elementów metodą `at()`,
* sprawdzenie rozmiaru wektora metodą `size()`,
* obsługę wyjątku `std::out_of_range`,
* różnicę między przechwyceniem konkretnego wyjątku a użyciem ogólnego `catch (...)`.

## Wektor `data`

Na początku programu tworzony jest wektor:

```cpp
std::vector<int> data = { 1, 2, 4, 5, 5, 6 };
```

Zawiera on 6 elementów o indeksach:

* `0` → `1`
* `1` → `2`
* `2` → `4`
* `3` → `5`
* `4` → `5`
* `5` → `6`

## Modyfikacja elementu przez `at()`

Instrukcja:

```cpp
data.at(1) = 88;
```

zmienia element o indeksie `1`.

Początkowo pod tym indeksem znajdowała się wartość `2`, więc po tej operacji wektor ma postać:

```text
1 88 4 5 5 6
```

## Odczyt elementu przez `at()`

Następnie program wypisuje:

```cpp
std::cout << "Element at index 2 has value " << data.at(2) << '\n';
```

Element o indeksie `2` ma wartość `4`, więc program wypisze:

```text
Element at index 2 has value 4
```

## `size()` – liczba elementów

Instrukcja:

```cpp
std::cout << "data size = " << data.size() << '\n';
```

wypisuje rozmiar wektora. W tym przypadku `data.size()` zwraca `6`, bo wektor ma sześć elementów.

## Próba dostępu poza zakresem

Potem program wykonuje:

```cpp
data.at(6) = 666;
```

To jest błąd zakresu, ponieważ przy rozmiarze `6` poprawne indeksy to tylko:

```text
0, 1, 2, 3, 4, 5
```

Indeks `6` jest już poza końcem wektora.

### Co robi `at()` w takiej sytuacji

Metoda `at()` nie pozwala na cichy błędny dostęp. Zamiast tego zgłasza wyjątek:

```cpp
std::out_of_range
```

To jedna z najważniejszych zalet `at()`.

## Pierwszy blok `try-catch`

Program najpierw obsługuje błąd w ten sposób:

```cpp
try {
    data.at(6) = 666;
} catch (std::out_of_range const& exc) {
    std::cout << exc.what() << '\n';
}
```

Tutaj przechwytywany jest konkretny typ wyjątku: `std::out_of_range`.

Parametr `exc` zawiera obiekt wyjątku, a wywołanie:

```cpp
exc.what()
```

zwraca tekstowy opis błędu przygotowany przez bibliotekę standardową.

Dokładna treść komunikatu zależy od kompilatora i biblioteki standardowej, ale zwykle informuje, że indeks jest poza zakresem.

## Drugi blok `try-catch`

Potem program wykonuje skróconą wersję:

```cpp
try { data.at(6) = 666; } catch (...) { std::cout << "no!\n"; }
```

Tutaj użyto:

```cpp
catch (...)
```

co oznacza: przechwyć **dowolny wyjątek**, niezależnie od typu.

To rozwiązanie jest mniej precyzyjne niż łapanie konkretnego wyjątku, ale bywa użyteczne, gdy chcemy ogólnie zabezpieczyć program przed przerwaniem działania.

W tym przypadku zostanie wypisane:

```text
no!
```

## Wartość końcowa wektora

Ponieważ obie próby zapisu do `data.at(6)` kończą się wyjątkiem, wektor nie zostaje zmieniony w tych miejscach.

Jedyna skuteczna modyfikacja to:

```cpp
data.at(1) = 88;
```

Ostatecznie wektor zawiera więc:

```text
1 88 4 5 5 6
```

## Pętla wypisująca dane

Na końcu programu użyto pętli zakresowej:

```cpp
for (int elem : data)
    std::cout << " " << elem;
```

Każdy element wektora zostaje wypisany po kolei.

## Przykładowy wynik działania programu

Program wypisze coś w rodzaju:

```text
Element at index 2 has value 4
data size = 6
vector::_M_range_check: __n (which is 6) >= this->size() (which is 6)
no!
data: 1 88 4 5 5 6
```

Uwaga: dokładna treść komunikatu z `exc.what()` może być inna w zależności od kompilatora i implementacji biblioteki standardowej.

## Dlaczego ten przykład jest ważny

Program pokazuje praktyczną różnicę między bezpiecznym dostępem do elementu a potencjalnie niebezpiecznym dostępem bez kontroli zakresu.

Warto zapamiętać:

* `at()` sprawdza zakres i może zgłosić wyjątek,
* `[]` zwykle nie sprawdza zakresu,
* wyjątki można obsługiwać precyzyjnie lub ogólnie.

To ważne szczególnie wtedy, gdy indeks może pochodzić od użytkownika lub z obliczeń, które nie zawsze muszą być poprawne.

## Podsumowanie

Program `cw6-1.cpp` pokazuje:

* użycie `std::vector<int>`,
* odczyt i zapis elementów przez `at()`,
* użycie `size()` do sprawdzenia liczby elementów,
* zgłaszanie wyjątku `std::out_of_range` przy błędnym indeksie,
* obsługę wyjątku przez `catch (std::out_of_range const&)`,
* ogólne przechwytywanie wyjątków przez `catch (...)`.

Jest to bardzo dobry przykład pokazujący, jak pisać bezpieczniejszy kod przy pracy z kontenerami w C++.
