template <typename T, std::size_t N>
struct static_array : public std::array<T, N> {
    constexpr static_array() = default;
    constexpr explicit static_array(const T& val) { this->fill(val); }
    template <typename... U> requires (sizeof...(U) == N && (std::convertible_to<U, T> && ...))
    constexpr static_array(U&&... u) : std::array<T, N>{ { static_cast<T>(std::forward<U>(u))... } } {}
    constexpr void clear() noexcept {
        if constexpr (std::is_trivially_default_constructible_v<T> &&
                      std::is_trivially_copyable_v<T> &&
                      std::is_standard_layout_v<T>) {
            std::memset(this->data(), 0, sizeof(*this));
        } else {
            this->fill(T{});
        }
    }
    friend std::ostream& operator<<(std::ostream& out, const static_array& a) {
        for (std::size_t i = 0; i < N; ++i) {
            out << a[i];
            if (i + 1 < N) out << ' ';
        }
        return out;
    }
    friend std::istream& operator>>(std::istream& in, static_array& a) {
        for (auto& x : a) in >> x;
        return in;
    }
};