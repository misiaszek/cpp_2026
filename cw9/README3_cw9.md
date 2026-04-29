# `cw9-3.cpp` – polimorfizm z użyciem wskaźników do klasy bazowej

Program pokazuje, jak działa **polimorfizm dynamiczny** w C++, gdy w jednym kontenerze przechowujemy wskaźniki do obiektów klasy bazowej i klasy pochodnej.

To bardzo ważny przykład, ponieważ łączy kilka istotnych tematów:

- dziedziczenie,
- metody wirtualne,
- wskaźniki do klasy bazowej,
- przechowywanie obiektów różnych typów w jednym `std::vector`,
- oraz dostęp do wspólnego interfejsu.

## Kod programu

```cpp
#include <iostream>
#include <vector>

class Base
{
protected:
    int m_value {};

public:
    Base(int value)
        : m_value{ value }
    {
    }

    virtual std::string_view getName() const { return "Base"; }
    int getValue() const { return m_value; }
};

class Derived: public Base
{
public:
    Derived(int value)
        : Base{ value }
    {
    }

    std::string_view getName() const { return "Derived"; }
    int getValueDoubled() const { return m_value * 2; }
};

int main() {
   std::vector<Base*> vm;
   Base* p1 = new Base(1);
   Base* p2 = new Base(2);
   Derived* p3 = new Derived(3);
   vm.push_back(p1);
   vm.push_back(p2);
   vm.push_back(p3);
   for(auto v : vm) std::cout << v->getName() << "\n";
}
```

## Co pokazuje ten przykład

Program definiuje dwie klasy:

- `Base`
- `Derived`

Klasa `Derived` dziedziczy publicznie po `Base`:

```cpp
class Derived : public Base
```

W klasie bazowej znajduje się metoda wirtualna:

```cpp
virtual std::string_view getName() const { return "Base"; }
```

a klasa pochodna dostarcza własną wersję tej samej metody:

```cpp
std::string_view getName() const { return "Derived"; }
```

Dzięki temu, gdy wywołujemy `getName()` przez wskaźnik do klasy bazowej, C++ potrafi wybrać właściwą wersję metody zależnie od rzeczywistego typu obiektu.

---

## Klasa `Base`

Klasa bazowa zawiera:

- chronione pole `m_value`,
- konstruktor przyjmujący wartość,
- metodę wirtualną `getName()`,
- zwykłą metodę `getValue()`.

### Pole `m_value`

```cpp
protected:
    int m_value {};
```

Pole jest oznaczone jako `protected`, więc:

- nie jest publicznie dostępne z zewnątrz,
- ale klasa pochodna może z niego korzystać bezpośrednio.

### Konstruktor

```cpp
Base(int value)
    : m_value{ value }
{
}
```

Konstruktor ustawia pole `m_value` na wartość przekazaną przy tworzeniu obiektu.

### Metoda wirtualna `getName()`

```cpp
virtual std::string_view getName() const { return "Base"; }
```

To najważniejsza metoda w tym przykładzie.

Słowo kluczowe `virtual` oznacza, że gdy metoda będzie wywoływana przez wskaźnik lub referencję do klasy bazowej, C++ ma zdecydować, którą wersję uruchomić na podstawie **rzeczywistego typu obiektu**, a nie tylko typu wskaźnika.

### Metoda `getValue()`

```cpp
int getValue() const { return m_value; }
```

To zwykła metoda niewirtualna, zwracająca wartość pola `m_value`.

---

## Klasa `Derived`

Klasa pochodna dziedziczy po `Base`:

```cpp
class Derived: public Base
```

Zawiera:

- konstruktor wywołujący konstruktor klasy bazowej,
- własną wersję metody `getName()`,
- dodatkową metodę `getValueDoubled()`.

### Konstruktor klasy pochodnej

```cpp
Derived(int value)
    : Base{ value }
{
}
```

To oznacza, że obiekt klasy `Derived` przy tworzeniu przekazuje wartość do konstruktora klasy bazowej.

Najpierw tworzona jest część bazowa obiektu, a dopiero potem część pochodna.

### Nadpisanie `getName()`

```cpp
std::string_view getName() const { return "Derived"; }
```

Ta metoda przesłania wersję klasy bazowej.

Ponieważ metoda w klasie bazowej była `virtual`, tutaj zachowanie staje się polimorficzne.

### Dodatkowa metoda `getValueDoubled()`

```cpp
int getValueDoubled() const { return m_value * 2; }
```

Ta metoda pokazuje dwie rzeczy:

1. klasa pochodna ma dostęp do `m_value`, bo pole jest `protected`,
2. klasa pochodna może dodawać własne funkcje, których nie ma klasa bazowa.

Metoda zwraca podwojoną wartość pola.

---

## Kontener `std::vector<Base*>`

W `main()` tworzony jest wektor wskaźników do klasy bazowej:

```cpp
std::vector<Base*> vm;
```

To bardzo ważny moment programu.

Wektor ten może przechowywać adresy:

- obiektów klasy `Base`,
- obiektów klasy `Derived`,

bo wskaźnik do klasy pochodnej można przypisać do wskaźnika do klasy bazowej.

To nazywa się **rzutowaniem w górę** (*upcasting*).

---

## Tworzenie obiektów

Program tworzy trzy obiekty dynamicznie:

```cpp
Base* p1 = new Base(1);
Base* p2 = new Base(2);
Derived* p3 = new Derived(3);
```

### Co tu się dzieje?

