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

#define X first
#define Y second
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

const int maxn = 6e5 + 5;


struct Pt {
    int l, r, id;
    Pt(int a, int b, int c) :
        l(a), r(b), id(c) {}
    bool operator < (const Pt &a) const {
        return r < a.r;
    }
};

int l[maxn], r[maxn], k[maxn], bit[maxn], ans[maxn], bbit[2][maxn];
vector<pii> seg;
vector<Pt> ask;
vector<int> V;
int n, m;


void aadd(int id, int x, int v) {
    for(int i = x; i < maxn; i += i & (-i)) {
        bbit[id][i] += v;
    }
}

int aask(int id, int x) {
    int ret = 0;
    for(int i = x; i > 0; i -= i & (-i)) {
        ret += bbit[id][i];
    } 
    return ret;
}

int aask(int id, int l, int r) {
    return aask(id, r) - aask(id, l - 1);
}

void add(int x, int v) {
    for(int i = x; i < maxn; i += i & (-i)) {
        bit[i] += v;
    }
}

int ask_(int x) {
    int ret = 0;
    for(int i = x; i > 0; i -= i & (-i)) {
        ret += bit[i];
    }
    return ret;
}

int ask_(int l, int r) {
    return ask_(r) - ask_(l - 1);
}

pii dfs(int x) {
    int _min = k[x];
    int _max = k[x];
    if(l[x]) {
        pii temp = dfs(l[x]);
        chmin(_min, temp.X);
        chmax(_max, temp.Y);
        seg.eb(temp);
    }
    if(r[x]) {
        pii temp = dfs(r[x]);
        chmin(_min, temp.X);
        chmax(_max, temp.Y);
        seg.eb(temp);
    }
    return {_min, _max};
}

void solve() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i] >> k[i];
        V.eb(k[i]);
    }
    cin >> m;
    for(int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        V.eb(l), V.eb(r);
        ask.eb(l, r, i);
    }
    sort(ALL(V));
    V.erase(unique(ALL(V)), end(V));
    for(int i = 1; i <= n; i++) {
        k[i] = lower_bound(ALL(V), k[i]) - begin(V) + 1;
    }
    for(int i = 0; i < m; i++) {
        ask[i].l = lower_bound(ALL(V), ask[i].l) - begin(V) + 1;
        ask[i].r = lower_bound(ALL(V), ask[i].r) - begin(V) + 1;
    }
    seg.eb(dfs(1));
    sort(ALL(seg), [&](const pii &a, const pii &b){
        return a.Y < b.Y;
    });
    sort(ALL(ask));
    for(int i = 0; i < n; i++) {
        // debug(seg[i].X, seg[i].Y);
        aadd(0, seg[i].X, 1);
        aadd(1, seg[i].Y, 1);
    }
    // for(int i = 0; i < m; i++) {
        // debug(ask[i].l, ask[i].r);
    // }
    for(int i = 0, j = 0; i < m; i++) {
        while(j < n && seg[j].Y <= ask[i].r) {
            // debug("add"s, seg[j].X);
            add(seg[j].X, 1); j++;
        }
        // debug("ask"s, ask[i].l, ask[i].r);
        // debug(ans[ask[i].id]);
        ans[ask[i].id] = ask_(ask[i].l, ask[i].r);
        ans[ask[i].id] += aask(1, 1, ask[i].l - 1);
        ans[ask[i].id] += aask(0, ask[i].r + 1, maxn - 1);
        // debug(ans[ask[i].id]);
    }
    for(int i = 0; i < m; i++) {
        // debug(i, ans[i]);
        cout << 2LL * (n - ans[i]) + 1 << '\n';
    }
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
