#include <bits/stdc++.h>
using namespace std;

#define int __int128
using pii = pair<int, int>;
template <typename T> using Prior = std::priority_queue<T>;
template <typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define ALL(x) begin(x), end(x)
#define SZ(x) ((int)(x).size())
#define eb emplace_back
#define ee emplace

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int MAXN = 1e5 + 5;


int n;

struct Node {
    int tag_set, tag_add, s[3], w[3];
} tr[MAXN << 2];

void pull(int idx) {
    for(int i = 0; i < 3; i++) {
        tr[idx].s[i] = tr[idx << 1].s[i] + tr[(idx << 1) | 1].s[i];
        tr[idx].w[i] = tr[idx << 1].w[i] + tr[(idx << 1) | 1].w[i];
    }
}

void push(int x) {
    if(tr[])
}

void build(int idx, int l, int r, int arr[]) {
    if(l == r) {
        tr[idx].tag_add = tr[idx].tag_set = 0;
        tr[idx].w[0] = 1;
        tr[idx].w[1] = l;
        tr[idx].w[2] = n - l + 1;
        for(int i = 0; i < 3; i++) {
            tr.s[i] = arr[i] * tr[idx].w;
        }
        return;
    }
    int mid = (l + r) >> 1;
    build(idx << 1, l, mid, arr);
    build((idx << 1) | 1, mid + 1, r, arr);
    pull(idx);
}

void solve() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    
}

int32_t main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i) {
        solve();
    }
    
    return 0;
}
