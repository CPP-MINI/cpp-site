---
title: "W7 - Metaprogramowanie"
date: 2022-02-05T18:00:18+01:00
weight: 70
---

# Wykład 7 - Metaprogramowanie

Zakres:
* Szablony
  * Parametry szablonowe
  * Dedukcja i parametry domyślne
  * Instancjonowanie szablonów
  * Podział szablonu na pliki
  * Parametry stałe
  * Elementy zagnieżdżone
  * Specjalizacje szablonu
* Metaprogramowanie szablonowe
* Obliczenia w czasie kompilacji
  * `constexpr`

## Szablony

Szablony pozwalają na implementowanie parametryzowanych elementów programu klas, funkcji, zmiennych, etc.
Szablony deklarują **parametry szablonowe**, za które musi nastąpić podstawienie konkretnych typów/wartości.
Użycie danego szablonu wymaga podania **argumentów szablonowych**. 

```cpp
template <typename T>
class point
{
    T _x;
    T _y;
public:
    point() : _x{}, _y{} {}
    point(T x, T y) : _x(x), _y(y) {}

    T x() const { return _x; }
    T y() const { return _y; }
};

template<typename T>
void print(const point<T>& p)
{
    std::cout << "(" << p.x() << ", " << p.y() << ")\n";
}

point<int> pi{1, 2};
point<float> pf(1, 2);

print<int>(pi);
print<float>(pf);
```
Source: [parameters.cpp](templates/parameters.cpp)

W powyższym przykładzie `point<T>` jest szablonem klasy, a `print<T>` jest szablonem funkcji. `T` to parametr
szablonowy, za które podstawiane są odpowiednio argumenty `int` oraz `float`.
Użycie szablonu z konkretnymi argumentami, np. `point<int>` zmusza kompilator do **zinstancjonowania szablonu**.
Kompilator podstawia `T = int` i otrzymuje w wyniku zwykłą klasę:

```cpp
class point
{
    int _x;
    int _y;
public:
    point() : _x{}, _y{} {}
    point(int x, int y) : _x(x), _y(y) {}

    int x() const { return _x; }
    int y() const { return _y; }
};
```

Jednostka translacji `parameters.cpp` zawiera więc 4 zinstancjonowane szablony: `point<int>`, `point<float>`, `print<int>` i `print<float>`.
Kompilator nie instancjonuje szablonu dla parametrów, z którymi ten nie jest używany, np. `point<double>`, czy `point<std::vector<int>>`
nie istnieje w naszym programie.

```shell
g++ -c templates/parameters.cpp -o /tmp/parameters.o
objdump -t /tmp/parameters.o | c++filt | grep "point<.*>::"
```

```text
0000000000000000  w    F .text._ZN5pointIiEC2Eii        0000000000000028 point<int>::point(int, int)
0000000000000000  w    F .text._ZN5pointIfEC2Eff        0000000000000034 point<float>::point(float, float)
0000000000000000  w    F .text._ZN5pointIiEC2Eii        0000000000000028 point<int>::point(int, int)
0000000000000000  w    F .text._ZN5pointIfEC2Eff        0000000000000034 point<float>::point(float, float)
0000000000000000  w    F .text._ZNK5pointIiE1xEv        0000000000000014 point<int>::x() const
0000000000000000  w    F .text._ZNK5pointIiE1yEv        0000000000000015 point<int>::y() const
0000000000000000  w    F .text._ZNK5pointIfE1xEv        0000000000000016 point<float>::x() const
0000000000000000  w    F .text._ZNK5pointIfE1yEv        0000000000000017 point<float>::y() const
```

Narzędzie `objdump` listuje zawartość skompilowanych plików obiektowych.

### Parametry domyślne

Parametry szablonowe mogą mieć wartości domyślne. Podobnie jak przy funkcjach, można dodawać domyślne wartości
od końca listy parametrów.

```cpp
template<typename T = int, typename U = int>
class pair {
    T t;
    U u;
public:
    pair(T t, U u) : t(std::move(t)), u(std::move(u)) {}
    T& first() { return t; }
    U& second() { return u; }
    const T& first() const { return t; }
    const U& second() const { return u; }
};

pair<> p1(1, 2);                  // pair<int, int>
pair<float> p2(1.1, 2);           // pair<float, int>
pair<float, double> p3(1.1, 2.2); // pair<float, double>
```
Source: [constant_parameters.cpp](templates/constant_parameters.cpp)

### Dedukcja parametrów

Na podstawie argumentów szablonu funkcji lub argumentów konstruktora szablonu klasy kompilator jest w stanie
wydedukować argumenty szablonowe bez ich jawnego podawania.

```cpp
#include <vector>

template <typename T, typename U>
class pair
{
    T t;
    U u;

   public:
    pair(T t, U u) : t(std::move(t)), u(std::move(u)) {}
    T& first() { return t; }
    U& second() { return u; }
    const T& first() const { return t; }
    const U& second() const { return u; }
};

template <typename T, typename U>
pair<T, U> make_pair(const T& t, const U& u)
{
    return pair<T, U>(t, u);
}

pair p1(std::vector<int>{1, 2}, 4.0);  // pair<vector<int>, double>>
auto p2 = make_pair(3.0f, 50);         // pair<float, int>
return 0;
```
Source: [deduction.cpp](templates/deduction.cpp)

### Błędy podstawienia

Szablony są kompilowane w dwóch przebiegach. Pierwszy raz, gdy kompilator widzi definicję szablonu i drugi raz,
kiedy go instancjonuje. W pierwszym przebiegu kompilator nie zawsze może stwierdzić, czy szablon jest poprawny.
W zależności od użytych parametrów drugi przebieg może się udać albo nie.

