# Ćwiczenie 1: Wprowadzenie do C++

## Co to jest C++?

C++ to język programowania, który łączy cechy programowania niskopoziomowego (zbliżonego do asemblera) z wysokopoziomowymi abstrakcjami obiektowymi. Dzięki temu jest idealny do tworzenia wydajnych bibliotek i aplikacji systemowych.

**Przykład:** Przeglądarka Chromium jest napisana w C++, co pozwala jej być bardzo szybką i efektywną.

C++ pozwala na:
- Bezpośrednią manipulację pamięcią
- Tworzenie wydajnego kodu maszynowego
- Abstrakcje obiektowe (klasy, dziedziczenie, polimorfizm)
- Szablony generyczne (STL - Standard Template Library)

---

## Program main.cpp - Pierwszy "Hello World"

### Kod:
```cpp
#include <iostream>

int main() {
    std::cout << "hello world" << std::endl;
    std::cout.precision(2);
    std::cout << "pi: " << 3.14159 << std::endl;
    std::operator<<(std::operator<<(std::cout, "Hello world"), std::endl); 
    return 0;
}
```

### Objaśnienie:

1. **`#include <iostream>`** - Dołącza bibliotekę do operacji wejścia/wyjścia
2. **`int main()`** - Punkt wejścia programu, zwraca całkowitą wartość
3. **`std::cout`** - Obiekt reprezentujący standardowe wyjście (ekran)
4. **Operator `<<`** - Operator przesunięcia bitów używany tutaj jako operator otaczający do wysyłania danych do strumienia
5. **`std::endl`** - Wypisuje nową linię i "flush" bufor
6. **`precision(2)`** - Ustawia precyzję wypisywania liczb zmiennoprzecinkowych na 2 miejsca po przecinku

### Co się dzieje?

Linia:
```cpp
std::operator<<(std::operator<<(std::cout, "Hello world"), std::endl);
```

Jest równoważna z:
```cpp
std::cout << "Hello world" << std::endl;
```

To pokazuje, że operator `<<` jest wewnętrznie funkcją, która:
- Przyjmuje dwa argumenty: strumień wyjściowy i wartość do wypisania
- Zwraca referencję do strumienia, co umożliwia łączenie operacji

---

## Obiekty i Klasy STL

W C++ każdy "gadżet" do wykonania pracy jest **obiektem** stworzonym z **klasy**. 

### Przykład: `std::cout`

```cpp
std::cout << "Hello";  // cout to obiekt klasy std::basic_ostream
```

`std::cout` to obiekt klasy, który ma stany (np. precyzja) i metody (np. `precision()`, `operator<<`).

### Tworzenie obiektu ze standardowej biblioteki - Vector

```cpp
#include <vector>

int main() {
    std::vector<int> liczby;           // Tworzymy wektor (inteligentną tablicę)
    liczby.push_back(10);              // Dodajemy element
    liczby.push_back(20);
    
    for (int x : liczby)               // Pętla zakresowa (range-based for)
        std::cout << x << std::endl;
    
    return 0;
}
```

---

## bitset.cpp - Operatory Przesunięcia Bitów (C)

**Uwaga:** `bitset.cpp` zawiera kod w C, a nie C++!

### Operator przesunięcia w lewo (`<<`) i prawo (`>>`) 

W C (i C++), operatory przesunięcia bitów działają na poziomie bitów:

```c
int x = 5;        // 0101 w binarnym
int y = x << 1;   // 1010 w binarnym (10 w dziesiętnym)
int z = x >> 1;   // 0010 w binarnym (2 w dziesiętnym)
```

- **`x << 1`** - Przesuwa bity w lewo (mnożenie przez 2)
- **`x >> 1`** - Przesuwa bity w prawo (dzielenie przez 2)

W C++ te same operatory są przeciążane do obsługi strumieni danych (`std::cout << "tekst"`).

---

## Kompilacja

### C++:
```bash
g++ main.cpp -o main -lstdc++
```

- `g++` - Kompilator C++
- `main.cpp` - Plik źródłowy
- `-o main` - Nazwa pliku wyjściowego
- `-lstdc++` - Linkowanie standardowej biblioteki C++

### Uruchomienie:
```bash
./main
```

---

## Zasoby do Nauki C++

- **[Kurs C++ (cpp0x.pl)](https://cpp0x.pl/kursy/Kurs-C++/1)** - Polski kurs C++
- **[LearnCpp.com](https://www.learncpp.com/)** - Kompleksowy angielski kurs

---

## Wymagania do Zaliczenia Projektu

### 1. Programowanie Obiektowe (OOP)
- [ ] **Klasy** - Definiowanie klas z polami i metodami
- [ ] **Konstruktory i destruktory** - Inicjalizacja i czyszczenie zasobów
- [ ] **Konstruktor kopiujący** - Głębokie kopowanie obiektów
- [ ] **Deklaracja przyjaciela** (friend) - Dostęp do prywatnych członków
- [ ] **Dziedziczenie** - Klasa pochodna dziedziczy po klasie bazowej
- [ ] **Polimorfizm** - Wirtualne metody i przesłanianie
- [ ] **Klasa abstrakcyjna** - Klasa, której nie można instancjować bezpośrednio
- [ ] **Czysto wirtualne metody** - Metody, które muszą być zaimplementowane w podklasach

### 2. Standard Template Library (STL)
- [ ] **Szablony** - `std::vector`, `std::array` itp.
- [ ] **Iteratory** - Poruszanie się po kolekcjach
- [ ] **Algorytmy** - `std::sort`, `std::find` itp.

### 3. Cechy Języka C++
- [ ] **Pętla zakresowa** - `for (int x : container) { }`
- [ ] **Własny szablon klasy/funkcji** - Generyczne komponenty (opcjonalnie)
- [ ] **Przeciążanie operatorów** - Definiowanie zachowania operatorów dla klas
- [ ] **Wyjątki** - `try`, `catch`, `throw`

---

## Kolejne Ćwiczenia

Bardziej zaawansowane zagadnienia będą poruszane w kolejnych ćwiczeniach. Skupiamy się teraz na fundamentach i zrozumieniu, jak działa podstawowy program C++.
