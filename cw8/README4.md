# cw8-4 – dziedziczenie bez `protected`

## 📋 Przegląd programu

Projekt `cw8-4` pokazuje **dziedziczenie publiczne** w C++ na przykładzie dwóch klas:

- `CommissionEmployee` – pracownik wynagradzany prowizją od sprzedaży,
- `BasePlusCommissionEmployee` – pracownik prowizyjny, który oprócz prowizji ma także **stałą pensję podstawową**.

W porównaniu do wcześniejszych wersji tutaj szczególnie ważne jest to, że klasa pochodna **nie korzysta z pól `protected`** odziedziczonych z klasy bazowej. Zamiast tego działa przez:

- **wywołanie konstruktora klasy bazowej**,
- **używanie publicznych metod klasy bazowej**,
- **rozszerzenie zachowania o własne pole i własne metody**.

To jest podejście bardziej zgodne z ideą **enkapsulacji**: klasa bazowa sama pilnuje swoich danych, a klasa pochodna korzysta z jej publicznego interfejsu.

---

## 🧱 Struktura projektu

Projekt składa się z kilku plików:

- `CommissionEmployee.h` – deklaracja klasy bazowej,
- `CommissionEmployee.cpp` – definicje metod klasy bazowej,
- `BasePlusCommissionEmployee.h` – deklaracja klasy pochodnej,
- `BasePlusCommissionEmployee.cpp` – definicje metod klasy pochodnej,
- `main.cpp` – program testujący klasy.

Taki podział jest typowy dla programów obiektowych w C++:

- w plikach nagłówkowych (`.h`) umieszczamy **deklaracje klas**,
- w plikach źródłowych (`.cpp`) umieszczamy **implementację metod**,
- w `main.cpp` testujemy gotowe klasy.

---

## 🧩 Klasa bazowa `CommissionEmployee`

Klasa `CommissionEmployee` przechowuje dane pracownika prowizyjnego:

- imię,
- nazwisko,
- numer identyfikacyjny,
- wartość sprzedaży,
- stawkę prowizji.

Udostępnia publiczne metody:

- settery i gettery,
- `earnings()` – obliczanie zarobku,
- `print()` – wypisanie danych obiektu.

Najważniejsze jest to, że **pola tej klasy są prywatne (`private`)**, więc nie można ich bezpośrednio używać poza klasą.

To oznacza, że nawet klasa pochodna nie robi czegoś takiego:

```cpp
firstName = "Bob";      // niedozwolone, gdy pole jest private
commissionRate = 0.04;   // niedozwolone
```

Zamiast tego musi korzystać z interfejsu publicznego albo konstruktora klasy bazowej.

---

## 🧬 Klasa pochodna `BasePlusCommissionEmployee`

Deklaracja klasy wygląda tak:

```cpp
class BasePlusCommissionEmployee : public CommissionEmployee
```

Słowo `public` oznacza tutaj **dziedziczenie publiczne**.

Dzięki temu:

- publiczne elementy klasy bazowej pozostają publiczne w klasie pochodnej,
- można traktować klasę pochodną jako rozszerzoną wersję klasy bazowej,
- obiekt `BasePlusCommissionEmployee` **jest rodzajem** `CommissionEmployee`.

Klasa pochodna dodaje jedno nowe pole:

```cpp
double baseSalary;
```

oraz własne metody:

- `setBaseSalary(double)`
- `getBaseSalary() const`
- `earnings() const`
- `print() const`

Czyli klasa pochodna:

- **dziedziczy** cechy pracownika prowizyjnego,
- **dodaje** pensję podstawową,
- **nadpisuje** sposób liczenia zarobków i prezentowania danych.

---

## 🔧 Konstruktor klasy pochodnej

Najważniejszy fragment implementacji:

```cpp
BasePlusCommissionEmployee::BasePlusCommissionEmployee(
    const string &first, const string &last, const string &ssn,
    double sales, double rate, double salary )
    : CommissionEmployee( first, last, ssn, sales, rate )
{
    setBaseSalary( salary );
}
```

Tutaj dzieją się dwie bardzo ważne rzeczy.

### 1. Wywołanie konstruktora klasy bazowej

```cpp
: CommissionEmployee( first, last, ssn, sales, rate )
```

To oznacza, że część bazowa obiektu jest tworzona przez konstruktor klasy `CommissionEmployee`.

Najpierw powstaje część bazowa, a dopiero potem część pochodna.

### 2. Inicjalizacja własnych danych klasy pochodnej

Po utworzeniu części bazowej konstruktor ustawia pensję podstawową:

```cpp
setBaseSalary( salary );
```

Czyli klasa pochodna odpowiada tylko za swoje dodatkowe pole, a dane odziedziczone pozostają pod kontrolą klasy bazowej.

---

## 🚫 Dlaczego tutaj nie ma `protected`

To jest najważniejsza różnica merytoryczna tego przykładu.

Gdyby pola klasy bazowej były `protected`, klasa pochodna mogłaby odwoływać się do nich bezpośrednio, np.:

```cpp
firstName = first;
grossSales = sales;
```

W tym projekcie tak **nie jest**. Pola klasy bazowej są ukryte jako `private`, więc klasa pochodna:

- nie ma do nich bezpośredniego dostępu,
- nie może ich samodzielnie zmieniać poza interfejsem klasy bazowej,
- musi korzystać z konstruktora i metod publicznych.

To rozwiązanie ma zalety:

