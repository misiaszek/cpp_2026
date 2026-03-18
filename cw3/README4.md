# `cw3-4.cpp` – funkcja zaprzyjaźniona (`friend`)

Program pokazuje mechanizm **przyjaźni** w C++, czyli sytuację, w której zwykła funkcja spoza klasy otrzymuje prawo dostępu do jej prywatnych składowych.

Na tym przykładzie widać, że funkcja `print(const Accumulator&)` nie jest metodą klasy `Accumulator`, ale mimo to może odczytać prywatne pole `m_value`, ponieważ została zadeklarowana jako **przyjaciel klasy**.

## Kod programu

```cpp
#include <iostream>

class Accumulator
{
private:
    int m_value { 0 };

public:
    void add(int value) { m_value += value; }

    // Here is the friend declaration that makes non-member function void print(const Accumulator& accumulator) a friend of Accumulator
    friend void print(const Accumulator& accumulator);
};

void print(const Accumulator& accumulator)
{
    // Because print() is a friend of Accumulator
    // it can access the private members of Accumulator
    std::cout << accumulator.m_value;
}

int main()
{
    Accumulator acc{};
    acc.add(5); // add 5 to the accumulator

    print(acc); // call the print() non-member function

    return 0;
}
```

## Co pokazuje ten przykład

Klasa `Accumulator` zawiera:

* prywatne pole `m_value`,
* publiczną metodę `add(int)`,
* deklarację przyjaźni dla funkcji `print(const Accumulator&)`.

Najważniejszy element programu to linia:

```cpp
friend void print(const Accumulator& accumulator);
```

To właśnie ona nadaje funkcji `print` specjalne uprawnienie: mimo że `print` nie jest metodą klasy, może odczytać prywatne pole `m_value`.

## Czym jest funkcja zaprzyjaźniona

Funkcja zaprzyjaźniona to zwykła funkcja niebędąca metodą klasy, która dostała prawo dostępu do jej elementów prywatnych i chronionych.

W tym przykładzie funkcja:

```cpp
void print(const Accumulator& accumulator)
```

jest zdefiniowana poza klasą, ale może użyć:

```cpp
accumulator.m_value
```

co normalnie byłoby zabronione, bo `m_value` jest polem prywatnym.

## Jak deklaruje się przyjaciela w ciele klasy

Składnia deklaracji przyjaźni w ciele klasy wygląda tak:

```cpp
friend typ_zwracany nazwa_funkcji(parametry);
```

W omawianym programie ma ona postać:

```cpp
friend void print(const Accumulator& accumulator);
```

Rozbijmy to na części:

* `friend` – słowo kluczowe informujące, że jest to deklaracja przyjaźni,
* `void` – typ zwracany funkcji,
* `print` – nazwa funkcji,
* `(const Accumulator& accumulator)` – lista parametrów.

To jest **pełna deklaracja funkcji**, poprzedzona słowem `friend`.

## Bardzo ważna rzecz: to nie jest metoda klasy

Choć deklaracja `friend` znajduje się wewnątrz definicji klasy, nie oznacza to, że funkcja staje się metodą.

Funkcja:

```cpp
friend void print(const Accumulator& accumulator);
```

* nie ma ukrytego wskaźnika `this`,
* nie wywołuje się jej przez `acc.print()`,
* nadal jest zwykłą funkcją zewnętrzną,
* wywołuje się ją normalnie:

```cpp
print(acc);
```

Deklaracja przyjaźni daje jej tylko dodatkowe uprawnienia dostępu.

## Jak działa ten program krok po kroku

### 1. Tworzenie obiektu

```cpp
Accumulator acc{};
```

Powstaje obiekt `acc`, którego pole `m_value` ma początkowo wartość `0`.

### 2. Zmiana stanu obiektu

```cpp
acc.add(5);
```

Metoda `add` zwiększa `m_value` o `5`, więc po tej instrukcji:

```cpp
m_value == 5
```

### 3. Wywołanie funkcji zaprzyjaźnionej

```cpp
print(acc);
```

Wywoływana jest funkcja zewnętrzna `print`, która otrzymuje obiekt przez referencję do `const`.

### 4. Dostęp do prywatnego pola

Wewnątrz funkcji:

