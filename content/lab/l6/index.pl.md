---
title: "L6"
date: 2022-02-05T17:26:02+01:00
weight: 60
---

# Laboratorium 6
## Polimorfizm i Wyjątki

### 1. Wprowadzenie

Programowanie obiektowe (OOP) w C++ opiera się na kilku fundamentalnych zasadach, które umożliwiają tworzenie modułowego, wielokrotnego użytku i łatwego w utrzymaniu kodu. Cztery kluczowe filary OOP to abstrakcja, hermetyzacja, dziedziczenie i polimorfizm.
- **Abstrakcja** (ang. *abstraction*) polega na ukrywaniu szczegółów implementacyjnych i eksponowaniu jedynie istotnych cech obiektu, co pozwala użytkownikowi skupić się na tym, co dana klasa robi, a nie jak to robi.
- **Hermetyzacja** (ang. *encapsulation*) polega na ukrywaniu szczegółów działania obiektu przed jego użytkownikiem oraz na oddzieleniu interfejsu od implementacji. 
- **Dziedziczenie** (ang. *inheritance*) pozwala na tworzenie nowych klas (klas pochodnych) na bazie istniejących klas (klas bazowych), co promuje ponowne wykorzystanie kodu. 
- **Polimorfizm** (ang. *polymorphism*), czyli inaczej wielopostaciowość, umożliwia traktowanie obiektów różnych klas poprzez wspólny interfejs (klasy bazowej).

Zadanie polega na stworzeniu prostego systemu walk pomiędzy różnymi klasami postaci.

Skorzystaj z dostarczonego pliku [main.cpp](src/main.cpp), w którym umieszczone zostały testy do wszystkich etapów zadania.  
Po zakończeniu implementacji konkretnego etapu odkomentuj odpowiadającą mu część funkcji `main()` i porównaj swój wynik z oczekiwanym (**pamiętaj o załączeniu stworzonych przez ciebie plików w main.cpp**).

Tym razem nie został dostarczony żaden plik startowy do żadnego z etapów zadania. Klasy powinny być napisane od zera.

### Etap 1: Podstawowe Dziedziczenie i Polimorfizm

W pliku `Character.hpp` zdefiniuj abstrakcyjną klasę bazową `Character`. Powinna ona przechowywać podstawowe informacje o postaci (`name`, `health`). Kluczowym elementem jest czysto wirtualna metoda `attack()`, która pozwala na polimorficzne zachowanie różnych typów postaci.

**Pola prywatne**:
* `std::string name` - nazwa postaci
* `int health` - poziom życia postaci
* `int maxHealth` - maksymalny/początkowy poziom życia postaci

**Konstruktor**:
* Konstruktor przyjmujący dwa argumenty, nazwę postaci oraz ilość punktów życia - domyślnie 100.
  
**Metody**:
* `getName()`, `getHealth()`, `isAlive()` - gettery na pola klasy
* `takeDamage(int)` - metoda do zadawania obrażeń (wypisuje otrzymane obrażenia i pozostałe życie, oraz informację o pokonaniu postaci)
* `heal(int)` - metoda do leczenia postaci (wypisuje wyleczone życie i pozostałe życie)
* `attack(Character* target)` - wirtualna metoda
  
Ponieważ jest to klasa abstrakcyjna, pamiętaj również o zadeklarowaniu wirtualnego destruktora!

Dodaj dwie klasy dziedziczące po `Character`: `Warrior` oraz `Mage`.

W klasie `Warrior` dodaj prywatne pole `int meleeDamage` oraz konstruktor przyjmujący:
* `const std::string& name`
* `int health`, domyślnie wartość 120
* `int damage`, domyślnie wartość 15

W klasie `Mage` dodaj prywatne pole `int spellDamage` oraz konstruktor przyjmujący:
* `const std::string& name`
* `int health`, domyślnie wartość 80
* `int mana`, domyślnie wartość 150
* `int damage`, domyślnie wartość 20

Dla każdej z tych klas zaimplementuj metodę `attack`, w której zadawane są odpowiednio obrażenia przeciwnikowi o wartościach `meleeDamage` oraz `spellDamage`. Metody powinny wypisywać odpowiednie komunikaty o akcjach postaci (np. informacje o ataku, zadanych obrażeniach).

### Etap 2: Wielodziedziczenie i Wyjątki

