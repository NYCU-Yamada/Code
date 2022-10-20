#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template <typename T> using MinHeap = std::priority_queue<T, vector<T>, greater<T>>;
template <typename T> using MaxHeap = std::priority_queue<T>;

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
    cerr << "\u001b[33m",\
    cerr << "At func [" << __FUNCTION__ << "], line " << __LINE__ << ", ",\
    cerr << "(" << #__VA_ARGS__ << ") = ", _do(__VA_ARGS__),\
    cerr << "\u001b[0m"
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define IOS() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

bool flag = true;

vector<int> color;
vector<pii> child;

void recur(int &id, int c1, int c2) {
    int now = id;
    
    if (c2) color[now] = 2, --c2;
    else    color[now] = 1, --c1;
    if (c1 == 0 and c2 == 0) return;
    
    // debug(now, c1, c2);
    
    int flag_tr = 0;
    int szL = (c1+1) / 2 +  c2    / 2 * 2;
    int szR =  c1    / 2 + (c2+1) / 2 * 2;
    if (szR - szL == 2 and c1) flag_tr = 1, --szR, ++szL;
    if (abs(szL - szR) > 1) flag = false;
    
    if (szL) {
        child[now].first = ++id;
        recur(id, (c1+1)/2 + flag_tr, c2/2);
    }
    if (szR) {
        child[now].second = ++id;
        recur(id, c1/2 - flag_tr, (c2+1)/2);
    }
}

void solve() {
    int A, B; cin >> A >> B;
    
    color.assign(A+B+1, 0);
    child.assign(A+B+1, {0, 0});
    
    int id = 1;
    recur(id, A, B);
    
    if (!flag) cout << "-1" << "\n";
    else {
        for (int i = 1; i <= A+B; ++i) {
            cout << color[i] << " " << child[i].first << " " << child[i].second << "\n";
        }
    }
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