Rozpatrzmy szablon klasy reprezentującej prostokąt 2D:

```cpp
template<typename PointType>
class rectangle
{
    PointType _lb;
    PointType _tr;

public:
    rectangle() : _lb{}, _tr{} {}

    rectangle(PointType lb, PointType tr) : _lb(lb), _tr(tr)
    {
        if (lb.x() > tr.x()) std::swap(lb.x(), tr.x());
        if (lb.y() > tr.y()) std::swap(lb.y(), tr.y());
    }

    double left() { return _lb.x(); }
    double right() { return _tr.x(); }
    double bottom() { return _lb.y(); }
    double top() { return _tr.y(); }

    double area() const
    {
        return (_tr.x() - _lb.x()) * (_tr.y() - _lb.y());
    }
};
```
Source: [errors.cpp](templates/errors.cpp)

Szablon `rectangle` jest parametryzowany typem punktu. Sposób w jaki szablon wykorzystuje parametr `PointType`
narzuca listę wymagań, które `PointType` musi spełniać:
* `rectangle() : _lb{}, _tr{} {}`
  * punkt musi mieć konstruktor domyślny
*  `rectangle(PointType lb, PointType tr) : _lb(lb), _tr(tr)`
  * punkt musi mieć konstruktor kopiujący
* `lb.x()`, `lb.y()`
  * punkt musi mieć metody `x()` i `y()` nieprzyjmujące żadnych argumentów
* `lb.x() > tr.x()`, `lb.y() > tr.y()`
  * musi istnieć `operator>` porównujący typ zwracany przez `x()` i `y()`
* `std::swap(lb.x(), tr.x())`
  * to co `x()` i `y()` zwracają, musi być akceptowalne dla `std::swap<T>` (np. musi się dać przypisać)
* `double left() { return _lb.x(); }`, ...
   typ zwracany przez `x()` i `y()` musi się dać przekonwertować na `double`
* `(_tr.x() - _lb.x()) * (_tr.y() - _lb.y())`
  * typ zwracany przez `x()` i `y()` musi dać się odejmować, a to, co wyjdzie: mnożyć

Po takiej analizie nietrudno zaporonować typ, który takich wymagań nie spełnia.

```cpp
rectangle<int> rint;          // ok!
rectangle<int> rint2 {1, 2};  // nope :(
rint.area();                  // nope :(
```

Przykładowy błąd, który kompilator wygeneruje podczas próby zinstancjonowania szablonu `rectangle<int>`:

```text
/templates/errors.cpp: In instantiation of ‘rectangle<PointType>::rectangle(PointType, PointType) [with PointType = int]’:
/templates/errors.cpp:61:30:   required from here
/templates/errors.cpp:15:16: error: request for member ‘x’ in ‘lb’, which is of non-class type ‘int’
   15 |         if (lb.x() > tr.x()) std::swap(lb.x(), tr.x());
```

Czyli po prostu `int` nie ma metody `x()`.

Co ciekawe samo wyrażenie `rectangle<int> rint;` kompiluje się poprawnie. Kompilator instancjonuje tylko te metody
szablonu (w tym wypadku konstruktor domyślny), których potrzebuje.

Inny przykład:

```cpp
struct string_point
{
    std::string _x;
    std::string _y;

    string_point(std::string x, std::string y) : _x{std::move(x)}, _y{std::move(y)} {}

    std::string& x() { return _x; }
    std::string& y() { return _y; }

    std::string x() const { return _x; }
    std::string y() const { return  _y; }
};

rectangle<string_point> rstr {{"hey", "hi"}, {"hello", "cpp"}}; // ok!
rstr.area(); // błąd
```

Tu zaskakująco konstrukcja `rstr` się powiedzie. Wygenerowany konstruktor `rectangle(string_point, string_point)`
jest _poprawny_:

```cpp
rectangle(string_point lb, string_point tr) : _lb(lb), _tr(tr)
{
    if (lb.x() > tr.x()) std::swap(lb.x(), tr.x());
    if (lb.y() > tr.y()) std::swap(lb.y(), tr.y());
}
```

Typ `std::string` zwracany przez metody `x()` i `y()` da się porównywać i zamieniać miejscami.

Użycie metody `area()` wygeneruje błąd:

```text
/templates/errors.cpp: In instantiation of ‘double rectangle<PointType>::area() [with PointType = string_point]’:
/templates/errors.cpp:76:14:   required from here
/templates/errors.cpp:26:25: error: no match for ‘operator-’ (operand types are ‘std::string’ {aka ‘std::__cxx11::basic_string<char>’} and ‘std::string’ {aka ‘std::__cxx11::basic_string<char>’})
   26 |         return (_tr.x() - _lb.x()) * (_tr.y() - _lb.y());
      |                ~~~~~~~~~^~~~~~~~~~
```

Bo string'ów nie da się odejmować.

