# `cw7-2` – kolejność wywoływania konstruktorów i destruktorów

Ten program pokazuje, **w jakiej kolejności w C++ tworzone i niszczone są obiekty o różnym czasie życia**. Jest to przykład bardzo ważny dydaktycznie, ponieważ zestawia w jednym miejscu:

* obiekt globalny,
* obiekty lokalne automatyczne,
* obiekty lokalne statyczne,
* obiekt dynamiczny tworzony przez `new`.

Dzięki komunikatom wypisywanym przez konstruktor i destruktor można dokładnie prześledzić moment powstania i zniszczenia każdego obiektu.

## Pliki programu

Program składa się z trzech plików:

* `main.cpp` – zawiera funkcję `main()` oraz funkcję `create()`,
* `CreateAndDestroy.h` – deklaracja klasy `CreateAndDestroy`,
* `CreateAndDestroy.cpp` – definicje konstruktora i destruktora.

## `main.cpp`

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

## `CreateAndDestroy.cpp`

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

## Rola klasy `CreateAndDestroy`

Klasa `CreateAndDestroy` została przygotowana specjalnie po to, aby pokazać czas życia obiektów.

Każdy obiekt tej klasy przechowuje:

* `objectID` – numer identyfikacyjny obiektu,
* `message` – opis, gdzie i jak obiekt został utworzony.

### Konstruktor

Konstruktor:

```cpp
CreateAndDestroy::CreateAndDestroy( int ID, string messageString )
   : objectID( ID ), message( messageString )
{
   cout << "Object " << objectID << "   constructor runs   " 
      << message << endl;
}
```

ustawia pola obiektu i od razu wypisuje komunikat o jego utworzeniu.

### Destruktor

Destruktor:

```cpp
CreateAndDestroy::~CreateAndDestroy()
{ 
   cout << ( objectID == 1 || objectID == 6 ? "\n" : "" );

   cout << "Object " << objectID << "   destructor runs    " 
      << message << endl; 
}
```

wypisuje komunikat o zniszczeniu obiektu.

Dodatkowy warunek:

```cpp
cout << ( objectID == 1 || objectID == 6 ? "\n" : "" );
```

nie wpływa na logikę czasu życia obiektów – służy tylko poprawie czytelności wypisywanego wyniku.

## Jakie obiekty występują w programie

### 1. Obiekt globalny

```cpp
CreateAndDestroy first( 1, "(global before main)" );
```

To obiekt globalny, zdefiniowany poza wszystkimi funkcjami.

#### Wniosek

* jest tworzony **przed wejściem do `main()`**,
* jest niszczony **po zakończeniu `main()`**, przy zamykaniu programu.

## 2. Lokalny obiekt automatyczny w `main()`

```cpp
CreateAndDestroy second( 2, "(local automatic in main)" );
```

To zwykły lokalny obiekt automatyczny.

#### Wniosek

* powstaje w chwili wykonania tej instrukcji,
* istnieje do końca funkcji `main()`,
* jest niszczony automatycznie przy opuszczeniu `main()`.

## 3. Lokalny obiekt statyczny w `main()`

```cpp
static CreateAndDestroy third( 3, "(local static in main)" );
```

To obiekt lokalny, ale statyczny.

#### Wniosek

* jest tworzony tylko raz,
* istnieje do końca działania programu,
* jego destruktor wykona się dopiero na końcu programu.

## 4. Lokalna funkcja `create()`

Funkcja `create()` tworzy kolejne trzy obiekty:

```cpp
CreateAndDestroy fifth( 5, "(local automatic in create)" );
static CreateAndDestroy sixth( 6, "(local static in create)" );
CreateAndDestroy seventh( 7, "(local automatic in create)" );
```

### `fifth`

To lokalny obiekt automatyczny funkcji `create()`.

* powstaje przy wejściu do funkcji,
* ginie przy wyjściu z funkcji.

### `sixth`

To lokalny obiekt statyczny funkcji `create()`.

* jest tworzony tylko przy pierwszym wejściu do funkcji,
* nie znika po zakończeniu funkcji,
* zostanie zniszczony dopiero przy końcu programu.

### `seventh`

To również lokalny obiekt automatyczny funkcji `create()`.

