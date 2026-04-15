# `cw7-3` – obiekty stałe i funkcje składowe `const`

Program pokazuje jedną z bardzo ważnych zasad programowania obiektowego w C++: **jak działają obiekty stałe (`const`) oraz funkcje składowe oznaczone jako `const`**.

Na tym przykładzie widać wyraźnie, że:

* obiekt stały może wywoływać tylko metody oznaczone jako `const`,
* metody nieoznaczone jako `const` nie mogą być wywoływane dla obiektu stałego,
* oznaczenie funkcji jako `const` jest obietnicą, że metoda nie zmieni stanu obiektu.

Program jest podzielony na trzy pliki:

* `main.cpp`,
* `Time.h`,
* `Time.cpp`.

## Cel programu

Program ma pokazać zależność między:

* typem obiektu (`const` albo nie-`const`),
* typem funkcji składowej (`const` albo nie-`const`).

To bardzo ważny element interfejsu klas w C++, bo pozwala kompilatorowi pilnować, czy dany obiekt nie jest modyfikowany w niedozwolony sposób.

---

## `main.cpp`

```cpp
// const objects and const member functions.
#include "Time.h" // include Time class definition

int main()
{
   Time wakeUp( 6, 45, 0 ); // non-constant object
   const Time noon( 12, 0, 0 ); // constant object

                          // OBJECT      MEMBER FUNCTION
   wakeUp.setHour( 18 );  // non-const   non-const
   
   //noon.setHour( 12 );    // const       non-const
   
   wakeUp.getHour();      // non-const   const
   
   noon.getMinute();      // const       const
   noon.printUniversal(); // const       const
   
   //noon.printStandard();  // const       non-const
} // end main
```

W funkcji `main()` tworzone są dwa obiekty klasy `Time`:

```cpp
Time wakeUp( 6, 45, 0 );
const Time noon( 12, 0, 0 );
```

### `wakeUp`

To zwykły obiekt, czyli **nie-const**.

Może wywoływać:

* metody `const`,
* metody nie-`const`.

### `noon`

To obiekt stały:

```cpp
const Time noon( 12, 0, 0 );
```

Taki obiekt może wywoływać **tylko metody `const`**.

Nie może wywoływać metod, które potencjalnie zmieniają stan obiektu.

---

## `Time.h`

```cpp
// Fig. 9.4: Time.h
// Time class containing a constructor with default arguments.
// Member functions defined in Time.cpp.

// prevent multiple inclusions of header 
#ifndef TIME_H
#define TIME_H

// Time abstract data type definition
class Time 
{
public:
   explicit Time( int = 0, int = 0, int = 0 ); // default constructor

   // set functions
   void setTime( int, int, int ); // set hour, minute, second
   void setHour( int ); // set hour (after validation)
   void setMinute( int ); // set minute (after validation)
   void setSecond( int ); // set second (after validation)

   // get functions
   unsigned int getHour() const; // return hour
   unsigned int getMinute() const; // return minute
   unsigned int getSecond() const; // return second

   void printUniversal() const; // output time in universal-time format
   void printStandard(); // output time in standard-time format
private:
   unsigned int hour; // 0 - 23 (24-hour clock format)
   unsigned int minute; // 0 - 59
   unsigned int second; // 0 - 59
}; // end class Time

#endif
```

Nagłówek pokazuje bardzo ważny podział metod na dwie grupy:

### Metody modyfikujące stan obiektu

```cpp
void setTime( int, int, int );
void setHour( int );
void setMinute( int );
void setSecond( int );
```

To metody **nie-const**, ponieważ zmieniają pola obiektu.

### Metody tylko do odczytu

```cpp
unsigned int getHour() const;
unsigned int getMinute() const;
unsigned int getSecond() const;
void printUniversal() const;
```

To metody oznaczone jako `const`, bo mają tylko odczytywać stan obiektu i go nie zmieniać.

