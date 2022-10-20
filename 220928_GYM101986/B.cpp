#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define double long double
using pii = pair<int, int>;
template<typename T> using MaxHeap = priority_queue<T>;
template<typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

#define SZ(a) (int)((a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)
#define X first
#define Y second
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

pii operator - (const pii &lhs, const pii rhs) {
    return {lhs.first - rhs.first, lhs.second - rhs.second};
}

bool chk(pii a, pii b) {
    return (a.X * b.Y - a.Y * b.X) == 0;
}

int N, ans = 0;
vector<pii> point;
vector<int> group, app;

void calc() {
    vector<pii> vec(N/2);
    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N; ++j) {
            if (group[i] == group[j]) vec[group[i]] = point[i] - point[j];
        }
    }
    // debug(vec);
    
    int cnt = 0;
    for (int a = 0; a < N/2; a++) {
        for (int b = a + 1; b < N/2; b++) {
            if (chk(vec[a], vec[b])) cnt++;
        }
    }
    chmax(ans, cnt);
}

void dfs(int now, int mx) {
    if (now == N) return calc();
    for (int i = 0; i <= mx; ++i) {
        if (app[i] < 2) group[now] = i, ++app[i], dfs(now+1, mx), --app[i];
    }
    if (mx+1 < N/2) group[now] = mx+1, ++app[mx+1], dfs(now+1, mx+1), --app[mx+1];
}

void solve() {
    cin >> N;
    
    point.resize(N);
    for (auto &[x, y] : point) cin >> x >> y;
    
    group.resize(N), app.assign(N/2, 0);
    dfs(0, -1);
    
    cout << ans << "\n";
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
