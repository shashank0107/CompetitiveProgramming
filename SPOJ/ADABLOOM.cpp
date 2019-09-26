/*
    Author : manu_sy

    Idea : Convert the graph to bipartite : 
           For every edge i-j - make edge i-j, j-i in bipartite graph of n to n nodes
           ans in matching/2
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

const int N = 5e3+7;
const int maxN = N;
const int maxint = 1e9+7;

/** Template Ends **/
int n;
ll a[N];

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
    int t;  cin >> t;
    while (t--) {
        cin >> n;
        FOR(i,1,n) cin >> a[i];

        BipartiteMatcher bm(n+1,n+1);
        FOR(i,1,n) FOR(j,i+1,n) {
            ll xr = a[i]^a[j];
            if ( (a[i] > xr && xr > a[j]) || (a[i] < xr && xr < a[j]))
                bm.AddEdge(i, j),
                bm.AddEdge(j, i);
        }
        cout << bm.Solve()/2 << endl;
    } 

    return 0;
}
