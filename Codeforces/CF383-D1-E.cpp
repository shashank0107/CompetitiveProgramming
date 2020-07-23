/*
    Author : manu_sy
    Idea : For answer of each query - find answer in terms of complement.
           - The complement can be easily calculated using dp_sos
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
 
const int N = (1 << 25) +7;
 
/** Template Ends **/
int n, dp[N];
 
signed main() {
 
    IOS;
    cin >> n;
    LP(i,n) {
    	string s;	cin >> s;
    	int mask = 0;
    	for (auto i : s) mask |= (1 << (i - 'a'));
    	dp[mask]++;
    }
    LP(i,24) {
    	LP(mask,(1 << 24)) {
    		if ((mask >> i) & 1)
    			dp[mask] += dp[mask ^ (1 << i)];
    	}
    }
    ll ans = 0;
    LP(mask,(1 << 24)) {
    	ll cur = (n - dp[mask]) * 1ll * (n - dp[mask]);
    	ans ^= cur;
    }
    cout << ans << endl;

    return 0;
}
