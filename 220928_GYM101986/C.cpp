#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T> using MaxHeap = priority_queue<T>;
template<typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

#define SZ(a) (int)((a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)
// #define X first
// #define Y second
#define eb emplace_back
#define ef emplace_front
#define ee emplace
#define pb pop_back
#define pf pop_front

#ifdef local
#define debug(...) \
    fprintf(stderr, "LINE %d : (%s) = ", __LINE__, #__VA_ARGS__),\
    _do(__VA_ARGS__)
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

const int MAXN = 1e5+5;

int h[MAXN];
void solve() {
    int n,t;
    cin >> n >> t;
    for (int i=1;i<=n;++i) cin >> h[i];
    int tt = 0, ans = 0;
    for (int i=1;i<=n;++i) {
        tt += h[i];
        ans = 1;
        chmax(h[i], h[i-1]);
        if (tt <= t + 1) {
            int tmp = t + 1 - tt;
            ans += tmp / h[i] + (tmp % h[i] != 0);
        }
        cout << ans << endl;
    }
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
