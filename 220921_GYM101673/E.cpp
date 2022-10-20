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
    fprintf(stderr, "LINE %d: (%s) = ", __LINE__, #__VA_ARGS__);\
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

const int maxn = 1005;

int is[maxn][maxn], all[maxn][maxn];
map<string, int> id;
int n, q, tot = 0;

int get_id(string &s) {
    if(!id[s]) {
        id[s] = ++tot;
    }
    return id[s];
}

void floyd(int v[maxn][maxn]) {
    for(int k = 1; k <= tot; k++) {
        for(int i = 1; i <= tot; i++) {
            for(int j = 1; j <= tot; j++) {
                v[i][j] = min(v[i][j], v[i][k] + v[k][j]);
            }
        }
    }
}

void solve() {
    cin >> n >> q;
    memset(is, 0x3f, sizeof(is));
    memset(all, 0x3f, sizeof(all));
    for(int i = 1; i <= tot; i++) {
        all[i][i] = 0;
    }
    for(int i = 0; i < n; i++) {
        string A, B, C;
        cin >> A >> B >> C;
        int x = get_id(A);
        int y = get_id(C);
        if(B == "is-a") {
            is[x][y] = 1;
            all[x][y] = 1;
        }
        else all[x][y] = -100000; 
    }
    
    floyd(is);
    floyd(all);
    for(int i = 1; i <= q; i++) {
        string A, B, C;
        cin >> A >> B >> C;
        cout << "Query " << i << ": ";
        int x = id[A], y = id[C];
        if (x == y && B[0] == 'i') cout << "true\n";
        else if(B == "has-a" && all[x][y] < 0) cout << "true\n";
        else if(B == "is-a" && all[x][y] < 0x3f3f3f3f3f3f && all[x][y] >= 0) cout << "true\n";
        else cout << "false\n";
    }
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
