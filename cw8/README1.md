# cw8-1 – klasa `CommissionEmployee`

## 📋 Przegląd projektu

Projekt `cw8-1` wprowadza klasyczny przykład programowania obiektowego w C++: klasę `CommissionEmployee`, czyli pracownika wynagradzanego prowizją od sprzedaży.

Program pokazuje, jak:

- zdefiniować własną klasę w pliku nagłówkowym,
- zaimplementować jej metody w osobnym pliku `.cpp`,
- przechowywać dane obiektu w polach prywatnych,
- udostępnić kontrolowany dostęp do danych przez metody publiczne,
- użyć walidacji w setterach,
- obliczyć wynik na podstawie stanu obiektu.

Jest to bardzo ważny krok przejścia od prostych przykładów z pojedynczego pliku do **prawdziwego projektu wieloplikowego**.

---

## 🧱 Struktura projektu

Projekt składa się z trzech plików:

- `CommissionEmployee.h` – deklaracja klasy,
- `CommissionEmployee.cpp` – definicje metod klasy,
- `main.cpp` – program testujący klasę.

Taki podział jest standardowy w C++:

- w `.h` umieszczamy **interfejs** klasy,
- w `.cpp` umieszczamy **implementację**,
- w `main.cpp` tworzymy obiekty i sprawdzamy działanie programu.

---

## 🧩 Co reprezentuje klasa `CommissionEmployee`

Klasa opisuje pracownika, którego wynagrodzenie zależy od wielkości sprzedaży i stawki prowizji.

Obiekt tej klasy przechowuje:

- `firstName` – imię,
- `lastName` – nazwisko,
- `socialSecurityNumber` – numer identyfikacyjny,
- `grossSales` – wartość sprzedaży brutto,
- `commissionRate` – stawkę prowizji.

Wszystkie te dane są umieszczone w sekcji `private`, czyli są ukryte przed bezpośrednim dostępem z zewnątrz.

---

## 🔒 Enkapsulacja i pola prywatne

W klasie:

```cpp
private:
    std::string firstName;
    std::string lastName;
    std::string socialSecurityNumber;
    double grossSales;
    double commissionRate;
```

pola są prywatne, więc kod w `main()` nie może zrobić czegoś takiego:

```cpp
employee.grossSales = 5000;      // niedozwolone
employee.commissionRate = 0.15;  // niedozwolone
```

Zamiast tego trzeba używać metod publicznych, takich jak:

```cpp
employee.setGrossSales(8000);
employee.setCommissionRate(0.1);
```

To jest właśnie **enkapsulacja** – dane są ukryte, a dostęp do nich odbywa się przez kontrolowany interfejs.

---

## 🛠️ Interfejs publiczny klasy

Klasa udostępnia:

### Konstruktor

```cpp
CommissionEmployee( const std::string &, const std::string &,
    const std::string &, double = 0.0, double = 0.0 );
```

Pozwala utworzyć obiekt i od razu przekazać wartości początkowe.

### Settery

- `setFirstName(...)`
- `setLastName(...)`
- `setSocialSecurityNumber(...)`
- `setGrossSales(...)`
- `setCommissionRate(...)`

### Gettery

- `getFirstName()`
- `getLastName()`
- `getSocialSecurityNumber()`
- `getGrossSales()`
- `getCommissionRate()`

### Metody użytkowe

- `earnings()` – oblicza zarobki,
- `print()` – wypisuje pełny stan obiektu.

---

## 🏗️ Konstruktor

Konstruktor klasy ma postać:

```cpp
CommissionEmployee::CommissionEmployee(
    const string &first, const string &last, const string &ssn,
    double sales, double rate )
{
    firstName = first;
    lastName = last;
    socialSecurityNumber = ssn;
    setGrossSales( sales );
    setCommissionRate( rate );
}
```

Widzimy tu ważną rzecz:

- pola tekstowe są przypisywane bezpośrednio,
- pola liczbowe są ustawiane przez settery.

To oznacza, że już podczas tworzenia obiektu działa walidacja dla:

- `grossSales`,
- `commissionRate`.

To bardzo dobra praktyka – obiekt od początku powinien być tworzony w poprawnym stanie.

---

## ✅ Walidacja danych

Najciekawsze metody w tej klasie to:

```cpp
void CommissionEmployee::setGrossSales( double sales )
{
    if ( sales >= 0.0 )
        grossSales = sales;
    else
        throw invalid_argument( "Gross sales must be >= 0.0" );
}
```

oraz:

```cpp
void CommissionEmployee::setCommissionRate( double rate )
{
    if ( rate > 0.0 && rate < 1.0 )
        commissionRate = rate;
    else
        throw invalid_argument( "Commission rate must be > 0.0 and < 1.0" );
}
```

