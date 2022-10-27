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
// #define X first
// #define Y second

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

vector<int> A, B;

struct cute {
    int sum;
    vector<int> V, bit[2];
    void init(vector<int> &val) {
        for(int i = 0; i < SZ(val); ++i) {
            V.eb(val[i]);
        }
        sum = 0;
        sort(ALL(V));
        V.erase(unique(ALL(V)), end(V));
        for(int i = 0; i < 2; ++i) {
            bit[i].resize(SZ(V) + 1);
            fill(ALL(bit[i]), 0);
        }
    }
    int kth(int k) {
        int ret = 0;
        for(int i = __lg(SZ(V)); i >= 0; --i) {
        if(ret + (1 << i) <= SZ(V) && bit[0][ret + (1 << i)] < k)  
            k -= bit[0][ret += (1 << i)];
        }
        return ret + 1;
    }
    int ask(int id, int x) {
        int ret = 0;
        for(int i = x; i > 0; i -= i & (-i)) {
            ret += bit[id][i];
        }
        return ret;
    }
    int ask(int id, int l, int r) {
        return ask(id, r) - ask(id, l - 1);
    }
    void add(int id, int x, int v) {
        for(int i = x; i <= SZ(V); i += i & (-i)) {
            bit[id][i] += v; 
        }
    }
    void insert(int a, int b) {
        sum += a;
        int pos = lower_bound(ALL(V), b) - begin(V) + 1;
        add(0, pos, 1); add(1, pos, b);
    }
    void erase(int a, int b) {
        sum -= a;
        int pos = lower_bound(ALL(V), b) - begin(V) + 1;
        add(0, pos, -1); add(1, pos, -b);
    }
    int cal(int k) {
        int temp = ask(0, 0, SZ(V)) - k + 1;
        temp = kth(temp);
        // debug(ask(0, 1, SZ(V)), temp, SZ(V));
        int sum_ = ask(1, temp, SZ(V));
        int cnt_ = ask(0, temp, SZ(V));
        // debug(sum_, cnt_);
        // debug(V[temp - 1], sum_, cnt_, k, sum + sum_ - (cnt_ - k) * V[temp - 1]);
        return sum + sum_ - (cnt_ - k) * V[temp - 1];
    }
};

void solve() {
    int N, K, L;
    cin >> N;
    A.resize(N); B.resize(N);
    for(int i = 0; i < N; i++) {
        cin >> A[i];
    }
    for(int i = 0; i < N; i++) {
        cin >> B[i];
    }
    cin >> K >> L;
    cute loli;
    loli.init(B);
    for(int i = 0; i < K; i++) {
        loli.insert(A[i], B[i]);
    } 
    int ans = loli.cal(L);
    for(int i = K - 1, j = N - 1; i >= 0; i--, j--) {
        loli.erase(A[i], B[i]);
        loli.insert(A[j], B[j]);
        ans = max(ans, loli.cal(L));
    }
    cout << ans << '\n';
}

signed main() {
    IOS();
    int t = 1; // cin >> t;
    for (int i=1;i<=t;++i) solve();
    return 0;
}