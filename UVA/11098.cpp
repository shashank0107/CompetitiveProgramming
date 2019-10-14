/*
    Author : manu_sy

    Idea : Make a directed graph on bomb i->j if i triggers j
           - Note that only one node in a SCC can be included in the result
           - So we make component graph and represent each component by the cheapest bomb in it
           - All nodes in this component graph with indegree 0 should be included
           - Now other nodes can be included as long as they decrease the average
           - To order the result, just do according to their position in toposort,
             i.e, if i->j then definately in result j must be before i
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

const int N = 1e3+7;

/** Template Ends **/
int n, x[N], y[N], r[N], e[N], cost[N], bomb[N];
vector<int> g[N], res;
bool taken[N];

ll sq(ll a) {   return a*a; }
ll dist2(int i, int j) {
    return sq(x[i]-x[j]) + sq(y[i]-y[j]);
}

/* Tarjan */
int dfn[N], lowLink[N], ndfn, comp[N], instack[N], in[N], pos[N];
stack<int> st;
vector<vector<int> > comps;
vector<int> adj[N];

void pre() {
    comps.clear(), ndfn = 0;
    LP(i,n+2) dfn[i] = -1, g[i].clear(), adj[i].clear(), in[i] = 0, taken[i] = 0, pos[i] = -1;
    res.clear();
}
void tarjan(int v) {
    dfn[v] = lowLink[v] = ndfn++, instack[v] = 1;
    st.push(v);
    
    for (auto ch : g[v]) {
        if (dfn[ch] == -1) {
            tarjan(ch);
            lowLink[v] = min(lowLink[v], lowLink[ch]);
        } else if (instack[ch]) {
            lowLink[v] = min(lowLink[v], dfn[ch]);
        }
    }
    if (lowLink[v] == dfn[v]) {
        comps.pb(vector<int>());
        int x = -1;
        bomb[comps.size()-1] = v;
        while (x != v) {
            x = st.top(), st.pop(), instack[x] = 0;
            comps.back().pb(x);
            comp[x] = comps.size()-1;
            if (e[x] < e[bomb[comps.size()-1]]) bomb[comps.size()-1] = x;
        }
    }
}
void makeCompGraph() {
    for (int v = 1; v <= n; v++) for (auto nb : g[v]) if (comp[nb] != comp[v]) adj[comp[v]].pb(comp[nb]), in[comp[nb]]++;
}
/* Tarjan Ends */
vector<int> toposort() {
    queue<int> q;
    for (int i = 0; i < comps.size(); i++) if (in[i] == 0)  q.push(i);
    vector<int> ret;
    while (!q.empty()) {
        int p = q.front();  q.pop();
        ret.pb(p);
        for (auto nb : adj[p]) {
            in[nb]--;
            if (in[nb] == 0) q.push(nb);
        }
    }
    for (int i = 0; i < ret.size(); i++) {
        pos[ret[i]] = i;
    }
    return ret;
}
bool compare(int a, int b) {
    assert(pos[comp[a]] != -1 && pos[comp[b]] != -1 && comp[a] != comp[b]);
    return pos[comp[a]] > pos[comp[b]];
}
signed main() {

    IOS;
    int tc; cin >> tc;
    for (int t = 1; t <= tc; t++) {

        cin >> n;
        for (int i = 1; i <= n; i++) cin >> x[i] >> y[i] >> r[i] >> e[i];
        pre();

        FOR(i,1,n) FOR(j,1,n) if (i != j) {
            if (dist2(i,j) <= sq(r[i]+r[j]+e[i]))
                g[i].pb(j);
        }
        for (int i = 1; i <= n; i++) if (dfn[i] == -1) tarjan(i);
        makeCompGraph();
        
        ll tot = 0;
        for (int i = 0; i < comps.size(); i++) 
            if (in[i] == 0) 
                res.pb(bomb[i]), tot += e[bomb[i]], taken[i] = true;
        vector<int> topo = toposort();

        vector<PII> p;
        for (int i = 0; i < topo.size(); i++) {
            if (!taken[topo[i]])
                p.pb(mp(e[bomb[topo[i]]], topo[i]));
        }
        sort(all(p));

        for (auto i : p) {
            int new_tot = (tot+i.F);
            if (new_tot*(res.size()) <= tot*(res.size()+1)) {
                res.pb(bomb[i.S]), tot += e[bomb[i.S]], taken[i.S] = true;
            } 
        }
        sort(all(res), compare);

        cout << "Case #" << t << ": ";
        for (int i = 0; i < res.size(); i++) {
            if (i) cout << " "; cout << res[i]-1;
        } cout << endl;
    }    
    return 0;
}
