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

const int MAXN = 1505;
const int INF = 0x3f3f3f3f;

struct MaxFlow {
    struct edge {
        int to, cap, flow, rev;
    };
    vector<edge> G[MAXN];
    int s, t, dis[MAXN], cur[MAXN], n;
    int dfs(int u, int cap) {
        if (u == t || !cap) return cap;
        for (int &i = cur[u]; i < SZ(G[u]); ++i) {
            edge &e = G[u][i];
            if (dis[e.to] == dis[u] + 1 && e.flow != e.cap) {
                int df = dfs(e.to, min(e.cap - e.flow, cap));
                if (df) {
                    e.flow += df;
                    G[e.to][e.rev].flow -= df;
                    return df;
                }
            }
        }
        dis[u] = -1;
        return 0;
    }
    bool bfs() {
        fill_n(dis, n, -1);
        queue<int> q;
        q.ee(s), dis[s] = 0;
        while (SZ(q)) {
            int tmp = q.front();
            q.pop();
            for (auto &u : G[tmp]) {
                if (!~dis[u.to] && u.flow != u.cap) {
                    q.ee(u.to);
                    dis[u.to] = dis[tmp] + 1;
                }
            }
        }
        return dis[t] != -1;
    }
    int maxflow(int _s, int _t) {
        s = _s, t = _t;
        int flow = 0, df;
        while (bfs()) {
            fill_n(cur, n, 0);
            while ((df = dfs(s, INF))) flow += df;
        }
        return flow;
    }
    void init(int _n) {
        n = _n;
        for (int i = 0; i < n; ++i) G[i].clear();
    }
    void reset() {
        for (int i = 0; i < n; ++i)
            for (auto &j : G[i]) j.flow = 0;
    }
    void add_edge(int u, int v, int cap) {
        G[u].eb(edge{v, cap, 0, SZ(G[v])});
        G[v].eb(edge{u, 0, 0, SZ(G[u])-1});
    }
} ff;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<pii> home(n);
    for (int i = 0; i < n; ++i) {
        cin >> home[i].X >> home[i].Y;
    }
    ff.init(800 + 2 + n);
    int s = 0, t = 801 + n;
    for (int i = 0; i < n; ++i) {
        ff.add_edge(s, i+1, 1);
        for (int j = home[i].X; j <= home[i].Y; ++j) {
            ff.add_edge(i+1, n + 2 * j - 1, 1);
        }
    }
    for (int i = 1; i <= 400; ++i) {
        ff.add_edge(n + 2 * i - 1, n + 2 * i, 1);
        ff.add_edge(n + 2 * i, t, 1);
    }
    int ans = ff.maxflow(s, t);
    cout << ans << endl;
    
    ff.init(800 + 2 + n);
    for (int i = 0; i < m; ++i) {
        ff.add_edge(s, i+1, 1);
        for (int j = home[i].X; j <= home[i].Y; ++j) {
            ff.add_edge(i+1, n + 2 * j - 1, 1);
        }
    }
    for (int i = 1; i <= 400; ++i) {
        ff.add_edge(n + 2 * i - 1, n + 2 * i, 1);
    }
    for (int i = m; i < n; ++i) {
        ff.add_edge(i+1, t, 1);
        for (int j = home[i].X; j <= home[i].Y; ++j) {
            ff.add_edge(n + 2 * j, i+1, 1);
        }
    }
    ans = ff.maxflow(s, t);
    cout << ans << endl;
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
