#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
using pdd = pair<double, double>;
template <typename T> using MinHeap = std::priority_queue<T, vector<T>, greater<T>>;
template <typename T> using MaxHeap = std::priority_queue<T>;

#define X first
#define Y second
#define ee emplace
#define eb emplace_back
#define ef emplace_front
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())

#ifdef local
#define IOS() void()
#define debug(...) \
    cerr << "\u001b[33m",\
    cerr << "At func [" << __FUNCTION__ << "], line " << __LINE__ << ", ",\
    cerr << "(" << #__VA_ARGS__ << ") = ", _do(__VA_ARGS__),\
    cerr << "\u001b[0m"
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define IOS() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

pdd operator-(const pdd &a, const pdd &b) {
    return pdd(a.X - b.X, a.Y - b.Y);
}
pdd operator*(const pdd &a, const double &b) {
    return pdd(a.X * b, a.Y * b);
}
pdd operator/(const pdd &a, const double &b) {
    return pdd(a.X / b, a.Y / b);
}
double cross(const pdd &a, const pdd&b) {
    return a.X * b.Y - a.Y * b.X;
}
pdd intersect(const pdd &p1, const pdd &p2, const pdd &p3, const pdd &p4) {
    double a123 = cross(p2 - p1, p3 - p1);
    double a124 = cross(p2 - p1, p4 - p1);
    return (p4 * a123 - p3 * a124) / (a123 - a124);
}

const int maxc = 1e6 + 5;
const int mod = 1e9 + 7;

int power(int x, int n) {
    int ret = 1;
    while(n) {
        if(n & 1) {
            ret = ret * x % mod;
        }
        n >>= 1;
        x = x * x % mod;
    }
    return ret;
}

int inv(int x) {
    return power(x, mod - 2);
}

vector<int> P(maxc), invP(maxc);

int C(int n, int m) {
    if(n < 0 || m > n || m < 0) return 0; 
    return P[n] * (invP[m] * invP[n - m] % mod) % mod;
}

void init_P() {
    P[0] = 1;
    for (int i = 1; i <= maxc-1; ++i) P[i] = P[i-1] * i % mod;
    invP[maxc-1] = inv(P[maxc-1]);
    for (int i = maxc-1; i >= 1; --i) invP[i-1] = invP[i] * i % mod;
}

pdd Pt[3];

pdd hit(double y, pdd p3, pdd p4) {
    if(p3.Y == p4.Y) {
        if(p3.Y == y) {
            if(p3.X > p4.X) swap(p3, p4);
            return {p3.X, p4.X};
        }
        return {94878763, 94878763};
    }
    pdd p1(1e6 + 5, y), p2(-1e6 - 5, y);
    if(p3.Y > p4.Y) swap(p3, p4);
    if(p3.Y <= y && y <= p4.Y) {
        pdd temp = intersect(p1, p2, p3, p4);
        return {temp.X, temp.X};
    }
    return {94878763, 94878763};
}

void solve() {
    for(int i = 0; i < 3; i++) {
        cin >> Pt[i].X >> Pt[i].Y; 
    }
    sort(Pt, Pt + 3, [](pdd a, pdd b){
        return a.Y < b.Y;
    });
    int curL = 1, curR = 0, curS = 0, ans = 0;
    for(double y = max((double)0.0, Pt[0].Y); y <= Pt[2].Y; y += 1.0) {
        double l = 1e6 + 5, r = -1e6 - 5;
        for(int i = 0; i < 3; i++) {
            pdd temp = hit(y, Pt[i], Pt[(i + 1) % 3]);
            if(temp.X != 94878763) {
                l = min(l, temp.X);
                r = max(r, temp.Y);
            }
        }
        // debug(y, l, r);
        double L = (l + y) / 2, R = (r + y) / 2;
        L = max((double)0.0, L); R = min(y, R);
        L = ceil(L), R = floor(R);
        // debug(y, L, R);
        if(curR < curL) {
            curS = 0;
            for(int i = L; i <= R; i++) {
                curS = (curS + C(y, i)) % mod;
            }
            ans = (ans + curS) % mod;
            curL = L; curR = R;
        }
        else {
            while(curL > L) {
                curS = (curS + C(y - 1, --curL)) % mod;
            }
            while(curR < R) {
                curS = (curS + C(y - 1, ++curR)) % mod; 
            }
            
            while(curL < L) {
                curS = (curS - C(y - 1, curL++) + mod) % mod;
            }
            while(curR > R) {
                curS = (curS - C(y - 1, curR--) + mod) % mod;
            }
            
            curS = (2LL * curS) - C(y - 1, R) + mod + C(y - 1, L - 1);
            curS %= mod;
            ans = (curS + ans) % mod;
        }
    }
    cout << ans << '\n';
}

int32_t main() {
    IOS();
    init_P();
    
    int t = 1;
    cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
