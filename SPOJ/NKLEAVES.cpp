/*
    Author : manu_sy
    Idea : dp[i][j] - min cost of having i piles to cover whole and the ith pile is in jth position
           s[i] = w[i] + w[i + 1] + w[i + 2] + ...
           
           dp[k][i] = min(dp[k - 1][j] + j * s[i]) - i * s[i]      {j < i}
           which can be solved using convex hull trick
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
int n, k, dp[12][N], w[N];
 
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
		debug(k, m);
		k *= -1, m *= -1;
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		Q = 1; auto l = *lower_bound({0,0,x}); Q = 0;
		int ret = -(l.k * x + l.m);
		debug(x, ret);
		return ret;
	}
};
int sw[N];
int s[N];

signed main() {
 
    IOS;
    cin >> n >> k;
    FOR(i,1,n) cin >> w[i];
    for (int i = n; i >= 1; i--) {
    	sw[i] = sw[i + 1] + w[i] * i;
    	s[i] = s[i + 1] + w[i];
    }
    dp[1][1] = sw[1] - s[1];

    FOR(i,1,k - 1) {
    	LineContainer lc;
    	FOR(j,i,n-1) {
    		if (!(i == 1 && j != 1))	
    			lc.add(j, dp[i][j]);
    		dp[i + 1][j + 1] = - (j + 1) * s[j + 1] + lc.query(s[j + 1]);
    		debug(i, j, dp[i + 1][j + 1], dp[i][j]);
    	}
    }
    int ans = dp[1][1];
    if (k != 1) {
	    FOR(i,k,n) {
	    	debug(i, dp[k][i]);
	    	ans = min(ans, dp[k][i]);
	    }
	}
    cout << ans << endl;

    return 0;
}
