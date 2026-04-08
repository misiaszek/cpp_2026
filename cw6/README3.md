# `cw6-3.cpp` – kompozycja obiektów w C++

Program pokazuje mechanizm **kompozycji** w programowaniu obiektowym. Kompozycja oznacza, że jeden obiekt **zawiera inny obiekt jako swoją część składową**. W tym przykładzie obiekt klasy `Samochod` zawiera obiekt klasy `Silnik`.

Jest to bardzo ważna relacja w projektowaniu klas, ponieważ pozwala budować bardziej złożone obiekty z prostszych elementów.

## Kod programu

```cpp
#include <iostream>
#include <string>

class Silnik {
public:
   Silnik(const std::string& typ) : typ(typ) {}
   void uruchom() const {
       std::cout << "Silnik " << typ << " uruchomiony." << std::endl;
   }
private:
   std::string typ;
};

class Samochod {
public:
   Samochod(const std::string& marka, const std::string& typSilnika)
       : marka(marka), silnik(typSilnika) {}
   void uruchom() const {
       std::cout << "Samochod " << marka << " uruchamia silnik." << std::endl;
       silnik.uruchom();
   }
private:
   std::string marka;
   Silnik silnik;
};

int main() {
   Samochod samochod("Toyota", "benzynowy");
   samochod.uruchom();
   return 0;
}
```

## Co pokazuje ten przykład

Program demonstruje:

* zdefiniowanie dwóch klas,
* umieszczenie jednego obiektu wewnątrz drugiego,
* inicjalizację obiektu składowego przez listę inicjalizacyjną,
* wywołanie metody obiektu zawartego w innym obiekcie,
* relację typu **całość–część**.

## Klasa `Silnik`

Klasa `Silnik` reprezentuje silnik samochodu.

Zawiera:

* prywatne pole `typ`,
* konstruktor ustawiający typ silnika,
* metodę `uruchom()`, która wypisuje komunikat.

```cpp
class Silnik {
public:
   Silnik(const std::string& typ) : typ(typ) {}
   void uruchom() const {
       std::cout << "Silnik " << typ << " uruchomiony." << std::endl;
   }
private:
   std::string typ;
};
```

### Konstruktor klasy `Silnik`

```cpp
Silnik(const std::string& typ) : typ(typ) {}
```

Konstruktor przyjmuje napis określający typ silnika, na przykład `"benzynowy"`, a następnie zapisuje go do pola klasy.

## Klasa `Samochod`

Klasa `Samochod` reprezentuje samochód.

Zawiera:

* prywatne pole `marka`,
* prywatny obiekt `silnik` typu `Silnik`,
* konstruktor ustawiający markę samochodu i tworzący silnik,
* metodę `uruchom()`, która uruchamia silnik.

```cpp
class Samochod {
public:
   Samochod(const std::string& marka, const std::string& typSilnika)
       : marka(marka), silnik(typSilnika) {}
   void uruchom() const {
       std::cout << "Samochod " << marka << " uruchamia silnik." << std::endl;
       silnik.uruchom();
   }
private:
   std::string marka;
   Silnik silnik;
};
```

## Na czym polega kompozycja w tym programie

Najważniejsza linia to:

```cpp
Silnik silnik;
```

znajdująca się wewnątrz klasy `Samochod`.

Oznacza to, że każdy obiekt klasy `Samochod` **zawiera w sobie** obiekt klasy `Silnik`.

Nie jest to wskaźnik, nie jest to referencja i nie jest to osobny obiekt przekazywany z zewnątrz. To pełnoprawna część składowa samochodu.

Właśnie to jest kompozycja:

* `Samochod` jest całością,
* `Silnik` jest częścią tej całości.

## Relacja „ma” zamiast „jest”

W programowaniu obiektowym kompozycję często opisuje się jako relację **has-a**:

* samochód **ma** silnik,
* silnik nie jest samochodem,
* samochód składa się między innymi z silnika.

To odróżnia kompozycję od dziedziczenia, które opisuje relację **is-a**:

* samochód **nie jest** silnikiem,
* więc tutaj nie ma dziedziczenia,
* jest właśnie kompozycja.

## Inicjalizacja obiektu składowego

Konstruktor klasy `Samochod` ma postać:

```cpp
Samochod(const std::string& marka, const std::string& typSilnika)
    : marka(marka), silnik(typSilnika) {}
```

To bardzo ważny fragment.

