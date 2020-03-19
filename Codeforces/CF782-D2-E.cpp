/*
    Author : manu_sy
    Idea : Same as the editorial - Just have to find the euler tour and print it in k segments
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
 
#ifdef LOCAL
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif
 
/* Debug Ends */
 
const int N = 2e5+7;
 
/** Template Ends **/
int n, m, k;
vector<int> g[N];

/* DSU Begins */
int parent[N], sz[N];
void make_set(int v) {
	parent[v] = v;
	sz[v] = 1;
}
int find_set(int v) {
	if (v == parent[v])	return v;
	return parent[v] = find_set(parent[v]);
}
void union_sets(int u, int v) {
	u = find_set(u);
	v = find_set(v);
	if (u != v) {
		if (sz[u] < sz[v])	swap(u, v);
		parent[v] = u;
		sz[u] += sz[v]; 
	}
}
/* DSU Ends */
vector<int> path;
bool vis[N];

void dfs(int v) {
	vis[v] = true;
	for (auto nb: g[v]) if (!vis[nb])
	{ 
		path.pb(v);
		dfs(nb);
	}
	path.pb(v);
} 
signed main() {
 
    IOS;
    cin >> n >> m >> k;
    FOR(i,1,n) make_set(i);
    LP(i,m)
    {
    	int u, v;	cin >> u >> v;
    	if (find_set(u) != find_set(v))
    		g[u].pb(v), g[v].pb(u), union_sets(u, v);
    }
    dfs(1);
    debug(path);
    path.resize(unique(all(path)) - path.begin());
    debug(path);
    int mxlen = (2 * n + k - 1) / k;
    for (int i = 0, cur = 0; i < k; i++)
    {
    	int cnt = min(mxlen, (int)path.size() - cur);
    	vector<int> temp;
    	LP(z,cnt) 
    	{
    		if (!(temp.size() && temp.back() == path[cur]))
    			temp.pb(path[cur]);
    		cur++;
    	}
    	if (temp.size() == 0)	temp.pb(1);
    	cout << temp.size() << " ";
    	for (auto i: temp)	cout << i << " "; cout << endl;
    }
 
    return 0;
}
