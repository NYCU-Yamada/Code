#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define double __float80
using pii = pair<int, int>;
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

pii operator-(const pii &a, const pii &b) {return pii(a.X - b.X, a.Y - b.Y);}
pii operator+(const pii &a, const pii &b) {return pii(a.X + b.X, a.Y + b.Y);}
pii operator*(const pii &a, const int &b) {return pii(a.X * b,   a.Y * b);}
pii operator/(const pii &a, const int &b) {return pii(a.X / b,   a.Y / b);}
int   dot(const pii &a, const pii &b) {return a.X * b.X + a.Y * b.Y;}
int cross(const pii &a, const pii &b) {return a.X * b.Y - a.Y * b.X;}
int  sign(const int &a) {return a == 0 ? 0 : (a > 0 ? 1 : -1);}
bool  col(const pii &p1, const pii &p2, const pii &p3) {return sign(cross(p1-p3, p2-p3)) == 0;}
bool  btw(const pii &p1, const pii &p2, const pii &p3) {if (!col(p1, p2, p3)) return 0; else return sign(dot(p1-p3, p2-p3)) <= 0;}
int   ori(const pii &p1, const pii &p2, const pii &p3) {return sign(cross(p2-p1, p3-p1));}

bool seg_intersect(const pii &p1, const pii &p2, const pii &p3, const pii &p4) {
    // debug(p1.X, p1.Y, p2.X, p2.Y);
    // debug(p3.X, p3.Y, p4.X, p4.Y);
    int a123 = ori(p1, p2, p3);
    int a124 = ori(p1, p2, p4);
    int a341 = ori(p3, p4, p1);
    int a342 = ori(p3, p4, p2);
    if (a123 == 0 and a124 == 0) {
        return btw(p1, p2, p3) or btw(p1, p2, p4) or btw(p3, p4, p1) or btw(p3, p4, p2);
    }
    return a123 * a124 <= 0 and a341 * a342 <= 0;
}

vector<int> p;

int R(int x) {return x ^ p[x] ? p[x] = R(p[x]) : x;}
int U(int x, int y) {x = R(x), y = R(y); return x ^ y ? p[x] = y, 1 : 0;}

void solve() {
    int N; cin >> N;
    p.resize(N), iota(ALL(p), 0);
    
    vector<pair<pii, pii>> lines;
    for (int i = 0, x1, y1, x2, y2; i < N; ++i) {
        cin >> x1 >> y1 >> x2 >> y2;
        lines.eb(pii(x1, y1), pii(x2, y2));
    }
    
    int c_cc = N, c_it = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N; ++j) {
            // debug(i, j);
            if (seg_intersect(lines[i].X, lines[i].Y, lines[j].X, lines[j].Y)) {
                ++c_it;
                c_cc -= U(i, j);
            }
        }
    }
    cout << c_cc + c_it - N << "\n";
    // debug(c_cc, c_it);
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