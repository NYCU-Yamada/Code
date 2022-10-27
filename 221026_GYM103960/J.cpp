#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#include <bits/stdc++.h>
using namespace std;
// #define int int64_t
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

bool chk(int sum_j, int sum_m) {
    if(sum_j > 23 && sum_m <= 23) return true;
    if(sum_j <= 23 && sum_m == 23) return true;
    return false;
}

int cnt[15] = {};

void solve() {
    int N;
    cin >> N;
    int sum_m = 0, sum_j = 0;
    for(int i = 0; i < 2; i++) {
        int x; cin >> x; cnt[x]++;
        x = min(x, 10);
        sum_j += x;
    }
    for(int i = 0; i < 2; i++) {
        int x; cin >> x; cnt[x]++;
        x = min(x, 10);
        sum_m += x;
    }
    for(int i = 0; i < N; i++) {
        int x; cin >> x; cnt[x]++;
        x = min(x, 10);
        sum_m += x; sum_j += x;
    }
    int ans = -1;
    for(int i = 1; i <= 13; i++) {
        if(cnt[i] == 4) continue;
        int val = min(i, 10);
        if(chk(sum_j + val, sum_m + val)) {
            ans = val; break;
        }
    }
    cout << ans << '\n';
}

signed main() {
    IOS();
    int t = 1; // cin >> t;
    for (int i=1;i<=t;++i) solve();
    return 0;
}