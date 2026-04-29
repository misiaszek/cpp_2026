`cw9-2.cpp` – funkcje wirtualne i niewirtualne w dziedziczeniu
Program pokazuje bardzo ważną różnicę między:
metodą wirtualną,
metodą niewirtualną,
gdy obiekt klasy pochodnej jest używany przez:
wskaźnik do klasy bazowej,
referencję do klasy bazowej.
To klasyczny przykład polimorfizmu dynamicznego w C++.
Kod programu
```cpp
#include <iostream>
using namespace std;

class Animal {
  public:
    virtual void sound() {
      cout << "Animal sound\n";
    }
    void print() {
      cout << "Animal\n";
    }
};

class Dog : public Animal {
  public:
    void sound() override {
      cout << "Dog barks\n";
    }
    void print() {
      cout << "Dog\n";
    }
};

int main() {
  Animal* a;  // Declare a pointer to the base class (Animal)
  Dog d;  // Create an object of the derived class (Dog)
  a = &d;  // Point the base class pointer to the Dog object
  a->sound();
  a->print();

  Animal &ar = d;
  ar.sound();
  ar.print();

  return 0;
}
```
Co pokazuje ten przykład
W programie są dwie klasy:
`Animal` – klasa bazowa,
`Dog` – klasa pochodna.
Klasa `Dog` dziedziczy publicznie po `Animal`:
```cpp
class Dog : public Animal
```
Obie klasy mają dwie metody:
`sound()`
`print()`
Ale tylko jedna z nich w klasie bazowej została oznaczona jako `virtual`.
To właśnie decyduje o tym, czy przy wywołaniu przez wskaźnik lub referencję do klasy bazowej zadziała wersja z klasy bazowej, czy z klasy pochodnej.
---
Klasa `Animal`
Klasa bazowa zawiera:
```cpp
virtual void sound() {
  cout << "Animal sound\n";
}
```
oraz:
```cpp
void print() {
  cout << "Animal\n";
}
```
Ważna różnica
`sound()` jest wirtualna,
`print()` jest niewirtualna.
To oznacza:
`sound()` może być wybierana dynamicznie na podstawie rzeczywistego typu obiektu,
`print()` będzie wybierana statycznie na podstawie typu wskaźnika lub referencji.
---
Klasa `Dog`
Klasa pochodna redefiniuje obie metody:
```cpp
void sound() override {
  cout << "Dog barks\n";
}
```
oraz:
```cpp
void print() {
  cout << "Dog\n";
}
```
`override`
Słowo kluczowe:
```cpp
override
```
przy metodzie `sound()` oznacza, że programista świadomie nadpisuje metodę wirtualną klasy bazowej.
To jest bardzo dobra praktyka, bo kompilator sprawdza wtedy, czy naprawdę istnieje zgodna metoda w klasie bazowej. Gdyby podpis funkcji się nie zgadzał, kompilator zgłosiłby błąd.
---
Wskaźnik do klasy bazowej
W `main()` mamy:
```cpp
Animal* a;
Dog d;
a = &d;
```
To oznacza, że wskaźnik typu `Animal*` wskazuje na obiekt klasy `Dog`.
To jest poprawne dzięki dziedziczeniu publicznemu i nazywa się rzutowaniem w górę (upcasting).
---
Wywołanie `a->sound()`
Program wykonuje:
```cpp
a->sound();
```
Ponieważ `sound()` w klasie bazowej jest metodą wirtualną, C++ sprawdza rzeczywisty typ obiektu, na który wskazuje wskaźnik.
Wskaźnik `a` ma typ `Animal*`, ale wskazuje na obiekt `Dog`, więc wywołana zostanie metoda:
```cpp
Dog::sound()
```
czyli program wypisze:
```text
Dog barks
```
To właśnie jest polimorfizm dynamiczny.
---
Wywołanie `a->print()`
Program wykonuje:
```cpp
a->print();
```
Tym razem metoda `print()` nie jest wirtualna, więc decyzja o tym, którą wersję wywołać, zapada na podstawie typu wskaźnika, a nie typu obiektu.
Ponieważ `a` ma typ:
```cpp
Animal*
```
wywołana zostanie:
```cpp
Animal::print()
```
czyli program wypisze:
```text
Animal
```
Mimo że wskaźnik wskazuje na obiekt `Dog`, brak `virtual` powoduje, że nie ma dynamicznego wyboru funkcji.
---
Referencja do klasy bazowej
Dalej program tworzy referencję:
```cpp
Animal &ar = d;
```
To oznacza, że `ar` jest referencją typu `Animal`, ale odnosi się do obiektu klasy `Dog`.
Tak jak wcześniej, mamy więc sytuację, w której obiekt pochodny jest traktowany jak bazowy.
---
Wywołanie `ar.sound()`
Program wykonuje:
```cpp
ar.sound();
```
Ponieważ `sound()` jest metodą wirtualną, C++ znów wybiera metodę na podstawie rzeczywistego typu obiektu.
A rzeczywisty typ obiektu to `Dog`, więc wypisane zostanie:
```text
Dog barks
```
---
Wywołanie `ar.print()`
Program wykonuje:
```cpp
ar.print();
```
Ponieważ `print()` nie jest wirtualna, wybór wersji funkcji zależy od typu referencji, a nie od rzeczywistego typu obiektu.
Typ referencji to:
```cpp
Animal&
```
więc wywołana zostanie:
```cpp
Animal::print()
```
czyli wypisane zostanie:
```text
Animal
```
---
Wynik działania programu
Program wypisze:
```text
Dog barks
Animal
Dog barks
Animal
```
Interpretacja
`a->sound();` → `Dog barks`
`a->print();` → `Animal`
`ar.sound();` → `Dog barks`
`ar.print();` → `Animal`
---
Najważniejsza lekcja
Ten przykład pokazuje bardzo jasno:
jeśli metoda jest `virtual`, to przy wywołaniu przez wskaźnik lub referencję do klasy bazowej użyta zostanie wersja odpowiadająca rzeczywistemu typowi obiektu,
jeśli metoda nie jest `virtual`, to zostanie użyta wersja wynikająca z typu wskaźnika lub referencji.
Czyli:
`sound()` działa polimorficznie,
`print()` nie działa polimorficznie.
---
Uwaga do komentarza w kodzie
W komentarzu przy:
```cpp
a->sound();
```
jest napisane:
```cpp
// Since sound() is not virtual, this calls Animal's version
```
Ten komentarz jest niepoprawny merytorycznie.
W rzeczywistości `sound()` jest wirtualna, więc wywołanie:
```cpp
a->sound();
```
uruchamia wersję klasy `Dog`, a nie `Animal`.
Poprawny komentarz powinien raczej brzmieć:
```cpp
// Since sound() is virtual, this calls Dog's version
```
To ważna poprawka, bo właśnie na tym polega sens całego przykładu.
---
Przesłanianie a polimorfizm
W projekcie występują dwa zjawiska jednocześnie:
1. Przesłanianie metod
Klasa `Dog` definiuje własne wersje `sound()` i `print()`.
2. Polimorfizm dynamiczny
Działa tylko dla metody `sound()`, bo tylko ona jest `virtual`.
To znaczy, że nie każda przesłonięta metoda automatycznie daje polimorfizm – potrzebne jest jeszcze słowo kluczowe `virtual` w klasie bazowej.
---
Czego uczy ten przykład
Program bardzo dobrze pokazuje:
dziedziczenie publiczne,
rzutowanie w górę,
działanie wskaźników i referencji do klasy bazowej,
znaczenie słowa kluczowego `virtual`,
sens użycia `override`,
różnicę między metodą wirtualną a niewirtualną.
---
Podsumowanie
Program `cw9-2.cpp` pokazuje podstawy polimorfizmu dynamicznego w C++.
Najważniejsze wnioski są takie:
metoda `virtual` wywoływana przez wskaźnik lub referencję do klasy bazowej używa wersji klasy pochodnej, jeśli obiekt jest typu pochodnego,
metoda niewirtualna wywoływana przez wskaźnik lub referencję do klasy bazowej używa wersji klasy bazowej,
`override` pomaga bezpiecznie nadpisywać metody wirtualne,
sam fakt dziedziczenia nie wystarcza – kluczowe znaczenie ma obecność `virtual`.
To bardzo dobry przykład pokazujący, jak w praktyce działa polimorfizm w C++.
