/*
    Author : manu_sy
    Idea : All the bank nodes connected to source with capacity 1 and all nodes on the side to the sink with cap 1.
        - All nodes have capacity 1
        - Find maxflow
    Complexity : O(E*f)
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
int n, m, b;

int in(int v) {
    return v;
}
int out(int v) {
    return n*m+v;
}
struct MF {
    int n;
    vector<vector<int> > adj;
    vector<map<int, int> > cap;
    vector<int> vis;

    MF(int nn) {
        n = nn;
        adj.resize(n);
        vis.resize(n);
        cap.resize(n);
    }
    void addEdge(int s, int e, int capacity) {
        adj[s].pb(e);
        adj[e].pb(s);
        cap[s][e] = capacity;
        cap[e][s] = 0;
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
    int t;  cin >> t;
    while (t--) {
        cin >> n >> m >> b;
        MF mf(2*n*m+2);

        int source = 2*n*m, sink = 2*n*m+1;
        LP(i,n) LP(j,m) { 
            mf.addEdge(in(i*m+j), out(i*m+j),1);
            if (i == 0 || i == n-1 || j == 0 || j == m-1)
                mf.addEdge(out(i*m+j), sink,1);
        }
        LP(i,n) LP(j,m) {
            int ri = i, rj = j+1, di = i+1, dj = j;
            if (j != m-1) {
                mf.addEdge(out(i*m+j), in(ri*m+rj), 1);
                mf.addEdge(out(ri*m+rj), in(i*m+j), 1);
            } 
            if (i != n-1) {
                mf.addEdge(out(i*m+j), in(di*m+dj), 1);
                mf.addEdge(out(di*m+dj), in(i*m+j), 1);
            }
        }
        LP(i,b) {
            int x, y;   cin >> x >> y;
            x--,y--;
            mf.addEdge(source,in(x*m+y),1);
        }

        int flow = mf.maxFlow(source, sink);
        //debug(flow);
        if (flow == b)  cout << "possible" << endl;
        else cout << "not possible" << endl;
    }
    
    return 0;
}
