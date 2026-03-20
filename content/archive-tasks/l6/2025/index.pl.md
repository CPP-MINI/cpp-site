---
title: "2025"
date: 2025-05-23T12:00:00+01:00
weight: 30
url: "/lab/l6/previous-years/2025/"
---

# Zadanie oceniane 6 [15 pkt]
## Polimorfizm

W tym laboratorium twoim zadaniem będzie wykorzystanie polimorfizmu, rzutowania dynamicznego oraz RTTI.

Skorzystaj z dostarczonego pliku [main.cpp](src/main.cpp), w którym umieszczone zostały testy dla wszystkich etapów zadania.
Po zakończeniu implementacji konkretnego etapu odkomentuj odpowiadającą mu część funkcji `main` i porównaj swój wynik z oczekiwanym
(**pamiętaj o załączeniu stworzonych przez ciebie plików w `main.cpp`**).

Dostarczony jest również startowy plik [Makefile](src/Makefile).

**Uwaga:**
- Etapy muszą być wykonywane po kolei.
- W razie wątpliwości co do np. kolejności argumentów lub innych tego typu szczegółów możesz spojrzeć na wywołania w `main.cpp`.

---

## Pliki startowe

[Makefile](src/Makefile)

[main.cpp](src/main.cpp)

Galaktyczna Federacja Handlowa (Galactic Trade Federation) potrzebuje nowego solidnego systemu do zarządzania swoją rozległą międzygwiezdną siecią logistyczną. 
System ten musi obsługiwać różne rodzaje ładunków, statków transportowych i regulacji międzyplanetarnych.
Używając polimorfizmu, dynamicznego rzutowania i RTTI pomóż stworzyć prototyp nowego systemu.

### Etap 1: Implementacja ładunku [4 pkt]

W pliku `Cargoes.hpp` stwórz abstrakcyjną klasę bazową `Cargo`, powinna ona zawierać następujące informacje na temat przewożonego ładunku: 
- 64-bitowy (bez znaku) unikalny numer identyfikacyjny ładunku (ID), numerowany od 1
- nazwę ładunku (`string`)

Publiczne gettery do przechowywanych pól:
- `getID()` - zwraca ID ładunku
- `getName()` - zwraca nazwę ładunku

Dodatkowo, klasa powinna dostarczać interfejs dla klas potomnych w celu zwrócenia następujących danych:
- `getDescription()` - opis ładunku (`string`)
- `getWeight()` - waga ładunku (`double`)

Zaimplementuj klasę `RawMaterialCargo` dziedziczącą po `Cargo` reprezentującą ładunek określonego surowca:
- `double purityPercentage` - stopień czystości surowca (0-100%)
- `double weight` - masa surowca

Konstruktor przyjmuje jako parametry `std::string name`, `double weight` oraz `double purity`.

Opis tego ładunku powinien być formatu:  
`{name} (ID: {id}) - Raw Material: Purity {purityPercentage}%`

Ponadto, zaimplementuj klasę `ManufacturedGoodsCargo` dziedziczącą po `Cargo` reprezentującą produkty pochodzące z fabryk Federacji. Klasa posiada następujące pola:
- `unsigned int unitCount` - ilość sztuk
- `double weightPerUnit` - waga jednej sztuki

Konstruktor przyjmuje jako parametry `std::string name`, `unsigned int count` oraz `double weightPU`.  
Metoda `getWeight()` zwraca masę całego załadunku.

Opis tego ładunku powinien być formatu:  
`{name} (ID: {id}) - Manufactured Goods: {unitCount} units`

Oczekiwane wyjście:
```text
 --------- Unrefined Spicestone (1) ---------
        Weight: 500
        Description: Unrefined Spicestone (ID: 1) - Raw Material: Purity 95.500000%
 --------- Xenon Blasters (2) ---------
        Weight: 250
        Description: Xenon Blasters (ID: 2) - Manufactured Goods: 10 units
 --------- Gaseous Helium-3 (3) ---------
        Weight: 150
        Description: Gaseous Helium-3 (ID: 3) - Raw Material: Purity 99.000000%
 --------- Medical Droids (4) ---------
        Weight: 150
        Description: Medical Droids (ID: 4) - Manufactured Goods: 2 units
 --------- Live Xenoflora Specimen (5) ---------
        Weight: 15
        Description: Live Xenoflora Specimen (ID: 5) - Manufactured Goods: 1 units
 --------- Synthetic Nutrient Paste (Bulk) (6) ---------
        Weight: 800
        Description: Synthetic Nutrient Paste (Bulk) (ID: 6) - Raw Material: Purity 100.000000%
 --------- Cryogenic Data Core (7) ---------
        Weight: 0.5
        Description: Cryogenic Data Core (ID: 7) - Manufactured Goods: 1 units
 --------- Pre-Fabricated Colony Modules (8) ---------
        Weight: 20000
        Description: Pre-Fabricated Colony Modules (ID: 8) - Manufactured Goods: 4 units
 --------- Ancient Alien Artifact (9) ---------
        Weight: 10
        Description: Ancient Alien Artifact (ID: 9) - Manufactured Goods: 1 units
```

