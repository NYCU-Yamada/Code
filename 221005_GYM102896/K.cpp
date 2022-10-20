#include <bits/stdc++.h>
using namespace std;

#ifdef local
#define IOS() void()
#else
#define IOS() ios_base::sync_with_stdio(0), cin.tie(0)
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

void solve() {
    int N; cin >> N;
    
    int ans = 0, min_price = INT_MAX;
    for (int i = 1; i <= N; ++i) {
        int price; cin >> price;
        string pack; cin >> pack;
        
        vector<int> cnt(10, 0);
        for (char &c : pack) ++cnt[c-'0'];
        if (cnt[0] >= 1 and cnt[1] >= 1 and cnt[2] >= 2) {
            if (chmin(min_price, price)) ans = i;
        }
    }
    cout << ans << "\n";
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
