# PROGRAMOWANIE OBIEKTOWE W C++
## Część 6: Wyjątki, Kompozycja i Organizacja kodu

**Prowadzący:** dr Marcin Misiaszek  
Rok akademicki 2025/2026  
*Wydział Fizyki, Astronomii i Informatyki Stosowanej UJ*

---

## 1. Bezpieczny wektor - metoda at()

W **Laboratorium 5** poznaliśmy `std::vector`. Dzisiaj skupimy się na bezpiecznym dostępie do jego danych.

* `v[i]` - Szybki, ale niebezpieczny (brak kontroli zakresu).
* `v.at(i)` - Bezpieczny (sprawdza zakres).
* Jeśli indeks jest zły -> rzuca wyjątek `std::out_of_range`.

```cpp
std::vector<int> data = {1, 2, 3};
try {
    data.at(10) = 666; // Błąd zakresu!
} catch (const std::out_of_range& e) {
    std::cout << e.what() << std::endl;
}
```

---

## 2. Mechanizm Wyjątków (throw, try-catch)

Wyjątki pozwalają reagować na sytuacje awaryjne w kontrolowany sposób.

1. **throw** - zgłoszenie błędu (może to być `int`, `string` lub obiekt).
2. **try** - blok kodu, który "obserwujemy".
3. **catch** - obsługa konkretnego typu błędu.

```cpp
try {
    throw 42; // Zgłaszamy liczbę
} catch (int e) {
    std::cout << "Złapano błąd nr: " << e;
}
```

---

## 3. Hierarchia Wyjątków Standardowych

Większość błędów w C++ dziedziczy po `std::exception`. Możemy je łapać ogólnie.

* `std::out_of_range` - błąd indeksu.
* `std::runtime_error` - błąd w trakcie działania.
* `catch(...)` - łapie **wszystko** (ostatnia deska ratunku).

```cpp
try {
    // kod mogący zawieść
} catch (const std::exception& e) {
    std::cerr << "Standardowy błąd: " << e.what();
} catch (...) {
    std::cerr << "Nieznany błąd!";
}
```

---

## 4. Kompozycja: Relacja "has-a"

Kompozycja to budowanie złożonych obiektów z prostszych części. Obiekt **ZAWIERA** inny obiekt.

* Samochód **ma** Silnik.
* Stwór **ma** Pozycję (np. `Point2D`).
* Część powstaje i ginie razem z całością (silna więź).

```cpp
class Samochod {
    Silnik m_silnik; // Kompozycja (pole klasy)
    std::string m_marka;
public:
    Samochod(string m, string t) : m_marka(m), m_silnik(t) {}
};
```

---

## 5. Inicjalizacja Części Składowych

Pamiętasz **Laboratorium 3** i listę inicjalizacyjną? Jest ona KLUCZOWA przy kompozycji.

* Obiekty składowe muszą zostać utworzone **zanim** wejdziemy do ciała konstruktora.
* Używamy składni `: pole(argument)`.

```cpp
Samochod(string m, string t) 
    : m_marka(m), m_silnik(t) // Tu powstaje silnik!
{
    // Tu silnik już działa
}
```

---

## 6. Organizacja kodu: Pliki Nagłówkowe (.h)

Większe projekty dzielimy na pliki, aby zachować porządek.

* **.h** (header) - deklaracje klas i funkcji.
* **.cpp** - implementacja (definicje metod).
* Pliki dołączamy przez `#include "MojaKlasa.h"`.

> 💡 **Dobra praktyka:** Logika punktu w `Point2D.h`, logika stwora w `Creature.h`.

---

## 7. Problem Wielokrotnego Dołączenia

Jeśli dwa pliki dołączą ten sam nagłówek, kompilator zgłosi błąd (podwójna definicja).

**Rozwiązanie klasyczne (Include Guards):**
```cpp
#ifndef MOJAKLASA_H
#define MOJAKLASA_H

class MojaKlasa { ... };

#endif
```

---

## 8. Nowoczesna Alternatywa: #pragma once

Większość współczesnych kompilatorów wspiera prostszą dyrektywę:

```cpp
#pragma once // Zastępuje cały mechanizm #ifndef/#define

class MojaKlasa {
    // zawartość nagłówka
};
```

* **Zalety:** Krótszy kod, brak ryzyka pomyłki w nazwie makra, szybsza kompilacja.
* **Wady:** Nie jest formalną częścią standardu (ale działa wszędzie: GCC, Clang, MSVC).

---

## 9. Współpraca obiektów (Delegacja)

Obiekt złożony może prosić swoje części o wykonanie pracy.

```cpp
// W klasie Creature
void moveTo(int x, int y) {
    m_location.setPoint(x, y); // Prosimy punkt o zmianę
}

// W wypisywaniu (operator << z cw5)
friend ostream& operator<<(ostream& os, const Creature& c) {
    os << c.name << " jest w " << c.m_location;
    return os;
}
```

---

## 10. Zadanie Praktyczne 1

> 💡 **Zadanie:** Bezpieczny dostęp.

1. Stwórz `std::vector<int>` o rozmiarze 5.
2. Spróbuj zmienić element `v.at(10)`.
3. Dodaj blok `try-catch`, który wypisze komunikat o błędzie.
4. Sprawdź, co się stanie, jeśli użyjesz `v[10]` (bez `at`).

---

## 11. Zadanie Praktyczne 2

> 💡 **Zadanie:** Kompozycja i Nagłówki.

1. Stwórz klasę `Kolo` (pole `promien`).
2. Stwórz klasę `Rysunek`, która zawiera obiekt `Kolo`.
3. Podziel kod na pliki `.h` (użyj `#pragma once`) oraz `main.cpp`.
4. Zainicjalizuj koło w konstruktorze rysunku przez listę inicjalizacyjną.
