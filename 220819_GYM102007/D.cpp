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

void solve() {
    int N, A, B; cin >> N >> A >> B;
    
    vector<array<int, 3>> vertex(N);
    for (auto &[l, r, c] : vertex) cin >> l >> r >> c;
    
    vector<int> p(N);
    iota(ALL(p), 0);
    
    auto R = [&](auto &&R_, int x) -> int {return p[x] ^ x ? p[x] = R_(R_, p[x]) : x;};
    auto U = [&](int x, int y) -> int {x = R(R, x), y = R(R, y); return x ^ y ? p[x] = y, 1 : 0;};
    
    deque<array<int, 3>> que{{A, B, 0}};
    while (SZ(que)) {
        auto [a, b, dis] = que[0]; que.pf();
        // debug(a, b, dis, R(R, a), R(R, b));
        if (vertex[a][2] != vertex[b][2]) return cout << dis << "\n", void();
        if (!U(a, b)) continue;
        que.eb(array{vertex[a][0], vertex[b][0], dis + 1});
        que.eb(array{vertex[a][1], vertex[b][1], dis + 1});
    }
    cout << "indistinguishable" << "\n";
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
