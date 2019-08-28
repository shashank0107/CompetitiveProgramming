/*
    Author : manu_sy
    Idea : Same as 
        http://www.apfloat.org/prim.html
*/
#include <bits/stdc++.h>
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
#define FOR(i,a,b)  for(int i=a;i<=b;i++)

/* Debug */
template<class L, class R> ostream &operator<<(ostream &os, pair<L,R> P) {
  return os << "(" << P.st << "," << P.nd << ")";
} 
template<class T> ostream &operator<<(ostream& os, vector<T> V) {
  os << "["; for (auto vv : V) os << vv << ","; return os << "]";
}
template<class TH> void _dbg(const char *sdbg, TH h){ cerr<<sdbg<<'='<<h<<endl; }
template<class TH, class... TA> void _dbg(const char *sdbg, TH h, TA... a) {
  while(*sdbg!=',')cerr<<*sdbg++;
  cerr<<'='<<h<<','; _dbg(sdbg+1, a...);
}
#ifdef LOCAL
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif
/* Debug Ends */

const int N = 1e5+7;

/** Template Ends **/
int p, q, r;

vector<int> calc_pf (int n) {
    vector<int> ans;
    int nn = sqrt(n);
    vector<bool> prime(nn+3, true);

    for (ll i = 2; i*i <= n; i++) {
        if (prime[i]) {
            ans.pb(i);
            for (ll j = i*i; j <= nn; j+=i) prime[j] = false;   
            while (n%i == 0)    n/=i;
        }
    }
    if (n > 1)  ans.pb(n);
    //debug(n, ans);
    return ans;
}
ll power(ll x, ll y, ll p){ ll res = 1;x = x % p;while (y > 0){ if (y & 1) res = (res*x) % p;y = y>>1;x = (x*x) % p;} return res; } 

signed main() {

    IOS;
    while (cin >> p >> q) {
        if (p == 0 && q == 0)   break;

        vector<int> pf = calc_pf(p-1);

        while (q--) {
            cin >> r;

            bool valid = true;
            for (auto i : pf) {
                if (power(r, (p-1)/i, p) == 1) {
                    valid = false;
                    break;
                }
            }
            cout << (valid ? "YES" : "NO") << endl;
        }
    }

    return 0;
}
