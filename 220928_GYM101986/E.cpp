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

string s, t;
int n, k;

void solve() {
    cin >> n >> k;
    cin >> s >> t;
    s = "#" + s;
    t = "#" + t;
    vector<int> sum(n + 1, 0), dp(n + 1, 0);
    for(int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + (int)(t[i] != t[i - 1]);
    }
    deque<int> dq;
    dq.push_back(0);
    for(int i = 1; i <= n; i++) {
        while(SZ(dq) && (i - dq.front() > k)) dq.pop_front();
        // vector<int> tmp(ALL(dq));
        // debug(tmp);
        if(t[i] == s[i]) 
            dp[i] = dp[i - 1];
        else 
            dp[i] = dp[dq.front()] + (sum[i] - sum[dq.front()]) / 2 + 1;
        if(i < n && sum[i + 1] == sum[i]) 
            sum[i]--;
        while(SZ(dq) && (2 * dp[dq.back()] - sum[dq.back()]) > (2 * dp[i] - sum[i])) dq.pb(); 
        dq.eb(i);
        
    }
    // debug(dp);
    cout << dp[n] << '\n';
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
