---
title: "2026"
date: 2024-03-19T12:00:00+01:00
weight: 2026
url: "/lab/l1/previous-years/2026/"
---

# Zadanie oceniane 1
## Podstawowe elementy biblioteki standardowej

W tym zadaniu stworzysz prosty program w C++ z użyciem klas `vector` i `string` oraz strumieni `cout` i `cin` z biblioteki standardowej. 

Sklonuj repozytorium zgodnie z instrukcją z laboratorium wprowadzającego.
Po wykonaniu każdego etapu skompiluj program z użyciem komendy `make` w terminalu. Wyślij go do repozytorium oraz zgłoś to prowadzącemu, który go sprawdzi. Dopiero po tym przejdź do kolejnego etapu.

W sekcji **Oczekiwane wyjście** znajdują się linie zaczynające się od `<` lub `>`. Oznaczają odpowiednio linie wypisane przez program i wprowadzone przez użytkownika. Twój program również powinien wypisywać te symbole dla czytelności.

## Pliki startowe

[main.cpp](src/main.cpp)

### Etap 1 - `make` i przywitanie (2 pkt)

Stwórz plik `Makefile` tak, aby kompilował program poprawnie. Kompilacja powinna wykonywać się tylko jeśli plik z kodem źródłowym został modyfikowany od momentu ostatniej kompilacji (lub jest to pierwsza kompilacja) (jako wymagania targetu pliku wykonywalnego ustaw pliki z kodem). Po wpisaniu komendy `make clean` plik wykonywalny usuwa się.

Plik z kodem początkowym `main.cpp` zawiera dyrektywy załączenia nagłówków opisujących klasy `vector`, `string` oraz strumienie standardowego wejścia (`cin`) oraz wyjścia (`cout`). Napisz program który poprosi użytkownika o pseudonim i przywita go używając tego pseudonimu.

#### Oczekiwane wyjście:
```
< Podaj pseudonim:
> student
< Witaj, student!
```
### Etap 2 - `std::vector<std::string>` (3 pkt)

W tym etapie użyj `std::vector` do przechowywania ciągów znaków `std::string`. Wczytaj od użytkownika maksymalną liczbę (N) przechowanych pseudonimów. Pytaj użytkownika o pseudonim i dodawaj go do wektora, a następnie wypisuj czytelnie zawartość wektora. Powtarzaj ten proces N razy.

#### Oczekiwane wyjście:
```
< Podaj liczbę użytkowników:
> 2
< Podaj pseudonim:
> student
< Witaj, student!
< Użytkownicy: 1/2
    - student
< Podaj pseudonim:
> nauczyciel
< Witaj, nauczyciel!
< Użytkownicy: 2/2
    - student
    - nauczyciel
```

### Etap 3 - więcej operacji na `std::vector` (2 pkt)

Przed zakończeniem programu usuń jeden po drugim wprowadzone pseudonimy z użyciem metody `.pop_back()`. Pomiędzy każdym usunięciem wypisuj pozostałe pseudonimy jak w etapie 2. Poza wypisywaniem pseudonimów nie wykorzystuj w tym etapie wprowadzonego wcześniej limitu elementów.

*Podpowiedź: możesz użyć metod* `.empty()` *lub* `.size()` *wektora w warunku pętli* `while`*.* 

#### Oczekiwane wyjście:
```
< Podaj liczbę użytkowników:
> 2
< Podaj pseudonim:
> student
< Witaj, student!
< Użytkownicy: 1/2
    - student
< Podaj pseudonim:
> nauczyciel
< Witaj, nauczyciel!
< Użytkownicy: 2/2
    - student
    - nauczyciel
< Usuwanie użytkowników...
< Użytkownicy: 1/2
    - student
< Usuwanie użytkowników...
< Użytkownicy: 0/2
```

### Etap 4 - więcej operacji na `std::string` (2 pkt)

Zamiast usuwać całą zawartość wektora z pseudonimami, pozwalaj użytkownikowi wybierać czy usunąć pseudonim czy zakończyć program. Przyjmuj od użytkownika "pop", "quit" (bez cudzysłowu):
- Program usuwa ostatni pseudonim oraz wypisuje pozostałych użytkowników po otrzymaniu "pop",
- Program kończy się po otrzymaniu "quit",
- Program ponawia prośbę o wprowadzenie komendy po otrzymaniu czegokolwiek innego.

Program kończy się również po usunięciu ostatniego pseudonimu.

*Podpowiedź: operator równości (*`==`*) na* `std::string` *porówuje **zawartość** ciągów znaków! (W odróżnieniu od operatora równości dla dwóch* `char*`*.)*
#### Oczekiwane wyjście:
```
< Podaj liczbę użytkowników:
> 2
< Podaj pseudonim:
> student
< Witaj, student!
< Użytkownicy: 1/2
    - student
< Podaj pseudonim:
> nauczyciel
< Witaj, nauczyciel!
< Użytkownicy: 2/2
    - student
    - nauczyciel
< Wpisz "pop", aby usunąć użytkownika lub "quit" aby wyjść z programu:
> foo
< Wpisz "pop", aby usunąć użytkownika lub "quit" aby wyjść z programu:
> pop
< Użytkownicy: 1/2
    - student
< Wpisz "pop", aby usunąć użytkownika lub "quit" aby wyjść z programu:
> quit
```

### Etap 5 - rozbicie na pliki (1 pkt)

Dodaj kolejną komendę "hack", która podmienia pierwszy pseudonim w wektorze na `haker`. Zaimplementuj to w funkcji zawartej w osobnym pliku `.cpp` (pamiętaj o zawarciu jej deklaracji w osobnym pliku nagłówkowym i dołączeniu go w plikach `.cpp`). Powinna ona przyjmować wskaźnik na `std::string`. Zmodyfikuj plik `Makefile`, aby wciąż kompilował cały program.

Udajemy, że opcja "hack" jest tajna, więc nie jest wymieniona w wiadomości podpowiedzi.
#### Oczekiwane wyjście:
```
< Podaj liczbę użytkowników:
> 2
< Podaj pseudonim:
> student
< Witaj, student!
< Użytkownicy: 1/2
    - student
< Podaj pseudonim:
> nauczyciel
< Witaj, nauczyciel!
< Użytkownicy: 2/2
    - student
    - nauczyciel
< Wpisz "pop", aby usunąć użytkownika lub "quit" aby wyjść z programu:
> hack
< Użytkownicy: 2/2
    - haker
    - nauczyciel
< Wpisz "pop", aby usunąć użytkownika lub "quit" aby wyjść z programu:
> quit
```

## Rozwiązania

[Makefile-etap1-4](solution/Makefile-etap1-4)

[Makefile-etap5](solution/Makefile-etap5)

[haker-etap5.cpp](solution/haker-etap5.cpp)

[haker-etap5.h](solution/haker-etap5.h)

[main-etap1.cpp](solution/main-etap1.cpp)

[main-etap2.cpp](solution/main-etap2.cpp)

[main-etap3.cpp](solution/main-etap3.cpp)

[main-etap4.cpp](solution/main-etap4.cpp)

[main-etap5.cpp](solution/main-etap5.cpp)
