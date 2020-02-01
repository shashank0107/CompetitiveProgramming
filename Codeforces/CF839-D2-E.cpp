/*
    Author : manu_sy
    Idea : Same as editorial - https://codeforces.com/blog/entry/53815
*/
#include "bits/stdc++.h"
using namespace std;

/** Template Begins **/
#define int              ll
#define double           long double 
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

const int N = 5e6;

/** Template Ends **/
int n, k, e, dp[N];
ll adj[N];
double ans;
set<PII> s;

int maxClique() {
    int mid = n / 2, tmask = (1LL << mid) - 1;
    for (int mask = 0; mask < (1LL << mid); mask++) 
    {
        int x = mask;
        for (int bit = 0; bit < mid; bit++) 
        {
            if ((mask >> bit) & 1LL)  x &= (adj[bit] & tmask);
        }
        if (x == mask)  dp[mask] = __builtin_popcount(mask);
    }
    for (int mask = 0; mask < (1LL << mid); mask++)
        for (int bit = 0; bit < mid; bit++)
            if ((mask >> bit) & 1LL)    
                dp[mask] = max(dp[mask], dp[mask ^ (1LL << bit)]);

    int ret = 0;
    for (int mask = 0; mask < (1LL << (n - mid)); mask++)
    {
        int x = mask;
        for (int bit = 0; bit < n - mid; bit++)
        {
            if ((mask >> bit) & 1LL) x &= (adj[bit + mid] >> mid);
        }
        if (x != mask)  continue;
        int nmask = tmask;
        for (int bit = 0; bit < n - mid; bit++)
        {
            if ((mask >> bit) & 1LL) nmask &= adj[bit + mid] & tmask;
        }
        ret = max(ret, __builtin_popcount(mask) + dp[nmask]);
    }
    return ret;
}

signed main() {

    IOS;
    cin >> n >> k;
    LP(i,n) {
        LP(j,n) {
            int x;  cin >> x;
            if (x)    adj[i] ^= (1LL << j);
        } 
        adj[i] ^= (1LL << i);
    }
    double ans = maxClique();
    cout << fixed << setprecision(10) << (k * k * (ans - 1)) / (2 * ans) << endl;

    return 0;
}
