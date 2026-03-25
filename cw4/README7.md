# `cw4-7.cpp` – pętla zakresowa `range-based for`

Program pokazuje użycie **pętli zakresowej** (`range-based for`) do odczytywania i modyfikowania elementów tablicy `std::array`. Jest to nowocześniejszy i często wygodniejszy sposób przechodzenia po wszystkich elementach kontenera niż klasyczna pętla z indeksem.

W tym przykładzie program:

- wypisuje elementy tablicy przed zmianą,
- mnoży każdy element przez `2`,
- wypisuje elementy po modyfikacji.

## Kod programu

```cpp
// Using range-based for to multiply an array's elements by 2.
#include <iostream>
#include <array>
using namespace std;

int main()
{
   array< int, 5 > items = { 1, 2, 3, 4, 5 };

   // display items before modification
   cout << "items before modification: ";
   for ( const int &item : items )
      cout << item << " ";

   // multiply the elements of items by 2
   for (int &itemRef : items )
      itemRef *= 2;

   // display items after modification
   cout << "\nitems after modification: ";
   for ( const int &item : items )
      cout << item << " ";

   cout << endl;
} // end main
```

## Co pokazuje ten przykład

Program demonstruje:

- deklarację i inicjalizację tablicy `std::array`,
- użycie pętli zakresowej do odczytu elementów,
- użycie pętli zakresowej z referencją do modyfikacji elementów,
- różnicę między odczytem a modyfikacją danych w kontenerze.

## Tablica `items`

Na początku programu tworzona jest tablica:

```cpp
array< int, 5 > items = { 1, 2, 3, 4, 5 };
```

Oznacza to, że tablica `items` przechowuje pięć liczb całkowitych:

- `1`
- `2`
- `3`
- `4`
- `5`

## Pętla zakresowa

W programie użyto konstrukcji:

```cpp
for ( const int &item : items )
```

To jest właśnie **pętla zakresowa**. Jej ogólny schemat wygląda tak:

```cpp
for ( deklaracja_elementu : kontener )
```

Oznacza to: przejdź kolejno po wszystkich elementach danego kontenera i w każdej iteracji udostępnij bieżący element pod nazwą podaną po lewej stronie.

W tym przypadku kontenerem jest tablica `items`.

## Odczyt elementów przed modyfikacją

Pierwsza pętla ma postać:

```cpp
for ( const int &item : items )
   cout << item << " ";
```

### Dlaczego użyto `const int&`

Tutaj zastosowano:

```cpp
const int &item
```

co oznacza:

- `item` jest referencją do elementu tablicy,
- `const` zabezpiecza przed przypadkową zmianą wartości,
- element nie jest kopiowany.

W tym konkretnym przykładzie dla typu `int` kopiowanie nie byłoby problemem, bo `int` jest mały, ale zapis przez referencję do `const` jest dobrą praktyką i dobrze pokazuje intencję: **tylko odczytujemy dane**.

Ta pętla wypisuje:

```text
1 2 3 4 5
```

## Modyfikacja elementów

Druga pętla wygląda tak:

```cpp
for (int &itemRef : items )
   itemRef *= 2;
```

Tutaj użyto:

```cpp
int &itemRef
```

czyli zwykłej referencji do elementu tablicy.

To bardzo ważne, ponieważ dzięki referencji zmieniana jest **oryginalna wartość w tablicy**, a nie tylko jej kopia.

Instrukcja:

```cpp
itemRef *= 2;
```

jest skróconym zapisem:

```cpp
itemRef = itemRef * 2;
```

Każdy element tablicy zostaje więc pomnożony przez `2`.

### Jak zmieniają się wartości

Początkowo tablica zawiera:

```text
1, 2, 3, 4, 5
```

Po wykonaniu pętli zawiera:

```text
2, 4, 6, 8, 10
```

## Dlaczego referencja jest tu konieczna

Gdyby napisać:

```cpp
for ( int item : items )
   item *= 2;
```

wtedy `item` byłby kopią elementu tablicy. Program zmieniałby tylko tę kopię, a oryginalna tablica pozostałaby bez zmian.

