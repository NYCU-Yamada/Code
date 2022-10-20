#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
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
    fprintf(stderr, "LINE %d: (%s) = ". __LINE__, #__VA_ARGS__);\
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

const int MAXN = 1e4+5;

int n;
vector<int> e[MAXN];
int sz[MAXN];
int cnt[MAXN];
pii P[MAXN];
void st(pii &cur, int val) {
    if (val > cur.X) {
        swap(cur.X, cur.Y);
        cur.X = val;
    }
    else if (val > cur.Y) cur.Y = val;
}
void dfs(int x, int p) {
    sz[x] = 1;
    P[x] = {0, 0};
    for (auto i : e[x]) {
        if (i == p) continue;
        dfs(i, x);
        sz[x] += sz[i];
        cnt[x] += (n+1 - sz[i] - 1) * sz[i];
        cnt[i] += (sz[i] - 1) * (n+1 - sz[i]);
        
        st(P[x], sz[i]);
    }
    st(P[x], n+1 - sz[x]);
}
void solve() {
    cin >> n;
    for (int i=0;i<n;++i) {
        int u,v;
        cin >> u >> v;
        e[u].eb(v);
        e[v].eb(u);
    }
    dfs(0, 0);
    pii ans = {0, 0};
    for (int i=0;i<=n;++i) chmax(ans, pii(cnt[i], P[i].X * P[i].Y));
    cout << ans.X / 2 << ' ' << ans.X / 2 - ans.Y << endl;
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
