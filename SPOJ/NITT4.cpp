/*
    Author : manu_sy
    
    Idea : We need to find a way to place the maximum no. of 1*2 blocks in the given grid.
           Visualize it a bipartite graph as follows : 
           - all the vertices with (i+j)%2 == 0 are on left side
           - the above vertices can be matched with neighbouring vertices (who definately have (i+j)%2 == 1) who are on right side
           
           Just find the maximum matching to get the maximum no. of 1*2 blocks that can be placed.
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
 
const int N = 1e4+10;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
 
/** Template Ends **/
int n, m, b;
bool valid[N];

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
 
signed main() {
 
    IOS;
    cin >> n >> m >> b;
 	  BipartiteMatcher bm(n*m+5, n*m+5);

    memset(valid, true, sizeof valid);
    for (int i = 0; i < b; i++) {
        int x, y;   cin >> x >> y;
        valid[x*m+y] = false;
    }
 
    LP(i,n) LP(j,m) if (valid[i*m+j]) {
        if ((i+j)%2 == 0) {
            for (int k = 0; k < 4; k++) {
                int nx = i+dx[k], ny = j+dy[k];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && valid[nx*m+ny]) {
                    bm.AddEdge(i*m+j, nx*m+ny);
                }
            }
        }
    }
    int mf = bm.Solve();
 
    if ((n*m-b)%2 == 0 && mf == (n*m-b)/2) {
        cout << "Yes" << endl;
    } else {
        cout << "No " << n*m-b-2*mf << endl;
    }
 
    return 0;
}
