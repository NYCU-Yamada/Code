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

// #define X first
// #define Y second
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

const double PI = acos(-1);

double M, N, R;

double arc(double L, double d) {
    return PI * L * R / N * d / M;
}

double cal(double x1, double y1, double x2, double y2, double L) {
    if(y1 > y2) {
        swap(y1, y2);
        swap(x1, x2);
    }
    double ret = arc(L, abs(x1 - x2));
    if(y1 <= L and L <= y2) {
        ret += R / N * (y2 - y1);
    }
    else if(L < y1) {
        ret += R / N * (y1 - L + y2 - L);
    }
    else {
        ret += R / N * (L - y1 + L - y2);
    }
    return ret;
}

void solve() {
    cin >> M >> N >> R;
    double a,b,c,d;
    cin >> a >> b >> c >> d;
    // double ans = PI * (min(b, d) * r / n) * abs(a - c) / m + r * abs(b - d) / n;
    double ans = 1e18, temp;
    for(int L = 0; L <= N; L++) {
        if(chmin(ans, cal(a, b, c, d, L))) {
            temp = L;
        }
    }
    // debug(temp);
    cout << fixed << setprecision(15) << ans << endl;
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