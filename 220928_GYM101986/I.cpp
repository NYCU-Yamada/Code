#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
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
    fprintf(stderr, "\u001b[33mLINE %d : (%s) = ", __LINE__, #__VA_ARGS__),\
    _do(__VA_ARGS__), fprintf(stderr, "\u001b[0m")
template<typename T> void _do(T &&_x) {cerr << _x << endl;}
template<typename T, typename ...S> void _do(T &&_x, S && ..._t){cerr << _x << ", "; _do(_t...);}
#define IOS()
#else
#define debug(...) void()
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0)
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

template <typename T, typename U>
ostream& operator << (ostream &os, const pair<T, U> &_p_) {
    os << "(" << _p_.first << ", " << _p_.second << ")";
    return os;
}

template <typename T>
ostream& operator << (ostream &os, const vector<T> &_vec_) {
    os << "[";
    for (int i = 0; i < SZ(_vec_); ++i) {
        if (i) os << ", ";
        os << _vec_[i];
    }
    os << "]";
    return os;
}

const int maxc = 100'000 + 5;

void solve() {
    int N; cin >> N;
    
    vector<pii> itv(N);
    for (auto &[l, r] : itv) cin >> l >> r;
    
    int ans_1 = 0;
    
    vector<int> L, R;
    for (auto &[l, r] : itv) L.eb(l), R.eb(r);
    sort(ALL(L)), sort(ALL(R));
    
    for (auto &[l, r] : itv) {
        // debug(R, l, upper_bound(ALL(R), l) - begin(R));
        // debug(L, r, end(L) - lower_bound(ALL(L), r));
        chmax(ans_1, N - (upper_bound(ALL(R), l) - begin(R)) - (end(L) - lower_bound(ALL(L), r)));
    }
    
    vector<int> pre(maxc, 0);
    for (auto &[l, r] : itv) ++pre[l], --pre[r];
    partial_sum(ALL(pre), begin(pre));
    
    int ans_2 = *max_element(ALL(pre));
    
    cout << ans_1 << " " << ans_2 << "\n";
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
