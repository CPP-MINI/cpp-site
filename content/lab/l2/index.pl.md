---
title: "L2"
date: 2022-02-05T17:26:02+01:00
weight: 20
---

# Laboratorium 2
## Pamięć

Na tym laboratorium twoim zadaniem jest stworzenie niestandardowych typu danych oraz eksperymentowanie z jego czasem życia.
Tym razem zadanie podzielone jest na sześć etapów.
W kodzie znajdują się wskazówki, gdzie należy umieścić rozwiązania poszczególnych etapów (szukaj komentarzy zawierających `STAGE N`).

Skorzystaj z kodu startowego oraz dołączonego do niego pliku `Makefile`. Można w nim znaleźć dwie zmienne: `CXXFLAGS` oraz `LDFLAGS`. Pierwsza z nich powinna być używania przy tworzeniu obiektów.
Druga natomiast jest przewidziany przy linkowaniu obiektów do gotowych plików wykonywalnych lub bibliotek.

[Makefile](src/Makefile)

[main.cpp](src/main.cpp)

[vector3.h](src/vector3.h) [vector3.cpp](src/vector3.cpp) 

[holey_string.h](src/holey_string.h) [holey_string.cpp](src/holey_string.cpp) 

[memory_manipulation.h](src/memory_manipulation.h) [memory_manipulation.cpp](src/memory_manipulation.cpp)

### Etap 0: Deklaracji enumeracji w duchu C++

Na rozgrzewkę twoim zadaniem będzie utworzenie dwóch enumeracji opisujących kolory oraz typy owoców.
W tym celu utwórz plik `fruit.h` i zadeklaruj dwie enumeracje: `Color` oraz `FruitType`.
Pierwsza z nich dopuszcza 4 kolory:
* `Red`
* `Orange`
* `Green`
* `Violet`.

Druga natomiast opisuje trzy rodzaje owoców:
* `Apple`
* `Orange`
* `Plum`

Następnie zdefiniuj strukturę `Fruit` składającą się z tych dwóch enumeracji.
Na końcu pliku `fruit.h` zdefiniuj 6 statycznych wyrażeń statycznych (`static constexpr`) zmiennych typu `Fruit` opisujące dojrzałe i niedojrzałe jabłko, pomarańczę oraz śliwkę.

Zwróć uwagę, że przy dojrzałej pomarańczy enumerację w stylu C++ wprost wyrażają, który `Orange` powinien zostać użyty w trakcie tworzenia instancji owoców.

### Etap 1: Trójwymiarowy wektor
W pliku `vector3.h` zadeklarowana jest struktura, która ma reprezentować wektor trójwymiarowy.
Jako element jej definicji znajdziesz `using internal_representation`, który definiuje, jak wewnętrznie przechowywane są informacje o trzech liczbach rzeczywistych.
Twoim zadaniem jest stworzyć definicję struktury `internal_representation` w taki sposób, aby dostęp do trzech liczb typu `double` można było wykonać poprzez trzy oddzielne zmienne `x`, `y` oraz `z`, albo poprzez trójelementową tablicę typu `double`.
Stworzona struktura powinna mieć rozmiar `3 * sizeof(double)` oraz alignment taki jako typ double.
Proszę zwrócić uwagę na dwie linie zawierające `static_asert`.
Jest to sposób na upewnienie się, że zdefiniowany przez ciebie typ będzie traktowany jak blok trzech liczb.
Zastanów się, dlaczego akurat tak wyglądają sprawdzenia poprawności.

Struktura `Vector3` ma zdefiniowane pole `v` stworzonego przez ciebie typu `internal_representation`.
W czterech funkcjach, które musisz teraz zaimplementować w pliku `vector3.cpp`, będzie ona dostępna jako pole `v`.

