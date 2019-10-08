/*
    Author : manu_sy

    Idea : - Make component graph.
           - Now we want to find the nodes which can reach the maximum no. of nodes
           - Note that only those nodes that have indegree = 0 can be the answer since 
             if a node has an in_edge than its answer is always less than the parent
             ( Without using this observation and brute forcing for all nodes also pases)
           - So just dfs to find reachability of each node with indegree 0
           Complexity : O(V*E)
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

const int N = 9e3+5;

/** Template Ends **/
int n, m, dp[N], ans, inDeg[N], viscnt, reach[N];
vector<int> g[N], adj[N];
bool vis[N];

/* Tarjan */
int dfn[N], lowLink[N], ndfn, comp[N], instack[N];
stack<int> st;
vector<vector<int> > comps;

void pre() {
    comps.clear();
    ndfn = 0;
    LP(i,n+2) dfn[i] = -1, comp[i] = -1, dp[i] = -1, g[i].clear(), adj[i].clear(), inDeg[i] = 0;
    ans = 0;
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
    FOR(v,1,n) for (auto nb : g[v]) if (comp[nb] != comp[v]) adj[comp[v]].pb(comp[nb]), inDeg[comp[nb]]++;
}
/* Tarjan Ends */

void dfs(int v) {
    vis[v] = true;
    viscnt += comps[v].size();

    for (auto nb : adj[v])
        if (!vis[nb])
            dfs(nb);
}
signed main() {

    IOS;
    int t;  cin >> t;
    while (t--) {
        cin >> n >> m;

        pre();
        LP(i,m) {
            int a, b;   cin >> a >> b;
            if (a == b) continue;
            g[b].pb(a);
        }
        FOR(i,1,n) if (dfn[i] == -1) tarjan(i);

        makeCompGraph();
        int nn = comps.size();

        int ans = 0;
        LP(i,nn) {
            if (inDeg[i] == 0) {
                memset(vis, false, sizeof vis);
                viscnt = 0;
                dfs(i);
                reach[i] = viscnt;
                ans = max(ans, viscnt);
            } else reach[i] = 0;
        }

        vector<int> cps;
        LP(i,nn) if (reach[i] == ans) cps.pb(i);

        vector<int> ret;
        for (auto c : cps) for (auto v : comps[c]) ret.pb(v);

        sort(all(ret));
        for (int i = 0; i < ret.size(); i++) {
            if (i) cout << " ";
            cout << ret[i];
        } cout << endl;
    }
    return 0;
}
