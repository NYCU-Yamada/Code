#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
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

const int maxn = 20 + 5;

vector<int> adj[maxn];

void add_reverse(deque<int> &ans, deque<int> meow) {
    deque<int> tmp = ans;
    for (int i = 0; i < SZ(meow); ++i) {
        tmp.eb(meow[i]);
        if (i & 1) {
            for (int j = 0; j < SZ(ans); ++j) tmp.eb(ans[j]);
        }
        else {
            for (int j = SZ(ans)-1; j >= 0; --j) tmp.eb(ans[j]);
        }
    }
    ans.swap(tmp);
}

deque<int> dfs(int now) {
    deque<int> ans;
    for (int x : adj[now]) add_reverse(ans, dfs(x));
    ans.ef(now);
    return ans;
}

void solve() {
    int N; cin >> N;
    for (int i = 2, p_i; i <= N; ++i) cin >> p_i, adj[p_i].eb(i);
    
    deque<int> ans = dfs(1);
    ans.pf();
    
    cout << SZ(ans) << "\n";
    for (int x : ans) cout << x << " ";
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
