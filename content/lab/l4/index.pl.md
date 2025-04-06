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

### Uruchomienie debuggera

#### Tryb konsolowy

#### Tryb graficzny

### Użycie biblioteki GTest oraz przygotowanie testów jednostkowych

### Wczytanie *core dump* z momentu wystąpienia błędu

