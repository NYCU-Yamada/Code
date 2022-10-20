#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
using pdd = pair<double, double>;
template<typename T> using MaxHeap = priority_queue<T>;
template<typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

#define SZ(a) (int)((a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)
#define X first
#define Y second
#define eb emplace_back
#define ef emplace_front
#define ee emplace
#define pb pop_back
#define pf pop_front

#ifdef local
#define debug(...) \
    fprintf(stderr, "\u001b[33mLINE %d : (%s) = ", __LINE__, #__VA_ARGS__),\
    _do(__VA_ARGS__), fprintf(stderr, "\u001b[0m")
template<typename T> void _do(T &&_x) {cerr << _x << endl;}
template<typename T, typename ...S> void _do(T &&_x, S && ..._t){cerr << _x << ", "; _do(_t...);}
#define IOS()
#else
#define debug(...) void()
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0)
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

template <typename T, typename U>
ostream& operator << (ostream &os, const pair<T, U> &_p_) {
    os << "(" << _p_.first << ", " << _p_.second << ")";
    return os;
}

template <typename T>
ostream& operator << (ostream &os, const vector<T> &_vec_) {
    os << "[";
    for (int i = 0; i < SZ(_vec_); ++i) {
        if (i) os << ", ";
        os << _vec_[i];
    }
    os << "]";
    return os;
}

double dot(pdd a, pdd b) {
    return a.X * b.X + a.Y * b.Y;
}

double len2(pdd x) {
    return x.X * x.X + x.Y * x.Y;
}

const double pi = acos(-1);

pair<double, double> trans(double deg, double len) {
    deg = pi * deg / 180.0;
    pdd pt(cos(deg) * len, sin(deg) * len);
    // pdd axis(1, sqrt(3));
    // double v = dot(axis, pt) / sqrt(len2(axis));
    // return {pt.X, v};
    return {pt.X - (1 / sqrt(3)) * pt.Y, pt.Y * (2 / sqrt(3))};
}

int face() {
    string XY; cin >> XY;
    int d, l; cin >> d >> l;
    
    if (XY == "BC") d = d;
    if (XY == "CD") d = d + 60;
    if (XY == "DB") d = d + 120;
    
    auto [x, y] = trans(d, l);
    
    int fx = (int)floor(x), fy = (int)floor(y);
    int fp = (x - fx) + (y - fy) > 1.0;
    
    // debug(x, y, (((fx ^ fy ^ 1) & 1) << 1) xor (fy & 1) xor fp);
    return (((fx ^ fy ^ 1) & 1) << 1) xor (fy & 1) xor fp;
}

void solve() {
    cout << (face() == face() ? "YES" : "NO") << "\n";
}

signed main() {
    IOS();
    
    int _ = 1;
    // cin >> _;
    for (int i=1;i<=_;++i) {
        solve();
    }
    
    return 0;
}
