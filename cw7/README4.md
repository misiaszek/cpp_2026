# `cw7-4.cpp` – wskaźnik `this` w klasie C++

Program pokazuje działanie **wskaźnika `this`**, czyli specjalnego wskaźnika dostępnego wewnątrz niestatycznych metod klasy. Jest to jeden z podstawowych mechanizmów programowania obiektowego w C++, ponieważ pozwala metodzie odwoływać się do konkretnego obiektu, dla którego została wywołana.

W tym przykładzie program demonstruje trzy równoważne sposoby dostępu do składowej `x` obiektu:

* przez zwykłe odwołanie do pola,
* przez jawne użycie `this->x`,
* przez dereferencję wskaźnika `this`, czyli `(*this).x`.

---

## Kod programu

```cpp
// Using the this pointer to refer to object members.
#include <iostream>
using namespace std;

class Test
{
public:
   explicit Test( int = 0 ); // default constructor
   void print( int = 0) const;
private:
   int x;
}; // end class Test

// constructor
Test::Test( int value )
   : x( value ) // initialize x to value
{
   // empty body
} // end constructor Test

// print x using implicit and explicit this pointers;
// the parentheses around *this are required
void Test::print(int y) const   
{
   // implicitly use the this pointer to access the member x
   cout << "        x = " << x;

   // explicitly use the this pointer and the arrow operator
   // to access the member x
   cout << "\n  this->x = " << this->x;

   // explicitly use the dereferenced this pointer and
   // the dot operator to access the member x
   cout << "\n(*this).x = " << ( *this ).x << endl;
} // end function print

int main()
{
   Test testObject( 12 ); // instantiate and initialize testObject

   testObject.print(3);
} // end main
```

---

## Cel programu

Głównym celem programu jest pokazanie, że każda niestatyczna metoda klasy działa zawsze dla jakiegoś konkretnego obiektu, a dostęp do tego obiektu odbywa się właśnie przez ukryty wskaźnik `this`.

W praktyce oznacza to, że gdy wywołujemy:

```cpp
testObject.print(3);
```

to wewnątrz metody `print()` kompilator przekazuje informację, **dla którego obiektu metoda została wywołana**. Tą informacją jest właśnie wskaźnik `this`.

---

## Klasa `Test`

Klasa zawiera jedno prywatne pole:

```cpp
int x;
```

oraz dwie publiczne funkcje:

```cpp
explicit Test( int = 0 );
void print( int = 0 ) const;
```

### Pole `x`

To zwykła prywatna zmienna członkowska klasy.

Każdy obiekt klasy `Test` posiada własną kopię tego pola.

---

## Konstruktor

```cpp
Test::Test( int value )
   : x( value )
{
}
```

Konstruktor przyjmuje liczbę całkowitą i ustawia nią pole `x` za pomocą **listy inicjalizacyjnej**.

Jeśli utworzymy obiekt tak:

```cpp
Test testObject( 12 );
```

to pole `x` otrzyma wartość `12`.

### `explicit`

W deklaracji konstruktora użyto słowa kluczowego:

```cpp
explicit Test( int = 0 );
```

Oznacza to, że kompilator nie będzie wykonywał niejawnych konwersji z `int` do `Test` tam, gdzie mogłoby to prowadzić do niejednoznaczności lub błędów.

To dobra praktyka przy konstruktorach jednoargumentowych.

---

## Funkcja `print()`

```cpp
void Test::print(int y) const
```

Metoda została oznaczona jako `const`, czyli nie może zmieniać stanu obiektu.

Parametr `y` w tym przykładzie w ogóle nie jest używany – pełni jedynie rolę dodatkowego argumentu pokazującego, że metoda może mieć zwykłe parametry, niezależnie od tego, że wewnątrz ma też dostęp do obiektu przez `this`.

---

## Czym jest wskaźnik `this`

W każdej **niestatycznej** metodzie klasy C++ istnieje ukryty wskaźnik o nazwie `this`.

Wskazuje on na obiekt, dla którego metoda została wywołana.

Dla wywołania:

```cpp
testObject.print(3);
```

wewnątrz `print()` wskaźnik `this` wskazuje na `testObject`.

Można o tym myśleć tak, jakby kompilator zamieniał wywołanie na coś w rodzaju:

```cpp
print(&testObject, 3);
```

To oczywiście tylko model pojęciowy, ale dobrze tłumaczy sens działania `this`.

---

## Trzy sposoby dostępu do `x`

W metodzie `print()` pokazano trzy wersje dostępu do tej samej składowej:

### 1. Dostęp niejawny

```cpp
cout << "        x = " << x;
```

To najczęściej spotykana forma.

Wewnątrz metody klasy można po prostu pisać `x`, a kompilator i tak rozumie to jako odwołanie do pola bieżącego obiektu.

