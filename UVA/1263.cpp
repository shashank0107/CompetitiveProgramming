/*
    Author : manu_sy
    
    Idea : Represent the problem as a Directed Graph where i->j if mine i triggers j
           We just have to find the no. of source vertices in the component graph to get the answer, 
           since triggering those will make sure all other mines are triggered.
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

const int N = 2e3+7;

/** Template Ends **/
int n, x[N], y[N], d[N];
vector<int> g[N];

/* Tarjan */
int dfn[N], lowLink[N], ndfn, comp[N], instack[N], inDeg[N];
stack<int> st; 
vector<vector<int> > comps;
vector<int> adj[N];

void pre() {
    comps.clear();
    ndfn = 0;
    LP(i,n+2) dfn[i] = -1, comp[i] = -1, g[i].clear(), adj[i].clear(), inDeg[i] = 0;
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
            comp[x] = comps.size()-1;
        }
    }
}
void makeCompGraph() {
    FOR(v,0,n-1) for (auto nb : g[v]) if (comp[nb] != comp[v]) adj[comp[v]].pb(comp[nb]), inDeg[comp[nb]]++;
}
/* Tarjan Ends */

signed main() {

    IOS;
    int t;  cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> x[i] >> y[i] >> d[i];
        pre();

        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (i != j) {
            int xlo = x[i]-d[i]/2, xhi = x[i]+d[i]/2;
            int ylo = y[i]-d[i]/2, yhi = y[i]+d[i]/2;
            if ((xlo <= x[j] && x[j] <= xhi) && (ylo <= y[j] && y[j] <= yhi))
                g[i].pb(j);
        }
        for (int i = 0; i < n; i++) if (dfn[i] == -1) tarjan(i);
        makeCompGraph();

        int ans = 0;
        for (int i = 0; i < comps.size(); i++) ans += (inDeg[i] == 0);
        cout << ans << endl;
    }

    return 0;
}
