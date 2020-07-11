/*
    Author : manu_sy
    Idea : Standard Case for convex hull optimization (2).
           Idea similar to editorial : https://codeforces.com/blog/entry/7785
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
 
const int N = 1e5+2;
const int P = 1e2+2;
const int INF = 1e15;

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
        return (l.k * x + l.m);
    }
};
int n;
int m;
int p;
int d[N];
int t[N];
int s[N];
int dp[P][N];

signed main() {
 
    IOS;
    cin >> n >> m >> p;
    FOR(i,2,n) {
        cin >> d[i];
        d[i] += d[i - 1];
    }
    int ini = 0;
    FOR(i,1,m) {
        int idx;    cin >> idx;
        cin >> t[i];
        t[i] -= d[idx];
    }
    sort(t + 1, t + m + 1);
    FOR(i,1,m) s[i] = s[i - 1] + t[i];
    dp[0][0] = 0;
    FOR(i,1,m) dp[0][i] = INF;
    FOR(i,0,p-1) {
        dp[i + 1][0] = 0;
        LineContainer lc;
        FOR(j,0,m-1) {
            lc.add(j, -(dp[i][j] + s[j]));
            dp[i + 1][j + 1] = -lc.query(t[j + 1]) + (j + 1) * t[j + 1] - s[j + 1];
        }
    }
    cout << dp[p][m] + ini << endl;

    return 0;
}
