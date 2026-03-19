---
title: "2025"
date: 2025-03-19T12:00:00+01:00
weight: 2025
url: "/lab/l3/previous-years/2025/"
---

# Zadanie oceniane 3
## Pamięć

Celem tego laboratorium jest napisanie swojego kontenera, którego zadaniem jest przechowywanie listy znaków (typ **char**) zmiennej długości. Jak możesz się domyślać, będzie to uproszczona forma klasy już istniejącej w biblitece standardowej, a mianowicie `std::vector`. Założeniem tego typu kontenera jest przechowywanie obiektów tego samego typu w **ciągłym** bloku pamięci.

W celu zaimplementowania zadania musisz stworzyć 2 pliki:
- plik nagłówkowy zawierające deklaracje stuktury oraz funkcji realizujących kolejne funkcjonalności,
- plik źródłowy z definicją ww. funkcji.

W repozytorium znajdziesz jeden plik startowy: `main.cpp` oraz Makefile, do którego musisz dodać linie kompilujące i linkujące dodane przez Ciebie pliki.

Uwaga: Address Sanitizer został włączony na potrzeby tego zadania poprzez flagę `-fsanitize=address` w Makefile. Nie wolno go usunąć, gdyż będzie on podpowiadał przy błędach alokacji/dealokacji pamięci. Przy implementacji każdego etapu należy dodać dodatkowe wywołania odpowiednich funkcji na początku bądź na końcu etapu tak, by Address Sanitizer był zadowolony.

## Pliki startowe

[Makefile](src/Makefile)

[main.cpp](src/main.cpp)

### 1. Deklaracja struktury [5pkt]
Utwórz plik: `mini_vector.hpp`. W tym etapie powinien on zawierać:
- Statyczną stałą `INIT_CAPACITY` typu int równą 4.
- Definicję struktury `MiniVector`, zawierającej 3 pola:
  `elements`, wskaźnik na pierwszy element tablicy znaków (`char`),
  `capacity`, wielkości zaalokowanej tablicy,
  `size`, liczba elementów w tablicy.
Każdym momencie programu musi zachodzić zależność `size` <= `capacity`.
Jeśli `size` < `capacity`, to znaczy to, że pierwsze `size` elementów tablicy `elements` uznajemy za poprawne, a kolejne za niepoprawne.

Utwórz plik `mini_vector.cpp` i zaimplementuj w nim:
- Funkcję `vector_init` przyjmującą referencję do obiektu typu `MiniVector` oraz agrument `capacity` typu `int`, nie zwracającą żadnej wartości. Funkcja inicjuje pola struktury `MiniVector` w następujący sposób: `size` ustawia na 0, `capacity` na wartość przekazaną przez parametr do funkcji, i alokuje tablicę długości `capacity`, przypisując wskaźnik na nią do `elements`.
- Funkcję `vector_init_fill`, która przyjmie parametry takie jak `vector_init` i dodatkowo `char init_character`. Funkcja wykonuje te same kroki co `vector_init`, ale wypełnia tablicę `elements` znakiem `init_character` i ustawia `size` równy `capacity`.
- Funkcję `vector_print`, przyjmującą jako parametr referencję do obiektu typu `MiniVector`, która wypisuje elementy tablicy oddzielone przecinkiem. Jeśli tablica nie zawiera elementów, powinien zostać wypisany komunikat `no elements in vector`.
- Funkcję `vector_destroy`, która zapewni odpowiednie zwolnienie zaalokowanej przez struktury pamięci.

Udostępnij deklaracje powyższych funkcji w pliku `mini_vector.hpp`.
W `main.cpp` utwórz dwa wektory. Jeden z nich zainicjalizuj za pomocą `vector_init`, drugi - `vector_init_fill`. Wypisz zawartość obu wektorów.

Poprawny wynik pierwszego etapu:
```
Vector elements: no elements in vector.
Vector elements: *, *, *, *
```

### 2. Wypisywanie stanu pamięci i dynamiczne zmimenianie wielkości pamięci [3pkt]

