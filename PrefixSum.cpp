template <typename T> struct PrefixSum : public vector<T> {
    PrefixSum(const int n) : vector<T>(n) {}
    PrefixSum(const vector<T>& ps) : vector<T>(ps.size()) {
        partial_sum(ps.begin(), ps.end(), this->begin());
    }
    T query(int l, int r) const {
        assert(l >= 0 && r < this->size() && l <= r);
        if (l == 0) {
            return (*this)[r];
        }
        return (*this)[r] - (*this)[l - 1];
    }
};

template <typename T> struct PrefixSum2D : public vector<vector<T>> {
    PrefixSum2D(const int n, const int m) : vector<vector<T>>(n, vector<T>(m)) {}
    PrefixSum2D(const vector<vector<T>>& ps)
        : vector<vector<T>>(ps.size(), vector<T>(ps[0].size())) {
        const int n = ps.size(), m = ps[0].size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                (*this)[i][j] = ps[i][j];
                if (i > 0) {
                    (*this)[i][j] += (*this)[i - 1][j];
                }
                if (j > 0) {
                    (*this)[i][j] += (*this)[i][j - 1];
                }
                if (i > 0 && j > 0) {
                    (*this)[i][j] -= (*this)[i - 1][j - 1];
                }
            }
        }
    }
    T query(int x1, int y1, int x2, int y2) const {
        assert(x1 >= 0 && y1 >= 0 && x2 < this->size() && y2 < (*this)[0].size() && x1 <= x2 && y1 <= y2);
        T res = (*this)[x2][y2];
        if (x1 > 0) {
            res -= (*this)[x1 - 1][y2];
        }
        if (y1 > 0) {
            res -= (*this)[x2][y1 - 1];
        }
        if (x1 > 0 && y1 > 0) {
            res += (*this)[x1 - 1][y1 - 1];
        }
        return res;
    }
};

template <typename T> struct DifferenceArray : public vector<T> {
    DifferenceArray(const int n) : vector<T>(n) {}
    DifferenceArray(const vector<T>& da) : vector<T>(da.size()) {
        ranges::copy(da, this->begin());
    }
    void increment(int l, int r, T val) {
        assert(l >= 0 && r < this->size() && l <= r);
        (*this)[l] += val;
        if (r + 1 < this->size()) {
            (*this)[r + 1] -= val;
        }
    }
    void build() {
        partial_sum(this->begin(), this->end(), this->begin());
    }
};

template <typename T> struct DifferenceArray2D : public vector<vector<T>> {
    DifferenceArray2D(const int n, const int m) : vector<vector<T>>(n, vector<T>(m)) {}
    DifferenceArray2D(const vector<vector<T>>& da)
        : vector<vector<T>>(da.size(), vector<T>(da[0].size())) {
        const int n = da.size(), m = da[0].size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                (*this)[i][j] = da[i][j];
                if (i > 0) {
                    (*this)[i][j] -= da[i - 1][j];
                }
                if (j > 0) {
                    (*this)[i][j] -= da[i][j - 1];
                }
                if (i > 0 && j > 0) {
                    (*this)[i][j] += da[i - 1][j - 1];
                }
            }
        }
    }
    void increment(int x1, int y1, int x2, int y2, T val) {
        assert(x1 >= 0 && y1 >= 0 && x2 < this->size() && y2 < (*this)[0].size() && x1 <= x2 && y1 <= y2);
        (*this)[x1][y1] += val;
        if (x2 + 1 < this->size()) {
            (*this)[x2 + 1][y1] -= val;
        }
        if (y2 + 1 < (*this)[0].size()) {
            (*this)[x1][y2 + 1] -= val;
        }
        if (x2 + 1 < this->size() && y2 + 1 < (*this)[0].size()) {
            (*this)[x2 + 1][y2 + 1] += val;
        }
    }
    void build() {
        for (int i = 0; i < this->size(); ++i) {
            for (int j = 0; j < (*this)[0].size(); ++j) {
                if (i > 0) {
                    (*this)[i][j] += (*this)[i - 1][j];
                }
                if (j > 0) {
                    (*this)[i][j] += (*this)[i][j - 1];
                }
                if (i > 0 && j > 0) {
                    (*this)[i][j] -= (*this)[i - 1][j - 1];
                }
            }
        }
    }
};