#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3,unroll-loops")

#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define pb push_back
#define eb emplace_back
// #define x first
// #define y second
#define debug(var) cerr << #var " = " << (var) << '\n'

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vll = vector<ll>;
using vb = vector<bool>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

[[maybe_unused]] const int MOD = 1e9 + 7;
// [[maybe_unused]] const int MOD = 998244853;
[[maybe_unused]] const int INF = 0x3f3f3f3f;
[[maybe_unused]] const ll LLINF = 0x3f3f3f3f3f3f3f3f;

template<typename T> istream& operator>>(istream& is, vector<T>& v) { for (auto& x : v) is >> x; return is; }
template<typename T, typename U> istream& operator>>(istream& is, pair<T, U>& p) { return is >> p.first >> p.second; }
template<typename T, size_t N> istream& operator>>(istream& is, array<T, N>& a) { for (auto& x : a) is >> x; return is; }
template<typename... T> istream& operator>>(istream& is, tuple<T...>& t) { apply([&](auto&&... args) { ((is >> args), ...); }, t); return is; }

template<typename T> ostream& operator<<(ostream& os, const vector<T>& v) { for (const auto& x : v) os << x << ' '; return os; }
template<typename T, typename U> ostream& operator<<(ostream& os, const pair<T, U>& p) { return os << p.first << ' ' << p.second; }
template<typename T, size_t N> ostream& operator<<(ostream& os, const array<T, N>& a) { for (const auto& x : a) os << x << ' '; return os; }
template<typename... T> ostream& operator<<(ostream& os, const tuple<T...>& t) { apply([&](const auto&... args) { ((os << args << ' '), ...); }, t); return os; }

template <typename T, typename U> bool chmin(T& a, U b) { return b < a ? a = b, 1 : 0; }
template <typename T, typename U> bool chmax(T& a, U b) { return a < b ? a = b, 1 : 0; }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    
}