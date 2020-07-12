/*
    Author : manu_sy
    Idea : Can easily be solved using dp knuth
           dp[i][j] : cost of splitting blocks i till j
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
 
const int N = 5e6+7;
const int INF = 1e9 +7;

/** Template Ends **/
int n, m;

signed main() {
 
    IOS;
    while (cin >> n >> m) {
        vector<int> v(m + 2, 0);
        FOR(i,1,m) cin >> v[i];
        m++;
        v[m] = n;
        // debug(v, m);
        vector<int> pv(m + 1, 0);
        FOR(i,1,m) pv[i] = pv[i - 1] + v[i] - v[i - 1];
        // debug(pv);
        vector<vector<int> > dp(m + 2, vector<int>(m + 2, INF));
        auto opt = dp;
        FOR(i,1,m) {
            dp[i][i] = 0;
            opt[i][i] = i;
        }
        FOR(len,2,m) {
            FOR(l,1,m-len+1) {
                int r = l + len - 1;
                FOR(k,opt[l][r - 1], min(opt[l + 1][r], r - 1)) {
                    int cur = dp[l][k] + dp[k + 1][r] + pv[r] - pv[l - 1];
                    if (cur <= dp[l][r]) {
                        dp[l][r] = cur;
                        opt[l][r] = k;
                    }
                }
            }
        }
        cout << dp[1][m] << endl;
    }

    return 0;
}
