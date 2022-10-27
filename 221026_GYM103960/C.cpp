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

const int maxc = 1005;

vector<vector<bool>> vL, vD;
vector<int> p, sz;

int R(int x) {return x ^ p[x] ? p[x] = R(p[x]) : x;}
int U(int x, int y) {x = R(x), y = R(y); return x ^ y ? sz[y] += sz[x], p[x] = y, 1 : 0;}

void solve() {
    int N; cin >> N;
    
    vL.assign(maxc, vector<bool>(maxc, true));
    vD.assign(maxc, vector<bool>(maxc, true));
    
    int lx, ly; cin >> lx >> ly;
    for (int i = 0, nx, ny; i < N; ++i) {
        cin >> nx >> ny;
        if (lx == nx) {
            for (int y = min(ly, ny); y < max(ly, ny); ++y) vL[lx][y] = 0;
        }
        else if (ly == ny) {
            for (int x = min(lx, nx); x < max(lx, nx); ++x) vD[x][ly] = 0;
        }
        lx = nx, ly = ny;
    }
    
    p.resize(maxc * maxc), iota(ALL(p), 0);
    sz.assign(maxc * maxc, 1);
    
    auto tr = [](int x, int y) -> int {return x * maxc + y;};
    
    for (int i = 0; i < maxc; ++i) {
        for (int j = 0; j < maxc; ++j) {
            if (vL[i][j] and i) U(tr(i, j), tr(i-1, j));
            if (vD[i][j] and j) U(tr(i, j), tr(i, j-1));
        }
    }
    
    int max_sz = 0;
    for (int i = 0; i < maxc; ++i) {
        for (int j = 0; j < maxc; ++j) {
            if (R(tr(i, j)) == R(tr(maxc-1, maxc-1))) continue;
            chmax(max_sz, sz[R(tr(i, j))]);
        }
    }
    cout << max_sz << "\n";
}

signed main() {
    IOS();
    int t = 1; // cin >> t;
    for (int i=1;i<=t;++i) solve();
    return 0;
}

/*

cout << string(10, '=') << "\n";
for (int y = 9; y >= 0; --y) {
    for (int x = 0; x <= 9; ++x) cout << vR[x][y];
    cout << "\n";
}
cout << string(10, '=') << "\n";
for (int y = 9; y >= 0; --y) {
    for (int x = 0; x <= 9; ++x) cout << vD[x][y];
    cout << "\n";
}
cout << string(10, '=') << "\n";

*/