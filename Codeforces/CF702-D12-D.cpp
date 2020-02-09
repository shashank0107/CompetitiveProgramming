/*
    Author : manu_sy
    Idea : ternary search on distance travelled by car and minimize time
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

const int N = 1e5+7;

/** Template Ends **/
int d, k, a, b, t, ans;

int allC() {
    int stops = d / k;
    if (d % k == 0) stops--;
    return d * a + stops * t;
}

int f(int p) {
    int s1 = k * p;
    int s2 = d - s1;
    int t1 = s1 * a + (p > 0 ? (p - 1) * t : 0);
    int t2 = s2 * b;
    return t1 + t2;
}

signed main() {

    IOS;
    cin >> d >> k >> a >> b >> t;
    ans = min(d * b, allC());

    int lo = 0, hi = d / k;
    while (hi - lo > 3)
    {
        int m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
        if (f(m1) <= f(m2))  hi = m2;
        else lo = m1;
    }
    FOR(i,lo,hi) ans = min(ans, f(i));
    cout << ans << endl;

    return 0;
}
