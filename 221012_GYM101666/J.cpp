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

const int MX = 5e6+5;

int lb(int x) {return x & (-x);}
int B[2][MX + 100];
void add(int x, int val, int id) {
    x++;
    for(int i = x; i < MX; i += lb(i)) {
        B[id][i] += val;
    }
}
void add(int l, int r, int val, int id) {
    add(l, val, id); add(r + 1, -val, id);
}
int qr(int pos, int id) {
    int ret = 0; pos++;
    for(int i = pos; i > 0; i -= lb(i)) {
        ret += B[id][i];
    }
    return ret;
}
vector<pii> even, odd;
void init() {
    int cur = 0;
    even.eb(0, 0);
    for (int i=1;i<1500;++i) {
        cur += i;
        if (cur > MX) break;
        if (cur % 2 == 0) even.eb(cur, i);
        else odd.eb(cur, i);
    }
}
void add_frog(int pos, int T) {
    int l = pos, r = pos;
    for (auto ev : even) {
        int tl = max(0LL, pos - ev.X), tr = min(MX-1, pos + ev.X);
        add(tl, l, T * ev.Y, pos % 2);
        add(r, tr, T * ev.Y, pos % 2);
        
        l = max(0LL, tl - 2), r = min(MX-1, tr + 2);
    }
    
    l = pos - 1, r = pos + 1;
    for (auto od : odd) {
        int tl = max(0LL, pos - od.X), tr = min(MX-1, pos + od.X);
        add(tl, l, T * od.Y, !(pos % 2));
        add(r, tr, T * od.Y, !(pos % 2));
        
        l = max(0LL, tl - 2), r = min(MX-1, tr + 2);
    }
}

int cal(int p) {
    return qr(p, p % 2);
}

void solve() {
    init();
    int n, t;
    cin >> n >> t;
    t++;
    for (int i=0;i<n;++i) {
        int p;
        cin >> p;
        p++;
        add_frog(p, 1);
    }
    int Q;
    cin >> Q;
    while (Q--) {
        char cmd;
        int p;
        cin >> cmd >> p;
        p++;
        if (cmd == 't') t = p;
        else {
            int T = 1;
            if (cmd == '-') T = -1;
            add_frog(p, T);
        }
        cout << cal(t) << endl;
    }
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