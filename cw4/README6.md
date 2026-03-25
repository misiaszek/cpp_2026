# `cw4-6.cpp` – tablica statyczna lokalna i tablica automatyczna lokalna

Program pokazuje różnicę między **lokalną tablicą statyczną** a **lokalną tablicą automatyczną**. Obie tablice są zadeklarowane wewnątrz funkcji, ale zachowują się inaczej przy kolejnych wywołaniach tych funkcji.

Jest to bardzo ważny przykład, ponieważ pokazuje, że nie wystarczy wiedzieć, gdzie zmienna została zadeklarowana. Trzeba jeszcze rozumieć **czas życia obiektu** i sposób jego inicjalizacji.

## Kod programu

```cpp
// static array initialization and automatic array initialization.
#include <iostream>
#include <array>
using namespace std;

void staticArrayInit(); // function prototype
void automaticArrayInit(); // function prototype
const size_t arraySize = 3;

int main()
{
   cout << "First call to each function:\n";
   staticArrayInit();
   automaticArrayInit();

   cout << "\n\nSecond call to each function:\n";
   staticArrayInit();
   automaticArrayInit();
   cout << endl;
} // end main

// function to demonstrate a static local array
void staticArrayInit()
{
   // initializes elements to 0 first time function is called
   static array< int, arraySize > array1; // static local array

   cout << "\nValues on entering staticArrayInit:\n";

   // output contents of array1
   for ( size_t i = 0; i < array1.size(); ++i )
      cout << "array1[" << i << "] = " << array1[ i ] << "  ";

   cout << "\nValues on exiting staticArrayInit:\n";

   // modify and output contents of array1
   for ( size_t j = 0; j < array1.size(); ++j )
      cout << "array1[" << j << "] = " << ( array1[ j ] += 5 ) << "  ";
} // end function staticArrayInit

// function to demonstrate an automatic local array
void automaticArrayInit()
{
   // initializes elements each time function is called
   array< int, arraySize > array2 = { 1, 2, 3 }; // automatic local array

   cout << "\n\nValues on entering automaticArrayInit:\n";

   // output contents of array2
   for ( size_t i = 0; i < array2.size(); ++i )
      cout << "array2[" << i << "] = " << array2[ i ] << "  ";

   cout << "\nValues on exiting automaticArrayInit:\n";

   // modify and output contents of array2
   for ( size_t j = 0; j < array2.size(); ++j )
      cout << "array2[" << j << "] = " << ( array2[ j ] += 5 ) << "  ";
} // end function automaticArrayInit
```

## Co pokazuje ten przykład

Program porównuje dwa przypadki:

- `array1` – tablica lokalna statyczna,
- `array2` – tablica lokalna automatyczna.

Obie tablice mają ten sam rozmiar, ale różnią się tym:

- kiedy są tworzone,
- jak długo istnieją,
- czy zachowują swoje wartości pomiędzy kolejnymi wywołaniami funkcji.

## Stała `arraySize`

Na początku programu znajduje się:

```cpp
const size_t arraySize = 3;
```

Jest to stała określająca rozmiar obu tablic. Dzięki temu zarówno `array1`, jak i `array2` mają po 3 elementy.

## Funkcja `staticArrayInit()`

Najważniejsza deklaracja w tej funkcji to:

```cpp
static array< int, arraySize > array1;
```

To jest **lokalna zmienna statyczna**.

### Co oznacza `static` wewnątrz funkcji

Słowo kluczowe `static` oznacza tutaj, że:

- obiekt jest tworzony tylko raz,
- jego czas życia trwa do końca działania programu,
- przy kolejnych wywołaniach funkcji nie powstaje nowa tablica,
- tablica zachowuje zmienione wartości między wywołaniami funkcji.

### Inicjalizacja `array1`

Ponieważ `array1` jest lokalną zmienną statyczną i nie podano dla niej własnych wartości początkowych, jej elementy są zainicjalizowane zerami przy pierwszym użyciu.

Na pierwszym wejściu do funkcji mamy więc:

```text
array1[0] = 0
array1[1] = 0
array1[2] = 0
```

### Modyfikacja `array1`

W drugiej pętli elementy tablicy są zwiększane o `5`:

