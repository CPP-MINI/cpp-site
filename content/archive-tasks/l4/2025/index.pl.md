---
title: "2025"
date: 2025-03-29T12:00:00+01:00
weight: 30
url: "/lab/l4/previous-years/2025/"
---

# Zadanie oceniane 4 [15 pkt]
## Klasy

W tym laboratorium twoim zadaniem będzie zaprojektowanie klas reprezentujących zadania.

Skorzystaj z dostarczonego pliku [main.cpp](src/main.cpp), w którym umieszczone zostały testy dla wszystkich etapów zadania.
Po zakończeniu implementacji konkretnego etapu odkomentuj odpowiadającą mu część funkcji `main` i porównaj swój wynik z oczekiwanym
(**pamiętaj o załączeniu stworzonych przez ciebie plików w `main.cpp`**).

Dostarczone są również: startowy plik [Makefile](src/Makefile) i startowy plik [Task.hpp](src/Task.hpp) (etap 2 i 3).

## Pliki startowe

[Makefile](src/Makefile)

[Task.hpp](src/Task.hpp)

[main.cpp](src/main.cpp)

**Uwaga:**
- Etapy muszą być wykonywane po kolei.
- Wszystkie implementacje funkcji umieść w plikach `.cpp`.
- W razie wątpliwości co do np. kolejności argumentów lub innych tego typu szczegółów możesz spojrzeć na wywołania w `main.cpp`.

---

### Etap 1: Implementacja klasy `Subtask` [5 pkt]

W plikach `Subtask.hpp` i `Subtask.cpp` zaimplementuj klasę `Subtask`, która reprezentuje pojedyncze pod-zadanie.

Klasa powinna zawierać następujące elementy:

**Prywatne pola**:
- `std::string description` – opis pod-zadania.
- `unsigned int priority` – priorytet zadania (im wyższa liczba, tym wyższy priorytet).
- `bool completed` – informacja, czy zadanie zostało wykonane.

**Konstruktor**:
- Konstruktor przyjmujący opis, opcjonalny priorytet (domyślnie `0`) i opcjonalny status ukończenia (domyślnie `false`).

**Metody publiczne**:
- `void mark_completed()` – oznacza pod-zadanie jako wykonane.
- `bool is_completed()` – zwraca, czy zadanie jest ukończone.
- `unsigned int get_priority()` – zwraca priorytet.
- `void print() const` – wypisuje pod-zadanie w formacie:
```
[x]/[ ] P: <priority>, <description>
```
gdzie `[x]` oznacza pod-zadanie wykonane, a `[ ]` niewykonane.

Oczekiwane wyjście:
```
[ ] P: 0, Go shopping
[x] P: 5, Vacuum
[x] P: 10, Do the dishes

s0: completed=0, priority=0
```

---

### Etap 2: Implementacja klasy `Task` (bez kopiowania i przenoszenia) [5 pkt]

W plikach `Task.hpp` i `Task.cpp` zaimplementuj klasę `Task`, która zarządza listą pod-zadań za pomocą dynamicznie alokowanej jednokierunkowej listy.
Pod-zadania powinny być zawsze przechowywane w kolejności od największego priorytetu.

**Uwaga:** Mimo dynamicznego alokowania pamięci wstrzymaj się na razie od implementowania konstruktora kopiującego, operatora przypisania, konstruktora przenoszącego i operatora przeniesienia.
Elementy te dodasz w czasie wykonywania etapu 3.

**Struktura pomocnicza, której trzeba użyć do przechowywania listy (już gotowa)**:
```
struct SubtaskNode {
    Subtask data;
    SubtaskNode* next;
    SubtaskNode(const Subtask& data);
};
```

**Pola klasy `Task`**:
- `std::string description` – opis zadania.
- `SubtaskNode* head` – wskaźnik na początek listy pod-zadań.

**Konstruktor i destruktor**:
- Konstruktor przyjmujący opis zadania, inicjalizujący zadanie bez żadnych pod-zadań (`head = nullptr`).
- Destruktor odpowiednio czyszczący zaalokowaną pamięć.

**Metody publiczne**:
- `void add_subtask(const Subtask& subtask)` – dodaje pod-zadanie do listy, zachowując kolejność zgodnie z nierosnącym priorytetem.
- `void complete_subtask(unsigned int index)` – oznacza jako ukończone pod-zadanie o wskazanym indeksie (licząc od 0).
- `bool is_completed() const` – zwraca `true`, jeśli wszystkie pod-zadania są ukończone, w przeciwnym razie `false`.
- `void clear()` – usuwa wszystkie pod-zadania z listy.
- `void print() const` – wypisuje zadanie oraz jego pod-zadania w formacie:
```
[ ]/[x] <description>
    - [ ]/[x] P: <priority>, <description>
    - [ ]/[x] P: <priority>, <description>
    ...
```
gdzie `[x]` oznacza zadanie/pod-zadanie wykonane, a `[ ]` niewykonane.

Oczekiwane wyjście:
```
[ ] Finish C++ project
    - [ ] P: 99, Write a Makefile
    - [x] P: 5, Run tests
    - [ ] P: 3, Refactor the code
    - [ ] P: 0, Write the documentation
[ ] Finish C++ project
    - [x] P: 99, Write a Makefile
    - [x] P: 5, Run tests
    - [ ] P: 3, Refactor the code
    - [x] P: 0, Write the documentation

[ ] Study algebra
    - [x] P: 11, Matrix multiplication
    - [ ] P: 10, Linear combinations
[x] Study algebra
```

---

### Etap 3: Implementacja konstruktora i operatorów kopiujących/przenoszących w `Task` [5 pkt]

Uzupełnij klasę `Task` o brakujące funkcjonalności zgodnie z regułą 5/0.

**Do zaimplementowania**:
- Konstruktor kopiujący (głęboka kopia)
- Operator przypisania (głęboka kopia)
- Konstruktor przenoszący
- Operator przeniesienia

Zadbaj o brak wycieków pamięci.

Oczekiwane wyjście:
```
Task copy (constructor):
[ ] Finish C++ project
    - [x] P: 99, Write a Makefile
    - [x] P: 5, Run tests
    - [ ] P: 3, Refactor the code
    - [x] P: 0, Write the documentation

Task copy (assignment):
[ ] Finish C++ project
    - [x] P: 99, Write a Makefile
    - [x] P: 5, Run tests
    - [ ] P: 3, Refactor the code
    - [x] P: 0, Write the documentation

Playlist moved (constructor):
[ ] Finish C++ project
    - [x] P: 99, Write a Makefile
    - [x] P: 5, Run tests
    - [ ] P: 3, Refactor the code
    - [x] P: 0, Write the documentation

Playlist moved (assignment):
[ ] Finish C++ project
    - [x] P: 99, Write a Makefile
    - [x] P: 5, Run tests
    - [ ] P: 3, Refactor the code
    - [x] P: 0, Write the documentation
```

---

## Rozwiązania

[Makefile](solution/Makefile)

[Subtask.cpp](solution/Subtask.cpp)

[Subtask.hpp](solution/Subtask.hpp)

[Task.cpp](solution/Task.cpp)

[Task.hpp](solution/Task.hpp)

[main.cpp](solution/main.cpp)