Dwie z tych funkcji to tzw. *konstruktory*, o których mowa będzie na kolejnych laboratoriach.
Twoim zadaniem jest ustawić w nich wartości `x`, `y` oraz `z` pola `v` zgodnie z przekazanymi argumentami (brak argumentów oznacza wypełnienie zerami).
Funkcja `length` służy do wyliczenia długości euklidesowej wektora (**Podpowiedź**: funkcja `sqrt` znajduje się w nagłówku `cmath`).
Funkcja `mul` służy do pomnożenia wektora przez liczbę.
Do zaimplementowania funkcji `length` oraz `mul` użyj możliwości dostępu do `v` z perspektywy tablicy typu `double`.

Jak rozszerzenie klasy `Vector3` zadeklaruj dwie wolne funkcje w pliku `vector3.h`:
* `vector3_add` - funkcja wykonuje dodawanie wektorów oraz przyjmuje dwie stałe referencje na typ `Vector3` reprezentujące lewą i prawą stronę operatora dodawania. Funkcja powinna zwracać nowy `Vector3` przechowujący wynik dodawania.
* `vector3_print` - funkcja formatuje i wypisuje na standardowe wyjście współrzędne wektora oraz jego długość (`[x,y,z] length`). Przyjmuje jako argument jedną stałą referencję na wektor, który należy wypisać na standardowe wyjście.

Ciała funkcji powinny zostać zaimplementowane w pliku `vector3.cpp`.

Po skończeniu implementacji struktury `Vector3` przejdź do funkcji `main` w pliku `main.cpp`. 
Mając już wszystkie konieczne operacje na wektorach, możemy wyrazić wektor `[3,5,7]` jako kombinację liniową wektorów bazowych pomnożonych przez pewne stałe.
Zdefiniuj trzy wektory bazowe jako zmienne automatyczne i wykorzystując funkcje `mul` oraz `vector3_add` oblicz wynikowy wektor. Na koniec wypisz wynik na standardowe wyjście przy pomocy funkcji `vector3_print`.


W ramach przypomnienia: wektory z bazy kanonicznej to `[1,0,0]`, `[0,1,0]` oraz `[0,0,1]` (**Podpowiedź**: `= {x,y,z}` zainicjalizuje wektor wartościami podanymi w klamrach).

### Etap 2: Tablice wektorów

Kiedy typ `Vector3` działa jak trzeba, możemy przejść do deklarowania tablic w funkcji `main`.
Twoim zadaniem jest zadeklarować trzy rodzaje tablic:
* automatyczna (na stosie),
* dynamiczną (na stercie) - oznacza to wykonanie wszystkich akcji związanych z obsługą otrzymanej pamięci,
* używając `std::vector` (używając obiektu, który zarządza pamięcią wewnętrznie).

Do każdej tablicy wstaw 10 obiektów typu `Vector3` o wartościach `{i,i,i}`, gdzie `i` - numer wstawianego wektora.
Przy każdym wstawieniu pobierz adres pierwszego elementu oraz wypisz go na standardowe wyjście (czy w każdym wypadku te adresy będą identyczne w każdym obrocie pętli?).
Po zakończeniu wstawiania przejdź po tablicy ponownie oraz wypisz długość wektora na standardowe wyjście.

### Etap 3: Memory dumper (*pol. drukarz pamięci*)

