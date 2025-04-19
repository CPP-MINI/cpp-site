---
title: "L5"
date: 2025-04-19T17:00:00+02:00
weight: 50
---

# Laboratorium 5
## STL

Na tym laboratorium twoim zadaniem będzie zaimplementowanie klas związanych z filmami.

Skorzystaj z dostarczonego pliku [main.cpp](src/main.cpp), w którym umieszczone zostały testy do wszystkich czterech etapów zadania.  
Po zakończeniu implementacji konkretnego etapu odkomentuj odpowiadającą mu część funkcji `main()` i porównaj swój wynik z oczekiwanym (**pamiętaj o załączeniu stworzonych przez ciebie plików w main.cpp**).

Tym razem nie został dostarczony żaden plik startowy do żadnego z etapów zadania. Klasy powinny być napisane od zera.

**Uwaga:** Zamiast `Makefile` napisz tym razem `CMakeLists.txt`.

### Etap 1: Implementacja klasy `Movie` (część 1)

W pliku `Movie.hpp` zaimplementuj klasę szablonową `Movie`, która przechowuje informacje o pojedynczym filmie.
Typem szablonowym powinien być `RatingType` reprezentujący typ, w jakim przechowywana jest pojedyncza ocena filmu (docelowo będzie to np. `double` lub `int`).

Klasa powinna zawierać następujące elementy:

**Struktura zagnieżdżona**:
- Zaimplementuj strukturę `Director` wewnątrz klasy `Movie`, która powinna przechowywać:
    - `std::string name` – imię i nazwisko reżysera,
    - `int numberOfOscars` – liczba zdobytych Oscarów.
- Struktura powinna posiadać konstruktor inicjalizujący oba te pola na podstawie argumentów o tych samych typach.

**Prywatne pola**:
- `std::string title` – tytuł filmu,
- `int year` – rok premiery,
- `std::variant<Director, std::string> director` – reżyser filmu (może być albo struktura `Director`, albo tylko imię jako `std::string`),
- `std::optional<std::string> description` – opcjonalny opis filmu,
- `std::list<RatingType> ratings` – lista ocen filmu.

**Konstruktor**:
- Konstruktor przyjmujący: tytuł, rok, reżysera (powinna być możliwość podania dowolnego z dwóch typów wyspecyfikowanych w `std::variant`) oraz opcjonalnie opis (pamiętaj o wybraniu odpowiedniej wartości domyślnej - patrz `std::optional`).

**Gettery**:
- `getTitle()`, `getYear()`, `getDescription()`, `getDirector()`, `getRatings()` – zwracające bezpośrednio wartości odpowiednich pól.

Oczekiwane wyjście etapu 1:
```
Movie1 info:
Title: Inception
Year: 2010
Director: Christopher Nolan (Oscars: 2)
Description: Paprika and HSM3 rip-off

Movie2 info:
Title: Interstellar
Year: 2014
Director: Christopher Nolan
```

---

### Etap 2: Implementacja klasy `Movie` (część 2)

W tym etapie rozbuduj klasę `Movie` o dodatkowe funkcjonalności:

**Metody**:
- `getAverageRating()` – zwraca średnią ocenę (do iteracji po liście użyj `ranged-for-loop`),
- `getTopRating()` – zwraca najwyższą ocenę (do iteracji po liście użyj iteratora).

**Operatory**:
- `operator<` (zdefiniowany w klasie) – porównuje filmy alfabetycznie po tytule, a jeśli są równe, to po roku.
- `operator==` (zdefiniowany w klasie) – porównuje tytuł i rok.
- `operator+` (zdefiniowany w klasie) – jako argument przyjmuje zmienną typu `RatingType` i dodaje ocenę do listy ocen i zwraca referencję do filmu (powinien umożliwiać łańcuchowe dodawanie ocen - patrz `main.cpp`).
- `operator<<` (zdefiniowany poza klasą) – wypisuje film w formacie:
  ```
  <Tytuł> (<Rok>), Director: <Imię Nazwisko> (Oscars: <Liczba Oscarów>), Avg: <średnia ocena>, Top: <najwyższa ocena>
  Description: <opcjonalny opis>
  ```
  gdzie:
    - `(Oscars: <Liczba Oscarów>)` powinno być pominięte, jeżeli reżyser dla tego filmu reprezentowany jest tylko jako `std::string`;
    - druga linijka zawierająca `Description: <opcjonalny opis>` występuje tylko wtedy gdy film posiada opis.

  **Uwaga:** Nie musisz samodzielnie dbać o wypisywanie zmiennych z dokładnością do 2 miejsc po przecinku, ponieważ jest to ustawione na początku funkcji `main()`.

