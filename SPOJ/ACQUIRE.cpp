/*
    Author : manu_sy
    Idea : - Sort according to decreasing widths
           - Remove all irrelevent rectangles - i.e whose length is <= previous rectangle (since they can be included in previous rect)
           - Now move i from 1 till n :
             - We'll store the partial solution for this - min cost before this, current width
             - Now to find cost at ith rect : min(costj - 1 + widthj * lengthi)
             - See that the above is the case of convex hull trick. Solve using that.
             - Just have to find min here instead of max in hull -> Insert -ve values in hull and when you query => take -ve of that
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
    vector<PII> v(n);
    LP(i,n) cin >> v[i].F >> v[i].S;
    sort(all(v), greater<PII>());
    vector<PII> rect;
    for (auto i: v) {
        if (!rect.empty() && rect.back().S >= i.S)  continue;
        rect.pb(i);   
    }
    debug(rect);
    LineContainer lc;
    lc.add(-rect[0].F, 0);
    FOR(i,1,(int)rect.size() - 1) {
        ll p = -lc.query(rect[i - 1].S);
        debug(i, p);
        lc.add(-rect[i].F, -p);
    }
    cout << -lc.query(rect.back().S) << endl;

    return 0;
}
