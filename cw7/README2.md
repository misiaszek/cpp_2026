# `cw7-2` – kolejność wywoływania konstruktorów i destruktorów

Ten przykład pokazuje bardzo ważne zagadnienie w C++: **w jakiej kolejności tworzone i niszczone są obiekty o różnym czasie życia**.

Program prezentuje jednocześnie kilka rodzajów obiektów:

* obiekt globalny,
* obiekty lokalne automatyczne,
* obiekty lokalne statyczne,
* obiekt utworzony dynamicznie przez `new`.

Dzięki temu można prześledzić, **kiedy uruchamiają się konstruktory i destruktory** oraz od czego zależy moment zniszczenia obiektu.

## Uwaga dotycząca pliku `CreateAndDestroy.h`

W przesłanym fragmencie pod nazwą `CreateAndDestroy.h` znajduje się najprawdopodobniej omyłkowo ponownie kod z `main.cpp`, a nie właściwa definicja klasy.

Na podstawie pliku `CreateAndDestroy.cpp` można jednak bez problemu odtworzyć, jaka jest idea programu. Typowa zawartość nagłówka dla tego przykładu powinna wyglądać mniej więcej tak:

```cpp
#ifndef CREATEANDDESTROY_H
#define CREATEANDDESTROY_H

#include <string>

class CreateAndDestroy
{
public:
    CreateAndDestroy(int ID, std::string messageString);
    ~CreateAndDestroy();

private:
    int objectID;
    std::string message;
};

#endif
```

To właśnie taka klasa jest później używana w `main.cpp` i definiowana w `CreateAndDestroy.cpp`.

## Plik `main.cpp`

```cpp
// Demonstrating the order in which constructors and
// destructors are called.
#include <iostream>
#include "CreateAndDestroy.h" // include CreateAndDestroy class definition
using namespace std;

void create( void ); // prototype

CreateAndDestroy first( 1, "(global before main)" ); // global object

int main()
{
   cout << "\nMAIN FUNCTION: EXECUTION BEGINS" << endl;
   CreateAndDestroy second( 2, "(local automatic in main)" );
   static CreateAndDestroy third( 3, "(local static in main)" );
   
   create(); // call function to create objects

   cout << "\nMAIN FUNCTION: EXECUTION RESUMES" << endl;
   CreateAndDestroy fourth( 4, "(local automatic in main)" );
   
   CreateAndDestroy* c  = new CreateAndDestroy(8, "pointer");
   cout << "\nMAIN FUNCTION: EXECUTION ENDS" << endl;
   delete c;
   
} // end main

// function to create objects
void create( void )
{
   cout << "\nCREATE FUNCTION: EXECUTION BEGINS" << endl;
   CreateAndDestroy fifth( 5, "(local automatic in create)" );
   static CreateAndDestroy sixth( 6, "(local static in create)" );
   CreateAndDestroy seventh( 7, "(local automatic in create)" );
   cout << "\nCREATE FUNCTION: EXECUTION ENDS" << endl;
} // end function create
```

## Plik `CreateAndDestroy.cpp`

```cpp
// CreateAndDestroy class member-function definitions.
#include <iostream>
#include "CreateAndDestroy.h" // include CreateAndDestroy class definition
using namespace std;

// constructor sets object's ID number and descriptive message
CreateAndDestroy::CreateAndDestroy( int ID, string messageString )
   : objectID( ID ), message( messageString )
{
   cout << "Object " << objectID << "   constructor runs   "
      << message << endl;
} // end CreateAndDestroy constructor

// destructor
CreateAndDestroy::~CreateAndDestroy()
{
   // output newline for certain objects; helps readability
   cout << ( objectID == 1 || objectID == 6 ? "\n" : "" );

   cout << "Object " << objectID << "   destructor runs    "
      << message << endl;
} // end ~CreateAndDestroy destructor
```

## Cel programu

Program ma pokazać, że w C++ moment tworzenia i niszczenia obiektu zależy od tego, **jakiego rodzaju jest to obiekt**.

Najważniejsze kategorie tutaj to:

* **globalny**,
* **lokalny automatyczny**,
* **lokalny statyczny**,
* **dynamiczny**.

## Klasa `CreateAndDestroy`

Każdy obiekt tej klasy przechowuje:

* numer `objectID`,
* opis tekstowy `message`.

Konstruktor wypisuje informację o utworzeniu obiektu, a destruktor informację o jego zniszczeniu.

Dzięki temu można łatwo obserwować kolejność zdarzeń.

## Rodzaje obiektów w tym programie

### 1. Obiekt globalny

```cpp
CreateAndDestroy first( 1, "(global before main)" );
```

To obiekt globalny, zdefiniowany **poza funkcją `main()`**.

#### Co to oznacza

* zostaje utworzony **przed wejściem do `main()`**,
* jego destruktor wykona się **po zakończeniu `main()`**, na samym końcu działania programu.

To pierwszy obiekt, który powstaje, i jeden z ostatnich, który znika.

## 2. Obiekt lokalny automatyczny w `main()`

```cpp
CreateAndDestroy second( 2, "(local automatic in main)" );
```

Jest to zwykły obiekt lokalny.

#### Co to oznacza

* powstaje, gdy program dochodzi do tej instrukcji,
* istnieje do końca zakresu funkcji `main()`,
* zostanie zniszczony automatycznie przy wychodzeniu z `main()`.

Takie obiekty nazywa się często **automatic objects**, bo ich czas życia jest automatycznie zarządzany przez język.

## 3. Obiekt lokalny statyczny w `main()`

```cpp
static CreateAndDestroy third( 3, "(local static in main)" );
```

To obiekt lokalny, ale oznaczony słowem kluczowym `static`.

