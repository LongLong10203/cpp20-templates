template <std::integral auto N>
concept Prime = ([](auto n) constexpr -> bool {
    if (n < 2) return false;
    for (auto i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}(N));

template <const int MOD> requires Prime<MOD>
struct Modular {
    int value;
    Modular() : value(0) {}
    Modular(const Modular& m) : value(m.value) {}
    Modular(const std::string& s) : value(std::stoll(s) % MOD) { if (value < 0) value += MOD; }
    template <std::integral T>
    Modular(T v) : value(int(v % MOD)) { if (value < 0) value += MOD; }
    template <std::integral T>
    explicit operator T() const { return value; }
    explicit operator std::string() const { return std::to_string(value); }
    friend std::istream& operator>>(std::istream& in, Modular& n) {
        long long v; in >> v;
        n = Modular(v); return in;
    }
    friend std::ostream& operator<<(std::ostream& out, const Modular& n) { return out << n.value; }
    friend auto operator<=>(const Modular&, const Modular&) = default;
    friend bool operator!(const Modular& a) { return !a.value; }

    Modular& operator+=(const Modular& m) { if ((value += m.value) >= MOD) value -= MOD; return *this; }
    Modular& operator-=(const Modular& m) { if ((value -= m.value) < 0) value += MOD; return *this; }
    Modular& operator*=(const Modular& m) { value = int((long long)value * m.value % MOD); return *this; }
    Modular& operator/=(const Modular& m) { return *this *= inv(m); }
    Modular operator-() const { return Modular(-value); }
    Modular& operator++() { return *this += 1; }
    Modular& operator--() { return *this -= 1; }
    friend Modular operator+(Modular a, const Modular& b) { return a += b; }
    friend Modular operator-(Modular a, const Modular& b) { return a -= b; }
    friend Modular operator*(Modular a, const Modular& b) { return a *= b; }
    friend Modular operator/(Modular a, const Modular& b) { return a /= b; }
    friend Modular operator++(Modular& a, int) { Modular r = a; ++a; return r; }
    friend Modular operator--(Modular& a, int) { Modular r = a; --a; return r; }
    
    friend Modular pow(Modular a, std::integral auto p) {
        if (p < 0) return inv(pow(a, -p));
        Modular ans = 1;
        for (; p > 0; p >>= 1, a *= a) if (p & 1) ans *= a;
        return ans;
    }
    friend Modular inv(const Modular& a) {
        assert(a.value != 0);
        return pow(a, MOD - 2);
    }
    friend std::pair<Modular, Modular> divmod(const Modular& a, const Modular& b) { return std::make_pair(a.value / b.value, a.value % b.value); }

    template <typename T>
    static constexpr auto Integral = std::is_integral_v<T> || std::is_same_v<T, Modular>;
    template <typename T, typename U> requires Integral<T> && Integral<U>
    friend std::pair<Modular, Modular> divmod(T a, U b) { return divmod(Modular(a), Modular(b)); }
    template <typename T> requires Integral<T>
    friend Modular abs(T a) { return a < 0 ? -a : a; }
    template <typename T, typename U> requires Integral<T> && Integral<U>
    friend Modular gcd(T a, U b) { return b ? gcd(b, divmod(a, b).second) : a; }
    template <typename T, typename U> requires Integral<T> && Integral<U>
    friend Modular lcm(T a, U b) { return (a == MOD || b == MOD) ? 0 : (divmod(a, gcd(a, b)).first * b); }
};