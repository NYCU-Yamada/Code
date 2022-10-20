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

const int MAXN = 5e5+5;
map<int,int> mp;
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i=0;i<n;++i) cin >> a[i];
    mp[a[0]] = 1;
    map<int,int> ans;
    ans[a[0]] = 1;
    for (int i=1;i<n;++i) {
        map<int,int> tmp;
        for (auto it : mp) {
            int cur = __gcd(it.X, a[i]);
            tmp[cur] = 1;
            ans[cur] = 1;
        }
        tmp[a[i]] = 1;
        ans[a[i]] = 1;
        mp.swap(tmp);
        // for (auto it : mp) debug(i, it.X);
    }
    cout << SZ(ans) << endl;
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