- zwiększa bezpieczeństwo kodu,
- lepiej chroni spójność danych,
- zmniejsza zależność klasy pochodnej od szczegółów implementacji klasy bazowej,
- ułatwia późniejsze zmiany w klasie bazowej.

Krótko mówiąc: **klasa pochodna rozszerza zachowanie, ale nie „grzebie” bezpośrednio w prywatnych danych klasy bazowej**.

---

## 💰 Nadpisanie metody `earnings()`

W klasie pochodnej metoda `earnings()` wygląda tak:

```cpp
double BasePlusCommissionEmployee::earnings() const
{
    return getBaseSalary() + CommissionEmployee::earnings();
}
```

To bardzo dobry przykład ponownego użycia kodu.

Zamiast jeszcze raz liczyć prowizję ręcznie, klasa pochodna korzysta z gotowej metody klasy bazowej:

```cpp
CommissionEmployee::earnings()
```

A następnie dodaje do niej pensję podstawową:

```cpp
getBaseSalary()
```

Dzięki temu:

- kod jest krótszy,
- nie powiela logiki klasy bazowej,
- łatwiej go utrzymać i poprawiać.

---

## 🖨️ Nadpisanie metody `print()`

Metoda `print()` w klasie pochodnej:

```cpp
void BasePlusCommissionEmployee::print() const
{
    cout << "base-salaried ";
    CommissionEmployee::print();
    cout << "\n base salary: " << getBaseSalary();
}
```

Najpierw wypisywany jest tekst:

```cpp
"base-salaried "
```

Potem wywoływana jest metoda klasy bazowej:

```cpp
CommissionEmployee::print();
```

Na końcu dopisywana jest pensja podstawowa.

To znów pokazuje bardzo dobrą praktykę:

- używamy istniejącej funkcjonalności klasy bazowej,
- tylko **rozszerzamy** jej wynik o nowe informacje.

---

## ▶️ Co robi `main.cpp`

Program testowy tworzy obiekt:

```cpp
BasePlusCommissionEmployee employee(
    "Bob", "Lewis", "333-33-3333", 5000, .04, 300 );
```

Następnie:

1. wypisuje dane przez gettery,
2. zmienia pensję podstawową na `1000`,
3. wywołuje `print()`,
4. wypisuje wynik `earnings()`.

To pokazuje, że obiekt klasy pochodnej:

- ma dostęp do metod odziedziczonych z klasy bazowej,
- ma własne dodatkowe metody,
- może nadpisywać zachowanie klasy bazowej.

---

## 🔍 Dziedziczenie `public`, `protected`, `private`

Poniższa tabela pokazuje, co dzieje się z elementami klasy bazowej po odziedziczeniu:

| Sposób dziedziczenia | `public` z bazy staje się | `protected` z bazy staje się | `private` z bazy staje się | Typowe znaczenie |
|---|---|---|---|---|
| `public` | `public` | `protected` | nadal niedostępne bezpośrednio | relacja **is-a** („jest rodzajem”) |
| `protected` | `protected` | `protected` | nadal niedostępne bezpośrednio | rzadziej używane, bardziej techniczne dziedziczenie |
| `private` | `private` | `private` | nadal niedostępne bezpośrednio | implementacyjne użycie bazy, bez publicznej relacji „is-a” |

### Najważniejsze wnioski

- **`private` składniki klasy bazowej nigdy nie stają się bezpośrednio dostępne w klasie pochodnej**.
- Sposób dziedziczenia wpływa tylko na to, jak traktowane są elementy `public` i `protected` klasy bazowej.
- W praktyce najczęściej używa się **dziedziczenia publicznego**.

W tym projekcie użyto właśnie:

```cpp
class BasePlusCommissionEmployee : public CommissionEmployee
```

co oznacza klasyczne dziedziczenie typu **„BasePlusCommissionEmployee jest rodzajem CommissionEmployee”**.

---

## 🧠 Najważniejsze pojęcia pokazane w projekcie

### 1. Dziedziczenie
Nowa klasa może przejąć dane i metody istniejącej klasy.

### 2. Klasa bazowa i pochodna
- `CommissionEmployee` – baza,
- `BasePlusCommissionEmployee` – klasa pochodna.

### 3. Rozszerzanie klasy
Klasa pochodna dodaje nowe pole `baseSalary` i nowe zachowanie.

### 4. Enkapsulacja
Dane klasy bazowej są ukryte jako `private`, więc klasa pochodna nie psuje ich bezpośrednio.

### 5. Ponowne użycie kodu
Metody klasy pochodnej korzystają z metod klasy bazowej zamiast powielać logikę.

### 6. Jawne odwołanie do klasy bazowej
Zapisy takie jak:

```cpp
CommissionEmployee::earnings()
CommissionEmployee::print()
```

pozwalają wywołać wersję zdefiniowaną w klasie bazowej.

---

## ✅ Podsumowanie

Projekt `cw8-4` pokazuje dojrzałe użycie dziedziczenia w C++.

Najważniejsza idea tego przykładu jest taka:

- klasa pochodna **dziedziczy publicznie** po klasie bazowej,
- **dodaje własne pole** i własne metody,
- **nadpisuje** część zachowań,
- ale **nie korzysta z `protected`**, tylko z interfejsu publicznego klasy bazowej.

To podejście jest zwykle lepsze projektowo niż bezpośredni dostęp do odziedziczonych pól, bo zachowuje enkapsulację i zmniejsza sprzężenie między klasami.

Jeśli poprzednie przykłady pokazywały samo dziedziczenie, to `cw8-4` pokazuje, jak robić to **czyściej i bezpieczniej**.
