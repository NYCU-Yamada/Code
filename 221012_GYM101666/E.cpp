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

const int MAXN = 505;

int B, R;
vector<pii> blue, red;

bitset<MAXN> vx, vy;
vector<int> G[MAXN];
int match[MAXN];

bool dfs(int x) {
    if(vx[x]) return false;
    vx[x] = true;
    for(int y : G[x]) {
        if(vy[y]) continue;
        vy[y] = true;
        if(match[y] == -1 || dfs(match[y])) {
            match[y] = x;
            return true;
        }
    }
    return false;
}

int calc(int thres) {
    for (int i = 0; i < MAXN; ++i) G[i].clear();
    for (int i = 0; i < B; ++i) {
        for (int j = 0; j < R; ++j) {
            if ((blue[i].X - red[j].X) * (blue[i].X - red[j].X) + (blue[i].Y - red[j].Y) * (blue[i].Y - red[j].Y) < thres) {
                /// build edge (i, j) ///
                G[i].eb(j);
            }
        }
    }
    int ans = 0;
    memset(match, -1, sizeof(match));
    for(int i = 0; i < B; i++) {
        vy.reset();
        vx.reset();
        dfs(i);
    }
    for(int i = 0; i < R; i++) if(match[i] != -1) ans++;
    return B + R - ans;
}

void solve() {
    int N; cin >> N >> B >> R;
    
    blue.resize(B), red.resize(R);
    for (auto &[x, y] : blue) cin >> x >> y;
    for (auto &[x, y] :  red) cin >> x >> y;
    
    int lo = 0, hi = 1E9, mi;
    while (lo < hi) {
        mi = (lo + hi + 1) >> 1;
        if (calc(mi) >= N) lo = mi;
        else               hi = mi - 1;
    }
    
    cout << fixed << setprecision(15) << sqrtl(lo) << "\n";
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