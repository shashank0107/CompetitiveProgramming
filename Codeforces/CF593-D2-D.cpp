/*
    Author : manu_sy
    
    Idea : Same as editorial
*/
#include <bits/stdc++.h>
using namespace std;

/** Template Begins **/
#define int ll
typedef long long        ll;
typedef pair<int,ll>    PII;

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
template<class TH> void _dbg(const char *sdbg, TH h){ cerr<<sdbg<<'='<<h<<endl; }
template<class TH, class... TA> void _dbg(const char *sdbg, TH h, TA... a) {
  while(*sdbg!=',')cerr<<*sdbg++;
  cerr<<'='<<h<<','; _dbg(sdbg+1, a...);
}
#ifdef LOCAL
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif
/* Debug Ends */

const int N = 2e5+7;

/** Template Ends **/
int n, m, par[N], L[N], up[N][22], l;
ll edge_up[N];
vector<PII> g[N];
PII ed[N];

/* DSU */
int parent[N], size[N];
void make_set(int u) {
	parent[u] = u;
	size[u] = 1;
}
int find_set(int v) {
	if (parent[v] == v)	return v;
	return parent[v] = find_set(parent[v]);
}
void union_sets(int u, int v) {
	assert(u = parent[u]);
	v = find_set(v);
	parent[u] = v;
}
/* DSU ENDS */
void dfs(int v, int p, int lvl)
{
	par[v] = p;
	if (p) up[v][0] = p;
	L[v] = lvl;

	for (int i = 1; i <= l; i++)
		if (up[v][i-1] != -1)
			up[v][i] = up[up[v][i-1]][i-1];

	for (auto nbe : g[v]) 
	{
		int u = nbe.F;	ll wt = nbe.S;
		if (u == p)	continue;

		if (wt == 1)	union_sets(u, v);
		else edge_up[u] = wt;

		dfs(u, v, lvl+1);
	}
}
int walk(int u, int k) 
{
	for (int i = l; i >= 0; i--)
		if ((k>>i)&1) {
			u = up[u][i];
		}
	return u;
}
int lca(int u, int v) 
{
	if (L[u] < L[v])	swap(u, v);
	u = walk(u, L[u] - L[v]);
	if (u == v)	return u;

	for (int i = l; i >= 0; i--)
		if (up[u][i] != up[v][i])
			u = up[u][i], v = up[v][i];

	return up[v][0];
}

ll solve(int a, int b, ll y)
{
	int lc = lca(a, b);
	vector<ll> upa;

	a = find_set(a);
	while (a != lc && L[lc] <= L[par[a]]) 
	{
		upa.pb(edge_up[a]);
		a = par[a];
		a = find_set(a);

		if (upa.size() > 62)	return 0;
	}	

	b = find_set(b);
	while (b != lc && L[lc] <= L[par[b]])
	{
		upa.pb(edge_up[b]);
		b = par[b];
		b = find_set(b);

		if (upa.size() > 62)	return 0;
	}

	for (auto i : upa)	y /= i;
	return y;
}

signed main() {

    IOS;
    cin >> n >> m;
    for (int i = 0; i < n-1; i++) 
    {
    	int a, b;	ll c;
    	cin >> a >> b >> c;

    	g[a].pb(mp(b, c));
    	g[b].pb(mp(a, c));
    	ed[i+1] = mp(a, b);
    }
    for (int i = 1; i <= n; i++) make_set(i);

    l = ceil(log2(n));
    memset(up, -1, sizeof up);
    dfs(1, 0, 0);

    for (int i = 0; i < m; i++)
    {
    	int t;	cin >> t;
    	if (t == 1)
    	{
    		int a, b;	ll y;
    		cin >> a >> b >> y;
    		cout << solve(a, b, y) << endl;
    	}
    	else 
    	{
    		int id;	ll val;
    		cin >> id >> val;

    		int u = ed[id].F;
    		int v = ed[id].S;
    		if (L[u] < L[v])	swap(u, v);

    		if (val == 1)	union_sets(u, v);
    		edge_up[u] = val;
    	}
    }

    return 0;
}
