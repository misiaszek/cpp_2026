# Kurs Języka C++ (2026)

## Cel kursu
Głównym celem kursu jest opanowanie języka C++ od podstaw aż po zaawansowane techniki programowania obiektowego (OOP) oraz wykorzystanie biblioteki standardowej (STL). Kurs kładzie nacisk na:
* **Wydajność:** Zrozumienie, jak C++ zarządza pamięcią i zasobami.
* **Abstrakcję:** Tworzenie bezpiecznego i czytelnego kodu za pomocą klas, wzorców i polimorfizmu.
* **Standardy:** Wykorzystanie nowoczesnych cech języka (C++11/14/17/20).

---

## Co zostało omówione do tej pory?

### 1. Fundamenty (Laboratorium 1)
* **Wprowadzenie do C++:** Różnice między C a C++, rola kompilatora (`g++`), linkowanie biblioteki standardowej.
* **Operacje wejścia/wyjścia:** Użycie strumieni `std::cout`, manipulatorów takich jak `std::endl` oraz ustawianie precyzji wyświetlania.
* **Podstawy STL:** Wprowadzenie do kontenera `std::vector` i pętli zakresowej (*range-based for*).
* **Operacje niskopoziomowe:** Manipulacje bitowe (przesunięcia w lewo/prawo) i ich różnica w kontekście C (operatory bitowe) oraz C++ (przeciążone operatory strumieni).

### 2. Programowanie Obiektowe – Podstawy (Laboratorium 2)
W ramach obecnych zajęć skupiamy się na ewolucji od prostych struktur do zaawansowanych klas:

* **Struktury (`struct`):**
    * Grupowanie powiązanych danych (np. `Date`).
    * Inicjalizacja agregatów.
    * Przekazywanie obiektów do funkcji przez referencję do stałej (`const Date&`).
* **Metody (Funkcje członkowskie):**
    * Przenoszenie zachowania (logiki) do wnętrza typu danych.
    * Różnica między strukturą w C (tylko dane) a w C++ (dane + metody).
* **Klasy (`class`) i Enkapsulacja:**
    * Różnica między `struct` a `class` (domyślne poziomy dostępu: `public` vs `private`).
    * Ukrywanie wewnętrznej reprezentacji danych (specyfikator `private`).
    * Udostępnianie kontrolowanego interfejsu (specyfikator `public`).
* **Interfejs klasy:**
    * **Gettery i Settery:** Bezpieczny odczyt i modyfikacja pól prywatnych.
    * **Spójność danych:** Zapewnienie, że powiązane pola (np. imię i inicjał) są zawsze aktualizowane wspólnie.
    * **Metody stałe (`const`):** Oznaczanie metod, które nie zmieniają stanu obiektu.
* **Inicjalizacja i Konstruktory:**
    * Cykl życia obiektu – automatyczne wywołanie konstruktora.
    * **Lista inicjalizacyjna konstruktora:** Najbardziej wydajny i poprawny sposób ustawiania wartości początkowych pól klasy.
    * Różnica między argumentami konstruktora a polami klasy.

---

## Wymagania do zaliczenia projektu (kamienie milowe)
Podczas kursu uczeń powinien zaimplementować:
1.  **Klasy** z pełną enkapsulacją, konstruktorami i destruktorami.
2.  **Mechanizmy OOP:** Dziedziczenie, polimorfizm (metody wirtualne), klasy abstrakcyjne.
3.  **Zasoby STL:** Kontenery, iteratory i algorytmy.
4.  **Zaawansowane cechy:** Przeciążanie operatorów, obsługa wyjątków, szablony.

---

*Szczegółowe opisy poszczególnych programów z Laboratorium 2 znajdują się w plikach `README1.md` – `README7.md`.*

