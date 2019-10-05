/*
    Author : manu_sy
    
    Idea : Goal is to find the minimal set of edges to be added to a DAG to make the graph strongly connected
          - Build component graph. It is acyclic DAG
          - No. of edges to make it connected : max(src, sink)
            src : no incoming edge, sink : no outgoing edge
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
int n, m, in[N], out[N];
vector<int> g[N];

int dfn[N], lowLink[N], comp[N], instack[N], ndfn, ncmp;
stack<int> st;

void pre() {
    ndfn = ncmp = 0;
    FOR(i,0,n+4) 
        g[i].clear(), dfn[i] = lowLink[i] = -1, 
        comp[i] = -1, in[i] = out[i] = 0, instack[i] = 0;
}
void tarjan(int v) {
    dfn[v] = lowLink[v] = ++ndfn, instack[v] = 1;
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
        
        while (1) {
            int vv = st.top();  st.pop(), instack[vv] = 0;
            comp[vv] = ncmp;
            if (vv == v) break;
        }
        ncmp++;
    }
}
signed main() {

    IOS;
    int t;  cin >> t;
    while (t--) {
        cin >> n >> m;
        pre();
        LP(i,m) {
            int a, b;   cin >> a >> b;
            g[a].pb(b);
        }

        FOR(i,1,n) if (dfn[i] == -1) tarjan(i);

        FOR(i,1,n) {
            for (auto nb : g[i]) {
                assert(comp[i] != -1 && comp[nb] != -1);
                if (comp[i] != comp[nb]) 
                    in[comp[nb]]++, out[comp[i]]++;
            }
        }
        int src = 0, snk = 0;
        LP(i,ncmp) { 
            if (in[i] == 0)  src++;
            if (out[i] == 0) snk++;
        }
        if (ncmp == 1) cout << 0 << endl;
        else cout << max(src, snk) << endl;
    }

    return 0;
}
