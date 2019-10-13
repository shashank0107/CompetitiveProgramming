/*
    Author : manu_sy
    
    Idea : If A manages to reach a cycle before B, then A wont be caught.
           So just find all the nodes that are in cycle and the time to reach there by A and B
           If no such cyclic node exists where A reach before B, then ans is the max time to reach a node by B (where A reach first)
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
#ifdef LOCALI
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif
#define tm tmmm
/* Debug Ends */

const int N = 3e3+7;

/** Template Ends **/
int n, m, A, B, tm[2][N];
vector<int> g[N], adj[N];
bool incycle[N];

/* Tarjan */
int dfn[N], lowLink[N], ndfn, comp[N], instack[N];
stack<int> st;
vector<vector<int> > comps;

void pre() {
    comps.clear();
    ndfn = 0;
    LP(i,n+2) dfn[i] = -1, comp[i] = -1, g[i].clear(), adj[i].clear(), 
              tm[0][i] = -1, tm[1][i] = -1, incycle[i] = 0;
}
void tarjan(int v, int par) {
    dfn[v] = lowLink[v] = ndfn++, instack[v] = 1;
    st.push(v);

    for (auto ch : g[v]) if (ch != par) {
        if (dfn[ch] == -1) {
            tarjan(ch, v);
            lowLink[v] = min(lowLink[v], lowLink[ch]);
        } else if (instack[ch]) {
            incycle[ch] = true;
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

void bfs(int id, int s) {
    
    queue<PII> q;
    tm[id][s] = 0;
    q.push(mp(s,0));

    while (!q.empty()) {
        auto p = q.front(); q.pop();
        int v = p.F;

        for (auto nb : g[v]) if (tm[id][nb] == -1) {
            tm[id][nb] = tm[id][v]+1;
            q.push(mp(nb, tm[id][nb]));
        }
    }
}

signed main() {

    IOS;
    int t;  cin >> t;
    while (t--) {
        cin >> n >> m >> A >> B;
        assert(A != B);
        pre();
        for (int i = 0; i < m; i++) {
            int a, b;   cin >> a >> b;
            g[a].pb(b); g[b].pb(a);
        }
        for (int i = 1; i <= n; i++) if (dfn[i] == -1) tarjan(i, -1);
        for (int i = 1; i <= n; i++) if (dfn[i] > lowLink[i]) incycle[i] = true;

        bfs(0, A);
        bfs(1, B);
        
        bool found = false;
        int tme = INT_MIN;
        for (int i = 1; i <= n; i++) {
            if (incycle[i] && tm[0][i] < tm[1][i]) {
                found = true;   break;
            }
            if (tm[0][i] <= tm[1][i])
                tme = max(tme, tm[1][i]);
        } 
        if (found) cout << "No" << endl;
        else cout << tme << endl;
    }

    return 0;
}
