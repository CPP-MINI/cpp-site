---
title: "L3"
date: 2022-02-05T17:26:02+01:00
weight: 30
---

# Laboratorium 3
## Klasy

Na tym laboratorium twoim zadaniem będzie przećwiczenie różnych funkcjonalności związanych z klasami, a także eksperymentowanie z inteligentnymi wskaźnikami.
Głównym tematem laboratorium są funkcjonalności związane z piosenkami.

Skorzystaj z dostarczonego pliku [main.cpp](src/main.cpp), w którym umieszczone zostały testy do pierwszych 3 etapów zadania.
Po zakończeniu implementacji konkretnego etapu odkomentuje odpowiadającą mu część funkcji main i porównaj swój wynik z oczekiwanym (**pamiętaj o załączeniu stworzonych przez ciebie plików w main.cpp**).
Dostarczony jest również startowy plik [Makefile](src/Makefile).

### Etap 1: Implementacja klasy `SongDuration`

W pliku `SongDuration.hpp` zaimplementuj klasę `SongDuration`, która reprezentuje czas trwania utworu w minutach i sekundach.

Klasa powinna zawierać następujące elementy:

**Prywatne pola**:
- `unsigned int minutes` – liczba minut.
- `unsigned int seconds` – liczba sekund.

**Konstruktor**:
- Zaimplementuj konstruktor przyjmujący liczbę minut i sekund. Jeśli liczba sekund przekracza 59, powinna być automatycznie przeliczona na minuty (np. `SongDuration(1, 65)` powinno skutkować `2 minutami i 5 sekundami`).

**Metody publiczne**:
- `get_total_seconds()` – zwraca całkowity czas trwania w sekundach.
- `get_formatted()` – zwraca string zawierający czas trwania w formacie `"Xm Ys"`, gdzie `X` i `Y` to odpowiednio liczna minut i sekund.

Oczekiwane wyjście etapu 1:
```
Duration 1: 2m 5s (125s)
Duration 2: 4m 38s (278s)
```

### Etap 2: Implementacja klasy `Song`

W plikach `Song.hpp` i `Song.cpp` zaimplementuj klasę `Song`, która reprezentuje pojedynczy utwór muzyczny.

Klasa powinna zawierać następujące elementy:

**Prywatne pola**:

- `std::string title` – tytuł utworu.
- `std::string artist` – wykonawca utworu.
- `SongDuration duration` – czas trwania utworu.

**Konstruktory**:
- Konstruktor bezargumentowy inicjalizuje tytuł jako `"Untitled"`, wykonawcę jako `"Unknown"`, a czas trwania jako 0 sekund.
- Konstruktor przyjmujący tytuł, czas trwania (`SongDuration`) oraz wykonawcę (wykonawca powinien mieć domyślną wartość `"Unknown"`).
- Konstruktor przyjmujący tytuł, czas trwania (w minutach i sekundach) oraz wykonawcę (sekundy powinny mieć domyślną wartość 0, a wykonawca `"Unknown"`).

**Uwaga**: Pamiętaj o używaniu list inicjalizacyjnych.

**Metody publiczne**:
- `print()` – wypisuje informacje o utworze w formacie:
  ```
  <tytuł>, Artist: <wykonawca> [<czas trwania>]
  ```
- gettery i settery do pól prywatnych (getter i setter do `duration` powinien przyjmować i zwracać tylko sumaryczną liczbę sekund)

**Statyczne pole i metodę**:
- Pole statyczne `int count_songs` powinno przechowywać aktualną liczbę stworzonych obiektów typu `Song`.
- Metoda statyczna `get_total_songs()` zwraca liczbę aktualnie istniejących obiektów typu `Song`.

**Uwaga**: Żeby powyższy licznik działał poprawnie, musisz uwzględnić tę funkcjonalność w konstruktorach i zdefiniować odpowiedni destruktor.

Oczekiwane wyjście etapu 2:
```
Untitled, Artist: Unknown [0m 0s]
Recursion Anthem, Artist: Stack Overflow [4m 38s]
Binary Love, Artist: The Algorithms [3m 45s]
Segmentation Fault, Artist: Unknown [2m 5s]
Git Happens, Artist: Unknown [2m 0s]

Total songs: 5

Total songs: 3

get_title(): Polymorphic Dreams
get_artist(): Object-Oriented Orchestra
get_duration(): 300
```

### Etap 3: Implementacja klasy `Playlist`

W plikach `Playlist.hpp` i `Playlist.cpp` zaimplementuj klasę `Playlist`, która reprezentuje playlistę utworów.
Klasa będzie podobna w funkcjonalności do implementowanego przez was ostatnio w czasie laboratorium punktowanego wektora.
Piosenki powinny być przechowywane w dynamicznie alokowanej tablicy. Tym razem jednak będziemy pozwalać tylko na dodawanie elementów.

Klasa powinna zawierać następujące elementy:

