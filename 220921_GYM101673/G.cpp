#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

// #define X first
// #define Y second
#define SZ(a) (int)((a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)
#define ee emplace
#define eb emplace_back
#define ef emplace_front
#define pb pop_back
#define pf pop_front

#ifdef local
#define debug(...) \
    fprintf(stderr, "LINE %d: (%s) = ", __LINE__, #__VA_ARGS__);\
    _do(__VA_ARGS__);
template<typename T> void _do(T &&_x){cerr << _x << endl;}
template<typename T, typename ...S> void _do(T &&_x, S &&..._t){cerr << _x << ", "; _do(_t...);}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0);
#define debug(...) void()
#endif

template<typename T>
ostream operator << (ostream &os, vector<T> &vec) {
    os << "[";
    for (int i = 0; i < SZ(vec); ++i) {
        if (i) os << ", ";
        os << vec[i];
    }
    os << "]";
    return os;
}

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

void solve() {
    int N, M; cin >> N >> M;
    
    vector<int> f(N);
    for (int &x : f) cin >> x;
    
    vector<int> e(N, M);
    for (int i = 1; i < N; ++i) e[i] = 2 * e[i-1] / 3;
    
    vector<vector<int>> dp(N, vector<int>(N, 0));
    dp[0][0] = min(f[0], e[0]);
    for (int i = 1; i < N; ++i) {
        for (int p = i-3; p >= 0; --p) {
            for (int k = 0; k <= p; ++k) chmax(dp[i][0], dp[p][k]);
        }
        for (int p = i-2; p >= 0; --p) chmax(dp[i][0], dp[p][0]);
        dp[i][0] += min(f[i], e[0]);
        for (int j = 1; j <= i; ++j) {
            for (int p = i-1; p >= 0; --p) chmax(dp[i][j], dp[p][j-1]);
            for (int p = i-2; p >= 0; --p) chmax(dp[i][j], dp[p][j]);
            dp[i][j] += min(f[i], e[j]);
        }
    }
    
    int ans = 0;
    for (vector<int> &vec : dp) chmax(ans, *max_element(ALL(vec)));
    cout << ans << "\n";
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
