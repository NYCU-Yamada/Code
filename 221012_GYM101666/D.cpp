#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define double __float80
using pii = pair<int, int>;
template <typename T> using MaxHeap = std::priority_queue<T>;
template <typename T> using MinHeap = std::priority_queue<T, vector<T>, greater<T>>;

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
    fprintf(stderr, "\u001b[33m"), \
    fprintf(stderr, "At [%s], line %d: (%s) = ", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), \
    fprintf(stderr, "\u001b[0m")
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else 
#define IOS() ios_base::sync_with_stdio(), cin.tie()
#define debug(...) void()
#define endl "\n"
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int INF = LLONG_MAX >> 3;
const int maxn = 1E5 + 5;

vector<tuple<int, int, int>> adj[maxn];
vector<int> dis, fr;

void solve() {
    int N, M; cin >> N >> M;
    
    for (int i = 0, u, v, w; i < M; ++i) {
        cin >> u >> v >> w;
        adj[u].eb(v, w, 0), adj[v].eb(u, w, 0);
    }
    
{   /// first time SP(*, 1) ///
    
    dis.assign(N, INF); dis[1] = 0;
    MinHeap<pii> pq; pq.ee(dis[1], 1);
    while (SZ(pq)) {
        auto [_, now] = pq.top(); pq.pop();
        if (dis[now] != _) continue;
        for (auto [x, cost, flag] : adj[now]) {
            if (chmin(dis[x], dis[now] + cost)) pq.ee(dis[x], x);
        }
    }
    
    // for (int i = 0; i < N; ++i) debug(dis[i]);
    
}   
    /// remove edges in SP(*, 1) ///
    
    for (int i = 0; i < N; ++i) {
        for (auto &[x, cost, flag] : adj[i]) {
            if (dis[x] == dis[i] - cost) flag = 1;
        }
    }
    
{   /// second time SP ///
    
    dis.assign(N, INF), dis[0] = 0;
    fr.assign(N, -1);
    MinHeap<pii> pq; pq.ee(dis[0], 0);
    while (SZ(pq)) {
        auto [_, now] = pq.top(); pq.pop();
        if (dis[now] != _) continue;
        for (auto [x, cost, flag] : adj[now]) {
            if (!flag and chmin(dis[x], dis[now] + cost)) fr[x] = now, pq.ee(dis[x], x);
        }
    }
    
    // for (int i = 0; i < N; ++i) debug(dis[i]);
    
}   
    /// get path in SP(0, 1) ///
    
    if (dis[1] == INF) return cout << "impossible" << "\n", void();
    
    vector<int> path;
    int now = 1;
    while (now != -1) path.eb(now), now = fr[now];
    reverse(ALL(path));
    
    cout << SZ(path) << " ";
    for (int x : path) cout << x << " ";
    cout << "\n";
}

signed main() {
    IOS();
    int _ = 1;
    // cin >> _;
    for (int i = 1; i <= _; ++i) {
        solve();
    }
    return 0;
}