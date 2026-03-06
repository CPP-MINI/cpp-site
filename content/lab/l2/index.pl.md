---
title: "L2"
date: 2022-02-05T17:26:02+01:00
weight: 30
---

# Laboratorium 2
## Translacja

W tym zadaniu stworzysz prosty projekt w C++ składający się z:
- Dwóch programów, z czego na jeden z nich składać się będzie wiele plików `.cpp`.
- Biblioteki statycznej.
- Biblioteki współdzielonej.

Ani podczas tego laboratorium, ani podczas któregokolwiek przyszłego (o ile nie będzie to wprost sprecyzowane), nie używaj standardowej biblioteki C (czyli np. `stdio.h`, `string.h` itd.).
W pełni dozwolone (o ile nie będzie to wprost zabronione) jest i będzie korzystanie z biblioteki C++ (czyli np. `vector`, `string`).

**Skorzystaj z następującego kodu startowego**: [greeter.cpp](src/greeter.cpp) [program_2.cpp](src/program_2.cpp).

### Program z wieloma plikami
Utwórz trzy nowe pliki: `program_1.cpp`, `vars.hpp` i `vars.cpp`.
Wszystkie te pliki kompilowane będą do jednego programu o nazwie `program_1`.
W pliku `vars.cpp` utwórz dwie zmienne globalne typu `int` o nazwach `global_extern` i `global_static`.
Pierwsza z nich jest zwykłą zmienną, a druga statyczną.
Obie zainicjuj wartością 0.
Utwórz też w tym pliku dwie funkcje.
- `void inc_vars()`, które wypisuje na ekran „Increasing...”, a potem zwiększa wartość obu zmiennych o 1.
- `void print_vars()`, które wypisuje wartości obu zmiennych w następującym formacie:
  ```
  global_extern: <global_extern>
  global_static: <global_static>
  ```
  (Oczywiście bez znaków `<` i `>` -- one tylko pokazują, że nie mamy na myśli ciągu, a wartość zmiennej).

Napisz plik `vars.hpp`, który udostępnia napisane funkcje i zmienną `global_extern`.
Pamiętaj m.in. o barierach kompilacji.

Następnie napisz plik `progam_1.cpp`.
Powinna się w nim znaleźć funkcja `main`, a w niej wywołanie funkcji `print_vars()`, `inc_vars()` i znowu `print_vars()`.
Potem wypisz zawartość zmiennej `global_extern` (nie używając funkcji z `vars.hpp`).

Skompiluj program przy pomocy polecenia `g++` z linii poleceń.
Najpierw utwórz skompilowane obiekty, a potem zlinkuj je do w jeden plik `program_1`.

### Makefile
Zautomatyzuj powyższy proces kompilacji przy pomocy systemu `make`.
Utwórz plik `Makefile` i zdefiniuj w nim cele:
- `vars.o`
- `program_1.o`
- `program_1`
Każdy z nich powinien mieć odpowiednie wymagania i polecenie budujące.
W kolejnych etapach podobnie pliki `.cpp` najpierw kompiluj do plików `.o`,
    a następnie je linkuj.
W prawdziwych projektach pozwala to na przyśpieszenie procesu kompilacji -- jeśli zmienił się tylko jeden plik `.cpp`, to tylko on będzie musiał być kompilowany.
U nas jest to oczywiście bez znaczenia, bo projekt jest mikroskopijny.

Dodatkowo w pliku zdefiniujemy dwa cele „oszukańcze”, tzn. takie, które nie odnoszą się do żadnego pliku.
Pierwszym z nich będzie `clean`.
Pozwoli on nam na szybkie usuwanie wszystkich plików wynikowych kompilacji poleceniem `make clean`.
Aby zdefiniować ten cel, dodajemy do naszego `Makefile`:
```
.PHONY: clean
clean:
    rm -f program_1 ... # dodaj pozostałe pliki wynikowe kompilacji
```

**UWAGA 1**: Upewnij się, że cel `clean` nie usuwa przypadkiem plików z kodem źródłowym -- nie o to nam tutaj w końcu chodzi.

Linijka `.PHONY: clean` mówi, że `clean` jest celem, który nie produkuje pliku `clean`, a po prostu się tak nazywa. Dzięki temu etap ten nie zostanie pominięty, nawet jeśli z jakiegoś powodu w naszym katalogu znajdzie się plik `clean`.

W podobny sposób zdefiniuj cel `all`, który na ten moment zawiera tylko `program_1`.
W późniejszym etapie dodamy tam też `program_2`.
Umieść go na samej górze pliku `Makefile` -- spowoduje to, że przy wpisaniu polecenia `make`,
właśnie ten cel będzie wybierany domyślnie.