W tym etapie twoim celem jest napisanie funkcji, która przyjmie dowolny wskaźnik oraz ilość bajtów do wypisania na standardowe wyjście.
W każdej linii wypisz 8 bajtów na dwa sposoby: jako liczbę heksadecymalną oraz znak ASCII (jeśli jest to możliwe).
Aby dopełnić obraz wypisanych bajtów, na początku linii wypisz adres pierwszego bajtu (**Podpowiedź**: [`std::hex`](https://en.cppreference.com/w/cpp/io/manip/hex) służy do formatowania jako liczby heksadecymalne).

Przykładowo funkcja dla pamięci zajmowanej przez `Vector3{1,2,3}` wypisze na standardowe wyjście
```
0x75c1bc3000f0: 00 00 00 00 00 00 f0 3f | .......? |
0x75c1bc3000f8: 00 00 00 00 00 00 00 40 | .......@ |
0x75c1bc300100: 00 00 00 00 00 00 08 40 | .......@ |
```
a dla ciągu znaków `Hello world!`
```
0x76a298300240: 48 65 6c 6c 6f 20 77 6f | Hello wo |
0x76a298300248: 72 6c 64 21 | rld! |
```

Definicja funkcji jest przygotowana w pliku `main.cpp`.
Po wykonaniu implementacji wypisz na ekran pamięć zajmowaną przez każdą tablicę z etapu drugiego.

### Etap 4: Dziurawy ciąg znaków

W pliku `holey_string.h` zdefiniowana jest struktura reprezentująca 16 elementowy ciąg znaków.
Znaki w tym tej strukturze są specjalne, pomimo wykorzystania typu `char` każdy znak zajmuje 2 bajty.

Twoim zadaniem jest zdefiniować ten specjalny typ znaku `holey_char` (**Podpowiedź**: `alignas`) i zaimplementować trzy funkcje:
* `print` - ta funkcja wypisuje taki specjalnie przygotowany ciąg znaków na standardowe wyjście (długość ciągu znaków ustal na podstawie terminującego zera - jak w języku C),
* `assign` - ta funkcja przypisuje otrzymany `std::string` do specjalnego ciągu znaków (zaterminuj string w stylu C - ustawiając ostatni bajt na zero),
* `hide` - ta funkcja przypisuje otrzymany `std::string` do dziur powstałych pomiędzy znakami.
W przypadku ostatniej funkcji wykonanie funkcji `hide` nie powinno wpłynąć na zawartość ciągu znaków oraz kolejne wywołania funkcji `print`. *Po laboratoriuum zastanów się, czy ta funkcja przypadkiem nie łamie jakichś zasad* 🤔

Po zaimplementowaniu powyższych funkcji przejdz do pliku `main.cpp` oraz stwórz automatyczny obiekt typu `HoleyString`. Wykonaj na nim funkcję `assign` ze stringiem `"hello"` oraz hide z `"world"`. Po wykonaniu każdej z tych dwóch operacji wykonaj funkcję `print` oraz wypisz pamięć zajmowaną przez obiekt funkcją `dump_memory`.


### Etap 5: Manipulacja pamięcią

W standardowej bibliotece C znajdują się dwie bardzo przydatne funkcje: `memcpy` oraz `memmove`.
Obydwie służą do przekopiowania bloku pamięci ze wskazanego adresu do docelowego.
Różni je jednak bardzo subtelny szczegół: fakt nachodzenia się bloków źródłowego oraz docelowego.
Funkcja `memcpy` zakłada, że podane bloki nie nachodzą na siebie, a `memmove` dopuszcza, aby bloki nachodziły na siebie.
Zachęcam do przeczytania instrukcji dla standardowej biblioteki, aby zapoznać się z funkcjami (`man 3p memcpy` oraz `mam 3p memmove`).

Twoim zadaniem jest zaimplementować obydwie funkcje w pliku `memory_manipulation.cpp`.
W celu sprawdzenia implementacji w pliku `main.cpp` wykonaj następujące przekształcenia:
* `Hello world!` -> `Hello Hello!`
* `Hello world once again!` -> `Hello world world once!`

Zabronione jest użycie funkcji `std::memcpy` oraz `std::memmove` w implementacjach i przykładzie użycia!

## Rozwiązanie

[Makefile](solution/Makefile)

[main.cpp](solution/main.cpp) [fruit.h](solution/fruit.h)

[vector3.h](solution/vector3.h) [vector3.cpp](solution/vector3.cpp) 

[holey_string.h](solution/holey_string.h) [holey_string.cpp](solution/holey_string.cpp) 

[memory_manipulation.h](solution/memory_manipulation.h) [memory_manipulation.cpp](solution/memory_manipulation.cpp)
