/*
    Author : manu_sy
    Idea : Think of tree as a directed graph where each leaf has an edge to its kth parent
           So we just need to go in this directed graph from root till any leaf.
           Think in terms of component graph where profit of each node is the no. of leaves in that component
           Since component graph is acyclic, we can easily calculate the answer using dfs
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

const int N = 1e6+7;

/** Template Ends **/
int n, k, dp[N], profit[N];
bool leaf[N];
vector<int> tempg[N], g[N], anc;

void dfs(int v, int par) {

    if (par != -1) {
        g[par].pb(v);
        int kanc = max(0, (int)anc.size()-k);
        if (tempg[v].size() == 0) g[v].pb(anc[kanc]), leaf[v] = true;
    }
    anc.pb(v);

    for (auto nb : tempg[v]) 
        if (nb != v) 
            dfs(nb, v);

    anc.pop_back();
}

/* Tarjan */
int dfn[N], lowLink[N], ndfn, comp[N], instack[N];
stack<int> st;
vector<vector<int> > comps;
vector<int> adj[N];

void pre() {
    LP(i,n+2) dfn[i] = -1, comp[i] = -1, dp[i] = -1;
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
        while (x != v) {
            x = st.top(), st.pop(), instack[x] = 0;
            comps.back().pb(x);
            profit[comps.size()-1] += leaf[x];
            comp[x] = comps.size()-1;
        }
    }
}
void makeCompGraph() {
    FOR(v,1,n) for (auto nb : g[v]) if (comp[nb] != comp[v]) adj[comp[v]].pb(comp[nb]);
}
/* Tarjan Ends */

int calc(int v) {
    if (dp[v] != -1)    return dp[v];

    dp[v] = 0;
    for (auto nb : adj[v]) dp[v] = max(dp[v], calc(nb));
    dp[v] += profit[v];
    return dp[v];
}
signed main() {

    IOS;
    cin >> n >> k;
    for (int i = 2; i <= n; i++) {
        int a;   cin >> a;
        tempg[a].pb(i);
    }    
    dfs(1, -1);

    pre();
    for (int i = 1; i <= n; i++) if (dfn[i] == -1) tarjan(i);
    makeCompGraph();

    cout << calc(comp[1]) << endl;
    return 0;
}
