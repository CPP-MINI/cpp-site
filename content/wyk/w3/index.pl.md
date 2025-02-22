---
title: "W3 - Klasy"
date: 2022-02-05T18:00:18+01:00
weight: 30
---

# Wykład 3 - Klasy

Zakres:

* cechy programowania obiektowego
* klasy, metody, widoczność
* przeładowywanie funkcji, argumenty domyślne
* konstruktory i destruktory
* RAII
* kopiowanie obiektów
* przenoszenie obiektów
* reguła 5/0
* nagłówek `<memory>` i sprytne wskaźniki
* składowe statyczne

## Programowanie Obiektowe

Programy obiektowe manipulują zbiorem obiektów, które mogą
się ze sobą komunikować. Obiekty łączą w sobie stan i zachowanie,
to definiująca je cecha.
Stan to najczęściej dane przechowywane w pamięci obiektu, czyli pola.
Zachowanie modelujemy za pomocą funkcji związanych z obiektem, czyli metod.

> Nie należy łączyć tak samo brzmiących pojęć: _obiekt_ języka C++
> i _obiekt_ w paradygmacie programowania obiektowego.

Język programowanie nie musi zawierać mechanizmów wspierających
programowanie obiektowe. W C też można napisać program obiektowy
i często się to robi:

```c
struct Vector2f { float x, y; }; // definicja klasy

struct Vector2f make_vector(float x, float y) // konstruktor
{
    struct Vector2f v = {x, y};
    return v;
}

float vector2f_length(const struct Vector2f* this) // metoda
{
    return (float)sqrt(this->x * this->x + this->y * this->y);
}

struct Vector2f vector2f_add(struct Vector2f* this, const struct Vector2f* other) // metoda z argumentem
{
    this->x += other->x;
    this->y += other->y;
    return *this;
}
```

W tym przykładzie typ `Vector2f` łączy w sobie 2 pola danych: `x` i `y` oraz dostarcza interfejs
modyfikujący i odczytujący ten stan w postaci dwóch funkcji, z których każda operuje na instancji typu `Vector2f`.

## Cechy programowania obiektowego

#### Abstrakcja

Polega na ukrywaniu zbędnych szczegółów implementacyjnych i prezentowaniu jedynie istotnych cech obiektu.
Dzięki abstrakcji obiekty mają zrozumiały dla programisty interfejs, odzwierciedlający rzeczywiste obiekty
lub zjawiska. Użytkownik operuje na interfejsie, a szczegóły techniczne są ukryte.

#### Hermetyzacja (Enkapsulacja)

To cecha polegająca na ukrywaniu wewnętrznego stanu obiektu oraz dostarczaniu kontrolowanego dostępu do niego przez
metody
(np. _gettery_ i _settery_). Hermetyzacja chroni przed bezpośrednią ingerencją w strukturę obiektu i pozwala na większą
kontrolę nad jego spójnością.

#### Dziedziczenie

Umożliwia tworzenie nowych typów obiektu, na podstawie istniejących,
dzięki czemu można ponownie wykorzystać kod oraz dodawać lub modyfikować funkcjonalności.
Typ bazowy udostępnia pola i metody typom dziedziczącym (klasom pochodnym),
co poprawia organizację i minimalizuje redundancję kodu.

#### Polimorfizm (Wielopostaciowość)

Pozwala na różne zachowanie obiektów w zależności od ich konkretnego typu,
korzystając z tego samego interfejsu. Wybór konkretnej implementacji zachowania
może zachodzić w czasie kompilacji, np. wybór funkcji przeciążonej, wybór operatora,
lub co bardziej charakterystyczne, w czasie wykonania programu.

> Te 4 cechy to bardzo często zadawane pytania na obronie :)

Użytkownik typu `Vector2f` nie musi wnikać w to, jak są przechowywane składowe wektora. Na stosie, stercie,
w tablicy w niezależnych zmiennych. To bez znaczenia, bo posługuje się jasno określonym interfejsem
`make_vector`. Mamy abstrakcję.

Na tym przykładzie widać, że C nie dostarcza dobrej hermetyzacji.
Każdy może ręcznie dobrać się do pól obiektu i je zmodyfikować, potencjalnie wprowadzając w niepoprawny stan.
Hermetyzacji brakuje. Możnaby ukryć pola korzystając z idiomu _pointer to the implementation_:

```c
// vector2f.h - publiczny nagłówek

struct _vector2f_impl; // coś ukrytego
struct Vector2f { _vector2f_impl* _impl; };

float vector2f_length(const struct Vector2f* this);

// impl.c - prywatna jednostka translacji

struct _vector2f_impl { float x, y; }

float vector2f_length(const struct Vector2f* this) {
    // tu widać czym _vector2f_impl jest
    return (float)sqrt(this->_impl->x * this->_impl->x + this->_impl->y * this->_impl->y);
}
```

Niewygodne, ale można.

Może wydawać się, że dziedziczenie i polimorfizm nie są w C do zrealizowania, ale to nieprawda!
Do realizacji dziedziczenia wystarczy zagnieżdżać struktury bazowe w pochodnych:

```c
struct Shape { char name[10]; }
struct Circle { Shape base; float cx, cy, r; }
struct Square { Shape base; float x1, y1, x2, y2; }
```

Struktury dziedziczące, re-używają pól struktury bazowej, a ponieważ `Circle*` można rzutować na `Shape*`
(bo `Shape` to pierwszy pod-obiekt) to funkcje dostarczane przez `Shape`, oczekujące `Shape*` będą działać też
z typami pochodnymi.

Polimorfizm dynamiczny, czyli wybór implementacji zachowania w zależności od typu można zrealizować,
przechowując w strukturze wskaźniki na funkcje. Wskaźniki będą ustawione na różne wartości
w zależności od konkretnego typu obiektu.

```c
struct Shape;
typedef float (*area_func_t)(const Shape*); 
struct Shape {
    char name[10];
    area_func_t f_area; // funkcja obliczająca pole zależna od konkretnego kształtu
}

float shape_area(Shape* s) {
    return s.f_area(s); // Skok do dynamicznie wybranej implementacji
}
```

Warto spojrzeć na kompleksowy przykład: [cobj.c](cobj.c)

## Klasy

C++ wspiera programowanie obiektowe. Dostarcza kilka mechanizmów językowych, ułatwiających
programowanie z zachowaniem wyżej wymienionych cech. Programowanie obiektowe w C++ jest oparte o **klasy**.

Klasy to zdefiniowane przez programistę typy obiektów, enkapsulujące stan i dostarczające abstrakcyjny interfejs
w postaci metod.

