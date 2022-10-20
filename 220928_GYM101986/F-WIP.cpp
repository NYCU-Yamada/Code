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

const int maxn = 100'000 + 5;
const int INF = LLONG_MAX >> 2;

vector<tuple<int, int, int, int>> edges;
vector<tuple<int, int, int>> adj[maxn], jda[maxn];
vector<int> deg(maxn, 0), ged(maxn, 0), cnt(maxn, 0), tnc(maxn, 0);

void dfs(int now) {
    for (auto [x, cost, id] : adj[now]) {
        if (get<3>(edges[id]) >> 1 & 1) continue;
        cnt[x] += cnt[now];
        if (!--deg[x]) dfs(x);
    }
}

void sfd(int now) {
    for (auto [x, cost, id] : jda[now]) {
        if (get<3>(edges[id]) >> 2 & 1) continue;
        tnc[x] += tnc[now];
        if (!--ged[x]) sfd(x);
    }
}

void solve() {
    int N, M; cin >> N >> M;
    
    edges.resize(M);
    int tok = 0;
    for (auto &[u, v, w, flag] : edges) {
        cin >> u >> v >> w, --u, --v, flag = 0;
        adj[u].eb(v, w, tok), jda[v].eb(u, w, tok), ++tok;
    }
    
    vector<int> dis(N, INF), sid(N, INF), tag(N, -1), gat(N, -1);
    MinHeap<pii> pq, qp;
    
    pq.ee(0, dis[0] = 0);
    while (SZ(pq)) {
        auto [now, _d] = pq.top(); pq.pop();
        if (dis[now] != _d) continue;
        for (auto [x, cost, id] : adj[now]) {
            if (dis[x] == dis[now] + cost) tag[x] = -1;
            if (dis[x] > dis[now] + cost) tag[x] = id, pq.ee(x, dis[x] = dis[now] + cost);
        }
    }
    for (int i = 0; i < N; ++i) {
        for (auto [x, cost, id] : adj[i]) {
            if (dis[x] == dis[i] + cost) ++deg[x], get<3>(edges[id]) |= 1;
        }
    }
    dfs(0);
    
    pq.ee(1, sid[1] = 0);
    while (SZ(qp)) {
        auto [now, _d] = qp.top(); qp.pop();
        if (sid[now] != _d) continue;
        for (auto [x, cost, id] : jda[now]) {
            if (sid[x] == sid[now] + cost) gat[x] = -1;
            if (sid[x] > sid[now] + cost) gat[x] = id, qp.ee(x, sid[x] = sid[now] + cost);
        }
    }
    for (int i = 0; i < N; ++i) {
        for (auto [x, cost, id] : jda[i]) {
            if (sid[x] == sid[i] + cost) ++ged[x], get<3>(edges[id]) |= 2;
        }
    }
    sfd(1);
    
    vector<bool> important(M, false);
    for (int &x : tag) if (~x) important[x] = true;
    for (int &x : gat) if (~x) important[x] = true;
    
    // debug(cnt, tnc);
    
    for (int i = 0; i < M; ++i) {
        if (!important[i]) continue;
        auto [u, v, w, flag] = edges[i];
        if (cnt[u] * tnc[v] != cnt[1]) important[i] = false;
    }
    
    int global = INF;
    for (int i = 0; i < N; ++i) chmin(global, dis[i] + sid[i]);
    
    tok = 0;
    for (auto [u, v, w, flag] : edges) {
        if (important[tok]) cout << "SAD" << "\n";
        else if (flag) cout << "SOSO" << "\n";
        else {
            int tmp = dis[v] + w + sid[u];
            if (tmp < global) cout << "HAPPY" << "\n";
            else              cout << "SOSO" << "\n";
        }
        ++tok;
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
