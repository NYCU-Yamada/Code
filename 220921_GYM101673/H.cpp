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

const int maxn = 105;

int mx[] = {1, 1, 1, 0, -1, -1, -1, 0};
int my[] = {1, 0, -1, -1, -1, 0, 1, 1};

bitset<maxn> vis[maxn];
string mp[maxn];
int n, m;

bool in(int x, int y) {
    return (0 <= x && x < n) && (0 <= y && y < m);
}

void dfs(int i, int j) {
    vis[i][j] = 1;
    for(int d = 0; d < 8; d++) {
        int ii = i + mx[d];
        int jj = j + my[d];
        if(in(ii, jj) && mp[ii][jj] == '#' && !vis[ii][jj]) {
            dfs(ii, jj);
        }
    }
}    

void solve() {
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        vis[i].reset();
        cin >> mp[i];
    }
    int ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(mp[i][j] == '#' && !vis[i][j]) {
                ans++; dfs(i, j);
            }
        }
    }
    cout << ans << '\n';
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
