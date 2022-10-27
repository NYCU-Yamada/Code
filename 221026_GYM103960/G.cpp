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
#define X first
#define Y second

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


map<pair<pii, pii>, int> id;
vector<vector<pii>> tri;
vector<vector<int>> G;
int N;
vector<int> W;
const int MAXN = 1e5+5;
const int INF = 0x3f3f3f3f3f3f3f3f;
int dp[MAXN][2];

void dfs(int x, int p) {
    // debug(x);
    dp[x][1] = W[x];
    for (auto i : G[x]) {
        if (i == p) continue;
        dfs(i, x);
        dp[x][1] += min(dp[i][0], dp[i][1]);
    }
    if (SZ(G[x]) <= 2) dp[x][0] = INF;
    else {
        for (auto i : G[x]) {
            if (i == p) continue;
            dp[x][0] += dp[i][1];
        }
    }
}

void solve() {
    cin >> N;
    G.resize(N);
    tri.resize(N);
    W.resize(N);
    for(int i = 0; i < N; ++i) {
        tri[i].resize(3);
        for(int j = 0; j < 3; j++) {
            cin >> tri[i][j].X >> tri[i][j].Y;
        }
        W[i] = tri[i][0].X * tri[i][1].Y + tri[i][1].X * tri[i][2].Y + tri[i][2].X * tri[i][0].Y - tri[i][1].X * tri[i][0].Y - tri[i][2].X * tri[i][1].Y - tri[i][0].X * tri[i][2].Y;
        W[i] = abs(W[i]);
        debug(W[i]);
        sort(ALL(tri[i]));
        for(int j = 0; j < 3; j++) {
            for(int k = j + 1; k < 3; k++) {
                pair<pii, pii> temp =  {tri[i][j], tri[i][k]};
                if(id.count(temp)) {
                    int prev_id = id[temp];
                    G[prev_id].eb(i);
                    G[i].eb(prev_id);
                    // debug(prev_id, i);
                }
                id[temp] = i;
            }
        }
    }
    
    dfs(0, 0);
    int ans = min(dp[0][0], dp[0][1]);
    cout << ans/2 << "." << (ans&1 ?5:0) << endl;
}

signed main() {
    IOS();
    int t = 1; // cin >> t;
    for (int i=1;i<=t;++i) solve();
    return 0;
}