```cpp
std::cout << accumulator.m_value;
```

następuje odczyt pola `m_value`.

To jest legalne tylko dlatego, że wcześniej w klasie pojawiła się deklaracja:

```cpp
friend void print(const Accumulator& accumulator);
```

## Wynik działania programu

Program wypisze:

```text
5
```

## Co by się stało bez `friend`

Gdyby z klasy usunąć deklarację:

```cpp
friend void print(const Accumulator& accumulator);
```

to definicja funkcji:

```cpp
void print(const Accumulator& accumulator)
{
    std::cout << accumulator.m_value;
}
```

nie skompilowałaby się, ponieważ `m_value` jest polem prywatnym klasy `Accumulator`.

Czyli `friend` nie zmienia widoczności pola w całym programie, tylko daje konkretnemu wskazanemu elementowi specjalny dostęp.

## Ogólna składnia przyjaźni w C++

W C++ można zaprzyjaźniać nie tylko pojedyncze funkcje, ale również inne funkcje składowe, całe klasy, a nawet szablony.

Najczęstsze formy składni to:

### 1. Funkcja niebędąca metodą

```cpp
friend void print(const MyClass& obj);
```

### 2. Cała inna klasa

```cpp
friend class AnotherClass;
```

Wtedy wszystkie metody `AnotherClass` mają dostęp do prywatnych elementów tej klasy.

### 3. Pojedyncza metoda innej klasy

To jest możliwe, ale składnia jest bardziej rozbudowana i wymaga wcześniejszej znajomości deklaracji tej klasy.

## Najważniejsze cechy przyjaźni w C++

### Przyjaźń nie jest dziedziczona

Jeśli klasa `A` zaprzyjaźni klasę `B`, to klasy pochodne po `B` nie stają się automatycznie przyjaciółmi `A`.

### Przyjaźń nie jest symetryczna

Jeśli `A` zaprzyjaźni `B`, to nie oznacza, że `B` automatycznie zaprzyjaźnia `A`.

### Przyjaźń nie jest przechodnia

Jeśli `A` zaprzyjaźni `B`, a `B` zaprzyjaźni `C`, to `C` nie staje się automatycznie przyjacielem `A`.

To ważne, bo przyjaźń w C++ nadaje bardzo konkretne, lokalne uprawnienie i nie rozprzestrzenia się automatycznie dalej.

## Dlaczego używa się `friend`

Mechanizm `friend` stosuje się wtedy, gdy chcemy zachować logiczny związek funkcji z klasą, ale jednocześnie nie chcemy robić z niej metody.

Typowe przypadki to:

* funkcje wypisujące obiekt,
* przeciążenia operatorów,
* funkcje pomocnicze wymagające dostępu do wnętrza obiektu,
* współpraca dwóch silnie powiązanych klas.

W tym przykładzie funkcja `print` jest dobrym kandydatem, bo logicznie operuje na `Accumulator`, ale nie musi być metodą.

## Czy `friend` jest dobrą praktyką

`friend` jest legalnym i czasem bardzo użytecznym mechanizmem, ale powinien być stosowany świadomie.

Dlaczego?

Bo przyjaźń osłabia enkapsulację: zewnętrzna funkcja dostaje dostęp do prywatnych danych klasy.

Dlatego zwykle:

* używa się `friend` wtedy, gdy naprawdę ma to sens projektowy,
* nie należy nadużywać tego mechanizmu,
* trzeba pamiętać, że każda deklaracja `friend` poszerza krąg kodu mającego dostęp do wnętrza klasy.

## Podsumowanie

Program `cw3-4.cpp` pokazuje:

* czym jest funkcja zaprzyjaźniona,
* jak deklaruje się przyjaciela w ciele klasy,
* że funkcja `friend` nie staje się metodą klasy,
* że może ona mimo to odczytywać prywatne pola obiektu,
* jak działa składnia:

```cpp
friend void print(const Accumulator& accumulator);
```

To bardzo ważny przykład, ponieważ pokazuje jeden z wyjątków od zwykłej zasady, że tylko metody klasy mają dostęp do jej prywatnych danych. Dzięki `friend` można świadomie przyznać taki dostęp wybranej funkcji lub klasie.
