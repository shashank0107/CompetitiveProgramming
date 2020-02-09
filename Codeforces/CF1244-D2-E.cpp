/*
    Author : manu_sy
    Idea : ternary search for the point x from where the size of subsegment you choose is minimum.
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

const int N = 1e5+7, INF = 1e17;

/** Template Ends **/
int n, a[N], k;

int f(int pos) {
    int r = k, high = -1e18;
    int left = 0;
    for (left = 0; left < n && a[left] < pos; left++)
        r -= (pos - a[left]);
    if (r < 0)  return 9*INF;

    for (int i = n - 1; a[i] > pos; i--)
    {
        int next = a[i - 1], cnt = (n - i);
        if (cnt * (a[i] - next) <= r)
        {
            r -= cnt * (a[i] - next);
        }
        else
        {
            int steps = r / cnt;
            high = max(a[i] - steps, pos);
            r = 0;
            break;
        }
    }
    if (high == -1e18) high = pos;
    return max(high - pos, 0LL);
}
signed main() {

    IOS;
    cin >> n >> k;
    LP(i,n) cin >> a[i];
    sort(a, a + n);

    int lo = a[0], hi = a[n - 1];
    while (hi - lo > 3)
    {
        int m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
        if (f(m1) > f(m2)) lo = m1;
        else hi = m2;
    }
    int ans = 1e18;
    FOR(i,lo,hi) ans = min(ans, f(i));
    cout << ans << endl;

    return 0;
}
