# `cw7-1.cpp` – destruktor i czas życia obiektów w C++

Program pokazuje, czym jest **destruktor** w C++, kiedy jest wywoływany oraz jak działa czas życia obiektów lokalnych tworzonych na stosie. Jest to bardzo ważny przykład, ponieważ uczy jednej z podstawowych zasad języka: obiekt zostaje automatycznie zniszczony, gdy wychodzi poza swój zakres.

## Kod programu

```cpp
#include <iostream>

class Simple
{
private:
    int m_id {};

public:
    Simple(int id)
        : m_id { id }
    {
        std::cout << "Constructing Simple " << m_id << '\n';
    }

    ~Simple() // here's our destructor
    {
        std::cout << "Destructing Simple " << m_id << '\n';
    }

    int getID() const { return m_id; }
};

int main()
{
    // Allocate a Simple
    Simple simple1{ 1 };
    {
        Simple simple2{ 2 };
    } // simple2 dies here

    return 0;
} // simple1 dies here
```

## Co pokazuje ten przykład

Program demonstruje:

* definicję klasy z konstruktorem i destruktorem,
* tworzenie obiektów lokalnych,
* działanie zakresów blokowych,
* automatyczne niszczenie obiektów przy wyjściu z zakresu,
* kolejność wywoływania konstruktorów i destruktorów.

## Klasa `Simple`

Klasa `Simple` zawiera jedno prywatne pole:

```cpp
int m_id {};
```

To pole przechowuje identyfikator obiektu. Dzięki temu łatwo zobaczyć, który obiekt jest właśnie tworzony lub niszczony.

## Konstruktor

Konstruktor klasy ma postać:

```cpp
Simple(int id)
    : m_id { id }
{
    std::cout << "Constructing Simple " << m_id << '\n';
}
```

### Co robi konstruktor

* przyjmuje argument `id`,
* zapisuje go do pola `m_id`,
* wypisuje komunikat o utworzeniu obiektu.

Konstruktor jest wywoływany automatycznie w chwili tworzenia obiektu.

Na przykład:

```cpp
Simple simple1{ 1 };
```

powoduje utworzenie obiektu `simple1` i wypisanie:

```text
Constructing Simple 1
```

## Destruktor

Destruktor został zdefiniowany tak:

```cpp
~Simple()
{
    std::cout << "Destructing Simple " << m_id << '\n';
}
```

### Co to jest destruktor

Destruktor to specjalna funkcja składowa klasy, która:

* ma nazwę klasy poprzedzoną znakiem `~`,
* nie przyjmuje argumentów,
* nie zwraca żadnej wartości,
* jest wywoływana automatycznie, gdy obiekt jest niszczony.

W tym przykładzie destruktor nie zwalnia pamięci ani zasobów systemowych, tylko wypisuje komunikat. Dzięki temu można łatwo zaobserwować moment zniszczenia obiektu.

## Czas życia obiektu lokalnego

Obiekty `simple1` i `simple2` są obiektami lokalnymi, czyli takimi, które są tworzone wewnątrz funkcji lub bloku.

Taki obiekt:

* powstaje w momencie dojścia programu do jego deklaracji,
* żyje do końca zakresu, w którym został utworzony,
* jest automatycznie niszczony przy wyjściu z tego zakresu.

## Zakres blokowy

W `main()` mamy taki fragment:

```cpp
Simple simple1{ 1 };
{
    Simple simple2{ 2 };
} // simple2 dies here
```

Wewnętrzne nawiasy klamrowe tworzą osobny blok.

To oznacza, że:

* `simple1` należy do całej funkcji `main()`,
* `simple2` należy tylko do wewnętrznego bloku.

Dlatego `simple2` zostanie zniszczony wcześniej niż `simple1`.

## Przebieg działania programu

### 1. Tworzenie `simple1`

Program wykonuje:

```cpp
Simple simple1{ 1 };
```

Wywołany zostaje konstruktor i wypisany zostaje komunikat:

```text
Constructing Simple 1
```

### 2. Wejście do wewnętrznego bloku

Następnie program wchodzi do dodatkowego zakresu:

```cpp
{
    Simple simple2{ 2 };
}
```

Tworzony jest obiekt `simple2`, więc wypisane zostaje:

```text
Constructing Simple 2
```

### 3. Wyjście z wewnętrznego bloku

Po dojściu do końca tego bloku obiekt `simple2` przestaje istnieć. Automatycznie wywołuje się jego destruktor:

```text
Destructing Simple 2
```

### 4. Wyjście z `main()`

Na końcu funkcji `main()` kończy się życie obiektu `simple1`, więc uruchamia się jego destruktor:

```text
Destructing Simple 1
```

## Kolejność niszczenia obiektów

To bardzo ważna zasada:

* obiekty lokalne są niszczone w odwrotnej kolejności do kolejności tworzenia,
* ale tylko w obrębie swojego zakresu.

W tym programie:

1. najpierw tworzony jest `simple1`,
2. potem tworzony jest `simple2`,
3. potem niszczony jest `simple2`,
4. na końcu niszczony jest `simple1`.

## Przykładowy wynik działania programu

Program wypisze:

```text
Constructing Simple 1
Constructing Simple 2
Destructing Simple 2
Destructing Simple 1
```

To bardzo dobrze pokazuje, że obiekty są niszczone automatycznie po opuszczeniu swojego zakresu.

## Dlaczego destruktory są ważne

W tym przykładzie destruktor tylko wypisuje tekst, ale w prawdziwych programach destruktor często służy do:

* zwalniania pamięci dynamicznej,
* zamykania plików,
* zwalniania uchwytów systemowych,
* odblokowywania mutexów,
* sprzątania zasobów związanych z obiektem.

To jest jedna z podstaw mechanizmu RAII w C++.

## `getID()`

W klasie znajduje się także metoda:

```cpp
int getID() const { return m_id; }
```

Jest to prosty getter zwracający identyfikator obiektu. W tym programie nie jest używany, ale pokazuje typowy sposób udostępniania prywatnych danych klasy.

## Najważniejsza idea przykładu

Ten program uczy, że w C++:

* obiekt lokalny nie musi być ręcznie niszczony,
* kompilator i środowisko uruchomieniowe robią to automatycznie,
* destruktor jest wywoływany samoczynnie w odpowiednim momencie,
* zakres obiektu decyduje o tym, kiedy zakończy się jego życie.

## Podsumowanie

Program `cw7-1.cpp` pokazuje:

* czym jest destruktor,
* kiedy destruktor jest wywoływany,
* jak działa czas życia obiektów lokalnych,
* jak zakres blokowy wpływa na moment zniszczenia obiektu,
* że obiekty są niszczone automatycznie w odwrotnej kolejności do ich tworzenia.

Jest to podstawowy i bardzo ważny przykład do zrozumienia zarządzania czasem życia obiektów w C++.
