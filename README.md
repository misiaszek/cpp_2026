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

### 3. Zaawansowane Konstruktory i RAII (Laboratorium 3)
Skupiamy się na poprawnym zarządzaniu zasobami, unikaniu powielania kodu oraz bezpiecznym kopiowaniu obiektów:

* **Delegacja Konstruktorów:**
    * Wywoływanie jednego konstruktora przez inny w ramach tej samej klasy (Lista Inicjalizacyjna).
    * **Zasada DRY (Don't Repeat Yourself):** Unikanie duplikacji logiki walidacyjnej w przeciążonych konstruktorach.
* **Konstruktor Kopiujący (Copy Constructor):**
    * Tworzenie kopii istniejącego obiektu.
    * **Dlaczego referencja do stałej?** Wyjaśnienie sygnatury `ClassName(const ClassName&)` i unikanie nieskończonej rekurencji.
* **Zasada RAII (Resource Acquisition Is Initialization):**
    * Wiązanie cyklu życia zasobów (pamięć, pliki) z czasem życia obiektu.
    * Automatyczne zwalnianie zasobów w destruktorze (determinisme C++).
* **Płytka vs Głęboka Kopia (Shallow vs Deep Copy):**
    * Niebezpieczeństwa gołych wskaźników w klasach.
    * **Błąd Double Free:** Dlaczego domyślny konstruktor kopiujący zawodzi przy pamięci dynamicznej.
    * Implementacja głębokiej kopii poprzez alokację nowego obszaru pamięci.
* **Mechanizm Przyjaźni (friend):**
    * Udostępnianie prywatnych składowych funkcjom zewnętrznym.
    * **Przeciążanie operatora strumienia `<<`:** Wygodne wypisywanie stanu obiektu przy użyciu `std::cout`.
* **Nowoczesny C++ (C++17):**
    * Zmienne `static inline`, elizja kopii, CTAD oraz atrybut `[[nodiscard]]`.

### 4. Kontenery (std::array) i Nowoczesny C++ (Laboratorium 4)
Wprowadzenie do bezpiecznych kontenerów biblioteki standardowej oraz nowoczesnych mechanizmów losowania i iteracji:

* **Kontener `std::array`:**
    * Przewagi nad tablicami w stylu C (bezpieczeństwo, metody pomocnicze).
    * Statyczny rozmiar jako parametr szablonu (Compile-time).
* **Formatowanie Wyjścia (`<iomanip>`):**
    * Użycie `setw()`, `left`, `right` do tworzenia czytelnych tabel i wizualizacji danych.
* **Nowoczesne Losowanie Liczb (`<random>`):**
    * Wykorzystanie silników (engines) i rozkładów (distributions) zamiast przestarzałej funkcji `rand()`.
* **Czas życia obiektów lokalnych:**
    * Różnica między `auto` (automatycznym) a `static` (statycznym) czasem życia zmiennych wewnątrz funkcji.
* **Pętla zakresowa (*range-based for*):**
    * Bezpieczna i zwięzła iteracja po kontenerach z wykorzystaniem referencji (`&`) oraz kwalifikatora `const`.
* **C++17 w praktyce:**
    * Wykorzystanie uniwersalnej funkcji `std::size()` oraz CTAD dla kontenerów.

---

## Wymagania do zaliczenia projektu
Aby zaliczyć kurs, student musi przygotować autorski projekt, który praktycznie wykorzystuje poniższe mechanizmy języka C++:

### 1. Projekt Obiektowy
* **Klasy:** Podział kodu na logiczne obiekty z zachowaniem enkapsulacji (hermetyzacji).
* **Konstruktory i destruktory:** Inicjalizacja stanu obiektów oraz poprawne zwalnianie zasobów (RAII).
* **Konstruktor kopiujący:** Samodzielna implementacja głębokiej kopii, np. dla dynamicznych zasobów.
* **Deklaracja przyjaciela (`friend`):** Świadome udostępnianie prywatnego stanu klasy (np. do przeciążenia operatora `<<`).
* **Dziedziczenie:** Budowanie hierarchii klas i relacji "is-a".
* **Polimorfizm:** Wykorzystanie metod wirtualnych do wywoływania zachowań zależnych od rzeczywistego typu obiektu.
* **Klasa abstrakcyjna i metody czysto wirtualne:** Projektowanie interfejsów (klas bazowych, których nie można zainstancjonować).

### 2. Biblioteka Standardowa (STL)
* **Szablony kontenerów:** Praktyczne wykorzystanie m.in. `std::vector` lub `std::array` do przechowywania danych.
* **Iteratory:** Przemieszczanie się po kolekcjach danych.
* **Algorytmy:** Wykorzystanie wbudowanych funkcji z `<algorithm>` (np. sortowanie, wyszukiwanie).

### 3. Mechanizmy Języka C++
* **Podział na pliki (`.h` / `.cpp`):** Poprawna struktura projektu – deklaracje w plikach nagłówkowych, definicje w źródłowych, z wykorzystaniem linkera.
* **Zakresowa pętla for:** Użycie nowoczesnego *range-based for loop* do iteracji po kontenerach.
* **Przeciążanie operatorów:** Zdefiniowanie własnego zachowania np. dla operatorów arytmetycznych, porównania lub strumienia wejścia/wyjścia.
* **Obsługa wyjątków (`try-catch`):** Bezpieczne zarządzanie błędami i awariami w trakcie działania programu.
* **Własny szablon klasy/funkcji:** *(Nieobowiązkowe)* Opcjonalne wykorzystanie programowania uogólnionego (`template`).

---

*Szczegółowe opisy poszczególnych programów znajdują się w folderach `cw2/`, `cw3/` oraz `cw4/` w odpowiednich plikach `README.md`.*

