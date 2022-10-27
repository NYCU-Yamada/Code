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

const int maxc = 1E5 + 5;

vector<vector<int>> pfact;
vector<vector<int>> tag, op_id;

void solve() {
    int N, Q; cin >> N >> Q;
    
    tag.assign(maxc, vector<int>(1, 0));
    op_id.assign(maxc, vector<int>(1, -1));
    
    vector<int> A(N+1);
    for (int i = 1; i <= N; ++i) cin >> A[i];
    
    for (int qid = 1, c, d; qid <= Q; ++qid) {
        cin >> c >> d;
        int psz = SZ(pfact[c]);
        vector<int> val(1 << psz, 1);
        for (int mask = 1; mask < (1<<psz); ++mask) {
            int lowbit = mask & -mask, bitcnt = __builtin_popcount(mask);
            val[mask] = val[mask ^ lowbit] * pfact[c][__lg(lowbit)];
            tag[val[mask]].eb((bitcnt & 1 ? d : -d));
            op_id[val[mask]].eb(qid);
        }
    }
    
    for (int i = 0; i < maxc; ++i) partial_sum(ALL(tag[i]), begin(tag[i]));
    
    auto query = [&](int pid, int thres) -> int {
        int psz = SZ(pfact[pid]), ans = 0;
        vector<int> val(1 << psz, 1);
        for (int mask = 1; mask < (1<<psz); ++mask) {
            int lowbit = mask & -mask;
            val[mask] = val[mask ^ lowbit] * pfact[pid][__lg(lowbit)];
            
            int pos = prev(upper_bound(ALL(op_id[val[mask]]), thres)) - begin(op_id[val[mask]]);
            ans += tag[val[mask]][pos];
        }
        return ans;
    };
    
    for (int pid = 1; pid <= N; ++pid) {
        int lo = 1, hi = Q+1, mi;
        while (lo < hi) {
            mi = (lo + hi) >> 1;
            if (query(pid, mi) >= A[pid]) hi = mi;
            else                          lo = mi + 1;
        }
        cout << (lo == Q+1 ? -1 : lo) << "\n";
    }
}

void init() {
    pfact.resize(maxc);
    bitset<maxc> isprime; isprime.set();
    for (int i = 2; i < maxc; ++i) {
        if (!isprime[i]) continue;
        for (int j = i; j < maxc; j += i) isprime[j] = 0, pfact[j].eb(i);
    }
}

signed main() {
    IOS();
    init();
    int t = 1; // cin >> t;
    for (int i=1;i<=t;++i) solve();
    return 0;
}