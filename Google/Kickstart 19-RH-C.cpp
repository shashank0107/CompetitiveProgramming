/*
    Author : manu_sy
    Idea : - dp[i][j][k] - true if possible to reach till i (inclusive) with mod alternate sum = j 
             and no. of even positions used = k
           - similar to https://github.com/farmerboy95/CompetitiveProgramming/blob/master/Google%20Kickstart/Kickstart%2019-RH-C.cpp
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
 
#ifdef LOCALi
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif
 
/* Debug Ends */
 
const int N = 5e6+7;
 
/** Template Ends **/
bool dp[12][12][250];
int a[N], s[N];

signed main() {
 
    IOS;
    int t;  cin >> t;
    FOR(tt,1,t)
    {
        memset(dp, false, sizeof dp);
        dp[0][0][0] = 1;

        int tot = 0;
        FOR(i,1,9) 
        {
            cin >> a[i];
            if (a[i] >= 20) a[i] = (a[i] & 1 ? 21 : 20);
            tot += a[i], s[i] = a[i] + s[i - 1];
        }

        int te = tot / 2, to = (tot + 1) / 2;
        FOR(i,0,8) FOR(j,0,10) FOR(k,0,te) if (dp[i][j][k])
        {
            int odu = s[i] - k;
            FOR(e,0,a[i + 1])
            {
                int ne = k + e;
                int no = odu + a[i + 1] - e;

                if (ne <= te && no <= to)
                {
                    int m = (((j + (i + 1) * (a[i + 1] - e - e)) % 11) + 11) % 11;
                    dp[i + 1][m][ne] = 1; 
                }
            }
        }

        cout << "Case #" << tt << ": ";
        cout << (dp[9][0][te] ? "YES" : "NO") << endl;
    }
 
    return 0;
}
