---
title: "L4"
date: 2022-02-05T17:26:02+01:00
weight: 40
---

# Laboratorium 4
## Narzędzia

W tym laboratorium zajmiemy się poznaniem nowego narzędzia do budowania programów: **CMake**.
Umożliwi to nam używanie debuggera **gdb** oraz skorzystanie z biblioteki do testów oprogramowania **GTest**.

### Kodowanie base32hex
Tematyka laboratorium obejmuje kodowanie strumieni bajtów.
Jest to zadanie zapisania arbitralnego strumienia bajtów w formacie ustalonym wcześniej z odbiorcą danych.
W przypadku tych laboratorium użyjemy kodowania [**base32hex**](https://datatracker.ietf.org/doc/html/rfc4648#section-7), które zapisuje bajty wykorzystując 32 znaki `0-9A-V`.
Jest to zapis, który powoduje zwiększenie objętości zapisanych danych.
W zamian uzyskujemy możliwość zapisu danych w miejscach, gdzie powinien znaleźć się tekst (np. nazwy plików lub pismo wydane drukiem).

Aby skorzystać z tego sposobu zapisu, potrzebne są dwa procesy: **kodowania** i **rozkodowania**.

**Implementacja tych procesów jest poza zakresem tego laboratorium i zajęłaby zbyt dużo czasu.**

Z tego powodu otrzymasz pewną implementację tych procesów w postaci dwóch klas: **Encoder** oraz **Decoder**.

#### Encoder base32hex

Klasa `Encoder` implementuje proces kodowania strumienia bajtów do `std::string`.
Posiada ona dwie metody:
* `pushBytes`, która przyjmuje wskaźnik na początek strumienia oraz jego długość.
* `encodedString`, która zwraca `std::string` zawierający napis z zakodowanym strumieniem bajtów.

Typowe użycie to:
1. Stworzenie obiektu klasy `Encoder`.
2. Zawołanie raz lub więcej funkcji `pushBytes`.
3. Uzyskanie zakodowanego napisu przy pomocy `encodedString`.

#### Decoder base32hex

Klasa `Decoder` implementuje proces dekodowania napisu w postaci `std::string` do strumienia bajtów.
W czasie konstrukcji obiekt musi poznać cały napis z zakodowaną wiadomością.
Posiada ona dwie metody:
* `isEmpty`, która informuje czy można zdekodować strumień bajtów z napisu.
* `pullBytestream`, która zwraca `std::vector<std::byte>` zawierający rozkodowany strumień bajtów.

Typowe użycie to:
1. Stworzenie obiektu klasy `Decoder`. W czasie konstrukcji należy przekazać zakodowany napis.
2. Sprawdzenie, czy jest strumień bajtów do zdekodowania przy pomocy metody `isEmpty`. Jeśli tak, to wykonaj pkt. 3. W przeciwnym wypadku koniec.
3. Uzyskanie zdekodowanego strumienia przy pomocy `pullBytestream`.
4. Idź do pkt.2

### Korzystanie z obcego kodu

Gdy w naszym projekcie korzystamy z kodu napisanego przez innego programistę, ponosimy ryzyko, że obcy kod posiada błędy.
Z tego powodu należy korzystać z bibliotek renomowanych, które są wysokiej jakości.

Jeśli jednak musimy skorzystać z biblioteki wątpliwej jakości (jak w przypadku tych laboratoriów), to kluczowe są dwie zasady:
1. Mimo podejrzenia istnienia błędów należy zaufać, że kod działa prawidłowo.
2. Jeśli jednak w czasie korzystania z biblioteki znajdziemy błąd:
    * Jako autor projektu korzystającego z obcego kodu bierzemy odpowiedzialność za całokształt i naprawiamy błąd (*trudna ścieżka*).
    * Kontaktujemy się z autorem biblioteki i prosimy go o naprawienie błędu (*trochę łatwiejsza ścieżka*).

Powyższa praktyka ma charakter **reaktywny** i sprawdza się *w większości przypadków*.
Proszę pamiętać, że błąd w naszym projekcie może być oczekiwaną własnością w innym projekcie.

### Projekt CMake

W tym etapie zadanie chcemy skorzystać z bibiloteki `base32`.
Twórca biblioteki poza dwoma klasami dostarcza plik Makefile opisujący zbudowanie przykłądowego programu.
Zawiera on dodatkowo plik `main.cpp`, który symuluje program `basenc` z paramaterem `--base32hex`.

**Proszę potraktować otrzymany kod w pliku main.cpp jako czarną skrzynkę. Wewnątrz znajdują się funkcje wychodzące poza zakres tego przedmiotu i nie będziemy ich omawiać.**

Twoim zadaniem jest stworzenie projektu `CMake` i powielenie procesu budowania już w nowym systemie.
Stwórz następującą strukturę katalogów:
```
 - src/
 |  - main.cpp
 |  - CMakeLists.txt
 - lib/
 |  - base32/
 |  |  - base32_def.hpp
 |  |  - CMakeLists.txt
 |  |  - decoder.cpp
 |  |  - decoder.hpp
 |  |  - encoder.cpp
 |  |  - encoder.hpp
 |  - CMakeLists.txt
 - tests/ # No cpp files for now
 |  - CMakeLists.txt
 - CMakeLists.txt
```

W folderze `lib/base32` należy zdefiniować target `base32`, który reprezentuje budowanie **shared object** zawierający kod biblioteki.
Wszystkie pięć plików `.hpp` oraz `.cpp` należy załączyć jako źródła targetu `base32`.

W folderze `src` należy zdefiniować target reprezentujący budowanie **pliku wykonywalnego** `l4_base32`.
Powinien polegać prywatnie na targecie `base32`.

Wspólne ustawienia flag kompilacji powinny być ustawione w głównym pliku `CMakeLists.txt`.

Aby sprawdzić, czy skompilowany program działa prawidłowo, wykonaj następujące kroki:
1. Skonfiguruj projekt cmake i wykonaj budowanie targetu `l4_base32`.
2. Wykonaj polecenie `echo "foobar" | path/to/built/executable/l4_base32`.
3. Wykonaj polecenie `echo "foobar" | basenc --base32hex`.
4. Wyjścia kroków 2. oraz 3. powinny być identyczne (konkretnie `CPNMUOJ1E850====`).

### Uruchomienie debuggera

W świecie GNU Linux standardem stał się debugger `gdb` (GNU debugger).
Debugger pozwala nam śledzić i modyfikować proces wykonania dowolnego programu.
W przypadku dzisiejszego laboratorium będziemy uzywać go do znalezienia błędu w trakcie używania biblioteki `base32`.
Najpierw jednak należy przygotować swoj program oraz środowisko programistyczne do używania debuggera.

Pierwszym krokiem jest upewnienie się, że każda jednostka translacji (plik `.o`) składający się na nasz program został zbudowany z flagą `-g`.
Flaga ta dodaje do wynikowego pliku wykonywalnego niezbędne wskazówki, aby odnaleźć miejsce w kodzie źródłowym związane z aktualnym miejscem w kodzie maszynowym.
Dodatkowo da nam także możliwość połączenia zawartości rejestrów procesora ze zmiennymi zdefiniowanymi w kodzie źródłowym.

#### Tryb konsolowy

Zacznijmy od najprostszego sposobu użycia `gdb` - trybu konsolowego.
Można go użyć, nie posiadając skonfigurowanego środowiska programistycznego.
Aby uruchomić nasz program pod kontrolą debuggera, należy wydać polecenie `gdb path/to/built/executable/l4_base32`.

W tym momencie debugger powinien dać działać programowi i ładować wszystkie potrzebne symbole.
Program powinien się zatrzymać w wejściu do funkcji `main`.
Teraz możemy pozwolić mu działać dalej poleceniem `run` lub wykonać pewne akcje (np. stawianie breakpointów poleceniem `break nazwa_pliku:nr_linii`).

Ten tryb działania debugger jest bardzo potężny i elastyczny, jednak nie należy do prostych w użyciu.
Aby odkryć pewną funkcję debuggera, należy się o niej dowiedzieć z [dokumentacji użytkownika](https://sourceware.org/gdb/current/onlinedocs/gdb.html/) i wprowadzić odpowiednie polecenie.
Nie jest to najszybszy sposób na zapoznanie się z podstawowymi funkcjonalnościami tego narzędzia.

Jeśli jednak jest to nasze jedyne wyjście (np. trzeba wykonać debuggowanie na komputerze bez środowiska graficznego), to istnieją w internecie tzw. *cheat-sheety* przygotowane przez bardziej doświadczonych użytkowników.
Ułatwiają one znalezienie potrzebnej akcji do wykonania w trakcie użytkowania (przykładowy [cheat-sheet](https://users.ece.utexas.edu/~adnan/gdb-refcard.pdf)).

**Proszę nie zapominać, że nie zastąpią one [dokumentacji użytkownika](https://sourceware.org/gdb/current/onlinedocs/gdb.html/) oraz polecenia `help`.**

#### Tryb graficzny

Używanie `gdb` w środowisku graficznym pozwala nam uprościć użytkowanie debuggera.
Mamy do dyspozycji integrację z naszym środowiskiem graficznym albo niezależne programy.
Na laboratorium zachęcamy do korzystania do integracji z ze swoim IDE, ponieważ projekt CMake umożliwia takie podejście.
Jeśli jednak nasze IDE nie wspiera integracji lub nie skonfigurowaliśmy go do odpowiedniego poziomu, można posłużyć się bardzo dobrym projektem [`gdbgui`](https://github.com/cs01/gdbgui/), który jest niezależnym webowym interfejsem graficznym.

### Użycie biblioteki GTest oraz przygotowanie testów jednostkowych

### Wczytanie *core dump* z momentu wystąpienia błędu