W rzeczywistości jest to skrót myślowy dla:

```cpp
this->x
```

---

### 2. Dostęp jawny przez `this->x`

```cpp
cout << "\n  this->x = " << this->x;
```

Tutaj wskaźnik `this` został użyty bezpośrednio.

* `this` jest wskaźnikiem do obiektu,
* operator `->` służy do dostępu do składowych przez wskaźnik.

Czyli:

```cpp
this->x
```

oznacza: „weź obiekt wskazywany przez `this` i odczytaj jego pole `x`”.

---

### 3. Dostęp przez `(*this).x`

```cpp
cout << "\n(*this).x = " << ( *this ).x << endl;
```

To forma równoważna poprzedniej, tylko bardziej dosłowna.

Najpierw:

```cpp
*this
```

oznacza obiekt wskazywany przez `this`, a potem:

```cpp
(*this).x
```

dostaje się do pola `x` operatorem `.`.

To dokładnie to samo co:

```cpp
this->x
```

Ponieważ operator `->` jest w praktyce skrótem od dereferencji i użycia operatora `.`.

---

## Dlaczego nawiasy przy `(*this).x` są konieczne

W kodzie znajduje się komentarz:

```cpp
// the parentheses around *this are required
```

To bardzo ważne.

Nie można napisać:

```cpp
*this.x
```

ponieważ operator `.` ma wyższy priorytet niż operator `*`.

Taki zapis zostałby zinterpretowany błędnie.

Dlatego poprawna forma to:

```cpp
(*this).x
```

Najpierw dereferencja wskaźnika `this`, a dopiero potem dostęp do pola `x`.

---

## Wynik programu

Dla obiektu:

```cpp
Test testObject( 12 );
```

wszystkie trzy instrukcje wypiszą tę samą wartość:

```cpp
        x = 12
  this->x = 12
(*this).x = 12
```

To właśnie potwierdza, że wszystkie trzy zapisy odnoszą się do tego samego pola tego samego obiektu.

---

## Znaczenie `this` w praktyce

Choć w prostych przykładach `this` nie zawsze jest potrzebne jawnie, w praktyce ma ono bardzo duże znaczenie.

### 1. Rozróżnianie pól i parametrów o tej samej nazwie

Na przykład:

```cpp
class Example {
private:
    int x;
public:
    void setX(int x) {
        this->x = x;
    }
};
```

Tutaj:

* `x` po prawej stronie to parametr funkcji,
* `this->x` to pole obiektu.

Bez `this->` nie dałoby się tego łatwo rozróżnić.

### 2. Zwracanie bieżącego obiektu

W bardziej zaawansowanych klasach często spotyka się:

```cpp
return *this;
```

co pozwala zwracać bieżący obiekt i np. łączyć wywołania metod.

### 3. Przekazywanie bieżącego obiektu do innych funkcji

Można też przekazać wskaźnik `this` dalej, np. do innych funkcji lub klas.

---

## `this` a funkcje `const`

Metoda `print()` ma deklarację:

```cpp
void print(int y) const
```

To oznacza, że wskaźnik `this` wewnątrz tej funkcji ma specjalny sens: wskazuje na obiekt, który nie powinien być modyfikowany.

W uproszczeniu można to rozumieć tak, że w metodzie `const`:

```cpp
this
```

zachowuje się jak wskaźnik do stałego obiektu.

Dlatego wewnątrz takiej metody nie można zmieniać zwykłych pól obiektu.

---

## Co program demonstruje merytorycznie

Program pokazuje kilka ważnych rzeczy naraz:

* każda niestatyczna metoda klasy ma dostęp do ukrytego wskaźnika `this`,
* zwykły zapis `x` wewnątrz metody to w praktyce skrót do `this->x`,
* zapis `this->x` i `(*this).x` są równoważne,
* `this` wskazuje dokładnie na ten obiekt, dla którego wywołano metodę,
* w metodzie `const` wskaźnik `this` nie pozwala modyfikować obiektu.

---

## Podsumowanie

Program `cw7-4.cpp` jest klasycznym przykładem wyjaśniającym działanie wskaźnika `this` w C++.

Najważniejsze wnioski:

* `this` to ukryty wskaźnik dostępny w niestatycznych metodach klasy,
* wskazuje na bieżący obiekt,
* `x`, `this->x` i `(*this).x` mogą oznaczać to samo pole tego samego obiektu,
* forma `this->x` jest szczególnie przydatna, gdy trzeba jednoznacznie wskazać, że chodzi o pole obiektu,
* wskaźnik `this` jest jednym z podstawowych mechanizmów działania metod klas w C++.

To ważny krok do zrozumienia, jak w rzeczywistości działają obiekty i metody w programowaniu obiektowym.
