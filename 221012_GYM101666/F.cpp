#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define double __float80

template <typename T> using MaxHeap = priority_queue<T>;

#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)

#ifdef local
#define IOS() void()
#else 
#define IOS() ios_base::sync_with_stdio(), cin.tie()
#endif

void solve() {
    int N; cin >> N;
    
    int sum = 0, sc_a = 0;
    vector<int> A(N);
    for (int &x : A) cin >> x, sum += x;
    sort(RALL(A));
    
    for (int i = 0; i < N; i += 2) sc_a += A[i];
    cout << sc_a << " " << sum - sc_a << "\n";
}

signed main() {
    IOS();
    int _ = 1;
    // cin >> _;
    for (int i = 1; i <= _; ++i) {
        solve();
    }
    return 0;
}