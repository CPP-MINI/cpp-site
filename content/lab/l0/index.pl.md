---
title: "L0"
date: 2026-02-08T19:27:02+01:00
weight: 10
---

# Laboratorium 0

## Środowisko programistyczne
Zanim przejdziemy do właściwej treści, musimy wybrać edytor, w którym będziemy pisali kod.
W poprzednim semestrze było to Visual Studio.
Nie ma ono swojej wersji na Linuxa (wielu programistów powiedziałoby: i bardzo dobrze, nie chcemy go).
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

## Kompilowanie programów
Kiedy twój edytor stoi już przed tobą otworem, sprawdźmy zatem, czy działa jak należy.
Jako pierwsze zadanie stwórz program, wypisujący twoje:
1. imię,
2. nazwisko,
3. nr indeksu.

W przeciwieństwie do poprzedniego semestru tutaj będziemy używać **C++**.
Poniżej znajdziesz najprostszy program wypisujący wybrany tekst na standardowe wyjście.

```cpp
// Wczytanie definicji funkcji operujących na strumieniach wejścia-wyjścia 
// (analogiczne do <stdio.h> z C)
#include <iostream> 

int main()
{
  // Wypisanie ciągu na standardowe wyjście oraz zakończenie znakiem końca linii 
  // (analogiczne do puts z C)
  std::cout << "Jan Dzban, 123456" << std::endl;
  return 0;
}
```

Powyższy program po rozpoczęciu wypisuje na standardowe wyjście tekst znajdujący się w kodzie i od razu się kończy.
Więcej szczegółów obsługi strumieni w C++ dowiesz się na kolejnych warsztatach.

Stwórz plik o nazwie `hello.cpp` i otwórz go za pomocą twojego edytora.
Skopiuj przykład i zmień jego zawartość na dane opisujące ciebie.
Gdy plik będzie gotowy, uruchom terminal w miejscu utworzenia pliku.
Każde ze środowisk programistycznych powinno mieć opcję uruchomienia terminala w ramach swojego okna.
Skonsultuj dokumentację środowiska, aby odnaleźć tę funkcję.
Będzie bardzo przydatna przez cały semestr.
Jeśli nie uda ci się znaleźć tej funkcji, uruchom terminal w oddzielnym oknie.

Teraz należy **skompilować** program, aby komputer mógł wykonać przekazane mu instrukcje w języku **C++**.
Do tego zadania służy **kompilator**.
Każdy szanujący się system operacyjny dostarczany jest z pewnym kompilatorem języka C.
W dużej mierze w komplecie instalowane są także kompilatory języka C++.
W przypadku naszego laboratorium mamy do dyspozycji kompilatory **GCC** (GNU Compiler Collection).
Interesować nas będzie program o nazwie `g++`, który jest kompilatorem języka C++.

Skompiluj swój przykładowy program poleceniem
```sh
g++ -o hello hello.cpp
```
Powyższe polecenie uruchamia kompilator i instruuje go, aby potraktował plik `hello.cpp` jako kod źródłowy (wejście) oraz wygenerował gotowy program wykonywalny o nazwie `hello` (wyjście).
Jeśli kod posiada błędy (jest niezgodny ze składnią języka C++), kompilator wypisze błąd i zakończy się niepowodzeniem.
W przeciwnym wypadku w bieżącym katalogu roboczym stworzony zostanie plik `hello`, który można uruchomić poleceniem
```sh
./hello
```
Dla przykładowego programu wyjście powinno wyglądać
```
Jan Dzban, 123456
```

Gdy już mamy możliwość pisania kodu, możemy przejść do dzielenia się nim z innymi programistami.

## Git
Git (z ang. „głupek”) jest programem, tak zwanym **systemem kontroli wersji**, którego współcześnie używa praktycznie każdy programista.
Pozwala on na udostępnianie kodu źródłowego między programistami i modyfikowanie go (zamiast np. wysyłania sobie ręcznie mailem plików z kodem).
W połączeniu z serwerem (często github.com) pozwala na przechowywanie kodu w chmurze (czyli na cudzym komputerze).
W przypadku naszych laboratoriów Git posłuży nam do współdzielenia kodu między studentami a prowadzącymi.
Każde zadanie oceniane będzie udostępniane w tak zwanym **repozytorium**.
Umiejętność korzystania z Gita jest obowiązkowa na wszystkich laboratoriach ocenianych w zakresie pozwalającym na przekazanie rozwiązania zadania laboratoryjnego.
Tylko kod znajdujący się w repozytorium na koniec zajęć podlega ocenie!

Poniżej znajduje się prosta instrukcja korzystania z Gita.
Osoby zainteresowane zachęcam do głębszego zapoznania z tematem, w szczególności dzięki oficjalnej [książce](https://git-scm.com/book/en/v2).

### 1. Konfiguracja Gita
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

### 2. Repozytoria
Każdy projekt związany jest z repozytorium -- to w nim przechowywany jest kod i jego historia.
Repozytoria możemy tworzyć lub **klonować** z serwera.
W przypadku tych zajęć repozytoria będą klonowane przez każdego studenta.

### 3. Podstawowe operacje
Załóż konto w serwisie [Github](github.com).
Utwórz nowe repozytorium i spróbuj wykonać na nim poniższe operacje.

Aby sklonować repozytorium, używamy polecenia
```sh
git clone <adres repozytorium>
```

Każdy nowy plik musi zostać dodany do Gita, aby go śledzić:
```sh
git add <nazwa pliku>
```
Do Gita dodajemy tylko kod źródłowy.
Nie dodajemy nigdy plików, które powstają przy kompilacji!
Z pomocą przychodzi specjalny plik `.gitignore`, który pozwala ignorować pliki o wybranej nazwie.

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

### 4. Połączenie z systemem wydziałowym
Aby połączyć się z naszym systemem udostępniającym repozytoria, z sieci wydziałowej wejdź na stronę [ghlabs](https://ghlabs.mini.pw.edu.pl/) i połącz swoje konto GitHub z kontem USOS.
Dzięki temu w trakcie laboratoriów ocenianych uzyskasz dostęp do repozytorium na Twoje rozwiązanie.

Aby uzyskać dostęp do systemu spoza sieci wydziałowej, najprostszym sposobem jest dodać do pliku `/etc/hosts` (na Windowsie: `%systemroot%\System32\Drivers\etc\hosts`) poniższy wpis:
```
194.29.178.38 ghlabs.mini.pw.edu.pl
```
Po dodaniu takiego wpisu wyżej wspomniana strona powinna się normalnie otwierać.

## Zadanie na dziś - zaznaczenie obecności

Aby potwierdzić działanie twojej konfiguracji gita, twoim zadanie jest przesłanie przykładowego programu do repozytorium udostępnionego w ramach systemu ghlabs.
Wykonaj następujące kroki:
1. Odnajdź przyporządkowane do ciebie repozytorium o nazwie podobnej do `WUT-MiNI/P2_26L_{USOS_ID}_L0`.
2. Wykonaj operację `git clone`.
3. Skopiuj plik `hello.cpp` (nie kopiuj pliku `hello` - to każdy może utworzyć z kodu źródłowego).
4. Dodaj pliki do śledzonych poleceniem `git add hello.cpp`.
5. Potwierdź status repozytorium poprzez `git status`.
6. Zatwierdź zmiany w repozytorium wykonując `git commit -m "Example hello program"`.
7. Wyślij zmiany do zdalnego repozytorium poprzez polecenie `git push`.
