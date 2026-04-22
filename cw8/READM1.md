# cw8-1 – `CommissionEmployee`

Program przedstawia klasę `CommissionEmployee`, która reprezentuje pracownika otrzymującego wynagrodzenie prowizyjne. Projekt został podzielony na trzy pliki: nagłówek z deklaracją klasy, plik implementacyjny z definicjami metod oraz program testowy `main.cpp`. Klasa przechowuje dane pracownika, udostępnia metody dostępowe (`get` / `set`), wykonuje podstawową walidację i potrafi obliczyć zarobek na podstawie sprzedaży i stawki prowizji.

## Struktura projektu

Projekt składa się z trzech plików:

- `CommissionEmployee.h` – deklaracja klasy
- `CommissionEmployee.cpp` – definicje metod klasy
- `main.cpp` – program testujący działanie klasy

Taki podział jest typowy dla C++:
- w pliku `.h` umieszcza się **interfejs** klasy,
- w pliku `.cpp` umieszcza się **implementację**,
- w `main.cpp` tworzy się obiekty i sprawdza ich działanie.

---

## Klasa `CommissionEmployee`

W pliku nagłówkowym klasa zawiera publiczny interfejs oraz prywatne pola danych. Deklarowane są metody ustawiające i odczytujące dane pracownika, metoda licząca zarobek oraz metoda wypisująca obiekt. Klasa przechowuje imię, nazwisko, numer SSN, wartość sprzedaży brutto oraz stawkę prowizji.

Najważniejsze elementy interfejsu:

- konstruktor:
  - przyjmuje imię, nazwisko, numer SSN, sprzedaż brutto i stawkę prowizji,
  - dla dwóch ostatnich parametrów ma wartości domyślne `0.0`,
- settery:
  - `setFirstName`
  - `setLastName`
  - `setSocialSecurityNumber`
  - `setGrossSales`
  - `setCommissionRate`
- gettery:
  - `getFirstName`
  - `getLastName`
  - `getSocialSecurityNumber`
  - `getGrossSales`
  - `getCommissionRate`
- metoda biznesowa:
  - `earnings()` – oblicza wynagrodzenie
- metoda prezentacyjna:
  - `print()` – wypisuje dane pracownika

---

## Pola prywatne i enkapsulacja

Klasa ukrywa swoje dane w sekcji `private`:

- `firstName`
- `lastName`
- `socialSecurityNumber`
- `grossSales`
- `commissionRate`

To oznacza, że kod zewnętrzny nie powinien modyfikować tych pól bezpośrednio. Zamiast tego używa metod klasy. Jest to przykład **enkapsulacji** – obiekt sam kontroluje sposób dostępu do swojego stanu.

Dzięki temu:
- można dodać walidację,
- można zmienić implementację bez zmiany kodu używającego klasy,
- łatwiej utrzymać poprawność danych.

---

## Konstruktor klasy

Konstruktor przyjmuje pięć parametrów:

```cpp
CommissionEmployee(
    const std::string& first,
    const std::string& last,
    const std::string& ssn,
    double sales = 0.0,
    double rate = 0.0
);
