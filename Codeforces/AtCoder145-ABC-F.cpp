/*
    Author : manu_sy
    Idea : dp[i][j][k] - min operations required to color till ith column &
    					 j is the color of the ith column using k operations

    	 - Observe that it is optimal that final heights will contain only heights which were initially in h[]
    	 - so we have only 300 choices of heights for each column
    	 - Note that it is optimal that :
    	 	dp[i][j][k] updates dp[i+1][h(i+1)][k] with dp[i][j][k] + max(0LL, h[i + 1] - height represented by j)
    	 				 	and dp[i][j][k + 1] with dp[i][j][k]
    	 - Final answer is min(dp[n][j][k]) j <= 300 & k <= K
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
 
const int N = 3e2+7;
const int INF = 1e17+7;

/** Template Ends **/
int dp[N][N][N], n, K, h[N];
vector<int> v;
 
signed main() {
 
    IOS;
    cin >> n >> K;
    FOR(i,1,n) {
    	cin >> h[i];
    	v.pb(h[i]);
    }
    v.pb(0);
    sort(all(v));
    v.resize(unique(all(v)) - v.begin());

    int l = v.size();
    FOR(i,0,n) FOR(j,0,l-1) FOR(k,0,K) dp[i][j][k] = INF;

    dp[0][0][0] = 0;
    FOR(i,0,n-1) FOR(j,0,l-1) FOR(k,0,K)
    {
    	int ch = v[j];
    	int nh = lower_bound(all(v), h[i + 1]) - v.begin();

    	dp[i + 1][nh][k] = min(dp[i+1][nh][k], dp[i][j][k] + max(0LL, h[i + 1] - ch));
    	dp[i + 1][j][k + 1] = min(dp[i + 1][j][k + 1], dp[i][j][k]);
    }
    int ans = INF;
    FOR(j,0,l-1) FOR(k,0,K) ans = min(ans, dp[n][j][k]);
    cout << ans << endl;

    return 0;
}
