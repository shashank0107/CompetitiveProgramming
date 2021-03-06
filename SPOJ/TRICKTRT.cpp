/*
    Author : manu_sy
    Idea : ternary search
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
int n;
double x[N], y[N];

double sq(double x) {
    return x * x;
}
double dist(double x1, double y1, double x2, double y2) {
    return sqrt(sq(x1 - x2) + sq(y1 - y2));
}
double f(double xx) {
    double ret = 0;
    LP(i,n) ret = max(ret, dist(x[i], y[i], xx, 0));
    return ret;
}

signed main() {

    IOS;
    cout << fixed << setprecision(15);
    while (cin >> n)
    {
        if (!n) break;
        LP(i,n) cin >> x[i] >> y[i];

        double lo = -2e5, hi = 2e5;
        int itr = 70;
        while (itr--)
        {
            double m1 = lo + (hi - lo) / 3, m2 = lo + 2 * (hi - lo) / 3;
            if (f(m1) >= f(m2))  lo = m1;
            else hi = m2;
        } 
        cout << (hi + lo) / 2 << " " << f((hi + lo) / 2) << endl;
    }

    return 0;
}
