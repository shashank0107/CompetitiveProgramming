/*
    Author : manu_sy
    Idea : Same as editorial. Getting TLE though (i think by a small margin)
*/
#include "bits/stdc++.h"
using namespace std;

/** Template Begins **/
// #define int ll
typedef long long        ll;
typedef pair<int,ll>    PII;
typedef vector<int>      vi;

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
 
const int N = 1e3+7;
 
/** Template Ends **/
ll n, k, a[N], d;
vector<ll> dv;
vector<int> primes;
PII dp[N][7 * N];
int taken[N][7 * N];

int idx(ll e)
{
    return lower_bound(all(dv), e) - dv.begin();
}
PII add(PII& a, PII b) {
    return {a.F + b.F, a.S + b.S};
}
signed main() {

    IOS;
    cin >> n >> k;
    FOR(i,1,n) cin >> a[i];
    if (k == 1) {
        cout << 1 << endl << 1 << endl;
        return 0;
    }
    
    for (ll i = 1; i * i <= k; i++) {
        if (k % i == 0) {
            dv.pb(i);
            if (k / i != i) dv.pb(k / i);
        }
    }
    sort(all(dv));
    d = dv.size();

    debug(dv.size());
    FOR(i,0,n) FOR(j,0,d) dp[i][j] = {1e9, 1e18};
    dp[0][0] = {0, 0};

    FOR(i,1,n) FOR(j,0,d-1)
    {
        ll cur = dv[j];
        ll pr = cur / __gcd(a[i], cur);
        int pridx = idx(pr);
        dp[i][j] = dp[i - 1][j];

        if (dp[i][j] > add(dp[i - 1][pridx], {1, a[i]}))    
            dp[i][j] = add(dp[i - 1][pridx], {1, a[i]}),
            taken[i][j] = 1;
        // debug(i, j, dp[i][j], taken[i][j]);
    }
    if (dp[n][idx(k)].F == 1e9) {
        cout << -1 << endl;
        return 0;
    }
    vector<ll> ans;
    ll cur = k;
    for (int i = n; i >= 1; i--) {
        if (taken[i][idx(cur)]) {
            ans.pb(i);
            ll contrib = __gcd(a[i], cur);
            cur = cur / contrib;
        }
    }
    cout << ans.size() << endl;
    for (auto i : ans) cout << i << " "; cout << endl;
 
    return 0;
}
