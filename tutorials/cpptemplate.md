# cpptemplate

This is the starting C++ template, which includes a variety of macros, shortened type names, common constants and helper functions.

## Macros
`all(x)` and `rall(x)`:
```cpp
accumulate(all(a), 0LL);
sort(rall(a));
```

---

uncomment `#define x first` and `#define y second` for geometry problems.

---

`debug(var)` helps debugging by listing the variable names and their values.

## Shortened type names
|  Shortened form  |           Type name          |             Common usage             |
|:----------------:|:----------------------------:|:------------------------------------:|
|       `ll`       |          `long long`         | numbers ranges from $1$ to $10^{18}$ |
|       `vi`       |         `vector<int>`        | array of integers                    |
|       `vii`      |     `vector<vector<int>>`    | 2D array                             |
|       `vll`      |      `vector<long long>`     | array of large numbers               |
|       `vb`       |        `vector<bool>`        | array of booleans                    |
|       `pii`      |       `pair<int, int>`       | coordinates or positions             |
|       `pll`      | `pair<long long, long long>` | extended coordinates                 |

## Common constants
|  Variable name  |         Value         |                Usage                |
|:---------------:|:---------------------:|:-----------------------------------:|
|      `MOD`      |    $1'000'000'007$    | $10^9 + 7$ prime modulo             |
|      `MOD`      |      $998244853$      | another prime modulo                |
|      `INF`      |      $1061109567$     | infinite under int constraint       |
|     `LLINF`     | $4557430888798830399$ | infinite under long long constraint |

## Helper functions
Auto input for
- vectors
- pairs
- arrays
- tuples

---

`chmin` and `chmax` for `check min/max`, setting the min or max and returning a boolean of whether the value is changed.

