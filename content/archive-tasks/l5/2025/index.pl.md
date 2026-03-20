---
title: "2025"
date: 2025-04-29T12:00:00+01:00
weight: 30
url: "/lab/l5/previous-years/2025/"
---

# Zadanie oceniane 5 [15 pkt]
## STL

W tym laboratorium twoim zadaniem będzie wykorzystanie klas szablonowych, kontenerów i algorytmów STL (standardowej biblioteki szablonów).

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

### Etap 1: Implementacja klasy szablonowej `Sensor<T>` [3 pkt]

W pliku `Sensor.hpp` zaimplementuj szablonową klasę `Sensor<T>`, która przechowuje dane z pojedynczego czujnika.

Struktura zagnieżdżona:
- `struct Identity`:
  - `std::string hardwareID` – np. „CPU0”, „GPU1”, „Disk A”.
  - `std::string type` – np. „thermal”, „power”.
  - Konstruktor inicjalizujący te pola.

Pola prywatne:
- `std::string label` - nazwa czujnika
- `std::variant<Identity, std::string> source` – pełna informacja lub tylko skrócona nazwa
- `std::optional<std::string> unit` - opcjonalna jednostka
- `std::vector<T> measurements` – dane pomiarowe

Konstruktor:
- Przyjmuje: nazwę czujnika, źródło (`Identity` lub `std::string`), opcjonalną jednostkę.
- Po konstrukcji obiekt powinien zawierać pustą listę pomiarów.

Gettery:
- `getLabel()`, `getSource()`, `getUnit()`, `getMeasurements()`

Oczekiwane wyjście:
```text
Sensor1 info:
Label: CPU Load
Source: CPU0 (thermal)
Unit: %

Sensor2 info:
Label: RAM Usage
Source: memory
```

### Etap 2: Rozbudowa Sensor<T> [4 pkt]

Metody:
- `getRMS()` – oblicza pierwiastek ze średniej kwadratów wartości (należy użyć `std::accumulate`)
- `getMin()` – zwraca najmniejszy pomiar (należy użyć odpowiedniej funkcji z nagłówka `algorithms`)
- W przypadku braku danych każda funkcja zwraca `T(0)`.

Operatory:
- `operator>` – porównuje po nazwie, a jeśli równa, to po liczbie pomiarów
- `operator!=` – porównuje tylko nazwę
- `operator<<` – dodaje pomiar do listy i zwraca referencję do obiektu
- `operator<<` (wypisywanie) – wypisuje czujnik w formacie:
    ```text
    <Label> [<hardwareID>, <type>] RMS: <rms>, Min: <min>
    Unit: <unit>
    ```
    Jeśli jednostka nie została ustawiona, pomiń drugą linię.

**Wskazówka**: Ponieważ `operator<<` zdefiniowany jest poza klasą `Sensor`, to nie ma on bezpośredniego dostępu do jej pól prywatnych. Aby rozwiązać ten problem możemy w klasie utworzyć pomocniczą funkcję, np. `writeToStream`, którą następnie wywołamy wewnątrz operatora.

Oczekiwane wyjście:
```text
Sensor1 RMS: 52.15, Min: 33.50
Sensor2 RMS: 72.07, Min: 65.00
Sensor3 RMS: 89.25, Min: 88.50
Sensor4 RMS: 0.00, Min: 0.00

CPU Load [CPU0, thermal] RMS: 52.15, Min: 33.50
Unit: %
RAM Usage [memory] RMS: 72.07, Min: 65.00
GPU Load [GPU0, graphics] RMS: 89.25, Min: 88.50
Unit: %
Fan Speed [cooling] RMS: 0.00, Min: 0.00
Unit: RPM

sensor1 != sensor2: true
sensor1 > sensor2: false
sensor3 > sensor1: true
sensor4 != sensor4: false
```

### Etap 3: Implementacja klasy SensorCollection [3 pkt]

W plikach `SensorCollection.hpp` i `SensorCollection.cpp` utwórz klasę przechowującą wiele czujników.

Pole:
- `std::unordered_map<std::string, std::list<Sensor<double>>> sensorsByType` – czujniki pogrupowane według typu (np. "thermal", "power")

Metody:
- `addSensor(const std::string& type, const Sensor<double>& sensor)` – dodaje sensor do odpowiedniej grupy
- `getSensorsByType()` – zwraca referencję do mapy
- `getAllSensors()` – zwraca wszystkie czujniki jako listę `std::list` bez podziału na typ

Operator:
- `operator<<` – wypisuje zawartość kolekcji:
    ```text
    === thermal ===
    CPU Load [CPU0, thermal] RMS: 50.25, Min: 33.50
    Unit: %
    === memory ===
    RAM Usage [memory] RMS: 71.75, Min: 65.00
    ```

Oczekiwane wyjście:
```text
=== graphics ===
GPU Load [GPU0, graphics] RMS: 89.25, Min: 88.50
Unit: %
=== thermal ===
CPU Load [CPU0, thermal] RMS: 52.15, Min: 33.50
Unit: %
Core Temp [CPU1, thermal] RMS: 41.01, Min: 40.00
Unit: °C
VRM Temp [thermal] RMS: 55.00, Min: 55.00
Unit: °C
=== memory ===
RAM Usage [memory] RMS: 72.07, Min: 65.00
=== cooling ===
Fan Speed [cooling] RMS: 0.00, Min: 0.00
Unit: RPM

Sensors in 'thermal':
CPU Load [CPU0, thermal] RMS: 52.15, Min: 33.50
Unit: %

Core Temp [CPU1, thermal] RMS: 41.01, Min: 40.00
Unit: °C

VRM Temp [thermal] RMS: 55.00, Min: 55.00
Unit: °C
```

### Etap 4: Algorytmy STL w SensorCollection [5 pkt]

Dodaj metody wykorzystujące różne algorytmy STL:

- `reverseSensors()` – odwraca kolejność listy w każdej kategorii (należy użyć `std::list::reverse`)
- `removeShortSensors(const std::string& type, std::size_t minCount)` – usuwa czujniki o liczbie pomiarów mniejszej niż `minCount` (należy użyć `std::list::remove_if`)
- `getTotalMinSum()` – zwraca sumę wartości minimalnych ze wszystkich czujników (należy użyć `std::accumulate`)
- `getSensorsContaining(const std::string& keyword)` – zwraca czujniki, których nazwa zawiera podany fragment (należy użyć `std::copy_if`)
- `findHighestRMS()` – zwraca czujnik o największej wartości RMS lub `std::nullopt` w przypadku jego braku (należy użyć `std::max_element`)

Oczekiwane wyjście:
```text
Total of minimum values across all sensors: 227.00
Total of minimum values across all sensors (empty collection): 0.00

Sensors containing 'Temp':
Core Temp [CPU1, thermal] RMS: 41.01, Min: 40.00
Unit: °C

Count of sensors containing 'RAM' (empty collection):0

[OK] Sensor with highest RMS:
GPU Load [GPU0, graphics] RMS: 89.25, Min: 88.50
Unit: %

This should be std::nullopt: OK
```

## Rozwiązania

[Makefile](solution/Makefile)

[Sensor.hpp](solution/Sensor.hpp)

[SensorCollection.cpp](solution/SensorCollection.cpp)

[SensorCollection.hpp](solution/SensorCollection.hpp)

[main.cpp](solution/main.cpp)
