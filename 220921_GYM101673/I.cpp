#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define SZ(a) (int)((a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)
#define ee emplace
#define eb emplace_back
#define ef emplace_front
#define pb pop_back
#define pf pop_front

#ifdef local
#define debug(...) \
    fprintf(stderr, "LINE %d: (%s) = ", __LINE__, #__VA_ARGS__);\
    _do(__VA_ARGS__);
template<typename T> void _do(T &&_x){cerr << _x << endl;}
template<typename T, typename ...S> void _do(T &&_x, S &&..._t){cerr << _x << ", "; _do(_t...);}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0);
#define debug(...) void()
#endif

template<typename T>
ostream operator << (ostream &os, vector<T> &vec) {
    os << "[";
    for (int i = 0; i < SZ(vec); ++i) {
        if (i) os << ", ";
        os << vec[i];
    }
    os << "]";
    return os;
}

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

int ans = 1000;

void calc_3(string S, auto A, auto B, auto C, auto D, int base) {
    deque<int> num;
    deque<char> ops;
    int flag = 0, x, y, z;
    for (char c : S) {
        if (c == ' ') continue;
        if(isalpha(c)) {
            switch(c) {
                case 'A': 
                    num.eb(A);
                    break;
                case 'B':
                    num.eb(B);
                    break;
                case 'C':
                    num.eb(C);
                    break;
                case 'D':
                    num.eb(D);
                    break;
            }
            if(ops.empty()) {}
            else if(ops.back() == '*') {
                x = num.back(); num.pb();
                y = num.back(); num.pb();
                z = y * x;
                num.eb(z);
                ops.pb();
            }
            else if(ops.back() == '/') {
                x = num.back(); num.pb();
                y = num.back(); num.pb();
                if (x == 0 or y % x != 0) flag = 1, z = 1;
                else z = y / x;
                num.eb(z);
                ops.pb();
            }
        }
        else if(c == '+' || c == '-' || c == '*' || c == '/') {
            ops.eb(c);
        }
        else if(c == ')') {
            deque<int> tmp_num;
            deque<char> tmp_ops;
            while(ops.back() != '(') {
                x = num.back(); num.pb();
                char tmp = ops.back(); ops.pb();
                tmp_num.eb(x); tmp_ops.eb(tmp);
            }
            x = num.back(); num.pb();
            tmp_num.eb(x);    
            ops.pb();
            while(SZ(tmp_num) > 1) {
                x = tmp_num.back(); tmp_num.pb();
                y = tmp_num.back(); tmp_num.pb();
                char d = tmp_ops.back(); tmp_ops.pb();
                switch(d){ 
                    case '+':
                        z = y + x;
                        tmp_num.eb(z);
                        break;
                    case '-':
                        z = x - y;
                        tmp_num.eb(z);
                        break;
                    case '*':
                        z = y * x;
                        tmp_num.eb(z);
                        break;
                    case '/':
                        if(y == 0 or x % y != 0) flag = 1, z = 1;
                        else z = x / y;
                        tmp_num.eb(z);
                        break;
                }
            }
            num.eb(tmp_num.back());
            if(ops.empty()) {}
            else if(ops.back() == '*') {
                x = num.back(); num.pb();
                y = num.back(); num.pb();
                z = y * x;
                num.eb(z);
                ops.pb();
            }
            else if(ops.back() == '/') {
                x = num.back(); num.pb();
                y = num.back(); num.pb();
                if (x == 0 or y % x != 0) flag = 1, z = 1;
                else z = y / x;
                num.eb(z);
                ops.pb();
            }
        }
        else ops.eb(c);
        // if (c == ' ') continue;
        // if (c == '+' or c == '-' or c == '*' or c == '/') ops.ef(c, dep);
        // if (c == 'A') num.ef(A, dep);
        // if (c == 'B') num.ef(B, dep);
        // if (c == 'C') num.ef(C, dep);
        // if (c == 'D') num.ef(D, dep);
        // if (c == '(') ++dep;
        // if (c == ')') --dep;
    }

    while(SZ(num) > 1) {
        x = num.front(); num.pf();
        y = num.front(); num.pf();
        char d = ops.front(); ops.pf();
        switch(d){ 
            case '+': {
                z = y + x;
                num.ef(z);
                break;
            }
            case '-': {
                z = x - y;
                num.ef(z);
                break;
            }
            case '*': {
                z = y * x;
                num.ef(z);
                break;
            }
            case '/': {
                if(y == 0 or x % y != 0) flag = 1, z = 1;
                else z = x / y;
                num.ef(z);
                break;
            }
        }
    }
    
    if(!flag && num.back() == 24) {
        chmin(ans, base);
        debug(S, A, B, C, D);
    }
}