Te funkcje pilnują, żeby:

- sprzedaż nie była ujemna,
- prowizja była większa od 0 i mniejsza od 1.

Jeśli użytkownik poda błędne dane, program zgłosi wyjątek `invalid_argument`.

To pokazuje, że klasa nie tylko przechowuje dane, ale także **dba o ich poprawność**.

---

## 💰 Obliczanie zarobków

Metoda:

```cpp
double CommissionEmployee::earnings() const
{
    return commissionRate * grossSales;
}
```

oblicza wynagrodzenie jako:

**zarobek = prowizja × sprzedaż brutto**

Dla danych z programu:

- `grossSales = 8000`
- `commissionRate = 0.10`

wynik będzie:

```cpp
8000 * 0.10 = 800
```

czyli pracownik zarobi **800.00**.

---

## 🖨️ Metoda `print()`

Metoda:

```cpp
void CommissionEmployee::print() const
{
    cout << "commission employee: " << firstName << ' ' << lastName
         << "\nsocial security number: " << socialSecurityNumber
         << "\ngross sales: " << grossSales
         << "\ncommission rate: " << commissionRate;
}
```

wypisuje pełny stan obiektu w czytelnej formie.

To wygodna metoda diagnostyczna – pozwala szybko sprawdzić, jakie dane są zapisane w obiekcie.

---

## ▶️ Co robi `main.cpp`

Program testowy wykonuje następujące kroki:

### 1. Tworzy obiekt

```cpp
CommissionEmployee employee( "Sue", "Jones", "222-22-2222", 10000, .06 );
```

Powstaje pracownik o imieniu `Sue Jones`, z numerem identyfikacyjnym, sprzedażą `10000` i prowizją `0.06`.

### 2. Ustawia format wyświetlania liczb zmiennoprzecinkowych

```cpp
cout << fixed << setprecision( 2 );
```

Dzięki temu liczby będą wypisane z dwoma miejscami po przecinku.

### 3. Pobiera dane przez gettery

Program wypisuje informacje o pracowniku, korzystając z metod `get...()`.

To pokazuje, jak odczytywać dane z obiektu w sposób bezpieczny.

### 4. Modyfikuje stan obiektu

```cpp
employee.setGrossSales( 8000 );
employee.setCommissionRate( .1 );
```

czyli zmienia:

- sprzedaż z `10000` na `8000`,
- prowizję z `0.06` na `0.10`.

### 5. Wypisuje dane metodą `print()`

Program pokazuje zaktualizowany stan obiektu.

### 6. Oblicza zarobki

```cpp
employee.earnings()
```

Na końcu wypisywany jest wynik obliczenia prowizji.

---

## 🧠 Najważniejsze pojęcia pokazane w projekcie

### 1. Klasa
`CommissionEmployee` jest własnym typem danych definiowanym przez użytkownika.

### 2. Obiekt
`employee` to konkretny egzemplarz klasy `CommissionEmployee`.

### 3. Enkapsulacja
Dane są ukryte jako `private`, a dostęp do nich odbywa się przez metody publiczne.

### 4. Gettery i settery
Pozwalają odczytywać i modyfikować pola bez łamania zasad hermetyzacji.

### 5. Walidacja
Settery sprawdzają poprawność danych i w razie błędu zgłaszają wyjątek.

### 6. Metody `const`
Funkcje takie jak `getFirstName()`, `earnings()` czy `print()` nie zmieniają obiektu.

### 7. Projekt wieloplikowy
Kod został podzielony na nagłówek, implementację i plik testowy.

---

## 📌 Dlaczego ten przykład jest ważny

Ten projekt jest ważny, bo pokazuje pierwszy „pełniejszy” model klasy w C++:

- dane prywatne,
- publiczny interfejs,
- walidację,
- metody obliczeniowe,
- osobne pliki `.h` i `.cpp`.

To już nie jest tylko demonstracja składni, ale mały model dobrze zaprojektowanego obiektu.

---

## ✅ Podsumowanie

Projekt `cw8-1` pokazuje, jak w C++ zbudować klasę reprezentującą rzeczywisty byt – tutaj pracownika prowizyjnego.

Najważniejsze elementy tego przykładu to:

- ukrycie danych w sekcji `private`,
- dostęp do danych przez gettery i settery,
- walidacja liczb w metodach ustawiających,
- obliczanie wynagrodzenia przez metodę `earnings()`,
- organizacja kodu w osobnych plikach.

To bardzo dobry przykład na zrozumienie podstaw programowania obiektowego w C++ i przygotowanie do kolejnych tematów, takich jak dziedziczenie, polimorfizm i kompozycja.
