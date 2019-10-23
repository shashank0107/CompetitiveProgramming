/*
    Author : manu_sy
    
    Idea : Just keep mn[i][j] : 10 minimum values till 2^i th parent for each up[i][j].
           Then answer each query easily using lca concept
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
#ifdef LOCAL
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif
/* Debug Ends */
 
const int N = 1e5+7;
 
/** Template Ends **/
int n, m, q, up[N][22], L[N], l;
vector<int> live[N], mn[N][22], g[N]; 
 
vector<int> merge(vector<int>& a, vector<int>& b)
{
    vector<int> ret = a;
    for (auto i : b) ret.pb(i);
    sort(all(ret));
    ret.resize(unique(all(ret)) - ret.begin());
    if (ret.size() > 10)    ret.resize(10);
    return ret;
}
void dfs(int v, int p, int dep)
{
    L[v] = dep;
    if (p) up[v][0] = p, mn[v][0] = merge(live[v], live[p]);
    
    for (int i = 1; i <= l; i++)
        if (up[v][i-1] != -1)
            up[v][i] = up[up[v][i-1]][i-1],
            mn[v][i] = merge(mn[v][i-1], mn[up[v][i-1]][i-1]);
 
    for (auto ch : g[v]) if (ch != p) dfs(ch, v, dep+1);
}
vector<int> get(int u, int v)
{
    if (u == v) return live[u];
    if (L[u] < L[v])    swap(u, v);
 
    vector<int> ret = merge(live[u], live[v]);
    for (int i = l; i >= 0; i--)
        if (((L[u]-L[v])>>i)&1)
            ret = merge(ret, mn[u][i]),
            u = up[u][i];
    
    if (u == v)
    {
        return ret;
    }
 
    for (int i = l; i >= 0; i--)
        if (up[u][i] != up[v][i])
            ret = merge(ret, mn[u][i]),
            ret = merge(ret, mn[v][i]),
            u = up[u][i], v = up[v][i];
    ret = merge(ret, mn[u][0]);
 
    return ret;
}
signed main() {
 
    IOS;
    cin >> n >> m >> q;
    LP(i,n-1) 
    {
        int a, b;   cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }
    FOR(i,1,m)
    {
        int c;  cin >> c;
        live[c].pb(i);
    }
    FOR(i,1,n) 
    {
        sort(all(live[i]));
        if (live[i].size() > 10) live[i].resize(10);
    }
    memset(up, -1, sizeof up);
    l = ceil(log2(n));
    dfs(1, 0, 0);
 
    LP(i,q)
    {
        int u, v, a;    cin >> u >> v >> a;
        vector<int> res = get(u, v);
        if (res.size() > a) res.resize(a);
        cout << res.size() << " ";
        for (auto i : res) cout << i << " ";    cout << endl;
    }
 
    return 0;
}
