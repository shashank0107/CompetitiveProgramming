/*
    Author : manu_sy
    Idea : Sort with decreasing yi :
          - dp[i] : profit till ith (inclusive)
          - dp[i] = max(dp[j] + (x[i] - x[j]) * y[i]) - a[i]
          - dp[i] = max(dp[j] - x[j] * y[i]) + x[i] * y[i] - a[i]
          which can be easily solved using dp_convex_hull
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
 
signed main() {
 
    IOS;
    int n;  cin >> n;
    using piii = pair<PII, int>;
    vector<piii> v(n);
    LP(i,n) cin >> v[i].F.F >> v[i].F.S >> v[i].S;
    sort(all(v), [&] (const piii& a, const piii& b) {
        return a.F.S > b.F.S;
    });
    int ans = v[0].F.F * v[0].F.S - v[0].S;
    LineContainer lc;
    lc.add(0, 0);
    lc.add(-v[0].F.F, ans);
    FOR(i,1,n - 1) {
        int cur = lc.query(v[i].F.S) + v[i].F.F * v[i].F.S - v[i].S;
        ans = max(ans, cur);
        lc.add(-v[i].F.F, cur);
    }
    cout << ans << endl;

    return 0;
}
