# cw8-3 – dziedziczenie klas w C++

## 📋 Cel projektu

Projekt pokazuje **dziedziczenie publiczne** w C++, czyli sytuację, w której nowa klasa powstaje na bazie już istniejącej klasy i **rozszerza jej funkcjonalność**.

W tym przykładzie:

- klasa bazowa `CommissionEmployee` opisuje pracownika otrzymującego wyłącznie prowizję,
- klasa pochodna `BasePlusCommissionEmployee` dodaje do tego **stałą pensję podstawową**.

To klasyczny przykład relacji:

**„BasePlusCommissionEmployee jest rodzajem CommissionEmployee”**

czyli:
pracownik z pensją podstawową i prowizją **jest szczególnym przypadkiem** pracownika prowizyjnego.

Projekt składa się z kilku plików źródłowych i pokazuje nie tylko samo dziedziczenie, ale także:

- wywoływanie konstruktora klasy bazowej,
- rozszerzanie interfejsu klasy,
- nadpisywanie metod,
- ponowne użycie kodu,
- a także pewne problemy projektowe wynikające z użycia `protected`.

---

## 🏗️ Struktura projektu

Projekt zawiera pliki:

- `CommissionEmployee.h`
- `CommissionEmployee.cpp`
- `BasePlusCommissionEmployee.h`
- `BasePlusCommissionEmployee.cpp`
- `main.cpp`

### 1. `CommissionEmployee` – klasa bazowa

Klasa `CommissionEmployee` przechowuje dane typowego pracownika prowizyjnego:

- imię,
- nazwisko,
- numer PESEL / SSN,
- wartość sprzedaży,
- stawkę prowizji.

Udostępnia metody:

- ustawiające dane (`set...`)
- odczytujące dane (`get...`)
- `earnings()` – oblicza zarobek jako:

```cpp
commissionRate * grossSales