### Etap 2: Implementacja floty [4 pkt]

W pliku `TransportVessels.hpp` stwórz abstrakcyjną klasę bazową `TransportVessel`, reprezentującą statek floty. Każdy statek posiada:
- identyfikator będący nazwą statku (`string`)
- listę ładunku (`std::vector<Cargo*>`)
- masę aktualnego załadunku (`currentLoad`) typu `double`

Gettery:
- `getCurrentLoad()` - zwraca wartość masy aktualnego załadunku
- `getID()` - zwraca identyfikator/nazwę statku
- `getLoadedCargo()` - zwraca listę z ładunkiem

Dodatkowo, za pomocą metody `getMaxCapacity()` można pobrać informację informację o maksymalnej ładowności statku. Metoda powinna zwracać wartość `-1` jeżeli statek nie posiada ładowni zdolnej do przenoszenia towarów.

Metoda `bool loadCargo(Cargo* cargo)` pozwala na dodanie ładunku do ładowni statku. Implementacja tej metody powinna zależeć od typu statku.

Dodaj dwa typy statków `Freighter` oraz `ScoutShip`:
- `Freighter` jest w stanie załadować ładunek o dowolnej masie o ile mieści się w ładowni (`maxCapacity`). 
- `ScoutShip` jest w stanie załadować ładunki nie przekraczające masy `200.0` oraz mieszczące się w ładowni.

Konstruktor obu klas jako parametry przyjmuje `std::string id` i `double capacity`.

W przypadku kiedy załadunek nie jest możliwy wypisz komunikat `{vesselID} cannot load {cargoDescription}. Exceeds capacity of {maxCapacity} units."` oraz zwróć wartość `false`.

Oczekiwane wyjście:
```text
Loading vessels with cargo:
GTF-FR-Alpha-001 loaded Unrefined Spicestone (ID: 1) - Raw Material: Purity 95.500000%. Current load: 500 / 1000
GTF-FR-Alpha-001 loaded Xenon Blasters (ID: 2) - Manufactured Goods: 10 units. Current load: 750 / 1000
GTF-FR-Alpha-001 loaded Gaseous Helium-3 (ID: 3) - Raw Material: Purity 99.000000%. Current load: 900 / 1000
GTF-FR-Alpha-001 cannot load Medical Droids (ID: 4) - Manufactured Goods: 2 units. Exceeds capacity of 1000 units.
GTF-PD-Epsilon-004 loaded Live Xenoflora Specimen (ID: 5) - Manufactured Goods: 1 units. Current load: 15 / 1500
GTF-PD-Epsilon-004 cannot load Synthetic Nutrient Paste (Bulk) (ID: 6) - Raw Material: Purity 100.000000%. Exceeds capacity of 1500 units.
GTF-MF-Eta-006 loaded Cryogenic Data Core (ID: 7) - Manufactured Goods: 1 units. Current load: 0.5 / 100
GTF-MF-Eta-006 cannot load Pre-Fabricated Colony Modules (ID: 8) - Manufactured Goods: 4 units. Exceeds capacity of 100 units.
GTF-MF-Eta-006 loaded Ancient Alien Artifact (ID: 9) - Manufactured Goods: 1 units. Current load: 10.5 / 100

Vessels:
ID: GTF-FR-Alpha-001
        Load: 900/1000
        Cargo count: 3
ID: GTF-SC-Beta-002
        Load: 0/75
        Cargo count: 0
ID: GTF-PD-Epsilon-004
        Load: 15/1500
        Cargo count: 1
ID: GTF-MF-Eta-006
        Load: 10.5/100
        Cargo count: 2
```

### Etap 3: Niebezpieczne odpady [3 pkt]

Federacja posiada również kontrakt na przewóz niebezpiecznych odpadów, które mogą być jedynie transportowane przez odpowiednio do tego przystosowane statki.

Dodaj nowy typ ładunku `HazardousWasteCargo`, który posiada:
- `DangerLevel dangerLevel` - stopień poziom zagrożenia materiału - reprezentowany przez silną enumeracja `DangerLevel`, która może przyjmować wartości `LOW=0`, `MEDIUM=1`, `HIGH=2` lub `CRITICAL=3`.
- `double weight` - masa odpadów

Konstruktor przyjmuje jako parametry `std::string name`, `double weight` oraz `DangerLevel danger`.

Opis tego ładunku powinien być formatu:  
`{name} (ID: {id}) - Hazardous Waste: Danger Level {levelStr}`, gdzie `levelStr` to wartość tekstowa odpowiadająca stopniowi zagrożenia materiału.

Zmodyfikuj metody `loadCargo(Cargo* cargo)` używając dynamicznego rzutowania tak, aby:
- statki `Freighter` w przypadku załadunku `HazardousWasteCargo` wypisywały komunikat:  
  `WARNING: Hazardous Waste Cargo ({name}, Danger Level: {dangerLevel}) loaded!`
- statki `ScoutShip` są w stanie jedynie przewozić materiały których poziom niebezpieczeństwa to `LOW` oraz wyświetlają komunikat:  
  `WARNING: Hazardous Waste Cargo ({name}, Danger Level: {dangerLevel}) loaded!`

