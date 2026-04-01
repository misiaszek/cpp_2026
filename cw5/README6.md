# `cw5-6.cpp` – podstawy użycia `std::vector`

Program pokazuje szeroki przekrój podstawowych operacji na kontenerze `std::vector`. Demonstruje on:

* tworzenie wektorów o zadanym rozmiarze,
* odczyt rozmiaru metodą `size()`,
* wypisywanie i wczytywanie elementów,
* porównywanie wektorów,
* kopiowanie i przypisanie,
* dostęp do elementów przez `[]` i `at()`,
* obsługę wyjątku `out_of_range`,
* dynamiczne powiększanie wektora metodą `push_back()`.

Jest to bardzo ważny przykład, ponieważ `std::vector` jest jednym z najczęściej używanych kontenerów w C++.

## Kod programu

```cpp
// Demonstrating C++ Standard Library class template vector.
#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept> // for out_of_range exception class
using namespace std;

void outputVector( const vector< int > & ); // display the vector
void inputVector( vector< int > & ); // input values into the vector

int main()
{
   vector< int > integers1( 7 ); // 7-element vector< int >
   vector< int > integers2( 10 ); // 10-element vector< int >

   // print integers1 size and contents
   cout << "Size of vector integers1 is " << integers1.size()
      << "\nvector after initialization:" << endl;
   outputVector( integers1 );

   // print integers2 size and contents
   cout << "\nSize of vector integers2 is " << integers2.size()
      << "\nvector after initialization:" << endl;
   outputVector( integers2 );

   // input and print integers1 and integers2
   cout << "\nEnter 17 integers:" << endl;
   inputVector( integers1 );
   inputVector( integers2 );

   cout << "\nAfter input, the vectors contain:\n"
      << "integers1:" << endl;
   outputVector( integers1 );
   cout << "integers2:" << endl;
   outputVector( integers2 );

   // use inequality (!=) operator with vector objects
   cout << "\nEvaluating: integers1 != integers2" << endl;

   if ( integers1 != integers2 )
      cout << "integers1 and integers2 are not equal" << endl;

   // create vector integers3 using integers1 as an
   // initializer; print size and contents
   vector< int > integers3( integers1 ); // copy constructor

   cout << "\nSize of vector integers3 is " << integers3.size()
      << "\nvector after initialization:" << endl;
   outputVector( integers3 );

   // use assignment (=) operator with vector objects
   cout << "\nAssigning integers2 to integers1:" << endl;
   integers1 = integers2; // assign integers2 to integers1

   cout << "integers1:" << endl;
   outputVector( integers1 );
   cout << "integers2:" << endl;
   outputVector( integers2 );

   // use equality (==) operator with vector objects
   cout << "\nEvaluating: integers1 == integers2" << endl;

   if ( integers1 == integers2 )
      cout << "integers1 and integers2 are equal" << endl;

   // use square brackets to use the value at location 5 as an rvalue
   cout << "\nintegers1[5] is " << integers1[ 5 ];

   // use square brackets to create lvalue
   cout << "\n\nAssigning 1000 to integers1[5]" << endl;
   integers1[ 5 ] = 1000;
   cout << "integers1:" << endl;
   outputVector( integers1 );

   // attempt to use out-of-range subscript
   //http://www.cplusplus.com/reference/stdexcept/out_of_range/
   try
   {
      cout << "\nAttempt to display integers1.at( 15 )" << endl;
      cout << integers1.at( 15 ) << endl; // ERROR: out of range
   } // end try
   catch ( out_of_range &ex )
   {
      cerr << "An exception occurred: " << ex.what() << endl;
   } // end catch

   // changing the size of a vector
   cout << "\nCurrent integers3 size is: " << integers3.size() << endl;
   integers3.push_back( 1000 ); // add 1000 to the end of the vector
   cout << "New integers3 size is: " << integers3.size() << endl;
   cout << "integers3 now contains: ";
   outputVector( integers3 );
} // end main

// output vector contents
void outputVector( const vector< int > &items )
{
   for ( int item : items )
      cout << item << " ";

   cout << endl;
} // end function outputVector

// input vector contents
void inputVector( vector< int > &items )
{
   for ( int &item : items )
      cin >> item;
} // end function inputVector
```

## Co pokazuje ten przykład

Program jest przeglądem najważniejszych operacji na `std::vector<int>`.

Wektor to kontener dynamiczny, czyli taki, którego rozmiar może się zmieniać w czasie działania programu. W przeciwieństwie do `std::array`, jego liczba elementów nie musi być stała na etapie kompilacji.

## Tworzenie wektorów

Na początku programu tworzone są dwa wektory:

```cpp
vector< int > integers1( 7 );
vector< int > integers2( 10 );
```

Oznacza to utworzenie:

* `integers1` o rozmiarze `7`,
* `integers2` o rozmiarze `10`.

Ponieważ elementy mają typ `int`, zostaną zainicjalizowane wartością `0`.

Czyli na początku:

* `integers1` zawiera siedem zer,
* `integers2` zawiera dziesięć zer.

## `size()` – rozmiar wektora

