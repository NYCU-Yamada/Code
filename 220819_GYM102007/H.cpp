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

const int INF = LLONG_MAX >> 2;

void solve() {
    int N, M, S, T; cin >> N >> M >> S >> T;
    
    vector<vector<pii>> adj(2*N);
    vector<int> deg_i(2*N, 0);
    
    for (int i = 0, u, v, w; i < M; ++i) {
        cin >> u >> v >> w;
        adj[v].eb(u+N, w), ++deg_i[u+N];
        adj[v+N].eb(u, w), ++deg_i[u];
    }
    
    vector<int> dis(2*N, INF), vis(2*N, 0);
    fill(begin(dis), begin(dis) + N, -INF);
    dis[T] = dis[T+N] = 0;
    
    MinHeap<pii> pq;
    pq.ee(dis[T], T), pq.ee(dis[T+N], T+N);
    
    while (SZ(pq)) {
        auto [_dis, now] = pq.top(); pq.pop();
        vis[now] = 1;
        if (_dis != dis[now]) continue;
        
        for (auto [x, cost] : adj[now]) {
            if (now < N) {
                if (chmin(dis[x], dis[now] + cost)) pq.ee(dis[x], x);
            }
            else {
                chmax(dis[x], dis[now] + cost);
                if (!--deg_i[x]) pq.ee(dis[x], x);
            }
        }
    }
    
    if (!vis[S]) cout << "infinity" << "\n";
    else         cout << dis[S] << "\n";
    
    // for (int i = 0; i < 2*N; ++i) cerr << dis[i] << " \n"[i%N == N-1];
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
