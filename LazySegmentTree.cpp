template <typename T>
concept Arithmetic = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
    { a - b } -> std::convertible_to<T>;
    { a < b } -> std::convertible_to<bool>;
};

template <Arithmetic U>
class LazySegmentTree {
public:
    struct Node { U sum, mn, mx; };
    struct Lazy { U add{}; std::optional<U> assign; };

private:
    int n;
    std::vector<Node> tree;
    std::vector<Lazy> lazy;

    static Node combine(const Node &a, const Node &b) {
        return { a.sum + b.sum, std::min(a.mn, b.mn), std::max(a.mx, b.mx) };
    }

    void apply_assign(int idx, int len, U v) {
        tree[idx].sum = v * len;
        tree[idx].mn = v;
        tree[idx].mx = v;
        lazy[idx].assign = v;
        lazy[idx].add = U{};
    }

    void apply_add(int idx, int len, U v) {
        tree[idx].sum += v * len;
        tree[idx].mn += v;
        tree[idx].mx += v;
        if (lazy[idx].assign) {
            *lazy[idx].assign += v;
        } else {
            lazy[idx].add += v;
        }
    }

    void push(int idx, int l, int r) {
        if (l == r) return;
        int m = std::midpoint(l, r);
        if (lazy[idx].assign) {
            apply_assign(idx * 2, m - l + 1, *lazy[idx].assign);
            apply_assign(idx * 2 + 1, r - m, *lazy[idx].assign);
            lazy[idx].assign.reset();
        }
        if (lazy[idx].add != U{}) {
            apply_add(idx * 2, m - l + 1, lazy[idx].add);
            apply_add(idx * 2 + 1, r - m, lazy[idx].add);
            lazy[idx].add = U{};
        }
    }

    Node query(int idx, int l, int r, int left, int right) {
        push(idx, l, r);
        if (l == left && r == right) {
            return tree[idx];
        }
        int m = std::midpoint(l, r);
        if (right <= m) {
            return query(idx * 2, l, m, left, right);
        }
        if (left > m) {
            return query(idx * 2 + 1, m + 1, r, left, right);
        }
        auto L = query(idx * 2, l, m, left, m);
        auto R = query(idx * 2 + 1, m + 1, r, m + 1, right);
        return combine(L, R);
    }

    void update(int idx, int l, int r, int left, int right, U v, bool is_assign) {
        if (left <= l && r <= right) {
            if (is_assign) apply_assign(idx, r - l + 1, v);
            else apply_add(idx, r - l + 1, v);
            return;
        }
        push(idx, l, r);
        int m = std::midpoint(l, r);
        if (left <= m) update(idx * 2, l, m, left, right, v, is_assign);
        if (right > m) update(idx * 2 + 1, m + 1, r, left, right, v, is_assign);
        tree[idx] = combine(tree[idx * 2], tree[idx * 2 + 1]);
    }

public:
    LazySegmentTree(int size)
        : n(size)
        , tree(4 * size, { U{}, std::numeric_limits<U>::max(), std::numeric_limits<U>::lowest() })
        , lazy(4 * size)
    {}

    LazySegmentTree(const std::vector<U>& arr) : LazySegmentTree(static_cast<int>(arr.size())) {
        std::function<void(int, int, int)> build = [&](int idx, int l, int r) {
            if (l == r) {
                U v = arr[l];
                tree[idx] = { v, v, v };
                return;
            }
            int m = std::midpoint(l, r);
            build(idx * 2, l, m);
            build(idx * 2 + 1, m + 1, r);
            tree[idx] = combine(tree[idx * 2], tree[idx * 2 + 1]);
        };
        build(1, 0, n - 1);
    }

    U range_sum(int l, int r) {
        return query(1, 0, n - 1, l, r).sum;
    }

    U range_min(int l, int r) {
        return query(1, 0, n - 1, l, r).mn;
    }

    U range_max(int l, int r) {
        return query(1, 0, n - 1, l, r).mx;
    }

    void update_add(int l, int r, U v) {
        update(1, 0, n - 1, l, r, v, false);
    }

    void update_set(int l, int r, U v) {
        update(1, 0, n - 1, l, r, v, true);
    }
};