#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#include <bits/stdc++.h>
using namespace std;

// #define int int64_t
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

const int MAXN = 2e4+5;

struct Trie {
    vector<vector<int>> T;
    vector<int> cnt;
    void init() {
        T.clear();
        T.eb(6, -1);
        cnt.clear();
        cnt.eb(0);
        cnt.reserve((1 << 10) * MAXN);
    }
    void ins(vector<int> &val) {
        int cur = 0;
        for (auto x : val) {
            if (T[cur][x] == -1) {
                T[cur][x] = SZ(T);
                T.eb(6, -1);
                cnt.eb(0);
                // T[cur][x] = tot;
                // memset(T[tot], -1, sizeof(T[tot]));
                // cnt[tot] = 0;
                // ++tot;
            }
            cur = T[cur][x];
        }
        ++cnt[cur];
    }
    int cal(vector<int> &val) {
        int cur = 0;
        for (auto x : val) {
            if (x > 5) return 0;
            if (T[cur][x] == -1) return 0;
            cur = T[cur][x];
        }
        return cnt[cur];
    }
} trie;

string s[MAXN];
int sc[MAXN];

void solve() {
    int n;
    cin >> n;
    for (int i=0;i<n;++i) {
        cin >> s[i] >> sc[i]; 
        sc[i] /= 10;
    }
    
    // precalculate last 5 problems
    trie.init();
    for (int I=0;I<(1 << 10);++I) {
        int tmp = I;
        vector<int> tmpsum(n, 0);
        for (int i=5;i<10;++i) {
            int cur = tmp % 4;
            tmp /= 4;
            for (int j=0;j<n;++j) {
                tmpsum[j] += ((s[j][i] - 'A') == cur);
            }
        }
        trie.ins(tmpsum);
    }
    
    int ans = 0;
    for (int I=0;I<(1 << 10);++I) {
        int tmp = I;
        vector<int> tmpsum(n, 0);
        bool fg = true;
        for (int i=0;i<n;++i) tmpsum[i] = sc[i];
        for (int i=0;i<5;++i) {
            int cur = tmp % 4;
            tmp /= 4;
            for (int j=0;j<n;++j) {
                tmpsum[j] -= ((s[j][i] - 'A') == cur);
                if (tmpsum[j] < 0) {
                    fg = false;
                    break;
                }
            }
            if (!fg) break;
        }
        if (fg) ans += trie.cal(tmpsum);
    }
    cout << ans << endl;
}

signed main() {
    IOS();
    int t = 1; cin >> t;
    for (int i=1;i<=t;++i) solve();
    return 0;
}