```cpp
array1[ j ] += 5
```

Po pierwszym wywołaniu funkcji wartości będą więc wynosiły:

```text
5, 5, 5
```

Przy drugim wywołaniu funkcji program zobaczy właśnie te wartości na wejściu, ponieważ tablica nie jest tworzona od nowa.

Potem znów doda `5` do każdego elementu, więc po wyjściu będzie:

```text
10, 10, 10
```

## Funkcja `automaticArrayInit()`

Najważniejsza deklaracja w tej funkcji to:

```cpp
array< int, arraySize > array2 = { 1, 2, 3 };
```

To jest **lokalna zmienna automatyczna**, czyli zwykła zmienna lokalna funkcji.

### Co oznacza zmienna automatyczna

Zmienna automatyczna:

- powstaje przy każdym wejściu do funkcji,
- przestaje istnieć po wyjściu z funkcji,
- przy każdym kolejnym wywołaniu funkcji jest tworzona od nowa,
- nie pamięta zmian z poprzedniego wywołania.

### Inicjalizacja `array2`

Za każdym razem, gdy program wchodzi do `automaticArrayInit()`, tworzona jest nowa tablica z wartościami:

```text
1, 2, 3
```

### Modyfikacja `array2`

Potem program zwiększa każdy element o `5`, więc na końcu wywołania otrzymujemy:

```text
6, 7, 8
```

Jednak przy następnym wywołaniu funkcji tablica znowu zostaje utworzona od początku jako:

```text
1, 2, 3
```

Czyli poprzednie zmiany nie zostają zachowane.

## Co wypisze program przy pierwszym wywołaniu

### `staticArrayInit()` – pierwsze wywołanie

Na wejściu:

```text
array1[0] = 0  array1[1] = 0  array1[2] = 0
```

Na wyjściu:

```text
array1[0] = 5  array1[1] = 5  array1[2] = 5
```

### `automaticArrayInit()` – pierwsze wywołanie

Na wejściu:

```text
array2[0] = 1  array2[1] = 2  array2[2] = 3
```

Na wyjściu:

```text
array2[0] = 6  array2[1] = 7  array2[2] = 8
```

## Co wypisze program przy drugim wywołaniu

### `staticArrayInit()` – drugie wywołanie

Na wejściu:

```text
array1[0] = 5  array1[1] = 5  array1[2] = 5
```

Na wyjściu:

```text
array1[0] = 10  array1[1] = 10  array1[2] = 10
```

### `automaticArrayInit()` – drugie wywołanie

Na wejściu znowu:

```text
array2[0] = 1  array2[1] = 2  array2[2] = 3
```

Na wyjściu znowu:

```text
array2[0] = 6  array2[1] = 7  array2[2] = 8
```

## Kluczowa różnica

Najważniejsza różnica między tymi dwiema tablicami jest taka:

- `array1` **pamięta** zmiany między wywołaniami funkcji,
- `array2` **nie pamięta** zmian, bo powstaje od nowa przy każdym wejściu do funkcji.

To jest istota różnicy między lokalnym obiektem statycznym a lokalnym obiektem automatycznym.

## Czas życia obiektu

Ten program bardzo dobrze pokazuje pojęcie **czasu życia obiektu**:

- obiekt statyczny żyje przez cały czas działania programu,
- obiekt automatyczny żyje tylko od wejścia do funkcji do jej zakończenia.

To jedno z najważniejszych zagadnień w C++, ponieważ sposób życia obiektu wpływa na jego inicjalizację, zachowanie oraz pamiętanie stanu.

## Podsumowanie

Program `cw4-6.cpp` pokazuje:

- różnicę między tablicą lokalną statyczną a automatyczną,
- że lokalna zmienna statyczna jest inicjalizowana tylko raz,
- że lokalna zmienna automatyczna jest tworzona od nowa przy każdym wywołaniu,
- że obiekt statyczny zachowuje stan między wywołaniami funkcji,
- że obiekt automatyczny nie zachowuje zmian po zakończeniu funkcji.

Jest to bardzo ważny przykład pomagający zrozumieć nie tylko tablice, ale też ogólne zasady życia i inicjalizacji obiektów w C++.

