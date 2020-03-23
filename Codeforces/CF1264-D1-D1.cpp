/*
    Author : manu_sy
    Idea : same as the editorial 
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
 
const ll N = 2e3+7, hell = 998244353;
 
/** Template Ends **/
ll power(ll x, ll y, ll p){ ll res = 1;x = x % p;while (y > 0){ if (y & 1) res = (res*x) % p;y = y>>1;x = (x*x) % p;} return res; } 

ll dp[N][N], n, p[N];
string s;
 
ll calc(int i, int j) {
    if (i >= j) return 0;
    ll &ret = dp[i][j];
    if (ret != -1)  return ret;
    ret = 0;
    if (s[i] != '(') {
        ret = calc(i + 1, j);
    }
    if (s[j] != ')') {
        ret = (ret + calc(i, j - 1)) % hell;
    }
    if (s[i] != '(' && s[j] != ')') {
        ret = (ret - calc(i + 1, j - 1) + hell) % hell;
    }
    if (s[i] != ')' && s[j] != '(') {
        ret = (ret + calc(i + 1, j - 1) + power(2, p[j-1] - p[i], hell)) % hell;
    }
    return ret;
}

signed main() {
 
    IOS;
    cin >> s;
    n = s.size();
    s = 'a' + s;
    FOR(i,1,n) p[i] = p[i - 1] + (s[i] == '?');
    memset(dp, -1, sizeof dp);
    cout << calc(1, n) << endl;    
 
    return 0;
}
