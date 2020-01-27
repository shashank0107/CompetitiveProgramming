/*
    Author : manu_sy
    Idea : meet in middle
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

const int N = 100+5;

/** Template Ends **/

int n;
map<int, int> m;

signed main() {

    IOS;
    cin >> n;
    vector<int> v(n);
    LP(i,n) cin >> v[i];
    for (auto a : v) for (auto b : v) for (auto c : v) {
        int res = a * b + c;
        m[res]++;
    }
    ll ans = 0;
    for (auto d : v) if (d != 0) for (auto e : v) for (auto f : v) {
        int res = (f + e) * d;
        ans += m[res];
    } 
    cout << ans << endl;

    return 0;
}
