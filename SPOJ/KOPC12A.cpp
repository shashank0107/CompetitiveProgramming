/*
    Author : manu_sy
    Idea : Ternary Search
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
int n, h[N], c[N];

int f(int x) {
    int ret = 0;
    LP(i,n) ret += c[i] * abs(h[i] - x);
    return ret;
}

signed main() {

    IOS;
    int t;  cin >> t;
    while (t--)
    {
        cin >> n;
        LP(i,n) cin >> h[i];
        LP(i,n) cin >> c[i];

        int lo = 0, hi = 10000;
        while (hi - lo > 3)
        {
            int m1 = lo + (hi - lo) / 3, m2 = lo + (2 * (hi - lo)) / 3;
            if (f(m1) >= f(m2)) lo = m1;
            else hi = m2;
        }
        int sIdx = -1, cst = 1e18;
        FOR(i,lo,hi) if (f(i) < cst) cst = f(i), sIdx = i;
        cout << cst << endl;
    }

    return 0;
}
