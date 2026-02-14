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
```

#### 4. Wydzielenie struktury `bounded_buffer`

Funkcjonalności bufora mogą zostać wydzielone jako oddzielna struktura.
Chcielibyśmy uogólnić dopuszczony rozmiar do dowolnej liczby całkowitej
Przygotuj następującą strukturę

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

### System budowania -- GNU Make

Po zaimplementowaniu programu `pager.cpp` możemy zobaczyć wydzielony kawałek kodu z implementacją `bounded_buffer`.
Jeśli chcielibyśmy użyć go w innym programie, warto utworzyć dla niego osobny plik `bounded_buffer.cpp`.
Powoduje to jednak pewne komplikacje.
W czasie kompilacji należy dostarczyć więcej informacji o tym, jak uzyskać skompilowany program.
Od teraz zwykłe polecenie
```bash
g++ -o pager pager.cpp
```
już nie wystarczy.
Wymaga to nietrywialnej logiki, która trzeba podzielić się z użytkownikami lub innymi programistami.

Do przechowywania informacji o sposobie skompilowania programu służy **system budowania**.
W przypadku naszego laboratorium będziemy posługiwać się systemem (**GNU Make**)[https://www.gnu.org/software/make/manual/make.html].

#### 1. Utworzenie `Makefile`
Poza kodem źródłowym programu typowo rozprowadza się także plik `Makefile`, który opisuje sposób budowania.
Najpierw przygotuj plik `Makefile` o zawartości
```makefile
CXX=g++

.PHONY: all clean

all: pager

pager: pager.cpp
	${CXX} pager.cpp -o pager

clean:
	rm -f pager
```

System budowania make konstruuje się z **targetów** (np. `all`, `pager` albo `clean`).
Każdy target ma swoje **zależności** podane po dwukropku.
Jest o konieczne do określenia, w jakiej kolejności należy wykonywać polecenia, aby uzyskać podany target.
Poniżej definicji targetu znajdują się polecenia, które konsumują zależności (najczęściej pliki), aby uzyskać wynik.
Rozważmy przykład targetu `all`.

```
all -> pager
pager -> pager.cpp
```
Oznacza to, że aby uzyskać **wszystko**, należy wykonać polecenia z targetu `pager`, które potrzebują pliku `pager.cpp`.
I rzeczywiście po przeanalizowaniu polecenia
```bash
${CXX} -o pager pager.cpp
```
Rzeczywiście używamy kompilatora C++ (opisanego zmienną `CXX`), aby skonsumować `pager.cpp` i uzyskać plik `pager`.

W terminalu przejdź do folderu z plikami źródłowymi twojego programu i wykonaj polecenie
```bash
make
```
Wykona ono polecenia,aby uzyskać target `all`.
Jeśli chcesz zbudować tylko pager, wykonaj
```bash
make pager
```
Aby usunąć pliki binarne wykonaj
```bash
make clean
```

#### 2. Wydzielenie `bounded_buffer` do oddzielnego pliku

Teraz twoim zadaniem jest wydzielić logikę związaną ze strukturą `bounded_buffer` do oddzielnego pliku `bounded_buffer.cpp`.
Aby można było użyć **definicji** funkcji z `bounded_buffer.cpp` w `pager.cpp`, potrzebny jest **plik nagłówkowy**.
Taki plik posiada **deklaracje** funkcji, które opisują nagłówki funkcji bez ich implementacji.

W tym celu utwórz kolejny plik `bounded_buffer.hpp`, który będzie posiadać definicje struktury oraz deklaracje funkcji.
Jeśli chcesz skorzystać ze struktury `bounded_buffer` oraz czterech skojarzonych z nią funkcji, należy dodać w pliku `pager.cpp` następującą linijkę.
```cpp
#include "bounded_buffer.hpp"
```
Informuje ona kompilator, aby załączył cała zawartość pliku `bounded_buffer.hpp` w miejscu linijki `#include "bounded_buffer.hpp`.

Pozostał jeszcze jeden szczegół, który jest dobrą praktyką w definiowaniu plików nagłówkowych.
Na początku należy zdefiniować tzw. **include guard** (pol. strażnik inkluzywności).
Jest to konstrukcja przeciwdziałająca wielokrotnej deklaracji zawartości pliku nagłówkowego.

Proponuję eksperyment. Dodaj do swojego pliku `pager.cpp` następujące linijki
``cpp
// ... wcześniejsze includy z biblioteki standardowej ...

#include "bounded_buffer.hpp"
#include "bounded_buffer.hpp"

// ... funkcja main ...
```
Wykonaj polecenie
```bash
g++ pager.cpp
```
W tym momencie powinien pojawić się błąd kompilacji
```
TODO: wstaw błąd
```

Jest to objaw braku include guard.
Dodaj do swojego pliku `bounded_buffer.hpp` następujące instrukcje preprocessora na końcu i początku.
```cpp
#ifndef _BOUNDED_BUFFER_H
#define _BOUNDED_BUFEFR_H

// ... definicja struktury oraz deklaracje zmiennych ...

#endif
```

Od tego momentu kompilator załączy deklaracje tylko raz, ponieważ za drugim razem będzie istniejć już zmienna preprocessora `_BOUNDED_BUFFER_H`, co spowoduje ominięcie deklaracji.

Zachęcam do wykonania polecenia
```bash
g++ -E pager.cpp | tail 200
```
To polecenie wykona tylko instrukcje preprocessora i wypisze wynik na standardowe wyjście.
Wykonaj powyższe polecenie z include guardem i bez niego.

#### 3. Kompilacja programu `pager`

Gdy już mamy 3 pliki: `pager.cpp`, `bounded_buffer.hpp` oraz `bounded_buffer.hpp`, mozemy przejśc do budowania programu.
Wykonanie polecenia
```bash
make
```
zwróci błąd kompilacji.
Należy przerobić target `pager`, aby zależał także od pliku `bounded_buffer.cpp` i wykonywał następujące polecenie
```bash
g++ -o pager pager.cpp bounded_buffer.cpp
```
Wtedy program zbuduje się prawidłowo, ponieważ będzie posiadał wszystkie **definicje** funkcji użytych w programie.

### Rozwiązanie laboratorium
