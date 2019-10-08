/*
    Author : manu_sy
    
    Idea : - Make a Component graph.
           - Now you profit in each component is the total value that you can derive from walking in that component
           - Calculate the answer for component of s using dfs - trivial dp
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

const int N = 1e6+5;

/** Template Ends **/
int n, m, s;
ll dp[N], compCost[N];
vector<PII> g[N];

/* Tarjan */
int dfn[N], lowLink[N], ndfn, comp[N], instack[N];
stack<int> st;
vector<vector<int> > comps;
map<int, int> adj[N];

void pre() {
    LP(i,n+2) dfn[i] = -1, comp[i] = -1, dp[i] = -1;
}
void tarjan(int v) {
    dfn[v] = lowLink[v] = ndfn++, instack[v] = 1;
    st.push(v);

    for (auto che : g[v]) {
        int ch = che.F;
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
            comp[x] = comps.size()-1;
        }
    }
}
/* Tarjan Ends */

ll f(ll n) {
    return (n*(n+1))/2;
}
ll totCost(ll n) {

    ll lo = 0, hi = n, t;
    while (hi-lo>1) {
        ll mid = (hi+lo)/2;
        if (f(mid) <= n)    lo = mid;
        else hi = mid;
    }
    if (f(hi) <= n)  t = hi;
    else if (f(lo) <= n) t = lo;
    
    ll ret = (t+1)*n - (t*(t+1)*(t+2))/6;
    return ret;
}
void makeCompGraph() {
    FOR(v,1,n) 
        for (auto nbe : g[v]) {
            int nb = nbe.F;
            if (comp[nb] != comp[v]) adj[comp[v]][comp[nb]] = max(adj[comp[v]][comp[nb]], nbe.S);
            else compCost[comp[v]] += totCost(nbe.S);
        }
}
ll calc(int v) {
    if (dp[v] != -1)    return dp[v];

    dp[v] = 0;
    for (auto nbe : adj[v]) {
        dp[v] = max(dp[v], nbe.S + calc(nbe.F));
    }
    dp[v] += compCost[v];
    return dp[v];
}

signed main() {

    IOS;
    cin >> n >> m;
    LP(i,m) {
        int a, b, w;    cin >> a >> b >> w;
        g[a].pb(mp(b,w));
    }
    cin >> s;
    pre();
    FOR(i,1,n) if (dfn[i] == -1) tarjan(i);
    makeCompGraph();

    cout << calc(comp[s]) << endl;
    return 0;
}
