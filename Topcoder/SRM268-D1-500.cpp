/*
    Author : manu_sy
    Idea : Just need to find the minimum number of edges to add to graph such that a euler path exists.
          - for each connected component : convert it to euler path using (odd_edges)/2 - 1 edges
          - Join all disjoint components using (components - 1) edges
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

template<class TH> void _dbg(const char *sdbg, TH h){ cerr << sdbg << '=' << h << endl; }

template<class TH, class... TA> void _dbg(const char *sdbg, TH h, TA... a) {
  while(*sdbg!=',') cerr << *sdbg++;
  cerr<<'='<<h<<','; _dbg(sdbg+1, a...);
}

#ifdef LOCALI
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif

/* Debug Ends */

const int C = 26;

/** Template Ends **/

void dfs(int v, vector<vector<int> >& adj, bool vis[], vector<int>& vertex) {
    vis[v] = true;
    vertex.pb(v);
    for (auto nb : adj[v]) if (!vis[nb]) {
        dfs(nb, adj, vis, vertex);
    }
}

int calc(int v, vector<vector<int> >& adj, bool vis[], vector<int> deg) {
    vector<int> vertex;
    dfs(v, adj, vis, vertex);
    
    int odd = 0;
    for (auto v : vertex) if (deg[v]&1) odd++;
    assert(odd%2 == 0);
    return max(0, odd / 2 - 1); 
}

class MaxTrip {
public: 
    int minBuy(string portA, string portB) {

        int n = portA.size();
        vector<vector<int> > adj(C);
        vector<int> deg(C, 0);
        bool present[C] = {false}, vis[C] = {false};
        for (int i = 0; i < n; i++) {
            int a = portA[i] - 'A', b = portB[i] - 'A';
            adj[a].pb(b);
            adj[b].pb(a);
            deg[a]++, deg[b]++;
            present[a] = present[b] = true;
        }

        int comps = 0;
        int ans = 0;
        for (int i = 0; i < C; i++) if (present[i] && !vis[i]) {
            comps++;
            ans += calc(i, adj, vis, deg);
        } 
        return ans + (comps - 1);
    }
};
