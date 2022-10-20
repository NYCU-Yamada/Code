#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define double __float80
using pii = pair<int, int>;
using pdd = pair<double, double>;
template <typename T> using MaxHeap = std::priority_queue<T>;
template <typename T> using MinHeap = std::priority_queue<T, vector<T>, greater<T>>;

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
    fprintf(stderr, "\u001b[33m"), \
    fprintf(stderr, "At [%s], line %d: (%s) = ", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), \
    fprintf(stderr, "\u001b[0m")
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else 
#define IOS() ios_base::sync_with_stdio(), cin.tie()
#define debug(...) void()
#define endl "\n"
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

pdd operator-(const pdd &a, const pdd &b) {
    return pdd(a.X - b.X, a.Y - b.Y);
}
pdd operator+(const pdd &a, const pdd &b) {
    return pdd(a.X + b.X, a.Y + b.Y);
}
pdd operator*(const pdd &a, const double &b) {
    return pdd(a.X * b, a.Y * b);
}
pdd operator/(const pdd &a, const double &b) {
    return pdd(a.X / b, a.Y / b);
}
double dot(const pdd &a, const pdd &b) {
    return a.X * b.X + a.Y * b.Y;
}
double cross(const pdd &a, const pdd &b) {
    return a.X * b.Y - a.Y * b.X;
}
double abs2(const pdd &a) {
    return dot(a, a);
}
double abs(const pdd &a) {
    return sqrtl(abs2(a));
}

struct Cir {
    pdd O; double R;
};

const double eps = 1e-9;

bool CCinter(Cir &a, Cir &b, pdd &p1, pdd &p2) {
    pdd o1 = a.O, o2 = b.O;
    double r1 = a.R, r2 = b.R, d2 = abs2(o1 - o2), d = sqrtl(d2);
    if (d < max(r1, r2) - min(r1, r2) - eps or d > r1 + r2 + eps) return 0;
    pdd u = (o1 + o2) * 0.5 + (o1 - o2) * ((r2 * r2 - r1 * r1) / (2 * d2));
    double A = sqrtl((r1 + r2 + d) * (r1 - r2 + d) * (r1 + r2 - d) * (-r1 + r2 + d));
    pdd v = pdd(o1.Y - o2.Y, -o1.X + o2.X) * A / (2 * d2);
    p1 = u + v, p2 = u - v;
    return 1;
}

bool PinC(Cir &a, pdd &p1) {
    return sqrtl(abs2(p1 - a.O)) <= a.R + eps;
}

vector<pdd> circleLine(Cir C, pdd a, pdd b) {
    pdd c = C.O; double r = C.R;
    pdd p = a + (b - a) * dot(c - a, b - a) / abs2(b - a);
    double s = cross(b - a, c - a), h2 = r * r - s * s / abs2(b - a);
    if(h2 < 0) return {};
    if(h2 == 0) return {p, p};
    pdd h = (b - a) / abs(b - a) * sqrtl(h2);
    return {p - h, p + h};
}

vector<Cir> c;
vector<pdd> pts;

bool chk(pdd p1, pdd p2) {
    // debug(p1.X, p1.Y, p2.X, p2.Y);
    vector<pdd> itv;
    for (Cir cir : c) {
        auto vc = circleLine(cir, p1, p2);
        if (!SZ(vc)) continue;
        double l = abs(vc[0] - p1) / abs(p2 - p1);
        double r = abs(vc[1] - p1) / abs(p2 - p1);
        if(l > r) swap(l, r);
        for (auto cir : vc)
        if (p2 == {1, 3}) debug(cir.O.X, cir.O.Y, cir.R, l, r);
        itv.eb(l, r);
    }
    sort(ALL(itv));
    
    double right = 0.0;
    for (auto [L, R] : itv) {
        if (right > L + eps) return false;
        chmax(right, R);
        if (right >= 1) return true;
    }
    return right > 1 - eps;
}

void solve() {
    int n;
    double x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2 >> n;
    c.resize(n);
    
    for(int i = 0; i < n; i++) {
        double x, y, r;
        cin >> x >> y >> r;
        c[i].O = pdd(x, y);
        c[i].R = r;
    }
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            // debug(i, j);
            pdd p1, p2;
            if(CCinter(c[i], c[j], p1, p2)) pts.eb(p1), pts.eb(p2);
        }
    }
    sort(ALL(pts));
    pts.erase(unique(ALL(pts)), end(pts));
    pts.eb(pdd(x1, y1));
    pts.eb(pdd(x2, y2));
    
    int m = SZ(pts);
    vector<vector<pair<int, double>>> G(m);
    for(int i = 0; i < m; i++) {
        for(int j = i+1; j < m; j++) {
            if(chk(pts[i], pts[j])) {
                debug(pts[i].X, pts[i].Y, pts[j].X, pts[j].Y);
                double d = abs(pts[i] - pts[j]);
                G[i].eb(j, d), G[j].eb(i, d);
            }
        }
    } 
    
    MinHeap<pair<double, int>> pq;
    vector<double> dis(m, 1e14);
    vector<bool> vis(m, false);
    pq.ee(dis[m-2] = 0, m-2);
    while(SZ(pq)) {
        auto [d, x] = pq.top(); pq.pop();
        if(vis[x]) continue; else vis[x] = true;
        for(auto e : G[x]) {
            if(chmin(dis[e.X], dis[x] + e.Y)) pq.ee(dis[e.X], e.X);
        }
    }
    if (!vis[m-1]) cout << "impossible" << "\n";
    else cout << fixed << setprecision(20) << dis[m-1] << "\n";
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