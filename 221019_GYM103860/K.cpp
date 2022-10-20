#include <bits/stdc++.h>
using namespace std;

#define int __int128
#define double __float80
using pii = pair<int,int>;
template <typename T> using MaxHeap = std::priority_queue<T>;
template <typename T> using MinHeap = std::priority_queue<T, vector<T>, greater<T>>;

#define SZ(a) ((int)(a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)
// #define X first
// #define Y second
#define ee emplace
#define eb emplace_back
#define ef emplace_front
#define pb pop_back
#define pf pop_front

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
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0)
#define endl '\n'
#define debug(...)
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

ostream& operator << (ostream &os, int n) {
    return os << (int64_t)n;
}

const int mod = 998'244'353;

int fpow(int base, int exp = mod-2, int ans = 1) {
    while (exp) {
        if (exp & 1) ans = ans * base % mod;
        base = base * base % mod, exp >>= 1;
    }
    return ans;
}

int C(int N, int M) {
    if (N < M) return 0;
    int ans = 1;
    for (int i = 1; i <= M; ++i) {
        ans = ans * (N-i+1) % mod;
        ans = ans * fpow(i) % mod;
    }
    return ans;
}

void solve() {
    int N, M;
    int64_t _N, _M; cin >> _N >> _M, N = _N, M = _M;
    if (N > M) swap(N, M);
    
    if (N == 1 and M == 1) cout << 1 << "\n";
    else if (N == 1) cout << (2 + C(M-2, 2)) % mod << "\n";
    else {
        int case1 = 4;
        int case2 = (N-2) * (N-2) + (M-2) * (M-2) + (N-2) * (N-3) + (M-2) * (M-3);
        // int case3 = C(N*M-4, 3)
                  // - C((N-2)*(M-2), 3)
                  // - ((M-2) * (M-2) * ((N*N*N + 3*N*N + 2*N - 24) % mod) % mod * fpow(6))
                  // - ((N-2) * (N-2) * ((M*M*M + 3*M*M + 2*M - 24) % mod) % mod * fpow(6))
                  // ;
        int case3 = (4 * (N-2) * (N-2) % mod * (M-2) * (M-2) % mod)
                  + (N > 3) * (((M-2) * ((M-2) * ((N-2) * (N-1) * (2*N-3) % mod * fpow(3) - 10) - (N-4) * (N+1) % mod) - 2 * (N-4) * C(3*M-6, 2)) % mod)
                  + (M > 3) * (((N-2) * ((N-2) * ((M-2) * (M-1) * (2*M-3) % mod * fpow(3) - 10) - (M-4) * (M+1) % mod) - 2 * (M-4) * C(3*N-6, 2)) % mod)
                  + (2 * (4 - (N == 3) - (M == 3)) * C((N-2)*(M-2), 2) % mod);
        int case4 = C((N-2)*(M-2), 4);
        // debug(case1, case2, case3, case4);
        
        // debug((4 * (N-2) * (N-2) % mod * (M-2) * (M-2) % mod) % mod);
        // debug(((N > 3) * ((M-2) * ((M-2) * ((N-2) * (N-1) * (2*N-3) % mod * fpow(3) - 10) - (N-4) * (N+1) % mod) - 2 * (N-4) * C(3*M-6, 2)) % mod) % mod);
        // debug(((M > 3) * ((N-2) * ((N-2) * ((M-2) * (M-1) * (2*M-3) % mod * fpow(3) - 10) - (M-4) * (M+1) % mod) - 2 * (M-4) * C(3*N-6, 2)) % mod) % mod);
        // debug((2 * (4 - (N == 3) - (M == 3)) * C((N-2)*(M-2), 2) % mod) % mod);
        
        cout << ((case1 + case2 + case3 + case4) % mod + mod) % mod << "\n";
    }
}

signed main() {
    IOS();
    int64_t t = 1; cin >> t;
    for (int i=1;i<=t;++i) solve();
    return 0;
}