Oczekiwane wyjście etapu 2:
```
Movie1 Average Rating: 8.50
Movie1 Top Rating: 9.00
Movie2 Average Rating: 7.50
Movie2 Top Rating: 8.00

Movie1 operator<< output:
Inception (2010), Director: Christopher Nolan (Oscars: 2), Avg: 8.50, Top: 9.00
Description: Paprika and HSM3 rip-off

Movie2 operator<< output:
Interstellar (2014), Director: Christopher Nolan, Avg: 7.50, Top: 8.00

Movies are not equal
Movie1 comes before Movie2
```

---

### Etap 3: Implementacja klasy `MovieCollection` (część 1)

W plikach `MovieCollection.hpp` i `MovieCollection.cpp` zaimplementuj klasę `MovieCollection`, która reprezentuje kolekcję filmów pogrupowanych według pierwszej litery tytułu.
Pojedynczy film reprezentowany jest przez klasę `Movie<double>`.

Klasa powinna zawierać następujące elementy:

**Prywatne pole**:
- `std::map<char, std::vector<Movie<double>>> moviesByLetter` – mapa, której kluczem jest litera alfabetu, a wartością wektor filmów zaczynających się na daną literę.

**Publiczne metody**:
- `getMoviesByLetter()` – getter zwracający referencję do przechowywanej mapy,
- `getAllMovies()` – zwraca wszystkie filmy jako jeden spłaszczony wektor,
- `addMovie(const Movie<double>& movie)` – dodaje film do kolekcji poprzez dodanie go do odpowiedniego wektora odpowiadającemu pierwszej literze tytułu,

**Operator**:
- `operator<<` (zdefiniowany poza klasą) – wypisuje zawartość kolekcji w postaci:
  ```
  === <litera1> ===
  <film1>
  <film2>
  ...
  === <litera2> ===
  <film1>
  <film2>
  ...
  === <litera3> ==
  ...
  ```

Oczekiwane wyjście etapu 3:
```
All movies in collection:
=== D ===
Dunkirk (2017), Director: Christopher Nolan (Oscars: 2), Avg: 8.50, Top: 9.00
=== I ===
Isle of Dogs (2018), Director: Wes Anderson, Avg: 7.33, Top: 7.50
Interstellar (2014), Director: Christopher Nolan, Avg: 7.50, Top: 8.00
Inception (2010), Director: Christopher Nolan (Oscars: 2), Avg: 8.50, Top: 9.00
Description: Paprika and HSM3 rip-off
=== T ===
The Dark Knight (2008), Director: Christopher Nolan (Oscars: 2), Avg: 9.17, Top: 9.50
Description: We live in a society.
Tenet (2020), Director: Christopher Nolan, Avg: 7.50, Top: 8.00
Description: Don't even try to understand it.
The Grand Budapest Hotel (2014), Director: Wes Anderson (Oscars: 1), Avg: 8.33, Top: 8.50
Description: Pastel chaos and fancy mustaches.

Total number of movies: 7

Movies under letter 'I':
Isle of Dogs (2018), Director: Wes Anderson, Avg: 7.33, Top: 7.50
Interstellar (2014), Director: Christopher Nolan, Avg: 7.50, Top: 8.00
Inception (2010), Director: Christopher Nolan (Oscars: 2), Avg: 8.50, Top: 9.00
Description: Paprika and HSM3 rip-off
```

---

### Etap 4: Implementacja klasy `MovieCollection` (część 2)

W tej części rozszerz klasę `MovieCollection` o dodatkowe metody wykorzystujące algorytmy STL.  
**W każdej funkcji należy wykorzystać dokładnie wskazany algorytm STL**.

**Metody**:
- `sortMovies()` – sortuje wewnętrzne wektory filmów dla każdej litery (użyj `std::sort`),
- `removeMoviesOlderThan(char letter, int year)` – usuwa z grupy filmów zaczynającej się na podaną literę filmy starsze niż podany rok (użyj `std::remove_if`),
- `getAverageTopRating()` – zwraca średnią z najwyższych ocen wszystkich (użyj `getAllMovies()` i `std::accumulate` do policzenia sumy najwyższych ocen),
- `getMoviesByDirector(const std::string& director)` – zwraca wszystkie filmy danego reżysera jako wektor (użyj `std::copy_if`),
- `findMovieWithAverageAbove(double threshold)` – znajduje pierwszy film, którego średnia ocena przekracza podany próg (użyj `std::find_if`).

#### Użycie funktora z algorytmem z STL

W wykładzie w kilku miejscach wspomniane jest pojęcie funktora. Jest to klasa posiadająca zdefiniowany `operator()` co pozwala nam traktować instancję tej klasy jak funkcję, którą możemy wywoływać.
W takim funktorze możemy przechowywać dodatkowo wartości potrzebne do ewaluacji funkcji jako zmienne klasowe. Dla przykładu, jeżeli chciałbym zaimplementować funktor sprawdzający, czy liczba jest większa od `x`, liczba `x` może zostać podana w konstruktorze funktora i zapisana w klasie, a następnie użyta w czasie ewaluacji wartości operatora.

