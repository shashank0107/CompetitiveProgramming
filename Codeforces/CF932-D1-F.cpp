/*
    Author : manu_sy
    Idea : Just assign dfs no. to each node. We'll calculate the answer for each node while traversing dfs.
           - Now to query answer for uth node we need to find min(dp[j] + ai * bj) for all j in subtree of u -> (in[u] + 1 <= j <= out[u])
           - So we just need to query for a minimum between a range (l, r)
           - Use sqrt decomposition to answer queries -> maintain sqrt(n) hulls and answer appropriately
           - Observe that we query for a range only after it has been populated - since we are solving subtree first and then searching in subtree
             which is represented by range [l,r]
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
const int RN = 1e3+7;
const ll INF = 1e18;

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
int rn;
int timer = -1;
ll a[N];
ll b[N];
vector<int> g[N];
ll dp[N];
ll m[N];
LineContainer lc[RN];
bool done[RN];
int in[N];
int out[N];
bool dpdone[N];

ll calc(int idx, ll x) {
	if (!done[idx]) {
		done[idx] = 1;
		FOR(i,rn*idx, min(rn*(idx + 1) - 1, n - 1)) {
			lc[idx].add(-m[i], -dp[i]);
		}
	}
	return -lc[idx].query(x);
}

void dfs(int u, int p) {
	in[u] = ++timer;
	int nbc = 0;
	for (auto nb : g[u]) {
		if (nb != p) {
			dfs(nb, u);
			nbc++;
		}
	}
	out[u] = timer;

	m[in[u]] = b[u];
	if (nbc == 0) {
		dp[in[u]] = 0;
	} else {
		int l = in[u] + 1;
		int r = out[u];
		int li = l / rn;
		int ri = r / rn;
		dp[in[u]] = INF;
		if (li == ri) {
			FOR(j, l, r) {
				dp[in[u]] = min(dp[in[u]], dp[j] + a[u] * m[j]);
			}
		} else {
			int nl = ((l + rn - 1) / rn) * rn;
			int pr = r - (r % rn);
			FOR(j, l, nl) {
				dp[in[u]] = min(dp[in[u]], dp[j] + a[u] * m[j]);
			}
			FOR(j, pr, r) {
				dp[in[u]] = min(dp[in[u]], dp[j] + a[u] * m[j]);
			}
			pr--;
			FOR(j, nl/rn, pr/rn) {
				dp[in[u]] = min(dp[in[u]], calc(j, a[u]));
			}
		}
	}
	dpdone[in[u]] = 1;
}

signed main() {
 
    IOS;
    cin >> n;
    FOR(i,1,n) cin >> a[i];
    FOR(i,1,n) cin >> b[i];
    LP(i,n-1) {
    	int u, v;	cin >> u >> v;
    	g[u].pb(v);
    	g[v].pb(u);
    }
    rn = sqrt(n);
    dfs(1, 0);
    FOR(i,1,n) cout << dp[in[i]] << " ";

    return 0;
}