### Biblioteka Statyczna
W kodzie startowym znajduje się plik `greeter.cpp`.
Zapoznaj się z jego treścią.
Utwórz odpowiedni plik `greeter.hpp`, który udostępnia funkcje zdefiniowane w `greeter.cpp`.
Nie zmieniaj pliku `greeter.cpp`.
Pliki te składać się będą na bibliotekę statyczną (static library) `libgreeter.a`.
Zmodyfikuj `program_1.cpp` tak, aby przed dotychczasową funkcjonalnością na konsolę wypisywany był output wszystkich trzech funkcji z `librgreeter.a`.
Dodaj do pliku `Makefile` instrukcje budujące tę bibliotekę
oraz zmodyfikuj budowanie `program_1` tak, aby była ona do niego linkowana.
Zaktualizuj także cel `clean`.

Dodatkowo wprowadzimy teraz pewne udogodnienie w pliku `Makefile`.
Na sam jego szczyt dodaj linijkę
```
COMPILER=g++
```

I każde dotychczasowe wystąpienie ciągu `g++` w pliku zamień na `${COMPILER}`.
Zadeklarowaliśmy teraz oczywiście zmienną `COMPILER` w `Makefile`,
a poprzez `${COMPILER}` odwołujemy się do niej.
Pozwala to łatwo zmienić kompilator (np. na `clang++`) na jakiś inny modyfikując tylko jedną linijkę, a nie cały plik.

### Biblioteka Współdzielona
Utwórz pliki `rome.cpp` i `rome.hpp`.
Będą to pliki biblioteki współdzielonej (shared library) o nazwie `librome.so`.
Biblioteka ta powinna udostępniać w przestrzeni nazw `rome`:
- Strukturę `Province`, zawierającą dwa pola.
  - `std::string name`, czyli nazwę prowincji.
  - `std::vector<std::string> cities`, czyli listę miast w prowincji.
- Funkcję `Province create_province(std::string name)`, która tworzy obiekt prowincji bez miast o podanej nazwie.
- Funkcję `void add_city(Province* province, std::string city)`, która dodaje do przekazanej prowincji jedno miasto.
- Funkcję `std::string description(Province* province)`, która tworzy ciąg znaków postaci
  ```
  <province>: <city_1>, <city_2>, ..., <city_n>.
  ```
  Zwróć uwagę na kropki i przecinki w formacie.
  Czyli dla prowincji „Ægyptus” z miastami „Alexanria” i „Ptolemais” poprawnym wynikiem jest
  ```
  Ægyptus: Alexandria, Ptolemais.
  ```

**UWAGA 2**: W C++ definicja i deklaracja zmiennej, której typem jest pewna struktura, następuje jako
```
Province variable;
```
W przeciwieństwie do C, gdzie mielibyśmy
```
struct Province variable;
```
Nie jest więc potrzebne żadne kombinowanie z `typedef`, jakie mogło się pojawić na Programowaniu 1.

**UWAGA 3**: Nagłówki funkcji tej biblioteki są bardziej w stylu C, nie C++. Zwykle w C++ unikamy za wszelką cenę czystych wskaźników, ale o tym będzie dopiero na późniejszych zajęciach. Na ten moment musimy się zadowolić tym, co wiemy z poprzedniego semestru.


Dodaj do pliku `Makefile`:
- Zasady budujące bibliotekę współdzieloną `librome.so`.
- Zasady budujące program `program_2`.
  Plik `program_2.cpp` jest dostarczony wraz z kodem startowym.
  Zapoznaj się z jego treścią.
  `program_2` powinien linkować biblioteki `librome.so` i `libgreeter.a`.
- Zaktualizuj cel `clean`.
- Dodaj `program_2` do celu `all`.

Zbuduj `program_2` i go uruchom.
Pamiętaj, że przy uruchamianiu programu linkującego bibliotekę dynamiczną, będzie on jej szukał domyślnie w katalogach systemowych. U nas jednak jest ona w obecnym katalogu. Można to zmienić modyfikując zmienną środowiskową `LD_LIBRARY_PATH`, która zawiera listę dodatkowych katalogów do przeszukania w tym celu.

Rozwiązanie: [Makefile](solution/Makefile) [greeter.cpp](solution/greeter.cpp) [greeter.hpp](solution/greeter.hpp) [rome.cpp](solution/rome.cpp) [rome.hpp](solution/rome.hpp) [program_1.cpp](solution/program_1.cpp) [vars.cpp](solution/vars.cpp) [vars.hpp](solution/vars.hpp) [program_2.cpp](solution/program_2.cpp).