**Prywatne pola**:
- `Song* songs` – wskaźnik na dynamiczną tablicę utworów.
- `unsigned int capacity` – pojemność playlisty.
- `unsigned int size` – aktualna liczba utworów w playliście.

**Konstruktory, operatory przypisania i destruktor**:
- Konstruktor przyjmujący początkową pojemność playlisty (domyślnie 10).
- Konstruktor kopiujący.
- Operator przypisania.
- Konstruktor przenoszący.
- Operator przypisania z przeniesieniem.
- Destruktor.

Z racji na to, że klasa `Playlist` zarządza dynamiczną pamięcią, chcemy zdefiniować dla niej powyższe funkcjonalności zgodnie z regułą 5/0.

**Metoda prywatna**:
- `resize(unsigned int new_capacity)` – pomocnicza funkcja zmieniająca pojemność playlisty na podaną wartość.

**Metody publiczne**:
- `add_song(const Song& song)` – dodaje utwór do playlisty. Jeśli tablica jest pełna, zwiększ jej pojemność dwukrotnie.
- `get_size()` – zwraca liczbę utworów w playliście.
- `print()` – wypisuje wszystkie utwory w playliście w formacie (lub `Playlist is empty` jeżeli playlista jest pusta):
  ```
  1. <tytuł>, Artist: <wykonawca> [<czas trwania>]
  2. <tytuł>, Artist: <wykonawca> [<czas trwania>]
  ...
  ```  
Oczekiwane wyjście etapu 3:
```
Playlist size: 3
1. Polymorphic Dreams, Artist: Object-Oriented Orchestra [5m 0s]
2. Recursion Anthem, Artist: Stack Overflow [4m 38s]
3. Binary Love, Artist: The Algorithms [3m 45s]

Playlist copy (constructor):
1. Polymorphic Dreams, Artist: Object-Oriented Orchestra [5m 0s]
2. Recursion Anthem, Artist: Stack Overflow [4m 38s]
3. Binary Love, Artist: The Algorithms [3m 45s]

Playlist copy (assignment):
1. Polymorphic Dreams, Artist: Object-Oriented Orchestra [5m 0s]
2. Recursion Anthem, Artist: Stack Overflow [4m 38s]
3. Binary Love, Artist: The Algorithms [3m 45s]

Playlist moved (constructor):
1. Polymorphic Dreams, Artist: Object-Oriented Orchestra [5m 0s]
2. Recursion Anthem, Artist: Stack Overflow [4m 38s]
3. Binary Love, Artist: The Algorithms [3m 45s]

Moved from:
Playlist is empty

Playlist moved (assignment):
1. Polymorphic Dreams, Artist: Object-Oriented Orchestra [5m 0s]
2. Recursion Anthem, Artist: Stack Overflow [4m 38s]
3. Binary Love, Artist: The Algorithms [3m 45s]

Moved from:
Playlist is empty
```

### Etap 4: Eksperymentowanie z inteligentnymi wskaźnikami

W tej części zostawimy już tematykę piosenek ze sobą i będziemy eksperymentować z inteligentnymi wskaźnikami `std::shared_ptr` i `std::unique_ptr`.
Tę część wykonaj całkowicie w przygotowanej części na końcu funkcji main. Znajdziesz tam pomocniczą klasę, która pomoże obserwować, kiedy obiekt jest tworzony i niszczony.

**1. Wykonaj polecenia oznaczone w kodzie jako [TODO 1]**
* Oczekiwane wyjście:
```
A created
B created
C created

Clearing v1
A destroyed

Clearing v2
B destroyed
C destroyed
```
* Zastanów się, dlaczego dostaliśmy akurat taki wynik.
* Czy wynik zmieniłby się, gdybyśmy usunęli nawiasy `{ }`? Dlaczego? Sprawdź!

Jeżeli chcielibyśmy zrobić to samo tylko z wykorzystaniem `std::unique_ptr` mielibyśmy problem, ponieważ jak nazwa wskazuje, może istnieć tylko jeden taki wskaźnik (nie można go kopiować).
Aby umieścić taki wskaźnik w wektorze, musimy skonstruować go od razu w środku wektora.
W tym celu można wykorzystać funkcję [emplace_back](https://en.cppreference.com/w/cpp/container/vector/emplace_back), która przyjmuje argumenty konstruktora elementu i tworzy element już w wektorze.

**1. Wykonaj teraz polecenia oznaczone w kodzie jako [TODO 2]**
* Oczekiwane wyjście:
```
D created
E created
D destroyed
E destroyed
```

---
### Rozwiązanie

[SongDuration.hpp](solution/SongDuration.hpp)

[Song.hpp](solution/Song.hpp)

[Song.cpp](solution/Song.cpp)

[Playlist.hpp](solution/Playlist.hpp)

[Playlist.cpp](solution/Playlist.cpp)

[main.cpp](solution/main.cpp)

[Makefile](solution/Makefile)
