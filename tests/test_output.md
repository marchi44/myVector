## test_functions.cpp output
```
[doctest] doctest version is "2.5.2"
[doctest] run with "--help" for options
===============================================================================
[doctest] test cases:  46 |  46 passed | 0 failed | 0 skipped
[doctest] assertions: 213 | 213 passed | 0 failed |
[doctest] Status: SUCCESS!
```
## Efektyvumo analizė: `std::vector` vs `myVector`

- Kiekvienas matavimas kartojamas 5 kartus, pateikiamas vidurkis (ms).
- Kompiliuota su `-O2` optimizacija.

| Elementų sk. | std::vector (ms) | myVector (ms) |
|---|---|---|
| 10000 | 0.0202178 | 0.0058556 |
| 100000 | 0.450682 | 0.346912 |
| 1000000 | 4.34137 | 3.82052 |
| 10000000 | 63.0205 | 60.3083 |
| 100000000 | 1319.15 | 555.826 |

`myVector` visais atvejais veikia greičiau nei `std::vector`. Tai galima
paaiškinti tuo, kad:
- `std::vector` turi papildomą logiką: išimčių saugumą,
iterator invalidation tikrinimą ir kitus standarto
reikalavimus. 
- `myVector` yra minimali implementacija be šių sluoksnių,
todėl `push_back` ciklas vykdomas greičiau. 

## Atminties perskirstymų skaičius (100 000 000 elementų)

| Konteineris | Perskirstymų sk. |
|---|---|
| `std::vector` | 27 |
| `myVector` | 27 |

Abu vektoriai naudoja padvigubinimo strategiją (capacity × 2), todėl
perskirstymų skaičius identiškas — ⌈log₂(100 000 000)⌉ = 27.