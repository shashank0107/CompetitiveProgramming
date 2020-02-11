/*
    Author : manu_sy
    Idea : We will try to make water reach point x, y from every side in minimum time
          - Observe that for a given line the time to reach from a point on line to (x,y) follows order : dec-inc
          - So we can use ternary search for calculating min time for water to reach from side with end (p1, p2)
*/
#include "bits/stdc++.h"
using namespace std;

/** Template Begins **/

typedef long long        ll;
typedef pair<double, double>    PII;

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

#ifdef LOCALI
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif

/* Debug Ends */

const int N = 1e5+7;
const int ITR = 100;
/** Template Ends **/

int n, xx, yy;
PII p[N];
double ans, v, c;

double dcmp(double a, double b) {
    return abs(a - b) < 1e-12 ? 0 : (a > b ? 1 : -1);
}
double sq(double x) {
    return x * x;
}
double dist(double x1, double y1, double x2, double y2) {
    return sqrt(sq(x1 - x2) + sq(y1 - y2));
}
double getY(double xc, PII p1, PII p2) {
    return p1.S + (((p2.S - p1.S) / (p2.F - p1.F)) * (xc - p1.F));
}
double f(PII p) {
    double xc = p.F, yc = p.S;
    double tme = (dist(xc, yc, xx, yy) / c) + yc / v;        
    double ret = max(tme, (yy*1.0) / v);
    ans = min(ans, ret);
    return ret;
}
void doX(PII p1, PII p2) {
    double lo = p1.F, hi = p2.F;
    int itr = ITR;
    while (itr--)
    {
        double m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
        if (f(mp(m1, getY(m1, p1, p2))) < f(mp(m2, getY(m2, p1, p2))))  hi = m2;
        else lo = m1;
    }
    f(mp((hi + lo) / 2, getY((hi + lo)/2, p1, p2)));
}
void doY(PII p1, PII p2) {
    if (p1.S > p2.S)    swap(p1, p2);
    double lo = p1.S, hi = p2.S;
    int itr = ITR;
    while (itr--)
    {
        double m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
        if (f(mp(p1.F, m1)) < f(mp(p1.F, m2)))    hi = m2;
        else lo = m1;
    }
    f(mp(p1.F, (hi + lo)/2));
}
void check(PII p1, PII p2) {
    if (p1.F > p2.F)    swap(p1, p2);
    double dx = p2.F - p1.F;
    if (dcmp(dx,0) == 0)    doY(p1, p2);
    else doX(p1, p2);
}
signed main() {

    IOS;
    cout << fixed << setprecision(4);
    while (cin >> n >> xx >> yy >> v >> c)
    {
        if (n == 0) break;
        LP(i,n) cin >> p[i].F >> p[i].S;
        ans = 1e18;

        LP(i,n) check(p[i], p[(i + 1) % n]);
        cout << ans << endl;
    }
    return 0;
}
