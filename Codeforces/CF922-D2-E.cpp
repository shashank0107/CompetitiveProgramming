/*
    Author : manu_sy
    Idea : Similar to editorial - https://codeforces.com/blog/entry/57605
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
 
const int N = 1e3+7, C = 1e4+7;
 
/** Template Ends **/
int n, w, b, x, c[N], cost[N];
int dp[N][C];

signed main() {
 
    IOS;
    cin >> n >> w >> b >> x;
    FOR(i,1,n) cin >> c[i];
    FOR(i,1,n) cin >> cost[i];

    memset(dp, -1, sizeof dp);

    dp[0][0] = w;
    FOR(i,1,n) 
    {
        FOR(j,0,10000)
        {
            FOR(cur,0,min(j,c[i])) if (dp[i - 1][j - cur] != -1)
            {
                int mana = min(dp[i - 1][j - cur] + x, w + (j - cur) * b);
                if (mana >= cur * cost[i])
                    dp[i][j] = max(dp[i][j], mana - cur * cost[i]);
            }
        }
    }
    for (int taken = 10000; taken >= 0; taken--)
        if (dp[n][taken] != -1) {
            cout << taken << endl;
            return 0;
        }
    assert(false);

    return 0;
}