- `p1` wskazuje na obiekt `Base` z wartością `1`,
- `p2` wskazuje na obiekt `Base` z wartością `2`,
- `p3` wskazuje na obiekt `Derived` z wartością `3`.

Następnie wszystkie trzy wskaźniki trafiają do jednego wektora:

```cpp
vm.push_back(p1);
vm.push_back(p2);
vm.push_back(p3);
```

W przypadku `p3` następuje automatyczne rzutowanie z `Derived*` do `Base*`.

Dzięki temu jeden kontener może przechowywać obiekty różnych klas należących do tej samej hierarchii.

---

## Pętla i polimorfizm

Na końcu programu wykonywana jest pętla:

```cpp
for(auto v : vm) std::cout << v->getName() << "\n";
```

Każdy element `v` ma typ `Base*`, ale może wskazywać na różne rzeczywiste obiekty.

### Dla `p1`

`v` wskazuje na obiekt `Base`, więc:

```cpp
v->getName()
```

zwraca:

```text
Base
```

### Dla `p2`

Znów wskazuje na `Base`, więc wynik to:

```text
Base
```

### Dla `p3`

Choć `v` ma typ `Base*`, to wskazuje na obiekt `Derived`.

Ponieważ `getName()` jest metodą wirtualną, wywołana zostaje wersja z klasy pochodnej:

```text
Derived
```

To właśnie jest sedno polimorfizmu dynamicznego.

---

## Wynik działania programu

Program wypisze:

```text
Base
Base
Derived
```

To pokazuje, że jeden kontener może przechowywać wskaźniki do różnych obiektów z tej samej hierarchii klas, a metoda wirtualna pozwala każdemu obiektowi „zachować własne zachowanie”.

---

## Dlaczego `virtual` jest tu kluczowe

Gdyby metoda `getName()` w klasie `Base` nie była zadeklarowana jako `virtual`, to wywołanie:

```cpp
v->getName()
```

dla każdego elementu wektora używałoby wersji wynikającej z typu wskaźnika, czyli zawsze:

```cpp
Base::getName()
```

Wtedy program wypisałby:

```text
Base
Base
Base
```

A więc nie byłoby prawdziwego polimorfizmu.

---

## Rola `protected`

Pole:

```cpp
protected:
    int m_value {};
```

umożliwia klasie `Derived` bezpośredni dostęp do danych klasy bazowej.

Dzięki temu metoda:

```cpp
int getValueDoubled() const { return m_value * 2; }
```

może odczytać `m_value` bez wywoływania gettera.

To działa, ale projektowo warto pamiętać, że `protected` osłabia enkapsulację bardziej niż `private`.

W większych projektach często preferuje się pola `private` i dostęp przez metody publiczne lub chronione.

---

## Uwaga praktyczna – wyciek pamięci

W tym programie obiekty są tworzone przez `new`:

```cpp
new Base(1)
new Base(2)
new Derived(3)
```

ale nigdzie nie ma:

```cpp
delete
```

To oznacza, że program powoduje **wyciek pamięci**.

Dla krótkiego programu demonstracyjnego nie ma to dużego znaczenia praktycznego, ale merytorycznie warto to zauważyć.

Lepsza wersja programu powinna na końcu usunąć obiekty, np. tak:

```cpp
for (auto v : vm)
    delete v;
```

Jeszcze lepszym rozwiązaniem w nowoczesnym C++ byłoby użycie inteligentnych wskaźników, np. `std::unique_ptr`.

---

## Bardzo ważna uwaga o destruktorze

Klasa `Base` ma metodę wirtualną `getName()`, ale nie ma jawnie zdefiniowanego **wirtualnego destruktora**.

W praktyce, jeśli zamierzamy usuwać obiekty klasy pochodnej przez wskaźnik do klasy bazowej, klasa bazowa powinna mieć destruktor wirtualny, np.:

```cpp
virtual ~Base() = default;
```

To bardzo ważna zasada projektowania klas polimorficznych.

W tym konkretnym programie nie wykonujemy `delete` przez `Base*`, więc błąd się nie ujawnia, ale projektowo byłoby to zalecane.

---

## Czego uczy ten przykład

Program pokazuje bardzo ważne mechanizmy C++:

### 1. Dziedziczenie publiczne
Klasa pochodna może rozszerzać klasę bazową.

### 2. Metody wirtualne
Pozwalają na dynamiczny wybór wersji funkcji zależnie od rzeczywistego typu obiektu.

### 3. Polimorfizm dynamiczny
Wskaźnik do klasy bazowej może wskazywać na obiekty różnych klas pochodnych.

### 4. Kontenery wskaźników
Można przechowywać różne obiekty z jednej hierarchii klas w jednym `std::vector`.

### 5. `protected`
Klasa pochodna może używać niektórych danych klasy bazowej bezpośrednio.

---

## Podsumowanie

Program `cw9-3.cpp` pokazuje, jak działa polimorfizm z użyciem:

- klasy bazowej,
- klasy pochodnej,
- metody wirtualnej,
- wskaźników do klasy bazowej,
- oraz kontenera `std::vector<Base*>`.

Najważniejsza idea tego przykładu jest taka:

> jeden wspólny interfejs klasy bazowej pozwala przechowywać i obsługiwać obiekty różnych klas pochodnych, a metoda wirtualna zapewnia, że każdy obiekt zachowa własne zachowanie.

To bardzo ważny krok w stronę bardziej zaawansowanego programowania obiektowego w C++.
