`cw9-1.cpp` – przesłanianie metod i rzutowanie w górę
Program pokazuje dwa bardzo ważne zjawiska w programowaniu obiektowym w C++:
dziedziczenie publiczne,
przesłanianie metody klasy bazowej w klasie pochodnej.
Dodatkowo przykład pokazuje, co dzieje się, gdy obiekt klasy pochodnej jest używany przez wskaźnik do klasy bazowej.
Kod programu
```cpp
#include <iostream>

class Bazowa
{
public:
    void metoda()
    {
        std::cout << "Bazowa::metoda" << std::endl;
    }
};

class Pochodna
    : public Bazowa
{
public:
    void metoda() //Przesłaniamy metode z klasy bazowej
    {
        std::cout << "Pochodna::metoda" << std::endl;
    }
};

int main()
{
    Bazowa b;
    Pochodna p;

    b.metoda();
    p.metoda();

    Bazowa * bptr = & p; //rzutowanie w górę
    bptr->metoda();
}
```
Co pokazuje ten przykład
Program definiuje dwie klasy:
`Bazowa`
`Pochodna`
Klasa `Pochodna` dziedziczy po klasie `Bazowa`:
```cpp
class Pochodna : public Bazowa
```
Obie klasy mają metodę o tej samej nazwie:
```cpp
void metoda()
```
W klasie pochodnej metoda ta przesłania metodę odziedziczoną z klasy bazowej.
Na końcu program pokazuje, jak zachowuje się wskaźnik typu `Bazowa*`, który wskazuje na obiekt klasy `Pochodna`.
---
Klasa bazowa
Klasa `Bazowa` zawiera jedną publiczną metodę:
```cpp
void metoda()
{
    std::cout << "Bazowa::metoda" << std::endl;
}
```
Jej zadanie jest bardzo proste: wypisuje tekst informujący, że została wywołana metoda klasy bazowej.
---
Klasa pochodna
Klasa `Pochodna` dziedziczy publicznie po `Bazowa` i definiuje własną metodę o tej samej nazwie:
```cpp
void metoda()
{
    std::cout << "Pochodna::metoda" << std::endl;
}
```
Ta metoda przesłania metodę z klasy bazowej.
Co to znaczy „przesłania”?
Jeżeli klasa pochodna definiuje metodę o tej samej nazwie i tej samej liście parametrów co metoda klasy bazowej, to w kontekście obiektu klasy pochodnej nowa metoda zasłania odziedziczoną wersję.
W tym programie:
dla obiektu `Bazowa` wywołana będzie `Bazowa::metoda`,
dla obiektu `Pochodna` wywołana będzie `Pochodna::metoda`.
---
Wywołania metod w `main()`
W funkcji `main()` tworzone są dwa obiekty:
```cpp
Bazowa b;
Pochodna p;
```
Następnie wykonywane są wywołania:
```cpp
b.metoda();
p.metoda();
```
Co się stanie?
1. `b.metoda();`
Obiekt `b` ma typ `Bazowa`, więc zostanie wywołana metoda klasy bazowej:
```text
Bazowa::metoda
```
2. `p.metoda();`
Obiekt `p` ma typ `Pochodna`, więc zostanie wywołana metoda klasy pochodnej:
```text
Pochodna::metoda
```
---
Rzutowanie w górę
Najciekawsza część programu to:
```cpp
Bazowa * bptr = & p;
```
To jest tzw. rzutowanie w górę (upcasting).
Co to oznacza?
Obiekt klasy pochodnej może być traktowany jako obiekt klasy bazowej, ponieważ:
`Pochodna` jest rodzajem `Bazowa`,
zawiera część bazową,
można więc przypisać adres obiektu `Pochodna` do wskaźnika typu `Bazowa*`.
To jest poprawne i naturalne w dziedziczeniu publicznym.
---
Co się stanie przy `bptr->metoda();`
Program wykonuje:
```cpp
bptr->metoda();
```
Na pierwszy rzut oka mogłoby się wydawać, że ponieważ `bptr` wskazuje na obiekt `Pochodna`, to wywołana zostanie:
```cpp
Pochodna::metoda
```
Ale tak nie będzie.
Dlaczego?
Ponieważ metoda `metoda()` w klasie bazowej nie jest zadeklarowana jako `virtual`.
W C++ jeśli metoda nie jest wirtualna, to wybór wersji metody odbywa się na podstawie typu wskaźnika, a nie rzeczywistego typu obiektu.
Tutaj wskaźnik ma typ:
```cpp
Bazowa*
```
więc wywołana zostanie:
```cpp
Bazowa::metoda
```
mimo że wskaźnik wskazuje na obiekt klasy `Pochodna`.
---
Wynik działania programu
Program wypisze:
```text
Bazowa::metoda
Pochodna::metoda
Bazowa::metoda
```
Interpretacja
pierwsza linia: wywołanie metody dla obiektu `Bazowa`,
druga linia: wywołanie przesłoniętej metody dla obiektu `Pochodna`,
trzecia linia: wywołanie przez wskaźnik `Bazowa*`, więc bez `virtual` używana jest wersja z klasy bazowej.
---
Przesłanianie a polimorfizm
Ten przykład pokazuje ważną różnicę między:
przesłanianiem metody,
a polimorfizmem dynamicznym.
W tym programie jest przesłanianie
Klasa pochodna definiuje metodę o tej samej nazwie co klasa bazowa.
Ale nie ma jeszcze prawdziwego polimorfizmu dynamicznego
Żeby wywołanie przez wskaźnik bazowy używało wersji klasy pochodnej, metoda w klasie bazowej musiałaby być zadeklarowana jako `virtual`, na przykład:
```cpp
virtual void metoda()
{
    std::cout << "Bazowa::metoda" << std::endl;
}
```
Wtedy:
```cpp
bptr->metoda();
```
wywołałoby:
```text
Pochodna::metoda
```
bo C++ zdecydowałby o wyborze metody na podstawie rzeczywistego typu obiektu, a nie typu wskaźnika.
---
Czego uczy ten przykład
Program dobrze pokazuje kilka ważnych zasad:
1. Dziedziczenie publiczne
Klasa pochodna może przejąć interfejs klasy bazowej i dodać własne zachowanie.
2. Przesłanianie metody
Klasa pochodna może zdefiniować własną metodę o tej samej nazwie co metoda klasy bazowej.
3. Rzutowanie w górę
Adres obiektu klasy pochodnej można przypisać do wskaźnika klasy bazowej.
4. Znaczenie `virtual`
Jeżeli metoda nie jest wirtualna, to przy wywołaniu przez wskaźnik bazowy używana jest wersja wynikająca z typu wskaźnika.
---
Co warto zapamiętać
Najważniejsza obserwacja z tego programu jest taka:
> Samo dziedziczenie i przesłonięcie metody nie wystarczą, by działał polimorfizm dynamiczny.
Do tego potrzebne jest jeszcze słowo kluczowe:
```cpp
virtual
```
Bez niego wywołania przez wskaźnik lub referencję do klasy bazowej są rozstrzygane statycznie.
---
Podsumowanie
Program `cw9-1.cpp` pokazuje:
klasę bazową i pochodną,
przesłanianie metody w klasie pochodnej,
tworzenie obiektów obu klas,
rzutowanie w górę z `Pochodna*` do `Bazowa*`,
wywołanie metody przez wskaźnik do klasy bazowej,
brak polimorfizmu dynamicznego z powodu braku `virtual`.
To bardzo dobry przykład wprowadzający do tematu metod wirtualnych i polimorfizmu w C++.
