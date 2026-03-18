# PROGRAMOWANIE OBIEKTOWE W C++
## Część 3: Delegacja, Kopiowanie, RAII i Przyjaźń

**Prowadzący:** dr Marcin Misiaszek  
Rok akademicki 2025/2026  
*Wydział Fizyki, Astronomii i Informatyki Stosowanej UJ*

---

## 1. Zmora powielania kodu - Wstęp do Delegacji

Często klasa potrzebuje wielu konstruktorów (przeciążanie), by móc tworzyć obiekty na różne sposoby. Złe podejście polega na kopiowaniu logiki inicjalizacyjnej między nimi.

### Dlaczego kopiowanie to błąd?
* **Zasada DRY (Don't Repeat Yourself)** - "Nie powtarzaj się". Fundamentalna zasada inżynierii oprogramowania.
* Kiedy ta sama linijka kodu pojawia się 2 razy w programie, prosisz się o kłopoty. Gdy zajdzie potrzeba zmiany logiki, zaktualizujesz tylko jedno miejsce, a drugie zapomnisz, tworząc **niespójność (bug)**.

```cpp
// ZŁE PODEJŚCIE - POWIELANIE KODU
class_c(int my_max) {
    max = my_max > 0 ? my_max : 10;
}
class_c(int my_max, int my_min) {
    max = my_max > 0 ? my_max : 10; // Kopia! Złe!
    min = my_min > 0 && my_min < max ? my_min : 1;
}
```

---

## 2. Delegacja Konstruktorów w praktyce

Aby zachować czystość kodu i zasadę DRY, nowsze standardy C++ wprowadziły **delegację konstruktorów**. Pozwala ona jednemu konstruktorowi wywołać inny konstruktor tej samej klasy w liście inicjalizacyjnej.

```cpp
// DOBRE PODEJŚCIE - DELEGACJA KONSTRUKTORÓW
class class_c {
public:
    int max; int min; int middle;

    class_c(int my_max) {
        max = my_max > 0 ? my_max : 10;
    }
    
    // Delegujemy ustawienie "max" do pierwszego konstruktora
    class_c(int my_max, int my_min) : class_c(my_max) {
        min = my_min > 0 && my_min < max ? my_min : 1;
    }
    
    // Delegujemy ustawienie "max" i "min" o poziom wyżej
    class_c(int my_max, int my_min, int my_middle) : class_c(my_max, my_min) {
        middle = my_middle < max && my_middle > min ? my_middle : 5;
    }
};
```

> 💡 **Ważne:** Dzięki delegacji logika walidacji danej zmiennej znajduje się ZAWSZE tylko w jednym miejscu (Single Source of Truth).

---

## 3. Konstruktor Kopiujący

Konstruktor kopiujący to specjalny konstruktor, który tworzy nowy obiekt jako **kopię** istniejącego obiektu tej samej klasy. Używamy go m.in. przy inicjalizacji, przekazywaniu obiektu do funkcji przez wartość oraz przy zwracaniu go przez wartość.

```cpp
class Fraction {
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };
public:
    Fraction(int num = 0, int den = 1) : m_numerator{num}, m_denominator{den} {}

    // WŁASNY KONSTRUKTOR KOPIUJĄCY
    Fraction(const Fraction& fraction) 
        : m_numerator{ fraction.m_numerator }, 
          m_denominator{ fraction.m_denominator } 
    {
        std::cout << "Kopiuję obiekt!\n";
    }
};

Fraction f1{ 5, 3 };
Fraction f2{ f1 }; // Wywołuje konstruktor kopiujący!
```

---

## 4. Tajemnica Argumentu Konstruktora Kopiującego

Zwróć uwagę na sygnaturę: `Fraction(const Fraction& fraction)`. Dlaczego musi być tam referencja i słówko const?

### Dlaczego referencja (&)?
Gdyby argument przekazywano przez wartość: `Fraction(Fraction fraction)`, to podczas wywołania konstruktora kompilator musiałby... **skopiować argument** do zmiennej lokalnej. Do skopiowania użyłby oczywiście... konstruktora kopiującego! Ten znowu próbowałby skopiować argument, co doprowadziłoby do nieskończonej rekurencji i błędu kompilacji.

### Dlaczego const?
Chcemy skopiować dane z oryginału, ale pod żadnym pozorem nie chcemy zmodyfikować obiektu, z którego kopiujemy! `const` jest naszą gwarancją bezpieczeństwa. Dodatkowo pozwala na kopiowanie z obiektów tymczasowych (r-wartości, gdy z const l-value reference jest to dozwolone w starszym kodzie).

---

## 5. Koncept RAII: Resource Acquisition Is Initialization

RAII to fundamentalny paradygmat w C++, odróżniający ten język np. od Javy czy C#. Mówi o tym, że **cykl życia zasobu powinien być ściśle związany z cyklem życia obiektu**.

* **Acquisition (Pozyskanie)** - Przydzielanie pamięci, otwieranie plików czy gniazd sieciowych odbywa się **w konstruktorze**.
* **Release (Zwolnienie)** - Sprzątanie zasobów, zamykanie plików, usuwanie pamięci następuje zawsze **w destruktorze**.

> 💡 **Ważne:** Dzięki RAII nie musimy ręcznie pamiętać o zwalnianiu zasobów w przypadku błędów czy wczesnych powrotów (return). Gdy obiekt schodzi z zakresu (kończy się blok klamrowy `}`), jego destruktor jest wywoływany automatycznie, a zasoby zwalniane.

---

## 6. Pułapka Płytkiej Kopii (Shallow Copy) - Gołe Wskaźniki

Jeśli klasa zarządza zasobem dynamicznym (np. pamięcią przez goły wskaźnik), domyślny konstruktor kopiujący (generowany przez kompilator) skopiuje **tylko adres wskaźnika**, a nie same dane. To zjawisko to płytka kopia.

```cpp
class BadArray {
    int* data;
public:
    BadArray(int size) { data = new int[size]; }
    ~BadArray() { delete[] data; } // Destruktor zwalnia pamięć
};

void test() {
    BadArray a1(10);
    BadArray a2(a1); // Płytka kopia! a2.data i a1.data wskazują na TO SAMO miejsce!
} // KONIEC BLOKU: Wywoływany jest ~BadArray() dla a2, a potem dla a1.
```

> ⚠️ **BŁĄD: Double Free!** Destruktor obiektu `a2` usuwa pamięć wskazywaną przez `data`. Następnie destruktor `a1` próbuje usunąć **dokładnie tę samą, już zwolnioną pamięć**. Program ulegnie awarii (Segmentation Fault / Heap Corruption). W takich wypadkach musimy napisać WŁASNY konstruktor kopiujący robiący "Głęboką Kopię" (Deep Copy), alokując nową pamięć dla kopii.

---

## 7. Deklaracje Przyjaciela (friend)

Z zasady enkapsulacji dane klasy są prywatne. Czasem jednak globalna funkcja (lub inna klasa) musi ściśle współpracować z naszą klasą. Zamiast otwierać na stałe publiczny dostęp do pół, deklarujemy funkcję jako **przyjaciela (friend)**.

Klasycznym przykładem jest przeciążenie operatora wypisywania na strumień `<<`, który musi mieć dostęp do prywatnego stanu obiektu, by wypisać jego zawartość.

```cpp
class Accumulator {
private:
    int m_value { 0 };

public:
    void add(int value) { m_value += value; }

    // Deklaracja przyjaciela: ta funkcja NIE jest metodą klasy,
    // ale dzięki 'friend' może używać prywanych pól (np. m_value).
    friend std::ostream& operator<<(std::ostream& os, const Accumulator& accumulator);
};
 
std::ostream& operator<<(std::ostream& os, const Accumulator& accumulator) {
    os << accumulator.m_value; // Dostęp do pola prywatnego m_value!
    return os;
}
```

---

## 8. C++17 z myślą o Klasach (Bonus)

Standard C++17 wprowadził wiele ulepszeń, które ułatwiają programowanie obiektowe i eliminują przestarzałe "boilerplate'y" (powtarzalne kody).

* **Zmienne inline (inline variables)** - W C++17 możesz wreszcie zainicjalizować statyczną zmienną członkowską (`static inline int counter = 0;`) bezpośrednio w ciele klasy (w pliku nagłówkowym), bez konieczności definiowania jej osobno w pliku .cpp.
* **Gwarantowana elizja kopii (Copy Elision)** - W wielu sytuacjach kompilator ma teraz **obowiązek** wyciąć operację kopiowania (np. zwracając nowy obiekt z funkcji), co czyni przekazywanie obiektów przez wartość przy zwracaniu bezkosztowym, pomijając konstruktor kopiujący!
* **CTAD (Class Template Argument Deduction)** - Kompilator potrafi domyślić się typu szablonowego z argumentów konstruktora (np. piszemy `std::pair p(1, 2.5);` zamiast `std::pair<int, double> p(1, 2.5);`).
* **Atrybut [[nodiscard]]** - Użyty nad klasą lub metodą nakazuje kompilatorowi zgłosić ostrzeżenie, jeśli programista zignoruje zwrócony wynik. Bardzo przydatne przy zwracaniu kodów błędu lub nowych obiektów.

---

## 9. Zadanie Praktyczne 1 (A)

> 💡 **Zadanie:** Podstawowa struktura klasy SmartArray (Zasada RAII).

### Krok 1: Pola i cykl życia
Zaimplementuj szkielet klasy `SmartArray`:
* **Pola prywatne:** `int* m_data` (wskaźnik na tablicę) oraz `int m_size` (rozmiar).
* **Konstruktor:** `SmartArray(int size)` – alokuje dynamicznie tablicę typu int o podanym rozmiarze i wypełnia ją zerami (użyj pętli lub `std::fill`).
* **Destruktor:** Zwalnia bezpiecznie pamięć przy użyciu operatora `delete[]`.

---

## 10. Zadanie Praktyczne 1 (B)

> 💡 **Zadanie:** Implementacja Głębokiej Kopii (Deep Copy).

### Krok 2: Kopiowanie
Do klasy `SmartArray` dodaj **własny konstruktor kopiujący**:
* Musi on alokować **nowy, osobny obszar pamięci** o takim samym rozmiarze jak oryginał.
* Następnie musi skopiować każdą wartość (każdy element int) z tablicy obiektu źródłowego do nowej tablicy.
* Pamiętaj o poprawnej sygnaturze: `SmartArray(const SmartArray& other)`.

---

## 11. Zadanie Praktyczne 2

> 💡 **Zadanie:** Testowanie i weryfikacja niezależności obiektów.

### Krok 3: Weryfikacja w main()
1. Stwórz obiekt `a1(5)`.
2. Stwórz kopię: `SmartArray a2 = a1;`
3. Zmień wartość tylko w oryginale: `a1.m_data[0] = 999;` (możesz tymczasowo upublicznić pola lub dodać metodę `set`).
4. Wypisz `a1[0]` oraz `a2[0]`.
5. Jeśli `a2[0]` nadal wynosi 0, gratulacje! Masz dwa niezależne obszary pamięci.
