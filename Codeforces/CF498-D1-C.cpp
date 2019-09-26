/*
    Author : manu_sy
    
    Idea : Just make a graph where each vertex a[i] is represented as a list of vertices representing its prime factorization :
         So if a[i] = p1^a * p2^b . Then i is represented as two nodes p1 and p2 with capacities a and b.
         Now if i is odd connect to source else to sink
         For each pair - make edge with INF capacity btw all same prime factors 
         Find maxflow
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

const int N = 1e2+7;
const int INF = 1e9+7;

/** Template Ends **/
int n, m, a[N], r[N];
vector<PII> p;


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
    void addEdge(int s, int e, int capacity) {
        adj[s].pb(e);
        adj[e].pb(s);
        cap[s][e] = capacity;
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
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 1; i <= n; i++) {

        for (int j = 2; 1LL*j*j <= a[i]; j++) {
            if (a[i]%j == 0) {
                int cnt = 0;
                while (a[i]%j == 0) a[i] /= j, cnt++;
                p.pb(mp(j,cnt));
            }
        }
        if (a[i] > 1)   p.pb(mp(a[i],1));
        r[i] = p.size();
    }
    int nn = p.size();
    MF mf(nn+2);
    int source = nn, sink = nn+1;

    while (m--) {
        int a, b;   cin >> a >> b;
        if (b&1)    swap(a,b);
        for (int i = r[a-1]; i < r[a]; i++)
            for (int j = r[b-1]; j < r[b]; j++)
                if (p[i].F == p[j].F) 
                    mf.addEdge(i,j,INF);
    }
    for (int i = 1; i <= n; i++) {
        if (i&1) {
            for (int l = r[i-1]; l < r[i]; l++)
                mf.addEdge(source, l, p[l].S);
        } else {
            for (int l = r[i-1]; l < r[i]; l++)
                mf.addEdge(l, sink, p[l].S);
        }
    }
    cout << mf.maxFlow(source, sink) << endl;

    return 0;
}
