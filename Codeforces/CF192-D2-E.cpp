/*
    Author : manu_sy
    
    Idea : For each pair of fools a,b who have path -
          - Go from a to b using the lca path and keep adding 1 to sum[v][i] everytime you go from v to up[v][i]
          
          Now after this we have to propagate this sum[u][i] to finally sum[j][0]
          which can be done in just reverse order of how we make up[v][i] using dfs
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
int n, L[N], k;
vector<int> g[N];
map<int, int> ans[N];

int l, timer;
vector<int> tin, tout;
vector<vector<int> > up, sum;

void dfs(int v, int p, int lvl) {
    L[v] = lvl;
    tin[v] = timer++;
    up[v][0] = p;
    for (int i = 1; i <= l; i++)
        up[v][i] = up[up[v][i-1]][i-1];
    for (int i : g[v])
        if (i != p) dfs(i, v, lvl+1);
    tout[v] = timer++;
}
bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}
void add(int u, int v)  {
    if (is_ancestor(u,v))   swap(u,v);
    if (!is_ancestor(v,u)) {
        for (int i = l; i >= 0; i--)
            if (!is_ancestor(up[v][i],u))
                sum[v][i]++, v = up[v][i];
        sum[v][0]++, v = up[v][0];
    }
    assert(is_ancestor(v,u));
    for (int i = l; i >= 0; i--)
        if (L[up[u][i]] >= L[v])
            sum[u][i]++, u = up[u][i];
    assert(u == v);
}
void preProcess(int root) {
    tin.resize(n+1);
    tout.resize(n+1);
    l = ceil(log2(n));
    up.assign(n+1, vector<int>(l+1));
    sum = up;
    dfs(1,1,0);
}

void dfs(int v, int p) {
    for (int i : g[v])
        if (i != p) dfs(i, v);
    for (int i = l; i >= 1; i--) { 
        sum[v][i-1]+=sum[v][i];
        if (up[v][i-1] != v) sum[up[v][i-1]][i-1] += sum[v][i];
    }
    ans[min(p,v)][max(p,v)] = sum[v][0];
}

signed main() {

    IOS;
    cin >> n;
    vector<PII> edges;
    LP(i,n-1) {
        int a, b;   cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
        edges.pb(mp(a, b));
    }
    preProcess(1);
    cin >> k;
    LP(i,k) {
        int a, b;   cin >> a >> b;
        add(a,b);
    }
    dfs(1,1);
    for (auto &e : edges) {
        if (e.F > e.S)  swap(e.F, e.S);
        cout << ans[e.F][e.S] << " ";
    } cout << endl;
    return 0;
}
