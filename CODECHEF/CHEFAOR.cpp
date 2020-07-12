/*
    Author : manu_sy
    Idea : Use divide and conquer
           dp[i][j] : max cost to split first j elements in i groups
                    = max(dp[i - 1][k] + C[k + 1][j]) (k < j)
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
 
const int N = 5e3+7;
const int INF = 1e18 +7;

/** Template Ends **/
int n;
int k;
ll a[N];
ll dp[N][N];
ll c[N][N];
ll opt[N][N];

inline void compute(int i, int l, int r, int ql, int qr) {
    if (l > r)  return;
    int mid = (l + r) >> 1;
    int idx = -1;
    ll val = -INF;
    for (int j = ql; j <= min(qr, mid); ++j) {
        ll tmp = dp[i - 1][j - 1] + c[j][mid];
        if (tmp >= val) {
            val = tmp;
            idx = j;
        }
    }
    dp[i][mid] = val;
    compute(i, l, mid - 1, ql, idx);
    compute(i, mid + 1, r, idx, qr);
}
signed main() {
 
    IOS;
    int t;  cin >> t;
    while (t--) {
        cin >> n >> k;
        FOR(i,1,n) {
            cin >> a[i], dp[1][i] = a[i] | dp[1][i - 1], c[i][i] = a[i];
        }
        FOR(i,1,n) FOR(j,i+1,n) c[i][j] = c[i][j - 1] | a[j];
        FOR(i,2,k) {
            compute(i, 1, n, 1, n);
        }
        cout << dp[k][n] << endl;
    }
    
    return 0;
}
