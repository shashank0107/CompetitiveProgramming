/*
    Author : manu_sy
	
	Idea : Similar to 
		https://github.com/BRAINOOOO/CompetitiveProgramming/blob/master/CF/CF101142-gym-G
*/
#include <bits/stdc++.h>
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
template<class TH> void _dbg(const char *sdbg, TH h){ cerr<<sdbg<<'='<<h<<endl; }
template<class TH, class... TA> void _dbg(const char *sdbg, TH h, TA... a) {
  while(*sdbg!=',')cerr<<*sdbg++;
  cerr<<'='<<h<<','; _dbg(sdbg+1, a...);
}
#ifdef LOCALI
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif
/* Debug Ends */

const int N = 4e5+7;

/** Template Ends **/
int n, q, sz[N], up[N][22], l, L[N], H[N], nn, in[N], out[N], tree[4*N], timer;
vector<int> g[N];
set<int> taken;
int tot, gangsters;

void dfs(int v, int p, int lvl, int hd)
{
	in[v] = ++timer;
	L[v] = lvl;
	H[v] = hd;

	if (g[v].empty())	sz[v] = 1;

	for (int i = 1; i <= l; i++)
		if (up[v][i-1] != -1)
			up[v][i] = up[up[v][i-1]][i-1];

	for (auto ch : g[v])
	{
		dfs(ch, p, lvl + 1, v == 1 ? ch : hd);
		sz[v] += sz[ch];
	}
	out[v] = timer;
}
int walk(int u, int k)
{
	for (int i = l; i >= 0; i--)
		if ((k>>i) & 1)	
			u = up[u][i];
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
	return up[u][0];
}
int combine(int l, int r)
{
	if (l && r)	return lca(l, r);
	if (l)	return l;
	return r;
}
void update(int s, int e, int nd, int idx, int val)
{
	if (s == e)
	{
		tree[nd] = val;
		return;
	}
	int mid = (s + e) / 2;
	if (idx <= mid)	update(s, mid, 2*nd, idx, val);
	else 			update(mid+1, e, 2*nd+1, idx, val);
	tree[nd] = combine(tree[2*nd], tree[2*nd+1]);
}
int query(int s, int e, int nd, int l, int r)
{	
	if (r < s || e < l)	return 0;
	if (l <= s && e <= r)	return tree[nd];
	int mid = (s + e) / 2;
	int p1 = query(s, mid, 2*nd, l, r);
	int p2 = query(mid+1, e, 2*nd+1, l, r);
	return combine(p1, p2);
}
void remove(int p) 
{
	if (p == 0)	return;
	assert(taken.find(p) != taken.end());
	taken.erase(p);
	tot -= sz[p];
}
void add(int p)
{
	if (p == 0)	return;
	assert(taken.find(p) == taken.end());
	taken.insert(p);
	tot += sz[p];
}
signed main() {

    freopen("gangsters.in", "r", stdin);
    freopen("gangsters.out", "w", stdout);

    cin >> n >> q;
    memset(up, -1, sizeof up);
    for (int i = 2; i <= n; i++)
    {
    	cin >> up[i][0];
    	g[up[i][0]].pb(i);
    }

    l = ceil(log2(n));
    dfs(1, 0, 0, 1);
    nn = timer+1;
 
    while (q--)
    {
    	char ch; int idx;	cin >> ch >> idx;
    	if (ch == '+')
    	{
    		int p = query(0, nn-1, 1, in[H[idx]], out[H[idx]]);
    		remove(p);

    		update(0, nn-1, 1, in[idx], idx);
    		p = query(0, nn-1, 1, in[H[idx]], out[H[idx]]);
    		add(p);

    		gangsters++;
    	}	
    	else
    	{
    		int p = query(0, nn-1, 1, in[H[idx]], out[H[idx]]);
    		remove(p);

    		update(0, nn-1, 1, in[idx], 0);
    		p = query(0, nn-1, 1, in[H[idx]], out[H[idx]]);
    		add(p);

    		gangsters--;
    	}
    	cout << taken.size() << " " << tot - gangsters << endl;
    }

    return 0;
}