Dlatego do modyfikacji elementów kontenera trzeba użyć referencji:

```cpp
int &itemRef
```

## Odczyt elementów po modyfikacji

Trzecia pętla znów używa odczytu przez referencję do `const`:

```cpp
for ( const int &item : items )
   cout << item << " ";
```

Tym razem wypisane zostaną już wartości po zmianie:

```text
2 4 6 8 10
```

## Wynik działania programu

Program wypisze:

```text
items before modification: 1 2 3 4 5
items after modification: 2 4 6 8 10
```

Układ końca linii może zależeć od środowiska, ale sens wyniku pozostaje taki sam.

## Dlaczego ten przykład jest ważny

Pętla zakresowa jest jednym z najwygodniejszych sposobów pracy z kontenerami w nowoczesnym C++. Jej zalety to:

- prostszy zapis niż klasyczna pętla z indeksem,
- mniejsze ryzyko błędu w warunku lub indeksowaniu,
- większa czytelność,
- łatwe rozróżnienie między odczytem a modyfikacją dzięki użyciu `const` i referencji.

Ten przykład dobrze pokazuje dwa podstawowe warianty:

- **odczyt** – `const int&`,
- **modyfikacja** – `int&`.

## `auto`, `auto&` i `const auto&` w pętli zakresowej

W pętli zakresowej zamiast jawnie pisać typ elementu można użyć słowa kluczowego `auto`. Kompilator sam wywnioskuje odpowiedni typ.

### `auto`

```cpp
for ( auto item : items )
    cout << item << ' ';
```

Tutaj `item` jest kopią elementu tablicy. Taki zapis nadaje się do odczytu, ale zmiany wykonywane na `item` nie wpływają na oryginalny kontener.

### `auto&`

```cpp
for ( auto& item : items )
    item *= 2;
```

Tutaj `item` jest referencją do rzeczywistego elementu kontenera. Dzięki temu można modyfikować oryginalne dane.

### `const auto&`

```cpp
for ( const auto& item : items )
    cout << item << ' ';
```

To bardzo częsty i wygodny zapis do samego odczytu:

- nie tworzy kopii elementu,
- nie pozwala go zmienić,
- działa dobrze także dla większych obiektów, nie tylko dla `int`.

W praktyce:

- `auto` – gdy kopia jest w porządku,
- `auto&` – gdy chcemy modyfikować elementy,
- `const auto&` – gdy chcemy tylko czytać bez kopiowania.

## Przykład z `auto*` dla własnej klasy

Pętla zakresowa może też działać na kontenerze przechowującym wskaźniki. Wtedy można użyć `auto*`.

Przykład:

```cpp
#include <array>
#include <iostream>
using namespace std;

class Person
{
public:
    void say() const
    {
        cout << "Hello
";
    }
};

int main()
{
    Person a{};
    Person b{};
    array<Person*, 2> people = { &a, &b };

    for ( auto* person : people )
        person->say();
}
```

Tutaj:

- `people` jest tablicą wskaźników do obiektów `Person`,
- `auto* person` oznacza, że zmienna pętli ma być wskaźnikiem,
- do wywołania metody używa się operatora `->`.

To przydatne wtedy, gdy kontener przechowuje adresy obiektów zamiast samych obiektów.

## Podsumowanie

Program `cw4-7.cpp` pokazuje:

- użycie pętli zakresowej `for`,
- odczyt elementów tablicy przez referencję do `const`,
- modyfikację elementów tablicy przez referencję,
- wpływ zmian na oryginalny kontener,
- wygodny sposób iterowania po wszystkich elementach `std::array`,
- możliwość stosowania `auto`, `auto&`, `const auto&`, a także `auto*` przy pracy ze wskaźnikami.

Jest to bardzo ważny przykład nowoczesnego stylu C++, ponieważ pętla zakresowa jest często preferowanym sposobem przechodzenia po elementach kontenerów wtedy, gdy nie potrzebujemy bezpośrednio indeksu elementu.

