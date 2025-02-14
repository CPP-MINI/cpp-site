---
title: "L1"
date: 2022-02-05T17:26:02+01:00
weight: 10
---

# Laboratorium 1
## Translacja

W tym zadaniu stworzysz prosty projekt w C++ składający się z:
- Dwóch programów, z czego na jeden z nich składać się będzie wiele plików `.cpp`.
- Biblioteki statycznej.
- Biblioteki współdzielonej.

Ani podczas tego laboratorium, ani podczas któregokolwiek przyszłego (o ile nie będzie to wprost sprecyzowane), nie używaj standardowej biblioteki C (czyli np. `stdio.h`, `string.h` itd.).
W pełni dozwolone (o ile nie będzie to wprost zabronione) jest i będzie korzystanie z biblioteki C++ (czyli np. `vector`, `string`).

**Skorzystaj z następującego kodu startowego**: [greeter.cpp](src/greeter.cpp) [program_2.cpp](src/program_2.cpp).

### Środowisko programistyczne
Zanim przejdziemy do właściwej treści, musimy wybrać edytor, w którym będziemy pisali kod.
W poprzednim semestrze było to Visual Studio.
Nie ma ono swojej wersji na Linuxa (wielu programistów powiedziało by: i bardzo dobrze, nie chcemy go).
W naszym laboratorium dostępne jest:
- Visual Studio Code -- niemające wiele wspólnego z Visual Studio środowisko (też wydawane przez Microsoft). Ma mniejszą funkcjonalność, ale dzięki temu jest znacznie szybsze i lżejsze.
- CLion -- cięższe środowisko mające bardziej rozbudowaną funkcjonalność, bardziej przypominające Visual Studio.
- Vim -- edytor tekstowy w terminalu. Bez odpowiedniej konfiguracji korzystanie z niego byłoby bardzo nieprzyjemne. Wbrew pozorom pozwala jednak na bardzo wiele rozszerzeń. Możliwości rozbudowy są jednak znacznie większe, niż w wymienionych wyżej edytorach.
- Emacs -- edytor tekstowy, który podobnie jak vim, pozwala na dowolne rozbudowywanie funkcjonalności.
- Geany -- prosty edytor tekstowy, bez wielkich możliwości rozbudowy.

Wybór środowiska zależy od każdego indywidualnie.
Na początek zarekomendowałbym Visual Studio Code lub CLion.
Osoby bardziej ambitne, chcące zbudować sobie swoje własne środowisko od podstaw zachęcam do spróbowania Vima lub Emacsa. W internecie znajdziemy setki poradników, jak to zrobić.

Na kolejnych laboratoriach, w szczególności na laboratoriach ocenianych, zakładamy znajomość z wybranym środowiskiem.

### Program z wieloma plikami
Utwórz trzy nowe pliki: `program_1.cpp`, `vars.hpp` i `vars.cpp`.
Wszystkie te pliki kompilowane będą do jednego programu o nazwie `program_1`.
W pliku `vars.cpp` utwórz dwie zmienne globalne typu `int` o nazwach `global_extern` i `global_static`.
Pierwsza z nich jest zwykłą zmienną, a druga statyczną.
Obie zainicjuj wartością 0.
Utwórz też w tym pliku dwie funkcje.
- `void inc_vars()`, które wypisuje na ekran ,,Increasing...", a potem zwiększa wartość obu zmiennych o 1.
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

Dodatkowo w pliku zdefiniujemy dwa cele ,,oszukańcze", tzn. takie, które nie odnoszą się do żadnego pliku.
Pierwszym z nich będzie `clean`.
Pozwoli on nam na szybkie usuwanie wszystkich plików wynikowych kompilacji poleceniem `make clean`.
Aby zdefiniować ten cel dodajemy do naszego `Makefile`:
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
Dodaj do pliku `Makefile` instrukcje budujące tę bibliotekę,
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
  Czyli dla prowincji ,,Ægyptus" z miastami ,,Alexanria" i ,,Ptolemais" poprawnym wynikiem jest
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

### Git
Git (z ang. ,,głupek") jest programem, tak zwanym **systemem kontroli wersji**, którego współcześnie używa praktycznie każdy programista.
Pozwala on na udostępnianie kodu źródłowego między programistami i modyfikowanie go (zamiast np. wysyłania sobie ręcznie mailem plików z kodem).
W połączeniu z serwerem (często github.com) pozwala na przechowywanie kodu w chmurze (czyli na cudzym komputerze).
W przypadku naszych laboratoriów Git posłuży nam do współdzielenia kodu między studentami a prowadzącymi.
Każde zadanie oceniane będzie udostępniane w tak zwanym **repozytorium**.
Umiejętność korzystania z Gita jest obowiązkowa na wszystkich laboratoriach ocenianych w zakresie pozwalającym na przekazanie rozwiązania zadania laboratoryjnego.
Tylko kod znajdujący się w repozytorium na koniec zajęć podlega ocenie!

Poniżej znajduje się prosta instrukcja korzystania z Gita.
Osoby zainteresowane zachęcam do głębszego rozeznania w temacie, w szczególności dzięki oficjalnej [książce](https://git-scm.com/book/en/v2).

#### 1. Konfiguracja Gita
Przed pierwszym użyciem należy skonfigurować swoją tożsamość:
```sh
git config --global user.name "Twoje Imię i Nazwisko"
git config --global user.email "twoj@email.com"
```
Możesz sprawdzić swoją konfigurację za pomocą:
```sh
git config --list
```
To działanie jest wymagane tylko raz.

#### 2. Repozytoria
Każdy projekt związany jest z repozytorium -- to w nim przechowywany jest kod i jego historia.
Repozytoria możemy tworzyć, lub **klonować** z serwera.
W przypadku tych zajęć, repozytoria będą klonowane przez każdego studenta.

#### 3. Podstawowe operacje
Załóż konto w serwisie [Github](github.com).
Utwórz nowe repozytorium i spróbuj wykonać na nim poniższe operacje.

Aby sklonować repozytorium używamy polecenia
```sh
git clone <adres repozytorium>
```

Każdy nowy plik musi zostać dodany do Gita, aby go śledzić:
```sh
git add <nazwa pliku>
```
Do gita dodajemy tylko kod źródłowy (w tym pliki `Makefile`).
Nie dodajemy nigdy plików, które powstają przy kompilacji!

Aby sprawdzić, jakie pliki zostały zmodyfikowane od ostatniego zapisania zmian:
```sh
git status
```

Zatwierdzenie zmian zapisuje je w historii repozytorium:
```sh
git commit -m "Opis zmian"
```

Aby sprawdzić historię zapisanych zmian, możemy użyć
```sh
git log
```

Wysłanie zmian na serwer wykonujemy przez
```sh
git push origin main
```

#### 4. Połączenie z systemem wydziałowym
Aby połączyć się z naszym systemem udostępniającym repozytoria, z sieci wydziałowej wejdź na stronę [ghlabs](ghlabs.mini.pw.edu.pl) i połącz swoje konto na Githubie z kontem USOS.
Dzięki temu w trakcie laboratoriów ocenianych uzyskasz dostęp do repozytorium na Twoje rozwiązanie.
