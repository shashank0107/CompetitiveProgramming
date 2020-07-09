/*
    Author : manu_sy
    Idea : Using dynamic hull (to insert lines and query of max) :
          - Sort machines with start dates
          - Now each machines earning can be represented using line : k * x + m
            - mi = -pi + ri + gi * di + max(mj + gj * (di - 1))
            - ki = gi
          - Keep inserting lines in hull and querying for maximum
*/
#include "bits/stdc++.h"
using namespace std;
 
/** Template Begins **/
#define int ll
typedef long long        ll;
typedef pair<int,int>    PII;
 
#define IOS         ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl        '\n'
#define pb          push_back
#define F           first
#define S           second
#define mp          make_pair
#define all(a)      (a).begin(), (a).end()
#define FOR(i,a,b)  for(int i=a;i<=b;i++)
#define LP(i,n)     for(int i=0;i< n;i++)
 
/* Debug */
 
template<class L, class R> ostream &operator<<(ostream &os, pair<L,R> P) {
  return os << "(" << P.F << "," << P.S << ")";
} 
 
template<class T> ostream &operator<<(ostream& os, vector<T> V) {
  os << "["; for (auto vv : V) os << vv << ","; return os << "]";
}
 
template<class TH> void _dbg(const char *sdbg, TH h){ cerr << sdbg << '=' << h << endl; }
 
template<class TH, class... TA> void _dbg(const char *sdbg, TH h, TA... a) {
  while(*sdbg!=',') cerr << *sdbg++;
  cerr<<'='<<h<<','; _dbg(sdbg+1, a...);
}
 
#ifdef LOCAL
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif
 
/* Debug Ends */
 
const int N = 5e6+7;
 
/** Template Ends **/
bool Q;
struct Line {
    mutable ll k, m, p;
    bool operator<(const Line& o) const {
        return Q ? p < o.p : k < o.k;
    }
};
 
struct LineContainer : multiset<Line> {
    // (for doubles, use inf = 1/.0, div(a,b) = a/b)
    const ll inf = LLONG_MAX;
    ll div(ll a, ll b) { // floored division
        return a / b - ((a ^ b) < 0 && a % b); }
    bool isect(iterator x, iterator y) {
        if (y == end()) { x->p = inf; return false; }
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ll k, ll m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ll query(ll x) {
        assert(!empty());
        Q = 1; auto l = *lower_bound({0,0,x}); Q = 0;
        return l.k * x + l.m;
    }
};

ll n, c, d;
struct machine {
    ll d, p, r, g;
    bool operator<(const machine& o) const {
        return d < o.d;
    }
};

signed main() {
 
    IOS;
    int tc = 1;
    while (cin >> n >> c >> d) {
        if (n == 0) break;
        LineContainer lc;
        lc.add(0, c);
        vector<machine> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i].d >> v[i].p >> v[i].r >> v[i].g;
        }
        sort(all(v));
        for (auto mac: v) {
            ll tot = lc.query(mac.d - 1);
            if (tot < mac.p) continue;
            ll m = -mac.p + mac.r + tot - mac.g * mac.d;
            lc.add(mac.g, m);
        }
        cout << "Case " << tc++ << ": " << lc.query(d) << endl;
    }
    return 0;
}
