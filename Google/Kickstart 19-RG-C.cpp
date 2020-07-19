/*
    Author : manu_sy
    Idea : We need to find no. of ways to select mask1 & mask2 s.t mask1 | mask2  == (1 << n) - 1
           and mask1 & mask2 are valid(i.e sum >= h).
           
           So we'll iterate over all valid mask1 in a[] :
           - Find the no. of valid mask2 in b[] s.t all unset bits in mask1 are set in mask1 and other are set or unset.
           - This can be solved using dp sos by represent mask2 by its complement.
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
 
const int N = 20+7;
 
/** Template Ends **/
int n, h;
int a[N];
int b[N];

signed main() {
 
    IOS;
    int t;	cin >> t;
    FOR(tc,1,t) {
    	cin >> n >> h;
    	LP(i,n) cin >> a[i];
    	LP(i,n) cin >> b[i];
    	vector<ll> ways((1 << n), 0);
    	for (int mask = 0; mask < (1 << n); ++mask) {
    		ll sum = 0;
    		for (int bit = 0; bit < n; ++bit) {
    			if (!((mask >> bit) & 1)) {
    				sum += b[bit];
    			}
    		}
    		if (sum >= h) {
    			ways[mask] = 1;
    		}
    	}
    	for (int i = 0; i < n; i++) {
    		for (int mask = 0; mask < (1 << n); mask++) {
    			if ((mask >> i) & 1) {
    				ways[mask] += ways[mask ^ (1 << i)];
    			}
    		}
    	}
    	ll ans = 0;
    	for (int mask = 0; mask < (1 << n); mask++) {
    		ll sum = 0;
    		for (int bit = 0; bit < n; bit++) {
    			if ((mask >> bit) & 1) {
    				sum += a[bit];
    			}
    		}
    		if (sum >= h) {
    			ans += ways[mask];
    		}
    	}
    	cout << "Case #" << tc << ": " << ans << endl;
    }
    return 0;
}
