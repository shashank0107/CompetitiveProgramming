/*
    Author : manu_sy
    
    Idea :  Binary search over the possible length :
            To check whether an arrangement is possible in indices [s,e] of likeness:
            - Make a bipartite graph with cows on left and barns on right
            - Just make duplicate copies of a barn according to its capacity
            - For each cow make an edge to all the barns within its likeness in range [s,e]
            - Now if the matching size is equal to n, then possible.
    
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

const int N = 1e3+7;
const int B = 20+3;
/** Template Ends **/
int n, b, a[N][B], cap[B];

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

bool found(int s, int e) {

	BipartiteMatcher bm(n, cap[b]);
	for (int i = 0; i < n; i++) {
		for (int j = s; j <= e; j++) {
			for (int k = cap[a[i][j]-1]; k < cap[a[i][j]]; k++)
				bm.AddEdge(i,k);
		}
	}
	if (bm.Solve() == n)	return true;
	else return false;
}

bool check(int len) {

	for (int st = 0; st+len-1 < b; st++) {
		if (found(st, st+len-1)) 	
			return true;
	}
	return false;
}

signed main() {

    IOS;
    cin >> n >> b;
    LP(i,n) LP(j,b) cin >> a[i][j];
    FOR(i,1,b) {
    	cin >> cap[i];
    	cap[i] = min(cap[i], n);
    	cap[i] += cap[i-1];
    }

    int lo = 1, hi = b;
    while (hi - lo > 1) {
    	int mid = (hi+lo)/2;
    	if (check(mid))	hi = mid;
    	else lo = mid;
    }
    if (check(lo))	cout << lo << endl;
    else if (check(hi))	cout << hi << endl;
    else assert(false);

    return 0;
}
