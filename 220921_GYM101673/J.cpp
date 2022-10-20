#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

// #define X first
// #define Y second
#define SZ(a) (int)((a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)
#define ee emplace
#define eb emplace_back
#define ef emplace_front
#define pb pop_back
#define pf pop_front

#ifdef local
#define debug(...) \
    fprintf(stderr, "LINE %d: (%s) = ". __LINE__, #__VA_ARGS__);\
    _do(__VA_ARGS__);
template<typename T> void _do(T &&_x){cerr << _x << endl;}
template<typename T, typename ...S> void _do(T &&_x, S &&..._t){cerr << _x << ", "; _do(_t...);}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0);
#define debug(...) void()
#endif

template<typename T>
ostream operator << (ostream &os, vector<T> &vec) {
    os << "[";
    for (int i = 0; i < SZ(vec); ++i) {
        if (i) os << ", ";
        os << vec[i];
    }
    os << "]";
    return os;
}

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int N = 10;

void solve() {
    vector<int> S(N), E(N), U(N), R(N), T(N);
    vector<int> TT(N), tt(N);
    for (int i = 0; i < N; ++i) {
        cin >> S[i] >> E[i];
        TT[i] = S[i] + E[i];
    }
    for (int i = 0; i < N; ++i) {
        cin >> U[i] >> R[i] >> T[i];
        tt[i] = U[i] + R[i];
    }
    int ans = 0;
    for (int cnt = 1; cnt <= 3; ++cnt) {
        for (int i = 0; i < N; ++i) {
            if (ans < T[i]) {
                ans += TT[i];
                chmax(T[i], ans - E[i]);
            }
            else {
                int num = (ans - T[i]) / tt[i];
                T[i] += num * tt[i] + U[i];
                if (ans < T[i]) ans = T[i];
                ans += TT[i];
                T[i] = max(T[i] + R[i], ans - E[i]);
            }
        }
    }
    cout << ans - E[N-1] << "\n";
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
