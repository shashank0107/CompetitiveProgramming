/*
    Author : manu_sy
    Idea : Simple ternary search
*/
#include "bits/stdc++.h"
using namespace std;

/** Template Begins **/
#define double long double
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
int n, d;
double r[N], c[N];

double dcmp(double a, double b) {
    return abs(a - b) < 1e-12 ? 0 : a > b ? 1 : -1;
}
double f(double rd) {
    double tmin = 1e18;
    LP(i,n-1) tmin = min(tmin, (rd/r[i]) + ((d - rd)/c[i]));
    double tt = (rd/r[n-1]) + ((d - rd)/c[n-1]);
    return tmin - tt;
}

signed main() {

    IOS;
    cout << fixed << setprecision(2);
    while (cin >> d)
    {
        cin >> n;
        LP(i,n) cin >> r[i] >> c[i];

        double lo = 0, hi = d;
        int itr = 5000;
        while (itr--)
        {
            double m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
            if (f(m1) <= f(m2)) lo = m1;
            else hi = m2;
        }
        lo = (hi + lo) / 2;
        double ans = f((hi + lo) / 2);
        if (dcmp(f(0),ans) > ans) lo = 0, ans = f(0);
        if (dcmp(f(d),ans) > ans) lo = d, ans = f(d);

        if (dcmp(ans,0) >= 0)
        {
            cout << "The cheater can win by " << llround(ans*60*60) << " seconds with r = " << lo << "km and k = " << d - lo << "km." << endl;
        }
        else 
        {
            cout << "The cheater cannot win." << endl;
        }
    }

    return 0;
}
