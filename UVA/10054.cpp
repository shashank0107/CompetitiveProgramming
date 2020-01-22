/*
    Author : manu_sy
    Idea : Just find the euler tour through the graph
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

const int N = 50+3;

/** Template Ends **/

pair<int, vector<int> > euler_undirected_adj(vector<vector<int> >& adj) 
{
    assert(adj.size() != 0);
    int n = adj.size(), edge_cnt = 0, start = -1;
    vector<int> in(n), out(n);
    for (int i = 0; i < n; i++) for (auto nb : adj[i]) {
        if (start == -1)    start = i;
        in[nb]++, edge_cnt++;
    }
    edge_cnt /= 2;
    
    vector<PII> deg;
    for (int i = 0; i < n; i++) if (in[i]&1) deg.pb(mp(in[i], i));

    int f = 0;
    if (deg.size() == 0)    f = 2;
    else if (deg.size() == 2) {
        sort(all(deg));
        f = 1;
        adj[deg[0].S].pb(deg[1].S), adj[deg[1].S].pb(deg[0].S);
        edge_cnt++;
    }
    if (f == 0) return mp(0, vector<int>());
    assert(start != -1);

    vector<int> path;
    stack<int> st;
    st.push(start);
    vector<multiset<int> > g(n);
    for (int i = 0; i < n; i++) for (auto nb : adj[i]) g[i].insert(nb);

    int ans = 0;
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
            int v = (*g[u].begin());
            g[v].erase(g[v].lower_bound(u));
            g[u].erase(g[u].begin());
            st.push(v);
        }
    }
    if (f == 1) {
        adj[deg[0].S].pop_back(), adj[deg[1].S].pop_back();
    }
    if (path.size() != edge_cnt + 1)    return mp(0, vector<int>());
    return mp(f, path);
}

signed main() {

    IOS;
    int t;  cin >> t;
    FOR(tc,1,t)
    {
        cout << "Case #" << tc << endl;
        int m;  cin >> m;
        vector<vector<int> > adj(N);
        while (m--) 
        {
            int a, b;   cin >> a >> b;
            adj[a].pb(b);
            adj[b].pb(a);
        }

        auto p = euler_undirected_adj(adj);
        if (p.F == 2) {
            for (int i = 0; i < (int)p.S.size() - 1; i++) 
                cout << p.S[i] << " " << p.S[i + 1] << endl;
        } else {
            cout << "some beads may be lost" << endl;
        }
        if (tc != t)    cout << endl;
    }

    return 0;
}
