/*
    Author : manu_sy
    Idea : Same as editorial https://codeforces.com/blog/entry/9726
*/
#include "bits/stdc++.h"
using namespace std;

/** Template Begins **/
#define int ll
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

#ifdef LOCAL
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif

/* Debug Ends */

const int N = 1e6+7;

/** Template Ends **/
int n, m, a[N];

bool check(int nds) {

	int edges;
	if (nds & 1) {
		edges = (nds * (nds - 1)) / 2; 
	} else {
		int need = (nds * (nds - 1)) / 2;
		int extra = (nds - 2) / 2;
		edges = need + extra;
	}
	return edges + 1 <= n;
}

signed main() {

    IOS;
    cin >> n >> m;
    LP(i,m) {
    	int u, w;	cin >> u >> w;
    	a[i] = w; 
    }
    sort(a, a + m, greater<int>());

    int cnt = 0;
    for (int i = 1; i <= m; i++) {
    	if (check(i))	cnt = i;
  		else break;
    }
    int ans = 0;
    LP(i, cnt) ans += a[i];
    cout << ans << endl;

    return 0;
}