Rozszerz system o wielodziedziczenie. Zdefiniuj dwie nowe "klasy cech": `CanCastSpells` oraz `CanUseMelee`. 

Zdefiniuj klasę wyjątku `NoManaException`, dziedziczącą po `std::exception`. Zaimplementuj metodę `what()` zwracającą opis błędu.

Klasa `CanCastSpells` posiada dwa pola:
* `int mana` - informacja o aktualnej ilości many
* `int maxMana` - maksymalna ilość many postaci
  
Oraz metody:
* `getMana()` - getter dla many
* `addMana(int amount)` - metoda dodaje wskazaną ilość many zachowując limit `maxMana` (wypisuje informację o dodanej many i aktualnym stanie)
* `useMana(int amount)` - metoda zużywa wskazaną ilość many (wypisuje informację o zużytej many i pozostałej ilości). W przypadku zbyt małej ilość powinna rzucać wyjątek `NoManaException`
* `castSpell(Character* target)` - metoda czysto wirtualna, będziemy ją później implementować w klasie postaci

Klasa `CanUseMelee` posiada jedynie metodę:
* `performMeleeAttack(Character* target)` - tak samo jak `castSpell`, metoda czysto wirtualna


Dodaj do klas `Warrior` oraz `Mage` odpowiednio dziedziczenie po `CanUseMelee` oraz `CanCastSpells` i zaimplementuj wymagane metody. Zmodyfikuj metody `attack()` tak by używały metod `castSpell` oraz `performMeleeAttack`. Rzucenie zaklęcia powinno zabierać 10 many. Metody powinny wypisywać komunikaty o wykonywanych akcjach (przygotowanie do ataku, wykonany atak z obrażeniami, informacje o zużyciu many). 

Zdefiniuj klasę `BattleMage` dziedziczącą po `Character`, `CanCastSpells`, `CanUseMelee`.
Zaimplementuj konstruktor `BattleMage`:
* `std::string name`
* `int health`, domyślnie 100
* `int mana`, domyślnie 100
* `int meleeDmg`, domyślnie 10
* `int spellDmg` domyślnie 15

Zaimplementuj polimorficzną metodę `attack()` w `BattleMage`. Wewnątrz tej metody losuj, czy użyć magii czy ataku fizycznego. Obsłuż potencjalny `NoManaException` wewnątrz metody attack, w przypadku braku many wykonaj atak wręcz `performMeleeAttack`. Załóż, że rzucenia zaklęcia zużywa 8 many (`castSpell`). Metoda powinna wypisywać komunikaty o wykonywanych akcjach.


### Etap 3: RTTI (`typeid`, `dynamic_cast`)

Dodaj klasę `Rogue` dziedziczącą po `Character` oraz po `CanUseMelee`.
Klasa ta posiada dwa pola:
* `int basicAttackDamage`
* `int backstabDamage`

Konstruktor przyjmuje:
* `std::string name`
* `int health`, domyślnie 90
* `int basicDmg`, domyślnie 12
* `int backstabDmg` domyślnie 30
  
Zmodyfikuj metodę `attack()` w `Mage` aby używała dynamicznego rzutowania do sprawdzenia, czy cel jest Wojownikiem lub posiada zdolności walki wręcz, zadając bonusowe obrażenia w takim przypadku (+10). Metoda powinna wypisać informację o bonusowych obrażeniach, jeśli występują.

Zaimplementuj specjalną metodę `backstab(Character* target)` w klasie `Rogue`. Użyj mechanizmu RTTI, aby sprawdzić, czy cel nie jest Magiem/Czarującym. Jeśli warunek spełniony, zadaj duże obrażenia (`backstabDamage`). W przeciwnym razie, wypisz komunikat, że dźgnięcie w plecy (backstab) się nie powiódł. Metoda powinna wypisywać komunikaty o próbie dźgnięcia oraz jego wyniku (sukces z obrażeniami lub porażka).

Zaimplementuj polimorficzną metodę `attack()` w klasie `Rogue`. Wewnątrz tej metody losuj, czy użyć zwykłego ataku wręcz czy spróbować wykonać dźgnięcie w plecy. Metoda powinna wypisywać komunikaty o podejmowanej akcji.

### Rozwiązanie

[Character.hpp](solution/Character.hpp)  
[Character.cpp](solution/Character.cpp)  
[main.cpp](solution/main.cpp)  
[Makefile](solution/Makefile)  