```cpp
class Mailbox {
private:
    std::vector<std::string> messages;

public:
    void post(const std::string& message) {
        messages.push_back(message);
    }

    std::string get() {
        if (messages.empty()) {
            return "";
        }

        std::string message = messages.front();
        messages.erase(messages.begin());
        return message;
    }
    
    std::size_t size() const { 
        return messages.size();
    }

    bool empty() const {
        return messages.empty();
    }
};
```

Klasa `Mailbox` modeluje skrzynkę odbiorczą przechowującą wiadomości. Przykład użycia:

```cpp
int main()
{
    Mailbox box;

    box.post("Hello, my name is Adam. Nice to meet You");
    box.post("Hey, wanna buy some crypto?");
    box.post("I'm looking for a good deal. Call me");

    while (!box.empty())
    {
        std::string msg = box.get();
        std::cout << "Received message: \"" << msg << "\"\n";
    }

    return 0;
}
```

Jej stan to lista wiadomości, implementowana jako `std::vector<std::string>`.
Stan jest hermetyzowany w sekcji `private:`. Tylko kod tej klasy ma prawo dobierać się do zmiennych i metod z tej
sekcji.
Próba dostępu do pola `messages` z zewnątrz zakończy się błędem kompilacji.

```
/cpp-site/content/wyk/w3/mbox.cpp: In function ‘int main()’:
/cpp-site/content/wyk/w3/mbox.cpp:47:9: error: ‘std::vector<std::__cxx11::basic_string<char> > Mailbox::messages’ is private within this context
   47 |     box.messages;
      |         ^~~~~~~~
/cpp-site/content/wyk/w3/mbox.cpp:8:30: note: declared private here
    8 |     std::vector<std::string> messages;
```

Publiczny interfejs klasy składa się z metod `post()`, `get()`, `size()` i `empty()`.
Tylko to jest widoczne dla użytkownika obiektu klasy `Mailbox`. Budujemy w ten sposób abstrakcję.
Użytkownik (tu kod `main()`) używa zdefiniowanego przez klasę, abstrakcyjnego interfejsu, nieświadomy,
jak jest od pod spodem implementowany, z czego składa się stan skrzynki, gdzie jest on przechowywany.
Wie tylko tyle, że może dodać wiadomość, odczytać wiadomość i sprawdzić ilość wiadomości.

Mając zahermetyzowany stan i abstrakcyjny interfejs, wymiana implementacji jest fantastycznie prosta.
Jeżeli wiadomości stałyby się ogromne i miały być przechowywane w postaci plików na dysku
zamiast string'ów w pamięci, to z punktu widzenia użytkownika klasy nic się nie zmienia!

W programie powołujemy do życia **obiekt klasy** `Mailbox`. Program może oczywiście tworzyć wiele obiektów
tego samego typu. Definicja pełni więc rolę wzorca, na podstawie którego powstają obiekty, 
czasem nazywane **instancjami**.

## Metody

Funkcje składowe, czyli inaczej metody, to kluczowy element języka pozwalający modelować zachowanie obiektów.
Implementacyjnie, metody to po prostu funkcje znajdujące się w ciele klasy. Tak jak funkcje mają
typ zwracany, nazwę i listę parametrów. Nazwy metod leżą w tej samej przestrzeni nazw (klasie), mieszając się z nazwami
pól składowych. Nie można zatem utworzyć metody o tej samej nazwie co pole.

Do pól klasy możemy dostawać się operatorami `.` i `->`. Tak samo jest w przypadku metod.
Dysponując obiektem lub referencją na obiekt, możemy wywołać jego metodę:

```cpp
void fill(Mailbox& box) {
    box.post("spam");
    box.post("spam");
    box.post("spam");
}

void main() {
    Mailbox box;
    box.post("Hello, my name is Adam. Nice to meet You");
    fill(box);
}
```

Dysponując wskaźnikiem używamy operatora `->`:

```cpp
void fill(Mailbox* box) {
    box->post("spam");
    box->post("spam");
    box->post("spam");
}

void main() {
    Mailbox box;
    fill(&box);
}
```

Metody zawsze są wywoływane _na rzecz_ konkretnego obiektu (instancji klasy).
Nie da się wywołać metody, nie mając obiektu:

```cpp
Mailbox::post("hey");
```

```
/cpp-site/content/wyk/w3/mbox.cpp:43:18: error: cannot call member function ‘void Mailbox::post(const std::string&)’ without object
   43 |     Mailbox::post("asdf");
      |     ~~~~~~~~~~~~~^~~~~~~~
```

### Wskaźnik `this`

Metody mają dostęp do obiektu, na rzecz którego są wywoływane.
Możemy w ich ciele posługiwać się nazwami pól, np. `messages`, mimo,
że nie wiadomo, którego konkretnie obiektu jest to pole.

Jak to działa?

Metody posiadają ukryty parametr `T* const` o nazwie `this` wskazujący na obiekt, na rzecz którego metoda jest
wywoływana.
Przy wywołaniu metody kompilator niejawnie przekazuje ten parametr razem z innymi argumentami.

```cpp
class Mailbox {
private:
    std::vector<std::string> messages;

public:
    void post(/*T* const this, */const std::string& message) {
        this->messages.push_back(message);
    }
};


void main() {
    Mailbox box;
    box.post("Hello, my name is Adam. Nice to meet You");
    // Mailbox::post(&box, "Hello, my name is Adam. Nice to meet You");
    fill(box);
}
```

Kompilator widząc odwołania do nazw będących polami lub metodami w kodzie metody niejawnie korzysta ze wskaźnika `this`.
Metody mogą wywoływać inne metody na rzecz tego samego obiektu.

```cpp
class Mailbox {
private:
    std::vector<std::string> messages;

public:
    void post(const std::string& message) {
        if (size() < 10) { // Mailbox::size(this);
            messages.push_back(message);
        }   
    }
        
    std::size_t size() const { 
        return messages.size();
    }
};
```

### Metody `const` i `volatile`

Niektóre metody w przykładach zawierają słowo kluczowe `const` za listą parametrów:

```cpp
std::size_t size() const { 
    return messages.size();
}
```

To tak zwane metody stałe, które zobowiązują się nie zmieniać stanu obiektu.
Można z ich implementacji tylko odczytywać pola i wołać inne metody oznaczone jako `const`.

Po co coś takiego? Po pierwsze jest czytelniej i bezpieczniej. Programista, oznaczając metodę jako stałą,
komunikuje użytkownikom klasy, że to wywołanie nic w obiekcie nie zmieni. Kompilator to kontroluje,
generując błędy przy modyfikujących operacjach.

Po drugie, obiekty mogą być zadeklarowane jako `const` (i/lub `volatile`).
Wszystkie ich pola również są wtedy stałymi. Wywołanie metod modyfikujących na rzecz takich obiektów byłoby
niebezpieczne.

```cpp
const Mailbox box;
int size = box.size(); // powinno działać
box.post("hey!"); // nie ma sensu
```