Oczekiwane wyjście:
```text
New Hazardous Waste Cargo:
 --------- Corrosive Sludge (10) ---------
        Weight: 100
        Description: Corrosive Sludge (ID: 10) - Hazardous Waste: Danger Level High
 --------- Defective Gravitron Flux Capacitors (11) ---------
        Weight: 120
        Description: Defective Gravitron Flux Capacitors (ID: 11) - Hazardous Waste: Danger Level Low
 --------- Stabilized Antimatter Rods (12) ---------
        Weight: 250
        Description: Stabilized Antimatter Rods (ID: 12) - Hazardous Waste: Danger Level CRITICAL

Loading hazardous waste:
GTF-PD-Epsilon-004 cannot load Corrosive Sludge (ID: 10) - Hazardous Waste: Danger Level High. Too dangerous to ship!
Result: OK
  WARNING: Hazardous Waste Cargo (Corrosive Sludge, Danger Level: 2) loaded!
GTF-FR-Alpha-001 loaded Corrosive Sludge (ID: 10) - Hazardous Waste: Danger Level High. Current load: 1000 / 1000
Result: OK
  WARNING: Hazardous Waste Cargo (Defective Gravitron Flux Capacitors, Danger Level: 0) loaded!
GTF-PD-Epsilon-004 loaded Defective Gravitron Flux Capacitors (ID: 11) - Hazardous Waste: Danger Level Low. Current load: 235 / 1500
Result: OK
GTF-PD-Epsilon-004 cannot load Stabilized Antimatter Rods (ID: 12) - Hazardous Waste: Danger Level CRITICAL. Exceeds capacity of 1500 units.
Result: OK
```

### Etap 4: Generowanie raportu stanu floty [4 pkt]

Federacja potrzebuje okresowo sporządzać raporty ze stanu swojej floty. W pliku o nazwie `LogisticsReport` stwórz metodę `generateLogisticsReport(const std::vector<TransportVessel*>& allVessels)`, która dla każdego statku wypisuje jego dane oraz stan ładowni.

Aby pobrać typ statku oraz ładunku użyj mechanizmu RTTI.
Dla ładunku typu `HazardousWasteCargo` dodatkowo wypisz linię `Danger Level: {dangerLevel}`, gdzie `dangerLevel` to wartość liczbowa stopnia niebezpieczeństwa materiału. Dla pustego statku wypisz `"--- NONE ---"`.

Oczekiwane wyjście:
```text
- ID: GTF-FR-Alpha-001, Type: class Freighter
     Current Load: 1000 / 1000
     Cargo Inventory:
     1. ID: 1, Type: class RawMaterialCargo
        Desc: Unrefined Spicestone (ID: 1) - Raw Material: Purity 95.500000%
     2. ID: 2, Type: class ManufacturedGoodsCargo
        Desc: Xenon Blasters (ID: 2) - Manufactured Goods: 10 units
     3. ID: 3, Type: class RawMaterialCargo
        Desc: Gaseous Helium-3 (ID: 3) - Raw Material: Purity 99.000000%
     4. ID: 10, Type: class HazardousWasteCargo
        Desc: Corrosive Sludge (ID: 10) - Hazardous Waste: Danger Level High
        Danger Level: 2
- ID: GTF-SC-Beta-002, Type: class ScoutShip
     Current Load: 0 / 75
     Cargo Inventory:
        --- NONE ---
- ID: GTF-PD-Epsilon-004, Type: class ScoutShip
     Current Load: 235 / 1500
     Cargo Inventory:
     1. ID: 5, Type: class ManufacturedGoodsCargo
        Desc: Live Xenoflora Specimen (ID: 5) - Manufactured Goods: 1 units
     2. ID: 10, Type: class HazardousWasteCargo
        Desc: Corrosive Sludge (ID: 10) - Hazardous Waste: Danger Level High
        Danger Level: 2
     3. ID: 11, Type: class HazardousWasteCargo
        Desc: Defective Gravitron Flux Capacitors (ID: 11) - Hazardous Waste: Danger Level Low
        Danger Level: 0
- ID: GTF-MF-Eta-006, Type: class Freighter
     Current Load: 10.5 / 100
     Cargo Inventory:
     1. ID: 7, Type: class ManufacturedGoodsCargo
        Desc: Cryogenic Data Core (ID: 7) - Manufactured Goods: 1 units
     2. ID: 9, Type: class ManufacturedGoodsCargo
        Desc: Ancient Alien Artifact (ID: 9) - Manufactured Goods: 1 units
------------------------------------------------
```

## Rozwiązania

[Cargoes.cpp](solution/Cargoes.cpp)

[Cargoes.hpp](solution/Cargoes.hpp)

[LogisticsReport.cpp](solution/LogisticsReport.cpp)

[LogisticsReport.hpp](solution/LogisticsReport.hpp)

[Makefile](solution/Makefile)

[TransportVessels.cpp](solution/TransportVessels.cpp)

[TransportVessels.hpp](solution/TransportVessels.hpp)

[main.cpp](solution/main.cpp)
