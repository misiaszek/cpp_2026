# `cw5-4.cpp` – podstawy użycia `std::set`

Program pokazuje podstawowe użycie kontenera `std::set`, czyli zbioru przechowującego **unikalne** elementy w **porządku rosnącym**.

## Kod programu

```cpp
#include<iostream>
#include<set>
using namespace std;
int main()
{
   set<int> zbior;
   zbior.insert(5);
   zbior.insert(40);
   zbior.insert(1);
   zbior.insert(1);

   set<int>::iterator it;   // teraz it jest wskaznikiem do zbioru
   for( it=zbior.begin(); it!=zbior.end(); ++it )
      cout<<*it<<'\n';

   for(auto& z : zbior) std::cout << z << std::endl;

   return 0;
}
```

## Najważniejsze obserwacje

### 1. `std::set` nie przechowuje duplikatów

Do zbioru dodawane są wartości:

```cpp
5, 40, 1, 1
```

Mimo że `1` została wstawiona dwa razy, w zbiorze pojawi się tylko raz.

### 2. Elementy są uporządkowane

`std::set` przechowuje elementy w porządku rosnącym, więc wynik będzie uporządkowany:

```text
1
5
40
```

niezależnie od kolejności wstawiania.

## Iteracja po zbiorze

Program pokazuje dwa sposoby przechodzenia po elementach.

### Klasyczny iterator

```cpp
set<int>::iterator it;
for( it=zbior.begin(); it!=zbior.end(); ++it )
   cout<<*it<<'\n';
```

To podejście działa podobnie jak w poprzednich przykładach z iteratorami.

### Pętla zakresowa

```cpp
for(auto& z : zbior) std::cout << z << std::endl;
```

To krótsza i wygodniejsza forma przechodzenia po wszystkich elementach kontenera.

W tym przypadku `auto&` oznacza referencję do aktualnego elementu zbioru.

## Wynik działania programu

Program wypisze elementy dwa razy, najpierw przez iterator, potem przez pętlę zakresową:

```text
1
5
40
1
5
40
```

## Podsumowanie

Program `cw5-4.cpp` pokazuje:

* użycie kontenera `std::set`,
* dodawanie elementów przez `insert()`,
* automatyczne usuwanie duplikatów,
* automatyczne sortowanie elementów,
* iterację klasycznym iteratorem,
* iterację przez pętlę zakresową.

To prosty przykład pokazujący, że `std::set` jest dobrym wyborem wtedy, gdy chcemy przechowywać elementy unikalne i uporządkowane.
