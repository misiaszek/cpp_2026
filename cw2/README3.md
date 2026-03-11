# `cw2-3.cpp` – wprowadzenie do klas i enkapsulacji

Ten krótki program pokazuje kolejny krok ewolucji od prostych struktur w kierunku klas, które są fundamentem paradygmatu obiektowego w C++.

## Co się zmieniło w porównaniu do poprzednich przykładów

1. **`struct` → `class`**

   * Zamiast `struct` używamy `class`. W klasie domyślny poziom dostępu dla członków to **`private`**, a nie `public`, co wymusza świadome deklarowanie specyfikatorów dostępu.

2. **Pola `private` i inicjalizacja**

   * Członkowie danych (`m_year`, `m_month`, `m_day`) znajdują się w sekcji `private`. Są one niedostępne z zewnątrz klasy.
   * Każde pole ma przypisaną wartość domyślną przy deklaracji (`2020`, `14`, `10`). To **inicjalizacja w miejscu deklaracji** (ang. *in-class member initializer*), możliwa w C++11 i nowszych.

3. **Sekcja `public`**

   * Metoda `print()` jest zadeklarowana w sekcji `public`, dzięki czemu można ją wywołać z kodu zewnętrznego, na przykład z `main`.
   * Metoda jest oznaczona `const`, co informuje, że nie modyfikuje stanu obiektu.

## Co program demonstruje

* **Enkapsulację** – ukrycie danych wewnątrz klasy, aby uniemożliwić ich bezpośrednią modyfikację.
* **Kontrolę dostępu** – tylko publiczne elementy klasy mogą być używane w `main`, prywatne są chronione.
* **Inicjalizatory pól** – możliwość ustawienia początkowych wartości tuż przy ich deklaracji w klasie.
* **Łatwość rozbudowy** – w przyszłości można dodać metody do ustawiania i odczytu daty, walidację itp., nie zmieniając zewnętrznego interfejsu klasy.

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

* W `main` tworzymy obiekt `Date d{}` korzystając z domyślnej inicjalizacji obiektu. Pola klasy przyjmą wartości zdefiniowane przy ich deklaracji.
* Wywołanie `d.print();` jest możliwe, ponieważ metoda `print()` znajduje się w sekcji `public`.
* Bezpośredni dostęp do `m_year`, `m_month` i `m_day` z funkcji `main` nie byłby dozwolony, ponieważ są to pola prywatne.

## Wynik działania programu

```text
2020/14/10
```

Warto zauważyć, że miesiąc ma tu wartość `14`, czyli nielogiczną z punktu widzenia kalendarza. Jest to uproszczony przykład dydaktyczny pokazujący sam mechanizm enkapsulacji, a nie poprawną reprezentację daty.

## Znaczenie `const` przy metodzie `print`

Metoda została zadeklarowana jako:

```cpp
void print() const
```

Słowo kluczowe `const` oznacza tutaj, że metoda nie może zmieniać stanu obiektu. Dzięki temu kompilator pilnuje, aby `print()` była funkcją tylko odczytującą dane.

To ważny element projektowania klas, ponieważ pozwala jasno odróżnić metody:

* odczytujące stan obiektu,
* modyfikujące stan obiektu.

## Dlaczego to jest ważny krok

Poprzednie przykłady pokazywały struktury z publicznymi polami, które można było dowolnie zmieniać z zewnątrz. Tutaj po raz pierwszy dane zostały ukryte wewnątrz klasy, a użytkownik obiektu otrzymuje dostęp tylko do wybranych operacji.

To jest właśnie jedna z podstaw programowania obiektowego:

* obiekt ukrywa swoją reprezentację wewnętrzną,
* na zewnątrz udostępnia jedynie kontrolowany interfejs.

## Dalsze kierunki rozwoju

Ten przykład można łatwo rozbudować, na przykład o:

* publiczne metody ustawiające datę z walidacją,
* gettery zwracające rok, miesiąc i dzień,
* konstruktor przyjmujący datę jako argument,
* sprawdzanie poprawności zakresów wartości.

Dzięki temu klasa mogłaby stać się bezpieczniejsza i bardziej użyteczna niż prosta struktura z publicznymi polami.

## Podsumowanie

Program `cw2-3.cpp` wprowadza najważniejsze elementy klasy w C++:

* użycie `class` zamiast `struct`,
* rozdzielenie części `public` i `private`,
* ukrycie danych wewnątrz klasy,
* użycie metody `const`,
* pokazanie, że metody klasy mają dostęp do prywatnych pól obiektu.

Jest to pierwszy wyraźny krok od prostego grupowania danych do pełniejszego modelu obiektowego, w którym dane i operacje na nich są celowo organizowane oraz chronione przez interfejs klasy.
