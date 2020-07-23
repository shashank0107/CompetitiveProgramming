/*
    Author : manu_sy
    Idea : So for each i - answer is max(ans[0..i-1] or calc(i)]
           where calc(i) is the sum of a[k1] + a[k2] where k1, k2 are submasks of i and they are largest of them
          - This can be easily calculated using dp sos.
*/
#include "bits/stdc++.h"
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
 
#ifdef LOCAL
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif
 
/* Debug Ends */
const int M = 19 + 1;
const int N = (1 << 19) + 7;
 
/** Template Ends **/
int n, a[N];
vector<int> dp[N];

 
signed main() {
 
    IOS;
    cin >> n;
    int m = (1 << n);
    for (int i = 0; i < m; i++) {
    	int x;	cin >> x;
    	dp[i].pb(x);
    }
    auto comb = [&] (vector<int> a, vector<int> b) {
    	a.insert(a.end(), all(b));
    	sort(all(a), greater<int>());
    	a.resize(2);
    	return a;
    };
    for (int i = 0; i < n; i++) {
    	for (int msk = 0; msk < m; msk++) {
    		if ((msk >> i) & 1) {
    			dp[msk] = comb(dp[msk], dp[msk ^ (1 << i)]);
    		}
    	}
    }
    int mx = 0;
    for (int i = 1; i < m; i++) {
    	debug(dp[i]);
    	int cur = dp[i][0] + dp[i][1];
    	mx = max(cur, mx);
    	cout << mx << endl;
    }
 
    return 0;
}
