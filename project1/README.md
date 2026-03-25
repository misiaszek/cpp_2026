# Projekt 1: TinyPacker v1.0
## Prosty Archiwizator Plików Binarnych

Ten projekt demonstruje potęgę mechanizmów wprowadzonych w laboratoriach 1-4. Mimo że program jest krótki, wykorzystuje zaawansowane koncepcje zarządzania pamięcią i zasobami, które odróżniają nowoczesny C++ od tradycyjnego C.

### 🛠 Wykorzystane technologie

#### 1. RAII (Resource Acquisition Is Initialization)
W klasie `DataBuffer` alokujemy pamięć dla danych pliku (`new char[]`). Dzięki destruktorowi, pamięć ta jest **automatycznie zwalniana**, gdy obiekt wychodzi z zakresu. Student nie musi ręcznie wywoływać `delete` – robi to za niego automat C++.

#### 2. Głęboka Kopia (Deep Copy) i Operator Przypisania
Zaimplementowaliśmy własny **Konstruktor Kopiujący** oraz **Operator Przypisania**. Jest to kluczowe, ponieważ klasa `DataBuffer` zarządza pamięcią dynamiczną.

**Gdzie następuje wywołanie?**
W metodzie `addFile` wykonujemy operację:
```cpp
m_buffers[m_fileCount] = buf; // TUTAJ wywoływany jest operator przypisania!
```
Obiekt `buf` jest zmienną lokalną. Gdybyśmy nie zdefiniowali własnego operatora przypisania, kompilator wykonałby **płytką kopię** (skopiowałby tylko adres wskaźnika). Po zakończeniu funkcji `addFile`, destruktor lokalnego obiektu `buf` usunąłby pamięć, pozostawiając tablicę `m_buffers` ze wskaźnikami do nieistniejących danych (**Dangling Pointers**).

Dzięki Głębokiej Kopii, każdy plik w archiwum posiada własny, niezależny obszar pamięci, co zapobiega krytycznym błędom typu **Double Free**.

#### 3. Wzorzec Singleton (Meyers' Singleton)
Klasa `Logger` używa **lokalnej zmiennej statycznej** do zarządzania logowaniem. Gwarantuje to, że w całym programie istnieje tylko jedna instancja dziennika zdarzeń, a jej inicjalizacja jest bezpieczna i wydajna.

#### 4. Kontener `std::array` (C++11/14/17)
Użyliśmy `std::array` do przechowywania:
- **Magicznego numeru (Signature):** Identyfikatora formatu pliku.
- **Listy metadanych:** Stałej liczby wpisów o spakowanych plikach.
To bezpieczniejsza i nowocześniejsza alternatywa dla tablic w stylu C.

#### 5. Mechanizm Przyjaźni (`friend`) i Strumienie
Przeciążyliśmy `operator<<` jako przyjaciela klasy `TinyArchive`. Dzięki temu możemy wypisać całą strukturę archiwum (spis treści) jednym poleceniem: `std::cout << archive;`.

#### 6. Biblioteka `<iomanip>`
Użyliśmy `std::setw` oraz `std::left`/`std::right`, aby wygenerować profesjonalnie wyglądający raport w konsoli, z wyrównanymi kolumnami.

---

### 🚀 Jak uruchomić?
1. Skompiluj program: `g++ TinyPacker.cpp -o TinyPacker -std=c++17`
2. Upewnij się, że w katalogu znajduje się plik `README.md` (program spróbuje go spakować).
3. Uruchom: `./TinyPacker`
4. Program utworzy plik `test_archive.tpak`, który zawiera spakowane dane w formacie binarnym.

### 💡 Zadanie dla studenta
Spróbuj rozbudować projekt o funkcję **rozpakowywania** (`unpackFile`), która odczyta plik `.tpak`, przeanalizuje nagłówek i odtworzy oryginalne pliki na dysku!
