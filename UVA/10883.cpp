/*
    Author : manu_sy
    Idea : Same as https://algorithmist.com/wiki/UVa_10883_-_Supermean
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
 
const int N = 5e5+7;
 
/** Template Ends **/
int n;
double a[N];
double ncr[N];
 
signed main() {
 
    IOS;
    int t;	cin >> t;
    cout << fixed << setprecision(3);

    FOR(tc,1,t) {
    	cin >> n;
    	double ans = 0, comb = 0;

    	LP(i,n) {
    		double x;	cin >> x;
    		double tmp = log2(fabs(x));
    		if (i) {
    			comb += log2(double(n - i) / i);
    			tmp += comb;
    		}

    		if (x >= 0)	ans += pow(2, tmp - n + 1);
    		else ans -= pow(2, tmp - n + 1);
    	}

    	cout << "Case #" << tc << ": " << ans << endl;
    }
 
    return 0;
}
