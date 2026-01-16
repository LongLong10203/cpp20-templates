template <typename T, std::size_t N>
struct static_array : public std::array<T, N> {
    constexpr static_array() = default;
    constexpr explicit static_array(const T& val) {
        this->fill(val);
    }
    constexpr static_array(std::initializer_list<T> il) {
        std::size_t i = 0;
        for (auto &x : il) {
            if (i >= N) break;
            (*this)[i++] = x;
        }
        for (; i < N; ++i) (*this)[i] = T{};
    }
    void clear() noexcept {
        if constexpr (std::is_trivially_copyable_v<T> && std::is_standard_layout_v<T>) {
            std::memset(this->data(), 0, sizeof(*this));
        } else {
            this->fill(T{});
        }
    }
    friend std::istream& operator>>(std::istream& in, static_array& a) {
        for (auto& x : a) in >> x;
        return in;
    }
    friend std::ostream& operator<<(std::ostream& out, const static_array& a) {
        for (std::size_t i = 0; i < N; ++i) {
            out << a[i];
            if (i + 1 < N) out << ' ';
        }
        return out;
    }
};