Niejawny parametr `this` w zwykłych metodach ma typ `T* const` a w metodach stałych `const T* const`.
Dzięki temu kompilator łatwo wyłapie błędy w wywołaniach:

```cpp
const Mailbox box;
int size = box.size(); // Mailbox::size(&box) 
// ok! const T* przekazany jako parametr const T*
// const Mailbox* const this = &box; 
box.post("hey!"); // Mailbox::post(&box, "hey!") 
// błąd! const T* przekazany jako parametr T*, porzucając const
// Mailbox* const this = &box;
```

Ponieważ parametru `this` nie widać na liście parametrów język musiał jakoś inaczej umożliwić dodanie do
niego słowo `const`. Zrobił to pozwalając na `const` po liście parametrów.

To samo aplikuje się w przypadku słowa `volatile`.

### Definicje i deklaracje

Podobnie jak w przypadku zwykłych funkcji, metody można deklarować, nie podając ich implementacji.

```cpp
class Mailbox {
private:
    std::vector<std::string> messages;
public:
    void post(const std::string& message);
    std::string get();
    std::size_t size() const;
    bool empty() const;
};
```

Definicje metod znajdujące się poza klasą muszą być kwalifikowane nazwą klasy:

```cpp
void Mailbox::post(const std::string& message) {
    messages.push_back(message);
}

std::string Mailbox::get() {
    if (messages.empty()) {
        return "";
    }

    std::string message = messages.front();
    messages.erase(messages.begin());
    return message;
}

std::size_t Mailbox::size() const { 
    return messages.size();
}

bool Mailbox::empty() const {
    return messages.empty();
}
```

Programując klasę, musimy wybrać czy dana funkcja będzie zaimplementowana w ciele, czy też poza klasą.

Typowym podejściem jest posiadanie pliku `*.hpp` z definicją klasy, zawierającą same deklaracje metod.
Ich implementacja jest dostarczana przez odpowiadający plik `*.cpp`. Użytkownicy klasy nie muszą znać implementacji
metod. Wystarczy im dołączenie samego nagłówka.

```mermaid
graph TB
    style mailbox_hpp fill: #e0e0e0
    mailbox_hpp["mailbox.hpp"]
    mailbox_cpp["mailbox.cpp"]
    main_cpp["main.cpp"]
    mailbox_hpp -->|#include| mailbox_cpp
    mailbox_hpp -->|#include| main_cpp
```

Dla krótkich funkcji, prostych setterów/getterów, wydzielanie implementacji do
pliku `*.cpp` często nie jest pożądane. Można wtedy pozostawić implementację
w ciele klasy w nagłówku. Pojawia się jednak problem podwójnej definicji.

```cpp
// mailbox.hpp
class Mailbox {
private:
    std::vector<std::string> messages;
public:
    void post(const std::string& message);
    std::string get();
    std::size_t size() const { return messages.size(); } // implementacja w nagłówku 
    bool empty() const;
};
```

Definicja metody `Mailbox::size() const` znajdzie się wtedy w każdej jednostce translacji,
która dołączyła ten nagłówek. Aby sobie z tym poradzić C++ specyfikuje, że metody
zaimplementowane w ciele klasy są domyślnie `inline`!

Source: [mailbox.cpp](mailbox.cpp)
[mailbox.hpp](mailbox.hpp)
[mailbox_main.cpp](mailbox_main.cpp)

```shell
g++ mailbox.cpp mailbox_main.cpp -o mailbox.exe && ./mailbox.exe
```

### Przeładowywanie funkcji i metod

Funkcje i metody w C++ można przeładowywać, czyli definiować funkcje o tej samej nazwie, różniące się parametrami.

```cpp
int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}

double add(double a, double b, double c) {
    return a + b + c;
}
```

To ułatwienie w stosunku do C, gdzie takie podobne funkcje trzeba by rozróżniać nazwą.

Widząc wywołanie funkcji kompilator sam wybiera przeładowanie
analizując argumenty w wywołaniu.

```cpp
add(5, 10); // -> add(int, int)
add(1.0, 2.0); // -> add(double, double)
add(1.0, 2.0, 3.0); // -> add(double, double, double)
```

Nie można przeładowywać zmieniając tylko typ zwracany:

```cpp
int add(int a, int b) { ... }
double add(int a, int b) { ... } //!
```

Niektóre typy są do siebie na tyle podobne, że nie pozwolą na przeładowanie.
Poniżej kilka przykładów:

```cpp
void foo(int* ptr);
void foo(int tab[]); // to samo, argument tablicowy to wskaźnik

void goo(int x);
void goo(const int x);
void goo(volatile int x);
void goo(int& x);
void goo(const int& x);
```

Często używane są natomiast przeładowania typu `T&` i `const T&` oraz `T*` i `const T*`
zapewniające różne implementacje w zależności od tego, czy argument jest `const` czy nie.

```cpp
struct Person { ... };

void foo(Person& x);
void foo(const Person& x);

Person p;
foo(p); // -> foo(Person&)
foo(static_cast<const Person&>(p)); // -> foo(const Person&)
```

Funkcje składowe klasy również można przeciążać, na tych samych zasadach:

```cpp
struct Log { ... };
class Logger {
public:
    void write(const Log& msg);
    void write(const std::string& msg);
    void write(const char* msg);
};
```

Co ciekawe, można przeładować funkcję jej `const` odpowiednikiem, np.:

```cpp
class Logger {
public:
    void write(const std::string& msg);
    void write(const std::string& msg) const;
};
```

Kompilator wybierze jedną bądź drugą na w zależności od tego, czy obiekt klasy `Logger` jest stały czy nie.

Pełny przykład: [overloading.cpp](overloading.cpp)

### Argumenty domyślne

C++ pozwala na podanie domyślnej wartości dla ostatniego (kilku ostatnich argumentów funkcji), np.:

```cpp
void write(const std::string& msg, Severity sev = Severity::INFO);
```

Przy wywołaniu można wtedy podać tylko wymagane argumenty z początku listy. Pozostałe zostaną uzupełnione
wartościami domyślnymi.

```cpp
write("operation done"); // -> write("hey", Severity::INFO);
write("foo() returns", Severity::DEBUG);
```

Domyślna wartość danego parametru może pojawić się co najwyżej raz, bez znaczenia czy w definicji czy w deklaracji.
Nie można re-definiować argumentu domyślnego, nawet z tą samą wartością.

```cpp
void write(const std::string& msg, Severity sev = Severity::INFO);
void write(const std::string& msg, Severity sev = Severity::INFO) {
  // ...
} // !
```

