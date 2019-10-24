/*
    Author : manu_sy
    
    Idea : - Make mst.
           - for each edge a,b find the max edge in mst in path a->b
             mst for this edge is mst_cost - max_edge(a,b) + edge_cost(a,b)
*/
#include <bits/stdc++.h>
using namespace std;

/** Template Begins **/

typedef long long        ll;
typedef pair<int,int>    PII;
typedef pair<int, PII>   PIII;
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

const int N = 2e5+7;

/** Template Ends **/
int n, m, up[N][22], mx[N][22], l, L[N];
vector<PIII> edges;
ll ans[N], mst_cost;
vector<PII> g[N];

int parent[N], size[N];
void make_set(int v) {
    parent[v] = v, size[v] = 1;
}
int find_set(int v) {
    if (v == parent[v]) return v;
    return parent[v] = find_set(parent[v]);
}
void union_sets(int u, int v) {
    u = find_set(u);
    v = find_set(v);
    if (u != v) {
        if (size[u] < size[v]) swap(u, v);
        parent[v] = u;
        size[u] += size[v];
    }
}
void kruskal()
{
    vector<PIII> temp(edges);
    sort(all(temp));
    FOR(i,1,n) make_set(i);

    for (auto i : temp)
    {
        int u = i.S.F, v = i.S.S;
        if (find_set(u) != find_set(v))
        {
            union_sets(u, v), mst_cost += i.F;
            g[u].pb(mp(v, i.F));
            g[v].pb(mp(u, i.F));
        }
    }
}
void dfs(int v, int p, int lvl, int ed)
{
    L[v] = lvl;
    if (p) up[v][0] = p, mx[v][0] = ed;

    for (int i = 1; i <= l; i++)
        if (up[v][i-1] != -1)
            up[v][i] = up[up[v][i-1]][i-1],
            mx[v][i] = max(mx[v][i-1], mx[up[v][i-1]][i-1]);

    for (auto ch : g[v]) if (ch.F != p)
        dfs(ch.F, v, lvl+1, ch.S);
}
int get_mx(int u, int v)
{
    if (L[u] < L[v]) swap(u, v);
    int mxh = INT_MIN;
    for (int i = l; i >= 0; i--)
        if ( ( ( L[u] - L[v] ) >> i ) & 1)
            mxh = max(mxh, mx[u][i]),
            u = up[u][i];

    if (u == v) return mxh; 
    for (int i = l; i >= 0; i--)
        if (up[u][i] != up[v][i])
            mxh = max(mxh, mx[u][i]),
            mxh = max(mxh, mx[v][i]),
            u = up[u][i],
            v = up[v][i];

    return max(mxh, max(mx[u][0], mx[v][0]));
}
signed main() {

    IOS;
    cin >> n >> m;
    LP(i,m)
    {
        int a, b, c;    cin >> a >> b >> c;
        edges.pb(mp(c, mp(a, b)));
    }

    kruskal();
    l = ceil(log2(n));
    memset(up, -1, sizeof up);
    dfs(1, 0, 0, INT_MIN);

    LP(i,m)
    {
        int a = edges[i].S.F, b = edges[i].S.S;
        ans[i] = mst_cost - get_mx(a, b) + edges[i].F;
        cout << ans[i] << endl;
    }

    return 0;
}
