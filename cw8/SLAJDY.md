# PROGRAMOWANIE OBIEKTOWE W C++
## Część 8: Dziedziczenie i Hermetyzacja

**Prowadzący:** dr Marcin Misiaszek  
Rok akademicki 2025/2026  
*Wydział Fizyki, Astronomii i Informatyki Stosowanej UJ*

---

## 1. Projekt Wieloplikowy (.h / .cpp)

W **Laboratorium 7** widzieliśmy podział na pliki.
W **cw8-1** stosujemy standardowy wzorzec:

* **.h** – Interfejs (deklaracja klasy).
* **.cpp** – Implementacja (definicje metod).
* **main.cpp** – Testowanie obiektów.

---

## 2. Klasa CommissionEmployee

Reprezentuje pracownika prowizyjnego.

* Pola: `firstName`, `lastName`, `grossSales`, `rate`.
* Sekcja **private** chroni dane (**cw2**).
* Dostęp przez publiczne **gettery** i **settery**.

---

## 3. Walidacja w Setterach

Obiekt musi być zawsze w poprawnym stanie.

```cpp
void setGrossSales(double sales) {
    if (sales >= 0.0) 
        grossSales = sales;
    else 
        throw invalid_argument("Sales < 0!");
}
```
*Wyjątki poznaliśmy w **Laboratorium 6**.*

---

## 4. Ewolucja: BasePlusCommissionEmployee

W **cw8-2** dodajemy stałą pensję bazową.

* Nowe pole: `baseSalary`.
* Problem: Dużo powtórzonego kodu z `CommissionEmployee`.
* Rozwiązanie: **Dziedziczenie** (wprowadzone w **cw8-3**).

---

## 5. Dziedziczenie: Relacja "is-a"

Klasa pochodna "jest rodzajem" klasy bazowej.

```cpp
class BasePlusCommissionEmployee 
    : public CommissionEmployee 
{
    // Zawiera wszystko co baza + nowości
};
```

---

## 6. Konstruktor klasy pochodnej

Najpierw musi powstać "baza", potem "nadbudowa".

```cpp
Derived(args...) : Base(args_base) {
    // inicjalizacja pola pochodnego
}
```
*Lista inicjalizacyjna to klucz do wydajności.*

---

## 7. Protected vs Private

W **cw8-3** pola bazy są **protected**.

* **Private:** Tylko dla klasy bazowej.
* **Protected:** Dla bazy i jej dzieci.
* **Public:** Dla każdego.

> 💡 **Ważne:** `protected` ułatwia dostęp, ale osłabia hermetyzację.

---

## 8. Dziedziczenie bez protected (cw8-4)

Podejście profesjonalne: pola bazy są **private**.

* Klasa pochodna korzysta z publicznego interfejsu bazy.
* Przykład: `Base::print();` wewnątrz `Derived::print();`.
* Zmniejsza powiązanie między klasami.

---

## 9. Nadpisywanie metod (Overriding)

Klasa pochodna zmienia zachowanie bazy.

```cpp
double Derived::earnings() const {
    // Zarobek bazy + moja pensja
    return Base::earnings() + baseSalary;
}
```
*Używamy operatora zakresu `::`, by wywołać wersję bazową.*

---

## 10. Specyfikatory Dziedziczenia

| Typ | public bazy | protected bazy | private bazy |
|-----|-------------|----------------|--------------|
| **public** | public | protected | ukryte |
| **protected**| protected | protected | ukryte |
| **private** | private | private | ukryte |

---

## 11. Zadanie Praktyczne 1

1. Przeanalizuj kod **cw8-3** (`protected`).
2. Przeanalizuj kod **cw8-4** (brak `protected`).
3. W **cw8-4** spróbuj zmienić pole bazy w klasie pochodnej.
4. Zaobserwuj błąd kompilacji.

---

## 12. Zadanie Praktyczne 2

1. Stwórz klasę `Pracownik` (baza).
2. Stwórz `Programista` (pochodna).
3. Dodaj metodę `pracuj()` do bazy.
4. Nadpisz `pracuj()` w pochodnej, wywołując wersję bazową.