Wartości domyślne argumentów są stosowane automatycznie do każdego wywołania funkcji.
Muszą być zatem zdefiniowane wcześniej, przed wywołaniem. Jeżeli funkcja jest deklarowana w pliku nagłówkowym
a definiowana w dedykowanym pliku `*.cpp` to wartości domyślne powinny być umieszczone w deklaracji w nagłówku.
Umieszczone w definicji nie będą widoczne w jednostkach załączających plik nagłówkowy.

## Widoczność

Za pomocą etykiet `public:`, `private:` i `protected:` możemy sterować
widocznością składowych klasy. Dotyczy to zarówno pól, jak i metod.
To element języka wspomagający [hermetyzację](#hermetyzacja-enkapsulacja).

* Pola w sekcji `private` są dostępne tylko z wewnątrz metod klasy. Metody w sekcji `private` mogą być wywoływane tylko
  z wewnątrz klasy.
* Pola w sekcji `protected` są dostępne tylko z wewnątrz metod klasy i klas pochodnych. Metody w sekcji `protected` mogą
  być wywoływane tylko z wewnątrz metod klasy i klas pochodnych
* Pola i metody w sekcji `public` są dostępne dla wszystkich i stanowią publiczny interfejs (patrz [abstrakcja](#abstrakcja)).

Etykiety mogą pojawiać się w ciele klasy wielokrotnie.

```cpp
class Logger
{
private:
    std::vector<std::string> messages;

public:
    void write(const std::string& msg)
    {
        std::size_t idx = messages.size() + 1;
        add("[" + std::to_string(idx) + "] " + msg);
    }

private:
    void add(const std::string& msg) { messages.push_back(msg); }
};
```

#### `struct` vs `class`

Jedyną różnicą między strukturami a klasami jest domyślna widoczność ich składowych.
W przypadku klas jest to `private:` a dla struktur - `public:`. 

```cpp
struct Counter {
  int x; // public
  void increment() { x++; } // public
}
```

```cpp
class Counter {
  int x; // private
  void increment() { x++; } // private
}
```

Struktur konwencjonalnie używamy do małych prostych agregatów: typów jedynie grupujących kilka pól.
Nie jest to obowiązkiem.

## Konstruktory

Stan obiektu zawsze powinien być poprawny. Obiekty hermetyzują stan. 
Udostępniają publiczny interfejs do bezpiecznego modyfikowania tego stanu.
Rozważmy klasę modelującą stos ograniczonego rozmiaru:

```cpp
class Stack
{
    int tab[10];  //!< elementy stosu
    int size;     //!< aktualny rozmiar

public:
    void push(int val) {
      if (size == 10) return; 
      tab[size++] = val; 
    }
    
    int pop() {
        if (size == 0) return -1;
        return tab[--size];
    }

    int top() const { return size > 0 ? tab[size - 1] : -1; }
    
    bool empty() const { return size == 0; }
};
```
Source: [stack.cpp](stack.cpp)

Spróbujmy takiego stosu użyć:

```cpp
int main() {
    Stack s;

    s.push(1);
    s.push(2);
    s.push(3);

    while (!s.empty())
    {
        std::cout << s.pop() << std::endl;
    }
    
    return 0;
}
```

Rezultat?

```
Process finished with exit code 139 (interrupted by signal 11:SIGSEGV)
```

Stan początkowy jest niepoprawny. Czym inicjalizowane są pola klasy? Obecnie niczym. Wartość `size` jest 
nieznana. Korzystanie z niej ma niezdefiniowane zachowanie.

Klasa `Stack` ma **niezmienniki**: właności stanu, które powinny być prawdziwe
przez cały czas życia. Tutaj `0 <= size <= 10`. Zmienna `size`, jak i cały stan jest prywatny - i to dobrze!. 
Użytkownik klasy, nawet gdyby chciał, to nie może go ręcznie zainicjalizować. Klasa musi zrobić to sama!

Do tego celu służy **konstruktor**: specjalna funkcja składowa, nazywająca się dokładnie tak samo jak klasa:

```cpp
class Stack
{
    int tab[10];  //!< elementy stosu
    int size;     //!< aktualny rozmiar

public:
    Stack() : size{0} // lista inicjalizacyjna 
    {
       // ciało konstruktora
    }
    
    // ...
};
```

Konstruktory nie mają typu zwracanego, bo nic nie zwracają. Służą do inicjalizacji obiektu w jakimś regionie pamięci.

Konstruktor ma dostęp do nowo-tworzonego obiektu, można w nim posługiwać się wskaźnikiem `this`, chociaż 
z racji tego, że jest to obiekt _w trakcie inicjalizacji_ `this` nie koniecznie pokazuje na poprawny obiekt.

Konstruktory poza ciałem może mieć tzw. _listę inicjalizacyjną_ w formacie: 

```
: pole1{inicjalizator}, pole2{inicjalizator}, ...
```

Lista inicjalizacyjna zawiera wyrażenia inicjalizujące wybrane podobiekty. 
Podobiekty inicjalizowane są niejako przed wejściem w ciało konstruktora. 
W momencie wejścia w ciało konstruktora wszystkie obiekty składowe żyją: mają przydzieloną pamięć, ich inicjalizacja,
jawna czy nie, jest już zakończona. Ciało konstruktora może ich bezpiecznie używać.

> Bez względu na koleność występowania pól na liście, 
> podobiekty inicjalizowane są w kolejności występowania ich deklaracji w klasie!

Konstruktor klasy stack moglibyśmy napisać na kilka różnych sposobów:

Zainicjalizować jawnie `tab` i `size` na liście. Dzięki temu tablica również będzie wyzerowana:

```
Stack() : tab{}, size{0}
{
}
```

Pozostawić `tab` i `size` inicjalizowanymi domyślne (śmieciami) i potem to naprawić w ciele:

```
Stack()
{
   size = 0;
}
```

Dostarczyć inicjalizator przy definicji składowej, a nie na liście. Konstruktor może być wtedy pusty.

```
class Stack
{
  int tab[10]; 
  int size = 0;

public:
  Stack() {}
    
  // ...
};
```

Nie pisać konstruktora w ogóle. Kompilator wygeneruje go za nas:

```cpp
class Stack
{
  int tab[10];
  int size = 0;

public:
  // Stack() : size{0} {} 

  // ...
};
```

Ostatnia składnia powinna być preferowana ze względu na prostotę i czytelność.

### Konstruktor niejawny

Czy tego chcemy, czy nie, jeśli nie zdefiniujemy konstruktora, kompilator sam niejawnie go wygeneruje.
Taki konstruktor nic nie robi (więc nie jest dobry dla naszej klasy):

```cpp
class Stack
{
  int tab[10];
  int size;

public:
  // Stack() {} // konstruktor wygenerowany

  // ...
};
```

To samo możemy osiągnąć deklarując jawnie `Stack() = default;`

Możemy też kompilator zmusić do tego, żeby nie generował konsturktora: `Stack() = delete;`
Wtedy nie będzie się dało stworzyć obiektu typu `Stack`.

### Miejsce wywołania

Konstruktor jest automatycznie wywoływany w momencie tworzenia obiektu. Czyli kiedy? To zależy od jego trwałości.

Dla obiektów automatycznych dzieje się to w momencie napotkania definicji zmiennej:

```cpp
int main() {
  std::cout << "hey!";
  Stack s; // < tu będzie wywołanie konstruktora
  s.push();
}
```

Konstruktory automatycznych obiektów tymczasowych są wywoływnane w momencie ewaluacji wyrażenia:
```cpp
int main() {
  std::cout << "hey!";
  Stack{}.push(3);
}
```


Dla obiektów dynamicznych wywołanie konstruktora jest ostatnim etapem przetwarzania operatora `new`:

```cpp
int main() {
  std::cout << "hey!";
  Stack* s = new Stack; // < tu będzie wywołanie konstruktora
  s->push();
}
```

Dla obiektów statycznych wywołanie konstruktora nastąpi jeszcze przed `main()`!

```cpp
Stack s;

int main() {
  std::cout << "hey!";
  s.push();
}
```

Tu uwaga:

> Kolejność inicjalizowania obiektów statycznych pomiędzy jednostkami translacji jest niezdefiniowana!

### Argumenty konstruktora

Konstruktory tak jak metody mogą przyjmować parametry. Konstruktory można przeładowywać, dostarczając kilka metod inicjalizacji obiektu.

```cpp
class Stack
{
  int tab[10];
  int size;

public:
  Stack() : size{0} {} //!< konstruktor domyślny tworzy pusty stos
  Stack(int single_elem) : size{1}, tab{single_elem, 0} {} //!< konstruktor Stack(int) tworzy stos z 1 elementem
  Stack(const std::vector<int>& values) : size{static_cast<int>(values.size())} {
    for (std::size_t i = 0; i < values.size(); ++i) {
      tab[i] = values[i];
    }
  }
  Stack(int* values, int num) : size{num} {
    for (std::size_t i = 0; i < values.size(); ++i) {
      tab[i] = values[i];
    }
  }

  // ...
};

int main() {
    int arr[] = {1, 2, 3};
    std::vector<int> v{1, 2, 3};
    
    Stack s;
    Stack s2(1);
    Stack s3(arr, 3);
    Stack s4(v);

    Stack* ps = new Stack;
    Stack* ps2 = new Stack(1);
    Stack* ps3 = new Stack(arr, 3);
    Stack* ps4 = new Stack(v);
    
    return 0;
}
```
Source: [stack_constructors.cpp](stack_constructors.cpp)

### Konstruktor domyślny

Konstruktor, który może być wywołany bez podawania parametrów, nazywamy **konstruktorem domyślnym**.
Klasa, która nie ma konstruktora domyślnego, nie może być zainicjalizowana bezparametrowo:

```cpp
class A
{
    int val;

public:
    A(int x) : val(x)
    {
    }
};

// A ga;
A ga(3);

int main()
{
    // A a;
    A a(3);
    
    // A* pa = new A;
    A* pa = new A(3);

    return 0;
}
```
Source: [default_constructor.cpp](default_constructor.cpp)

Dla klas posiadających jakikolwiek konstruktor zdefiniowany przez programistę kompilator **nie generuje** 
niejawnego konstruktora bezparametrowego!

> Konstruktor, którego wszystkie argumenty mają wartości domyślne, też jest domyślny!

### Konstrukcja podobiektów

Podobiekty klasy muszą być zainicjalizowane przed wejściem w ciało konstruktora.
To znaczy, że trzeba podać parametry konstruktorów podobiektów na liście inicjalizacyjnej.
Szczególnie jeżeli podobiekty nie mają konstruktorów domyślnych! Kompilator nie jest w stanie wtedy wygenerować
konstruktora niejawnego, bo nie wie jak zainicjalizować składowe klasy.

```cpp
class A {
    int val;
public:
     A(int val = 0) : val{0}{}
};

class B {
    int val;
public:
    B(int val) : val{0}{}
};

class C {
    A a;
    B b;
    int val;
public:
     C(int a, int b, int c) : a{a}, b{b}, val{c}{}
     C(int b, int c) : b{b}, val{c}{} //!< ok bo A ma konstruktor domyślny
};

int main() {
    C obj(1, 2, 3);
    return 0;
};
```

## Destruktory

W analogii do konstruktorów, klasy posiadają też **destruktory**: specjalne funkcje składowe o nazwie `~NazwaKlasy()`, 
które są wywoływane w momencie niszczenia obiektu. Jest przydatny do _posprzątania_ stanu obiektu, w szczególności
zwolnienia zasobów.

* Obiekty automatyczne są niszczone wraz z końcem zakresu, gdzie zostały zdefiniowane. 
    * Kolejność niszczenia obiektów w tym samym bloku jest odwrotna do kolejności ich konstrukcji (definicji).
* Obiekty dynamiczne są niszczone w pierwszej fazie wykonania operatora `delete`.
* Obiekty statyczne są niszczone **po** wykonaniu `main()`.

```cpp
class A {
    std::string tag;
public:
    A(std::string tag) : tag{tag} { std::cout << "A(" << tag << ")\n"; }
    ~A() { std::cout << "~A(" << tag << ")\n"; }
};

class B {
    std::string tag;
public:
    B(std::string tag) : tag{tag} { std::cout << "B(" << tag << ")\n"; }
    ~B() { std::cout << "~B(" << tag << ")\n"; }
};

class C {
    A a;
    B b;
    std::string tag;
public:
    C(std::string tag) : a{tag}, b{tag}, tag{tag} { std::cout << "C(" << tag << ")\n"; }
    ~C() { std::cout << "~C(" << tag << ")\n"; }
};

C a("static");

int main() {
    C a("automatic");
    auto pa = new C("dynamic");
    delete pa;
    return 0;
}

```
Source: [destructor.cpp](destructor.cpp)

Najpierw wykonywane jest ciało destruktora danej klasy, dopiero potem destruktory jej podobiektów.
Moment rozpoczęcia wykonania destruktora jest jednocześnie momentem końca życia obiektu.
Dzięki tej kolejności destruktor klasy może korzystać ze składowych.
Destruktory podobiektów wykonują się w kolejności odwrotnej do kolejności ich konstrukcji:

```
A(automatic)
B(automatic)
C(automatic)
...
~C(automatic)
~B(automatic)
~A(automatic)
```

Destruktor też nie zwraca żadnej wartości. Nie może mieć argumentów (no bo jak je przekazać).

## RAII

Konstruktory i destruktory są wywoływane automatycznie. 
Dla poprawnie zaimplementowanych klas programista nie musi ręcznie inicjalizować obiektu. 
Nie musi też go ręcznie _czyścić_. Kompilator wstawia te wywołania niejawnie.
Ma to szczególne znaczenie, jeżeli obiekty klasy zarządzają zasobami, które trzeba jawnie alokować i zwalniać, np. pamięć.

Przykładowo: zaimplementujmy stos, którego rozmiar będzie dynamiczny, ustalany w trakcie konstrukcji:

```cpp
class DynamicStack
{
    const int capacity;
    int* tab;
    int size;

public:
    DynamicStack(int capacity = 10) : capacity(capacity), size(0)
    {
        tab = new int[capacity];
    }

    ~DynamicStack() { delete[] tab; }

   // ...
};

int main()
{
    DynamicStack s(5); // alokacja bufora w konstruktorze
    // ...
    return 0;
} // automatyczne wywołanie destruktora i dealokacja bufora!
```
Source: [dynamicstack.cpp](dynamicstack.cpp)

To potężny mechanizm. Koniec z wyciekami pamięci i innych zasobów. Nie musimy już pamiętać o ręczny wywołaniu `free()`
w każdej ścieżce, w tym w dziesięciu różnych miejscach, w których wychodzimy w związku z błędem. Destruktor zawsze 
zostanie wywołany!

Powiązanie czasu życia zasobów z czasem życia obiektów nosi nazwę idiomu RAII (_Resource Acquisition Is Initialization_).
Należy go stosować jak najczęściej. Sam [Bjarne Stroustrup](https://en.wikipedia.org/wiki/Bjarne_Stroustrup) mówi, że konstruktory i destruktory w powiązaniu 
z automatycznym czasem życia obiektu to najistotniejszy mechanizm języka C++.

## Kopiowanie obiektów

Obiekty, bez względu na typ, zwykle da się kopiować. Nie jest trudno wyobrazić sobie kopię typów prostych. Kopiowanie abstrakcyjnych, złożonych w środku obiektów
też jest możliwe do zamodelowania, np.: kopia stosu, kopia tekstu (string'a), kopia grafu, itp.

Kopie powstają w dwóch **różnych** sytuacjach:
1) Utworzenie nowego obiektu typu `T` z inicjalizatorem tego samego typu.

```cpp
class T { ... };
T b;
T a = b;
```

2) Przypisanie do istniejącego obiektu typu `T` innego obiektu tego samego typu.

```cpp
class T { ... };
T b;
T a;
a = b;
```

### Konstruktory kopiujące

W pierwszej sytuacji tworzymy nowy obiekt, więc kompilator używa konstruktora.
Konstruktorem kopiującym jest jednoargumentowy konstruktor klasy `T`, przyjmujący referencję na typ `T` (`(const/volatile) T&`), np.:

```cpp
DynamicStack(const DynamicStack& other)
    : capacity(other.capacity),
      size(other.size)
{
    tab = new int[capacity];
    for (int i = 0; i < size; ++i) {
        tab[i] = other.tab[i];
    }
}
```
Source: [dynamicstack_copy.cpp](dynamicstack_copy.cpp)

```
DynamicStack s(5);

s.push(1);
s.push(2);
s.push(3);

DynamicStack s2(s);  // kopia
DynamicStack s3 = s; // druga kopia
```

Jeżeli programista nie dostarczy swojego, to kompilator, o ile może, generuje niejawny konstruktor kopiujący.
Taki konstruktor kopiuje pole po polu. W przypadku klasy `DynamicStack` taki konstruktor _zawłaszczy sobie_ wkaźnik
na dane stosu. Jest więc niepoprawny!

### Operatory przypisania

W drugiej sytuacji obiekt docelowy, do którego kopiujemy, już istnieje. Kompilator nie może więc użyć konstruktora.
Wywoływany jest **operator przypisania**.

C++ pozwala na przeładowywanie operatorów, w tym operatora przypisania `=`. W zależności od typu argumentów
(stron operatora) w czasie kompilacji wybrana będzie odpowiednia implementacja. W ogólności o operatorach
będziemy mówić na następnych wykładach. Tu zajmiemy się tylko przypisaniem.

Operator przypisania `=` ma 2 parametry: lewą i prawą stronę przypisania:

```cpp
DynamicStack s3; // początkowo pusty stos 
s3 = s;          // nadpisanie stosu innym stosem (operatorem przypisania)
    
const DynamicStack empty;  // Utworzenie stałej: pustego stosu
s3 = empty;                // wyczyszczenie stosu s3 (operatorem przypisania)
```

Operator definiujemy składnią podobną do funkcji, z tym że jej nazwą jest `operator=`. `operator` to słowo kluczowe.
Prawa strona przypisania to argument operatora.
Lewa strona przypisania to obiekt wskazywany przez `this`.
Kompilator na podstawie typu lewej strony wybiera, z jakiej klasy ma użyć operatora.

```cpp
DynamicStack& operator=(const DynamicStack& other)
{
    if (this == &other) return *this;  // ochrona przed samoprzypisaniem
    if (capacity != other.capacity)    // musimy re-alokować tylko jeżeli prawa strona ma inną pojemność
    {
        delete[] tab;
        tab = new int[other.capacity];
        capacity = other.capacity;
    }
    size = other.size;                 // przepisanie rozmiaru ...
    for (int i = 0; i < size; ++i) {
        tab[i] = other.tab[i];         // ... i danych z prawej strony
    }
    return *this;
}
```
Source: [dynamicstack_copy.cpp](dynamicstack_copy.cpp)

Praktycznie każda implementacja operatora przypisania rozpoczyna się instrukcją warunkową chroniącą przed
przypisaniem typu `a = a;`.

> Można zauważyć, ze w tym przykładzie pole `capacity` straciło modyfikator `const`. To konieczne, jeżeli
obiekt ma wspierać przypisanie. Inaczej nie dałoby się zmienić wartości `capacity` przez cały czas życia obiektu!

Operator może zwracać (nie musi). Zwrócona wartość jest wynikiem wyrażenia `(a = b)`.
Typowo operatory przypisania zwracają referencję na `*this` aby umożliwić przypisania łańcuchowe:

```cpp
s1 = s2 = s3 = empty;
// s1 = (s2 = (s3 = empty));
```

W takim ciągu nastąpi:
* przypisanie `empty` do `s3`, co zwróci referencję na obiekt `s3`.
* przypisanie `s3` do `s2`, co zwróci referencję na obiekt `s2`
* przypisanie `s2` do `s1` zwracając referencję na `s1` (nieużywaną).

Podobnie jak przy konstruktorze, jeżeli programista nie dostarczy swojego, to kompilator, o ile może, 
generuje niejawny operator przypisania. Taki operator kopiuje pole po polu. 
Ponownie, w przypadku klasy `DynamicStack`, taki operator _zawłaszczy sobie_ wkaźnik na dane stosu
i jest niepoprawny!

## Przenoszenie obiektów

Czasami wiadomo, że obiekt, z którego kopiujemy, umrze zaraz po jego skopiowaniu.
Dzieje się tak na przykład, gdy:
1) zwracamy lokalny obiekt przez wartość z funkcji
```cpp
std::vector<int> get_v();

int main() {
  std::vector<int> values;
  values = get_v(); // skopiowanie obiektu zwróconego z funkcji do zmiennej values 
}

std::vector<int> get_v() {
  std::vector<int> v = {1, 2, 3};
  return v; // zwrócenie obiektu, wiadomo że natychmiast potem zmienna v będzie niszczona
}
```

2) Kopiujemy obiekt tymczasowy
```cpp
int main() {
  std::vector<int> values = std::vector<int>{1, 2, 3};
  values = std::vector<int>{4, 5};
}
```

W takich sytuacjach kopiowanie jest nadmiarowe i nieoptymalne w przypadku klas zarządzających dynamicznymi zasobami. 
Można by przecież _przejąć_ zasoby z prawej strony przypisania, które i tak zaraz zostaną zwolnione.

Konstruktory kopiujące i operatory przeniesienia przyjmują jako argumenty referencje.
Nie wiadomo czy te referencje odnoszą się do obiektów, które jeszcze pożyją czy też do takich, które zaraz umrą.
Dlatego C++11 wprowadził nowy typ referencji: `T&&` czyli referencje na r-wartości (wartości tymczasowe).

Tak jak zwykłe referencje, `T&&` muszą być zainicjalizowane w momencie tworzenia. W przeciwieństwie do `T&`
mogą być zainicjalizowane **tylko** wartościami tymczasowymi.

```cpp
void foo(int& rx) {}

void goo(int&& rrx) {}

int get() { return 3; }

int main() {
    int x = 0;  // l-wartość

    int& r1 = x;
    // int& r2 = get();  //! zwykła referencja inicjalizowana wartością tymczasową
    // int& r3 = 3;      //! zwykła referencja inicjalizowana wartością tymczasową

    // int&& rr1 = x;    //! referencja na r-wartość inicjalizowana l-wartością
    int&& rr2 = get();
    int&& rr3 = 3;

    foo(x);
    // foo(get());       //! zwykła referencja inicjalizowana wartością tymczasową
    // foo(3);           //! zwykła referencja inicjalizowana wartością tymczasową

    // goo(x);           //! referencja na r-wartość inicjalizowana l-wartością
    goo(get());
    goo(3);

    return 0;
}
```

Mając ten fantastyczny mechanizm języka, możemy dodatkowo przeładować konstruktor kopiujący i operator `=`.
Wersje przyjmujące `T&&` będą używane tylko, jeżeli po prawej stronie będzie wartość tymczasowa, której zasoby można 
wykorzystać!

### Konstruktory przenoszące

Konstruktorem przenoszącym jest jednoargumentowy konstruktor klasy `T`, przyjmujący `T&&` jako parametr, np.:

```cpp
DynamicStack(DynamicStack&& other)
    : capacity(other.capacity),
      size(other.size),
      tab(other.tab)
{
    other.capacity = 0;
    other.size = 0;
    other.tab = nullptr;
}
```
Source: [dynamicstack_move.cpp](dynamicstack_move.cpp)

Będzie wywoływany w momencie, kiedy tworzymy nowy obiekt inicjalizując go obiektem tymczasowym tej samej klasy. 

Konstruktor przenoszący, _kradnąc zasoby_, musi pozostawić obiekt źródłowy w poprawnym stanie. 
Ten, niedługo zostanie zniszczony. Jego destruktor będzie oczekiwał obiektu w poprawnym stanie.
Dla klas wspierających przenoszenie trzeba rozważyć, jak będzie wyglądał ten poprawny, przeniesiony stan.
Stąd warunek w destruktorze:

```cpp
~DynamicStack()
{
    if (tab) delete[] tab;
}
```

### Operatory przeniesienia

W sytuacji, kiedy do już istniejącego obiektu przypisujemy wartość tymczasową, 
wykonany zostanie **operator przeniesienia**. Wygląda podobnie do operatora przypisania, 
jedyna różnica to typ referencji:

```cpp
DynamicStack& operator=(DynamicStack&& other)
{
    if (this == &other) return *this;
    delete[] tab;
    capacity = other.capacity;
    size = other.size;
    tab = other.tab;
    other.capacity = 0;
    other.size = 0;
    other.tab = nullptr;
    return *this;
}
```
Source: [dynamicstack_move.cpp](dynamicstack_move.cpp)

Operator przeniesienia też musi pozostawić obiekt źródłowy w poprawnym, przeniesionym stanie.

W przeciwieństwie do konstruktora przenoszącego w momencie wywołania tego operatora obiekt docelowy istnieje.
Trzeba go posprzątać, stąd dealokacja tablicy na początku funkcji.

> _Samoprzeniesienie_, przed którym bronimy się w pierwszej linii operatora przenoszącego,
> jest możliwe za pomocą wyrażenia `x = std::move(x)`.

### Funkcja `std::move`

Czasami wygodnie jest jawnie przenieść obiekt będący l-wartością do innej zmiennej, nowej lub już istniejącej. 
Można do tego wykorzystać funkcję biblioteczną `std::move`:

```cpp
T source = make_T();
T other = std::move(source); // konstruktor przenosi source do nowego obiektu other
T another;
another = std::move(other);  // operator przenosi other do another
```

Ta funkcja to nic innego jak wykwintne rzutowanie argumentu typu `T&` na typ `T&&`. W dużym uproszczeniu:

```cpp
T&& move(T& val) {
  return static_cast<T&&>(t);
}
```

Typowe zastosowanie to przeniesienie argumentu do funkcji, unikając głębokiej kopii: 

```cpp
std::vector<std::string> v;
std::string str = "hey!";
v.push_back(str); // wywołuje push_back(const T& value) - wewnętrznie wektor kopiuje string 
v.push_back(std::move(str)); // string jest przenoszony do wektora, nie następuje alokacja i kopia znaków 
```

## Konstruktory i operatory generowane niejawnie

Dla prostych klas niedefiniujących żadnych z powyższych funkcji specjalnych kompilator sam je wygeneruje.

```cpp
class M { ... };

class A {
  M m;
public:
  A() {}
}

int main()
{
    A a, b;

    A copy = a;
    A moved = std::move(a);

    copy = b;
    moved = std::move(b);

    return 0;
}
```

Taką klasę można naturalnie kopiować i przenosić. Niejawnie wygenerowane konstruktory i operatory kopiują
lub przenoszą pole po polu.

Można jawnie wymuszać generowanie lub niegenerowanie tych szczególnych metod, 
korzystając ze składni `= default` lub `= delete`:

```cpp
class A {
  M m;
public:
  A() = default; 
  ~A() = default;
  
  A(const A& other) = delete;
  A(A&& other) = default;
   
  A& operator=(const A& other) = delete;
  A& operator=(A&& other) = default;
}
```

Obiekty takiej klasy będą przenoszalne, ale niekopiowalne!

Zdefiniowanie lub usunięcie jednej z tych składowych wpływa na generację reszty przez kompilator.

1) jawny destruktor, konstruktor kopiujący lub operator przypisania blokuje generację konstruktora i operatora przenoszącego
2) jawny konstruktor lub operator przenoszący blokuje generację konstruktora kopiującego i operatora przypisania

