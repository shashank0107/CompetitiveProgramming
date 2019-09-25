/*
    Author : manu_sy
    
    Idea : - Given an undirected graph (N = 500), some vertices can be colored A, some B and some both. 
             For each edge if the vertices of the edge have same color then the cost of that edge is added to profit.
             Color the edges s.t the profit is max and output the profit.
             
           - Make vertices which are only A as source and only B as sink. Find the mincut btw source and sink.
           - Answer is total - mincut
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

const int N = 500+7;
const int M = 1e3+7;
const int INF = 1e9+7;

/** Template Ends **/
int n, k, A, B, a[N], b[N], r[M], g[N];

struct MF {
    int n;
    vector<vector<int> > adj, cap;
    vector<int> vis;

    MF(int nn) {
        n = nn;
        adj.resize(n);
        vis.resize(n);
        cap = vector<vector<int> >(n, vector<int>(n, 0));
    }
    void addEdgeBi(int s, int e, int capacity) {
        adj[s].pb(e);
        adj[e].pb(s);
        cap[s][e] += capacity;
        cap[e][s] += capacity;
    }
    void addEdgeUni(int s, int e, int capacity) {
        adj[s].pb(e);
        adj[e].pb(s);
        cap[s][e] += capacity;
    }
    int bfs(int s, int e, vector<int>& parent) {
        fill(all(parent), -1);
        parent[s] = -2;
        queue<PII> q;
        q.push(mp(s, INT_MAX));

        while (!q.empty()) {
            PII p = q.front();  q.pop();
            int cur = p.F;
            int flow = p.S;

            for (auto next : adj[cur]) {
                if (parent[next] == -1 && cap[cur][next]) {
                    parent[next] = cur;
                    int newflow = min(flow, cap[cur][next]);
                    if (next == e)
                        return newflow;
                    q.push(mp(next, newflow));
                }
            }
        }
        return 0;
    }
    int maxFlow(int source, int sink) {
        int flow = 0;
        vector<int> parent(n);
        int newflow;

        while (newflow = bfs(source, sink, parent)) {
            flow += newflow;

            for (int cur = sink; cur != source; cur = parent[cur]) {
                int prev = parent[cur];
                cap[prev][cur] -= newflow;
                cap[cur][prev] += newflow;
            }
        }
        return flow;
    }
};

signed main() {

    IOS;
    cin >> k >> n >> A >> B;

    MF mf(k+2);
    int source = 0, sink = k+1;

    LP(i,A) {
        int x;  cin >> x;
        a[x] = 1;
    }
    LP(i,B) {
        int x;  cin >> x;
        b[x] = 1;
    }
    FOR(i,1,k) {
        if (!b[i])  mf.addEdgeUni(source, i, INF);
        if (!a[i])  mf.addEdgeUni(i, sink, INF);
    }

    LP(i,n) cin >> r[i];

    int ans = 0;
    FOR(i,1,n-1) {
        int x;  cin >> x;
        mf.addEdgeBi(r[i],r[i-1],x);
        ans += x;
    }  
    
    cout << ans - mf.maxFlow(source, sink) << endl;

    return 0;
}
