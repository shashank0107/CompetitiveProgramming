/*
    Author : manu_sy
    Idea : Iterate through all the points on east bank and find the optimal point on right using ternary.
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

const int N = 1e5+7;

/** Template Ends **/
int n, m, a, b, y[N], y2[N], l[N], idx1, idx2;
double ans = 1e18;

double sq(double x) {   return x * x;   }
double dist(double x1, double y1, double x2, double y2) {
    return sqrt(sq(x1 - x2) + sq(y1 - y2));
}
double d(int i, int j)
{
    double ya = y[i], yb = y2[j];
    double dd = dist(0.0, 0.0, a, ya) + dist(a, ya, b, yb) + l[j];
    if (dd < ans)
    {
        ans = dd;
        idx1 = i, idx2 = j;
    }
    return dd;
}

signed main() {

    IOS;
    cin >> n >> m >> a >> b;
    FOR(i,1,n) cin >> y[i];
    FOR(i,1,m) cin >> y2[i];
    FOR(i,1,m) cin >> l[i];

    FOR(i,1,m)
    {
        int lo = 1, hi = n;
        while (hi - lo > 3)
        {
            int m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
            if (d(m1, i) > d(m2, i))    lo = m1;
            else hi = m2;
        }
        FOR(j,lo,hi) d(j,i);
    }
    cout << idx1 << " " << idx2 << endl;

    return 0;
}
