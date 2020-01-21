/*
    Author : manu_sy
    Idea : just have to find the cost of the euler cycle, graph is connected
          - if instead there is a euler path only then connect any edge of len djikstra_dist(st,en) b/w starting and ending nodes
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
  return os << "(" << P.F << "," << (char)(P.S+'a') << ")";
} 

template<class T> ostream &operator<<(ostream& os, vector<T> V) {
  os << "["; for (auto vv : V) os << vv << ","; return os << "]";
}

template<class TH> void _dbg(const char *sdbg, TH h){ cerr << sdbg << '=' << h << endl; }

template<class TH, class... TA> void _dbg(const char *sdbg, TH h, TA... a) {
  while(*sdbg!=',') cerr << *sdbg++;
  cerr<<'='<<h<<','; _dbg(sdbg+1, a...);
}

#ifdef LOCALI
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif

/* Debug Ends */

const int N = 1e5+7;
const int C = 26;
const int INF = 1e9;

/** Template Ends **/
void add_edge(vector<vector<PII> >& adj, int a, int b, int len) {
    char c = (char)(a+'a'), d = (char)(b + 'a');
    if (mp(c, d) == mp('c', 't') || mp(c, d) == mp('t', 'c'))   assert(false);
    debug(c, d, len);
    adj[a].pb(mp(len, b));
    adj[b].pb(mp(len, a));
}
int djik(int st, int en, vector<vector<PII> >& adj) {
    int n = adj.size();
    int dist[n];
    for (int i = 0; i < n; i++) dist[i] = INF;
    dist[st] = 0;
    priority_queue<PII, vector<PII>, greater<PII> > q;
    q.push(mp(0, st));

    while (!q.empty()) {
        auto p = q.top();   q.pop();
        int v = p.S, dd = p.F;
        if (v == en)  return dd;
        for (auto nb : adj[v]) {
            if (dist[nb.S] > dd + nb.F) {
                dist[nb.S] = dd + nb.F;
                q.push(mp(dist[nb.S], nb.S));
            }
        }
    }
    return INF;
} 
PII euler_undirected(vector<vector<PII> >& adj) 
{
    assert(adj.size() != 0);
    int n = adj.size(), edge_cnt = 0, start = -1;
    vector<int> in(n), out(n);
    for (int i = 0; i < n; i++) for (auto nb : adj[i]) {
        if (start == -1)    start = i;
        in[nb.S]++, edge_cnt++;
    }

    edge_cnt /= 2;
    vector<PII> deg;
    for (int i = 0; i < n; i++) if (in[i]&1) deg.pb(mp(in[i], i));

    int f = 0;
    if (deg.size() == 0)    f = 2;
    else if (deg.size() == 2)
    {
        sort(all(deg));
        f = 1, add_edge(adj, deg[0].S, deg[1].S, djik(deg[0].S, deg[1].S, adj)), edge_cnt++;
    }
    if (f == 0 || start == -1) return mp(0, 0);
    
    vector<int> path;
    stack<int> st;
    st.push(start);
    vector<multiset<PII> > g(n);
    for (int i = 0; i < n; i++) for (auto nb : adj[i]) g[nb.S].insert(mp(nb.F, i));

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
            int v = (*g[u].begin()).S;
            ans += (*g[u].begin()).F;
            g[v].erase(g[v].lower_bound(mp((*g[u].begin()).F, u)));
            g[u].erase(g[u].begin());
            st.push(v);
        }
    }
    if (path.size() != edge_cnt + 1)    return mp(0, -1);
    return mp(f, ans);
}

signed main() {

    //IOS;
    string s;
    while (getline(cin, s))
    {
        if (s.size() == 0)  break;
        if (s == "deadend") {
            cout << 0 << endl;
            continue;
        }
        set<char> c;
        vector<vector<PII> > adj(C);
        do {    
            if (s == "deadend") break;
            debug(s);
            add_edge(adj, s[0] - 'a', s.back() - 'a', s.size());
            c.insert(s[0]), c.insert(s.back());
        } while (getline(cin, s));

        auto p = euler_undirected(adj);
        assert(p.F != 0);
        cout << p.S << endl;
    }

    return 0;
}
