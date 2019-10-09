/*
    Author : manu_sy
    
    Idea : Just make a graph where i->j edge if for any client (u(i)+1)%h = u(j)
           Now make component graph 
           Now we have to choose a component s.t the reachability count is minimum
           So we can check every component which is a sink and take the one which has minimum size
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
int n, m, h, u[N], out[N];
vector<int> g[N];

/* Tarjan */
int dfn[N], lowLink[N], ndfn, comp[N], instack[N];
stack<int> st;
vector<vector<int> > comps;
vector<int> adj[N];

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
            comp[x] = comps.size()-1;
        }
    }
}
void makeCompGraph() {
    FOR(v,1,n) for (auto nb : g[v]) if (comp[nb] != comp[v]) adj[comp[v]].pb(comp[nb]), out[comp[v]]++;
}
/* Tarjan Ends */

signed main() {

    IOS;
    cin >> n >> m >> h;
    for (int i = 1; i <= n; i++) cin >> u[i];
    
    for (int i = 0; i < m; i++) {
        int a, b;   cin >> a >> b;
        int ta = u[a], tb = u[b];
        
        if ((ta+1)%h == tb) g[a].pb(b);
        if ((tb+1)%h == ta) g[b].pb(a);   
    }

    for (int i = 1; i <= n; i++) dfn[i] = -1, comp[i] = -1;
    for (int i = 1; i <= n; i++) if (dfn[i] == -1)  tarjan(i);
    makeCompGraph();
    
    int id = -1, sz = INT_MAX;
    for (int i = 0; i < comps.size(); i++) 
        if (out[i] == 0 && comps[i].size() < sz) 
            id = i, sz = comps[i].size();

    cout << sz << endl;
    for (auto i : comps[id]) cout << i << " ";  cout << endl;
    return 0;
}
