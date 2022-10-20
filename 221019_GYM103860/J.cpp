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

const int MAXN = 20005;

// const int P[] = {
    // 1000000007, 998244353
// };
// const int MAXH = 2;

// vector<int> operator* (const vector<int> &a, const int &b) {
    // vector<int> ret(MAXH);
    // for(int i = 0; i < MAXH; ++i) {
        // ret[i] = a[i] * b % P[i];
    // }
    // return ret;
// }
// vector<int> operator+ (const vector<int> &a, const int &b) {
    // vector<int> ret(MAXH);
    // for(int i = 0; i < MAXH; ++i) {
        // ret[i] = (a[i] + b) % P[i];
    // }
    // return ret;
// }


int sc[MAXN], sum[MAXN];
string s[MAXN];
int n;

// Trie
vector<vector<int>> T;
vector<int> cnt;

// Let's make it hash
// map<vector<int>, int> cnt;


void init() {
    T.clear();
    cnt.clear();
    T.eb(5, -1);
    cnt.eb(0);
    // cnt.clear();
}

void insert(int val[], int len) {
    int cur = 0;
    for(int i = 0; i < len; ++i) {
        if(T[cur][val[i]] == -1) {
            T[cur][val[i]] = SZ(T);
            T.eb(5, -1);
            cnt.eb(0);
        }
        cur = T[cur][val[i]];
    }
    ++cnt[cur];
    // vector<int> res(MAXH, 0);
    // for(int i = 0; i < len; ++i) {
        // res = res * 7 + val[i];
    // }
    // cnt[res]++;
}

int cal(int val[], int len) {
    int cur = 0;
    for(int i = 0; i < len; ++i) {
        if(val[i] > 4) return 0;
        if(T[cur][val[i]] == -1) return 0;
        cur = T[cur][val[i]];
    }
    return cnt[cur];
    // vector<int> res(MAXH, 0);
    // for(int i = 0; i < len; ++i) {
        // res = res * 7 + val[i];
    // }
    // if(cnt.count(res)) return cnt[res];
    // return 0;
}

void solve() {
    cin >> n;
    init();
    for(int i = 0; i < n; ++i) {
        cin >> s[i] >> sc[i];
        sc[i] /= 10;
        for(int j = 0; j < 10; j++) {
            s[i][j] -= 'A';
        }
    }
    for(int S = 0; S < (1 << 8); ++S) {
        memset(sum, 0, sizeof(int) * n);
        for(int i = 0; i < 4; ++i) {
            int cur = (S >> (i << 1)) & 3;
            for(int j = 0; j < n; ++j) {
                if(s[j][i] == cur) sum[j]++;
            }
        }
        insert(sum, n);
    }
    int ans = 0;
    for(int S = 0; S < (1 << 12); ++S) {
        bool flag = true;
        memcpy(sum, sc, sizeof(int) * n);
        for(int i = 4; i < 10; ++i) {
            int cur = (S >> ((i - 4) << 1)) & 3;
            for(int j = 0; j < n; ++j) {
                if(s[j][i] == cur) {
                    sum[j]--; 
                    if(sum[j] < 0) {
                        flag = false; break;
                    }
                }
            }
            if(!flag) break;
        }
        if(flag) ans += cal(sum, n);
    }
    cout << ans << '\n';
}

signed main() {
    IOS();
    int t = 1; cin >> t;
    for (int i=1;i<=t;++i) solve();
    return 0;
}