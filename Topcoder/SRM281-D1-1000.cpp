/*
    Author : manu_sy
    Idea : Use nested ternary search :
          - First on the distance between points and then on the starting point
*/
#include "bits/stdc++.h"
using namespace std;
 
/** Template Begins **/
#define int long long 
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
 
/** Template Ends **/

class Equidistance {
public:
#undef int
    long long minimumEffort(vector <int> a) {
#define int long long
        int n = a.size();
        sort(a.begin(), a.end());
        if (n == 1) return 0;
        if (n == 2) return (a[0] != a[1] ? 0 : 1);

        // dist is fixed - now find answer
        auto f = [&] (ll dist) {
            
            // m is the start point
            auto calc = [&] (ll m) {
                ll ret = 0;
                for (int i = 0; i < n; i++)
                    ret += abs(a[i] - (m + i * dist) );
                return ret;
            };

            ll lo = -1e14, hi = 1e14;
            while (hi - lo > 3) {
                ll m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
                if (calc(m1) > calc(m2))  lo = m1;
                else hi = m2;
            }
            ll ans = 1e18;
            for (int i = lo; i <= hi; i++)  ans = min(ans, calc(i));
            // debug(dist, ans);
            return ans;
        };

        ll lo = 1, hi = 4e14;
        while (hi - lo > 3) {
            ll m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
            if (f(m1) > f(m2))  lo = m1;
            else hi = m2;
        }
        ll ans = 1e18;
        for (int i = lo; i <= hi; i++) ans = min(ans, f(i));

        return ans;
    }
};
#undef int
 
signed main() {
 
    Equidistance e;
    cout << e.minimumEffort({1, 4, 7, 10}) << endl;
    cout << e.minimumEffort({1, 3, 4}) << endl;
    cout << e.minimumEffort({3, 3, 3}) << endl;
    cout << e.minimumEffort({-2000000000, 2000000000}) << endl;
    cout << e.minimumEffort({1, 4, 7, 10}) << endl;
    cout << e.minimumEffort({ 2, 3, 4, 6, 8, 9, 10, 11, 12, 13, 14, 15, 16, 18 }) << endl;
 
    return 0;
}
