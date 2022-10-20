#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
template<typename T> using MaxHeap = priority_queue<T>;
template<typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;
#define SZ(a) (int)((a).size())
#define X first
#define Y second
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



void solve() {
    int N, K; cin >> N >> K;
    
    string S;
    vector<int> vec;
    int tmp;
    
    while (cin >> S) {
        if (S == "undo") {
            cin >> tmp;
            while (tmp--) vec.pb();
        }
        else {
            tmp = stoi(S);
            vec.eb(tmp + 10000 * N);
        }
    }
    
    cout << accumulate(ALL(vec), (int)0) % N << "\n";
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
