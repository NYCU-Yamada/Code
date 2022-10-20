#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
template<typename T> using MaxHeap = priority_queue<T>;
template<typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;
#define SZ(a) (int)((a).size())
// #define X first
// #define Y second
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)
#define eb emplace_back
#define pb pop_back
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

inline void rot(char &c, int k) {
    c += k % 26;
    if (c > 'Z') c -= 26;
}

void solve() {
    string S; cin >> S;
    int N = SZ(S);
    
    string A = S.substr(0, N/2), B = S.substr(N/2);
    
    int sum_A = 0, sum_B = 0;
    for (char &x : A) sum_A += x - 'A';
    for (char &x : B) sum_B += x - 'A';
    for (char &x : A) rot(x, sum_A);
    for (char &x : B) rot(x, sum_B);
    
    for (int i = 0; i < N/2; ++i) rot(A[i], B[i] - 'A');
    
    cout << A << "\n";
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
