# Laboratorium 3 - Pamięć
## Przewodnik prowadzącego · ~90 min

| # | Opis kroku | Typ | Czas |
|---|------------|-----|-----:|
| 1 | Stos vs sterta, czas życia zmiennych | wykład | 10 min |
| 2 | `enum class`, kwalifikowanie nazw (własna przestrzeń nazw), `fruit.hpp` | praca własna | 10 min |
| 3 | `Vector3`, trzy rodzaje tablic - kiedy zmienia się `data()`, czemu `delete[] =/= delete` | praca własna | 20 min |
| 4 | Hex dump, IEEE 754, implementacja `dump_memory` | wykład + praca własna | 15 min |
|   | *Fun fact: `0.1` nie ma dokładnej reprezentacji binarnej, stąd `0.1 + 0.2 != 0.3`* | | |
| 5 | `alignas`, `holey_char`, strict aliasing jako celowe UB - wzmianka o steganografii | praca własna | 20 min |
| 6 | `memcpy` vs `memmove`, nachodzące bufory, `size_t` - implementacja własnych wersji | praca własna | 15 min |
|   | *Fun fact: standard celowo nie gwarantuje poprawności `memcpy` dla nachodzących buforów, żeby umożliwić optymalizacje SIMD* | | |
