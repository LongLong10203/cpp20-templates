template <integral auto N = NULL> struct Sieve : public vector<bool> {
    int n;
    void init(int n) {
        (*this)[0] = (*this)[1] = false;
        for (auto i = 2; i * i <= n; i++) {
            if ((*this)[i]) {
                for (auto j = i * i; j <= n; j += i) {
                    (*this)[j] = false;
                }
            }
        }
    }
    Sieve() requires (N != NULL) : vector<bool>(N + 1, true), n(N) {
        init(N);
    }
    Sieve(int n) requires (N == NULL) : vector<bool>(n + 1, true), n(n) {
        init(n);
    }
    vector<bool> operator()() { return *this; }
    auto operator[](int i) -> vector<bool>::reference { return vector<bool>::operator[](i); }
    bool operator[](int i) const { return vector<bool>::operator[](i); }
};

template <integral auto L = NULL, integral auto R = NULL> requires (L < R)
struct SegmentedSieve : public vector<bool> {
    using T = decltype(R);
    T low, high;
    void init(T l, T r) {
        if (l < 2) {
            for (T i = l; i < min(T(2), r + 1); ++i) {
                (*this)[i] = false;
            }
        }
        const T limit = floor(sqrt(r));
        Sieve sieve(limit);
        for (T p = 2; p <= limit; ++p) {
            if (sieve[p]) {
                for (T j = max(p * p, ((l + p - 1) / p) * p); j <= r; j += p) {
                    (*this)[j] = false;
                }
            }
        }
    }
    SegmentedSieve() requires (L != NULL && R != NULL) : vector<bool>(R - L + 1, true), low(L), high(R) {
        init(L, R);
    }
    SegmentedSieve(T l, T r) requires (L == NULL && R == NULL) : vector<bool>(r - l + 1, true), low(l), high(r) {
        init(l, r);
    }
    vector<bool> operator()() { return *this; }
    auto operator[](T i) -> vector<bool>::reference { return vector<bool>::operator[](i - low); }
    bool operator[](T i) const { return vector<bool>::operator[](i - low); }
};