#### Co to oznacza

* zostaje utworzony tylko raz, przy pierwszym wykonaniu tej instrukcji,
* zachowuje swój stan do końca programu,
* jego destruktor wykona się dopiero przy zamykaniu programu.

Czyli zakres widoczności jest lokalny dla `main()`, ale czas życia jest prawie taki jak dla obiektu globalnego.

## 4. Obiekty automatyczne w funkcji `create()`

```cpp
CreateAndDestroy fifth( 5, "(local automatic in create)" );
CreateAndDestroy seventh( 7, "(local automatic in create)" );
```

To zwykłe lokalne obiekty funkcji `create()`.

#### Co to oznacza

* są tworzone przy wejściu do funkcji,
* są niszczone przy wyjściu z funkcji,
* destruktory wykonują się w odwrotnej kolejności do tworzenia.

Czyli najpierw zniszczony zostanie `seventh`, potem `fifth`.

## 5. Obiekt statyczny w funkcji `create()`

```cpp
static CreateAndDestroy sixth( 6, "(local static in create)" );
```

To lokalny obiekt statyczny funkcji `create()`.

#### Co to oznacza

* tworzony jest tylko raz, przy pierwszym wejściu do funkcji,
* nie znika po zakończeniu funkcji,
* będzie istniał aż do końca programu,
* jego destruktor uruchomi się dopiero przy zamykaniu programu.

To ważna różnica względem zwykłych obiektów lokalnych.

## 6. Kolejny obiekt automatyczny w `main()`

```cpp
CreateAndDestroy fourth( 4, "(local automatic in main)" );
```

To kolejny zwykły obiekt lokalny funkcji `main()`.

Żyje do końca `main()`, a potem zostaje automatycznie zniszczony.

## 7. Obiekt dynamiczny

```cpp
CreateAndDestroy* c  = new CreateAndDestroy(8, "pointer");
```

Ten obiekt powstaje dynamicznie na stercie.

#### Co to oznacza

* jego konstruktor uruchamia się w momencie `new`,
* obiekt **nie zostanie zniszczony automatycznie przy końcu zakresu**, bo wskaźnik `c` to tylko adres,
* trzeba go zniszczyć ręcznie przez `delete`.

W programie robione jest to poprawnie:

```cpp
delete c;
```

Wtedy uruchamia się destruktor obiektu nr 8.

Gdyby `delete c;` nie było, powstałby wyciek pamięci.

## Kolejność tworzenia obiektów

Przebieg programu wygląda następująco.

### Przed `main()`

Najpierw tworzony jest obiekt globalny:

1. `first`

### W `main()`

Następnie:

2. `second`
3. `third` (statyczny lokalny)

### Po wejściu do `create()`

4. `fifth`
5. `sixth` (statyczny lokalny, tworzony przy pierwszym wejściu)
6. `seventh`

### Po powrocie do `main()`

7. `fourth`
8. dynamiczny obiekt wskazywany przez `c`

## Kolejność niszczenia obiektów

### Przy wyjściu z `create()`

Zniszczone zostaną lokalne automatyczne obiekty tej funkcji w odwrotnej kolejności:

1. `seventh`
2. `fifth`

Obiekt `sixth` nie zostanie wtedy zniszczony, bo jest `static`.

### Po `delete c;`

3. dynamiczny obiekt nr `8`

### Przy wyjściu z `main()`

Zniszczone zostaną lokalne automatyczne obiekty `main()` w odwrotnej kolejności ich tworzenia:

4. `fourth`
5. `second`

Obiekt `third` nadal jeszcze istnieje, bo jest statyczny lokalny.

### Przy zamykaniu programu

Na końcu niszczone są obiekty statyczne i globalne. W praktyce dla tego przykładu zobaczymy jeszcze destruktory:

6. `sixth`
7. `third`
8. `first`

## Najważniejsza zasada

W tym przykładzie bardzo wyraźnie widać, że:

* **obiekty automatyczne** żyją do końca swojego zakresu,
* **obiekty statyczne** żyją do końca programu,
* **obiekty globalne** istnieją od startu programu do jego końca,
* **obiekty dynamiczne** żyją tak długo, aż zostaną usunięte przez `delete`.

## Dlaczego destruktory wywołują się w odwrotnej kolejności

To celowe zachowanie języka. Jeśli obiekty są tworzone jeden po drugim, to niszczenie ich w odwrotnej kolejności pomaga bezpiecznie zamykać zależności między nimi.

Ta zasada obowiązuje szczególnie dla obiektów lokalnych automatycznych w danym zakresie.

## Znaczenie edukacyjne przykładu

To jeden z klasycznych programów pokazujących:

* różne czasy życia obiektów,
* różnicę między storage duration a scope,
* znaczenie `static`,
* znaczenie `new` i `delete`,
* automatyczne wywoływanie konstruktorów i destruktorów.

## Podsumowanie

Program `cw7-2` pokazuje bardzo dokładnie, kiedy uruchamiane są konstruktory i destruktory dla:

* obiektu globalnego,
* obiektów lokalnych automatycznych,
* obiektów lokalnych statycznych,
* obiektu dynamicznego utworzonego przez `new`.

Najważniejsze wnioski są takie:

* obiekt globalny powstaje przed `main()` i znika po zakończeniu programu,
* obiekt lokalny automatyczny znika przy końcu swojego zakresu,
* obiekt lokalny statyczny istnieje do końca programu,
* obiekt dynamiczny trzeba usunąć ręcznie przez `delete`,
* destruktory obiektów lokalnych automatycznych wywołują się w odwrotnej kolejności do ich tworzenia.

Jest to bardzo dobry przykład do zrozumienia zarządzania czasem życia obiektów w C++.
