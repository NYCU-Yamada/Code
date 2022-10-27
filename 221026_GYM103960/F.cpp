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

void solve() {
    int N, C; cin >> N >> C;
    
    unordered_map<int, int> mp;
    for (int i = 0; i < N; ++i) {
        string S; cin >> S;
        int val = 0, mul = 0;
        for (char &c : S) {
            val = 26 * val + (c - 'a') * (c != '*');
            mul = 26 * mul + (c == '*');
        }
        for (int j = 0; j < 26; ++j) ++mp[val + j * mul];
    }
    
    auto decode = [&](int key) -> string {
        string ans;
        for (int i = 0; i < C; ++i) ans += (key % 26) + 'a', key /= 26;
        reverse(ALL(ans));
        return ans;
    };
    
    int max_app = -1, min_str;
    for (auto [key, val] : mp) {
        if (chmax(max_app, val)) min_str = key;
        if (max_app == val) chmin(min_str, key);
    }
    cout << decode(min_str) << " " << max_app << "\n";
}

signed main() {
    IOS();
    int t = 1; // cin >> t;
    for (int i=1;i<=t;++i) solve();
    return 0;
}