# `cw5-1.cpp` – przeciążenie operatora `<<` dla klasy `Fraction`

Program pokazuje, jak przeciążyć operator strumieniowego wyjścia `<<` dla własnej klasy, aby obiekty można było wygodnie wypisywać za pomocą `std::cout`.

W tym przykładzie klasa `Fraction` reprezentuje ułamek zapisany jako licznik i mianownik. Dzięki przeciążeniu operatora `<<` obiekty tej klasy można wypisywać w postaci:

```text
licznik/mianownik
```

## Kod programu

```cpp
#include <iostream>
#include <stdexcept>

class Fraction {
private:
    int numerator;
    int denominator;

public:
    // Konstruktor z parametrami
    Fraction(int num = 0, int denom = 1) : numerator(num), denominator(denom) {}
    friend std::ostream& operator<<(std::ostream& os, const Fraction& f);
};

std::ostream& operator<<(std::ostream& os, const Fraction& f) {
    os << f.numerator << "/" << f.denominator;
    return os;
}

int main() {
    Fraction f1;
    Fraction f2(1, 2);

    std::cout << f1 << " " << f2 << std::endl;

    operator<<(operator<<(operator<<(std::cout, f1), " "), f2);

    return 0;
}
```

## Co pokazuje ten przykład

Program demonstruje:

* definicję prostej klasy `Fraction`,
* konstruktor z wartościami domyślnymi,
* deklarację funkcji zaprzyjaźnionej `operator<<`,
* definicję przeciążonego operatora poza klasą,
* wypisywanie obiektów klasy przez `std::cout`,
* fakt, że zapis z operatorami można rozumieć jako zwykłe wywołania funkcji.

## Klasa `Fraction`

Klasa zawiera dwa prywatne pola:

* `numerator` – licznik,
* `denominator` – mianownik.

```cpp
class Fraction {
private:
    int numerator;
    int denominator;
```

Dane są prywatne, więc kod spoza klasy nie może odczytać ich bezpośrednio. To ważne, bo przeciążony operator `<<` będzie potrzebował specjalnego dostępu do tych pól.

## Konstruktor z parametrami domyślnymi

Konstruktor ma postać:

```cpp
Fraction(int num = 0, int denom = 1) : numerator(num), denominator(denom) {}
```

Oznacza to, że:

* jeśli nie przekażemy argumentów, powstanie ułamek `0/1`,
* jeśli przekażemy dwa argumenty, zostaną one zapisane jako licznik i mianownik.

W programie:

```cpp
Fraction f1;
Fraction f2(1, 2);
```

powstają więc obiekty:

* `f1` = `0/1`,
* `f2` = `1/2`.

## Deklaracja operatora `<<` jako `friend`

Wewnątrz klasy znajduje się deklaracja:

```cpp
friend std::ostream& operator<<(std::ostream& os, const Fraction& f);
```

To oznacza, że funkcja `operator<<` jest funkcją zaprzyjaźnioną klasy `Fraction`.

Dzięki temu może odczytywać prywatne pola `numerator` i `denominator`, mimo że nie jest metodą klasy.

### Dlaczego użyto `friend`

Bez `friend` funkcja zewnętrzna:

```cpp
std::ostream& operator<<(std::ostream& os, const Fraction& f)
```

nie mogłaby użyć:

```cpp
f.numerator
f.denominator
```

bo są to pola prywatne.

## Definicja przeciążonego operatora

Operator został zdefiniowany poza klasą:

```cpp
std::ostream& operator<<(std::ostream& os, const Fraction& f) {
    os << f.numerator << "/" << f.denominator;
    return os;
}
```

### Jak działa ten operator

Parametry funkcji to:

* `std::ostream& os` – strumień wyjściowy, na przykład `std::cout`,
* `const Fraction& f` – obiekt ułamka, który ma zostać wypisany.

Wewnątrz funkcji wykonywany jest zapis:

```cpp
os << f.numerator << "/" << f.denominator;
```

czyli do strumienia trafia tekst w postaci:

