---
title: "STL"
date: 2022-02-05T18:00:18+01:00
weight: 40
---

# Standard Template Library

Zakres:

* Przeładowywanie operatorów
* Konwersje
* Klasy zagnieżdżone i lokalne
* Iteratory
* Słowo kluczowe `auto`
* Składnia _ranged-for-loop_
* Szablony: wprowadzenie
* Typy algebraiczne
  * `std::pair`
  * `std::tuple`
  * `std::optional`
  * `std::variant`
* Standard Template Library
  * `std::array`
  * `std::vector`
  * `std::list`
  * `std::map`
  * `std::unordered_map`
* Algorytmy STL

## Przeładowywanie operatorów

W C++ można implementować zachowanie operatorów dla własnych typów innych niż wbudowane.
Ten zabieg potrafi znacznie uprościć korzystanie z obiektów naszej klasy.

```cpp
std::string text = "Hello";
text.append(", world!");
text += ", world";
```

Poznaliśmy już ten mechanizm przy okazji operatorów przypisania i przeniesienia `T& operator=(const T&)` i
`T& operator=(T&&)`. Własne operatory to tak naprawdę metody o specjalnej nazwie: `operator@`, gdzie `@`
jest konkretnym operatorem, takim jak `+=`. Typ biblioteczny `std::string` dostarcza 
[operator +=](https://en.cppreference.com/w/cpp/string/basic_string/operator%2B%3D) implementujący naturalnie oczekiwaną
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

Operatory arytmetyczne modyfikujące lewą stronę t.j. `+=`, `*=` zwykle zwracają referencję.
Operatory produkujące wartości tymczasowe takie jak `+`, `*` zwykle zwracają przez wartość.

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

Na potrzeby implementacji typów, których obiekty zachowują
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

Kompilator automatycznie będzie stosował konwersje przy przekazywaniu zmiennych, np. do funkcji.
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

## Klasy zagnieżdżone

Klasy w C++ można zganieżdżać, czyli definiować/deklarować jedną wewnątrz drugiej. 
To użyteczne, jeżeli jakiś typ ma sens tylko w ścisłym związku z innym.
Typ zagnieżdżony może być dodatkowo prywatny, pozwalając na ukrywanie detali implementacyjnych otaczającej klasy.

```cpp
class Rectangle {
    struct Point {
        float x, y;
    };

    Point a, b;
public:
    Rectangle(float x0, float y0, float x1, float y1) : a {x0, y0}, b{x1, y1} {}

    float area() const {
        return (b.x - a.x) * (b.y - a.y);
    }
};
```
Source: [nested_classes.cpp](nested_classes.cpp)

Z klasy zagnieżdżonej `Point` może korzystać tylko klasa `Rectangle` w swojej implementacji.
Kompilator nie pozwoli korzystać z takiej klasy z zewnątrz: 

```cpp
Rectangle::Point p {1, 2}; // błąd!
```

Przykład: [nested_classes.cpp](nested_classes.cpp)

Klasy można też definiować w funkcjach (ogólniej w blokach `{...}`). Mają wtedy lokalny zakres użycia,
od definicji, do końca bloku.

## Iteratory

Rozważmy fragment kodu iterujący się po tablicy za pomocą wskażnika:

```cpp
int tab[] = {1, 2, 3, 4};
for (int* ptr = tab; ptr != tab + 4; ++ptr) {
    ...
}
```

Wskaźnik `ptr` pełni tutaj rolę obiektu pokazującego na element pewnego kontenera.
Programując obiektowo, często implementujemy klasy reprezentujące kolekcje obiektów,
czasami o znacznie bardziej złożonej strukturze wewnętrznej niż tablica.

```cpp
class list {
    struct node {
        int value;
        std::unique_ptr<node> next;
        node(int value, std::unique_ptr<node> next) : value(value), next(std::move(next)) {}
    };

    std::unique_ptr<node> head;
  public:
    list() = default;

    void prepend(int value) {
        head = std::make_unique<node>(value, std::move(head));
    }
};
```

Powyżej zaimplementowana lista pięknie ukrywa swoją wewnętrzną implementację.
Użytkownik nie ma dostępu do jej wewnętrznych wskaźników i typów, dzięki czemu operacja `prepend()`
i inne metody zapewnią spójność struktury danych. Skoro tak, to pozostaje pytanie: jak się po czymś takim _przeiterować_?

Można np. dostarczyć metodę `size()` i `get(int n)` pozwalającą dobierać się do
n-tego elementu, ale takie rozwiązanie nie jest optymalne ze względu na przeszukiwanie
listy od początku za każdym wywołaniem `get()`.

Musimy rozbudować interfejs klasy o coś, co pozwoli nam iterować się po kolekcji,
podobnie do wskaźnika wędrującego po tablicy. _To coś_ musi implementować logikę iteracji,
pamiętać stan iteracji: aktualne miejsce.

Kontener może zwrócić obiekt, specjalnej, dostarczonej przez siebie klasy.
Takie klasy i obiekty nazywamy **iteratorami**, uogólniającymi wskaźnik.

```cpp
class list {
    // ...
public:
    class iterator {
        node* ptr;
    public:
        iterator(node* ptr) : ptr(ptr) {}

        int operator*() { return ptr->value; }

        iterator& operator++() {
            ptr = ptr->next.get();
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) { return ptr == other.ptr; }
        bool operator!=(const iterator& other) { return !(*this == other); }
    };

    iterator begin() { return iterator(head.get()); }
    iterator end() { return iterator(nullptr); }

    //...
};
```
Source: [iterators_list.cpp](iterators_list.cpp)

Lista pozwala pozyskać iterator na początek i koniec, umożliwiając czytelną implementację iteracji:

```cpp
for (list::iterator it = l.begin(); it != l.end(); ++it) {
    std::cout << *it << std::endl;
}
```

Iterator implementuje logikę przechodzenia po kontenerze dostarczając operator `++`. Dzięki temu
wartości klasy `list::iterator` zachowują się podobnie do wskaźników.

Kontenery często dostarczają kilka różnych klas iteratorów, np. `reverse_iterator`, pozwalający
iterować się _od tyłu_. Typowo implementowane są typy `iterator` i `const_iterator`. Drugi nie pozwala modyfikować
wartości w kontenerze. 

```cpp
class vector {
    std::unique_ptr<int[]> _data;
    std::size_t _capacity;
    std::size_t _size;
  public:
    /* ... */
    
    class iterator {
        int* ptr;
        /* ... */
    };

    iterator begin() { return iterator(_data.get()); }
    iterator end() { return iterator(_data.get() + _size); }

    class const_iterator {
        const int* ptr;
        /* ... */
    };

    const_iterator cbegin() const { return const_iterator(_data.get()); }
    const_iterator cend() const { return const_iterator(_data.get() + _size); }

    const_iterator begin() const { return cbegin(); }
    const_iterator end() const { return cend(); }
};
```
Source: [iterators_vector.cpp](iterators_vector.cpp)

Dzięki drugiemu typowi można iterować się po kontenerze mając jego niemodyfikowalny `const` obiekt lub referencję na stałą.

## `auto`

Praca z przestrzeniami nazw, typami zagnieżdżonymi, w szczególności z iteratorami wymaga dużo pisania:

```cpp
utils::vector::const_iterator it = v.begin();
utils::vector::const_iterator end = v.end();
while (it != end) { ... }
```

Pisanie typu w definicjach obiektów `it`, `end` jest niejako powtarzaniem siebie. Widać przecież, co
zwracają metody `begin()` i `end()`.

Dlatego C++ pozwala używać słowa kluczowego `auto` w definicjach zmiennych w przypadku kiedy 
dostarczamy inicjalizator. Typ zmiennej zostanie automatycznie wydedukowany.

```cmake
class A {};

A get_A() { return A(); }

int main() {
    auto x = 1; // x is int
    auto a = A(); // a is A
    auto a2 = get_A(); // a2 is A

    auto& rx = x; // rx is int&
    auto& ra = a; // ra is A&

    const auto& rxa = a; // rxa is const A&
    const auto& rxa2 = get_A(); // rxa2 is const A&
    return 0;
}
```
Source: [auto.cpp](auto.cpp)

Mając `auto` korzystanie z iteratorów staje się przyjemne:

```cpp
for (auto it = l.begin(); it != l.end(); ++it) {
    std::cout << *it << std::endl;
}
```

## Składnia ranged-for-loop

C++ dostarcza jeszcze przyjemniejszą składnię iterowania się po kolekcjach.
Dla tablic oraz klas dostarczających iteratory zwracane przez `begin()` i `end()`
typowo stosuje się tzw. _ranged-for-loop_:

```cpp
list l;
// ...
for (int it : l) {
    std::cout << it << " ";
}
```
Source: [ranged_for.cpp](ranged_for.cpp)

Składnia uwalnia z konieczności ręcznego zarządzania zmiennymi iterującymi.
Wymaga podania jedynie typu elementu (może być `auto`/`auto&`) i kontenera.

```cpp
for (item_type item : collection) {
    // ...
}
```


## Szablony

Jak zaimplementować kontener taki jak `std::vector<T>` mogący przechowywać wiele różnych typów danych?
C++ dostarcza w tym celu możliwość definiowania **szablonów klas**. Służy do tego słowo kluczowe `template`.

```cpp
template<typename T>
class vector {
  std::unique_ptr<T[]> data;
  /* ... */
  void push_back(const T& val);
  /* ... */
};
```
Source: [templates.cpp](templates.cpp)

Mimo że występuje tu słowo `class`, to nie jest definicja klasy. `vector` jest szablonem klasy, który trzeba
zinstancjonować podając konkretny typ jako `T` w czasie kompilacji.

```cpp
vector<int> v;     // vector<int> to już poprawny typ
vector<float> fv;
```

Kompilator w momencie natrafienia na wykorzystanie szablonu z danymi typami generuje w locie klasę (instancjonuje szablon)
podstawiając za `T` podane parametry. 

Parametrów szablonowych może być wiele:

```cpp
template<typename T, typename U>
class pair {
  T t;
  U u;
public:
  pair(T t, U u) : t(std::move(t)), u(std::move(u)) {}
  T& first() { return t; }
  U& second() { return u; }
};
```

> Czasami zamiast `typename` posługujemy się słowem kluczowym `class`. Nie ma różnicy.


C++ pozwala też na tworzenie **szablonów funkcji**:

```cpp
template<typename T>
void swap(T& a, T& b) {
    T tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
}
```
Source: [templates.cpp](templates.cpp)

Podobnie do klas, szablony funkcji do użycia wymagają podania konkretnych parametrów szablonowych.
Czasami kompilator potrafi je wydedukować:

```cpp

int x = 10, y = 20;
swap<int>(x, y);      // ok, generujemy funkcję swap<int>
swap(x, y);           // też ok!
```

## Para `std::pair`

Biblioteka standardowa dostarcza wielu użytecznych szablonów klas.
Pierwszym będzie para `std::pair<T1, T2>` która przechowuje 2 obiekty: jeden typu T1 a drugi typu T2.
W momencie konstrukcji pary, powstają 2 podobiekty, domyślnie konstruowane.

```cpp
{
    std::pair<A, B> p;
}
```
Source: [pair.cpp](stl/pair.cpp)

```text
A()
B()
~B()
~A()
```

Dostęp do elementów jest możliwy za pomocą składowych `first` i `second`.

```cpp
p.first = A();
p.second = B();
```

```text
A()                // konstrukcja wartości tymczasowej A()
A::operator=(A&&)  // przeniesienie wartości tymczasowej do wnętrza pary
~A()               // destrukcja wartości tymczasowej A()
B()                // konstrukcja wartości tymczasowej B()
B::operator=(B&&)  // przeniesienie wartości tymczasowej do wnętrza pary
~B()               // destrukcja wartości tymczasowej B()
```

Parę można stworzyć z istniejących obiektów, kopiując je lub przenosząc:

```cpp
A a;
B b;
std::pair<A, B> p(a, b);
std::pair<A, B> p2(std::move(a), std::move(b));
```

```text
A(const A&)
B(const B&)
A(A&&)
B(B&&)
```

Biblioteka dostarcza pomocniczy szablon funkcji `std::make_pair` tworzącą parę z podanych argumentów.

```cpp
std::pair<int, float> p = std::make_pair(1, 2.0f);
```

> Często mówi się, że para to tzw. _typ ilocznyowy_, bo liczba jej stanów możliwych to liczba stanów typu T1 pomnożona
przez liczbę stanów T2.

## Krotka `std::tuple`

Podobnym typem jest `std::tuple`, przechowujący kilka podobiektów.

```cpp
std::tuple<int, float, bool> t = {1, 2.0, true};

int i = std::get<0>(t);
float f = std::get<1>(t);
bool b = std::get<2>(t);
```
Source: [tuple.cpp](stl/tuple.cpp)

Dostęp do elementów krotki jest możliwy za pomocą pomocniczego 
szablonu funkcji `std::get<idx>` zwracającego referencję na dany element.

Podobnie, biblioteka dostarcza pomocniczy szablon `std::make_tuple`:

```cpp
auto t = std::make_tuple(0, 0.0, false);
```

C++17 dostarcza składnię znaną jako [_structured binding_](https://en.cppreference.com/w/cpp/language/structured_binding)
pozwalającą czytelniej korzystać z elementów typów iloczynowych:

```cpp
auto t = std::make_tuple(0, 0.0, false);
auto [i, f, b] = t;
auto& [ri, rf, rb] = t;
ri = 2;
rf = 4.0;
rb = false;
```

Podobna składnia działa dla struktur, tablic i `std::pair`.

## `std::optional`

Czasami chcielibyśmy w zmiennej przechowywać wartość jakiegoś typu
lub nic: wartość pustą, null.

Biblioteka dostarcza szablon `std::optional<T>`, który przechowuje albo wartość typu T,
albo nic, wartość pustą, reprezentowaną jako `std::nullopt`.

```cpp
std::optional<A> null;
std::optional<A> null2 = std::nullopt;

A a;
std::optional<A> opt(a);
opt = null;
```
Source: [optional.cpp](stl/optional.cpp)

```text
A()           // konstrukcja obiektu A a;
A(const A&)   // konstrukcja opt: kopia a
~A()          // destrukcja obiektu przechowywanego w opt
~A()          // destrukcja obiektu A a;
```

`std::optional` dostarcza metody `has_value`, `value`, `value_or`,
`operator*`, `reset` pozwalające badać jego stan
i dobierać się do przechowywanej wartości:

```cpp
std::optional<A> opt{A()};
if (opt.has_value()) {
    *opt = A();
    opt.value() = A();
}
opt.reset();
```

> `std::optional<T> to tzw. _typ sumacyjny_, bo liczba jego stanów to liczba stanów T + 1 (null)

## `std::variant`

`std::variant` to typ sumacyjny przechowujący wartość jednego z podanyh typów
(a nie wszystkich na raz, jak krotka). Zachowuje się podobnie do unii,
ale pamięta, który typ w danym momencie przechowuje.

```cpp
std::variant<int, float, bool> v;
v = 3;
v = 2.0f;
v = true;

if (std::holds_alternative<bool>(v)) {
    std::get<bool>(v) = false;
}
```
Source: [variant.cpp](stl/variant.cpp)

Domyslnie konstruowany variant przechowuje obiekt pierwszego typu.
Szablon `std::get<T>` pozwala na dostęp do przechowywanego obiektu.
`std::holds_alternative<T>` i metoda `index` pozwalają sprawdzić typ przechowywanego obiektu.

## Standard Template Library

Biblioteka standardowa C++ zawiera zbiór klas i algorytmów pozwalających programom
łatwo manipulować abstrakcyjnymi strukturami danych takimi jak listy, słowniki, zbiory.
Te komponenty często nazywane są _standardową biblioteką szablonów_.

Jeden z podstawowych kontenerów STL już znamy: `std::vector<T>`. [Biblioteka](https://en.cppreference.com/w/cpp/container)
zawiera ich znacznie więcej:

* `std::array`: tablica stałego rozmiaru
* `std::vector`: tablica dynamiczna
* `std::list`: lista łączona dwukierunkowa
* `std::forward_list`: lista łączona jednokierunkowa 
* `std::deque`: kolejka dwukierunkowa

* `std::set`/`std::multiset`: zbiór uporządkowany
* `std::map`/`std::multimap`: słownik uporządkowany

* `std::unordered_set`/`std::unordered_multiset`: zbiór nieuporządkowany
* `std::unordered_map`/`std::unordered_multimap`: słownik nieuporządkowany 

* `std::stack`: stos
* `std::queue`: kolejka
* `std::priority_queue`: kolejka priorytetowa

Wszystkie kontenery przechowują obiekty zadanego typu,
dostarczają operatory, iteratory, funkcje modyfikujące ich stan.
Omówienie wszystkich byłoby niemożliwe i nużące. Do pracy z kontenerami STL trzeba korzystać z dokumentacji.
Omówimy kilka najbardziej istotnych przykładów.

### std::array

Obiekty typu `std::array<T,N>` to zwykłe tablice N-elementowe.
W środku przechowują obiekt typu `T[N]`. Tablica jest zwykłą składową, nie jest alokowana dynamicznie.

```cpp
std::array<int, 10> a;
a[0] = 1;
a.at(1) = 2;
a.front() = 3;
a.back() = 4;
a.fill(3);
```

Typ dostarcza operator `[]` i metodę `at()` pozwalające
odczytywać i zapisywać elementy tablicy.
Metody `front()` i `back()` zwracają referencje na pierwszy i ostatni element.

Metoda `fill()` wypełnia tablicę daną wartością.

Klasa dostarcza iteratory i iteratory wsteczne:

```cpp
for (auto it = a.begin(); it != a.end(); it++) {
    // ...
}
for (auto it = a.rbegin(); it != a.rend(); it++) {
    // ...
}
```
Source: [array.cpp](stl/array.cpp)

Klasa nie definiuje jawnie konstruktora.
Dlatego elementy tablicy typu wbudowanego nie są domyślnie inicjalizowane.

Dla tablic typów klasowych tworzenie tablicy powoduje utworzenie elementów i wywołanie konstruktora.

```cpp
class A {
public:
    A() { std::cout << "A()\n"; }
};

std::array<A, 3> tab;
```

Jeżeli klasa nie ma konstruktora domyślnego, to trzeba jawnie podać argumenty konstruktora każdego podobiektu.

```cpp
class Point
{
public:
    Point(int x, int y) { std::cout << "Point(" << x << ", " << y << ")\n"; }
};

std::array<Point, 3> tab2{Point{1, 1}, Point{2, 2}, Point{3, 3}};
```

### std::vector

`std::vector` to tablica dynamicznego rozmiaru.

Posiada [mnóstwo konstruktorów](https://en.cppreference.com/w/cpp/container/vector/vector).
Domyślnie konstruowany wektor jest pusty (nie zawiera żadnych obiektów).
Można stworzyć wektor określonego rozmiaru, tworząc w nim od razu pewną liczbę obiektów:

```cpp
class A {
public:
    A() { std::cout << "A()\n"; }
    ~A() { std::cout << "~A()\n"; }
};

std::vector<A> v2(3); // {A(), A(), A()}
```

Jeżeli typ elementu nie ma domyślnego konstruktora to trzeba podać wartość, która zostanie skopiowana:

```cpp
class Int {
public:
    Int(int val);
};

std::vector<Int> v3(3, Int(1));
```

> Należy rozróżnić rozmiar bufora (_capacity_) klasy `std::vector` od liczby przechowywanych elementów (_size_).

Można stworzyć wektor, podając iteratory opisujące zakres elementów z innego źródła:

```cpp
std::array<int, 3> tab = {1, 2, 3};
std::vector<int> v4(tab.begin(), tab.end());
```
Source: [vector_constructors.cpp](stl/vector_constructors.cpp)

Podobnie do tablicy dostęp do elementów zapewniają metody `at()`, `operator[]`, `front()`, `back()`, `data()`.
Dostarcza identyczny interfejs iteratorowy pozwalający przechodzić po elementach wektora.

Wektor rośnie wraz ze wstawianiem do niego elementów. Kiedy kończy się miejsce
implementacja wektora:
1) alokuje większą tablicę
2) kopiuje do niej elementy ze starej tablicy
3) dealokuje starą tablicę niszcząc jej elementy

```cpp
std::vector<Int> v;
for (int i = 0; i < 5; ++i)
{
    std::cout << "  v.push_back(" << i << ")" << std::endl;
    v.push_back(Int(i));
}
```
Source: [vector_growth.cpp](stl/vector_growth.cpp)

Ten prosty kod woła nietrywialną ilość operacji na obiektach klasy `Int`:

```text
  v.push_back(0)
Int() val = 0              // konstrukcja wartości tymczasowej Int(0)
Int(Int&&) val = 0         // konstrukcja elementu wektora (przeniesienie)
~Int() val = 0             // destrukcja wartości tymczasowej I(0)
  v.push_back(1)
Int() val = 1              // konstrukcja wartości tymczasowej Int(1)
Int(Int&&) val = 1         // konstrukcja elementu wektora (przeniesienie)
Int(const Int&) val = 0    // kopia pierwszego elementu ze starej tablicy
~Int() val = 0             // destrukcja pierwszego elementu ze starej tablicy
~Int() val = 1             // destrukcja wartości tymczasowej Int(1)
  ...
```

Metodą `reserve()` można zawczasu zaalokować odpowiednio dużą przestrzeń i uniknąć
wielokrotnego kopiowania przy iteracyjnym wstawianiu.

Metoda `resize()` ustawiająca rozmiar wektora, potencjalnie tworzy lub niszczy obiekty.

```cpp
std::vector<Int> v;
std::cout << "  v.resize(3)" << std::endl;
v.resize(3, Int(999));
std::cout << "  v.resize(0)" << std::endl;
v.resize(0, Int(999));
```

```text
  v.resize(3)
Int() val = 999            // konstrukcja wartości tymczasowej Int(999)
Int(const Int&) val = 999  // konstrukcja elementu wektora
Int(const Int&) val = 999  // konstrukcja elementu wektora
Int(const Int&) val = 999  // konstrukcja elementu wektora
~Int() val = 999           // destrukcja wartości tymczasowej  
  v.resize(0)
Int() val = 999            // konstrukcja wartości tymczasowej Int(999)
~Int() val = 999           // destrukcja elementu wektora
~Int() val = 999           // destrukcja elementu wektora
~Int() val = 999           // destrukcja elementu wektora
~Int() val = 999           // destrukcja wartości tymczasowej  
```

Wstawianie elementów na koniec wektora wykonują metody `push_back` i `emplace_back`.

```cpp
std::vector<Int> v;
v.reserve(10);

Int val(999);

std::cout << "  v.push_back(val)" << std::endl;
v.push_back(val);
std::cout << "  v.push_back(std::move(val))" << std::endl;
v.push_back(std::move(val));
std::cout << "  v.emplace_back(999)" << std::endl;
v.emplace_back(999);
```

`push_back` kopiuje lub przenosi istniejącą wartość do wnętrza wektora.
`emplace_back` konstruuje element już w wektorze, unikając kopii.

```text
  v.push_back(val)
Int(const Int&) val = 999
  v.push_back(std::move(val))
Int(Int&&) val = 999
  v.emplace_back(999)
Int() val = 999
  v.insert(v.begin(), Int(1))
```
[vector_insert.cpp](stl/vector_insert.cpp)

Do wstawiania elementów na dowolnej pozycji wektora służą metody `insert` i `emplace`.
Przyjmują iterator mówiący gdzie wstawić.

```cpp
std::vector<int> vec = {1, 2, 3};
vec.insert(vec.begin() + 1, 999); // {1, 999, 2, 3} 
```

Te metody _przesuwają_ elementy wektora za pomocą operatora przeniesienia
tak, aby powstało miejsce na wstawiany element.

Podobnie podczas usuwania. Metoda `erase()` przyjmuje iterator na element usuwany
(lub cały zakres). Przesuwa elementy z końca wektora w miejsce pozostałe
po usunięciu.

```cpp
// v zawiera {1, 2, 3, 4, 5}
v.erase(v.begin() + 1, v.begin() + 4);
```

```text
Int& operator=(Int&&) val = 4  // przeniesienie ostatniego elementu na index [1]
~Int() val = 2  // usunięcie v[2]
~Int() val = 3  // usunięcie v[3]
~Int() val = 4  // usunięcie v[4]
```

[//]: # (/TODO: Kopiowanie, przenoeszenie całego wektora?)

### std::list

Lista przechowuje każdy element w osobnym obiekcie alokowanym na stercie. 
Dzięki temu nie trzeba kopiować, przenosić elementów przy wstawianiu, nawet w środek.

```cpp
std::list<Int> l;
for (int i = 0; i < 4; ++i) {
    l.emplace_back(i);
}
auto it = l.begin();
++it;
++it;
l.emplace(it, 100);
```

```text
Int() val = 0
Int() val = 1
Int() val = 2
Int() val = 3
Int() val = 100
~Int() val = 0
~Int() val = 1
~Int() val = 100
~Int() val = 2
~Int() val = 3
```

Nie ma dostępu swobodnego do i'tego elementu listy.
Trzeba iść od początku lub od końca, węzeł po węźle.

### std::map

`std::map` to słownik, przechowuje pary klucz-wartość,
posortowane po kluczu. Wewnątrz mapa przechowuje obiekty typu `std::pair<const Key, Value>`.
Podczas wstawiania trzeba podać parę, podczas iteracji, przeszukiwania również otrzymujemy parę.

```cpp
std::map<std::string, color> colors = {
    {"red", color{255, 0, 0}},
    {"green", color{0, 255, 0}},
    {"blue", color{0, 0, 255}}
};

for (auto it = colors.begin(); it != colors.end(); ++it)
{
    std::cout << "  colors[" << it->first << "] = " << it->second << std::endl;
}

colors.insert(std::make_pair("black", color{0, 0, 0}));

for (const auto& [key, value] : colors)
{
    std::cout << "  colors[" << key << "] = " << value << std::endl;
}

auto it = colors.find("black");
if (it != colors.end()) {
    std::cout << "Found colors[" << it->first << "] = " << it->second << std::endl;
}
```

Wartość pokazywana przez iterator mapy to para klucz wartość. Trzeba się potem posługiwać składnią `it->first` i `it->second`.
Dlatego bardzo czytelnym okazuje się połączenie _ranged-for-loop_ ze _structured binding_ podczas iteracji.

Podczas iteracji widać, że kontener jest posortowany po kluczach. Dla typu klucza `std::string` otrzymujemy porządek leksykograficzny:

```text
  colors[blue] = (0, 0, 255)
  colors[green] = (0, 255, 0)
  colors[red] = (255, 0, 0)
insert black
  colors[black] = (0, 0, 0)
  colors[blue] = (0, 0, 255)
  colors[green] = (0, 255, 0)
  colors[red] = (255, 0, 0)
```

Przy takim wstawianiu powstaje dużo wartości tymczasowych: `color`, potem `std::pair`, potem dopiero para jest kopiowana
do wnętrza mapy.

Metoda `find()` pozwala wyszukiwać po kluczu, zwracając iterator na wyszukany element (lub `end()` gdy nie znajdzie).

Mapa przeładowywuje często stosowany `operator[]` pozwalający odczytywać i zapisywać elementy mapy:

```cpp
colors["blue"] = color{0, 0, 254};
colors["magenta"] = color{255, 0, 255};
```

Trzeba mieć świadomość, że `operator[]` nie tylko zwraca referencję na wartość w mapie pod danym kluczem,
ale też potencjalnie tworzy element w mapie (o ile nie istnieje).

```text
color(0, 0, 254)                            // konstrukcja wartości tymczasowej (0, 0, 254)
color &operator=(color &&c) (0, 0, 254)     // kopia wartości tymczasowej do istniejącego elementu mapy
~color() (0, 0, 254)                        // destrukcja wartości tymczasowej
color(255, 0, 255)                          // konstrukcja wartości tymczasowej (255, 0, 255) 
color()                                     // konstrukcja nowego elementu mapy przez operator[]
color &operator=(color &&c) (255, 0, 255)   // kopia wartości tymczasowej do nowo utworzonego elementu mapy
~color() (255, 0, 255)                      // destrukcja wartości tymczasowej
```

Dlatego nie można użyć tego operatora do wyszukiwania (bo a nuż coś wstawimy). Nie da się go też stosować
mając `const` mapę lub referencję na stałą.

Mapa jest implementowana jako struktura drzewiasta. Wstawianie i wyszukiwanie ma złożoność logarytmiczną.
Typ klucza musi dostarczać `operator<` narzucający liniowy porządek w kontenerze.

`std::set` jest tym co `std::map`, tylko bez wartości. Przechowuje same klucze.

### std::unordered_map

Bardzo podobnym kontenerem jest `std::unordered_map`. Najważniejsza różnica to fakt, że klucze
nie są posortowane. Iteracja po kontenerze następuje w jakiejś nieznanej kolejności.
Cały interfejs omówiony dla wcześniej `std::map` jest identyczny. 

Taki nieposortowany słownik jest implementowany jako tablica mieszająca. Przy każdym dostępie
kontener oblicza funkcję skrótu na kluczu, otrzymując indeks w tablicy, gdzie ten powinien się znaleźć.
Dzięki temu dostęp do elementów może być najczęściej wykonany w czasie stałym.

Używając własnego typu jako klucza, trzeba dostarczyć mapie 2 rzeczy:
* możliwość porównywania kluczy, najczęściej `operator==`
* funkcję skrótu typu `std::size_t hash(Key k)`, najczęściej w postaci klasy implementującej `std::size_t operator()(Key)`

```cpp
struct color
{
    int r, g, b;
    color() : r(0), g(0), b(0) {}
    color(int r, int g, int b) : r(r), g(g), b(b) {}

    bool operator==(const color& c) const {
        return r == c.r && g == c.g && b == c.b;
    }
};

struct color_hash {
    std::size_t operator()(const color& c) const {
        return (c.r << 16) ^ (c.g << 8) ^ c.b;
    }
};

std::unordered_map<color, std::string, color_hash> color_names = {
        {color{255, 0, 0}, "red"}, 
        {color{0, 255, 0}, "green", }, 
        {color{0, 0, 255}, "blue"}
};
```
Source: [unordered_map.cpp](stl/unordered_map.cpp)

Typ skrótu jest dostarczany mapie w postaci trzeciego parametru szablonowego.

## Algorytmy STL

Poza samymi kontenerami, biblioteka STL dostarcza mnóstwo [algorytmów](https://en.cppreference.com/w/cpp/algorithm).
Funkcje te najczęściej pracują na zakresach zadanych przez 2 iteratory `[begin, end)`. Pozwalają przeszukiwać zakresy,
sortować je, przekształcać, kopiować, przenosić, usuwać wybrane elementy, itp.
Jest ich stanowczo za dużo do kompleksowego omawiania. Zilustrujemy bibliotekę najczęściej stosowanymi.

### Minima i maksima

Szablony funkcji `std::min_element`/`std::max_element` pozwalają liczyć minima i maksima z podanego zakresu:

```cpp
std::vector<int> v = {4, 2, 5, 3};
auto min = std::min_element(v.begin(), v.end());  // 2
auto max = std::max_element(v.begin(), v.end());  // 5
```
Source: [minmax.cpp](algos/minmax.cpp)

Szablony `std::min`/`std::max` wybierają odpowiednio mniejszy i większy z dwóch obiektów.

### Przeszukiwanie

Szablony `std::find`, `std::find_if`, `std::find_if_not` iterują się
po podanym zakresie i zwracają poszukiwany element. `std::find` szuka 
konkretnego obiektu, dla którego porównanie zwróci `true`.
Wersje `_if` szukają obiektu, dla którego zostanie spełniony warunek zadany
w postaci funkcji lub funktora.

```cpp
std::vector<std::string> names = {
  "John", "Jane", "Joseph", "Jac", "Jessica", "Jose", "Josh"
};

auto joseph = std::find(names.begin(), names.end(), "Joseph");

bool is_short(const std::string& name) {
    return name.length() < 4;
}

auto s = std::find_if(names.begin(), names.end(), is_short);
```
Source: [find.cpp](algos/find.cpp)

### Kopiowanie

Szablony `std::copy` i `std::copy_if` pozwalają kopiować elementy
z jednego zakresu do innego. `std::copy_if` kopiuje warunkowo.

```cpp
struct starts_with {
    char c;
    starts_with(char c) : c{c} {}
    bool operator()(const std::string& name) {
        return name.length() > 0 && name[0] == c;
    }
};

std::array<std::string, 3> names = {"Alfred", "Batman", "Catwoman"};

std::vector<std::string> vnames(names.size());
std::copy(names.begin(), names.end(), vnames.begin());

std::vector<std::string> good_names(names.size());
auto it = std::copy_if(names.begin(), names.end(), good_names.begin(), starts_with('A'));
good_names.erase(it, good_names.end());
```
Source: [copy.cpp](algos/copy.cpp)

### Transformacje

Szablon `std::transform` przechodzi element po elemencie po zadanym zakresie,
przepuszcza każdy element przez zadaną funkcję unarną, wynik zapisując
w innym zakresie wynikowym.

```cpp
class room {
    room(std::string name):
    const std::string& name();
};

std::unique_ptr<room> make_room(int id) {
    return std::make_unique<room>("Room " + std::to_string(id));
}

std::vector<int> ids = {107, 218, 304, 318, 404};
std::vector<std::unique_ptr<room>> rooms(ids.size());
std::transform(ids.begin(), ids.end(), rooms.begin(), make_room);
for (const auto& room_ptr : rooms) {
    std::cout << room_ptr->name() << std::endl;
} 
```
Source: [transform.cpp](algos/transform.cpp)

### Usuwanie

Szablony `std::remove` i `std::remove_if` pozwalają usuwać z zakresu daną wartość
lub wartości, dla których predykat jest prawdziwy.
Usuwanie trzeba rozumieć tutaj jako reorganizację zakresu.
Elementy usuwane są przesuwane na koniec, na początku zostają te nie usunięte.
Obie funkcje zwracają iterator na początek sekcji usuniętych elementów.

```cpp
std::vector<int> values = {4, 2, 5, 1, 10, 4, 24, 17};

bool is_even(int i) {
    return i % 2 == 0;
}
auto rit = std::remove_if(values.begin(), values.end(), is_even);
// begin -> 5, 1, 17, rit -> ?, ?, ?, ?, ?, end
values.erase(rit, values.end());
```
Source: [remove.cpp](algos/remove.cpp)

### Sortowanie

Szablon `std::sort` sortuje zakres. Potrzebuje do tego możliwości porównywania obiektów.
Sortowany typ musi definiować `operator<` lub musimy dostarczyć
funktor porównujący.

```cpp
struct person {
    std::string name;
    std::string surname;

    person(const std::string& n, const std::string& s) : name(n), surname(s) {}
};

struct person_cmp {
    bool operator()(const person& p1, const person& p2) {
        return p1.surname == p2.surname ? p1.name < p2.name : p1.surname < p2.surname;
    }
};

std::array<person, 5> ppl = {
    person{"John", "Doe"},
    person{"Jane", "Bluford"},
    person{"Joseph", "Doe"},
    person{"Jac", "Bluford"},
    person{"Jessica", "Bluford"}
};
std::sort(ppl.begin(), ppl.end(), person_cmp{});
```
Source: [sort.cpp](algos/sort.cpp)

### Agregacje

Szablon funkcji `std::accumulate` pozwala agregować dany zakres.
Mając zadaną wartość początkową akumulatora, funkcja iteruje się po
elementach zakresu, wywołując za każdym razem zadaną funkcję agregującą.
Funkcja otrzymuje wartość akumulatora i bieżący element jako parametry,
zwraca nową wartość akumulatora.

```cpp
int sum_agg(int acc, int val) {
    return acc + val;
}

int prod_agg(int acc, int val) {
    return acc * val;
}

std::string cat_agg(std::string acc, int val) {
    return acc + std::to_string(val) + ",";
}

std::vector<int> nums = {1, 2, 3, 4, 5};
std::accumulate(nums.begin(), nums.end(), 0, sum_agg);
std::accumulate(nums.begin(), nums.end(), 1, prod_agg);
std::accumulate(nums.begin(), nums.end(), std::string{}, cat_agg);
```
Source: [accumulate.cpp](algos/accumulate.cpp)
