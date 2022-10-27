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

const int mod = 1e9+7;

int fpow(int a, int b) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ret;
}

int dp[35][9];
int gtmask(int ok, int upp, int j) {
    int ret = 0;
    for (int i=0;i<3;++i) {
        int b1 = ((ok >> i) & 1), b2 = ((upp >> i) & 1), b3 = ((j >> i) & 1);
        if (b1 == b2) ret |= (b3 << i);
        else ret |= (b1 << i);
    }
    return ret;
}
vector<int> OK = {0, 3, 5, 6};
int gogo(int u1, int u2, int u3) {
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int i=0;i<32;++i) {
        int b1 = ((u1 >> i) & 1), b2 = ((u2 >> i) & 1), b3 = ((u3 >> i) & 1);
        int I = b1 * 4 + b2 * 2 + b3;
        for (int j=0;j<8;++j) {
            for (auto ok : OK) {
                dp[i + 1][gtmask(ok, I, j)] = (dp[i + 1][gtmask(ok, I, j)] + dp[i][j]) % mod;
            }
        }
    }
    return dp[32][0];
}

void solve() {
    int l1, r1, l2, r2, l3, r3;
    cin >> l1 >> r1 >> l2 >> r2 >> l3 >> r3;
    int ans1 = gogo(r1, r2, r3);
    int ans2 = gogo(r1, r2, l3-1);
    int ans3 = gogo(r1, l2-1, r3);
    int ans4 = gogo(l1-1, r2, r3);
    int ans5 = gogo(r1, l2-1, l3-1);
    int ans6 = gogo(l1-1, r2, l3-1);
    int ans7 = gogo(l1-1, l2-1, r3);
    int ans8 = gogo(l1-1, l2-1, l3-1);
    int ans = ((ans1 - ans2 - ans3 - ans4 + ans5 + ans6 + ans7 - ans8) % mod + mod) % mod;
    
    int den = (r1 - l1 + 1) * (r2 - l2 + 1) % mod * (r3 - l3 + 1) % mod;
    
    ans = ans * fpow(den, mod - 2) % mod;
    cout << (1 - ans + mod) % mod << endl;
}

signed main() {
    IOS();
    int t = 1; // cin >> t;
    for (int i=1;i<=t;++i) solve();
    return 0;
}