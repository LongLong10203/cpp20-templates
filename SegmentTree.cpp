template <typename T, auto combine>
requires std::is_invocable_v<decltype(combine), T, T>
struct SegmentTree {
    int n;
    vector<T> tree, data;

    SegmentTree(int n) : n(n), tree(4 * n), data(n, T(0)) {}
    SegmentTree(const vector<T>& data) : n(data.size()), tree(4 * n), data(data) {
        build(1, 0, n - 1);
    }

private:
    void build(int idx, int l, int r) {
        if (l == r) {
            tree[idx] = data[l];
            return;
        }
        int mid = std::midpoint(l, r);
        build(2 * idx, l, mid);
        build(2 * idx + 1, mid + 1, r);
        tree[idx] = combine(tree[2 * idx], tree[2 * idx + 1]);
    }

    [[nodiscard]] T query(int idx, int l, int r, int left, int right) const {
        if (left == l && right == r)
            return tree[idx];
        int mid = std::midpoint(l, r);
        if (right <= mid) {
            return query(2 * idx, l, mid, left, right);
        } else if (left > mid) {
            return query(2 * idx + 1, mid + 1, r, left, right);
        } else {
            return combine(
                query(2 * idx, l, mid, left, mid),
                query(2 * idx + 1, mid + 1, r, mid + 1, right)
            );
        }
    }

    void update(int idx, int l, int r, int pos, T val) {
        if (l == r) {
            tree[idx] = val;
            return;
        }
        int mid = std::midpoint(l, r);
        if (pos <= mid) {
            update(2 * idx, l, mid, pos, val);
        } else {
            update(2 * idx + 1, mid + 1, r, pos, val);
        }
        tree[idx] = combine(tree[2 * idx], tree[2 * idx + 1]);
    }

public:
    [[nodiscard]] T query(int left, int right) const {
        return query(1, 0, n - 1, left, right);
    }

    void update(int pos, T val) {
        data[pos] = val;
        update(1, 0, n - 1, pos, val);
    }
};