Błędy wynikające z niepoprawnego użycia szablonów mogą być bardzo trudne zrozumieniu. Szablon powinien jasno dokumentować
jakie wymagania narzuca na parametry szablonowe. Szablon z danymi argumentami może być _częściowo poprawny_, tzn.
część jego metod może się kompilować, a część nie. Nowsze standardy C++ wprowadzają mechanizm [konceptów](#koncepty)
pozwalający programiście implementować w kodzie wymagania, a kompilatorowi sprawdzać je na wczesnym etapie przetważania.

### Instancjonowanie jawne

Jednostka translacji może wymusić zinstancjonowanie całego szablonu korzystając ze składni:
```cpp
template class rectangle<string_point>;
```

Nawet jeżeli jednostka translacji nie używa danego szablonu, wygenerowany plik obiektowy będzie zawierał 
skompilowane funkcje:

```cpp

template class point<int>;
template class point<float>;

point<double> make_pointd()
{
    point<double> d;
    return d;
}
```
Source: [explicit.cpp](templates/explicit.cpp) [point.hpp](templates/headers/point.hpp)

```shell
g++ -c templates/explicit.cpp -o /tmp/explicit.o
objdump -t /tmp/explicit.o  | c++filt
```

```text
0000000000000000  w    F .text._ZN5pointIiEC2Ev         0000000000000024 point<int>::point()
0000000000000000  w    F .text._ZN5pointIiEC2Ev         0000000000000024 point<int>::point()
0000000000000000  w    F .text._ZN5pointIiEC2Eii        0000000000000028 point<int>::point(int, int)
0000000000000000  w    F .text._ZN5pointIiEC2Eii        0000000000000028 point<int>::point(int, int)
0000000000000000  w    F .text._ZNK5pointIiE1xEv        0000000000000014 point<int>::x() const
0000000000000000  w    F .text._ZNK5pointIiE1yEv        0000000000000015 point<int>::y() const
0000000000000000  w    F .text._ZN5pointIfEC2Ev         0000000000000028 point<float>::point()
0000000000000000  w    F .text._ZN5pointIfEC2Ev         0000000000000028 point<float>::point()
0000000000000000  w    F .text._ZN5pointIfEC2Eff        0000000000000034 point<float>::point(float, float)
0000000000000000  w    F .text._ZN5pointIfEC2Eff        0000000000000034 point<float>::point(float, float)
0000000000000000  w    F .text._ZNK5pointIfE1xEv        0000000000000016 point<float>::x() const
0000000000000000  w    F .text._ZNK5pointIfE1yEv        0000000000000017 point<float>::y() const
0000000000000000  g    F .text                          0000000000000057 make_pointd()
0000000000000000  w    F .text._ZN5pointIdEC2Ev         0000000000000028 point<double>::point()
```

Widziemy, że `explicit.o` zawiera wszystkie funkcje 
`point<float>` i `point<int>` oraz dodatkowo konstruktor `point<double>::point()`, użyty w funkcji `make_pointd()`.

Dzięki jawnemu instancjonowaniu kompilowane są wszystkie metody klasy.

### Pliki nagłówkowe

Do zinstancjonowania szablonu kompilator musi znać jego treść.
W szczególności potrzebne są ciała metod, żeby wygenerować z nich kod.
Z tego powodu zwykle nie da się podzielić szablonu na plik nagłówkowy i plik implementacyjny,
tak jak robiliśmy to w przypadku zwykłych klas i funkcji.

Standardowym podejściem jest umieszczenie kompletnej definicji szablonu w pliku nagłówkowym. Wszystkie jednostki translacji
korzystające z takiego nagłówka będą niezależnie instancjonować potrzebne szablony, potencjalnie duplikując wykonywaną pracę.

Rozpatrzmy projekt złożony z plików: [main.cpp](templates/headers/main.cpp)
[point.hpp](templates/headers/point.hpp)
[utils.cpp](templates/headers/utils.cpp)
[utils.hpp](templates/headers/utils.hpp)
[Makefile](templates/headers/Makefile)
Sources: {{< github-link "templates/headers" >}}

Funkcja główna korzysta z `point<double>`, dostarczonego przez nagłówek `utils.hpp`. 

```cpp
int main()
{
    auto center = make_point(0, 0);

    std::vector<pointd> points(10);
    for (auto& p : points)
    {
        p = make_random_point();
        std::cout << "generated " << p << std::endl;
    }

    auto f = get_furthest(center, points);
    std::cout << "furthest = " << f << std::endl;

    return 0;
}
```

`utils.cpp` korzysta z tej samej klasy `point<double>` w swojej implementacji.

```cpp
pointd make_point(double x, double y) {
    return pointd(x, y);
}

pointd make_random_point() {
  // ...
}

pointd get_furthest(pointd center, std::vector<pointd> points) {
  // ...
}
```

Kompilator przetwarzając niezależnie jednostki translacji `main.cpp` i `utils.cpp` wygeneruje więc kod dla klasy `point<double>`.

```shell
make -C templates/headers
objdump -t templates/headers/main.o  | c++filt | grep "point<double>::"
objdump -t templates/headers/utils.o | c++filt | grep "point<double>::"
```

```text
$ objdump -t templates/headers/main.o  | c++filt | grep "point<double>::"
0000000000000000  w    F .text._ZNK5pointIdE1xEv        0000000000000016 point<double>::x() const
0000000000000000  w    F .text._ZNK5pointIdE1yEv        0000000000000017 point<double>::y() const
0000000000000000  w    F .text._ZN5pointIdEC2Ev         0000000000000028 point<double>::point()
0000000000000000  w    F .text._ZN5pointIdEC2Ev         0000000000000028 point<double>::point()
$ objdump -t templates/headers/utils.o | c++filt | grep "point<double>::"
0000000000000000  w    F .text._ZN5pointIdEC2Edd        0000000000000034 point<double>::point(double, double)
0000000000000000  w    F .text._ZN5pointIdEC2Edd        0000000000000034 point<double>::point(double, double)
0000000000000000  w    F .text._ZNK5pointIdE1xEv        0000000000000016 point<double>::x() const
0000000000000000  w    F .text._ZNK5pointIdE1yEv        0000000000000017 point<double>::y() const
```

Czy to nie powinno spowodować błędu linkera? Podwójnej definicji? Zwykle tak, ale specjalnie dla szablonów
kompilatory są zobowiązane pozwalać na wielokrotne instancjonowanie tego samego szablonu w całym programie.
Kod wygenerowany z szablonów jest zwykle przechowywany w specjalnej sekcji w pliku obiektowym.
Na etapie linkowania kod jest deduplikowany.

### Wydzielenie definicji

Podobnie jak w przypadku zwykłych funkcji i metod klas, można definiować ich ciało w osobnym miejscu.

```cpp

template <typename PointType>
class rectangle
{
    PointType _lb;
    PointType _tr;

   public:
    rectangle();

    rectangle(PointType lb, PointType tr);

    double left() { return _lb.x(); }
    double right() { return _tr.x(); }
    double bottom() { return _lb.y(); }
    double top() { return _tr.y(); }

    double area();
};

template <typename PointType>
rectangle<PointType>::rectangle() : _lb{}, _tr{}
{
}

template <typename PointType>
rectangle<PointType>::rectangle(PointType lb, PointType tr) : _lb(lb), _tr(tr)
{
    if (lb.x() > tr.x())
        std::swap(lb.x(), tr.x());
    if (lb.y() > tr.y())
        std::swap(lb.y(), tr.y());
}

template <typename PointType>
double rectangle<PointType>::area()
{
    return (_tr.x() - _lb.x()) * (_tr.y() - _lb.y());
}
```
Source: [prototypes.cpp](templates/split/prototypes.cpp)

Za każdym razem trzeba poprzedzać definicję funkcji składnią `template<typename T, ...> class C` wskazując, 
którego szablonu, z jakimi parametrami szablonowymi jest to metoda.

Nie można natomiast wynieść tych definicji do pliku `.cpp` z powodów [opisanych powyżej](#pliki-nagłówkowe).
Kompilator nie będzie potrafił zinstancjonować używanej funkcji i otrzymamy błąd linkera. 
Demonstruje to projekt złożony z plików: 
[rectangle.hpp](templates/split/rectangle.hpp)
[rectangle.cpp](templates/split/rectangle.cpp)
[point.hpp](templates/split/point.hpp)
[Makefile](templates/split/Makefile)
[main.cpp](templates/split/main.cpp)
Sources: {{< github-link "templates/split" >}}

```shell
make -C templates/split
```

```
g++  -o main.out main.o rectangle.o
/usr/bin/ld: main.o: in function `main':
main.cpp:(.text+0x88): undefined reference to `rectangle<point<double> >::rectangle(point<double>, point<double>)'
/usr/bin/ld: main.cpp:(.text+0xb0): undefined reference to `rectangle<point<double> >::area()'
```

Można zmusić kompilator do wygenerowania kodu podczas kompilacji pliku `rectangle.cpp` korzystając z
[jawnego instancjonowania](#instancjonowanie-jawne).

```cpp
template class rectangle<point<double>>;
```

Ta metoda dzięki temu koprogramd, który potrzebuje klasy `rectangle<point<double>>` będzie się linkował poprawnie.
Jeżeli jednak użyje jakiegoś innego typu punktu, to problem linkowania dalej wystąpi.

### Blokowanie instancjonowania

Kompilator instancjonując szablon zdefiniowany w nagłówku, wykonuje wielokrotnie tę samą pracę.
Jeśli kilka jednostek translacji korzysta z szablonu z danymi parametrami, to jawnie zinstancjonować szablon
w jednej z nich, a w innych poinformować kompilator, żeby tego nie robił za pomocą składni. `extern template C<Args...>`.

Przebudujmy projekt generujący losowe punkty, uwzględniając fakt, że dwa pliki źródłowe [main.cpp](templates/headers/main.cpp) i [utils.cpp](templates/headers/utils.cpp).
Korzystają z tego samego szablonu `point<double>`. Delegujemy instancjonowanie do jednostki `utils.cpp` dodając tam:

```cpp
template class point<double>;
```

Aby zabronić instancjonowania tego samego szablonu w `main.c` dodamy do nagłówka `utils.hpp` linię:

```cpp
extern template class point<double>;
```

Przetwarzając plik `main.c` kompilator widzi, że nie powinien generować klasy `point<double>`, powstanie ona w innej jednostce translacji.

Te 2 linie są warunkowo dodane za pomocą preprocesora. Wystarczy przekazać zmienną środowiskową `EXTERN_POINTD`
aby je uwzględnić:

```shell
EXTERN_POINTD=TRUE make -C templates/headers -B
objdump -t templates/headers/main.o  | c++filt | grep "point<double>::"
objdump -t templates/headers/utils.o | c++filt | grep "point<double>::"
```

Podglądając zawartość plików binarnych widać, że kod klasy `point<double>` został wygenerowany tylko w jednym z nich:
```text
$ objdump -t templates/headers/main.o  | c++filt | grep "point<double>::"
0000000000000000         *UND*  0000000000000000 point<double>::x() const
0000000000000000         *UND*  0000000000000000 point<double>::y() const
0000000000000000         *UND*  0000000000000000 point<double>::point()
$ objdump -t templates/headers/utils.o | c++filt | grep "point<double>::"
0000000000000000  w    F .text._ZN5pointIdEC2Edd        0000000000000034 point<double>::point(double, double)
0000000000000000  w    F .text._ZN5pointIdEC2Ev         0000000000000028 point<double>::point()
0000000000000000  w    F .text._ZN5pointIdEC2Ev         0000000000000028 point<double>::point()
0000000000000000  w    F .text._ZN5pointIdEC2Edd        0000000000000034 point<double>::point(double, double)
0000000000000000  w    F .text._ZN5pointIdE1xEv         0000000000000012 point<double>::x()
0000000000000000  w    F .text._ZN5pointIdE1yEv         0000000000000016 point<double>::y()
0000000000000000  w    F .text._ZNK5pointIdE1xEv        0000000000000016 point<double>::x() const
0000000000000000  w    F .text._ZNK5pointIdE1yEv        0000000000000017 point<double>::y() const
```

Ta metoda pozwala ograniczyć pracę kompilatora, jednocześnie pozwalając na elastyczne korzystanie z szablonów.
Jeżeli jakiś plik źródłowy potrzebuje klasy `point<T>` z innym typem niż `T = double` to kompilator tam
dynamicznie utworzy potrzebną klasę.

### Parametry stałe

Parametrami szablonowymi mogą być nie tylko typy. Język pozwala też na stałe czasu kompilacji: liczby, wskaźniki, enumeracje.

```cpp
const char float_stack_name[] = "fstack";

template<typename T, std::size_t N, const char* NAME>
class stack
{
    T _data[N];
    std::size_t _size = 0;
public:
    void push(const T& value)
    {
        std::cout << "[" << NAME << "] push(" << value << ")" << std::endl;
        if (_size == N) throw std::overflow_error("stack overflow");
        _data[_size++] = value;
    }

    void pop()
    {
        std::cout << "[" << NAME << "] pop()" << std::endl;
        if (_size == 0) throw std::underflow_error("stack underflow");
        _size--;
    }

    T& top()
    {
        if (_size == 0) throw std::underflow_error("stack underflow");
        return _data[_size - 1];
    }
};

stack<float, 10, float_stack_name> fstack;
fstack.push(1.0);
fstack.push(2.0);
fstack.push(3.0);
fstack.pop();
```
Source: [constant_parameters.cpp](templates/constant_parameters.cpp)

Typowym przykładem stałego parametru szablonowego jest rozmiar tablicy `std::array<T, N>`.

### Elementy zagnieżdżone

Szablon może korzystać z elementów zagnieżdżonych w typie, którym jest parametryzowany za pomocą operatora `::`, np.
`T::Subtype` albo `T::value`. Rozważmy udawaną implementację ciągu znakowego i funkcję wyszukującą znak tekście:

```cpp
struct fake_string
{
    using value_type = char;
    using size_type = std::size_t;
    static const size_type npos = static_cast<size_type>(-1);

    size_type size() const { return 10; }
    value_type operator[](int i) const { return 'a' + i; }
};

template<typename StringType>
typename StringType::size_type find(const StringType& str, typename StringType::value_type c)
{
    for (typename StringType::size_type i = 0; i < str.size(); ++i)
    {
        if (c == str[i]) return i;
    }
    return StringType::npos;
}

fake_string fs;
std::string s("hello");

std::cout << "find(fs, 'c') = " << find(fs, 'a') << std::endl;
std::cout << "find(s, 'c') = " << find(s, 'a') << std::endl;
```
Source: [nested.cpp](templates/nested.cpp)

Funkcja `find()` jest parametryzowana typem string'a. Działa zarówno dla naszego typu `fake_string` jak i 
bibliotecznego `std::string`. Oczekuje, że typ `StringType` będzie posiadał zagnieżdżone typy `size_type` i `value_type`
oraz zagnieżdżoną stałą `StringType::npos` zwracaną w przypadku nieodnalezienia znaku.

Język wymaga prefixowania zagnieżdżonych typów słowem kluczowym `typename` w przeciwieństwie do zagnieżdżonych stałych.
Umożliwia to kompilatorowi wstępne sprawdzenie poprawności szablonu w pierwszym przebiegu. Bez tej podpowiedzi
kompilator miałby bardzo trudne zadanie. Rozważmy elementy funkcji find bez adnotacji:

```cpp
template<typename StringType>
StringType::size_type find(const StringType& str, StringType::value_type c)
{
    for (StringType::size_type i = 0; i < str.size(); ++i)
    {
        if (c == str[i]) return i;
    }
    return StringType::npos;
}
```

* `StringType::size_type find(...)` 
  * co, jeżeli `size_type` wbrew nazwie okaże się wartością, a nie typem? Wtedy to nawet nie jest funkcja!
* `find(const StringType& str, StringType::value_type c)`
  * co, jeżeli `value_type` okaże się stałą wartością, np. `10`? Wtedy to nie jest poprawna definicja parametru funkcji!
* `return StringType::npos;`
  * gdyby `npos` okazał się typem to nie jest to poprawne wyrażenie `return`!

Rozróżnienie typów i wartości jest kluczowe dla zrozumienia znaczenia kodu.
Bez słowa `typename` kompilator zakłada, że zagnieżdżony element jest wartością. 


### Specjalizacja szablonu

Czasami szablon funkcji/klasy powinien wyglądać inaczej dla pewnych konkretnych argumentów szablonowych.
Typowym przykładem jest szablon funkcji porównującej.

```cpp
template <typename T>
T min(T a, T b)
{
    return a < b ? a : b;
}

int main()
{
    std::cout << min(1, 2) << std::endl;
    std::cout << min(3.0, 2.0) << std::endl;

    const char* txt1 = "hey";
    const char* txt2 = "alex";

    std::cout << min(txt1, txt2) << std::endl;
    return 0;
}
```
Source: [specialization.cpp](templates/specialization.cpp)

O ile dla liczb (`int`, `double`) implementacja szablonu `min` ma sens, to w przypadku `T = const char*` już nie koniecznie.
Szablon porównuje adresy zamiast treści stringów, co skutkuje niepoprawnym wyjściem programu:

```text
hey
```

Można temu zaradzić **specjalizując szablon** dla typu `const char*`.

```cpp
template<>
const char* min(const char* a, const char* b)
{
    return std::strcmp(a, b) < 0 ? a : b;
}
```

Korzystamy tutaj ze składni `template<>` zaznaczając, że po wyspecjalizowaniu szablon nie ma już żadnych argumentów
wymagających podstawienia. Za wszystkie wystąpienia `T` w prototypie szablonu funkcji podstawiamy wybrany typ
i implementujemy ciało w dedykowany sposób.

Szablony można też specjalizować częściowo, nie podając w 100% typu podstawianego za argument szablonowy `T`
a jedynie go konkretyzując, lub ograniczając liczbę argumentów szablonowych.

```cpp
#include <cstring>
#include <iostream>
#include <vector>

template <typename T>
struct A
{
    void print()
    {
        std::cout << "A<T>" << std::endl;
    }
};

template <typename T>
struct A<T*>
{
    void print()
    {
        std::cout << "A<T*>" << std::endl;
    }
};


template<typename T>
struct A<std::vector<T>>
{
    void print()
    {
        std::cout << "A<std::vector<T>>" << std::endl;
    }
};
```
Source: [partial_specialization.cpp](templates/partial_specialization.cpp)

W powyższym przykładzie mamy ogólny szablon `A<T>` i jego specjalizowane wersje, wybierane, jeżeli `T` jest wskaźnikiem
lub wektorem.

## Metaprogramowanie szablonowe

Szablony można wykorzystać do przeprowadzenia dowolnych obliczeń w trakcie kompilacji.
Kompilator instancjonując szablon z danymi typami jako parametry szablonowe niejako _oblicza_ typ wynikowy.
Można zatem prowadzić obliczenia nie na wartościach w pamięci podczas działania programu
a na typach w trakcie kompilacji. Rozważmy przykład implementujący obliczanie wartości wyrażeń arytmetycznych
za pomocą działań na typach:

```cpp
template <int N>
struct value {};

template<int N>
std::ostream& operator<<(std::ostream& os, const value<N>& v)
{
    os << N;
    return os;
}

template<typename V1, typename V2>
struct add;

template<int N1, int N2>
struct add<value<N1>, value<N2>>
{
    using result_type = value<N1 + N2>;
};

template<typename V1, typename V2>
struct mul;

template<int N1, int N2>
struct mul<value<N1>, value<N2>>
{
    using result_type = value<N1 * N2>;
};

int main()
{
    using a = value<2>;
    using b = value<3>;
    using c = value<4>;
    using x = mul<a, b>::result_type; // x = 2 * 3
    using y = add<x, c>::result_type; // y = 2 * 3 + 4

    std::cout << x{} << std::endl;
    std::cout << y{} << std::endl;

    return 0;
}
```
Source: [metaprogramming.cpp](templates/metaprogramming.cpp)

Typy `value<0>`, `value<1>` odpowiadają poszczególnym wartościom typu `int`.
Szablonowy `operator<<` drukuje odpowiednią wartość na podstawie typu argumentu, sama liczba nie jest nigdzie przechowywana w pamięci.
Program ma za to wiele różnych funkcji: `operator<<(std::ostream, value<0>)` i `operator<<(std::ostream, value<1>)` to dwie, różne
funkcje, o różnym adresie i kodzie binarnym.

Szablon `add<V1, V2>` dodaje dwa typy. Program używa, go tylko dla `V1` i `V2` będących typami `value<N>` więc
istotna jest tylko specjalizacja szablonu:

```cpp
template<int N1, int N2>
struct add<value<N1>, value<N2>>
{
    using result_type = value<N1 + N2>;
};
```

Wewnątrz `add<value<N1>, value<N2>>` deklaruje typ `result_type` będący wynikiem dodawania dwóch typów `value<N>`.
Analogicznie, `mul` realizuje mnożenie.

Rozpatrzmy teraz co się dzieje w `main()`:

```cpp
using a = value<2>;
using b = value<3>;
using x = mul<a, b>::result_type; // x = 2 * 3
std::cout << x{} << std::endl;
```

Pierwsze trzy linie to jedynie deklaracje typów. Następnie kompilator natrafia na `x{}`, czyli tworzy wartość typu
`x`. A co to jest typ `x`? Zgodnie z `using` jest to `mul<a, b>::result_type`. Musi więc w pierwszej kolejności zinstancjonować szablon
`mul<a, b>`. Do tego potrzebuje typów `a` i `b` czyli instancjonuje odpowiednio `value<2>` i `value<3>`, które są
pustymi klasami. Mając je, instancjonuje `mul<value<2>, value<3>>`, które otrzymuje taką treść, zgodnie z definicją szablonu `mul`:

```cpp
struct value<2> {};
struct value<3> {};
struct value<6> {};
struct mul<value<2>, value<3>> {
  using result_type = value<6>;
};
```

Program tworzy zmienną typu zagnieżdżonego `value<6>` więc kompilator instancjonuje też ten typ wynikowy.
Kompilator wykonał tym samym mnożenie, nie generując żadnej instrukcji mnożenia i nie zajmując żadnej pamięci 
w czasie wykonania tego programu.

Korzystając z takiej techniki, można tworzyć dowolnie złożone programy, które zostaną wykonane przez kompilator
w trakcie budowania właściwego programu. Czytelność takiego podejścia jest często kwestionowana, obecnie mamy
lepsze metody metaprogramowania opisane poniżej.

## Obliczenia w czasie kompilacji

Rozważmy poniższy fragment kodu, który wykonuje obliczenia na stałych, znanych w czasie kompilacji:

```cpp
int add(int x, int y) { return x + y; }

int main(int argc, char** argv)
{
	const int x = 1;
	const int y = 2;
	const int result = 2 * x + y;
	
	const int limit = add(result, x);
	
	if (argc > limit) {
		return 1;
	}
	
	return 0;
}
```
Source: [const.cpp](constexpr/const.cpp)

Takie obliczenia mógłby wykonać kompilator w trakcie tłumaczenia naszego programu.
Po co spowalniać i powiększać kod programu generując instrukcje mnożenia, dodawania, skoro można
od razu wyznaczyć wartości zmiennych `result` i `limit`. Technicznie, nic nie stoi na przeszkodzie,
żeby ten program w czasie wykonania wykonywał jedynie porównania `argc` ze stałą `limit`.
To jeden z podstawowych trików stosowanych przez optymalizator. Sprawdźmy to!

```shell
g++ constexpr/const.cpp -O0 -o const.debug
objdump --disassemble=main -M intel const.debug
```

Kompilując bez optymalizacji, nasz program będzie musiał bardzo się napracować.
Optymalizator co prawda obliczył wartość stałej `result` ale i tak wywołuje funkcję `add()`:

```text
0000000000001141 <main>:
    1141:       f3 0f 1e fa             endbr64
    1145:       55                      push   %rbp
    1146:       48 89 e5                mov    %rsp,%rbp
    1149:       48 83 ec 20             sub    $0x20,%rsp
    114d:       89 7d ec                mov    %edi,-0x14(%rbp)
    1150:       48 89 75 e0             mov    %rsi,-0x20(%rbp)
    1154:       c7 45 f0 01 00 00 00    movl   $0x1,-0x10(%rbp)   # Stała x = 1
    115b:       c7 45 f4 02 00 00 00    movl   $0x2,-0xc(%rbp)    # Stała y = 2
    1162:       c7 45 f8 04 00 00 00    movl   $0x4,-0x8(%rbp)    # Stała result = 4
    1169:       be 01 00 00 00          mov    $0x1,%esi          # Drugi argument dla add()
    116e:       bf 04 00 00 00          mov    $0x4,%edi          # Pierwszy argument dla add()
    1173:       e8 b1 ff ff ff          call   1129 <_Z3addii>    # Wywołanie add(4, 1)
    1178:       89 45 fc                mov    %eax,-0x4(%rbp)    # Przypisanie limit = add(4, 1)
    117b:       8b 45 ec                mov    -0x14(%rbp),%eax
    117e:       3b 45 fc                cmp    -0x4(%rbp),%eax
    1181:       7e 07                   jle    118a <main+0x49>
    1183:       b8 01 00 00 00          mov    $0x1,%eax
    1188:       eb 05                   jmp    118f <main+0x4e>
    118a:       b8 00 00 00 00          mov    $0x0,%eax
    118f:       c9                      leave
    1190:       c3                      ret
```

Porównajmy to z włączonymi optymalizacjami:

```shell
g++ constexpr/const.cpp -DNDEBUG -O3 -o const.release
objdump --disassemble=main -M intel const.release
```

```text
0000000000001040 <main>:
    1040:       f3 0f 1e fa             endbr64
    1044:       31 c0                   xor    eax,eax
    1046:       83 ff 05                cmp    edi,0x5  # Porównanie argc > 5
    1049:       0f 9f c0                setg   al
    104c:       c3                      ret
```

I o to chodziło! Jedynie instrukcja porównania pozostała w skompilowanym kodzie.
Wszystkie stałe `x`, `y`, `result`, jak i nie-stała `limit` znikły, nie są nawet przechowywane w pamięci!

Jak widać słowo kluczowe `const` nie ma dla kompilatora w tym zakresie żadnego znaczenia. 
Jego jedynym zadaniem jest zapewnienie, żeby zmienna w czasie wykonania, miała stałą wartość.
`const` nie tworzy stałych czasu kompilacji tylko stałe czasu wykonania! Takich stałych nie da się użyć
w niektórych kontekstach, gdzie kompilator musi znać wartość stałej:

```cpp
std::array<int, limit> arr = {};  // Nie zadziała!
std::cout << "created std::array<int, " << arr.size() << ">" << std::endl;
```

Nowsze standardy języka C++ dodają słowa kluczowe pozwalające jawnie tworzyć stałe czasu kompilacji i wykonywać
na nich obliczenia!

### Słowo kluczowe `constexpr`

Słowo kluczowe `constexpr` pozwala deklarować stałe czasu kompilacji.
Pozwala również deklarować funkcje, które mogą być używane do obliczeń na takich stałych.

```cpp
constexpr int add(int x, int y) { return x + y; }

constexpr int x = 1;
constexpr int y = 2;
constexpr int result = 2 * x + y;

constexpr int limit = add(result, x);
```
Source: [constexpr.cpp](constexpr/constexpr.cpp)

Kwalifikując wszystkie stałe z powyższego przykładu słowem `constexpr`
mówimy, że nie tylko są `const`, to znaczy niemodyfikowalne w czasie wykonania,
ale też, że ich wartości mogą być obliczone przez kompilator.

Funkcje `constexpr` mogą być wołane zarówno jak zwykłe funkcje, w czasie wykonania,
jak i mogą być wykonywane przez kompilator, jeżeli ich argumenty są stałymi znanymi w czasie kompilacji.

Budując zmodyfikowany program, nawet bez obliczeń, zobaczymy, że kompilator obliczył wartość zmiennej `limit`,
nawet bez żadnych optymalizacji:

```shell
g++ constexpr/constexpr.cpp -O0 -o constexpr.debug
objdump --disassemble=main -M intel constexpr.debug
```

```
0000000000001129 <main>:
    1129:       f3 0f 1e fa             endbr64
    112d:       55                      push   rbp
    112e:       48 89 e5                mov    rbp,rsp
    1131:       89 7d ec                mov    DWORD PTR [rbp-0x14],edi
    1134:       48 89 75 e0             mov    QWORD PTR [rbp-0x20],rsi
    1138:       c7 45 f0 01 00 00 00    mov    DWORD PTR [rbp-0x10],0x1   # x = 1
    113f:       c7 45 f4 02 00 00 00    mov    DWORD PTR [rbp-0xc],0x2    # y = 2
    1146:       c7 45 f8 04 00 00 00    mov    DWORD PTR [rbp-0x8],0x4    # 2 * x
    114d:       c7 45 fc 05 00 00 00    mov    DWORD PTR [rbp-0x4],0x5    # limit = 2 * x + 1
    1154:       83 7d ec 05             cmp    DWORD PTR [rbp-0x14],0x5   # Porównanie argc < limit
    1158:       7e 07                   jle    1161 <main+0x38>
    115a:       b8 01 00 00 00          mov    eax,0x1
    115f:       eb 05                   jmp    1166 <main+0x3d>
    1161:       b8 00 00 00 00          mov    eax,0x0
    1166:       5d                      pop    rbp
    1167:       c3                      ret
```

W przeciwieństwie do `const`, wartości `constexpr` można używać jako parametrów szablonowych, lub w `static_assert`:

```cpp
constexpr int limit = ... ;
std::array<int, limit> arr = {};
std::cout << "created std::array<int, " << arr.size() << ">" << std::endl;
```

Funkcje `constexpr` pierwotnie miały wiele ograniczeń. W pierwotnej wersji język pozwalał w ich ciele
tylko na jedną instrukcję: `return <wyrażenie>`. Obecnie możliwości są bardzo rozbudowane. Kompilator może wykonać
pętle i wyrażenia warunkowe:



```cpp
constexpr bool is_prime(std::size_t n) noexcept {
    if (n <= 1) return false;
    for (std::size_t i = 2; i * i <= n; i++)   if (n % i == 0) return false;
    return true;
}

// Obliczenia w czasie wykonania
std::cout << "is_prime(10000) = " << is_prime(10000) << std::endl;
std::cout << "is_prime(48611) = " << is_prime(48611) << std::endl;
// Obliczenia w czasie kompilacji
static_assert(is_prime(10000) == false); 
static_assert(is_prime(48611) == true);
```
Source: [demo.cpp](constexpr/demo.cpp)

Można wołać inne funkcje `constexpr`, budować złożone algorytmy:

```cpp
constexpr unsigned int nth_prime(std::size_t i) noexcept {
    std::size_t k = 1;
    for  (std::size_t counter = 0; counter < i; ++k)
    {
        if (is_prime(k)) ++counter;
        if (counter == i) return k;
    }
    return 0;
}

std::cout << "nth_prime(1000) = " << nth_prime(10000) << std::endl;
static_assert(nth_prime(5000) == 48611);
```

Kompilator może wykonać funkcje rekurencyjne:

```cpp
constexpr int fib(int n) {
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}

std::cout << "fib(20) = " << fib(10) << std::endl;
static_assert(fib(10) == 55);

std::array<int, fib(10)> arr = {};
std::cout << "created std::array<int, " << arr.size() << ">" << std::endl;
```

Klasy mogą mieć metody, konstruktory, operatory, które są `constexpr`, pozwalając na korzystanie z nich
w czasie kompilacji:

```cpp
class point
{
    float _x, _y;
public:
    constexpr point() : _x{0}, _y{0} {}
    constexpr point(float x, float y) : _x{x}, _y{y} {}
    [[nodiscard]] constexpr float x() const { return _x; }
    [[nodiscard]] constexpr float y() const { return _y; }
};

constexpr float distance(point a, point b)
{
    float dx = a.x() - b.x();
    float dy = a.y() - b.y();
    return std::sqrt(dx * dx + dy * dy);
}

constexpr float epsilon = 1e-6;
constexpr point a = {1.0, 2.0};
constexpr point b = {4.0, 6.0};

static_assert(distance(a, b) - 5.0 < epsilon, "too distant!");
```
Source: [classes.cpp](constexpr/classes.cpp)

Nowsze standardy języka pozwalają na jeszcze więcej:
* słowo `consteval`: wymusza wykonanie funkcji/metody w czasie kompilacji. `constexpr` tego nie gwarantuje.
* słowo kluczowe `constinit`: zapewnia, że zmienna statyczna będzie zainicjalizowana w czasie kompilacji, a nie przy pierwszym dostępie

Obliczenia w czasie kompilacji pozwalają wykonać część obliczeń naszych programów
przez kompilator, w sposób znacznie czytelniejszy niż programowanie z użyciem szablonów.
