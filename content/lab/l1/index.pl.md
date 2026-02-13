---
title: "L1"
date: 2022-02-05T17:26:02+01:00
weight: 10
---

# Laboratorium 1
## System budowania i podstawowe elementy biblioteki standardowej


### Biblioteka standardowa

W jeżyku C++ programista ma dostęp do **biblioteki standardowej C++**.
Zawiera ona podstawowe funkcje i klasy, których warto nauczyć się używać.
Na laboratoriach nasze programy będą miały zawsze dostęp do wszystkich funkcjonalności biblioteki.

Proszę nie używać standardowe biblioteki **C** (np. `#include <stdio.h>`).
Jeśli będzie potrzeba dowiedzieć się, jakie funkcje są dostępne w bibliotece standardowe oraz jak ich używać, proszę odwiedzać takie strony jak [https://cppreference.com/](https://cppreference.com/).
Są to strony opisujące elementy standardowej biblioteki w sposób zwięzły i *przystępny* dla programisty (to ostatnie jest dyskusyjne).

### Zadanie - Buforowanie wejścia

Twoim zadaniem na dzisiejszych laboratoriach jest przygotowanie prostego programu zapamiętujący linie wprowadzone na standardowe wejście.
Po przeczytaniu 4 linii powinny zostać wypisane na standardowe wyjście z dodatkową pustą linią.

#### 1. Przygotowanie pracy
Rozpocznij od utworzenia pliku `pager.cpp` i otwarcia go w swoim środowisku programistycznym.
Dobrym kodem startowym będzie przykład z poprzednich laboratoriów

```cpp
#include <iostream> 

int main()
{
  std::cout << "Hello, nice to meet you. I'm pager." << std::endl;
  return 0;
}
```

Skompiluj program poleceniem 
```bash
g++ -o pager pager.cpp
```
Jeśli kod kompiluje się i uruchamia bez problemu, przejdź do kolejnego kroku

#### 2. Czytanie i pisanie

Na początku przygotuj kod, który czyta linie do zmiennej typu `std::string` i wypisuje ją na standardowe wyjście.
Do przeczytania całej linii na wejściu użyj funkcji (`std::getline()`)[https://en.cppreference.com/w/cpp/string/basic_string/getline].
Czytaj do czasu, jak standardowe wejście się zakończy.
Aby sprawdzić działanie programu, wykonaj

```bash
./pager < pager.cpp
```
Lub po uruchomieniu programu poprzez
```bash
./pager
```
wpisuj dane ręcznie. Zakończ strumień poprzez `Ctrl+D`.

**Podpowiedź**: użyj `while (std::getline(std:cin, ...))`, aby czytać do czasu końca strumienia standardowego wejścia. 

#### 3. Buforowanie danych

Użyj `std::vector`, aby przechowywać otrzymane linie.
Twoim celem jest przechowywanie do 4 linii.
Po osiągnięciu limitu wypisz wszystkie zapisane linie i dodaj linie zawierającą `=====`.

Stwórz wektor przechowujący typ `std::string`.
Użyj funkcji `.push_back()`, aby dodać linię.
Aby wyczyścić wektor, użyj funkcji `.clear()`.

Przykład wykonania dla wejścia
```
Ala
ma
kota
persa
i
psa
burka
```
Wyjście:
```
Ala
ma
kota
persa
=====
i
psa
burka
`

#### 4. Wydzielenie struktury `bounded_buffer`

Funkcjonalności bufora mogą zostać wydzielone jako oddzielna struktura.
Chcielibysmy uogólnić dopuszczony rozmiar do dowolnej liczby całkowitej
Przygotuj nastepującą strukturę

```cpp
struct bounded_buffer {
  std::vector<std::string> buffer;
  int max_size;
}
```

I zaimplementuj następujące funkcje
```
// Zwróć ilośc zgromadzonych linii w buforze
int buffer_size(const bounded_buffer* buffer);

// Zwróć maksymalny rozmiar bufora
int buffer_capacity(const bounded_buffer* buffer);

// Wypisz zawartośc bufora na standardowe wyjście i zwolnij zawartość bufora
void flush_buffer(bounded_buffer* buffer);

// Dodaj linie do bufora. Jeśli limit bufora został osiągniety, zwróć false i nie modyfikuj zawartości
bool add_to_buffer(bounded_buffer* buffer, std::string line);
```

Przebuduj funkcję `main`, aby tworzyła `bounded_buffer` o rozmiarze 4 i używała go w logice programu.

### System budowania - GNU Make

Po zaimplementowaniu programu `pager.cpp`, możemy zobaczyć wydzielony kawałek kodu z implementacją `bounded_buffer`

https://www.gnu.org/software/make/manual/make.html

Przez cały semestr projekty będą znacznie bardziej skomplikowane.

