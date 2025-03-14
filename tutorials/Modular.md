# Modular

The Modular class – which is often called the Modular Integer in full name, is a template class which tackles problems involving modulo operations. For example, some problems would need modulo the answer to a large prime number like $10^9 + 7$ like [this one](https://syoj.org/judge/problems/C001) created by me. So let's see how this class works.

---

Start by defining the modulo and the Modular Integer class like so:
```cpp
const int MOD = 1e9 + 7;
using mint = Modular<MOD>;
```

Note that the parameter `<MOD>` must be a constant value of prime number, which is ensured in C++20 [concepts](https://en.cppreference.com/w/cpp/language/constraints). The check is performed in compile time.

---

A `mint` can be initialised with a string or an integral:
```cpp
mint a = string("1234567890123");
mint b = 987654321098;
```

Or with input:
```cpp
mint n;
cin >> n;
```

---

A `mint` can be converted into any integral class or a string:
```cpp
mint n = 5;
int x = int(n);
string s = string(n);
```

---

When doing arithmetic operations, the `mint` class automatically modulo the answer:
```cpp
mint n = int(1e9);
n += 10;
cout << n << '\n'; // 3
```

Note that the `/` operator will return [modular inverse](https://en.wikipedia.org/wiki/Modular_multiplicative_inverse) of the number.

---

To do fast exponentiation:
```cpp
mint b = 3;
int p = 12345;
cout << pow(b, p) << '\n';
```

---

Lastly, the `divmod(a, b)` function returns a pair of `mint`, storing $\lfloor \frac{a}{b} \rfloor$ and $a \mod b$ respectively where `a` and `b` could be any integral or `mint` class.
```cpp
mint a = 13, b = 5;
auto [x, y] = divmod(a, b);
cout << x << ' ' << y << '\n'; // 2 3
```

---

Let's try using the template to solve [Modular Inverse (HKOI)](https://judge.hkoi.org/task/B400) and [Combinations (HKOI)](https://judge.hkoi.org/task/B401)!

<details>

<summary>Modular Inverse (HKOI)</summary>

```cpp
const int MOD = 1e9 + 7;
using mint = Modular<MOD>;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    mint x;
    cin >> x;

    cout << 1 / x << '\n';
}
```

[submission](https://judge.hkoi.org/submission/1361166/details)

</details>

<details>

<summary>Combinations (HKOI)</summary>

```cpp
const int MOD = 1e9 + 7;
using mint = Modular<MOD>;

vector<mint> fact, inv_fact;
const int mxN = 2e5;

void precompute(int n) {
    fact.resize(n + 1);
    inv_fact.resize(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; ++i)
        fact[i] = fact[i - 1] * i;
    inv_fact[n] = 1 / fact[n];
    for (int i = n; i > 0; --i)
        inv_fact[i - 1] = inv_fact[i] * i;
}

mint nCr(int n, int k) {
    return fact[n] * inv_fact[k] * inv_fact[n - k];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precompute(mxN);

    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;

        cout << nCr(n, k) << '\n';
    }
}
```

[submission](https://judge.hkoi.org/submission/1361167/details)

</details>