### Metoda nieoznaczona jako `const`

```cpp
void printStandard();
```

Ta metoda nie ma dopisku `const`, więc z punktu widzenia kompilatora jest traktowana jako metoda, która **może zmieniać obiekt**.

Dlatego nie można jej wywołać dla obiektu stałego.

---

## `Time.cpp`

```cpp
// Member-function definitions for class Time.
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "Time.h" // include definition of class Time from Time.h
using namespace std;

// Time constructor initializes each data member 
Time::Time( int hour, int minute, int second ) 
{ 
   setTime( hour, minute, second ); // validate and set time
} // end Time constructor

// set new Time value using universal time
void Time::setTime( int h, int m, int s )
{
   setHour( h ); // set private field hour
   setMinute( m ); // set private field minute
   setSecond( s ); // set private field second
} // end function setTime

// set hour value
void Time::setHour( int h )
{
   if ( h >= 0 && h < 24 )
      hour = h;
   else
      throw invalid_argument( "hour must be 0-23" );
} // end function setHour

// set minute value
void Time::setMinute( int m )
{
   if ( m >= 0 && m < 60 )
      minute = m; 
   else
      throw invalid_argument( "minute must be 0-59" );
} // end function setMinute

// set second value
void Time::setSecond( int s )
{
   if ( s >= 0 && s < 60 )
      second = ( ( s >= 0 && s < 60 ) ? s : 0 ); 
   else
      throw invalid_argument( "second must be 0-59" );
} // end function setSecond

// return hour value
unsigned int Time::getHour() const
{
   return hour;
} // end function getHour

// return minute value
unsigned int Time::getMinute() const 
{
   return minute;
} // end function getMinute

// return second value
unsigned int Time::getSecond() const
{
   return second;
} // end function getSecond

// print Time in universal-time format (HH:MM:SS)
void Time::printUniversal() const
{
   cout << setfill( '0' ) << setw( 2 ) << getHour() << ":"
      << setw( 2 ) << getMinute() << ":" << setw( 2 ) << getSecond();
} // end function printUniversal

// print Time in standard-time format (HH:MM:SS AM or PM)
void Time::printStandard() 
{
   cout << ( ( getHour() == 0 || getHour() == 12 ) ? 12 : getHour() % 12 )
      << ":" << setfill( '0' ) << setw( 2 ) << getMinute()
      << ":" << setw( 2 ) << getSecond() << ( hour < 12 ? " AM" : " PM" );
} // end function printStandard
```

---

## Co oznacza `const` po nazwie metody

Gdy metoda ma postać:

```cpp
unsigned int getHour() const;
```

oznacza to, że jest to **stała funkcja składowa**.

### Znaczenie praktyczne

Taka metoda:

* nie może zmieniać zwykłych pól obiektu,
* może być wywoływana dla obiektów `const`,
* informuje użytkownika klasy, że jest bezpieczna i tylko odczytuje dane.

W uproszczeniu:

> `const` po nazwie metody oznacza: „ta funkcja nie zmienia stanu obiektu”.

---

## Dlaczego `getHour()`, `getMinute()`, `getSecond()` są `const`

Te funkcje tylko zwracają aktualną wartość pól:

```cpp
unsigned int Time::getHour() const
{
   return hour;
}
```

Nie wykonują żadnej modyfikacji, więc powinny być oznaczone jako `const`.

To dobra praktyka i bardzo ważny element poprawnego projektowania interfejsu klasy.

---

## Dlaczego `printUniversal()` jest `const`

```cpp
void Time::printUniversal() const
```

Ta metoda tylko wypisuje dane obiektu, ale ich nie zmienia.

Dlatego również powinna być `const`.

Dzięki temu można ją wywołać także dla obiektu stałego:

```cpp
noon.printUniversal();
```

---

## Dlaczego `setHour()` nie jest `const`

```cpp
void setHour( int );
```