void calc_2(string S, auto A, auto B, auto C, auto D, int base) {
    string tmp;
    
    tmp = S;
    calc_3(tmp, A, B, C, D, base);
    
    tmp = S, tmp[1] = '(', tmp[9] = ')';
    calc_3(tmp, A, B, C, D, base + 1);
    tmp = S, tmp[1] = '(', tmp[15] = ')';
    calc_3(tmp, A, B, C, D, base + 1);
    tmp = S, tmp[7] = '(', tmp[15] = ')';
    calc_3(tmp, A, B, C, D, base + 1);
    tmp = S, tmp[7] = '(', tmp[21] = ')';
    calc_3(tmp, A, B, C, D, base + 1);
    tmp = S, tmp[13] = '(', tmp[21] = ')';
    calc_3(tmp, A, B, C, D, base + 1);
    
    tmp = S, tmp[1] = tmp[13] = '(', tmp[9] = tmp[21] = ')';
    calc_3(tmp, A, B, C, D, base + 2);
    tmp = S, tmp[0] = tmp[1] = '(', tmp[9] = tmp[16] = ')';
    calc_3(tmp, A, B, C, D, base + 2);
    tmp = S, tmp[0] = tmp[7] = '(', tmp[15] = tmp[16] = ')';
    calc_3(tmp, A, B, C, D, base + 2);
    tmp = S, tmp[6] = tmp[7] = '(', tmp[15] = tmp[22] = ')';
    calc_3(tmp, A, B, C, D, base + 2);
    tmp = S, tmp[6] = tmp[13] = '(', tmp[21] = tmp[22] = ')';
    calc_3(tmp, A, B, C, D, base + 2);
}

void calc_1(auto A, auto B, auto C, auto D, int base) {
    const char ops[4] = {'+', '-', '*', '/'};
    string tmp = "  A     B     C     D  ";
    for (char x1 : ops) for (char x2 : ops) for (char x3 : ops) {
        tmp[5] = x1, tmp[11] = x2, tmp[17] = x3;
        calc_2(tmp, A, B, C, D, base);
    }
}

void solve() {
    int A, B, C, D; cin >> A >> B >> C >> D;
    
    calc_1(A, B, C, D, 0);
    calc_1(A, B, D, C, 2);
    calc_1(A, C, B, D, 2);
    calc_1(A, C, D, B, 4);
    calc_1(A, D, B, C, 4);
    calc_1(A, D, C, B, 6);
    
    calc_1(B, A, C, D, 2);
    calc_1(B, A, D, C, 4);
    calc_1(B, C, A, D, 4);
    calc_1(B, C, D, A, 6);
    calc_1(B, D, A, C, 6);
    calc_1(B, D, C, A, 8);
    
    calc_1(C, A, B, D, 4);
    calc_1(C, A, D, B, 6);
    calc_1(C, B, A, D, 6);
    calc_1(C, B, D, A, 8);
    calc_1(C, D, A, B, 8);
    calc_1(C, D, B, A, 10);
    
    calc_1(D, A, B, C, 6);
    calc_1(D, A, C, B, 8);
    calc_1(D, B, A, C, 8);
    calc_1(D, B, C, A, 10);
    calc_1(D, C, A, B, 10);
    calc_1(D, C, B, A, 12);
    
    if (ans <= 20) cout << ans << "\n";
    else           cout << "impossible" << "\n";
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
