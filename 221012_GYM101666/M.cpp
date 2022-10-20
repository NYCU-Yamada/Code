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

#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())
#define eb emplace_back


#ifdef local
#define IOS() void()
#else 
#define IOS() ios_base::sync_with_stdio(), cin.tie()
#define endl "\n"
#endif



void solve() {
    int N; cin >> N;
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    if (x1 > x2) swap(x1, x2), swap(y1, y2);
    
    vector<pii> pts;
    for (int i = 0, x, y; i < N; ++i) {
        cin >> x >> y;
        if (x1 <= x and x <= x2 and min(y1, y2) <= y and y <= max(y1, y2)) {
            pts.eb(x, y * (y1 <= y2 ? 1 : -1));
        }
    }
    sort(ALL(pts));
    
    vector<int> lnds;
    for (auto [x, y] : pts) {
        // cerr << x << " " << y << "\n";
        if (!SZ(lnds) or y >= lnds.back()) lnds.eb(y);
        else *upper_bound(ALL(lnds), y) = y;
    }
    cout << SZ(lnds) << "\n";
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