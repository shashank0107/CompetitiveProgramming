/*
    Author : manu_sy
    Idea : Same as editorial https://codeforces.com/blog/entry/55989
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
 
const int N = 1e6+7;
const int hell = 1e9+7;

/** Template Ends **/
vector<int> p[N];
bool prime[N];

/*** NCR TEMPLATE STARTS ***/

const int MM = 1e6+50;

ll f[MM];
ll inv[MM];

ll power(ll x, ll y, ll p){ ll res = 1;x = x % p;while (y > 0){ if (y & 1) res = (res*x) % p;y = y>>1;x = (x*x) % p;} return res; } 

void comp_fact(){
    f[0]=1;
    for(ll i=1;i<MM;i++)
        f[i]=(f[i-1]*i)%hell;
    inv[MM-1] = power(f[MM-1],hell - 2, hell);
    for(ll i = MM - 2; i >= 0; i--)
        inv[i] = (inv[i + 1]*(i + 1))%hell;
}

ll ncr(ll n, ll r){
    return (((f[n]*inv[r])%hell)*inv[n-r])%hell;
}

/*** NCR TEMPLATE ENDS ***/
void primes()
{
    memset(prime, true, sizeof prime);
    for (int i = 2; i < N; i++) if (prime[i])
    {
        for (int j = i; j < N; j += i)
        {
            prime[j] = false;
            int cnt = 0;
            int temp = j;
            while (temp % i == 0)   temp /= i, cnt++;
            p[j].pb(cnt);
        }
    }
} 

signed main() {
 
    IOS;
    primes();
    comp_fact();
    int q;  cin >> q;
    while (q--)
    {
        int x, y;   cin >> x >> y;
        ll ans = power(2, y - 1, hell);
        for (auto cnt : p[x])  ans = (ans * ncr(cnt + y - 1, y - 1)) % hell;
        cout << ans << endl;
    }

    return 0;
}
