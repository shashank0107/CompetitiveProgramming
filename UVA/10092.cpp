/*
    Author : manu_sy
    
    Idea : Model it as a flow problem -
        - Source is connected to all category nodes (1 till nk) with edges weighted by their capacity.
        - All category are connected to their problem with capacity 1.
        - All problems are connected to sink with capacity 1.
        
        If flow from source to sink is equal to the summation of capacity of problems then answer exists else no.
        To check if a problem has been assigned to category just check in final state 
        - if cap[problem][category] (reverse edge) is 1.

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
const int INF = 1e8;

/** Template Ends **/
int nk, np;

struct MF {
    int n;
    vector<vector<int> > adj;
    vector<vector<int> > cap;

    MF(int nn) {
        n = nn;
        adj.resize(n);
        cap = vector<vector<int> >(n, vector<int>(n, 0));
    }
    void insertEdge(int s, int e, int capacity) {
        adj[s].pb(e);
        adj[e].pb(s);
        cap[s][e] = capacity;
    }
    int bfs(int st, int en, vector<int>& parent) {
        fill(all(parent), -1);
        parent[st] = -2;
        queue<PII> q;
        q.push(mp(st, INF));

        while (!q.empty()) {
            auto p = q.front();    q.pop();
            int cur = p.first;
            int flow = p.second;

            for (int nb : adj[cur]) {
                if (parent[nb] == -1 && cap[cur][nb]) {
                    parent[nb] = cur;
                    int newflow = min(flow, cap[cur][nb]);
                    if (nb == en)
                        return newflow;
                    q.push(mp(nb, newflow));
                }
            }

        }
        return 0;
    }
    int maxflow(int source, int sink) {
        int flow = 0;
        vector<int> parent(n);
        int newflow;

        while (newflow = bfs(source, sink, parent)) {
            flow += newflow;

            int cur = sink;
            while (cur != source) {
                int prev = parent[cur];
                cap[prev][cur] -= newflow;
                cap[cur][prev] += newflow;
                cur = prev;
            }
        }
        return flow;
    }
};

signed main() {

    IOS;
    while (cin >> nk >> np) {
        if (nk == 0 && np == 0) break;
        
        MF mf(nk+np+2);
        
        int need = 0;
        for (int i = 1; i <= nk; i++) {
            int capacity;   cin >> capacity;
            mf.insertEdge(0, i, capacity);
            need += capacity;
        }

        for (int i = 1; i <= np; i++) {
            int t;  cin >> t;
            while (t--) {
                int c;  cin >> c;
                mf.insertEdge(c, nk+i, 1);
            }
            mf.insertEdge(nk+i, nk+np+1, 1);
        }
        
        int maxflow = mf.maxflow(0, nk+np+1);
        if (maxflow == need) {
            cout << 1 << endl;
            for (int i = 1; i <= nk; i++) {
                bool first = true;
                for (int j = 1; j <= np; j++) {
                    if (mf.cap[nk+j][i] == 1) {
                        if (first)  cout << j, first = false;
                        else cout << " " << j;
                    }
                }
                cout << endl;
            }
        } 
        else cout << 0 << endl;
    }

    return 0;
}
