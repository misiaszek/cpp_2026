# cw8-3 – dziedziczenie klas w C++

## 📋 Cel projektu

Projekt pokazuje mechanizm **dziedziczenia publicznego** w C++, czyli tworzenie nowej klasy na podstawie już istniejącej klasy. Dzięki temu można **ponownie wykorzystać gotowy kod**, a jednocześnie rozszerzyć go o nowe pola i metody.

W tym projekcie:

- klasa `CommissionEmployee` opisuje pracownika prowizyjnego,
- klasa `BasePlusCommissionEmployee` dziedziczy po niej i dodaje **stałą pensję podstawową**.

To oznacza, że pracownik z pensją podstawową i prowizją jest bardziej szczegółową wersją zwykłego pracownika prowizyjnego.

---

## 🏗️ Struktura projektu

Projekt składa się z plików:

- `CommissionEmployee.h`
- `CommissionEmployee.cpp`
- `BasePlusCommissionEmployee.h`
- `BasePlusCommissionEmployee.cpp`
- `main.cpp`

### Klasa bazowa `CommissionEmployee`

Klasa bazowa przechowuje dane wspólne dla pracownika prowizyjnego:

- `firstName`
- `lastName`
- `socialSecurityNumber`
- `grossSales`
- `commissionRate`

Udostępnia metody:

- ustawiające dane (`setFirstName`, `setLastName`, `setGrossSales`, itd.),
- odczytujące dane (`getFirstName`, `getGrossSales`, itd.),
- `earnings()` – oblicza zarobek,
- `print()` – wypisuje dane pracownika.

### Klasa pochodna `BasePlusCommissionEmployee`

Klasa pochodna rozszerza klasę bazową o dodatkowe pole:

- `baseSalary`

oraz o dodatkowe metody:

- `setBaseSalary()`
- `getBaseSalary()`

Ponadto redefiniuje sposób liczenia wynagrodzenia i wypisywania danych.

---

## 🔑 Dziedziczenie – najważniejszy element projektu

Najważniejsza linia kodu wygląda tak:

```cpp
class BasePlusCommissionEmployee : public CommissionEmployee
```

Oznacza to, że:

- `BasePlusCommissionEmployee` **dziedziczy publicznie** po `CommissionEmployee`,
- obiekt klasy pochodnej zawiera wszystkie elementy klasy bazowej,
- klasa pochodna może dodawać własne elementy i zmieniać zachowanie wybranych metod.

### Co oznacza `public`?

Dziedziczenie publiczne oznacza, że publiczny interfejs klasy bazowej pozostaje publiczny także w klasie pochodnej. Dzięki temu obiekt klasy pochodnej może korzystać z metod odziedziczonych po klasie bazowej.

---

## 🧱 Konstruktor klasy pochodnej

Konstruktor klasy pochodnej wygląda tak:

```cpp
BasePlusCommissionEmployee::BasePlusCommissionEmployee(
    const string &first, const string &last, const string &ssn,
    double sales, double rate, double salary )
    : CommissionEmployee( first, last, ssn, sales, rate )
{
    setBaseSalary( salary );
}
```

Tutaj dzieją się dwie ważne rzeczy:

### 1. Wywołanie konstruktora klasy bazowej

Na liście inicjalizacyjnej pojawia się:

```cpp
: CommissionEmployee( first, last, ssn, sales, rate )
```

To oznacza, że przed wykonaniem ciała konstruktora klasy pochodnej C++ najpierw tworzy i inicjalizuje **część bazową obiektu**.

### 2. Inicjalizacja nowego pola klasy pochodnej

Po utworzeniu części bazowej wykonywane jest ciało konstruktora i ustawiana jest pensja podstawowa:

```cpp
setBaseSalary( salary );
```

---

## 💰 Nadpisanie metody `earnings()`

W klasie bazowej metoda `earnings()` zwraca:

```cpp
commissionRate * grossSales
```

czyli zarobek zależny wyłącznie od prowizji.

W klasie pochodnej metoda została zmieniona:

```cpp
double BasePlusCommissionEmployee::earnings() const
{
    return baseSalary + ( commissionRate * grossSales );
}
```

Teraz całkowity zarobek to:

- **pensja podstawowa**
- plus **prowizja od sprzedaży**

