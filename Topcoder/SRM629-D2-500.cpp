/*
    Author : manu_sy
    Idea : ternary search. Note that f first decreases then increases
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
const double EPS = 1e-15;
/** Template Ends **/

long double f(double d, vector<int> v, vector<int> w) {
    double res = 0;
    LP(i,v.size()) {
        res += abs(v[i] * d - w[i]);
    }
    return res;
}

class CandyMaking{
public:
    double findSuitableDensity(vector <int> v, vector <int> w) {
        int n = v.size();
        double lo = 0, hi = 1e9;
        int itr = 300;
        while (itr--)
        {
            double m1 = lo + ((hi - lo) / 3), m2 = lo + ((2 * (hi - lo)) / 3);
            if (f(m1, v, w) > f(m2, v, w))  lo = m1;
            else hi = m2;
        }
        return f((lo+hi)/2, v, w);
    }
};
