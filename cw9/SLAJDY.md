# PROGRAMOWANIE OBIEKTOWE W C++
## Część 9: Metody Wirtualne i Polimorfizm

**Prowadzący:** dr Marcin Misiaszek  
Rok akademicki 2025/2026  
*Wydział Fizyki, Astronomii i Informatyki Stosowanej UJ*

---

## 1. Problem: Wiązanie Statyczne

Domyślnie C++ wybiera metodę na podstawie typu wskaźnika.
W przykładzie **cw9-1.cpp** widzimy:

```cpp
Bazowa* ptr = &pochodna;
ptr->metoda(); // Wywoła BAZOWĄ (Early Binding)
```
* Kompilator decyduje w czasie kompilacji.
* Nie sprawdza zawartości pamięci pod wskaźnikiem.

---

## 2. Rozwiązanie: Metody Wirtualne

Słowo **`virtual`** włącza wiązanie dynamiczne (Late Binding).

* Decyzja o wyborze metody zapada w trakcie działania programu.
* C++ sprawdza rzeczywisty typ obiektu pod wskaźnikiem.

```cpp
virtual void sound(); // W klasie Animal (cw9-2.cpp)
```
* Dzięki temu `ptr->sound()` wywoła wersję klasy pochodnej.

---

## 3. Override: Strażnik Poprawności

Słowo **`override`** (**cw9-2**) informuje o intencjach.

* Sprawdza, czy sygnatura bazy i pochodnej pasują.
* Chroni przed błędami (np. literówką w nazwie).

```cpp
void sound() override; // Błąd, jeśli baza nie ma sound()
```

---

## 4. Pod Maską: vtable i vptr

Jak C++ wybiera właściwą funkcję?

* **vtable:** Tabela adresów funkcji dla każdej klasy polimorficznej.
* **vptr:** Ukryty wskaźnik w każdym obiekcie.
* Wywołanie to skok: `vptr -> vtable -> kod`.

> 💡 **Wydajność:** To bardzo szybki mechanizm O(1).

---

## 5. Istota Polimorfizmu (cw9-3.cpp)

Pozwala traktować różne klasy przez wspólny interfejs.

* Wspólny kontener: `std::vector<Base*> vm;`.
* Każdy obiekt (Base lub Derived) zachowuje się po swojemu.
* System staje się otwarty na nowe rodzaje obiektów.

---

## 6. Run-Time Type Information (RTTI)

Czasem musimy wiedzieć, z jakim obiektem pracujemy.

* **dynamic_cast:** Bezpieczne rzutowanie w dół hierarchii.
* Zwraca `nullptr`, jeśli typ się nie zgadza.
* Pozwala na bezpieczne wywołanie metod specyficznych dla dziecka.

---

## 7. RTTI: Operator typeid

Zwraca informacje o typie obiektu w runtime.

```cpp
#include <typeinfo>
if (typeid(*ptr) == typeid(Pochodna)) {
    std::cout << "To jest Pochodna!";
}
```
* Użyteczne w diagnostyce i systemach logowania.

---

## 8. Złota Zasada: Destruktor Wirtualny

Każda klasa bazowa z `virtual` **musi** mieć:

```cpp
virtual ~Base() = default;
```
* Bez tego `delete ptr_bazowy` nie usunie części pochodnej.
* Skutek: wycieki pamięci i błędy RAII (**cw3, cw7**).

---

## 9. Zadanie Praktyczne 1

1. Przeanalizuj **cw9-1** (brak `virtual`).
2. Dodaj `virtual` do bazy i `override` do klasy pochodnej.
3. Sprawdź, jak zmieniły się komunikaty w `main`.
4. Spróbuj użyć `dynamic_cast`, aby odróżnić obiekty w pętli.

---

## 10. Zadanie Praktyczne 2

1. Zbuduj hierarchię: `Pojazd` -> `Samochod`, `Rower`.
2. Dodaj metodę wirtualną `trab()`.
3. Stwórz wektor wskaźników do obu typów pojazdów.
4. Wywołaj `trab()` polimorficznie dla całej listy.
