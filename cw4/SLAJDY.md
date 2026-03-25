# PROGRAMOWANIE OBIEKTOWE W C++
## Część 4: Kontenery (std::array) i Nowoczesny C++

**Prowadzący:** dr Marcin Misiaszek  
Rok akademicki 2025/2026  
*Wydział Fizyki, Astronomii i Informatyki Stosowanej UJ*

---

## 1. std::array – Bezpieczniejsza alternatywa dla tablic C

W tradycyjnym C tablice są problematyczne: "gubią" swój rozmiar przy przekazywaniu do funkcji i nie oferują metod pomocniczych.

### Dlaczego warto używać std::array?
* **Zna swój rozmiar** - Metoda `size()` zwraca liczbę elementów.
* **Bezpieczeństwo** - Metoda `at()` sprawdza zakres (wyrzuca wyjątek przy błędzie).
* **Wydajność** - Pamięć jest alokowana na stosie, brak narzutu dynamicznego.
* **Interfejs STL** - Współpracuje z iteratorami i algorytmami standardowymi.

```cpp
#include <array>
std::array<int, 5> n = { 32, 27, 64, 18, 95 }; // Typ + Rozmiar
```

---

## 2. Rozmiar musi być stały (Compile-time)

Rozmiar `std::array` jest częścią jego typu. Musi być znany już w momencie kompilacji programu.

> 💡 **Ważne:** Używaj `const size_t` lub `constexpr size_t` do definiowania rozmiarów tablic.

```cpp
const size_t arraySize = 5; 
std::array<int, arraySize> s; // Poprawnie

// C++17: Class Template Argument Deduction (CTAD)
std::array data = { 1, 2, 3 }; // Kompilator sam wywnioskuje <int, 3>!
```

---

## 3. Formatowanie wyjścia i Wizualizacja danych

Biblioteka `<iomanip>` pozwala na tworzenie czytelnych tabel i raportów w konsoli.

* `std::setw(n)` - Ustala szerokość pola dla następnego elementu.
* `std::left` / `std::right` - Wyrównanie tekstu.

### Przykład: Tekstowy wykres słupkowy
```cpp
for (size_t i = 0; i < n.size(); ++i) {
    std::cout << std::setw(7) << i << ": ";
    for (unsigned int stars = 0; stars < n[i]; ++stars)
        std::cout << '*';
    std::cout << std::endl;
}
```

---

## 4. Nowoczesne Losowanie Liczb (<random>)

Zapomnij o `rand() % n`. C++11 wprowadził bibliotekę `<random>`, która oddziela silnik generujący bity od rozkładu prawdopodobieństwa.

```cpp
#include <random>
#include <ctime>

std::default_random_engine engine(time(0)); // Silnik
std::uniform_int_distribution<int> randomInt(1, 6); // Rozkład (kostka)

int wynik = randomInt(engine); // Generowanie wartości
```

> 💡 **Zalety:** Lepsza jakość losowości, łatwa zmiana rozkładu (np. na normalny/Gaussa), brak "skrzywienia" modulo.

---

## 5. Czas życia obiektu: static vs automatic

Zmienne lokalne w funkcjach mogą mieć różny czas życia (storage duration).

* **Automatyczne (Domyślne):** Tworzone przy każdym wejściu do funkcji, niszczone przy wyjściu. Stan nie jest zachowywany.
* **Statyczne (static):** Inicjalizowane tylko RAZ. Istnieją do końca programu. **Zachowują wartość** między wywołaniami funkcji!

```cpp
void func() {
    static int counter = 0; // Inicjalizacja tylko przy pierwszym wywołaniu
    counter++; 
    std::cout << counter;
} // counter nie ginie po wyjściu z funkcji!
```

---

## 6. Range-based for (Pętla zakresowa)

Pozwala na bezpieczną i zwięzłą iterację po kontenerach bez używania indeksów.

```cpp
std::array<int, 5> items = { 1, 2, 3, 4, 5 };

// TYLKO ODCZYT (bezpiecznie przez referencję do const)
for (const auto& item : items) {
    std::cout << item << " ";
}

// MODYFIKACJA (przez referencję)
for (auto& item : items) {
    item *= 2;
}
```

---

## 7. C++17: Udogodnienia dla tablic

* **std::size()** - Globalna funkcja zwracająca rozmiar kontenera lub tradycyjnej tablicy.
* **CTAD** - Wnioskowanie typów szablonów (np. `std::array a = {1, 2};`).
* **Structured Bindings** - Rozpakowywanie elementów (C++17).

```cpp
int oldTable[] = {1, 2, 3};
auto s = std::size(oldTable); // Uniwersalne podejście
```

---

## 8. Zadanie Praktyczne 1

> 💡 **Zadanie:** Symulator rzutu dwiema kostkami (suma 2-12).

### Opis zadania:
* Stwórz tablicę `std::array<int, 13> frequency` (indeksy 2-12).
* Użyj nowoczesnego generatora `<random>` do symulacji rzutu dwiema kostkami (1-6).
* Wykonaj 36 000 rzutów. W każdym rzucie oblicz sumę oczek.
* Zinkrementuj odpowiedni licznik w tablicy `frequency`.

---

## 9. Zadanie Praktyczne 2

> 💡 **Zadanie:** Analiza wyników i wizualizacja.

### Opis zadania:
* Wypisz tabelę wyników (Suma | Częstość).
* Użyj `std::setw`, aby tabela była czytelna.
* Dodaj kolumnę z procentowym udziałem danego wyniku.
* **Dla chętnych:** Wyświetl tekstowy wykres słupkowy (1 gwiazdka = 1%).
