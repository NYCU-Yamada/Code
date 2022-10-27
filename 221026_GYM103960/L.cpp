#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define double __float80
using pii = pair<int,int>;
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

#define SZ(a) ((int)(a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)
#define eb emplace_back
#define ef emplace_front
#define ee emplace
#define pb pop_back
#define pf pop_front
// #define X first
// #define Y second

#ifdef local
#define IOS() void()
#define debug(...) \
    fprintf(stderr, "\u001b[33mAt [%s], Line %d: (%s) = ", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), \
    fprintf(stderr, "\u001b[0m")
template <typename T> void _do(T &&_x) {cerr << _x << endl;}
template <typename T, typename ...S> void _do(T &&_x, S &&..._t) {cerr << _x << ", "; _do(_t...);}
#else
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0);
#define debug(...) void()
#define endl '\n'
#endif

template <typename U, typename V> bool chmin(U &u, V v) {return u > v ? u = v, 1 : 0;}
template <typename U, typename V> bool chmax(U &u, V v) {return u < v ? u = v, 1 : 0;}

vector<vector<pii>> adj;
vector<int> color, heavy, sz, color_dfn, tot, cnt, ans;
vector<pii> dfn;
int tot_ans = 0;

void add(int x) {
    tot_ans -= (tot[x] - cnt[x]) * cnt[x];
    cnt[x]++;
    tot_ans += (tot[x] - cnt[x]) * cnt[x];
}

void kill(int x) {
    tot_ans -= (tot[x] - cnt[x]) * cnt[x];
    cnt[x]--;
    tot_ans += (tot[x] - cnt[x]) * cnt[x];
}

void dfs_heavy(int now, int par) {
    static int tok = 0;
    color_dfn[tok] = color[now];
    dfn[now].first = tok++;
    for (auto [x, eid] : adj[now]) {
        if (x == par) continue;
        dfs_heavy(x, now);
        sz[now] += sz[x];
        if (heavy[now] == -1 || sz[heavy[now]] < sz[x]) heavy[now] = x;
    }
    dfn[now].second = tok;
}

void dfs(int now, int par, int peid, int keep) {
    int heavy_eid = -1;
    for (auto [x, eid] : adj[now]) {
        if (x != par and x != heavy[now]) dfs(x, now, eid, false);
        if (x == heavy[now]) heavy_eid = eid;
    }
    if (~heavy[now]) dfs(heavy[now], now, heavy_eid, true);
    
    add(color[now]);
    for (auto [x, eid] : adj[now]) {
        if (x == par or x == heavy[now]) continue;
        for (int i = dfn[x].first; i < dfn[x].second; ++i) {
            // cnt[color_dfn[i]]++;
            add(color_dfn[i]);
        }
    }
    
    // debug(now, par, peid, keep);
    // for (int x : cnt) cerr << x << " ";
    // cerr << "\n";
    
    if (~peid) ans[peid] = tot_ans;
    
    if (!keep) {
        for (int i = dfn[now].first; i < dfn[now].second; ++i) {
            // cnt[color_dfn[i]]--;
            kill(color_dfn[i]);
        }
    }
}

void solve() {
    int N; cin >> N;
    
          adj.resize(N);
        color.resize(N);
        heavy.assign(N,  -1);
           sz.assign(N,   1);
          tot.assign(N,   0);
          cnt.assign(N,   0);
          ans.assign(N-1, 0);
    color_dfn.resize(N);
          dfn.resize(N);
    
    for (int i = 0; i < N; ++i) cin >> color[i], ++tot[--color[i]];
    for (int i = 0, u, v; i < N-1; ++i) {
        cin >> u >> v, --u, --v;
        adj[u].eb(v, i), adj[v].eb(u, i);
    }
    
    dfs_heavy(0, -1);
    // for (auto [u, v] : dfn) debug(u, v);
    dfs(0, -1, -1, false);
    
    for (int x : ans) cout << x << " ";
    cout << "\n";
}

signed main() {
    IOS();
    int t = 1; // cin >> t;
    for (int i=1;i<=t;++i) solve();
    return 0;
}