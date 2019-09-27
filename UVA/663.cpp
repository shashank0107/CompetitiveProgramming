/*
    Author : manu_sy
    
    Idea : Goal is to find all the essential edges in the bipartite matching -
          i.e the edges without which the matching size would reduce. 
          Just do that by checking match for each edge removed
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

struct rect {
    int xmn, xmx, ymn, ymx;
}rec[N];

int n, x[N], y[N], ans[N];
vector<int> g[N];
set<int> out[N];

struct BipartiteMatcher {
  vector<vector<int>> G;
  vector<int> L, R, Viz;
  
  BipartiteMatcher(int n, int m) :
  G(n), L(n, -1), R(m, -1), Viz(n) {}
  
  void AddEdge(int a, int b) {
    G[a].push_back(b);
  }
  
  bool Match(int node) {
    if (Viz[node])
      return false;
    Viz[node] = true;
    
    for (auto vec : G[node]) {
      if (R[vec] == -1) {
        L[node] = vec;
        R[vec] = node;
        return true;
      }
    }
    
    for (auto vec : G[node]) {
      if (Match(R[vec])) {
        L[node] = vec;
        R[vec] = node;
        return true;
      }
    }
    
    return false;
  }
  
  int Solve() {
    int ok = true;
    while (ok--) {
      fill(Viz.begin(), Viz.end(), 0);
      for (int i = 0; i < (int)L.size(); ++i)
        if (L[i] == -1)
          ok |= Match(i);
    }
    
    int ret = 0;
    for (int i = 0; i < L.size(); ++i)
      ret += (L[i] != -1);
    return ret;
  }
};

bool lies(int x, int xmn, int xmx) {
    return x > xmn && x < xmx;
}

signed main() {

    IOS;
    int t = 1;
    while (cin >> n) {
        if (n == 0) break;

        LP(i,n) cin >> rec[i].xmn >> rec[i].xmx >> rec[i].ymn >> rec[i].ymx;
        FOR(i,1,n) cin >> x[i] >> y[i];

        BipartiteMatcher bm(n, n+1);
        vector<PII> res;
        LP(i,n) FOR(j,1,n) 
            if (lies(x[j], rec[i].xmn, rec[i].xmx) && lies(y[j], rec[i].ymn, rec[i].ymx))
                bm.AddEdge(i,j);

        LP(i,n) {
            for (int j = 0; j < bm.G[i].size(); j++) {
                int v = *bm.G[i].begin();

                bm.G[i].erase(bm.G[i].begin());

                BipartiteMatcher tempBm(bm);

                if (tempBm.Solve() != n) {
                    res.pb(mp(i,v));
                }
                bm.G[i].pb(v);
            }
        }
        
        sort(all(res));
        cout << "Heap " << t++ << endl;
        if (res.size() != 0) {
            LP(j,res.size()) {
                cout << "(" << (char)(res[j].F+'A') << "," << res[j].S << ")";
                if (j+1 != res.size())  cout << " ";
            } cout << endl;
        } else {
            cout << "none" << endl;
        }
        cout << endl;
    }

    return 0;
}