```text
licznik/mianownik
```

Na końcu funkcja zwraca:

```cpp
return os;
```

To bardzo ważne, ponieważ umożliwia łączenie wielu operatorów `<<` w jednym wyrażeniu.

## Dlaczego zwracany jest `std::ostream&`

Operator `<<` zwraca referencję do tego samego strumienia, aby można było pisać:

```cpp
std::cout << f1 << " " << f2 << std::endl;
```

Działa to łańcuchowo:

1. `std::cout << f1` zwraca `std::cout`,
2. potem na tym samym strumieniu wykonywane jest `<< " "`,
3. potem `<< f2`,
4. na końcu `<< std::endl`.

Gdyby operator nic nie zwracał, taki zapis nie byłby możliwy.

## Wypisywanie w `main()`

Program używa:

```cpp
std::cout << f1 << " " << f2 << std::endl;
```

Ponieważ:

* `f1` ma wartość `0/1`,
* `f2` ma wartość `1/2`,

na ekran trafi:

```text
0/1 1/2
```

## Jawne wywołanie operatora jako funkcji

W programie znajduje się też instrukcja:

```cpp
operator<<(operator<<(operator<<(std::cout, f1), " "), f2);
```

To pokazuje, że operator `<<` jest w rzeczywistości zwykłą funkcją, tylko zapisywaną w wygodniejszej formie operatorowej.

Zapis:

```cpp
std::cout << f1 << " " << f2
```

można rozumieć właśnie jako serię zagnieżdżonych wywołań `operator<<`.

To bardzo cenna obserwacja dydaktyczna: przeciążanie operatorów nie tworzy nowego mechanizmu działania języka, tylko pozwala nadać zwykłym funkcjom specjalną składnię.

## Wynik działania programu

Program wypisze:

```text
0/1 1/2
0/1 1/2
```

Pierwsza linia pochodzi z klasycznego zapisu operatorowego:

```cpp
std::cout << f1 << " " << f2 << std::endl;
```

Druga linia pochodzi z jawnego wywołania `operator<<` jako funkcji.

Uwaga: w drugiej instrukcji nie ma `std::endl`, więc dokładny układ końca linii może zależeć od tego, co wcześniej zostało wypisane, ale sens działania pozostaje taki sam.

## Uwaga merytoryczna

Program dołącza nagłówek:

```cpp
#include <stdexcept>
```

ale w tym przykładzie nie jest on używany. To nie jest błąd logiczny programu, tylko zbędny nagłówek.

Warto też zauważyć, że konstruktor nie sprawdza, czy mianownik jest równy `0`. W bardziej kompletnej wersji klasy `Fraction` należałoby dodać taką walidację, ponieważ ułamek z mianownikiem `0` jest matematycznie niepoprawny.

## Kiedy operator `<<` definiuje się jako funkcję zewnętrzną

Dla klas wypisywanych do strumienia operator `<<` bardzo często definiuje się jako funkcję zewnętrzną, a nie metodę klasy. Powód jest prosty:

w wyrażeniu:

```cpp
std::cout << f
```

lewym argumentem jest `std::cout`, czyli obiekt klasy strumienia, a nie obiekt `Fraction`.

Dlatego naturalna forma to funkcja przyjmująca:

* strumień jako pierwszy argument,
* obiekt klasy jako drugi argument.

## Podsumowanie

Program `cw5-1.cpp` pokazuje:

* definicję klasy `Fraction`,
* konstruktor z wartościami domyślnymi,
* deklarację funkcji zaprzyjaźnionej,
* przeciążenie operatora `<<` dla własnej klasy,
* zwracanie `std::ostream&` w celu łańcuchowania operatorów,
* związek między zapisem operatorowym a zwykłym wywołaniem funkcji.

Jest to bardzo ważny przykład, ponieważ pokazuje jeden z najczęściej przeciążanych operatorów w C++ i uczy, jak dostosować własną klasę do naturalnej współpracy ze strumieniami wejścia i wyjścia.