Program wypisuje rozmiar wektorów za pomocą:

```cpp
integers1.size()
integers2.size()
```

Metoda `size()` zwraca aktualną liczbę elementów w wektorze.

## Funkcja `outputVector()`

```cpp
void outputVector( const vector< int > &items )
```

Funkcja przyjmuje wektor przez referencję do `const`, więc:

* nie kopiuje całego wektora,
* nie może go zmieniać.

Wewnątrz używa pętli zakresowej:

```cpp
for ( int item : items )
   cout << item << " ";
```

Funkcja wypisuje wszystkie elementy wektora oddzielone spacjami.

## Funkcja `inputVector()`

```cpp
void inputVector( vector< int > &items )
```

Ta funkcja przyjmuje wektor przez zwykłą referencję, ponieważ ma zmieniać jego zawartość.

Wewnątrz:

```cpp
for ( int &item : items )
   cin >> item;
```

każdy element jest wczytywany z wejścia. Użycie referencji `int&` jest konieczne, aby dane trafiały do rzeczywistych elementów wektora.

## Wczytywanie danych

Program prosi użytkownika o:

```cpp
Enter 17 integers:
```

Liczba `17` wynika z tego, że:

* pierwszy wektor ma 7 elementów,
* drugi ma 10 elementów,
* razem daje to 17 liczb.

Najpierw wypełniany jest `integers1`, potem `integers2`.

## Porównywanie wektorów

Program używa operatorów:

```cpp
integers1 != integers2
```

oraz później:

```cpp
integers1 == integers2
```

Dla `std::vector` operatory porównania działają element po elemencie.

Dwa wektory są równe tylko wtedy, gdy:

* mają ten sam rozmiar,
* mają takie same wartości na odpowiadających pozycjach.

## Konstruktor kopiujący

Instrukcja:

```cpp
vector< int > integers3( integers1 );
```

wywołuje konstruktor kopiujący i tworzy nowy wektor `integers3` jako kopię `integers1`.

Po tej operacji `integers3` ma:

* ten sam rozmiar co `integers1`,
* te same wartości.

## Przypisanie

Później program wykonuje:

```cpp
integers1 = integers2;
```

To nie tworzy nowego obiektu, tylko zastępuje zawartość `integers1` zawartością `integers2`.

Po przypisaniu:

* `integers1` będzie miało taki sam rozmiar jak `integers2`,
* elementy będą skopiowane z `integers2`.

## Dostęp do elementów przez `[]`

Program używa:

```cpp
integers1[ 5 ]
```

Najpierw do odczytu:

```cpp
cout << "\nintegers1[5] is " << integers1[ 5 ];
```

potem do modyfikacji:

```cpp
integers1[ 5 ] = 1000;
```

To pokazuje, że operator `[]` może być używany zarówno jako:

* **rvalue** – gdy odczytujemy wartość,
* **lvalue** – gdy przypisujemy nową wartość.

## `at()` i sprawdzanie zakresu

Program próbuje wykonać:

```cpp
integers1.at( 15 )
```

Metoda `at()` działa podobnie do `[]`, ale dodatkowo sprawdza, czy indeks mieści się w dozwolonym zakresie.

Jeśli indeks jest niepoprawny, zgłaszany jest wyjątek `out_of_range`.

W tym programie po przypisaniu `integers1 = integers2` wektor `integers1` ma rozmiar `10`, więc indeks `15` jest niepoprawny.

Dlatego program wchodzi do bloku `catch`:

```cpp
catch ( out_of_range &ex )
{
   cerr << "An exception occurred: " << ex.what() << endl;
}
```

To pokazuje bezpieczny sposób obsługi błędnego dostępu do elementu.

## `push_back()` – zmiana rozmiaru wektora

Na końcu programu wykonywane jest:

```cpp
integers3.push_back( 1000 );
```

Metoda `push_back()` dodaje nowy element na końcu wektora.

Jeśli wcześniej `integers3` miało rozmiar `7`, to po tej operacji będzie miało rozmiar `8`.

Nowy element `1000` stanie się ostatnim elementem wektora.

To właśnie jedna z najważniejszych zalet `std::vector`: możliwość łatwego powiększania kontenera.

## Co warto zapamiętać o `vector`

Ten przykład pokazuje, że `std::vector`:

* przechowuje elementy tego samego typu,
* zna swój aktualny rozmiar,
* może być porównywany,
* może być kopiowany i przypisywany,
* pozwala na bezpośredni dostęp do elementów,
* może dynamicznie rosnąć.

## Podsumowanie

Program `cw5-6.cpp` pokazuje:

* tworzenie wektorów o zadanym rozmiarze,
* inicjalizację elementów domyślnymi wartościami,
* wypisywanie i wczytywanie danych do wektora,
* porównywanie wektorów operatorami `==` i `!=`,
* kopiowanie i przypisanie,
* dostęp do elementów przez `[]` i `at()`,
* obsługę wyjątku `out_of_range`,
* powiększanie wektora przez `push_back()`.

To bardzo dobry przykład przekrojowy, pokazujący najważniejsze podstawy pracy z `std::vector` w C++.
