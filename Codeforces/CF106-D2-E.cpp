/*
    Author : manu_sy
    Idea : 3 Ternary Searches. Same as editorial - https://codeforces.com/blog/entry/2493
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
#define y0 	y12312
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
const int II = 50;
const double X = 1e4;
/** Template Ends **/
int n;
double x[N], y[N], z[N], x0, y0, z0, ans, xa, ya, za;

inline double sq(double x){ return x * x; }
double distance(double x1, double y1, double z1, double x2, double y2, double z2) {
	return sq(x1 - x2) + sq(y1 - y2) + sq(z1 - z2);
}
double fz(double cz)
{
	z0 = cz;
	double dist = -1e18;
	LP(i,n) dist = max(distance(x[i], y[i], z[i], x0, y0, z0), dist);
	if (dist < ans)
	{
		ans = dist;
		xa = x0, ya = y0, za = z0;
	}
	return dist;
}
double fy(double cy)
{
	y0 = cy;
	double lo = -X, hi = X;
	LP(itr,II)
	{
		double m1 = (2 * lo + hi) / 3, m2 = (lo + 2 * hi) / 3;
		if (fz(m1) < fz(m2))	hi = m2;
		else lo = m1;
	}
	return fz((lo + hi) / 2);
}
double fx(double cx)
{
	x0 = cx;
	double lo = -X, hi = X;
	LP(itr,II)
	{
		double m1 = (2 * lo + hi) / 3, m2 = (lo + 2 * hi) / 3;
		if (fy(m1) < fy(m2))	hi = m2;
		else lo = m1;
	}
	return fy((lo + hi) / 2);
}

signed main() {

    IOS;
    cout << fixed << setprecision(15);
    cin >> n;
    LP(i,n) cin >> x[i] >> y[i] >> z[i];

    double lo = -X, hi = X;
    ans = 1e18;
    LP(itr,II)
    {
    	double m1 = (2 * lo + hi) / 3, m2 = (lo + 2 * hi) / 3;
    	if (fx(m1) < fx(m2))	hi = m2;
    	else lo = m1;
    }
    fx((lo + hi) / 2);
    debug(ans);
    cout << xa << " " << ya << " " << za;

    return 0;
}
