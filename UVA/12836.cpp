/*
    Author : manu_sy
    Idea : - power at i : lis[i] + lds[i] - 1 (longest inc subsequence ending at i , longest decreasing subsequence from i) 
           - Then use dp knuth to optimize dp
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
 
#ifdef LOCALi
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif
 
/* Debug Ends */
 
const int N = 5e6+7;
const int INF = 1e18;
/** Template Ends **/

 
signed main() {
 
    IOS;
    int t;  cin >> t;
    int tc = 1;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n);
        LP(i,n) cin >> a[i];
        auto get_lis = [] (vector<int> a) {
            vector<int> v;
            vector<int> lis;
            for (auto i : a) {
                int idx = lower_bound(all(v), i) - v.begin();
                if (idx == v.size()) {
                    v.pb(i);
                } else {
                    v[idx] = i;
                }
                lis.pb(idx + 1);
            }
            debug(a, lis);
            return lis;
        };
        vector<int> lis = get_lis(a);
        reverse(all(a));
        vector<int> lds = get_lis(a);
        reverse(all(a));
        reverse(all(lds));
        vector<int> p(n);
        LP(i,n) p[i] = (i ? p[i - 1] : 0) + lis[i] + lds[i] - 1;
        debug(p);

        vector<vector<int> > dp(n, vector<int>(n, INF));
        auto opt = dp;
        LP(i,n) {
            dp[i][i] = 0;
            opt[i][i] = i;
        }
        FOR(len,2,n) {
            LP(l,n-len+1) {
                int r = l + len - 1;
                FOR(k, opt[l][r - 1], min(opt[l + 1][r], r-1) ) {
                    int cur = dp[l][k] + dp[k + 1][r] + p[r] - (l > 0 ? p[l - 1] : 0);
                    if (cur <= dp[l][r]) {
                        dp[l][r] = cur;
                        opt[l][r] = k;
                    }
                }
                debug(l, r, dp[l][r]);
            }
        }
        cout << "Case " << tc++ << ": " << dp[0][n - 1] << endl;
    }
 
    return 0;
}
