# cw8-2 – klasa `BasePlusCommissionEmployee`

## Przegląd programu

Projekt `cw8-2` rozwija przykład z `cw8-1`. W poprzedniej wersji pracow([github.com](https://github.com/misiaszek/cpp_2026/blob/main/cw8/cw8-2/BasePlusCommissionEmployee.h))o **stałą pensję podstawową** (*base salary*), która jest wypłacana niezależnie od prowizji. Klasa nadal przechowuje imię, nazwisko, numer identyfikacyjny, wartość sprzedaży i stawkę prowizji, ale została rozszerzona o nowe pole opisujące dodatkowy składnik wynagrodzenia. ([github.com](https://github.com/misiaszek/cpp_2026/blob/main/cw8/cw8-2/BasePlusCommissionEmployee.h))

Program demonstruje więc naturalną ewolucję modelu obiektowego: od prostszej klasy `CommissionEmployee` do bardziej rozbudowanej `BasePlusCommissionEmployee`, która zachowuje wcześniejszą logikę i dodaje nową odpowiedzialność. W `main.cpp` obiekt jest tworzony, następnie odczytywane są jego dane przez gettery, później modyfikowana jest pensja podstawowa przez setter, a na końcu program wypisuje pełne dane oraz końcowe zarobki pracownika. ([github.com](https://github.com/misiaszek/cpp_2026/blob/main/cw8/cw8-2/main.cpp))

## Co zostało dodane względem `cw8-1`

W porównaniu do projektu `cw8-1` w klasie pojawiło się nowe prywatne pole:

```cpp
double baseSalary; // base salary
```

Oprócz tego rozszerzono interfejs publiczny o:

* nowy parametr konstruktora,
* metodę `setBaseSalary(double)`,
* metodę `getBaseSalary() const`.

W nagłówku klasy widać, że konstruktor przyjmuje teraz sześć argumentów: trzy tekstowe (`firstName`, `lastName`, `ssn`) oraz trzy liczbowe (`sales`, `rate`, `salary`). Ostatni z nich odpowiada właśnie za pensję podstawową. ([github.com](https://github.com/misiaszek/cpp_2026/blob/main/cw8/cw8-2/BasePlusCommissionEmployee.h))

## Konstruktor klasy

Konstruktor wygląda następująco:

```cpp
BasePlusCommissionEmployee::BasePlusCommissionEmployee(
 const string &first, const string &last, const string &ssn,
 double sales, double rate, double salary )
{
 firstName = first;
 lastName = last;
 socialSecurityNumber = ssn;
 setGrossSales( sales );
 setCommissionRate( rate );
 setBaseSalary( salary );
}
```

Jego działanie jest bardzo podobne do konstruktora z `cw8-1`, ale doszło dodatkowe wywołanie `setBaseSalary(salary)`. Oznacza to, że pensja podstawowa — podobnie jak sprzedaż i prowizja — przechodzi przez mechanizm walidacji zamiast być wpisywana bezpośrednio do pola. To dobra praktyka, ponieważ centralizuje sprawdzanie poprawności danych w jednej metodzie. ([github.com](https://github.com/misiaszek/cpp_2026/blob/main/cw8/cw8-2/BasePlusCommissionEmployee.cpp))

## Walidacja danych

Najważniejsza nowa metoda walidująca to:

```cpp
void BasePlusCommissionEmployee::setBaseSalary( double salary )
{
    if ( salary >= 0.0 )
        baseSalary = salary;
    else
        throw invalid_argument( "Salary must be >= 0.0" );
}
```

Zasada jest prosta: pensja podstawowa nie może być ujemna. Jeśli ktoś spróbuje przekazać wartość mniejszą od zera, zostanie zgłoszony wyjątek `invalid_argument`. Dzięki temu obiekt nie może wejść w niepoprawny stan. Podobną logikę miały już w `cw8-1` metody `setGrossSales()` oraz `setCommissionRate()`. ([github.com](https://github.com/misiaszek/cpp_2026/blob/main/cw8/cw8-2/BasePlusCommissionEmployee.cpp))

## Zmiana sposobu liczenia zarobków

Najważniejsza różnica logiczna między `cw8-1` i `cw8-2` dotyczy metody `earnings()`.

W `cw8-1`:

```cpp
return commissionRate * grossSales;
```

W `cw8-2`:

```cpp
return baseSalary + ( commissionRate * grossSales );
```

W pierwszej wersji pracownik zarabia wyłącznie prowizję od sprzedaży. W drugiej wersji jego dochód to suma dwóch składników:

1. stałej pensji podstawowej,
2. prowizji od sprzedaży.

To właśnie ta zmiana nadaje sens całemu rozszerzeniu projektu. Klasa nie jest już tylko kopią poprzedniej wersji z dodatkowym polem, lecz reprezentuje inny model wynagradzania. ([github.com](https://github.com/misiaszek/cpp_2026/blob/main/cw8/cw8-2/BasePlusCommissionEmployee.cpp))

## Zmiana metody `print()`

Rozszerzona została także metoda `print()`. W `cw8-1` wypisywała ona dane osobowe, sprzedaż i stawkę prowizji. W `cw8-2` dodano jeszcze informację o pensji podstawowej:

```cpp
cout << "base-salaried commission employee: " << firstName << ' '
     << lastName << "\nsocial security number: " << socialSecurityNumber
     << "\ngross sales: " << grossSales
     << "\ncommission rate: " << commissionRate
     << "\nbase salary: " << baseSalary;
```

Dzięki temu obiekt raportuje pełny stan zgodny z nowym modelem wynagrodzenia. ([github.com](https://github.com/misiaszek/cpp_2026/blob/main/cw8/cw8-2/BasePlusCommissionEmployee.cpp))

## Co dzieje się w `main.cpp`

Program testujący tworzy obiekt klasy `BasePlusCommissionEmployee`, przekazując mu wszystkie potrzebne wartości, w tym `baseSalary`. Następnie wypisuje dane pobrane getterami, po czym aktualizuje pensję podstawową do wartości `1000` przez `setBaseSalary(1000)`. Na końcu program wywołuje `print()` oraz `earnings()`, aby pokazać finalny stan obiektu i wyliczone wynagrodzenie. ([github.com](https://github.com/misiaszek/cpp_2026/blob/main/cw8/cw8-2/main.cpp))

To dobrze pokazuje klasyczny styl programowania obiektowego:

* konstruktor ustawia stan początkowy,
* gettery udostępniają dane do odczytu,
* settery pozwalają bezpiecznie modyfikować stan,
* metody biznesowe (`earnings`) realizują logikę domenową.

## Powtarzanie się kodu względem `cw8-1`

Warto zwrócić uwagę, że w `cw8-2` bardzo duża część kodu powtarza rozwiązanie z `cw8-1`. Nadal istnieją te same pola tekstowe:

* `firstName`,
* `lastName`,
* `socialSecurityNumber`,

oraz te same pola związane z prowizją:

* `grossSales`,
* `commissionRate`.

Także większość metod jest praktycznie identyczna:

* `setFirstName()` / `getFirstName()`,
* `setLastName()` / `getLastName()`,
* `setSocialSecurityNumber()` / `getSocialSecurityNumber()`,
* `setGrossSales()` / `getGrossSales()`,
* `setCommissionRate()` / `getCommissionRate()`.

Powtarza się również ogólny schemat konstruktora i sposób wypisywania danych. Różnice koncentrują się głównie wokół jednego nowego pola `baseSalary`. ([github.com](https://github.com/misiaszek/cpp_2026/blob/main/cw8/cw8-2/BasePlusCommissionEmployee.h))

To powtórzenie jest bardzo ważną obserwacją projektową. Taki kod działa poprawnie, ale jest mniej wygodny w utrzymaniu. Gdybyśmy chcieli później zmienić sposób walidacji imienia, nazwiska albo numeru identyfikacyjnego, trzeba byłoby poprawiać podobny kod w dwóch klasach. To prowadzi do duplikacji logiki.

## Dlaczego to jest ważne projektowo

`cw8-2` jest dobrym przykładem etapu przejściowego. Z jednej strony pokazuje, jak można rozbudować klasę przez dodanie nowego pola i nowych metod. Z drugiej strony ujawnia problem powielania kodu, który w większych projektach zwykle prowadzi do zastosowania **dziedziczenia** albo **kompozycji**.

Naturalna obserwacja po tym przykładzie brzmi:

* `BasePlusCommissionEmployee` jest bardzo podobny do `CommissionEmployee`,
* więc być może warto wydzielić część wspólną do klasy bazowej zamiast kopiować cały kod.

Taki wniosek jest bardzo cenny dydaktycznie, bo przygotowuje do kolejnych tematów związanych z hierarchią klas i ponownym użyciem kodu.

## Najważniejsze pojęcia pokazane w projekcie

* **rozszerzenie klasy** o nowe pole danych,
* **walidacja danych wejściowych** w setterze,
* **modyfikacja logiki biznesowej** w metodzie `earnings()`,
* **gettery i settery** jako kontrolowany interfejs klasy,
* **duplikacja kodu** jako sygnał, że projekt można dalej ulepszyć.

## Podsumowanie

Projekt `cw8-2` rozwija wcześniejszy przykład `cw8-1` przez dodanie pensji podstawowej do modelu pracownika prowizyjnego. Technicznie oznacza to:

* nowe pole `baseSalary`,
* nowy parametr konstruktora,
* nowe metody `setBaseSalary()` i `getBaseSalary()`,
* zmienioną metodę `earnings()`,
* rozszerzoną metodę `print()`.

Najważniejsza lekcja z tego przykładu jest jednak podwójna: po pierwsze pokazuje on, jak rozbudowuje się klasę, a po drugie ujawnia problem powtarzania kodu względem `cw8-1`. Właśnie takie sytuacje są później motywacją do stosowania dziedziczenia i l
