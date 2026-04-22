# Project 2: Advanced TinyPacker (v2.0)

## 📋 Przegląd
**Advanced TinyPacker** to rozbudowana wersja narzędzia do archiwizacji plików. Projekt pokazuje przejście od prostego, jednoplikowego programu (**Project 1**) do profesjonalnego systemu wieloplikowego, wykorzystującego pełną moc programowania obiektowego (Lab 1–8).

---

## 🏗️ Dlaczego ten projekt jest lepszy niż v1.0?

| Cecha | Project 1 (Lab 1-4) | Project 2 (Lab 1-8) | Dlaczego to ważne? |
|-------|---------------------|---------------------|-------------------|
| **Struktura** | Jeden plik `.cpp` | Wiele plików `.h` / `.cpp` | Łatwiejsze zarządzanie dużym kodem. |
| **Pamięć** | Sztywne tablice `array` | Dynamiczny `vector` | Archiwum nie ma już limitu 5 plików. |
| **Błędy** | Metody `bool` (true/false) | Wyjątki `try-catch` | Bezpieczniejsza obsługa błędów krytycznych. |
| **Rozszerzalność** | Jedna klasa "wszystkorobiąca" | Dziedziczenie klas | Można łatwo dodać nowe formaty zapisu. |
| **Zasoby** | Ręczne `new` / `delete` | RAII (Zasada Trójki) | Automatyczne sprzątanie pamięci. |

---

## 🛠️ Przewodnik po Technikach (Mapa Ćwiczeń)

### 📂 Organizacja i Budowa (Lab 6, 8)
* **`Makefile`**: Automatyzacja kompilacji. Zamiast wpisywać `g++` ręcznie, używamy jednego polecenia `make`.
* **`#pragma once`**: Nowoczesne strażniki nagłówków, chronią przed błędami redefinicji klas.
* **Lista inicjalizacyjna**: Najszybszy sposób ustawiania pól w konstruktorze (widoczny w każdym pliku `.cpp`).

### 🔒 Enkapsulacja i Bezpieczeństwo (Lab 2, 7)
* Wszystkie pola (np. `m_data`, `m_files`) są ukryte w sekcjach **`private`** lub **`protected`**.
* Metody odczytujące są oznaczone jako **`const`**, co zapobiega przypadkowej zmianie stanu obiektu przez programistę.
* Użycie **`this`** w `TinyPacker.cpp` do jawnego wskazania pól klasy bazowej.

### ♻️ Zarządzanie Zasobami (RAII) (Lab 3, 7)
* Klasa **`FileBuffer`** to serce zarządzania pamięcią. Realizuje **Zasadę Trójki**:
    1. **Destruktor**: Automatycznie zwalnia `delete[] m_data`.
    2. **Konstruktor kopiujący**: Pozwala bezpiecznie dodawać pliki do kontenera `vector`.
    3. **Operator przypisania**: Chroni przed wyciekami przy kopiowaniu obiektów.

### 🛑 Obsługa Sytuacji Awaryjnych (Lab 6)
* Zamiast sprawdzać `if (file == NULL)` po każdym kroku, program rzuca **`std::runtime_error`**.
* W `main.cpp` blok `catch (const std::exception& e)` przechwytuje dowolny błąd standardowy i wypisuje czytelny komunikat przez `e.what()`.

### 🧬 Dziedziczenie i Hierarchia (Lab 8)
* **`Packer` (Baza)**: Klasa ogólna. Wie jak przechowywać pliki i liczyć ich rozmiar.
* **`TinyPacker` (Pochodna)**: Specjalista. Wie dokładnie, w jakim formacie zapisać dane na dysk.
* **Przesłanianie (Shadowing)**: `TinyPacker` ma własną definicję metody `save()`, która wykonuje specyficzną pracę, korzystając z publicznego interfejsu klasy bazowej.

---

## 🚀 Jak uruchomić projekt?

1. Otwórz terminal w folderze `project2`.
2. Kompiluj: `make`
3. Uruchom: `./project2` (lub `project2.exe` na Windows)
4. Wyczyść: `make clean`
