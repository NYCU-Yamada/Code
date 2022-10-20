#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define double __float80
using pii = pair<int,int>;
template <typename T> using MaxHeap = std::priority_queue<T>;
template <typename T> using MinHeap = std::priority_queue<T, vector<T>, greater<T>>;

#define SZ(a) ((int)(a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)
#define X first
#define Y second
#define ee emplace
#define eb emplace_back
#define ef emplace_front
#define pb pop_back
#define pf pop_front

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
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0)
#define endl '\n'
#define debug(...)
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

int n, m, x, y;

pii cal(int pre, int len) {
    int val = min(y - pre, x);
    int temp = len % (y + 2);
    int cnt = 2 * (len / (y + 2));
    if(temp > val) {
        cnt++; temp -= val + 1;
    }
    return {cnt, temp};
}

void solve() {
    int ans = 0;
    cin >> n >> m >> x >> y;
    int pre_pos = 0, pre_len = 0;
    for(int i = 0; i < m; i++) {
        int p; cin >> p;
        auto temp = cal(pre_len, p - pre_pos - 1);
        pre_len = temp.Y; ans += temp.X;
        pre_pos = p;
    }
    auto temp = cal(pre_len, n - pre_pos);
    ans += temp.X;
    cout << ans << '\n';
}

signed main() {
    IOS();
    int t = 1; // cin >> t;
    for (int i=1;i<=t;++i) solve();
    return 0;
}