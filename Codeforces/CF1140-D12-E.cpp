/*
    Author : manu_sy
    Idea : Note the problem can be reduced to no. of ways s.t a[i] != a[i + 2]
          - and this can be reduced to no. of ways such that no two consequtive elements are equal
          - which can be solved using dp
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
 
const int N = 2e5+7;
const int hell = 998244353;

/** Template Ends **/
ll power(ll x, ll y, ll p){ ll res = 1;x = x % p;while (y > 0){ if (y & 1) res = (res*x) % p;y = y>>1;x = (x*x) % p;} return res; } 
int n, k;
int dp1[N][2];  // 0 == n
int dp2[N][2];  // 0 != n
vector<int> v1, v2;

ll solve(vector<int> v) 
{
    int n = v.size();
    vector<PII> t;
    LP(i,n) if (v[i] != -1) t.pb({v[i], i});
    if (t.empty()) 
    {
        return (power(k - 1, n - 1, hell) * k) % hell;
    }
    ll ans = (power(k - 1, t.front().S, hell) * power(k - 1, n - 1 - t.back().S, hell)) % hell;
    FOR(i,1,(int)t.size()-1)
    {
        int len = t[i].S - t[i - 1].S - 1;
        if (t[i].F == t[i - 1].F)
            ans = (ans * dp1[len][0]) % hell;
        else ans = (ans * dp2[len][0]) % hell;
    }
    return ans;
}
 
signed main() {
 
    IOS;
    cin >> n >> k;
    LP(i,n) {
        int x;  cin >> x;
        if (i & 1) v1.pb(x);
        else v2.pb(x);
    }

    dp1[0][1] = 1;
    dp2[0][0] = 1;
    FOR(i,1,n) {
        dp1[i][1] = dp1[i - 1][0];
        dp1[i][0] = ((dp1[i - 1][0] * (k - 2)) % hell + (dp1[i - 1][1] * (k - 1)) % hell) % hell;
        dp2[i][1] = dp2[i - 1][0];
        dp2[i][0] = ((dp2[i - 1][0] * (k - 2)) % hell + (dp2[i - 1][1] * (k - 1)) % hell) % hell;
    }

    cout << (solve(v1) * solve(v2)) % hell << endl;
    return 0;
}