* powstaje po `fifth` i `sixth`,
* zostanie zniszczony jako pierwszy przy wyjściu z funkcji, bo obiekty automatyczne niszczone są w odwrotnej kolejności do tworzenia.

## 5. Kolejny lokalny obiekt automatyczny w `main()`

Po powrocie z `create()` program tworzy:

```cpp
CreateAndDestroy fourth( 4, "(local automatic in main)" );
```

To zwykły lokalny obiekt automatyczny, który będzie żył do końca `main()`.

## 6. Obiekt dynamiczny

```cpp
CreateAndDestroy* c  = new CreateAndDestroy(8, "pointer");
```

To obiekt tworzony dynamicznie na stercie.

#### Wniosek

* jego konstruktor uruchamia się w chwili `new`,
* obiekt nie zostanie zniszczony sam przy końcu zakresu,
* trzeba go usunąć ręcznie przez `delete`.

W programie wykonano:

```cpp
delete c;
```

więc destruktor obiektu nr 8 uruchomi się od razu w tym miejscu.

## Kolejność tworzenia obiektów

Program tworzy obiekty w następującej kolejności:

1. `first` – obiekt globalny, jeszcze przed `main()`,
2. `second` – lokalny automatyczny w `main()`,
3. `third` – lokalny statyczny w `main()`,
4. `fifth` – lokalny automatyczny w `create()`,
5. `sixth` – lokalny statyczny w `create()`,
6. `seventh` – lokalny automatyczny w `create()`,
7. `fourth` – lokalny automatyczny w `main()`,
8. obiekt dynamiczny `8` – utworzony przez `new`.

## Kolejność niszczenia obiektów

### Po wyjściu z `create()`

Najpierw niszczone są lokalne obiekty automatyczne funkcji `create()`:

1. `seventh`,
2. `fifth`.

Obiekt `sixth` nie znika, bo jest statyczny.

### Po `delete c;`

3. niszczony jest obiekt dynamiczny nr `8`.

### Przy wyjściu z `main()`

Następnie niszczone są lokalne obiekty automatyczne funkcji `main()`:

4. `fourth`,
5. `second`.

Obiekt `third` nadal jeszcze istnieje, bo jest statyczny.

### Przy zamykaniu programu

Na końcu programu niszczone są obiekty o statycznym czasie życia:

6. `sixth`,
7. `third`,
8. `first`.

## Najważniejsze pojęcia pokazane w programie

### Obiekt automatyczny

To zwykły obiekt lokalny bez `static`.

* żyje do końca swojego zakresu,
* niszczy się automatycznie.

### Obiekt statyczny lokalny

To obiekt lokalny oznaczony `static`.

* ma lokalny zakres widoczności,
* ale jego czas życia trwa do końca programu.

### Obiekt globalny

To obiekt zadeklarowany poza funkcjami.

* jest tworzony przed `main()`,
* jest niszczony po zakończeniu programu.

### Obiekt dynamiczny

To obiekt tworzony przez `new`.

* żyje niezależnie od zakresu wskaźnika,
* musi zostać usunięty przez `delete`.

## Co dokładnie uczy ten przykład

Ten program pokazuje, że w C++ czas życia obiektu zależy od miejsca i sposobu jego utworzenia.

Najważniejsze wnioski:

* obiekty lokalne automatyczne giną przy końcu zakresu,
* obiekty statyczne żyją do końca programu,
* obiekty globalne istnieją od startu programu do jego zakończenia,
* obiekty dynamiczne trzeba usuwać ręcznie,
* destruktory dla obiektów automatycznych wywołują się w odwrotnej kolejności do tworzenia.

## Podsumowanie

Program `cw7-2` jest klasycznym przykładem pokazującym kolejność wywołań konstruktorów i destruktorów.

Dzięki niemu można bardzo dobrze zrozumieć:

* czym różni się obiekt globalny od lokalnego,
* co zmienia słowo kluczowe `static`,
* jak działa `new` i `delete`,
* kiedy C++ automatycznie wywołuje destruktory,
* dlaczego czas życia obiektu jest jedną z kluczowych cech programu w C++.

Jest to jeden z podstawowych przykładów pomagających zrozumieć zarządzanie ob