Efekty częściowego zdefiniowania mogą być bardzo nieoczywiste. 
Warto pobawić się przykładem: [implicit_members.cpp](implicit_members.cpp) selektywnie dodając funkcje.

## Reguła 5/0

Mówiąc o klasach, które zarządzają zasobami, tak jak np. `DynamicStack` warto wspomnieć o bardzo użytecznej regule, 
znanej jako _rule of 5/0_:

> Jeżeli musisz jawnie zdefiniować (lub usunąć) destruktor, konstruktor kopiujący, operator przypisania, 
> konstruktor przenoszący lub operator przeniesienia
> to prawdopodobnie musisz zdefiniować (lub usunąć) wszystkie 5 funkcji.

Czyli albo definiujemy wszystko, albo nic. Często zdarza się, że rozpatrzymy i zaimplementujemy zwalnianie zasobów
w destruktorze, ale nie pomyślimy, czy domyślne kopiowanie lub przeniesienie jest poprawne. Ta zasada pomaga.

Dla obiektów niewspierających operacji przeniesienia, zasada może być okrojona do _reguły 3/0_.

[//]: # (### TODO Copy/move elision)

## Nagłówek `<memory>` i sprytne wskaźniki

Zarządzanie dynamicznie alokowanym obiektem lub tablicą obiektów jest niezwykle powszechne.
Do tego, jak widzieliśmy na poprzednim wykładzie, ręczne operowanie wskaźnikami jest podatne na błędy.
Łatwo dwukrotnie zwolnić obiekt lub go nie zwolnić.

Dzięki semantyce przenoszenia biblioteka standardowa mogła dostarczyć typy, zachowujące się jak wskaźniki,
które zarządzają czasem życia obiektu automatycznie.

### `std::unique_ptr`

Pierwszy, najważniejszy typ to unikalny wskaźnik `std::unique_ptr`, który zwlania obiekt wskazywany
podczas swojej destrukcji. Ginie wskaźnik = ginie bufor. Nie trzeba ręcznie go zwalniać.

```cpp
{
  std::unique_ptr<int> ptr = std::make_unique<int>(3);
  std::unique_ptr<int[]> tab = std::make_unique<int[]>(10);
  
  *ptr = 3;
  for (int i = 0; i < 10; ++i) tab[i] = i;
  
  // ...
} // desturkcja ptr i tab zwalnia obiekty ze sterty
```

Elementem typu wskaźnika jest typ wskazywanego obiektu. Podobnie jak w przypadku `std::vector<T>` trzeba go podać.
`std::make_unique` jest funkcją pomocniczą, która alokuje obiekt, przyjmując parametry do jego inicjalizacji
jako argumenty i zwraca, opakowując go w sprytny wskaźnik.

Tak samo, jak w przypadku zwykłych wskaźników obiekt typu `std::unique_ptr<T>` może mieć wartość `nullptr`.
Jest to też wartość domyślna nowo utworzonego wskaźnika.
Przypisanie do niego `nullptr` zwolni wskazywany obiekt.

```cpp
std::unique_ptr<int> ptr;       // nullptr
ptr = std::make_unique<int>(3); // alokacja
ptr = nullptr;                  // zwolnienie
```

Obiekty typu `std::unique_ptr<T>` są **niekopiowalne**. Dzięki temu nie ma możliwości podwójnego zwolnienia bufora.
Możne je natomiast naturalnie przenosić, a dzięki temu przekazywać do funkcji i zwracać (bez kopii).

```cpp
// std::unique_ptr<int> p2 = ptr; //!
std::unique_ptr<int> p2 = std::move(ptr);
```

Mówimy, że wskaźnik unikalny jest odpowiedzialny za czas życia obiektu (jest jego właścicielem).
Jeżeli chcemy gdzieś przesłać wskazywany obiekt, bez przeniesienia tej odpowiedzialności
wystarczy przekazać surowy wskaźnik `T*` lub referencję `T&`.

### `std::shared_ptr`

W niektórych programach ciężko określić, który moduł jest odpowiedzialny za czas życia danego obiektu dynamicznego
i wygodnie byłoby mieć kilku właścicieli. Kto ma wtedy zwolnić obiekt? Ostatni żyjący właściciel.

Do tego służy drugi biblioteczny typ wskaźnika: `std::shared_ptr`. Wskaźniki tego typu można kopiować.
Wewnętrznie, `std::shared_ptr` zlicza instancje pokazujące na dany bufor. Na kopii inkrementuje licznik,
na destrukcji, wyzerowaniu itp.: dekrementuje. Obiekt zostanie zwolniony wraz ze śmiercią ostatniej
instancji wskaźnika (licznik = 0).

```cpp
class Point
{
    float x, y;
public:
    Point(float a, float b) : x{a}, y{b} {}
};

int main()
{
    std::shared_ptr<Point> ptr = std::make_shared<Point>(1.0, 2.0);  // counter = 1, alokacja
    std::shared_ptr<Point> ptr2 = ptr;                               // counter = 2
    ptr = nullptr;                                                   // counter = 1
    return 0;
}                                                                    // counter = 0, dealokacja
```

Source: [shared_ptr.cpp](shared_ptr.cpp)

## Składowe statyczne

Klasa może posiadać pola i metody statyczne, oznaczone słowem kluczowym `static`.
Takie pola i metody nie są związane z konkretnym obiektem. Są jedynie widoczne w przestrzeni `NazwaKlasy::`.
Pola statyczne to tak naprawdę zmienne globalne, których użycia trzeba prefixować nazwą klasy.
Metody statyczne to zwykłe funkcje, których wywołania trzeba poprzedzać nazwą klasy.

```cpp
class Entry {
 static int count; // deklaracja
public:
 static int getCount() { return count; }

 Entry() { ++count; }

 ~Entry() { --count; }
};

int Entry::count = 0; // definicja
```
Source: [static_members.cpp](static_members.cpp)

Powyższa klasa zlicza swoje instancje w zmiennej globalnej `int Entry::count`.
Definicja pól statycznych zawsze musi być umieszczona poza klasą. Najczęściej w pliku `*.cpp` zawierającym
implementację danej klasy.
