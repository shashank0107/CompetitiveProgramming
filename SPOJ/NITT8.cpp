/*
    Author : manu_sy
    
    Idea : We have to find max value of f(i,j) = |i-j| * min(a[i], a[j])
          - So without loss of generality we can assume for each i -> this is the minimum, now find the maximum frienship
            for this i
          - So for each i we need to find the farthest to its left and to its right which are not less than it and then we 
            can find the max value f(i,j) in which the minimum is present at ith index.
          - Can easily do it using binary search in prefix-max array
          Complexity : O(nlogn)
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

const int N = 1e5+7;

/** Template Ends **/
ll n, a[N], lf[N], rh[N];

ll calc() {
    lf[0] = a[0];
    for (int i = 1; i < n; i++) lf[i] = max(lf[i-1], a[i]);

    ll ret = 0;
    for (int i = 0; i < n; i++) 
    {
        int l = lower_bound(lf, lf + n, a[i]) - lf;
     
        ret = max((i - l) * a[i], ret);
    }
    return ret;
}

signed main() {

    IOS;
    int t;  cin >> t;
    while (t--)
    {
        cin >> n;   
        for (int i = 0; i < n; i++) cin >> a[i];

        ll ans = 0;
        ans = max(ans, calc());
        reverse(a, a+n);
        ans = max(ans, calc());

        cout << ans << endl;
    }

    return 0;
}
