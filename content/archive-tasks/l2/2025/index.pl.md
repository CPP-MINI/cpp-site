---
title: "2025"
date: 2025-03-19T12:00:00+01:00
weight: 2025
url: "/lab/l2/previous-years/2025/"
---

# Zadanie oceniane 2
## Translacja

W tym zadaniu stworzysz prosty projekt w C++ składający się z:
- Dwóch programów
- Biblioteki statycznej z wieloma plikami.
- Biblioteki współdzielonej.

Sklonuj repozytorium zgodnie z instrukcją z laboratorium wprowadzającego.
Najpierw wykonaj pierwszy etap. Wyślij go do repozytorium oraz zgłoś to prowadzącemu, który go sprawdzi. Dopiero po tym przejdź do kolejnego etapu.

W repozytorium znajdziesz jeden plik startowy: `test.cpp`.

## Pliki startowe

[test.cpp](src/test.cpp)

### 1. Biblioteka dynamiczna [4pkt]
Utwórz dwa pliki: `hello.cpp` i `hello.hpp`.
Pierwszy powinien zawierać:
- Definicję zmiennej globalnej statycznej `HELLO_COUNT` inicjowanej zerem.
- Definicję funkcji `void print(std::string name)` w przestrzeni nazw `hello`.
  Funkcja ta najpierw zwiększa `HELLO_COUNT` o 1, a potem wypisuje na stadardowe wyjście wartość licznika oraz powitanie dla `name`
  ```
  <HELLO_COUNT>. Hello <name>.<nowa linia>
  ```
  Czyli np. dla trzeciego wywołania, z argumentem `"Markusz"`, powinna wypisać
  ```
  3. Hello Markusz.<nowa linia>
  ```
W pliku `hello.hpp` udostępnij tę funkcję.

Utwórz plik `main_program.cpp` z funkcją `main()` i wywołaj w niej napisaną funkcję `print` trzy razy z dowolnymi argumentami (np. `"Darius"`, `"Xerxes"`, `"Ataxerxes"`).

Utwórz plik `Makefile` z celami:
- Zmienną `COMPILER` z wartością `g++`. Nie używaj polecenia `g++` bezpośrednio w dalszej części `Makefile`.
- `all` -- teraz tylko będzie tam tylko `main_program`.
- `clean` -- usuwa pliki wynikowe kompilacji
- Cele potrzebne do kompilacji utworzonych plików.
`hello.cpp` należy budować jako bibliotekę **współdzieloną (shared)** o nazwie `libhello.so`, oraz linkować ją do `main_program`.
Kompilację pliku `.cpp` dziel na dwa cele: kompilujący (t.j. tworzący plik `.o`) i linkujący.

Dodaj w komentarzu do `main_program.cpp` polecenie bash, którym uruchomić można ten program z katalogu projektu. Uwzględnij ścieżkę szukania bibliotek współdzielonych.

### 2. Biblioteka współdzielona [6pkt]
Utwórz cztery pliki: `vectors.cpp`, `vectors.hpp`, `strings.cpp` i `strings.hpp`.

W `vectors.cpp` zdefiniuj w przestrzeni nazw `vectors`:
- Funkcję `std::vector<int> reverse(std::vector<int>* old)`, która tworzy nowy `std::vector<int>` o zawartości `old`, ale w odwrotnej kolejności. Upewnij się, że funkcja działa poprawnie dla pustych wektorów (`->size()` zwraca zmienną `unsigned`).
- Funkcję `int max(std::vector<int>* vec)`, która zwraca maksymalny element wektora.
W `vectors.hpp` udostępnij te funkcje.

W `strings.cpp` zdefiniuj w przestrzeni nazw `strings`:
- Zmienną globalną `COMBINE_COUNT` typu `int` inicjowaną zerem.
- Funkcję `std::string combine_strings(std::string s1, std::string s2)`, która zwiększa `COMBINE_COUNT` o 1 oraz konkatenuje podane ciągi `s1` i `s2`. Przy argumentach `"Hello"` i `"world"` zwraca ciąg postaci `Hello world` (konkatenacja i dodanie spacji pomiędzy).
W `strings.hpp` udostępnij tę zmienną i funkcję.

Zaktualizuj `Makefile`:
- Zbuduj bibliotekę statyczną `liboperations.a` z plików `vectors.cpp` i `strings.cpp`. Podziel zadanie w pliku Makefile odpowiednio na cele (kompilacja każdego pliku `.cpp` i utworzenie biblioteki)
- Zbuduj program `test` i zlinkuj do niego `liboperations.a`.
- Zaktualizuj `all` dodając do niego `test`.
- Zaktualizuj `clean`, by usuwał nowe pliki wynikowe kompilacji.

Poprawny wynik uruchomienia programu `test` to:
```
vector: {1, 2, 3, 4, 5, 4}
reversed: reversed empty: {}
max: 5
COMBINE_COUNT: 0
Combining abc and efg: abc efg
COMBINE_COUNT: 1
```

Bon voyage.

## Rozwiązania

[Makefile](solution/Makefile)

[hello.cpp](solution/hello.cpp)

[hello.hpp](solution/hello.hpp)

[main_program.cpp](solution/main_program.cpp)

[strings.cpp](solution/strings.cpp)

[strings.hpp](solution/strings.hpp)

[test.cpp](solution/test.cpp)

[vectors.cpp](solution/vectors.cpp)

[vectors.hpp](solution/vectors.hpp)
