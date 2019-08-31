/*
    Author : manu_sy
    
    Idea : For any given c[i], we can determine all x%d where d is a divisor of c[i].
      
        - For the answer to exist we should be able to determine such c[i]'s such that lcm(c[i]) = k
        - So we these remainders can only be divisors of k
        - So we'll find which all divisors of k can be found using all c[i].
        - if lcm of all the ones found is k, the answer is yes
          else no
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

const int N = 1e6+7;

/** Template Ends **/
int n, k;
int c[N];
bool taken[N];

ll lcm(ll a, ll b) {
    return (a*b)/(__gcd(a,b));
}

signed main() {

    IOS;
    cin >> n >> k;
    LP(i,n) cin >> c[i];

    vector<int> div;
    for (ll i = 1; i*i <= k; i++)
        if (k%i == 0) {
            div.pb(i);
            if (i*i != k) div.pb(k/i);
        }

    assert(div.size() < 5e2);
    for (register int i = 0; i < n; i++) {
        for (register int d = 0; d < div.size(); d++) {
            if (c[i]%div[d] == 0)   taken[d] = true;
        }
    }

    ll ans = 1;
    for (int i = 0; i < div.size(); i++) if (taken[i]) ans = lcm(ans, div[i]);

    //debug(ans);
    if (ans%k == 0) cout << "Yes" << endl;
    else cout << "No" << endl;

    return 0;
}
