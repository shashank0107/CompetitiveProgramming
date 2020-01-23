/*
    Author : manu_sy
    Idea : We need a euler cycle in graph beginning at node 1 
           - Need to make all vertices degree to even ( count of vertices with odd degree is always even )
           - Select 2 odd nodes and make double the edges btw their shortest path to make their degrees even
           - So just try to all combinations possible
*/
#include <bits/stdc++.h>
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

const int N = 15+3;
const int INF = 1e12;
const int MM = (1 << N) + 5;

/** Template Ends **/
int n, m, ans, d[N][N], deg[N], dp[MM];
vector<vector<PII> > adj(N + 5);
bool vis[N];
set<int> vv;

int reach(int v) {
	vv.insert(v);
	vis[v] = true;
	int ret = 1;
	for (auto nb : adj[v]) if (!vis[nb.S]) ret += reach(nb.S);
	return ret;
}
int djikstra(int st, int en, vector<vector<PII> >& adj) {
    int dist[n];
    for (int i = 0; i < n; i++) dist[i] = INF;
    dist[st] = 0;
    priority_queue<PII, vector<PII>, greater<PII> > q;
    q.push(mp(0, st));

    while (!q.empty()) {
        auto p = q.top();   q.pop();
        int v = p.S, dd = p.F;
        // if (v == en)  return dd;
        for (auto nb : adj[v]) {
            if (dist[nb.S] > dd + nb.F) {
                dist[nb.S] = dd + nb.F;
                q.push(mp(dist[nb.S], nb.S));
            }
        }
    }
    for (int i = 0; i < n; i++)	d[st][i] = dist[i]; 
    return INF;
} 
int calc(int mask) {
	if (mask == 0)	return 0;
	int &ret = dp[mask];
	if (ret != -1)	return ret;
	ret = INF;

	for (int i = 0; i < n; i++) if ((mask >> i) & 1) {
		for (int j = i + 1; j < n; j++) if ((mask >> j) & 1) {
			int nmask = mask & (~(1 << i)) & (~(1 << j)); 
			//assert(d[i][j] == d[j][i]);
			ret = min(ret, calc(nmask) + d[i][j]);
		}
	}
	return ret;
}
signed main() {

    IOS;
    memset(dp, -1, sizeof dp);
    cin >> n >> m;
    set<int> nodes;
    if (m == 0) {
    	cout << 0 << endl;
    	return 0;
    }
    for (int i = 0; i < m; i++) {
    	int a, b, c;	cin >> a >> b >> c;
    	a--, b--;
    	nodes.insert(a), nodes.insert(b);
    	ans += c;
    	if (a == b)	{
    		continue;
    	}
    	adj[a].pb(mp(c, b));
    	adj[b].pb(mp(c, a));
    	deg[a]++, deg[b]++;
    }
    reach(0);
    if (vv != nodes) {
    	cout << -1 << endl;
    	return 0;
    }
    for (auto i : nodes) djikstra(i, i, adj); 

    int mask = 0;
	for (auto i : nodes) if (deg[i] & 1) mask |= (1 << i);
	
	int add = calc(mask);
	cout << add + ans << endl;

    return 0;
}