### Co tu się dzieje

* `marka(marka)` inicjalizuje pole `marka`,
* `silnik(typSilnika)` tworzy i inicjalizuje obiekt `silnik` klasy `Silnik`.

Czyli w chwili tworzenia obiektu `Samochod` od razu tworzony jest także jego silnik.

To właśnie typowe zachowanie dla kompozycji: obiekt złożony tworzy swoje części składowe razem z sobą.

## Dlaczego użyto listy inicjalizacyjnej

Obiekt `silnik` jest polem klasy, więc powinien zostać poprawnie utworzony już na etapie konstruowania obiektu `Samochod`.

Dlatego zapis:

```cpp
: silnik(typSilnika)
```

jest naturalnym i właściwym sposobem inicjalizacji obiektu składowego.

W przypadku obiektów składowych lista inicjalizacyjna jest bardzo ważna, bo pola klasy są tworzone **przed wejściem do ciała konstruktora**.

## Metoda `uruchom()` w klasie `Samochod`

Metoda:

```cpp
void uruchom() const {
    std::cout << "Samochod " << marka << " uruchamia silnik." << std::endl;
    silnik.uruchom();
}
```

najpierw wypisuje komunikat o samochodzie, a potem wywołuje metodę `uruchom()` obiektu `silnik`.

To pokazuje, że obiekt złożony może korzystać z zachowania swoich części.

Czyli `Samochod` nie tylko zawiera `Silnik`, ale też deleguje część pracy do tego obiektu.

## Przebieg działania programu

W `main()` tworzony jest obiekt:

```cpp
Samochod samochod("Toyota", "benzynowy");
```

Podczas tego kroku:

1. tworzony jest obiekt `samochod`,
2. pole `marka` przyjmuje wartość `"Toyota"`,
3. pole `silnik` zostaje utworzone jako obiekt `Silnik("benzynowy")`.

Następnie wykonywane jest:

```cpp
samochod.uruchom();
```

co prowadzi do:

1. wypisania informacji o samochodzie,
2. wywołania `silnik.uruchom()`,
3. wypisania informacji o silniku.

## Wynik działania programu

Program wypisze:

```text
Samochod Toyota uruchamia silnik.
Silnik benzynowy uruchomiony.
```

## Czas życia obiektów w kompozycji

Kompozycja ma też bardzo ważną konsekwencję dotyczącą czasu życia obiektów.

Jeśli `Samochod` zawiera `Silnik` jako pole składowe, to:

* silnik powstaje razem z samochodem,
* silnik jest niszczony razem z samochodem,
* nie istnieje niezależnie wewnątrz tego obiektu jako osobny byt zarządzany z zewnątrz.

To jedna z cech odróżniających kompozycję od innych relacji między obiektami.

## Kompozycja a agregacja

Ten przykład opisuje **kompozycję**, a nie agregację.

W kompozycji:

* obiekt zawiera swoje części bezpośrednio,
* część należy do całości,
* czas życia części jest związany z czasem życia całości.

Tutaj `Silnik` jest bezpośrednim polem klasy `Samochod`, więc jest to klasyczny przykład kompozycji.

Gdyby `Samochod` przechowywał tylko wskaźnik lub referencję do silnika utworzonego gdzieś indziej, byłaby to raczej inna relacja, często opisywana jako agregacja lub zależność.

## Dlaczego kompozycja jest ważna

Kompozycja jest jednym z najważniejszych mechanizmów projektowania klas, ponieważ pozwala tworzyć złożone obiekty z prostszych elementów.

W praktyce bardzo wiele obiektów modeluje się właśnie tak:

* samochód ma silnik,
* komputer ma procesor i pamięć,
* książka ma autora i rozdziały,
* zamówienie ma pozycje zamówienia.

To bardzo naturalny sposób odwzorowania świata rzeczywistego w kodzie.

## Podsumowanie

Program `cw6-3.cpp` pokazuje:

* definicję dwóch współpracujących klas,
* kompozycję obiektów,
* relację „samochód ma silnik”,
* inicjalizację obiektu składowego przez listę inicjalizacyjną,
* wywołanie metody obiektu będącego częścią innego obiektu,
* zależność czasu życia części od czasu życia całości.

Jest to bardzo dobry przykład pokazujący, czym w praktyce jest kompozycja w C++ i dlaczego stanowi jedną z podstaw programowania obiektowego.
