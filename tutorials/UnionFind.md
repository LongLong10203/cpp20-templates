# Union Find

To initialise a lomo tree of $n$ elements:
```cpp
UnionFind<int> dsu(10);
```

---

To initialise a lomo tree with map:
```cpp
UnionFind<int, map<int, int>> dsu;
```

---

To initialise a lomo tree with unordered map:
```cpp
UnionFind<int, unordered_map<int, int>> dsu;
```

---

To initialise a lomo tree with unordered map of custom hash:
```cpp
UnionFind<int, custom_hashed_map<int>, custom_hash<int>> dsu;
```

<details>
<summary>Example</summary>

```cpp
struct CustomHash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

template <typename T, typename U>
using safe_map = std::unordered_map<T, U, CustomHash>;
```
```cpp
UnionFind<int, safe_map<int, int>, CustomHash> dsu;
```
</details>

---

You may also initialise a lomo tree with any integral types:

```cpp
UnionFind<short> dsu(1000);
```

```cpp
UnionFind<short, map<short, short>> dsu;
```