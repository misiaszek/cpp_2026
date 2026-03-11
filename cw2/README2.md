

## `cw2-2.cpp`

- Struktura `Date` została rozszerzona o dodanie **funkcji członkowskiej** o nazwie `print` bezpośrednio w definicji struktury.
- `main` używa tej samej inicjalizacji agregatowej i dostępu do pól, ale teraz wywołuje `today.print()` zamiast funkcji zewnętrznej.
- Z punktu widzenia działania programów zachowanie jest identyczne; różnica polega na tym, że `print` jest logicznie powiązane z samym typem.

## C++ a C

- W **C++** można umieszczać funkcje wewnątrz definicji klasy lub struktury; nazywa się je *funkcjami członkowskimi* (lub metodami).
  - Mogą bezpośrednio odwoływać się do pól obiektu i są wywoływane za pomocą operatorów `.` lub `->`.
  - Dodawanie nowych funkcji członkowskich to powszechny sposób organizowania kodu wokół typów danych.
- W **C** struktury mogą zawierać tylko dane; nie ma językowego wsparcia dla metod. Aby powiązać zachowanie ze strukturą w C, pisze się oddzielne funkcje, które przyjmują wskaźnik do struktury jako argument (jak pokazano w `cw2-1.cpp`), jednak pozostają one funkcjami zewnętrznymi (nie-członkowskimi).

Podsumowując: w C++ można dodawać metody bezpośrednio do `struct`a (ten przykład to ilustruje), podczas gdy w C nie jest to możliwe.