Ta funkcja zmienia pole `hour`, więc nie może być oznaczona jako `const`.

Właśnie dlatego działa dla zwykłego obiektu:

```cpp
wakeUp.setHour( 18 );
```

ale nie działałaby dla obiektu stałego:

```cpp
//noon.setHour( 12 );
```

bo obiekt `noon` jest `const`.

---

## Dlaczego `printStandard()` nie działa dla `const` obiektu

W nagłówku metoda ma postać:

```cpp
void printStandard();
```

Nie ma dopisku `const`, więc kompilator uznaje, że może ona zmieniać stan obiektu.

Dlatego ta linia jest błędna:

```cpp
//noon.printStandard();
```

Mimo że z samej logiki programu metoda tylko wypisuje czas, to brak `const` w deklaracji sprawia, że nie wolno jej wywołać dla obiektu stałego.

To bardzo ważna lekcja: **nie wystarczy, że metoda „faktycznie nic nie zmienia” – musi być jeszcze poprawnie oznaczona jako `const`.**

---

## Zależność między obiektem a metodą

W `main()` pokazano cztery przypadki:

### 1. Obiekt nie-`const` + metoda nie-`const`

```cpp
wakeUp.setHour( 18 );
```

To jest poprawne.

### 2. Obiekt `const` + metoda nie-`const`

```cpp
//noon.setHour( 12 );
```

To jest niedozwolone.

### 3. Obiekt nie-`const` + metoda `const`

```cpp
wakeUp.getHour();
```

To jest poprawne.

Obiekt nie-`const` może wywoływać również metody `const`.

### 4. Obiekt `const` + metoda `const`

```cpp
noon.getMinute();
noon.printUniversal();
```

To jest poprawne.

---

## Walidacja danych w klasie `Time`

Program przy okazji pokazuje też enkapsulację i kontrolę poprawności danych.

Na przykład:

```cpp
void Time::setHour( int h )
{
   if ( h >= 0 && h < 24 )
      hour = h;
   else
      throw invalid_argument( "hour must be 0-23" );
}
```

Oznacza to, że nie można ustawić dowolnej liczby jako godziny – klasa pilnuje poprawnego zakresu.

Podobnie jest dla minut i sekund.

To pokazuje, że dobrze zaprojektowana klasa:

* ukrywa dane,
* udostępnia kontrolowany interfejs,
* sprawdza poprawność przekazywanych wartości.

---

## Uwaga o `printStandard()`

W tym przykładzie metoda:

```cpp
void printStandard();
```

powinna logicznie również być oznaczona jako `const`, bo tylko wypisuje dane i ich nie zmienia.

Lepsza wersja wyglądałaby tak:

```cpp
void printStandard() const;
```

oraz w pliku `Time.cpp`:

```cpp
void Time::printStandard() const
```

Wtedy można byłoby poprawnie wywołać:

```cpp
noon.printStandard();
```

To bardzo typowy przykład pokazujący, jak łatwo zapomnieć o `const` przy metodach tylko do odczytu.

---

## Najważniejsze wnioski

Program pokazuje, że w C++:

* obiekt `const` może wywoływać tylko metody `const`,
* metody `const` służą do bezpiecznego odczytu danych,
* metody zmieniające stan obiektu nie mogą być `const`,
* poprawne oznaczanie metod jako `const` jest ważną częścią projektowania klasy,
* kompilator pilnuje zgodności między stałością obiektu a wywoływaną metodą.

---

## Podsumowanie

Program `cw7-3` jest klasycznym przykładem wyjaśniającym relację między:

* obiektami stałymi,
* funkcjami składowymi `const`,
* metodami modyfikującymi stan obiektu.

Dzięki niemu można zrozumieć, że słowo `const` w C++ nie dotyczy tylko zmiennych, ale również metod klasy i całego sposobu projektowania interfejsu obiektowego.

To jeden z podstawowych tematów
