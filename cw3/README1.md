# `cw3-1.cpp` – delegacja konstruktorów

Program pokazuje mechanizm **delegacji konstruktorów** w C++. Klasa `class_c` ma trzy konstruktory przyjmujące różną liczbę argumentów, ale zamiast powielać ten sam kod inicjalizujący, kolejne konstruktory wywołują prostsze wersje konstruktora tej samej klasy.

Jest to wygodniejsza i bezpieczniejsza alternatywa dla ręcznego kopiowania logiki inicjalizacji w wielu przeciążonych konstruktorach.

## Kod programu

```cpp
#include <iostream>

/*
class class_c {
public:
    int max;
    int min;
    int middle;

    class_c() {}
    class_c(int my_max) {
        max = my_max > 0 ? my_max : 10;
    }
    class_c(int my_max, int my_min) {
        max = my_max > 0 ? my_max : 10;
        min = my_min > 0 && my_min < max ? my_min : 1;
    }
    class_c(int my_max, int my_min, int my_middle) {
        max = my_max > 0 ? my_max : 10;
        min = my_min > 0 && my_min < max ? my_min : 1;
        middle = my_middle < max && my_middle > min ? my_middle : 5;
    }
}; */

class class_c {
public:
    int max;
    int min;
    int middle;

    class_c(int my_max) {
        max = my_max > 0 ? my_max : 10;
    }
    class_c(int my_max, int my_min) : class_c(my_max) {
        min = my_min > 0 && my_min < max ? my_min : 1;
    }
    class_c(int my_max, int my_min, int my_middle) : class_c(my_max, my_min) {
        middle = my_middle < max && my_middle > min ? my_middle : 5;
    }
};

int main() {

    class_c c1{10,1,0};
    std::cout << c1.max << std::endl;
    std::cout << c1.min << std::endl;
    std::cout << c1.middle << std::endl;

    class_c c2{ 1, 3, 2};
    std::cout << c2.max << std::endl;
    std::cout << c2.min << std::endl;
}
```

## Co pokazuje ten przykład

Klasa `class_c` zawiera trzy publiczne pola:

* `max`
* `min`
* `middle`

oraz trzy konstruktory:

* `class_c(int my_max)`
* `class_c(int my_max, int my_min)`
* `class_c(int my_max, int my_min, int my_middle)`

Każdy kolejny konstruktor rozszerza inicjalizację o następne pole, ale nie powtarza już wcześniejszego kodu. Zamiast tego używa **delegacji konstruktora**.

## Delegacja konstruktorów

Delegacja konstruktorów polega na tym, że jeden konstruktor klasy wywołuje inny konstruktor tej samej klasy.

W tym programie widać to tutaj:

```cpp
class_c(int my_max, int my_min) : class_c(my_max)
```

oraz tutaj:

```cpp
class_c(int my_max, int my_min, int my_middle) : class_c(my_max, my_min)
```

To oznacza, że:

* konstruktor z dwoma argumentami najpierw wywołuje konstruktor z jednym argumentem,
* konstruktor z trzema argumentami najpierw wywołuje konstruktor z dwoma argumentami.

Dzięki temu logika ustawiania `max` znajduje się tylko w jednym miejscu, a logika ustawiania `min` tylko w jednym miejscu.

## Dlaczego to jest przydatne

W zakomentowanej wersji programu każdy konstruktor osobno powtarzał wcześniejsze instrukcje:

* ustawienie `max`,
* potem ustawienie `min`,
* potem ustawienie `middle`.

Takie podejście działa, ale ma wadę: ten sam kod pojawia się w wielu miejscach. Jeśli później trzeba zmienić sposób inicjalizacji `max`, trzeba pamiętać, by poprawić wszystkie konstruktory.

Delegacja rozwiązuje ten problem, ponieważ każda część logiki występuje tylko raz.

## Działanie poszczególnych konstruktorów

### Konstruktor z jednym argumentem

```cpp
class_c(int my_max) {
    max = my_max > 0 ? my_max : 10;
}
```

Ten konstruktor ustawia pole `max`:

* jeśli `my_max > 0`, to `max = my_max`,
* w przeciwnym razie `max = 10`.

### Konstruktor z dwoma argumentami

```cpp
class_c(int my_max, int my_min) : class_c(my_max) {
    min = my_min > 0 && my_min < max ? my_min : 1;
}
```

Najpierw wywoływany jest konstruktor `class_c(my_max)`, więc pole `max` jest już poprawnie ustawione.

Dopiero potem ustawiane jest pole `min`:

* jeśli `my_min > 0` i `my_min < max`, to `min = my_min`,
* w przeciwnym razie `min = 1`.

### Konstruktor z trzema argumentami

```cpp
class_c(int my_max, int my_min, int my_middle) : class_c(my_max, my_min) {
    middle = my_middle < max && my_middle > min ? my_middle : 5;
}
```

Najpierw wywoływany jest konstruktor z dwoma argumentami, więc pola `max` i `min` są już ustawione.

Następnie ustawiane jest pole `middle`:

* jeśli `my_middle < max` i `my_middle > min`, to `middle = my_middle`,
* w przeciwnym razie `middle = 5`.

## Funkcja `main()`

W funkcji `main` tworzone są dwa obiekty.

### Obiekt `c1`

```cpp
class_c c1{10,1,0};
```

Przebieg inicjalizacji:

* `max = 10`, bo `10 > 0`,
* `min = 1`, bo `1 > 0` i `1 < 10`,
* `middle = 5`, bo `0 > min` jest fałszywe.

Dlatego program wypisze dla `c1`:

```text
10
1
5
```

### Obiekt `c2`

```cpp
class_c c2{1, 3, 2};
```

Przebieg inicjalizacji:

* `max = 1`, bo `1 > 0`,
* `min = 1`, bo `3 < max` jest fałszywe, więc użyta zostaje wartość domyślna `1`,
* `middle = 5`, bo konstruktor trzyargumentowy sprawdza warunek `2 < max && 2 > min`, czyli `2 < 1`, co jest fałszywe.

W programie wypisywane są jednak tylko `max` i `min` dla `c2`, więc wynik będzie:

```text
1
1
```

## Pełny wynik działania programu

Program wypisze:

```text
10
1
5
1
1
```

## Uwaga merytoryczna

W tym przykładzie pola `max`, `min` i `middle` są publiczne, co upraszcza kod dydaktyczny, ale w praktyce częściej umieszcza się je w sekcji `private` i udostępnia przez metody klasy.

Warto też zauważyć, że w klasie

