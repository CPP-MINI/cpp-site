---
title: "W5 - STL"
date: 2022-02-05T18:00:18+01:00
weight: 50
---

# Wykład 5 - STL

Zakres:

* przeładowywanie operatorów
* konwersje
* konstruktory konwertujące
* `auto`
* ranged for loop
* lambdas
* literały zdefiniowane przez użytkownika
* szablony
* STL
* iteratory
* algorytmy STL
* ranges

## Przeładowywanie operatorów

W C++ można implementować zachowanie operatorów dla własnych typów innych niż wbudowane.
Ten zabieg potrafi znacznie uprościć korzystanie z obiektów naszej klasy.

```cpp
std::string text = "Hello";
text.append(", world!");
text += ", world";
````

Poznaliśmy już ten mechanizm przy okazji operatorów przypisania i przeniesienia `T& operator=(const T&)` i
`T& operator=(T&&)`. Własne operatory to tak naprawdę metody o specjalnej nazwie: `operator@`, gdzie `@`
jest konkretnym operatorem, takim jak `+=`. Typ biblioteczny `std::string` dostarcza 
[operator +=](https://en.cppreference.com/w/cpp/string/basic_string/operator%2B%3D implementujący naturalnie oczekiwaną
konkatenację ciągów znakowych:

```cpp
string& operator+=( const string& str );
```

Przykład

W C++ można przeładowywać [mnóstwo operatorów](https://en.cppreference.com/w/cpp/language/operators).
W rzeczywistości jedynymi, których nie można przeładowywać to operator zakresowy `::`, operatory wyłuskania `.`, `.*` i
operator trójargumentowy `?:`. Można natomiast przeładować:
* operatory arytmetyczne (`+`, `*`, `%`, `++`, `--`, `-`, ...),
* operatory logiczne (`&&`, `||`, ...),
* operatory porównania (`<`, `>`, `==`, ...), 
* operatory bitowe (`&`, `|`, `^`, ...),
* operatory przesunięć (`<<`, `>>=`, ...),
* operatory wyłuskania `->` i `->*`,
* operator `,`,
* operatory wywołania `()` i indeksowania `[]`,
* operatory `new`, `new[]`, `delete`, `delete[]`
* operator `co_await`

Język tłumaczy użycie operatora na wywołanie odpowiedniej metody, np.:
```cpp
T a, b;
a + b;    // (a).operator+(b)
-a        // (a).operator-()
a[b...]   // (a).operator[](b...)
a->x      // ((a).operator->())->x
++a       // (a).operator++()
a++       // (a).operator++(0)
```


