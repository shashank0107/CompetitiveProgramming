/*
    Author : manu_sy
    Idea : Just find the euler tour through the graph.
         Algo - https://math.stackexchange.com/questions/1871065/euler-path-for-directed-graph
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

const int N = 1e5+7;

/** Template Ends **/
int n;
vector<vector<int> > g;

// return {0, no_euler} / {1, euler_path} / {2, euler_cyle} 
pair<int, vector<int> > euler_directed(vector<vector<int> >& adj, int need, vector<int> nodes)
{
    assert(nodes.size() != 0);
    int n = g.size(), edge_cnt = 0;
    vector<int> in(n, 0), out(n, 0);
    for (auto x : nodes) for (auto nb : adj[x]) in[nb]++, out[x]++, edge_cnt++;
    vector<PII> deg;
    for (auto x : nodes) if ((in[x] - out[x])&1)    deg.pb(mp(in[x] - out[x], x));

    int f = 0;
    if (deg.size() == 0)    f = 2;
    else if (deg.size() == 2 ) {
        sort(all(deg));
        if (deg[0].F == -1 && deg[1].F == 1)    f = 1, adj[deg[1].S].pb(deg[0].S), edge_cnt++;
    }

    if (!f) return mp(f, vector<int>());
    
    vector<int> path;
    stack<int> st;
    st.push(nodes[0]);

    vector<set<int> > g;
    g.resize(n);
    for (auto x : nodes) for (auto nb : adj[x]) g[nb].insert(x);

    while (!st.empty())
    {
        int u = st.top();
        if (g[u].empty())
        {
            path.pb(u);
            st.pop();
        }
        else
        {
            int w = *g[u].begin();
            g[u].erase(w);
            st.push(w);
        }
    }
    if (path.size() != edge_cnt + 1)    return mp(0, vector<int>());
    else return mp(f, path);
}

signed main() {

    IOS;
    cin >> n;
    g.resize(N);
    set<int> nds;
    for (int i = 0; i < n; i++)
    {
        int m;  cin >> m;
        for (int j = 0, last = 0; j < m + 1; j++)
        {
            int x;  cin >> x;
            if (last)   g[last].pb(x);
            last = x;
            nds.insert(x);
        }
    } 
    vector<int> nodes;
    for (auto x : nds)  nodes.pb(x);

    auto p = euler_directed(g, nodes.size(), nodes);

    if (p.F != 2) 
    {
        cout << 0 << endl;
    }
    else 
    {
        cout << p.S.size() - 1;
        for (int i = 0; i < p.S.size(); i++) {
            cout << " " << p.S[i];
        } cout << endl;
    }

    return 0;
}
