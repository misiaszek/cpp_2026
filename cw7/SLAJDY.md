# PROGRAMOWANIE OBIEKTOWE W C++
## Część 7: Destruktory, Cykl życia i Obiekty stałe

**Prowadzący:** dr Marcin Misiaszek  
Rok akademicki 2025/2026  
*Wydział Fizyki, Astronomii i Informatyki Stosowanej UJ*

---

## 1. Destruktor: Sprzątanie po obiekcie

W **Laboratorium 3** poznaliśmy konstruktory. Destruktor to ich przeciwieństwo.

* Nazwa: `~NazwaKlasy()` (z tyldą).
* Wywoływany **automatycznie**, gdy obiekt ginie.
* Brak argumentów i typu zwracanego.
* Służy do zwalniania zasobów (RAII).

---

## 2. Przykład Destruktora (Kod)

```cpp
class Simple {
    int m_id;
public:
    Simple(int id) : m_id{id} {
        std::cout << "Tworzę " << m_id << "\n";
    }
    ~Simple() {
        std::cout << "Niszczę " << m_id << "\n";
    }
};
```

---

## 3. Czas życia na stosie (Stack)

Obiekty lokalne żyją tylko wewnątrz klamerek `{ }`.

```cpp
{
    Simple s1{1};
    {
        Simple s2{2};
    } // s2 ginie TUTAJ
} // s1 ginie TUTAJ
```

*Zasada: Obiekty niszczone są w odwrotnej kolejności do tworzenia.*

---

## 4. Rodzaje obiektów a cykl życia

W **cw7-2** widzimy różne typy obiektów:

* **Globalne:** Tworzone przed `main()`, giną na końcu.
* **Statyczne (`static`):** Żyją do końca programu.
* **Automatyczne:** Żyją do końca bloku `{ }`.
* **Dynamiczne (`new`):** Żyją do momentu `delete`.

---

## 5. Porównanie czasów życia

| Typ | Powstaje | Ginie |
|-----|----------|-------|
| Globalny | Przed `main()` | Koniec programu |
| Lokalny | W miejscu deklaracji | Koniec bloku `{ }` |
| Statyczny | Pierwsze użycie | Koniec programu |
| Dynamiczny | W chwili `new` | W chwili `delete` |

---

## 6. Obiekty stałe (const)

Słowo `const` (poznane w **cw2**) chroni obiekt przed zmianą.

* Obiekt stały może wywoływać **tylko** metody `const`.
* Metoda `const` obiecuje, że nie zmieni stanu obiektu.

```cpp
const Time noon(12, 0, 0);
noon.printUniversal(); // OK, jeśli metoda jest const
noon.setHour(13);      // BŁĄD KOMPILACJI
```

---

## 7. Funkcje składowe const

Metodę oznaczamy jako `const` po nawiasach parametrów.

```cpp
class Time {
    int hour;
public:
    // Ta metoda tylko ODCZYTUJE (bezpieczna)
    int getHour() const { return hour; }

    // Ta metoda ZMIENIA (brak const)
    void setHour(int h) { hour = h; }
};
```

---

## 8. Pułapka braku const

Jeśli metoda tylko wypisuje dane, ale nie ma dopisku `const`, kompilator nie pozwoli jej wywołać dla obiektu `const`.

```cpp
void print() { std::cout << hour; } // Brak const!

const Time t(10);
t.print(); // BŁĄD, mimo że print nic nie zmienia!
```

*Wniosek: Zawsze dodawaj `const` do metod odczytujących.*

---

## 9. Wskaźnik "this"

W każdej metodzie (nie-statycznej) istnieje ukryty wskaźnik `this`.

* Wskazuje na bieżący obiekt.
* Pozwala odróżnić pola klasy od parametrów.

```cpp
void setX(int x) {
    this->x = x; // this->x to pole, x to parametr
}
```

---

## 10. Trzy sposoby na to samo

Wewnątrz metody te zapisy są równoważne:

1. `x` (niejawne użycie `this`)
2. `this->x` (jawne użycie wskaźnika)
3. `(*this).x` (dereferencja wskaźnika)

*Wszystkie odnoszą się do pola `x` bieżącego obiektu.*

---

## 11. Zadanie Praktyczne 1

> 💡 **Zadanie:** Czas życia.

1. Użyj klasy `Simple` z destruktorem.
2. Stwórz obiekt globalny, statyczny i lokalny.
3. Zaobserwuj kolejność komunikatów w konsoli.
4. Czy kolejność niszczenia zgadza się z teorią?

---

## 12. Zadanie Praktyczne 2

> 💡 **Zadanie:** Kontrola stałości.

1. Do klasy `Simple` dodaj metodę `print()` (bez `const`).
2. Stwórz `const Simple s(1);`.
3. Spróbuj wywołać `s.print()`.
4. Napraw kod, dodając `const` do deklaracji metody.
