# cw2-1.cpp - Opis programu

## 📋 Przegląd ogólny

Program demonstruje **podstawowe użycie struktur w C++** (`struct`). Struktura `Date` reprezentuje datę i pokazuje, jak definiować dane i z nich korzystać w prosty sposób.

---

## 🏗️ Struktura programu

### 1. **Definicja struktury `Date` (linie 3-9)**

```cpp
struct Date
{
    int year {};
    int month {};
    int day {};
};
```

Struktura zawiera **trzy zmienne członkowskie** (member variables):
- `year` - rok
- `month` - miesiąc
- `day` - dzień

Inicjalizacja `{}` ustawia wartości na **0** (inicjalizacja domyślna).

### 2. **Funkcja `print()` (linie 11-15)**

```cpp
void print(const Date& date)
{
    std::cout << date.year << '/' << date.month << '/' << date.day;
}
```

- Przyjmuje referencję do struktury `Date` (parametr `const Date&`)
- Używa **operatora dostępu do składowych** (`.`) aby odczytać wartości
- Wyświetla datę w formacie: `rok/miesiąc/dzień`

### 3. **Funkcja `main()` (linie 17-25)**

```cpp
Date today { 2020, 10, 14 }; // inicjalizacja aggregate
today.day = 16;               // modyfikacja pola
print(today);                 // wywołanie funkcji
```

- **Inicjalizacja aggregate**: `{ 2020, 10, 14 }` przypisuje wartości do kolejnych pól
- **Modyfikacja pola**: `today.day = 16` zmienia dzień na 16
- **Wynik**: `2020/10/16`

---

## ⚠️ **Ważne: Różnice między `struct` a `class`** (Enkapsulacja i kierowanie dostępem)

Ten program pokazuje **przełomowy punkt** - jak przechodzić od struktur do klas:

### **Struktury (`struct`) - BEZ enkapsulacji:**
```cpp
struct Date {
    int year {};    // ✅ Dostęp PUBLICZNY (domyślnie)
    int month {};   // ✅ Każdy może czytać i modyfikować
    int day {};
};

// Anywhere in code:
today.year = -100;   // ❌ Można przypisać nielogiczną wartość!
today.month = 13;    // ❌ Brak walidacji!
```

### **Klasy (`class`) - Z enkapsulacją:**
```cpp
class Date {
private:              // 🔒 Dostęp PRYWATNY (domyślnie)
    int year {};
    int month {};
    int day {};

public:               // ✅ Kontrolowany dostęp
    void setDay(int d) {
        if (d >= 1 && d <= 31)  // Walidacja!
            day = d;
    }
    
    int getDay() const {
        return day;
    }
};

// Anywhere in code:
today.day = 50;       // ❌ BŁĄD KOMPILACJI - brak dostępu!
today.setDay(50);     // ❌ Odrzucone (walidacja)
today.setDay(16);     // ✅ OK
```

---

## 🎯 Kluczowe koncepty

| Koncepcja | Opis |
|-----------|------|
| **Struktura** | Prosty container dla danych, brak ochrony |
| **Enkapsulacja** | Ukrywanie szczegółów implementacji |
| **Kierowanie dostępem** | `private`, `public`, `protected` - kontrola kto może coś zmienić |
| **Operator `.`** | Dostęp do składowych struktury/obiektu |
| **Validacja** | Metody publiczne mogą sprawdzać poprawność danych |

---

## `cw2-2.cpp` – metoda członkowska

W drugim przykładzie struktura `Date` została wzbogacona o funkcję `print` zdefiniowaną **wewnątrz** samej struktury:

```cpp
struct Date
{
    int year {};
    int month {};
    int day {};

    void print() // metoda członkowska
    {
        std::cout << year << '/' << month << '/' << day;
    }
};
```

W `main` wywołujemy teraz `today.print();` zamiast korzystać z zewnętrznej funkcji. To pokazuje:

- ✅ W C++ można dodawać **metody** bezpośrednio do `struct`a – funkcja staje się częścią typu.
- ✅ Metody mają dostęp do pól obiektu bez potrzeby przesyłania ich jako argumentów.
- 🚫 W C takiej możliwości nie ma; należałoby użyć oddzielnej funkcji przyjmującej wskaźnik/referencję do struktury.

Sekcja ta uzupełnia wcześniejsze omówienie i demonstruje, jak w C++ można stopniowo przechodzić od prostych struktur do typów z własnym zachowaniem.

## 💡 Podsumowanie

Program `cw2-1.cpp` to **etap przejściowy**:
- ✅ Pokazuje jak pracować ze strukturami
- ⚠️ Brak ochrony przed niepoprawnych wartościami
- 🔜 Przygotowuje do nauki **klas**, gdzie można dodać walidację i kontrolować dostęp

W klasach możemy mieć **prywatne dane** (niedostępne z zewnątrz) i **publiczne metody** (kontrolujące dostęp do danych) 🔐