Wypisywanie stanu pamięci będzie się odbywało w dwóch trybach: wypisywania adresów poszczególnych elementów tablicy lub wypisywania zawartości (znaków - char).
`
W pliku `mini_vector.cpp`:
- Zaimplementuj funkcję `vector_expand`, która przyjmie referencję na obiekt typu `MiniVector` oraz `int new_capacity`. Funkcja powinna rozszerzyć wielkość tablicy przechowującej elementy, ale tylko jeśli nowa pojemność jest większa od obecnej. Wpp. wypisz komunikat. 
- Funkcja `vector_shrink`, która przyjmie referencję na obiekt typu `MiniVector` oraz `int new_capacity`. Funkcja powinna zmniejszyć wielkość tablicy przechowującej elementy, ale tylko jeśli nowa pojemność jest mniejsza od obecnej i liczba elementów w tablicy jest mniejsza od nowej pojemności. Wpp, wypisz odpowiednie komunikaty.

Udostępnij deklaracje powyższych funkcji w pliku `mini_vector.hpp`.

Poprawny wynik drugiego etapu (adresy pamięci mogą się zmieniać z każdym wywołaniem):

```
Vector elements: a, a, a, a
Vector elements: a, a, a, a
Cannot shrink vector: there are elements that would be lost in the process.
Cannot shrink vector: new capacity is greater than current.
Vector elements: a, a, a, a
Cannot expand vector: new capacity is lower than current.
Vector elements: a, a, a, a
```

### 3. Dodawanie elementów i czyszczenie wektora [4pkt]

W pliku `mini_vector.hpp`:
- Zaimplementuj funkcję `vector_add`, która przyjmie referencję na obiekt typu `MiniVector` oraz nowy element do wstawienia do tablicy. Jeśli obiekt się nie mieści (czyli `size == capacity`), zwiększ dwukrotnie pojemność tablicy. Nie zapomnij przepisać danych ze starej tablicy do nowej tablicy.
- Zaimplementuj funkcję `vector_clear`, która przyjmie referencję na obiekt typu `MiniVector`. Funkcja powinna zwolnić pamięć, zaalokować ją ponownie (z `capacity = INIT_CAPACITY`), i ustawić `size` na zero.

Udostępnij deklaracje powyższych funkcji w pliku `mini_vector.hpp`.

Poprawny wynik trzeciego etapu (adresy pamięci mogą się zmieniać z każdym wywołaniem):
```
Added H
Added e
Added l
Added l
Added o
Added !
Vector elements: 0, 0, 0, 0, H, e, l, l, o, !
Vector elements: no elements in vector.
```

### 4. Usuwanie elementów po indeksie i wartości [3pkt]

W pliku `mini_vector.hpp`:
- Zaimplementuj funkcję `vector_remove`, która przyjmie referencję na obiekt typu `MiniVector` oraz pozycję (`int`) elementu do usunięcia. Jeśli po usunięciu zachodzi `2 * size < capacity`, zredukuj pojemność o połowę.
- Zaimplementuj funkcję `vector_remove_occurrences`, która przyjmie referencję na obiekt typu `MiniVector` oraz znak (`char`) którego powtórzenia mają zostać usunięte z wektora. Jeśli po usunięciu zachodzi `2 * size < capacity`, zredukuj pojemność o połowę.

Udostępnij deklaracje powyższych funkcji w pliku `mini_vector.hpp`.

Poprawny wynik trzeciego etapu:
```
The requested element index is exceeding vector size. (Vector size: 22. Requested idx for element removal: 25)
Vector elements: M, y,  , i, r, s, t,  , V, e, c, t, o, r,  , i, n,  , C, +, +
Vector elements: M, y, i, r, s, t, V, e, c, t, o, r, i, n, C, +, +
Vector elements: M, y, C, +, +
Vector elements: no elements in vector.
```

## Rozwiązania

[Makefile](solution/Makefile)

[main.cpp](solution/main.cpp)

[mini_vector.cpp](solution/mini_vector.cpp)

[mini_vector.hpp](solution/mini_vector.hpp)
