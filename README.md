# `myVector<T>` — Funkcijų dokumentacija

`myVector<T>` — rankiniu būdu realizuota dinaminio masyvo klasė, analogiška `std::vector<T>`.

| Narys | Tipas | Reikšmė |
|---|---|---|
| `data` | `T*` | Rodyklė į dinamiškai allokuotą masyvą |
| `_size` | `size_t` | Kiek elementų šiuo metu yra vektoriuje |
| `_capacity` | `size_t` | Kiek elementų telpa be papildomos alokacijos |

---

## Copy konstruktorius

```cpp
myVector(const myVector& other)
```

Sukuria naują vektorių kaip pilną `other` kopiją. Alokuojamas atskiras atminties blokas ir nukopijuojami visi elementai.

**Naudojimas:**
```cpp
myVector<int> v1;
v1.push_back(1);
myVector<int> v2 = v1; // v2 yra atskira kopija
```

**Sudėtingumas:** O(n)

---

## Move konstruktorius

```cpp
myVector(myVector&& other) noexcept
```

Sukuria naują vektorių **perimdamas** `other` atminties bloką — duomenys nekopijuojami. Po perkėlimo `other` tampa tuščias.

**Naudojimas:**
```cpp
myVector<int> v2 = std::move(v1); // v1 tampa tuščias
```

**Sudėtingumas:** O(1)

---

## `push_back`

```cpp
void push_back(const T& value)
```

Prideda elementą vektoriaus gale. Jei `_size == _capacity`, talpa padvigubinama prieš pridedant.

**Naudojimas:**
```cpp
myVector<int> v;
v.push_back(10); // [10]
v.push_back(20); // [10, 20]
v.push_back(30); // [10, 20, 30]
```

**Talpos plėtimas:**
```
capacity = 0 → 1 → 2 → 4 → 8 → ...
```

**Sudėtingumas:** O(1)

---

## `insert`

```cpp
iterator insert(iterator pos, const T& value)
```

Įterpia elementą į poziciją `pos`. Visi elementai nuo `pos` iki galo pasislenka per vieną poziciją į dešinę. Grąžina iteratorių į įterptą elementą.

**Naudojimas:**
```cpp
// v = [1, 2, 4]
v.insert(v.begin() + 2, 3);
// v = [1, 2, 3, 4]
```

**Elemento perkėlimas:**
```
Prieš: [1] [2] [4] [ ]
Po:    [1] [2] [3] [4]
```

**Sudėtingumas:** O(n)

---

## `erase`

```cpp
iterator erase(iterator pos)
```

Pašalina elementą iš pozicijos `pos`. Visi elementai po jo pasislenka per vieną poziciją į kairę. Grąžina iteratorių į elementą, kuris atsidūrė ištrintoje pozicijoje. Meta `std::out_of_range` jei `pos` už ribų.

**Naudojimas:**
```cpp
// v = [1, 2, 3, 4]
v.erase(v.begin() + 1);
// v = [1, 3, 4]
```

**Elemento perkėlimas:**
```
Prieš: [1] [2] [3] [4]
Po:    [1] [3] [4]
```

**Sudėtingumas:** O(n)

---

