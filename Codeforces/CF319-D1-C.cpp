/*
    Author : manu_sy
    Idea : Observe that it is optimal to cut a subsequence of trees of increasing i starting at 1 and ending at n
           and then cut the remaining using the recharge cost b[n] (since it min)
          - We'll solve the problem backwards (So we reverse the a[] and b[])
          - We take nth always
          - dp[i] : cost to cut till ith (excluding i)
            dp[i] = min(dp[j] + a[j] * b[i] + (s[i - 1] - s[j]) * b[n]) {j < i}
                  = min(dp[j] - s[j] * b[n] + a[j] * b[i]) {j < i} + s[i - 1] * b[n]
                  = min(m[j] + a[j] * b[i]) + s[i - 1] * b[n]
                  
           - m[i] = min(m[j] + a[j] * b[i]) + s[i - 1] * b[n] - s[i] * b[n]
           
           which can be solved using dp convex hull
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
 
const int N = 1e5+7;
 
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
int n;
int a[N];
int b[N];
int s[N];

signed main() {
 
    IOS;
    cin >> n;
    for (int i = n - 1; i >= 0; i--)    cin >> a[i];
    for (int i = n - 1; i >= 0; i--)    cin >> b[i];
    s[0] = a[0];
    for (int i = 1; i < n; i++) s[i] = a[i] + s[i - 1];
    LineContainer lc;
    lc.add(-a[0], 0);
    for (int i = 1; i < n; i++) {
        int mi = -lc.query(b[i]) + s[i - 1] * b[0] - s[i] * b[n];
        lc.add(-a[i], -mi);
        if (i == n - 1) {
            cout << mi << endl;
        }
    }
    return 0;
}
