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
* funkcje lambda
* szablony
* STL
* iteratory
* `auto`
* ranged for loop
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

Bardziej złożony przykład klasy `vector3d` implementującej operacje arytmetyczne na wektorach jako operatory:

```cpp
class vector3d {
    float _x, _y, _z;
public:
    /* ... */
    
    vector3d& operator+=(const vector3d& other) {
        _x += other._x;
        _y += other._y;
        _z += other._z;
        return *this;
    }

    vector3d operator+(const vector3d& other) const {
        vector3d result = *this;
        result += other;
        return result;
    }

    /* ... */
};
```

Operatory można implementować jako funkcje składowe klasy lub jako funkcje swobodne, np.:

```cpp
vector3d operator*(float value, const vector3d& other) {
    vector3d result = other;
    result *= value;
    return result;
}
```

Typowym przykładem jest przeładowanie operatora `<<` dla strumieni wyjściowych:

```cpp
std::ostream& operator<<(std::ostream& os, const vector3d& v) {
    os << "vector3d(" << v.x() << ", " << v.y() << ", " << v.z() << ")";
    return os;
}
/* ... */
std::cout << vector3d(1, 2, 3) << std::endl;
```

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

> Jeżeli operator jest przeładowany jako funkcja swobodna, to teoretyczna składnia była inna, np.: `operator+(a, b)`.

Przeładowywanie typowych, dwuargumentowych operatorów jest analogiczne.
Rozważmy ciekawsze przypadki.

### Operatory unarne

Wyrażenia `+a` i `-a` wykorzystują operatory _unary plus_ i _unary minus_.
Implementowane jako składowe klasy nie mają argumentów:

```cpp
class Int {
  int value;
public:
    /* ... */
    Int operator+() { return *this; }
    Int operator-() { return Int(-value); }
    /* ... */
};
```
Source: [overloading_arithmetic.cpp](overloading_arithmetic.cpp)

### Pre- i post- inkrementacje

Jak rozróżnić między wyrażeniami `++a` i `a++`?
Post inkrementacje/dekrementacje posiadają dodatkowy parametr
typu `int`, którego pre- operatory nie posiadają:

```cpp
Int& operator++() {
    ++value;
    return *this;
}

Int operator++(int) {
    Int tmp = *this;
    ++value;
    return tmp;
}
```

> Operator preinkrementacji może zmodyfikować `this` i zwrócić
referencję. Post inkrementacja nie może tego zrobić.

### Operator wywołania

Klasy mogą przeładować operator `(...)` z dowolną liczbą argumentów
powodując, że ich obiekty zachowują się jak funkcje.

```cpp
class LessThanFunc {
    int value;
public:
    /* ... */
    bool operator()(int x) {
        return x < value;
    }
    /* ... */
};
```
Source: [overloading_call.cpp](overloading_call.cpp)

Takie obiekty często nazywamy _funktorami_.

### Operator indeksowania

Można przeciążać operator `[]` dzięki czemu obiekty 
wyglądają jakby były indeksowalnymi kontenerami.

```cpp
class FakeArray {
public:
    /* ... */
    int operator[](std::size_t i) {
        return i + 1;
    }
};
```
Source: [overloading_index.cpp](overloading_index.cpp)

### Operator wyłuskania

Na potrzeby implementacji typów których obiekty zachowują
się tak jakby były wskaźnikami można przeładować operator `->`.
Taki operator musi zwrócić wskaźnik (lub inny obiekt który)
ma przeładowany operator `->`).

```cpp
class Ptr
{
    Point* _ptr;
public:
    Ptr(Point* ptr) : _ptr(ptr) {}
    ~Ptr() { delete _ptr; }
    Point* operator->() { return _ptr; }
    Point& operator*() { return *_ptr; }
};
```

Przeciążamy również operator dereferencji `*` aby móc dobierać się 
do wskazywanego obiektu, a nie tylko do jego składowych.

## Konwersje

Implementując konstruktory, dostarczamy metody konstrukcji obiektów naszego typu.
Konstruktory jednoargumentowe są szczególne, bo pozwalają zamienić obiekt pewnego typu
na inny typ. To tak zwane **konstruktory konwertujące**. Taki konstruktor może zostać użyty niejawnie.

```cpp
class A {
public:
    A(int x);
};

void foo(A a);
void goo(const A& a);

foo(3); // ok!
goo(4)  // ok!
```

Kompilator automatycznie będzie stosował konwersje przy przekazywaniu zmiennych
Takie niejawne konwersje mogą być trudne do zauważenia i niepożądane.
Jeżeli tak jest to jednoargumentowe konstruktory powinny być oznaczone słowem kluczowym `explicit`
blokującym niejawne konwersje.

```cpp
class A {
public:
    explicit A(int x);
};

void foo(A a);

// foo(3);               // błąd!
foo(A(3));               // ok!
foo(static_cast<A>(3));  // ok!
```

Konwersje można definiować również w formie **operatorów konwertujących**.
Klasa `T` może zdefiniować operator rzutowania na dowolny inny typ `U` (również wbudowany)
korzystając ze składni:

```cpp
class T {
operator U() { ... }
};

T t;
U u = static_cast<U>(t);
```

Typ zwracany takiego operatora to jego nazwa, więc nie jest powtarzana przed słowem kluczowym `operator`.
Operatory rzutowania podobnie do konstruktorów pozwalają na konwersje niejawne. Blokujemy je słowem kluczowym `explicit`.

Przykłady rzutowań: [conversion.cpp](conversion.cpp)
