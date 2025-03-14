template<typename T, typename ... U>
concept IsAnyOf = (same_as<T, U> || ...);

template <typename T = int, typename Container = vector<T>, typename Hash = hash<T>>
requires is_integral_v<T> && IsAnyOf<Container, vector<T>, map<T, T>, unordered_map<T, T, Hash>>
struct DisjointSet {
    Container lomo, size;
    DisjointSet() = default;
    DisjointSet(T n) requires same_as<Container, vector<T>> : lomo(n), size(n, 0) {
        iota(lomo.begin(), lomo.end(), 0);
    }
    T find(T u) {
        if constexpr (!same_as<Container, vector<T>>) {
            if (lomo.find(u) == lomo.end()) {
                lomo[u] = u;
                size[u] = 1;
            }
        }
        return lomo[u] == u ? u : lomo[u] = find(lomo[u]);
    }
    void join(T u, T v) {
        T du = find(u), dv = find(v);
        if (du != dv) {
            if (size[du] < size[dv]) {
                swap(du, dv);
            }
            lomo[dv] = du;
            size[du] += size[dv];
        }
    }
    bool same(T u, T v) {
        return find(u) == find(v);
    }
    T get_size(T u) {
        return size[find(u)];
    }
};