/*
    Author : manu_sy
    Idea : Just have to find for each a[i] if there exists any no. in submask of complement of a[i] which can be easily done using dp_sos.
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
const int K = 24;
const int N = (1 << 24) + 3;

/** Template Ends **/
int n, a[N], dp[N];
 
signed main() {
 
    IOS;
    cin >> n;
    memset(dp, -1, sizeof dp);
    for (int i = 0; i < n; i++) {
    	cin >> a[i];
    	dp[a[i]] = a[i];
    }
    for (int i = 0; i < K; i++) {
    	for (int msk = 0; msk < (1 << K); msk++) {
    		if ((msk >> i) & 1) {
    			if (dp[msk] == -1)	dp[msk] = dp[msk ^ (1 << i)];
    		}
    	}
    }
    for (int i = 0; i < n; i++) {
    	cout << dp[(((1 << K) - 1) ^ a[i])] << " ";
    }

    return 0;
}
