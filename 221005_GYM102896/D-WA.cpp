#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define double long double
using pii = pair<int, int>;
template <typename T> using MinHeap = std::priority_queue<T, vector<T>, greater<T>>;
template <typename T> using MaxHeap = std::priority_queue<T>;

// #define X first
// #define Y second
#define ee emplace
#define eb emplace_back
#define ef emplace_front
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())

#ifdef local
#define IOS() void()
#define debug(...) \
    cerr << "\u001b[33m",\
    cerr << "At func [" << __FUNCTION__ << "], line " << __LINE__ << ", ",\
    cerr << "(" << #__VA_ARGS__ << ") = ", _do(__VA_ARGS__),\
    cerr << "\u001b[0m"
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define IOS() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

void solve() {
    int N; cin >> N;
    
    vector<int> stair(N, 0);
    for (string s; int &x : stair) {
        cin >> s;
        for (char &c : s) x = (x << 1) | (c == 'W');
    }
    
    vector<int> state(N, 0);
    state[0] = 2;
    for (int i = 1; i < N; ++i) {
        for (int j = 1; j <= min(i, 8); ++j) {
            int cnt = 8 - __builtin_popcount(stair[i] ^ stair[i-j]);
            if (state[i-j] and j <= cnt) {
                if (!state[i]) state[i] = 2;
                if (state[i-j] == 2) state[i] = 1;
            }
        }
    }
    for (int i = 1; i < N; ++i) if (!state[i]) state[i] = state[i-1];
    
    for (int x : state) cout << x;
    cout << "\n";
}

int32_t main() {
    IOS();
    
    int t = 1;
    // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
