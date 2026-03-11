# cw2-3.cpp – wprowadzenie do klas i enkapsulacji

Ten krótki program pokazuje kolejny krok ewolucji od prostych struktur w kierunku klas, które są fundamentem paradygmatu obiektowego w C++.

## Co się zmieniło w porównaniu do poprzednich przykładów

1. **`struct` → `class`**
   - Zamiast `struct` używamy `class`. W klasie domyślny poziom dostępu dla członków to **`private`**, a nie `public`, co wymusza świadome deklarowanie specyfikatorów dostępu.

2. **Pola `private` i inicjalizacja**
   - Członkowie danych (`m_year`, `m_month`, `m_day`) znajdują się w sekcji `private`. Są one niedostępne z zewnątrz klasy.
   - Każde pole ma przypisaną wartość domyślną przy deklaracji (`2020`, `14`, `10`). To **inicjalizacja w miejscu deklaracji** (ang. *in-class member initializer*), możliwa w C++11 i nowszych.

3. **Sekcja `public`**
   - Metoda `print()` jest zadeklarowana w sekcji `public`, dzięki czemu można ją wywołać z kodu zewnętrznego (np. z `main`).
   - Metoda jest oznaczona `const`, co informuje, że nie modyfikuje stanu obiektu.

## Co program demonstruje

- **Enkapsulację** – ukrycie danych wewnątrz klasy, aby uniemożliwić ich bezpośrednią modyfikację.
- **Kontrolę dostępu** – tylko publiczne elementy klasy mogą być używane w `main`, prywatne są chronione.
- **Inicjalizatory pól** – możliwość ustawienia początkowych wartości tuż przy ich deklaracji w klasie.
- **Łatwość rozbudowy** – w przyszłości można dodać metody do ustawiania/odczytu daty, walidację, itp., nie zmieniając zewnętrznego API.

## Struktura programu

```cpp
class Date
{
    // Any members defined here would default to private

public: // here's our public access specifier

    void print() const // public due to above public: specifier
    {
        // members can access other private members
        std::cout << m_year << '/' << m_month << '/' << m_day;
    }

private: // here's our private access specifier

    int m_year { 2020 };  // private due to above private: specifier
    int m_month { 14 }; // private due to above private: specifier
    int m_day { 10 };   // private due to above private: specifier
};

int main()
{
    Date d{};
    d.print();  // okay, main() allowed to access public members

    return 0;
}
```

- W `main` tworzymy obiekt `Date d{}` korzystając z domyślnego konstruktora wygenerowanego przez kompilator, który użyje zainicjalizowanych wartości pól.
- Wywołanie `d.print();` jest jedyną dostępną operacją na obiekcie, co ilustruje zasadę "programowanie w interfejsie".

---

### 🔧 Dalsze kierunki
- Dodanie publicznych setterów/getterów z walidacją.
- Zmiana wartości domyślnych na sensowne, np. aktualna data.
- Przemiana klasy w bibliotekę z separacją nagłówka/implementacji.

Ten przykład stanowi solidną bazę do zrozumienia, jak C++ rozwinął się z prostych, płaskich struktur w kierunku potężnego modelu obiektowego.