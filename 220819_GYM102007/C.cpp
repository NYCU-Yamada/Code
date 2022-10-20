#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define double __float80
using pii = pair<int,int>;
template <typename T> using MaxHeap = std::priority_queue<T>;
template <typename T> using MinHeap = std::priority_queue<T, vector<T>, greater<T>>;

// #define X first
// #define Y second
#define eb emplace_back
#define ef emplace_front
#define ee emplace
#define pb pop_back
#define pf pop_front
#define SZ(a) (int)((a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)

#ifdef local
#define debug(...) do{\
    fprintf(stderr, "LINE %d: (%s) = ", __LINE__, #__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template <typename T> void _do(T &&_x) {cerr << _x << endl;}
template <typename T, typename ...S> void _do(T &&_x, S &&..._t) {cerr << _x << ", "; _do(_t...);}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#define debug(...)
#define endl '\n'
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

void solve() {
    int N; cin >> N;
    
    vector<int> factors;
    for (int i = 1; i <= N; ++i) {
        if (N % i == 0) factors.eb(i);
    }
    
    int ans = 4*N+2;
    for (int x : factors) {
        for (int y : factors) {
            if (N % (x*y)) continue;
            int z = N / (x * y);
            chmin(ans, 2 * (x*y + x*z + y*z));
        }
    }
    cout << ans << "\n";
}

signed main() {
    IOS();
    
    int _ = 1;
    // cin >> _;
    for(int i = 1; i <= _; i++) {
        solve();
    }
    
    return 0;
}
