template<typename T, typename ... U>
concept IsAnyOf = (std::same_as<T, U> || ...);

template <std::integral T = int, typename Container = std::vector<T>, typename Hash = std::hash<T>>
requires IsAnyOf<Container, std::vector<T>, std::map<T, T>, std::unordered_map<T, T, Hash>>
struct UnionFind {
    Container lomo, size;
    UnionFind() = default;
    UnionFind(T n) requires std::same_as<Container, std::vector<T>> : lomo(n), size(n, 1) {
        std::iota(lomo.begin(), lomo.end(), 0);
    }
    [[nodiscard]] constexpr T find(T u) {
        if constexpr (!std::same_as<Container, std::vector<T>>) {
            if (lomo.find(u) == lomo.end()) {
                lomo[u] = u;
                size[u] = 1;
            }
        }
        return lomo[u] == u ? u : lomo[u] = find(lomo[u]);
    }
    constexpr void join(T u, T v) {
        T du = find(u), dv = find(v);
        if (du != dv) {
            if (size[du] < size[dv]) {
                std::swap(du, dv);
            }
            lomo[dv] = du;
            size[du] += size[dv];
        }
    }
    constexpr bool same(T u, T v) {
        return find(u) == find(v);
    }
    [[nodiscard]] constexpr T get_size(T u) {
        return size[find(u)];
    }
};