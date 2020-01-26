/*
    Author : manu_sy
    Idea : We need to remove minimum amount of edges in graph of 4 nodes such that there is euler tour.
           Note that only if the graph is connected and there are 4 vertices of odd degree, we need to remove an edge and
           that too only 1.
           Otherwise just from each node find the profit of euler path/tour and take max
*/
#include "bits/stdc++.h"
using namespace std;

/** Template Begins **/

typedef long long        ll;
typedef pair<int,int>    PII;
typedef pair<PII,int>    PIII;

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

const int N = 4+2;

/** Template Ends **/
int m, d[N];
vector<PIII> edges;

struct UNF {
    vector<int> par, sz;
    UNF(int n) {
        par.resize(n); sz.resize(n);
        for (int i = 0; i < n; i++) make_set(i);
    }
    void make_set(int v) {
        par[v] = v, sz[v] = 1;
    }
    int find_set(int v) {
        if (v == par[v])    return v;
        return par[v] = find_set(par[v]);
    }
    void union_sets(int u, int v) {
        u = find_set(u);
        v = find_set(v);
        if (u != v) {
            if (sz[u] < sz[v])  swap(u, v);
            par[v] = u;
            sz[u] += sz[v];
        }
    }
} uf(N+1);
bool vis[N];
void dfs(int v, vector<multiset<PII> >& adj, vector<int>& comp) {
    vis[v] = true;
    comp.pb(v);
    for (auto nb : adj[v]) if (!vis[nb.F]) dfs(nb.F, adj, comp);
}
pair<int, int> euler_undirected_adj(vector<multiset<PII> >& adj, int start) 
{
    assert(adj.size() != 0);
    int n = adj.size();
    vector<int> in(n), out(n);
    vector<int> comp;
    memset(vis, false, sizeof vis);
    dfs(start, adj, comp);
    for (auto i : comp) { 
        for (auto nb : adj[i]) in[nb.F]++;
    }
    
    vector<PII> deg;
    for (int i = 0; i < n; i++) if (in[i]&1) deg.pb(mp(in[i], i));
    int f = 0;
    if (deg.size() == 0)    f = 2;
    else if (deg.size() == 2) {
        sort(all(deg));
        f = 1;
        adj[deg[0].S].insert(mp(deg[1].S,0)), adj[deg[1].S].insert(mp(deg[0].S,0));
    }
    if (f == 0) return mp(-1, 0);
    assert(start != -1);

    vector<int> path;
    stack<int> st;
    st.push(start);

    int ans = 0;
    while (!st.empty())
    {
        int u = st.top();
        if (adj[u].empty())
        {
            path.pb(u);
            st.pop();
        }
        else 
        {
            auto vv = (*adj[u].begin());
            int v = vv.F, val = vv.S;
            adj[v].erase(adj[v].lower_bound(mp(u, val)));
            adj[u].erase(adj[u].begin());
            st.push(v);
            ans += val;
        }
    }
    return mp(f, ans);
}
signed main() {

    IOS;
    cin >> m;
    vector<multiset<PII> > adj(N);
    int sum = 0, mn = INT_MAX;
    for (int i = 0; i < m; i++) {
        int c1, val, c2;    cin >> c1 >> val >> c2;
        adj[c1].insert(mp(c2, val)), d[c1]++;
        adj[c2].insert(mp(c1, val)), d[c2]++;
        sum += val;
        if (c1 != c2)   edges.pb(mp(mp(c1, c2), val));
        uf.union_sets(c1, c2);
    }

    int odd = 0;
    for (int i = 1; i <= 4; i++) if (d[i]&1) odd++;
    if (uf.sz[uf.find_set(1)] == 4 && odd == 4) {
        int ans = 0;
        for (auto i : edges) {
            auto g = adj;
            int c1 = i.F.F, c2 = i.F.S, val = i.S;
            g[c1].erase(mp(c2, val)), g[c2].erase(mp(c1, val));
            for (int i = 1; i <= 4; i++) 
                if (!g[i].empty()) {
                    ans = max(ans, euler_undirected_adj(g, i).S);
                }
        }
        cout << ans << endl;
    } else {
        int ans = 0;
        for (int i = 1; i <= 4; i++) 
            if (!adj[i].empty()) {
                ans = max(ans, euler_undirected_adj(adj, i).S);
            }
        cout << ans << endl;
    }

    return 0;
}
