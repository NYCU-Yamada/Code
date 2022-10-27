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

const int MAXN = 1e4+5;

vector<int> e[MAXN], re[MAXN];
bitset<MAXN> vis;
vector<int> tp;
int scc[MAXN];
int in[MAXN], out[MAXN];
// int dsu[MAXN], sz[MAXN];
// int fnd(int x) {
    // debug(x);
    // return (x == dsu[x] ? x : dsu[x] = fnd(dsu[x]));
// }
// void mrg(int x, int y) {
    // x = fnd(x), y = fnd(y);
    // if (x == y) return;
    // if (sz[x] < sz[y]) swap(x, y);
    // dsu[y] = x;
    // sz[x] += sz[y];
// }
void dfs1(int x) {
    vis[x] = 1;
    for (auto i : e[x]) if (!vis[i]) dfs1(i);
    tp.eb(x);
}
void dfs2(int x, int cnt) { 
    vis[x] = 1;
    scc[x] = cnt;
    for (auto i : re[x]) {
        if (!vis[i]) dfs2(i, cnt);
    }
}
void solve() {
    int n,m;
    cin >> n >> m;
    for (int i=0;i<m;++i) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        e[u].eb(v), re[v].eb(u);
    }
    
    for (int i=0;i<n;++i) if (!vis[i]) dfs1(i);
    vis.reset();
    int cnt = 0;
    for (int i=n-1;i>=0;--i) if (!vis[tp[i]]) dfs2(tp[i], cnt++);
    if (cnt == 1) return cout << 0 << endl, void();
    
    // for (int i=0;i<cnt;++i) dsu[i] = i, sz[i] = 1;
    for (int i=0;i<n;++i) {
        for (auto j : e[i]) {
            if (scc[i] == scc[j]) continue;
           ++out[scc[i]], ++in[scc[j]];
           // mrg(scc[i], scc[j]);
        }
    }
    debug(cnt);
    // vector<int> In(cnt, 0), Out(cnt, 0);
    int In = 0, Out = 0;
    for (int i=0;i<cnt;++i) {
        // int cur = fnd(i);
        // In[cur] += (in[i] == 0);
        // Out[cur] += (out[i] == 0);
        In += (in[i] == 0);
        Out += (out[i] == 0);
    }
    // int ans = 0;
    // for (int i=0;i<cnt;++i) {
        // ans += max(In[i], Out[i]);
    // }
    int ans = max(In, Out);
    cout << ans << endl;
}

signed main() {
    IOS();
    int t = 1; // cin >> t;
    for (int i=1;i<=t;++i) solve();
    return 0;
}