/*
    Author : manu_sy
    Idea : Use ternary to find the minimal diameter.
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

const int N = 3e5+7;

/** Template Ends **/
int n, d, c[N], a[N], ed[N], ansidx, ansdia, dia;
vector<PII> g[N];

int dfs(int v, int p)
{
	int mx1 = 0, mx2 = 0;
	for (auto nb : g[v]) if (nb.F != p)
	{
		int chd = dfs(nb.F, v) + ed[nb.S];
		if (chd > mx1)	mx2 = mx1, mx1 = chd;
		else if (chd > mx2)	mx2 = chd;
	}
	dia = max(dia, mx1 + mx2);
	return mx1;
}

int f(int k) {
	LP(i,n-1) ed[i] = c[i] + a[i] * k;
	dia = -1e18;
	dfs(1, 0);
	if (dia < ansdia)
	{
		ansdia = dia;
		ansidx = k;
	}
	else if (dia == ansdia)	ansidx = min(ansidx, k);
	return dia;
}

signed main() {

    IOS;
    cin >> n >> d;
    LP(i,n-1)
    {
    	int x, y;	cin >> x >> y >> c[i] >> a[i];
    	g[x].pb(mp(y, i));
    	g[y].pb(mp(x, i));
    }
    ansdia = 1e18;
    int lo = 0, hi = d;
    while (hi - lo > 3)
    {
    	int m1 = (2 * lo + hi) / 3, m2 = (lo + 2 * hi) / 3;
    	if (f(m1) <= f(m2))	hi = m2;
    	else lo = m1;
    }
    FOR(i,lo,hi) f(i);
    cout << ansidx << endl;
    cout << ansdia << endl;

    return 0;
}
