/*
    Author : manu_sy
    Idea : Same as -
           https://github.com/aboodJAD/CompetitiveProgramming/blob/master/UVA/UVA%20557.cpp
*/
#include <bits/stdc++.h>
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
template<class TH> void _dbg(const char *sdbg, TH h){ cerr<<sdbg<<'='<<h<<endl; }
template<class TH, class... TA> void _dbg(const char *sdbg, TH h, TA... a) {
  while(*sdbg!=',')cerr<<*sdbg++;
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

signed main() {

    IOS;
    cout << fixed << setprecision(4);
    int t;  cin >> t;
    while (t--) {
        cin >> n;

        double ans = 1;
        int div = n-2;
        for (int i = 1, j = n/2; i <= n/2-1; i++, j++) {
            ans *= (1.0*j)/i;
            while (ans > 1 && div) {
                ans /= 2;
                div--;
            }
        }
        while (div) {
            ans /= 2;
            div--;
        }
        cout << 1 - ans << endl;
    }

    return 0;
}
