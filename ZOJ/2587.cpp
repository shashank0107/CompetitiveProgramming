/*
    Author : manu_sy
    Idea : We have to check whether mincut is unique
        So find 2 mincuts :
        - 1st by picking edges as near to sink as possible.
        - 2nd by picking edges as near the source as possible.
        If they are same then unique mincut else ambigous
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
int n, m, a, b;

struct MF {
    int n;
    vector<vector<int> > adj, cap;
    vector<int> vis;
    bool unique;

    MF(int nn) {
        n = nn;
        adj.resize(n);
        vis.resize(n);
        cap = vector<vector<int> >(n, vector<int>(n, 0));
    }
    void addEdge(int s, int e, int capacity) {
        adj[s].pb(e);
        adj[e].pb(s);
        cap[s][e] = capacity;
        cap[e][s] = capacity;
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
    void dfs(int v, vector<PII>& ans) {
        vis[v] = 1;
        for (auto nb : adj[v]) {
            if (vis[nb] == 0) {
                dfs(nb, ans);
            }
            else if (vis[nb] == 2)
                ans.pb(mp(v,nb));
        }
    }
    void dfs2(int v) {
        vis[v] = 2;
        for (auto nb : adj[v]) 
            if (!vis[nb] && cap[nb][v] > 0) dfs2(nb);
    }
    vector<PII> getMinCut(int source, int sink) {
        fill(all(vis), 0);
            
        unique = true;
        vector<PII> ans;
        dfs2(sink);
        dfs(source, ans);
        return ans;
    }
    void dfs1(int v, vector<PII>& ans) {
        vis[v] = 1;
        for (auto nb : adj[v])
            if (vis[nb] == 0)   dfs(nb,ans);
            else if (vis[nb] == 2)
                ans.pb(mp(v,nb));

    }
    void dfs22(int v) {
        vis[v] = 2;
        for (auto nb : adj[v])
            if (!vis[nb] && cap[v][nb] > 0) dfs22(nb);
    }
    vector<PII> getMinCut2(int source, int sink) {
        fill(all(vis), 0);
            
        unique = true;
        vector<PII> ans;
        dfs22(source);
        dfs1(sink, ans);
        return ans;
    }

};
void norm(vector<PII>& p) {
    for (int i = 0; i < p.size(); i++) {
        if (p[i].F > p[i].S)    swap(p[i].F, p[i].S);
    }
    sort(all(p));
}
signed main() {

    IOS;
    while (cin >> n >> m >> a >> b) {
        if (n == 0 && m == 0 && a == 0 && b == 0)   break;

        MF mf(n+1);
        for (int i = 0; i < m; i++) {
            int a, b, c;   cin >> a >> b >> c;
            mf.addEdge(a,b,c);
        }
        int flow = mf.maxFlow(a,b);
        //debug(flow);
        auto mincut = mf.getMinCut(a,b);
        auto mincut2 = mf.getMinCut2(a,b);

        norm(mincut);
        norm(mincut2);

        if (mincut == mincut2)  cout << "UNIQUE" << endl;
        else cout << "AMBIGUOUS" << endl;
    }

    return 0;
}
