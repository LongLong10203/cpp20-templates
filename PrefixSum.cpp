template <typename T> struct PrefixSum : public std::vector<T> {
    PrefixSum(const int n) : std::vector<T>(n) {}
    PrefixSum(const std::vector<T>& ps) : std::vector<T>(ps.size()) {
        std::ranges::copy(ps, this->begin());
        build();
    }
    void build() {
        std::partial_sum(this->begin(), this->end(), this->begin());
    }
    T query(int l, int r) const {
        assert(l >= 0 && r < this->size() && l <= r);
        return (l == 0) ? (*this)[r] : (*this)[r] - (*this)[l - 1];
    }
};

template <typename T> struct PrefixSum2D : public std::vector<std::vector<T>> {
    PrefixSum2D(const int n, const int m) : std::vector<std::vector<T>>(n, std::vector<T>(m)) {}
    PrefixSum2D(const std::vector<std::vector<T>>& ps)
        : std::vector<std::vector<T>>(ps.size(), std::vector<T>(ps[0].size())) {
        std::ranges::copy(ps, this->begin());
        build();
    }
    void build() {
        const int n = this->size(), m = this->size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                (*this)[i][j] = (*this)[i][j];
                if (i > 0) (*this)[i][j] += (*this)[i - 1][j];
                if (j > 0) (*this)[i][j] += (*this)[i][j - 1];
                if (i > 0 && j > 0) (*this)[i][j] -= (*this)[i - 1][j - 1];
            }
        }
    }
    T query(int x1, int y1, int x2, int y2) const {
        assert(x1 >= 0 && y1 >= 0 && x2 < this->size() && y2 < (*this)[0].size() && x1 <= x2 && y1 <= y2);
        T res = (*this)[x2][y2];
        if (x1 > 0) res -= (*this)[x1 - 1][y2];
        if (y1 > 0) res -= (*this)[x2][y1 - 1];
        if (x1 > 0 && y1 > 0) res += (*this)[x1 - 1][y1 - 1];
        return res;
    }
};

template <typename T> struct DifferenceArray : public std::vector<T> {
    DifferenceArray(const int n) : std::vector<T>(n) {}
    DifferenceArray(const std::vector<T>& da) : std::vector<T>(da.size()) {
        std::ranges::copy(da, this->begin());
    }
    void build() {
        std::partial_sum(this->begin(), this->end(), this->begin());
    }
    void increment(int l, int r, T val) {
        assert(l >= 0 && r < this->size() && l <= r);
        (*this)[l] += val;
        if (r + 1 < this->size()) (*this)[r + 1] -= val;
    }
};

template <typename T> struct DifferenceArray2D : public std::vector<std::vector<T>> {
    DifferenceArray2D(const int n, const int m) : std::vector<std::vector<T>>(n, std::vector<T>(m)) {}
    DifferenceArray2D(const std::vector<std::vector<T>>& da)
        : std::vector<std::vector<T>>(da.size(), std::vector<T>(da[0].size())) {
        const int n = da.size(), m = da[0].size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                (*this)[i][j] = da[i][j];
                if (i > 0) (*this)[i][j] -= da[i - 1][j];
                if (j > 0) (*this)[i][j] -= da[i][j - 1];
                if (i > 0 && j > 0) (*this)[i][j] += da[i - 1][j - 1];
            }
        }
    }
    void build() {
        for (int i = 0; i < this->size(); ++i) {
            for (int j = 0; j < (*this)[0].size(); ++j) {
                if (i > 0) (*this)[i][j] += (*this)[i - 1][j];
                if (j > 0) (*this)[i][j] += (*this)[i][j - 1];
                if (i > 0 && j > 0) (*this)[i][j] -= (*this)[i - 1][j - 1];
            }
        }
    }
    void increment(int x1, int y1, int x2, int y2, T val) {
        assert(x1 >= 0 && y1 >= 0 && x2 < this->size() && y2 < (*this)[0].size() && x1 <= x2 && y1 <= y2);
        (*this)[x1][y1] += val;
        if (x2 + 1 < this->size()) (*this)[x2 + 1][y1] -= val;
        if (y2 + 1 < (*this)[0].size()) (*this)[x1][y2 + 1] -= val;
        if (x2 + 1 < this->size() && y2 + 1 < (*this)[0].size()) (*this)[x2 + 1][y2 + 1] += val;
    }
};