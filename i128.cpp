using i128 = __int128;
using u128 = __uint128_t;

inline std::ostream& operator<<(std::ostream& os, i128 x) {
    constexpr size_t BUF_SIZE = std::numeric_limits<i128>::digits10 + 3;
    std::array<char, BUF_SIZE> buf;
    auto it = buf.end();
    bool neg = x < 0;
    u128 n = neg ? -static_cast<u128>(x) : x;
    do *--it = '0' + n % 10; while (n /= 10);
    if (neg) *--it = '-';
    return os.write(&*it, buf.end() - it);
}

inline std::istream& operator>>(std::istream& is, i128& x) {
    std::string s;
    if (!(is >> s)) return is;
    bool neg = !s.empty() && s[0] == '-';
    i128 val = 0;
    for (char c : s) if (c >= '0' && c <= '9') val = val * 10 + (c - '0');
    x = neg ? -val : val;
    return is;
}