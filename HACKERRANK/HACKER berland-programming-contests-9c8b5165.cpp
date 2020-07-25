/*
    Author : manu_sy
    Idea : Similar to editorial https://www.hackerearth.com/problem/algorithm/berland-programming-contests-9c8b5165/editorial/
*/
#include "bits/stdc++.h"
using namespace std;
 
/** Template Begins **/
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
 
#ifdef LOCALi
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif
 
/* Debug Ends */
 
const int N = 5e3+7;
const int B = 10;
const int MB = (1 << B);
const int hell = 1e9+7;

/** Template Ends **/
int n, m;
vector<int> g[N];
vector<int> dp[N];
int ans[B+2];

void pre() {
	LP(i,n + 1) g[i].clear(), dp[i].clear(), dp[i].assign(MB+5, 0);
	memset(ans, 0, sizeof ans);
}
int add(ll a, ll b) {
	return (a + b) % hell;
}
int mul(ll a, ll b) {
	return ((a % hell) * (b % hell)) % hell;
}
int sub(ll a, ll b) {
	return (a - b + hell) % hell;
}
vector<int> merge(vector<int> a, vector<int> b) {
	vector<int> ia = a;
	vector<int> res(a.size());
	debug(a, b);
	for (int i = 0; i < B; i++) {
		for (int msk = MB - 1; msk >= 0; msk--) {
			if (!((msk >> i) & 1)) {
				a[msk] = add(a[msk], a[msk ^ (1 << i)]);
				b[msk] = add(b[msk], b[msk ^ (1 << i)]);
			}
		}
	}
	debug(a, b);
	for (int msk = MB - 1; msk >= 0; msk--) {
		res[msk] = mul(a[msk], b[msk]);
	}
	debug(res);
	for (int i = 0; i < B; i++) {
		for (int msk = MB - 1; msk >= 0; msk--) {
			if (!((msk >> i) & 1)) {
				res[msk] = sub(res[msk], res[msk ^ (1 << i)]);
			}
		}
	}
	LP(i,MB) res[i] = add(res[i], ia[i]);
	debug(res);
	return res;
}
void dfs(int v, int p) {
	debug(v, p);
	for (auto c : g[v]) if (c != p) {
		dfs(c, v);
		debug(v, dp[v], dp[c]);
		dp[v] = merge(dp[v], dp[c]);
	}
}

signed main() {
 
    IOS;
    int t;	cin >> t;
    while (t--) {
    	cin >> n >> m;
    	pre();
    	LP(i,n-1) {
    		int a, b;	cin >> a >> b;
    		g[a].pb(b);
    		g[b].pb(a);
    	}
    	FOR(i,1,n) {
    		int msk = 0;
    		LP(j,m) {
    			int x;	cin >> x;
    			if (x)
    				msk |= (1 << j);
    		}
    		dp[i][msk] = 1;
    	}
    	dfs(1, 0);
    	FOR(i,1,n) {
    		debug(i, dp[i]);
    		LP(msk,MB) {
    			int k = __builtin_popcount(msk);
    			ans[k] = add(ans[k], dp[i][msk]);
    		}
    	}
    	LP(i,m+1) {
    		if (i) cout << " ";
    		cout << ans[i];
    	} cout << endl;
    }

    return 0;
}
