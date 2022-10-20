#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define double __float80
using pii = pair<int,int>;

#define SZ(a) ((int)(a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)

#ifdef local
#define IOS() void()
#else
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0)
#define endl '\n'
#define debug(...)
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

void solve() {
    int N; cin >> N;
    
    vector<int> A(N);
    for (int &x : A) cin >> x;
    sort(RALL(A));
    
    int X; cin >> X;
    
    int ans = 0;
    for (int i = 0; i < (1<<(N-1)); ++i) {
        int now = X;
        for (int j = 0; j < N-1; ++j) {
            if (i >> j & 1) now %= A[j];
        }
        now %= A.back();
        chmax(ans, now);
    }
    cout << ans << "\n";
}

signed main() {
    IOS();
    int t = 1; // cin >> t;
    for (int i=1;i<=t;++i) solve();
    return 0;
}