Poniżej zobrazowany jest przykład implementacji funktora, który sprawdza, czy dany film ma średnią ocenę wyższą niż pewien próg zdefiniowany przy konstrukcji funktora:
```cpp
struct HasAverageAbove {
    double threshold;
    explicit HasAverageAbove(double threshold) : threshold(threshold) {}
    
    bool operator()(const Movie<double>& movie) const {
        return movie.getAverageRating() > threshold;
    }
};
```

Natomiast tak wyglądałaby implementacja wspomnianej wcześniej funkcji `findMovieWithAverageAbove(double threshold)` w `MovieCollection` wykorzystująca taki funktor (zdefiniowany lokalnie) i funkcję `std::find_if`:
```cpp
std::optional<Movie<double>> MovieCollection::findMovieWithAverageAbove(double threshold) const {
    struct HasAverageAbove {
        double threshold;
        explicit HasAverageAbove(double threshold) : threshold(threshold) {}

        bool operator()(const Movie<double>& movie) const {
            return movie.getAverageRating() > threshold;
        }
    };

    auto allMovies = getAllMovies();
    auto it = std::find_if(allMovies.begin(), allMovies.end(), HasAverageAbove(threshold));
    if (it != allMovies.end()) {
        return *it;
    }
    return std::nullopt;
}
```

Przekopiuj powyższą funkcję do swojego kodu i przeanalizuj jej zawartość. Wzorując się na niej, możesz analogicznie zaimplementować resztę wymaganych funkcji.

Oczekiwane wyjście etapu 4:
```
Found a movie with average rating above 8.0:
Dunkirk (2017), Director: Christopher Nolan (Oscars: 2), Avg: 8.50, Top: 9.00

Movies after sorting:
=== D ===
Dunkirk (2017), Director: Christopher Nolan (Oscars: 2), Avg: 8.50, Top: 9.00
=== I ===
Inception (2010), Director: Christopher Nolan (Oscars: 2), Avg: 8.50, Top: 9.00
Description: Paprika and HSM3 rip-off
Interstellar (2014), Director: Christopher Nolan, Avg: 7.50, Top: 8.00
Isle of Dogs (2018), Director: Wes Anderson, Avg: 7.33, Top: 7.50
=== T ===
Tenet (2020), Director: Christopher Nolan, Avg: 7.50, Top: 8.00
Description: Don't even try to understand it.
The Dark Knight (2008), Director: Christopher Nolan (Oscars: 2), Avg: 9.17, Top: 9.50
Description: We live in a society.
The Grand Budapest Hotel (2014), Director: Wes Anderson (Oscars: 1), Avg: 8.33, Top: 8.50
Description: Pastel chaos and fancy mustaches.

Movies after removing movies before 2015 under letter 'I':
=== D ===
Dunkirk (2017), Director: Christopher Nolan (Oscars: 2), Avg: 8.50, Top: 9.00
=== I ===
Isle of Dogs (2018), Director: Wes Anderson, Avg: 7.33, Top: 7.50
=== T ===
Tenet (2020), Director: Christopher Nolan, Avg: 7.50, Top: 8.00
Description: Don't even try to understand it.
The Dark Knight (2008), Director: Christopher Nolan (Oscars: 2), Avg: 9.17, Top: 9.50
Description: We live in a society.
The Grand Budapest Hotel (2014), Director: Wes Anderson (Oscars: 1), Avg: 8.33, Top: 8.50
Description: Pastel chaos and fancy mustaches.

Average of top ratings across all movies: 8.50

Movies directed by Christopher Nolan:
Dunkirk (2017), Director: Christopher Nolan (Oscars: 2), Avg: 8.50, Top: 9.00
Tenet (2020), Director: Christopher Nolan, Avg: 7.50, Top: 8.00
Description: Don't even try to understand it.
The Dark Knight (2008), Director: Christopher Nolan (Oscars: 2), Avg: 9.17, Top: 9.50
Description: We live in a society.

Movies directed by Wes Anderson:
Isle of Dogs (2018), Director: Wes Anderson, Avg: 7.33, Top: 7.50
The Grand Budapest Hotel (2014), Director: Wes Anderson (Oscars: 1), Avg: 8.33, Top: 8.50
Description: Pastel chaos and fancy mustaches.
```

---

### Rozwiązanie

[Movie.hpp](solution/Movie.hpp)  
[MovieCollection.hpp](solution/MovieCollection.hpp)  
[MovieCollection.cpp](solution/MovieCollection.cpp)  
[main.cpp](solution/main.cpp)  
[CMakeLists.txt](solution/CMakeLists.txt)  
