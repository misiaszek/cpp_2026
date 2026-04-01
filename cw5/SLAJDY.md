# PROGRAMOWANIE OBIEKTOWE W C++
## Część 5: Operatory i Kontenery STL

**Prowadzący:** dr Marcin Misiaszek  
Rok akademicki 2025/2026  
*Wydział Fizyki, Astronomii i Informatyki Stosowanej UJ*

---

## 1. Naturalne wypisywanie obiektów

W **Laboratorium 1** poznaliśmy `std::cout` i operator `<<`.
Teraz nauczymy nasze klasy "gadać" ze strumieniami.

* Cel: Pisanie `std::cout << ułamek;` zamiast `ułamek.print();`.
* Obiekt zachowuje się jak wbudowany `int` czy `double`.
* Wymaga przeciążenia operatora jako funkcji zewnętrznej.

---

## 2. Przeciążanie operatora << (Kod)

Używamy mechanizmu `friend` (poznanego w **cw3**).

```cpp
class Fraction {
    int num, den;
public:
    Fraction(int n=0, int d=1) : num(n), den(d) {}
    friend std::ostream& operator<<(std::ostream& os, const Fraction& f);
};
```

---

## 3. Implementacja operatora <<

Zwracamy referencję do strumienia, by móc go "łączyć".

```cpp
std::ostream& operator<<(std::ostream& os, const Fraction& f) {
    os << f.num << "/" << f.den;
    return os; 
}

// Użycie:
std::cout << f1 << " i " << f2 << std::endl;
```

---

## 4. std::array vs std::vector

| Cecha | std::array | std::vector |
|-------|------------|-------------|
| **Rozmiar** | Stały (compile-time) | Dynamiczny (runtime) |
| **Alokacja** | Stos (stack) | Sterta (heap) |
| **Metody** | `size()`, `at()`, `[]` | `push_back()`, `size()` |

---

## 5. Przypomnienie o Kontenerach

* `std::array` (**cw4**): Bezpieczniejsza tablica C.
* `std::vector` (**cw1**): "Inteligentna" tablica, która rośnie.
* Oba oferują metodę `at()` dla bezpiecznego dostępu.

---

## 6. Algorytmy standardowe (<algorithm>)

STL to gotowe przepisy na dane. Współpracują przez **iteratory**.

* `std::sort` - układa elementy w porządku.
* `std::binary_search` - błyskawiczne szukanie.
* **UWAGA:** Szukanie binarne wymaga posortowanych danych!

---

## 7. Przykład: Sortowanie i Szukanie

```cpp
std::array data = {"red", "blue", "green"};

std::sort(data.begin(), data.end());

bool found = std::binary_search(data.begin(), data.end(), "blue");
```

---

## 8. Potęga Iteratorów: begin() i end()

Iteratory to "wskaźniki" na sterydach.

* `begin()` - wskazuje na **pierwszy** element.
* `end()` - wskazuje na pozycję **ZA ostatnim** elementem.
* `auto` (**cw4**) idealnie pasuje do typów iteratorów.

---

## 9. Przechodzenie po kontenerze

```cpp
std::vector<int> v = {1, 2, 3};

for (auto it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << " "; 
}
```
*Dereferencja (`*it`) daje dostęp do wartości.*

---

## 10. std::set – Zbiór unikalny

* **Unikalność:** Brak duplikatów.
* **Sortowanie:** Elementy są zawsze ułożone rosnąco.

```cpp
std::set<int> s;
s.insert(5); s.insert(1); s.insert(1);

for(int x : s) std::cout << x << " "; // 1 5
```

---

## 11. Tablice wielowymiarowe

W nowoczesnym C++ używamy zagnieżdżonych `std::array`.

```cpp
// Macierz 2 wiersze x 3 kolumny
std::array<std::array<int, 3>, 2> matrix = {{
    {1, 2, 3}, {4, 5, 6}
}};
```

---

## 12. Dostęp do macierzy

Używamy zagnieżdżonych pętli zakresowych.

```cpp
for (const auto& row : matrix) {
    for (int val : row) std::cout << val << " ";
    std::cout << std::endl;
}
```

---

## 13. Kopiowanie wektorów

`std::vector` automatycznie zarządza pamięcią (RAII - **cw3**).
Kopiowanie `=` wykonuje **głęboką kopię** (deep copy).

```cpp
std::vector<int> v1 = {1, 2, 3};
std::vector<int> v2 = v1; // Nowa pamięć, te same dane
```

---

## 14. Bezpieczeństwo: at() vs []

* `v[i]` - Szybki, ale **nie sprawdza** zakresu (możliwy crash).
* `v.at(i)` - Sprawdza zakres. Jeśli błąd -> **wyjątek**.
* Używaj `at()`, gdy nie masz pewności co do indeksu.

---

## 15. Obsługa błędów: Wyjątki

Gdy `at()` zawiedzie, używamy bloku `try-catch`.

```cpp
try {
    std::cout << v.at(100); 
} 
catch (const std::out_of_range& e) {
    std::cerr << "Błąd: " << e.what();
}
```

---

## 16. Zadanie Praktyczne 1

1. Stwórz `std::vector<int>` z duplikatami.
2. Posortuj go (`std::sort`).
3. Przepisz do `std::set<int>`.
4. Wyświetl oba kontenery i porównaj.

---

## 17. Zadanie Praktyczne 2

1. Użyj klasy `Fraction`.
2. Stwórz `std::vector<Fraction>` z 3 elementami.
3. Wypisz je pętlą zakresową.
4. Wywołaj `v.at(5)` w bloku `try-catch`.