To bardzo dobry przykład tego, jak klasa pochodna może **zmienić zachowanie odziedziczonej klasy**, dostosowując je do bardziej szczegółowego przypadku.

---

## 🖨️ Nadpisanie metody `print()`

Klasa pochodna ma własną wersję metody `print()`:

```cpp
void BasePlusCommissionEmployee::print() const
{
    cout << "base-salaried commission employee: " << firstName << ' '
         << lastName << "\nsocial security number: " << socialSecurityNumber
         << "\ngross sales: " << grossSales
         << "\ncommission rate: " << commissionRate
         << "\nbase salary: " << baseSalary;
}
```

Ta metoda wypisuje:

- dane odziedziczone z klasy bazowej,
- oraz nowe pole `baseSalary`.

Widać więc, że klasa pochodna nie tylko przejmuje dane klasy bazowej, ale także **rozszerza sposób ich prezentacji**.

---

## ⚠️ `protected` i dostęp do pól klasy bazowej

W tym projekcie pola klasy `CommissionEmployee` są oznaczone jako `protected`, a nie `private`.

To oznacza, że klasa pochodna może odwoływać się do nich bezpośrednio, np.:

```cpp
firstName
grossSales
commissionRate
```

### Zaleta

- łatwo pokazać mechanizm dziedziczenia,
- klasa pochodna ma bezpośredni dostęp do odziedziczonych danych.

### Wada

- osłabia to enkapsulację,
- zwiększa powiązanie między klasą bazową i pochodną,
- utrudnia późniejsze zmiany wewnętrznej implementacji klasy bazowej.

W praktyce produkcyjnej często lepiej pozostawić pola jako `private` i korzystać z getterów/setterów.

---

## 🔁 Powtarzanie kodu

W projekcie widać też **powtarzanie się kodu**, szczególnie w metodzie `print()` klasy pochodnej.

Klasa `BasePlusCommissionEmployee` wypisuje od nowa dane, które klasa bazowa już zna:

- imię,
- nazwisko,
- numer,
- sprzedaż,
- prowizję.

To oznacza, że jeśli zmienimy sposób wypisywania w klasie bazowej, trzeba będzie poprawić kod również w klasie pochodnej.

To ważna obserwacja: **dziedziczenie pomaga w ponownym użyciu kodu, ale nie usuwa automatycznie każdej duplikacji**. Kod nadal trzeba dobrze zaprojektować.

---

## ▶️ Działanie programu `main.cpp`

W `main.cpp` tworzony jest obiekt klasy pochodnej:

```cpp
BasePlusCommissionEmployee employee(
    "Bob", "Lewis", "333-33-3333", 5000, .04, 300 );
```

Następnie program:

1. odczytuje dane pracownika,
2. zmienia pensję podstawową,
3. wypisuje dane,
4. oblicza wynagrodzenie.

Po ustawieniu:

```cpp
employee.setBaseSalary(1000);
```

wynagrodzenie wynosi:

- prowizja: `5000 * 0.04 = 200`
- pensja podstawowa: `1000`

czyli razem:

```cpp
1200
```

---

## 🧠 Czego uczy ten projekt

Projekt `cw8-3` pokazuje w praktyce:

- jak działa **dziedziczenie publiczne**,
- jak klasa pochodna korzysta z elementów klasy bazowej,
- jak wywołać konstruktor klasy bazowej,
- jak dodać nowe pole do klasy pochodnej,
- jak zmienić zachowanie odziedziczonej klasy przez redefinicję metod,
- jakie konsekwencje ma użycie `protected`,
- że przy rozbudowie klas może pojawić się **powtarzanie kodu**.

---

## 📌 Podsumowanie

`cw8-3` to klasyczny przykład dziedziczenia w C++.

Klasa `BasePlusCommissionEmployee`:

- przejmuje dane i funkcjonalność klasy `CommissionEmployee`,
- dodaje własne pole `baseSalary`,
- rozszerza sposób liczenia zarobków,
- redefiniuje metodę `print()`.

Projekt dobrze pokazuje ideę:
**klasa pochodna buduje się na klasie bazowej**, korzysta z już istniejącego kodu, ale może go rozszerzać i dostosowywać do bardziej szczegółowego zastosowania.
