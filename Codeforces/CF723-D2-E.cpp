/*
    Author : manu_sy
    Idea : Similar to editorial https://codeforces.com/blog/entry/47502
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

const int N = 2e2+3;

/** Template Ends **/
int n, m, deg[N], in[N], out[N];
int g[N][N], ini[N][N];
vector<PII> edges;
vector<int> path;

void pre() {
    memset(g, 0, sizeof g);
    memset(in, 0, sizeof in);
    memset(out, 0, sizeof out);
    memset(ini, false, sizeof ini);
    memset(deg, 0, sizeof deg);
    edges.clear();
    path.clear();
}
void addEdge(int u, int v) {
    g[u][v]++, g[v][u]++;
    deg[u]++, deg[v]++;
}
void dfs(int v) {
    if (deg[v]) {
        for (int i = 1; i <= n; i++) {
            if (g[v][i]) {
                g[v][i]--, g[i][v]--;
                deg[v]--, deg[i]--;
                dfs(i);
                break;
            }
        }
    }
    path.pb(v);
}
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
};
signed main() {

    IOS;
    int t;  cin >> t;
    while (t--)
    {
        cin >> n >> m;
        pre();
        UNF uf(n+1);
        for (int i = 0; i < m; i++) {
            int a, b;   cin >> a >> b;
            ini[a][b] = ini[b][a] = 1;
            uf.union_sets(a, b);
            addEdge(a, b);
        }

        vector<int> odd;
        for (int i = 1; i <= n; i++) if (deg[i]&1) odd.pb(i);
        if (odd.size()) {
            vector<bool> taken(odd.size(), false);
            for (int i = 0; i < odd.size(); i++) if (!taken[i]) {
                bool found = false;
                for (int j = i + 1; j < odd.size(); j++) {
                    if (uf.find_set(odd[i]) == uf.find_set(odd[j])) {
                        found = true;
                        addEdge(odd[i], odd[j]);
                        taken[j] = taken[i] = true;
                    }
                }
                assert(found);
            }
        }

        for (int i = 1; i <= n; i++) while (deg[i]) {
            path.clear();
            dfs(i);
            for (int i = 1; i < path.size(); i++) {
                int u = path[i - 1], v = path[i];
                if (ini[u][v]) {
                    edges.pb(mp(u, v));
                    ini[u][v] = ini[v][u] = false;
                    in[v]++, out[u]++;
                }
            }
            debug(i, path, edges);
        }

        int cnt = 0;
        assert(edges.size() == m);
        for (int i = 1; i <= n; i++) {
            if (in[i] == out[i]) cnt++;
        }

        cout << cnt << endl;
        for (auto i : edges)    cout << i.F << " " << i.S << endl;
    }

    return 0;
}
