/*
    Author : manu_sy
    Idea : Each valid substring can be represented in a mask of 20 bits
          - so the problem reduces to finding 2 strings s.t they have no common chars which is easily done using dp_bitmasking 
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
 
/** Template Ends **/
int dp[N], n;
string s;

 
signed main() {
 
    IOS;
    cin >> s;
    n = s.size();
    int mask = 0;

    for (int i = 0, j = 0, mask = 0; i < n; i++)
    {
        while (j < n && ((mask>>(s[j] - 'a')) & 1) == 0)
        {
            mask |= (1 << (s[j] - 'a'));
            j++;
            dp[mask] = max(dp[mask], j - i);
        }
        dp[mask] = max(dp[mask], j - i);
        mask ^= (1 << (s[i] - 'a'));
    }

    for (int mask = 0; mask < (1 << 20); mask++)
    {
        for (int bit = 0; bit < 20; bit++)  if ((mask>>bit)&1)
        {
            dp[mask] = max(dp[mask], dp[mask^(1<<bit)]);
        }
    }

    int ans = 0, tt = (1 << 20) - 1;
    for (int mask = 0; mask < (1 << 20); mask++)
    {
        ans = max(ans, dp[mask] + dp[tt ^ mask]);
    }
    cout << ans << endl;
 
    return 0;
}
