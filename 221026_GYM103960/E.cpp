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

const int maxc = 1E6 + 5;

void solve() {
    int N; cin >> N;
    
    vector<set<int>> A(maxc);
    for (int i = 0, a_i; i < N; ++i) cin >> a_i, A[--a_i].ee(i);
    
    int cnt = 0, tok = maxc-1;
    while (tok >= 0) {
        if (!SZ(A[tok])) {--tok; continue;}
        ++cnt;
        int now = *A[tok].rbegin();
        auto it = begin(A[0]);
        // debug(tok, now);
        for (int i = tok; i >= 0; --i) {
            if ((it = A[i].lower_bound(now)) == end(A[i])) break;
            now = *it, A[i].erase(it);
        }
    }
    cout << cnt << "\n";
}

signed main() {
    IOS();
    int t = 1; // cin >> t;
    for (int i=1;i<=t;++i) solve();
    return 0;
}