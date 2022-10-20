#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
template<typename T> using MaxHeap = priority_queue<T>;
template<typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

#define SZ(a) (int)((a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)
// #define X first
// #define Y second
#define eb emplace_back
#define ef emplace_front
#define ee emplace
#define pb pop_back
#define pf pop_front

#ifdef local
#define debug(...) \
    fprintf(stderr, "LINE %d : (%s) = ", __LINE__, #__VA_ARGS__),\
    _do(__VA_ARGS__)
template<typename T> void _do(T &&_x) {cerr << _x << endl;}
template<typename T, typename ...S> void _do(T &&_x, S && ..._t){cerr << _x << ", "; _do(_t...);}
#define IOS()
#else
#define debug(...) void()
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0);
#endif

void solve() {
    int L, K; cin >> L >> K;
    
    vector<int> dp(L+K+1, 0);
    dp[1] = dp[K] = 1;
    for (int i = 1; i <= L; ++i) {
        dp[i] += (i >= 2 ? dp[i-2] : 0) + (i >= K+1 ? dp[i-K-1] : 0);
        // debug(i, dp[i]);
    }
    cout << accumulate(begin(dp) + 1, begin(dp) + L + 1, (int)0) << "\n";
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
